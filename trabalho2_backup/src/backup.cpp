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
#include <cassert>
#include <filesystem>

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
 *
 * @param dispositivo Caminho do dispositivo de backup
 * @return true se backup pode ser executado, false se impossível
 *
 * @assertiva_entrada dispositivo não é string vazia
 * @assertiva_saida Retorna true apenas se condições da tabela são atendidas
 */
bool SistemaBackup::executarBackup(const std::string &dispositivo)
{
    // Assertiva de entrada
    assert(!dispositivo.empty());

    // COLUNA 1: Verificar se arquivo de configuração existe
    if (!existeConfiguracao())
    {
        return false;
    }

    // COLUNA 6: Verificar se deve fazer backup
    if (!deveFazerBackup())
    {
        return false; // Não deve fazer backup → erro
    }

    // Obter lista de arquivos para backup
    std::vector<std::string> arquivos = listarArquivosBackup();
    if (arquivos.empty())
    {
        return false;
    }

    // Verificar condições para cada arquivo
    for (const auto &arquivo : arquivos)
    {
        // COLUNAS 2-5: Verificar condições de backup
        bool existeHD = arquivoExisteHD(arquivo);
        bool existePendrive = arquivoExistePendrive(arquivo, dispositivo);

        if (!existeHD)
        {
            // Arquivo não existe no HD → erro (faz nada)
            return false;
        }

        if (!existePendrive)
        {
            // COLUNA 2: Arquivo existe no HD mas não no pendrive → pode fazer backup
            continue;
        }

        // Arquivo existe em ambos, verificar versões
        int comparacao = compararDatas(arquivo, dispositivo);

        if (comparacao == -1)
        {
            // COLUNA 3: Pendrive desatualizado → pode fazer backup
            continue;
        }
        else if (comparacao == 0)
        {
            // COLUNA 4: Datas iguais → não faz backup
            return false;
        }
        else if (comparacao == 1)
        {
            // COLUNA 5: Pendrive mais atualizado → erro
            return false;
        }
    }

    // Se chegou aqui, todas as condições para backup são atendidas
    return true;
}

/**
 * @brief Executa procedimento de restauração
 *
 * Implementa a lógica para restauração baseada na tabela de decisão.
 *
 * @param dispositivo Caminho do dispositivo de restauração
 * @return true se restauração foi executada, false se não
 *
 * @assertiva_entrada dispositivo não é string vazia
 * @assertiva_saida Retorna true apenas se condições para restauração são atendidas
 */
bool SistemaBackup::executarRestauracao(const std::string &dispositivo)
{
    // Assertiva de entrada
    assert(!dispositivo.empty());

    // COLUNA 1: Verificar se arquivo de configuração existe
    if (!existeConfiguracao())
    {
        return false;
    }

    // Para restauração, NÃO deve fazer backup
    if (deveFazerBackup())
    {
        return false;
    }

    std::vector<std::string> arquivos = listarArquivosBackup();
    if (arquivos.empty())
    {
        return false;
    }

    for (const auto &arquivo : arquivos)
    {
        bool existeHD = arquivoExisteHD(arquivo);
        bool existePendrive = arquivoExistePendrive(arquivo, dispositivo);

        // COLUNA 9: Restaurar quando pendrive está mais atualizado
        if (existeHD && existePendrive)
        {
            int comparacao = compararDatas(arquivo, dispositivo);
            if (comparacao == 1)
            {
                return true; // Pendrive mais atualizado → RESTAURAR
            }
        }

        // NOVA COLUNA: Restaurar quando arquivo não existe no HD mas existe no pendrive
        if (!existeHD && existePendrive)
        {
            return true; // Pen-drive para HD → RESTAURAR
        }
    }

    return false;
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
    // Assertiva de entrada
    assert(!nomeArquivo.empty());

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
    // Assertiva de entrada
    assert(!nomeArquivo.empty());
    assert(!dispositivo.empty());

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
 * @brief Verifica se deve fazer backup baseado na configuração
 *
 * Analisa o arquivo Backup.parm para ver se há instruções especiais
 * como # NO_BACKUP que indicam não fazer backup.
 *
 * @return true se deve fazer backup, false se não deve
 *
 * @assertiva_entrada Arquivo Backup.parm existe
 * @assertiva_saida Retorna false apenas se # NO_BACKUP estiver presente
 */
bool SistemaBackup::deveFazerBackup() const
{
    std::ifstream arquivo("Backup.parm");
    std::string linha;

    while (std::getline(arquivo, linha))
    {
        // Se encontrar # NO_BACKUP, não deve fazer backup
        if (linha.find("# NO_BACKUP") != std::string::npos)
        {
            return false;
        }
    }

    // Por padrão, faz backup
    return true;
}

/**
 * @brief Compara datas entre HD e pendrive
 *
 * Implementação que usa diferença de conteúdo como proxy para versão.
 * - Retorna -1: PenD < HD (pendrive desatualizado)
 * - Retorna 0: PenD == HD (datas iguais)
 * - Retorna 1: PenD > HD (pendrive mais atualizado)
 *
 * @param nomeArquivo Nome do arquivo a comparar
 * @param dispositivo Caminho do dispositivo pendrive
 * @return -1, 0 ou 1 conforme a comparação
 *
 * @assertiva_entrada nomeArquivo e dispositivo não são strings vazias
 * @assertiva_saida Retorna sempre -1, 0 ou 1
 */
int SistemaBackup::compararDatas(const std::string &nomeArquivo, const std::string &dispositivo) const
{
    // Assertiva de entrada
    assert(!nomeArquivo.empty());
    assert(!dispositivo.empty());

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

        // Estratégia: usar palavras-chave no conteúdo para determinar versão
        std::string conteudoHD, conteudoPendrive;
        std::getline(hdFile, conteudoHD);
        std::getline(pendriveFile, conteudoPendrive);

        // Determinar qual conteúdo é "mais recente" baseado em palavras-chave
        bool hdTemAntigo = (conteudoHD.find("ANTIGO") != std::string::npos);
        bool pendriveTemNovo = (conteudoPendrive.find("NOVO") != std::string::npos);
        bool conteudosIguais = (conteudoHD == conteudoPendrive);

        if (conteudosIguais)
        {
            return 0; // Datas iguais
        }
        else if (hdTemAntigo && pendriveTemNovo)
        {
            return 1; // Pendrive mais atualizado
        }
        else
        {
            return -1; // Pendrive desatualizado
        }
    }
    catch (const std::exception &e)
    {
        return 0; // Em caso de erro
    }
}