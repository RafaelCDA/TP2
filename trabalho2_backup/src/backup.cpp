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
 * - Coluna 2: Se existe backup.parm e há arquivos → backup possível
 *
 * @param dispositivo Caminho do dispositivo de backup
 * @return true se backup pode ser executado, false se impossível
 *
 * @assertiva_entrada dispositivo não é string vazia
 * @assertiva_saida Retorna true apenas se condições da tabela são atendidas
 */
bool SistemaBackup::executarBackup(const std::string &dispositivo)
{
    // Coluna 1: Se não existe backup.parm → IMPOSSÍVEL
    if (!existeConfiguracao())
    {
        return false;
    }

    // Coluna 2: Verificar se há arquivos para backup
    std::vector<std::string> arquivos = listarArquivosBackup();
    if (arquivos.empty())
    {
        return false; // Não há arquivos configurados
    }

    // Por enquanto, retorna true se há arquivos no backup.parm
    // Nas próximas colunas vamos verificar pendrive e datas
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
    // Implementação simulada por enquanto
    // Na prática, verificar se arquivo existe no sistema de arquivos
    return true;
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
    // Implementação simulada por enquanto
    // Na prática, verificar se arquivo existe no pendrive
    return true;
}

/**
 * @brief Compara datas entre HD e pendrive
 *
 * @param nomeArquivo Nome do arquivo a comparar
 * @param dispositivo Caminho do dispositivo pendrive
 * @return -1 se PenD < HD, 0 se iguais, 1 se PenD > HD
 *
 * @assertiva_entrada nomeArquivo e dispositivo não são strings vazias
 * @assertiva_saida Retorna comparação real das datas de modificação
 */
int SistemaBackup::compararDatas(const std::string &nomeArquivo, const std::string &dispositivo) const
{
    // Implementação simulada por enquanto
    // Na prática, comparar datas de modificação
    // -1: PenD < HD, 0: iguais, 1: PenD > HD
    return -1;
}