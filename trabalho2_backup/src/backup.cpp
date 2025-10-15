/**
 * @file backup.cpp
 * @brief Implementação do sistema de backup
 *
 * Contém a implementação das funções declaradas em backup.h,
 * seguindo a lógica da tabela de decisão fornecida.
 *
 * @author Rafael
 * @date 2024
 * @version 1.0
 *
 * @see backup.h
 */

#include "backup.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Construtor do SistemaBackup
 *
 * Inicializa o sistema com estado não configurado.
 *
 * @assertiva_entrada Nenhuma
 * @assertiva_saida Sistema inicializado com configurado_ = false
 */
SistemaBackup::SistemaBackup() : configurado_(false)
{
}

/**
 * @brief Executa procedimento de backup
 *
 * Implementa a lógica baseada na tabela de decisão.
 * - Coluna 1: Se não existe backup.parm → IMPOSSÍVEL
 * - Coluna 2: Se arquivo existe no HD mas NÃO no pendrive → backup realizado
 * - Coluna 3: Se arquivo existe em ambos MAS pendrive desatualizado → backup realizado
 *
 * @param dispositivo Caminho do dispositivo de backup
 * @return true se backup pode ser executado, false se impossível
 *
 * @assertiva_entrada dispositivo não é string vazia
 * @assertiva_saida Retorna true apenas se condições da tabela são atendidas
 */
bool SistemaBackup::executarBackup(const std::string &dispositivo)
{
    // Coluna 1: Verificar se arquivo de configuração existe
    if (!existeConfiguracao())
    {
        return false;
    }

    // Obter lista de arquivos do backup.parm
    std::vector<std::string> arquivos = listarArquivosBackup();
    if (arquivos.empty())
    {
        return false;
    }

    // Verificar condições para cada arquivo
    for (const auto &arquivo : arquivos)
    {
        // Verificar se arquivo existe no HD (condição comum a todas as colunas)
        if (!arquivoExisteHD(arquivo))
        {
            return false;
        }

        // Verificar se arquivo existe no pendrive
        bool existeNoPendrive = arquivoExistePendrive(arquivo, dispositivo);

        if (!existeNoPendrive)
        {
            // COLUNA 2: Arquivo não existe no pendrive → condição atendida
            continue;
        }

        // COLUNA 3: Arquivo existe no pendrive → verificar se está desatualizado
        int comparacaoDatas = compararDatas(arquivo, dispositivo);
        if (comparacaoDatas != -1)
        {
            // Pendrive NÃO está desatualizado → não fazer backup
            return false;
        }
        // Se chegou aqui, pendrive está desatualizado → condição da Coluna 3 atendida
    }

    // Se passou por todos os arquivos sem retornar false, condições atendidas
    return true;
}

/**
 * @brief Verifica existência do arquivo de configuração
 *
 * @return true se backup.parm existe e é legível, false caso contrário
 *
 * @assertiva_entrada Nenhuma
 * @assertiva_saida Retorna estado real do arquivo backup.parm
 */
bool SistemaBackup::existeConfiguracao() const
{
    ifstream arquivo("Backup.parm");
    return arquivo.good();
}

/**
 * @brief Lista arquivos configurados para backup
 *
 * Lê o arquivo Backup.parm linha por linha, ignorando linhas vazias
 * e comentários (linhas começando com #).
 *
 * @return Vector com paths dos arquivos para backup
 *
 * @assertiva_entrada Arquivo Backup.parm existe
 * @assertiva_saida Retorna lista não vazia se arquivo tem conteúdo válido
 */
std::vector<std::string> SistemaBackup::listarArquivosBackup() const
{
    std::vector<std::string> arquivos;
    ifstream arquivo("Backup.parm");
    std::string linha;

    while (getline(arquivo, linha))
    {
        // Ignorar linhas vazias e comentários
        if (!linha.empty() && linha[0] != '#')
        {
            arquivos.push_back(linha);
        }
    }

    return arquivos;
}

/**
 * @brief Verifica se arquivo existe no HD
 *
 * @param nomeArquivo Nome do arquivo a verificar
 * @return true se arquivo existe no HD, false caso contrário
 *
 * @assertiva_entrada nomeArquivo não é string vazia
 * @assertiva_saida Retorna existência real do arquivo no sistema
 */
bool SistemaBackup::arquivoExisteHD(const std::string &nomeArquivo) const
{
    // Verificação REAL se arquivo existe no HD
    ifstream arquivo(nomeArquivo);
    return arquivo.good();
}

/**
 * @brief Verifica se arquivo existe no pendrive
 *
 * @param nomeArquivo Nome do arquivo a verificar
 * @param dispositivo Caminho do dispositivo pendrive
 * @return true se arquivo existe no pendrive, false caso contrário
 *
 * @assertiva_entrada nomeArquivo e dispositivo não são strings vazias
 * @assertiva_saida Retorna existência real do arquivo no pendrive
 */
bool SistemaBackup::arquivoExistePendrive(const std::string &nomeArquivo, const std::string &dispositivo) const
{
    try
    {
        std::string caminhoCompleto = dispositivo + "/" + nomeArquivo;
        std::ifstream arquivo(caminhoCompleto);
        return arquivo.good();
    }
    catch (const std::exception &e)
    {
        return false; // Em caso de erro, assumir que não existe
    }
}

/**
 * @brief Compara datas entre HD e pendrive
 *
 * Implementação que usa diferença de conteúdo como proxy para versão.
 * Na implementação real, seria usado timestamp de modificação.
 *
 * @param nomeArquivo Nome do arquivo a comparar
 * @param dispositivo Caminho do dispositivo pendrive
 * @return -1 se PenD < HD (pendrive desatualizado), 0 se iguais, 1 se PenD > HD
 *
 * @assertiva_entrada nomeArquivo e dispositivo não são strings vazias
 * @assertiva_saida Retorna comparação baseada em diferença de conteúdo
 */
int SistemaBackup::compararDatas(const std::string &nomeArquivo, const std::string &dispositivo) const
{
    try
    {
        std::string caminhoPendrive = dispositivo + "/" + nomeArquivo;

        // Verificar se ambos arquivos existem
        std::ifstream hdFile(nomeArquivo);
        std::ifstream pendriveFile(caminhoPendrive);

        if (!hdFile.is_open() || !pendriveFile.is_open())
        {
            return 0; // Não conseguiu comparar
        }

        // Estratégia: comparar conteúdo como proxy para versão
        std::string conteudoHD, conteudoPendrive;
        std::getline(hdFile, conteudoHD);
        std::getline(pendriveFile, conteudoPendrive);

        // Se conteúdos são diferentes, considerar HD como mais recente
        // (isso simula Data PenD < HD para Coluna 3)
        if (conteudoHD != conteudoPendrive)
        {
            return -1; // Pendrive desatualizado
        }

        return 0; // Conteúdos iguais
    }
    catch (const std::exception &e)
    {
        // Em caso de erro, assumir que não é possível fazer backup
        return 0;
    }
}