/**
 * @file testa_velha.cpp
 */

#include "third_party/catch.hpp"
#include "velha.hpp"

TEST_CASE("X vence por coluna", "[colx]")
{
  int t[3][3] = {
      {2, 0, 1},
      {2, 0, 1},
      {0, 2, 1},
  };
  REQUIRE(VerificaVelha(t) == 1);
}
TEST_CASE("X vence por coluna - caso 2", "[colx2]")
{
  int t[3][3] = {
      {1, 2, 0},
      {1, 0, 2},
      {1, 0, 0},
  };
  REQUIRE(VerificaVelha(t) == 1);
}

TEST_CASE("X vence por coluna - caso 3", "[colx3]")
{
  int t[3][3] = {
      {0, 1, 2},
      {2, 1, 0},
      {0, 1, 2},
  };
  REQUIRE(VerificaVelha(t) == 1);
}

TEST_CASE("X vence por linha", "[linx]")
{
  int t[3][3] = {
      {1, 1, 1},
      {2, 0, 1},
      {0, 2, 2},
  };
  REQUIRE(VerificaVelha(t) == 1);
}
TEST_CASE("X vence por linha - caso 2", "[linx2]")
{
  int t[3][3] = {
      {2, 0, 2},
      {1, 1, 1},
      {0, 2, 0},
  };
  REQUIRE(VerificaVelha(t) == 1);
}

TEST_CASE("X vence por linha - caso 3", "[linx3]")
{
  int t[3][3] = {
      {0, 2, 0},
      {2, 0, 2},
      {1, 1, 1},
  };
  REQUIRE(VerificaVelha(t) == 1);
}

TEST_CASE("X vence por diagonal principal", "[diagx]")
{
  int t[3][3] = {
      {1, 0, 2},
      {2, 1, 0},
      {0, 2, 1},
  };
  REQUIRE(VerificaVelha(t) == 1);
}

TEST_CASE("X vence por diagonal secundária", "[diagx2]")
{
  int t[3][3] = {
      {0, 2, 1},
      {2, 1, 0},
      {1, 0, 2},
  };
  REQUIRE(VerificaVelha(t) == 1);
}

TEST_CASE("0 vence por coluna", "[colo]")
{
  int t[3][3] = {
      {2, 2, 1},
      {2, 1, 0},
      {2, 1, 1},
  };
  REQUIRE(VerificaVelha(t) == 2);
}
TEST_CASE("0 vence por coluna - caso 2", "[colo2]")
{
  int t[3][3] = {
      {1, 2, 0},
      {0, 2, 1},
      {1, 2, 0},
  };
  REQUIRE(VerificaVelha(t) == 2);
}

TEST_CASE("0 vence por coluna - caso 3", "[colo3]")
{
  int t[3][3] = {
      {0, 1, 2},
      {1, 0, 2},
      {2, 0, 2},
  };
  REQUIRE(VerificaVelha(t) == 2);
}

TEST_CASE("0 vence por linha", "[lino]")
{
  int t[3][3] = {
      {2, 2, 2},
      {2, 0, 1},
      {0, 1, 1},
  };
  REQUIRE(VerificaVelha(t) == 2);
}

TEST_CASE("0 vence por diagonal", "[diago]")
{
  int t[3][3] = {
      {1, 2, 2},
      {1, 2, 0},
      {2, 1, 1},
  };
  REQUIRE(VerificaVelha(t) == 2);
}

TEST_CASE("empate", "[empate]")
{
  int t[3][3] = {
      {1, 2, 1},
      {0, 1, 2},
      {2, 1, 2},
  };
  REQUIRE(VerificaVelha(t) == 0);
}
TEST_CASE("Jogo em andamento", "[Indeterminado]")
{
  int t[3][3] = {
      {1, 2, 0},
      {0, 1, 0},
      {2, 0, 0},
  };
  REQUIRE(VerificaVelha(t) == -1);
}
TEST_CASE("Jogo impossível", "[Impossível]")
{
  int t[3][3] = {
      {1, 2, 1},
      {0, 1, 1},
      {2, 0, 1},
  };
  REQUIRE(VerificaVelha(t) == -2);
}