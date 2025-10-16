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
 *
 * @see Tabela de Decisão - Coluna 6
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
    // 1. backup.parm existe MAS indica NÃO fazer backup
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl; // ← INDICA NÃO FAZER BACKUP
    config.close();

    // 2. Arquivo existe no HD
    std::ofstream hdFile("documento.txt");
    hdFile << "conteudo" << std::endl;
    hdFile.close();

    // 3. Arquivo NÃO existe no pendrive (condição que permitiria backup na Coluna 2)
    // Mas como Faz backup: F, deve retornar erro

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
 * - Data PenD < HD: V (SIM) - pendrive desatualizado
 * - Data PenD == HD: F (NÃO)
 * - Data PenD > HD: F (NÃO)
 *
 * Ação esperada: erro
 *
 * @see Tabela de Decisão - Coluna 7
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
    // 1. backup.parm existe MAS indica NÃO fazer backup
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl; // ← NÃO FAZER BACKUP
    config.close();

    // 2. Arquivo existe no HD (conteúdo NOVO)
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_NOVO_HD" << std::endl;
    hdFile.close();

    // 3. Arquivo existe no pendrive (conteúdo ANTIGO - desatualizado)
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_ANTIGO_PENDRIVE" << std::endl; // ← DESATUALIZADO
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
 * - Faz backup: F (NÃO) ← CONDIÇÃO PRINCIPAL
 * - ArqX ∈ HD: V (SIM)
 * - ArqX ∈ Pen-drive: V (SIM)
 * - Data PenD < HD: F (NÃO)
 * - Data PenD == HD: V (SIM)
 * - Data PenD > HD: F (NÃO)
 *
 * Ação esperada: faz nada (não fazer backup)
 *
 * @see Tabela de Decisão - Coluna 8
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
    // 1. backup.parm existe MAS indica NÃO fazer backup
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl; // ← NÃO FAZER BACKUP
    config.close();

    // 2. Arquivo existe no HD
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_IGUAL" << std::endl;
    hdFile.close();

    // 3. Arquivo existe no pendrive com MESMO conteúdo
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_IGUAL" << std::endl; // ← DATAS "IGUAIS"
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
 * - Data PenD < HD: F (NÃO)
 * - Data PenD == HD: F (NÃO)
 * - Data PenD > HD: V (SIM) ← PENDRIVE MAIS ATUALIZADO
 *
 * Ação esperada: pen drive para hd (RESTAURAR)
 *
 * @see Tabela de Decisão - Coluna 9
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
    // 1. backup.parm existe MAS indica NÃO fazer backup
    std::ofstream config("Backup.parm");
    config << "documento.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl; // ← NÃO FAZER BACKUP
    config.close();

    // 2. Arquivo existe no HD (conteúdo ANTIGO)
    std::ofstream hdFile("documento.txt");
    hdFile << "CONTEUDO_ANTIGO_HD" << std::endl;
    hdFile.close();

    // 3. Arquivo existe no pendrive (conteúdo NOVO - mais atualizado)
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento.txt");
    pendriveFile << "CONTEUDO_NOVO_PENDRIVE" << std::endl; // ← MAIS ATUALIZADO
    pendriveFile.close();

    bool resultado = sistema.executarRestauracao(dispositivo);

    // Assert - Deve retornar TRUE (restauração realizada)
    REQUIRE(resultado == true);
}
/**
 * @test Coluna da tabela de decisão: Erro quando arquivo não existe no HD
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: F (NÃO)
 * - ArqX ∈ Pen-drive: F (NÃO)
 *
 * Ação esperada: erro
 *
 * @see Tabela de Decisão - Coluna 10
 */
TEST_CASE("Coluna: Erro quando arquivo não existe no HD", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento_inexistente.txt");
    system("rm -rf pendrive_teste");

    // Configuração ESPECÍFICA:
    // 1. backup.parm existe
    std::ofstream config("Backup.parm");
    config << "documento_inexistente.txt" << std::endl; // Arquivo que NÃO existe no HD
    config.close();

    // 2. Arquivo NÃO existe no HD (condição principal: ArqX ∈ HD: F)
    // Não criamos o arquivo "documento_inexistente.txt" no HD

    // 3. Arquivo NÃO existe no pendrive (ArqX ∈ Pen-drive: F)
    // Não criamos no pendrive também

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar FALSE (erro - arquivo não existe no HD)
    REQUIRE(resultado == false);
}

/**
 * @test Coluna da tabela de decisão: Faz nada quando arquivo não existe no HD mas existe no pendrive
 *
 * Condições:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: V (SIM)
 * - ArqX ∈ HD: F (NÃO)
 * - ArqX ∈ Pen-drive: V (SIM)
 *
 * Ação esperada: faz nada (não faz backup)
 *
 * @see Tabela de Decisão - Coluna 11
 */
TEST_CASE("Coluna: Faz nada quando arquivo não existe no HD mas existe no pendrive", "[backup][decisao]")
{
    // Arrange
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA
    std::remove("Backup.parm");
    std::remove("documento_inexistente_hd.txt"); // Garante que NÃO existe no HD
    system("rm -rf pendrive_teste");

    // Configuração ESPECÍFICA:
    // 1. backup.parm existe
    std::ofstream config("Backup.parm");
    config << "documento_inexistente_hd.txt" << std::endl; // Arquivo que NÃO existe no HD
    config.close();

    // 2. Arquivo NÃO existe no HD (condição principal: ArqX ∈ HD: F)
    // Não criamos o arquivo "documento_inexistente_hd.txt" no HD

    // 3. Arquivo EXISTE no pendrive (ArqX ∈ Pen-drive: V)
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/documento_inexistente_hd.txt");
    pendriveFile << "CONTEUDO_NO_PENDRIVE" << std::endl; // Existe apenas no pendrive
    pendriveFile.close();

    // Act
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Deve retornar FALSE (faz nada - não faz backup)
    REQUIRE(resultado == false);
}

/**
 * @test Coluna da tabela de decisão: Erro quando não deve fazer backup e arquivo não existe em nenhum lugar
 *
 * Condições EXATAS da coluna:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: F (NÃO)
 * - ArqX ∈ HD: F (NÃO)
 * - ArqX ∈ Pen-drive: F (NÃO)
 *
 * Ação esperada: erro
 *
 * @see Tabela de Decisão - 12
 */
TEST_CASE("Coluna: Tem Backup.parm:V, Faz backup:F, ArqX∈HD:F, ArqX∈Pen-drive:F → Erro", "[backup][decisao]")
{
    // Arrange - Configurar EXATAMENTE as condições da coluna
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA COMPLETA
    std::remove("Backup.parm");
    std::remove("arquivo_inexistente.txt"); // Garantir que não existe no HD
    system("rm -rf pendrive_teste");

    // CONDIÇÃO 1: Tem Backup.parm: V (SIM)
    std::ofstream config("Backup.parm");
    config << "arquivo_inexistente.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl; // CONDIÇÃO 2: Faz backup: F (NÃO)
    config.close();

    // CONDIÇÃO 3: ArqX ∈ HD: F (NÃO) - NÃO criar arquivo no HD

    // CONDIÇÃO 4: ArqX ∈ Pen-drive: F (NÃO) - NÃO criar arquivo no pendrive
    // (apenas criar o diretório vazio)
    system("mkdir -p pendrive_teste");

    // Act - Executar backup
    bool resultado = sistema.executarBackup(dispositivo);

    // Assert - Ação: erro (retorna false)
    REQUIRE(resultado == false);
}
/**
 * @test Coluna da tabela de decisão: Restaurar quando arquivo só existe no pendrive
 *
 * Condições EXATAS da coluna:
 * - Tem backup.parm: V (SIM)
 * - Faz backup: F (NÃO)
 * - ArqX ∈ HD: F (NÃO)
 * - ArqX ∈ Pen-drive: V (SIM)
 *
 * Ação esperada: pen-drive para hd (RESTAURAR)
 *
 * @see Tabela de Decisão - 13
 */
TEST_CASE("Coluna: Tem Backup.parm:V, Faz backup:F, ArqX∈HD:F, ArqX∈Pen-drive:V → Pen-drive para HD", "[backup][decisao]")
{
    // Arrange - Configurar EXATAMENTE as condições da coluna
    SistemaBackup sistema;
    std::string dispositivo = "pendrive_teste";

    // LIMPEZA COMPLETA
    std::remove("Backup.parm");
    std::remove("arquivo_restaurar.txt"); // Garantir que não existe no HD
    system("rm -rf pendrive_teste");

    // CONDIÇÃO 1: Tem Backup.parm: V (SIM)
    std::ofstream config("Backup.parm");
    config << "arquivo_restaurar.txt" << std::endl;
    config << "# NO_BACKUP" << std::endl; // CONDIÇÃO 2: Faz backup: F (NÃO)
    config.close();

    // CONDIÇÃO 3: ArqX ∈ HD: F (NÃO) - NÃO criar arquivo no HD

    // CONDIÇÃO 4: ArqX ∈ Pen-drive: V (SIM) - Criar arquivo APENAS no pendrive
    system("mkdir -p pendrive_teste");
    std::ofstream pendriveFile("pendrive_teste/arquivo_restaurar.txt");
    pendriveFile << "conteudo_para_restaurar" << std::endl;
    pendriveFile.close();

    // Act - Executar RESTAURAÇÃO (não backup!)
    bool resultado = sistema.executarRestauracao(dispositivo);

    // Assert - Ação: pen-drive para hd (RESTAURAR) - deve retornar true
    REQUIRE(resultado == true);
}