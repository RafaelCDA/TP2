#ifndef BACKUP_H
#define BACKUP_H

#include <string>

/*********************************************************************
 * Função: executarBackup
 * Descrição: Executa procedimento de backup
 * Parâmetros: dispositivo - caminho do dispositivo de backup
 * Assertiva de entrada: dispositivo não é string vazia
 * Assertiva de saída: Retorna true se backup realizado com sucesso
 *********************************************************************/
bool executarBackup(const std::string &dispositivo);

/*********************************************************************
 * Função: existeConfiguracao
 * Descrição: Verifica se arquivo de configuração existe
 * Assertiva de entrada: Nenhuma
 * Assertiva de saída: Retorna estado do arquivo backup.parm
 *********************************************************************/
bool existeConfiguracao();

#endif