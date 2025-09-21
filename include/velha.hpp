#ifndef VELHA_HPP_
#define VELHA_HPP_

/**
 * @file velha.hpp
 * @brief Declara a função de verificação do jogo da velha.
 *
 * Matriz 3x3:
 * 0 = vazio, 1 = X, 2 = O
 *
 * Retornos:
 *  1 = X vence
 *  2 = O vence
 *  0 = empate
 * -1 = indefinido
 * -2 = impossível
 */
int VerificaVelha(int velha[3][3]);

#endif // VELHA_HPP_
