/**
 * @file backup.h
 * @brief Sistema de backup e restauração baseado em TDD
 *
 * @author Rafael
 * @date 2024
 * @version 1.0
 */

#ifndef BACKUP_H
#define BACKUP_H

#include <string>
#include <vector>

/**
 * @brief Classe principal do sistema de backup
 */
class SistemaBackup
{
public:
    /**
     * @brief Construtor do sistema de backup
     */
    SistemaBackup();

    /**
     * @brief Executa procedimento de backup
     */
    bool executarBackup(const std::string &dispositivo);

    /**
     * @brief Verifica existência do arquivo de configuração
     */
    bool existeConfiguracao() const;

    /**
     * @brief Lista arquivos configurados para backup
     */
    std::vector<std::string> listarArquivosBackup() const;

    /**
     * @brief Verifica se arquivo existe no HD
     */
    bool arquivoExisteHD(const std::string &nomeArquivo) const;

    /**
     * @brief Verifica se arquivo existe no pendrive
     */
    bool arquivoExistePendrive(const std::string &nomeArquivo, const std::string &dispositivo) const;

    /**
     * @brief Compara datas entre HD e pendrive
     */
    int compararDatas(const std::string &nomeArquivo, const std::string &dispositivo) const;

private:
    bool configurado_;
};

#endif