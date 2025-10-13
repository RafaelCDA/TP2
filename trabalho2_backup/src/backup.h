#ifndef BACKUP_H
#define BACKUP_H

#include <string>
#include <vector>

/**
 * @brief Sistema de backup e restauração de arquivos
 *
 * Sistema que permite fazer backup e restauração de arquivos
 * baseado em lista definida no arquivo Backup.parm
 */
class SistemaBackup
{
public:
    /**
     * @brief Inicializa o sistema de backup
     * @return true se inicialização foi bem-sucedida
     * @return false se houve erro na inicialização
     *
     * @assertiva_entrada Nenhuma
     * @assertiva_saida Sistema está pronto para operar
     */
    bool inicializar();

    /**
     * @brief Executa procedimento de backup
     * @param dispositivo Caminho do dispositivo de backup
     * @return true se backup foi executado com sucesso
     * @return false se houve erro no backup
     *
     * @assertiva_entrada dispositivo não é string vazia
     * @assertiva_saida Arquivos foram copiados para o dispositivo
     */
    bool executarBackup(const std::string &dispositivo);

    /**
     * @brief Lista arquivos configurados para backup
     * @return Vector com paths dos arquivos para backup
     *
     * @assertiva_entrada Arquivo Backup.parm existe
     * @assertiva_saida Retorna lista não vazia se arquivo existe
     */
    std::vector<std::string> listarArquivosBackup() const;
};

#endif