/**
 * @file velha.cpp
 * @brief Implementação inicial (mínima) para TDD.
 */

#include "velha.hpp"

int VerificaVelha(int tab[3][3])
{
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

	// Jogo impossível se a diferença de X e 0 for maior que 2
	bool jogo_impossivel = ((count_o - count_x) > 2 || (count_x - count_o) > 2);

	// Verificar se há vencedor
	int vencedor = 0;

	// Colunas
	for (int c = 0; c < 3; ++c)
	{
		if (tab[0][c] != 0 && tab[0][c] == tab[1][c] && tab[1][c] == tab[2][c])
		{
			vencedor = tab[0][c];
			break;
		}
	}

	// Linhas
	if (vencedor == 0)
	{
		for (int r = 0; r < 3; ++r)
		{
			if (tab[r][0] != 0 && tab[r][0] == tab[r][1] && tab[r][1] == tab[r][2])
			{
				vencedor = tab[r][0];
				break;
			}
		}
	}

	// Diagonal principal
	if (vencedor == 0 && tab[0][0] != 0 && tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2])
	{
		vencedor = tab[0][0];
	}

	// Diagonal secundária
	if (vencedor == 0 && tab[0][2] != 0 && tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0])
	{
		vencedor = tab[0][2];
	}

	// Se há vencedor mas o jogo é impossível, verificar consistência
	if (vencedor != 0 && jogo_impossivel)
	{
		// Se X venceu, deve ter uma jogada a mais que O
		if (vencedor == 1 && count_x != count_o + 1)
		{
			return -2; // Impossível
		}
		// Se O venceu, deve ter o mesmo número de jogadas que X
		if (vencedor == 2 && count_x != count_o)
		{
			return -2; // Impossível
		}
		// Se for consistente, retorna o vencedor
		return vencedor;
	}

	// Se é impossível e não há vencedor (ou vencedor inconsistente)
	if (jogo_impossivel)
	{
		return -2;
	}

	// Se há vencedor consistente
	if (vencedor != 0)
	{
		return vencedor;
	}

	// Verificar se ainda é possível alguém vencer
	bool pode_vencer = false;

	// Verificar linhas que ainda podem ser completadas
	for (int r = 0; r < 3; ++r)
	{
		int x_count = 0, o_count = 0;
		for (int c = 0; c < 3; ++c)
		{
			if (tab[r][c] == 1)
				x_count++;
			else if (tab[r][c] == 2)
				o_count++;
		}
		if ((x_count > 0 && o_count == 0) || (o_count > 0 && x_count == 0))
		{
			pode_vencer = true;
			break;
		}
	}

	if (!pode_vencer)
	{
		// Verificar colunas
		for (int c = 0; c < 3; ++c)
		{
			int x_count = 0, o_count = 0;
			for (int r = 0; r < 3; ++r)
			{
				if (tab[r][c] == 1)
					x_count++;
				else if (tab[r][c] == 2)
					o_count++;
			}
			if ((x_count > 0 && o_count == 0) || (o_count > 0 && x_count == 0))
			{
				pode_vencer = true;
				break;
			}
		}
	}

	if (!pode_vencer)
	{
		// Diagonal principal
		int x_count = 0, o_count = 0;
		for (int i = 0; i < 3; ++i)
		{
			if (tab[i][i] == 1)
				x_count++;
			else if (tab[i][i] == 2)
				o_count++;
		}
		if ((x_count > 0 && o_count == 0) || (o_count > 0 && x_count == 0))
		{
			pode_vencer = true;
		}

		if (!pode_vencer)
		{
			// Diagonal secundária
			x_count = 0;
			o_count = 0;
			for (int i = 0; i < 3; ++i)
			{
				if (tab[i][2 - i] == 1)
					x_count++;
				else if (tab[i][2 - i] == 2)
					o_count++;
			}
			if ((x_count > 0 && o_count == 0) || (o_count > 0 && x_count == 0))
			{
				pode_vencer = true;
			}
		}
	}

	if (pode_vencer)
	{
		return -1;
	}

	return 0;
}