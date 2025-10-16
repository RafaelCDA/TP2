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
#include <fstream>

// ============================================================================
// TESTES DA TABELA DE DECISÃO - ORDENADOS POR COLUNA
// ============================================================================

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
 * @test Coluna 2 da tabela de decisão
 * @brief Backup quando arquivo existe no HD mas NÃO no pendrive
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: F (NÃO)
 *
 * Ação esperada: HD para Pen-drive (fazer backup)
 */
TEST_CASE("Coluna 2: Backup quando arquivo não existe no pendrive", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "/mnt/pendrive";

    // Garantir que backup.parm não existe inicialmente
    std::remove("Backup.parm");

    // Criar backup.parm
    std::ofstream arquivo("Backup.parm");
    arquivo << "documento.txt" << std::endl;
    arquivo.close();

    // Criar arquivo no HD (condição: ArqX ∈ HD: V)
    std::ofstream hdFile("documento.txt");
    hdFile << "conteudo do arquivo" << std::endl;
    hdFile.close();

    // NÃO criar arquivo no pendrive (condição: ArqX ∈ Pen-drive: F)
    // Isso simula que o arquivo só existe no HD

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar TRUE (backup realizado)
    REQUIRE(resultado == true);
}

/**
 * @test Coluna 3 da tabela de decisão
 * @brief Backup quando arquivo existe em ambos e pendrive está desatualizado
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)
 * - Data PenD < HD: V (SIM)
 *
 * Ação esperada: HD para Pen-drive (fazer backup)
 */
TEST_CASE("Coluna 3: Backup quando pendrive está desatualizado", "[backup][decisao]")
{
    // Arrange - Usando diretório local em vez de /mnt/pendrive
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA TOTAL
    std::remove("Backup.parm");
    std::remove("documento.txt");
    system("rm -rf pendrive_teste");

    // Configuração ESPECÍFICA da Coluna 3:
    // 1. backup.parm existe
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config.close();

    // 2. Arquivo existe no HD (conteúdo ATUALIZADO)
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_NOVO_HD" << std::endl;
    hdFile.close();

    // 3. Arquivo existe no "pendrive" (diretório local com conteúdo ANTIGO)
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_ANTIGO_PENDRIVE" << std::endl;
    pendriveFile.close();

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    REQUIRE(resultado == true);
}

/**
 * @test Coluna 4 da tabela de decisão
 * @brief Não fazer backup quando datas são iguais
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)
 * - Data PenD == HD: V (SIM)
 *
 * Ação esperada: faz nada (não fazer backup)
 */
TEST_CASE("Coluna 4: Não fazer backup quando datas são iguais", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento.txt");
    system("rm -rf pendrive_teste");

    // Configuração para Coluna 4:
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config.close();

    // MESMO conteúdo em ambos = datas "iguais"
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_IDENTICO" << std::endl;
    hdFile.close();

    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_IDENTICO" << std::endl;
    pendriveFile.close();

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - DEVE ser false (Coluna 4)
    REQUIRE(resultado == false);
}

/**
 * @test Coluna 5 da tabela de decisão
 * @brief Retornar erro quando pendrive está mais atualizado que HD
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)
 * - Data PenD > HD: V (SIM)
 *
 * Ação esperada: erro (não fazer backup)
 */
TEST_CASE("Coluna 5: Erro quando pendrive está mais atualizado que HD", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento.txt");
    system("rm -rf pendrive_teste");

    // Configuração ESPECÍFICA da Coluna 5:
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config.close();

    // Arquivo existe no HD (conteúdo ANTIGO)
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_ANTIGO_HD" << std::endl;
    hdFile.close();

    // Arquivo existe no pendrive com conteúdo MAIS RECENTE
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_NOVO_PENDRIVE" << std::endl;
    pendriveFile.close();

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar FALSE (erro - pendrive mais atualizado)
    REQUIRE(resultado == false);
}

/**
 * @test Coluna 6 da tabela de decisão
 * @brief Erro quando configuração diz para não fazer backup mas condições permitiriam
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: F (NÃO)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: F (NÃO)
 *
 * Ação esperada: erro
 */
TEST_CASE("Coluna 6: Erro quando não deve fazer backup mas condições permitiriam", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento.txt");
    system("rm -rf pendrive_teste");

    // Configuração ESPECÍFICA da Coluna 6:
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl;
    config.close();

    // Arquivo existe no HD
    std::ofstream hdFile("documento.txt");
    hdFile << "conteudo" << std::endl;
    hdFile.close();

    // Arquivo NÃO existe no pendrive
    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar FALSE (erro - não deve fazer backup)
    REQUIRE(resultado == false);
}

/**
 * @test Coluna 7 da tabela de decisão
 * @brief Erro quando não deve fazer backup mas pendrive está desatualizado
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: F (NÃO)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)
 * - Data PenD < HD: V (SIM)
 *
 * Ação esperada: erro
 */
TEST_CASE("Coluna 7: Erro quando não deve fazer backup mas pendrive está desatualizado", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento.txt");
    system("rm -rf pendrive_teste");

    // Configuração ESPECÍFICA da Coluna 7:
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl;
    config.close();

    // Arquivo existe no HD (conteúdo NOVO)
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_NOVO_HD" << std::endl;
    hdFile.close();

    // Arquivo existe no pendrive (conteúdo ANTIGO - desatualizado)
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_ANTIGO_PENDRIVE" << std::endl;
    pendriveFile.close();

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar FALSE (erro - não deve fazer backup)
    REQUIRE(resultado == false);
}

/**
 * @test Coluna 8 da tabela de decisão
 * @brief Não fazer backup quando configuração proíbe e datas são iguais
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: F (NÃO)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)
 * - Data PenD == HD: V (SIM)
 *
 * Ação esperada: faz nada (não fazer backup)
 */
TEST_CASE("Coluna 8: Não fazer backup quando configuração proíbe e datas são iguais", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento.txt");
    system("rm -rf pendrive_teste");

    // Configuração ESPECÍFICA da Coluna 8:
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl;
    config.close();

    // Arquivo existe no HD
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_IGUAL" << std::endl;
    hdFile.close();

    // Arquivo existe no pendrive com MESMO conteúdo
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_IGUAL" << std::endl;
    pendriveFile.close();

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar FALSE (não fazer backup)
    REQUIRE(resultado == false);
}

/**
 * @test Coluna 9 da tabela de decisão
 * @brief Restaurar do pendrive para HD quando pendrive está mais atualizado
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: F (NÃO)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)
 * - Data PenD > HD: V (SIM)
 *
 * Ação esperada: pen drive para hd (RESTAURAR)
 */
TEST_CASE("Coluna 9: Restaurar do pendrive para HD quando pendrive mais atualizado", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento.txt");
    system("rm -rf pendrive_teste");

    // Configuração ESPECÍFICA da Coluna 9:
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl;
    config.close();

    // Arquivo existe no HD (conteúdo ANTIGO)
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_ANTIGO_HD" << std::endl;
    hdFile.close();

    // Arquivo existe no pendrive (conteúdo NOVO - mais atualizado)
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_NOVO_PENDRIVE" << std::endl;
    pendriveFile.close();

    bool resultado = sistema.executarRestauracao(dispositivo);

    // Assert - Deve retornar TRUE (restauração realizada)
    REQUIRE(resultado == true);
}

/**
 * @test Coluna 10 da tabela de decisão
 * @brief Erro quando arquivo não existe no HD
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: F (NÃO)
 * - ArqX ∈ Pen-drive: F (NÃO)
 *
 * Ação esperada: erro
 */
TEST_CASE("Coluna 10: Erro quando arquivo não existe no HD", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento_inexistente.txt");
    system("rm -rf pendrive_teste");

    // Configuração para Coluna 10:
    std::ofstream config("Backup.parm");
    config << "documento_inexistente.txt" << std::endl;
    config.close();

    // Arquivo NÃO existe no HD
    // Arquivo NÃO existe no pendrive

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar FALSE (erro - arquivo não existe no HD)
    REQUIRE(resultado == false);
}

/**
 * @test Coluna 11 da tabela de decisão
 * @brief Faz nada quando arquivo não existe no HD mas existe no pendrive
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: F (NÃO)
 * - ArqX ∈ Pen-drive: V (SIM)
 *
 * Ação esperada: faz nada (não faz backup)
 */
TEST_CASE("Coluna 11: Faz nada quando arquivo não existe no HD mas existe no pendrive", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento_inexistente_hd.txt");
    system("rm -rf pendrive_teste");

    // Configuração para Coluna 11:
    std::ofstream config("Backup.parm");
    config << "documento_inexistente_hd.txt" << std::endl;
    config.close();

    // Arquivo NÃO existe no HD
    // Arquivo EXISTE no pendrive
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento_inexistente_hd.txt");
    pendriveFile << "CONTEUDO_NO_PENDRIVE" << std::endl;
    pendriveFile.close();

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar FALSE (faz nada - não faz backup)
    REQUIRE(resultado == false);
}

/**
 * @test Coluna 12 da tabela de decisão
 * @brief Erro quando não deve fazer backup e arquivo não existe em nenhum lugar
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: F (NÃO)
 * - ArqX ∈ HD: F (NÃO)
 * - ArqX ∈ Pen-drive: F (NÃO)
 *
 * Ação esperada: erro
 */
TEST_CASE("Coluna 12: Erro quando não deve fazer backup e arquivo não existe em nenhum lugar", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA COMPLETA
    std::remove("Backup.parm");
    std::remove("arquivo_inexistente.txt");
    system("rm -rf pendrive_teste");

    // Configuração para Coluna 12:
    std::ofstream config("Backup.parm");
    config << "arquivo_inexistente.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl;
    config.close();

    // Arquivo NÃO existe no HD
    // Arquivo NÃO existe no pendrive
    system("mkdir -p pendrive_teste");

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Ação: erro (retorna false)
    REQUIRE(resultado == false);
}

/**
 * @test Coluna 13 da tabela de decisão
 * @brief Restaurar quando arquivo só existe no pendrive
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: F (NÃO)
 * - ArqX ∈ HD: F (NÃO)
 * - ArqX ∈ Pen-drive: V (SIM)
 *
 * Ação esperada: pen-drive para hd (RESTAURAR)
 */
TEST_CASE("Coluna 13: Restaurar quando arquivo só existe no pendrive", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA COMPLETA
    std::remove("Backup.parm");
    std::remove("arquivo_restaurar.txt");
    system("rm -rf pendrive_teste");

    // Configuração para Coluna 13:
    std::ofstream config("Backup.parm");
    config << "arquivo_restaurar.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl;
    config.close();

    // Arquivo NÃO existe no HD
    // Arquivo EXISTE no pendrive
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/arquivo_restaurar.txt");
    pendriveFile << "conteudo_para_restaurar" << std::endl;
    pendriveFile.close();

    // Act
    bool resultado = sistema.executarRestauracao(dispositivo);

    // Assert - Ação: pen-drive para hd (RESTAURAR) - deve retornar true
    REQUIRE(resultado == true);
}
/**
 * @test Teste de listagem de arquivos
 * @brief Deve listar arquivos do backup.parm corretamente
 */
TEST_CASE("Deve listar arquivos do backup.parm", "[configuracao]")
{
    // Arrange
    SistemaBackup sistema;

    // Criar backup.parm
    std::ofstream arquivo("Backup.parm");
    arquivo << "arquivo1.txt" << std::endl;
    arquivo << "# comentario" << std::endl;
    arquivo << "arquivo2.jpg" << std::endl;
    arquivo << "" << std::endl;
    arquivo.close();

    // Act
    auto arquivos = sistema.listarArquivosBackup();

    // Assert
    REQUIRE(arquivos.size() == 2);
    REQUIRE(arquivos[0] == "arquivo1.txt");
    REQUIRE(arquivos[1] == "arquivo2.jpg");
}