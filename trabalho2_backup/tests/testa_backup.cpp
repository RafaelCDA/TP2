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
 * @brief Backup quando arquivo existe no HD mas NÃO no pendrive
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: F (NÃO)  // ← DIFERENÇA CHAVE!
 * - Data PenD < HD: V (SIM)     // ← Irrelevante (arquivo não existe no pendrive)
 *
 * Ação esperada: HD para Pen-drive (fazer backup)
 *
 * @see Tabela de Decisão - Coluna 2
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
    arquivo << "" << std::endl; // linha vazia
    arquivo.close();

    // Act
    auto arquivos = sistema.listarArquivosBackup();

    // Assert - Deve ignorar comentários e linhas vazias
    REQUIRE(arquivos.size() == 2);
    REQUIRE(arquivos[0] == "arquivo1.txt");
    REQUIRE(arquivos[1] == "arquivo2.jpg");
}
/**
 * @test Coluna 3 da tabela de decisão
 * @brief Backup quando arquivo existe em ambos e pendrive está desatualizado
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)  // ← DIFERENÇA!
 * - Data PenD < HD: V (SIM)     // ← DIFERENÇA!
 *
 * Ação esperada: HD para Pen-drive (fazer backup)
 *
 * @see Tabela de Decisão - Coluna 3
 */
/**
 * @test Cenário onde backup NÃO deve ocorrer
 * @brief Não fazer backup quando pendrive está atualizado
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)
 * - Data PenD >= HD: V (pendrive atualizado ou igual)
 *
 * Ação esperada: NÃO fazer backup
 *
 * @see Tabela de Decisão - Colunas onde backup NÃO ocorre
 */
/**
 * @test Coluna 3 da tabela de decisão
 * @brief Backup quando arquivo existe em ambos e pendrive está desatualizado
 *
 * Condições ESPECÍFICAS da Coluna 3:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)  // ← DIFERENÇA da Coluna 2!
 * - Data PenD < HD: V (SIM)     // ← CONDIÇÃO NÃO IMPLEMENTADA!
 *
 * Ação esperada: HD para Pen-drive (fazer backup)
 *
 * @see Tabela de Decisão - Coluna 3
 */
TEST_CASE("Coluna 3: Backup quando pendrive está desatualizado", "[backup][decisao]")
{
    // Arrange - Usando diretório local em vez de /mnt/pendrive
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste"; // ← DIRETÓRIO LOCAL

    // LIMPEZA TOTAL
    std::remove("Backup.parm");
    std::remove("documento.txt");
    system("rm -rf pendrive_teste"); // ← Limpa diretório local

    // Configuração ESPECÍFICA da Coluna 3:
    // 1. backup.parm existe
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config.close();

    // 2. Arquivo existe no HD (conteúdo ATUALIZADO)
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_NOVO_HD" << std::endl; // Versão NOVA
    hdFile.close();

    // 3. Arquivo existe no "pendrive" (diretório local com conteúdo ANTIGO)
    system("mkdir -p pendrive_teste"); // ← Diretório local
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_ANTIGO_PENDRIVE" << std::endl; // Versão ANTIGA
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
 * - Tem backup.parm: V (SIM) - assumido das colunas anteriores
 * - Faz backup: V (SIM) - assumido
 * - ArqX ∈ HD: V (SIM) - assumido
 * - ArqX ∈ Pen-drive: V (SIM) - assumido
 * - Data PenD < HD: F (NÃO)
 * - Data PenD == HD: V (SIM)
 * - Data PenD > HD: F (NÃO)
 *
 * Ação esperada: faz nada (não fazer backup)
 *
 * @see Tabela de Decisão - Coluna 4
 */
/**
 * @test Validação da Coluna 4
 * @brief Verifica se Coluna 4 realmente funciona e não é falso positivo
 */
TEST_CASE("VALIDAÇÃO: Coluna 4 realmente funciona", "[backup][validacao]")
{
    // Arrange - Cenário OBRIGATÓRIO para Coluna 4
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento.txt");
    system("rm -rf pendrive_teste");

    // Configuração que DEVE ativar Coluna 4:
    // - Arquivo existe no HD ✓
    // - Arquivo existe no pendrive ✓
    // - Datas "iguais" (conteúdo igual) ✓
    // - NÃO deve cair em Coluna 2 ou 3

    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config.close();

    // MESMO conteúdo em ambos = datas "iguais"
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_IDENTICO" << std::endl;
    hdFile.close();

    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_IDENTICO" << std::endl; // ← MESMO!
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
 * - Tem backup.parm: V (SIM) - assumido
 * - Faz backup: V (SIM) - assumido
 * - ArqX ∈ HD: V (SIM) - assumido
 * - ArqX ∈ Pen-drive: V (SIM) - assumido
 * - Data PenD < HD: F (NÃO)
 * - Data PenD == HD: F (NÃO)
 * - Data PenD > HD: V (SIM) - implícito
 *
 * Ação esperada: erro (não fazer backup)
 *
 * @see Tabela de Decisão - Coluna 5
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
    // 1. backup.parm existe
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config.close();

    // 2. Arquivo existe no HD (conteúdo ANTIGO)
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_ANTIGO_HD" << std::endl;
    hdFile.close();

    // 3. Arquivo existe no pendrive com conteúdo MAIS RECENTE
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_NOVO_PENDRIVE" << std::endl; // MAIS RECENTE!
    pendriveFile.close();

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar FALSE (erro - pendrive mais atualizado)
    REQUIRE(resultado == false);
}