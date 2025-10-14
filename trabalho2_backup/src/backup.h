/**
 * @file backup.h
 * @brief Sistema de backup e restauração baseado em TDD
 *
 * Implementa um sistema de backup que segue a tabela de decisão
 * fornecida, desenvolvido com metodologia TDD (Test-Driven Development).
 *
 * @author Seu Nome
 * @date 2024
 * @version 1.0
 *
 * @see https://github.com/seu-usuario/tecnicas-programacao-2
 */

#ifndef BACKUP_H
#define BACKUP_H

#include <string>
#include <vector>

/**
 * @brief Classe principal do sistema de backup
 *
 * Responsável por gerenciar operações de backup e restauração
 * baseadas na tabela de decisão fornecida no trabalho.
 *
 * Desenvolvido seguindo TDD com Catch2 e com cobertura mínima de 80%.
 *
 * @assertiva_geral Todas as funções seguem a tabela de decisão
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
     * se o backup pode ser executado baseado nas condições:
     * - Existência do backup.parm
     * - Disponibilidade do dispositivo
     * - Estado dos arquivos
     *
     * @param dispositivo Caminho do dispositivo de backup (pendrive/diretório)
     * @return true se backup foi executado com sucesso
     * @return false se houve erro ou condição impossível
     *
     * @assertiva_entrada dispositivo não é string vazia
     * @assertiva_saida Retorna true apenas se backup foi realizado conforme tabela
     *
     * @test Testado em testa_backup.cpp - Coluna 1 da tabela
     */
    bool executarBackup(const std::string &dispositivo);

    /**
     * @brief Executa procedimento de restauração
     *
     * Restaura arquivos do dispositivo de backup para o HD
     * seguindo as regras da tabela de decisão.
     *
     * @param dispositivo Caminho do dispositivo de restauração
     * @return true se restauração foi bem-sucedida
     * @return false se houve erro na restauração
     *
     * @assertiva_entrada dispositivo contém backup válido
     * @assertiva_saida Arquivos são restaurados mantendo integridade
     */
    bool executarRestauracao(const std::string &dispositivo);

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

    /**
     * @brief Lista arquivos configurados para backup
     *
     * Lê o arquivo Backup.parm e retorna a lista de arquivos
     * que devem ser incluídos no backup.
     *
     * @return Vector com paths absolutos dos arquivos
     *
     * @assertiva_entrada Arquivo Backup.parm existe
     * @assertiva_saida Retorna lista não vazia se arquivo existe e é válido
     */
    std::vector<std::string> listarArquivosBackup() const;

private:
    /**
     * @brief Verifica se arquivo existe no sistema
     *
     * @param caminho Path do arquivo a verificar
     * @return true se arquivo existe e é acessível
     *
     * @assertiva_entrada caminho não é vazio
     * @assertiva_saida Retorna existência real do arquivo
     */
    bool arquivoExiste(const std::string &caminho) const;

    std::vector<std::string> arquivosBackup_; ///< Lista de arquivos para backup
    bool configurado_;                        ///< Flag de configuração carregada
};

// Funções auxiliares (se necessário)

/**
 * @brief Verifica disponibilidade de dispositivo
 *
 * @param dispositivo Caminho do dispositivo
 * @return true se dispositivo está disponível e tem espaço
 *
 * @assertiva_entrada dispositivo não é vazio
 * @assertiva_saida Retorna disponibilidade real
 */
bool verificarDispositivo(const std::string &dispositivo);

#endif