/**
 * @file velha.cpp
 * @brief Implementação inicial (mínima) para TDD.
 */

#include "velha.hpp"

int VerificaVelha(int tab[3][3])
{
	// Colunas
	for (int c = 0; c < 3; ++c)
	{
		if (tab[0][c] != 0 && tab[0][c] == tab[1][c] && tab[1][c] == tab[2][c])
		{
			return tab[0][c];
		}
	}
	// Linhas
	for (int r = 0; r < 3; ++r)
	{
		if (tab[r][0] != 0 && tab[r][0] == tab[r][1] && tab[r][1] == tab[r][2])
		{
			return tab[r][0];
		}
	}
	// Diagonais
	if (tab[0][0] != 0 && tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2])
	{
		return tab[0][0];
	}
	if (tab[0][2] != 0 && tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0])
	{
		return tab[0][2];
	}
	return 0; // ninguém venceu
}
