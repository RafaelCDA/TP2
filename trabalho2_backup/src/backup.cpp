#include "backup.h"
#include <fstream>
#include <filesystem>

using namespace std;

bool executarBackup(const std::string &dispositivo)
{
    // Implementação MÍNIMA para compilar (teste irá falhar)
    return true;
}

bool existeConfiguracao()
{
    // Verifica se arquivo backup.parm existe
    ifstream arquivo("Backup.parm");
    return arquivo.good();
}