#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/backup.h"

TEST_CASE("Coluna 1: Backup impossível quando não existe backup.parm", "[backup][decisao]")
{

    std::string dispositivo = "/mnt/pendrive";

    bool resultado = executarBackup(dispositivo);

    REQUIRE(resultado == false);
}