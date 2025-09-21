/**
 * @file testa_velha.cpp
 */

#include "third_party/catch.hpp"
#include "velha.hpp"

TEST_CASE("X vence por coluna", "[coluna]")
{
  int t[3][3] = {
      {2, 0, 1},
      {2, 0, 1},
      {0, 2, 1},
  };
  REQUIRE(VerificaVelha(t) == 1);
}

TEST_CASE("X vence por linha", "[linha]")
{
  int t[3][3] = {
      {1, 1, 1},
      {2, 0, 1},
      {0, 2, 2},
  };
  REQUIRE(VerificaVelha(t) == 1);
}

TEST_CASE("X vence por diagonal", "[diagonal]")
{
  int t[3][3] = {
      {1, 2, 1},
      {2, 1, 0},
      {0, 2, 1},
  };
  REQUIRE(VerificaVelha(t) == 1);
}