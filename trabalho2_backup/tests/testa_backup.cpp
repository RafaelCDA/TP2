/**
 * @file testa_backup.cpp
 * @brief Testes unitários para o sistema de backup
 *
 * Desenvolvido seguindo TDD baseado na tabela de decisão.
 * Cada TEST_CASE corresponde a uma coluna da tabela.
 *
 * @author Rafael
 * @date 2024
 * @version 1.0
 *
 * @see backup.h
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/backup.h"

/**
 * @test Coluna 1 da tabela de decisão
 * @brief Backup impossível quando não existe backup.parm
 *
 * Condições:
 * - Tem backup.parm: F (NÃO)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: F (NÃO)
 *
 * Ação esperada: IMPOSSÍVEL
 *
 * @see Tabela de Decisão - Coluna 1
 */
TEST_CASE("Coluna 1: Backup impossível quando não existe backup.parm", "[backup][decisao]")
{
    // Arrange - Configurar cenário da coluna 1
    SistemaBackup sistema;
    std::string dispositivo = "/mnt/pendrive";

    // Garantir que backup.parm não existe
    std::remove("Backup.parm");

    // Act - Tentar executar backup
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar falso (impossível)
    REQUIRE(resultado == false);
}

/**
 * @test Teste de inicialização do sistema
 * @brief Sistema deve inicializar corretamente
 */
TEST_CASE("Sistema deve inicializar corretamente", "[inicializacao]")
{
    SistemaBackup sistema;
    // Teste de inicialização básica
    REQUIRE(sistema.existeConfiguracao() == false); // Inicialmente sem config
}
/**
 * @test Coluna 2 da tabela de decisão
 * @brief Backup quando arquivo existe em ambos mas pendrive está desatualizado
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)
 * - Data PenD < HD: V (SIM) - Pendrive desatualizado
 *
 * Ação esperada: HD para Pen-drive (fazer backup)
 *
 * @see Tabela de Decisão - Coluna 2
 */
TEST_CASE("Coluna 2: Backup quando pendrive está desatualizado", "[backup][decisao]")
{
    // Arrange - Cenário da Coluna 2
    SistemaBackup sistema;
    std::string dispositivo = "/mnt/pendrive";

    // Garantir que backup.parm EXISTE (condição V)
    std::ofstream arquivo("Backup.parm");
    arquivo << "arquivo.txt" << std::endl;
    arquivo.close();

    // Act - Executar backup
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar true (backup realizado)
    REQUIRE(resultado == true);
}