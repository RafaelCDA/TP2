#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/backup.h"

TEST_CASE("Coluna 1: Backup impossível quando não existe backup.parm", "[backup][decisao]")
{
    // Arrange
    std::string dispositivo = "/mnt/pendrive";

    // Act
    bool resultado = executarBackup(dispositivo);

    // Assert
    REQUIRE(resultado == false);
}