/**
 * @file backup.h
 * @brief Sistema de backup e restauração baseado em TDD
 *
 * Implementa um sistema de backup que segue a tabela de decisão
 * fornecida, desenvolvido com metodologia TDD (Test-Driven Development).
 *
 * @author Rafael
 * @date 2024
 * @version 1.0
 */

#ifndef BACKUP_H
#define BACKUP_H

#include <string>

/**
 * @brief Classe principal do sistema de backup
 *
 * Responsável por gerenciar operações de backup e restauração
 * baseadas na tabela de decisão fornecida no trabalho.
 */
class SistemaBackup
{
public:
    /**
     * @brief Construtor do sistema de backup
     *
     * Inicializa o sistema verificando a existência do arquivo
     * de configuração Backup.parm.
     *
     * @assertiva_entrada Nenhuma
     * @assertiva_saida Sistema pronto para operar
     */
    SistemaBackup();

    /**
     * @brief Executa procedimento de backup
     *
     * Implementa a lógica da tabela de decisão para determinar
     * se o backup pode ser executado baseado nas condições.
     *
     * @param dispositivo Caminho do dispositivo de backup (pendrive/diretório)
     * @return true se backup foi executado com sucesso
     * @return false se houve erro ou condição impossível
     *
     * @assertiva_entrada dispositivo não é string vazia
     * @assertiva_saida Retorna true apenas se backup foi realizado conforme tabela
     */
    bool executarBackup(const std::string &dispositivo);

    /**
     * @brief Verifica existência do arquivo de configuração
     *
     * @return true se backup.parm existe e é legível
     * @return false se arquivo não existe ou não pode ser lido
     *
     * @assertiva_entrada Nenhuma
     * @assertiva_saida Retorna estado atual do arquivo
     */
    bool existeConfiguracao() const;

private:
    bool configurado_; ///< Flag indicando se sistema está configurado
};

#endif