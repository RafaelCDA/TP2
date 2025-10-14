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
#include <cstdio>

using namespace std;

/**
 * @brief Construtor do SistemaBackup
 *
 * Inicializa o sistema com estado não configurado.
 */
SistemaBackup::SistemaBackup() : configurado_(false)
{
}

/**
 * @brief Executa procedimento de backup
 *
 * Implementa a lógica baseada na tabela de decisão.
 * Coluna 1: Se não existe backup.parm → IMPOSSÍVEL
 *
 * @param dispositivo Caminho do dispositivo de backup
 * @return true se backup executado, false se impossível
 */
bool SistemaBackup::executarBackup(const std::string &dispositivo)
{
    // Coluna 1: Se não existe backup.parm → IMPOSSÍVEL
    if (!existeConfiguracao())
    {
        return false;
    }

    // Para outras colunas serão implementadas depois
    return true;
}

/**
 * @brief Verifica existência do arquivo de configuração
 *
 * @return true se backup.parm existe, false caso contrário
 */
bool SistemaBackup::existeConfiguracao() const
{
    ifstream arquivo("Backup.parm");
    return arquivo.good();
}