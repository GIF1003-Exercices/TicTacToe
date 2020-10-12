/*
 * \file TicTacToe.h
 *
 *  Created on: 2020-10-10
 * \author: Pascal Charpentier
 */

#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include <string>

namespace lab7 {

/**
 * \class TicTacToe
 * Représentation d'un jeu de tic-tac-toe.
 * Contient une grille de 3 x 3 contenant des entiers.  Chaque entier peut prendre les valeurs suivantes: \n
 * 0: case vide\n
 * 1: coup du joueur 1\n
 * 2: coup du joeur 2\n
 *
 * La classe contient aussi les méthodes permettant de garantir la validité de la grille.  Le joueur 1 joue toujours
 * en premier et les deux joueurs jouent à tour de rôle de sorte que le nombre de 1 et de 2 doit être égale ou différer
 * de un.
 *
 * Il y a aussi les méthodes nécessaires pour assurer la bonne marche du jeu: vérifier si la partie est gagnée, si la partie est terminée
 * et si la partie est nulle, ainsi qu'identifier le joueur gagnant.
 *
 * Il y a aussi une méthode d'IO à la console, permettant une mise en oeuvre rapide.
 */
class TicTacToe {

private:
	int m_grille[3][3];

	bool valide() const ;
	bool carresSontValides() const ;
	static bool indicesSontValides(const int, const int);

public:
	TicTacToe();
	TicTacToe(const int p_enCours[3][3]);

	int auTourDe() const ;
	bool joue(int, int);

	bool carreEstLibre(const int p_rangee, const int p_colonne) const;
	bool grilleEstRemplie() const ;
	bool rangeeEstGagnante(const int p_rangee) const ;
	bool colonneEstGagnante(const int p_colonne) const ;
	bool diagonaleEstGagnante(const bool p_diagonaleDuCoinSupGauche) const;

	bool partieEstGagnee() const ;
	bool partieEstNulle() const ;
	bool partieEstTerminee() const;
	int reqGagnant() const ;

	void affiche() const ;
	std::string reqGrilleFormattee(const char symboles[3]) const ;

	virtual ~TicTacToe();
};

} /* namespace lab7 */

#endif /* TICTACTOE_H_ */
