/**
 * @file velha.cpp
 * @brief Implementação inicial (mínima) para TDD.
 */

#include "velha.hpp"

int VerificaVelha(int tab[3][3])
{
	// Primeiro: verificar se há vencedor

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

	// Diagonal principal
	if (tab[0][0] != 0 && tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2])
	{
		return tab[0][0];
	}

	// Diagonal secundária
	if (tab[0][2] != 0 && tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0])
	{
		return tab[0][2];
	}

	// Verificar se o jogo é impossível (contagem de X e O)
	int count_x = 0, count_o = 0;
	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			if (tab[r][c] == 1)
				count_x++;
			else if (tab[r][c] == 2)
				count_o++;
		}
	}

	// Verificar se ainda é possível alguém vencer
	bool pode_vencer = false;

	// Verificar linhas que ainda podem ser completadas
	for (int r = 0; r < 3; ++r)
	{
		int x_count = 0, o_count = 0, empty_count = 0;
		for (int c = 0; c < 3; ++c)
		{
			if (tab[r][c] == 1)
				x_count++;
			else if (tab[r][c] == 2)
				o_count++;
			else
				empty_count++;
		}
		// Se uma linha tem apenas X's ou O's e espaços vazios, ainda pode vencer
		if ((x_count > 0 && o_count == 0) || (o_count > 0 && x_count == 0))
		{
			pode_vencer = true;
		}
	}

	// Verificar colunas que ainda podem ser completadas
	for (int c = 0; c < 3; ++c)
	{
		int x_count = 0, o_count = 0, empty_count = 0;
		for (int r = 0; r < 3; ++r)
		{
			if (tab[r][c] == 1)
				x_count++;
			else if (tab[r][c] == 2)
				o_count++;
			else
				empty_count++;
		}
		if ((x_count > 0 && o_count == 0) || (o_count > 0 && x_count == 0))
		{
			pode_vencer = true;
		}
	}

	// Verificar diagonais
	// Diagonal principal
	int x_count = 0, o_count = 0, empty_count = 0;
	for (int i = 0; i < 3; ++i)
	{
		if (tab[i][i] == 1)
			x_count++;
		else if (tab[i][i] == 2)
			o_count++;
		else
			empty_count++;
	}
	if ((x_count > 0 && o_count == 0) || (o_count > 0 && x_count == 0))
	{
		pode_vencer = true;
	}

	// Diagonal secundária
	x_count = 0;
	o_count = 0;
	empty_count = 0;
	for (int i = 0; i < 3; ++i)
	{
		if (tab[i][2 - i] == 1)
			x_count++;
		else if (tab[i][2 - i] == 2)
			o_count++;
		else
			empty_count++;
	}
	if ((x_count > 0 && o_count == 0) || (o_count > 0 && x_count == 0))
	{
		pode_vencer = true;
	}

	// Se ainda é possível vencer => jogo indefinido
	if (pode_vencer)
	{
		return -1;
	}

	// Se não é possível vencer => empate
	return 0;
}