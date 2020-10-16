/**
 * \file TicTacToe.cpp
 *
 *  Created on: 2020-10-10
 * \author: Pascal Charpentier
 */

#include "TicTacToe.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <sstream>

namespace lab7 {

/**
 * Constructeur par défaut:  construit une grille vide.
 * Provoque un échec d'assertion si la grille est non-valide
 */

TicTacToe::TicTacToe() {

	for (auto& rangee: m_grille)
	{
		for (auto& carre: rangee)
		{
			carre = 0;
		}
	}
	assert(valide());
}

/**
 * Constructeur de débogage: créé une grille à partir d'un tableau 3x3 d'int
 * Pourrait servir à reprendre une partie en cours...
 */

TicTacToe::TicTacToe(const int p_enCours[3][3])
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_grille[i][j] = p_enCours[i][j];
		}
	}
	assert(valide());
}

/**
 * Vérifie si les rangée et colonnes en paramètres sont dans les limites
 * \param[in] p_rangee le numéro de rangée
 * \param[in] p_colonne le numéro de colonne
 * \return false si les indices sont hors-limite
 */
bool TicTacToe::indicesSontValides(const int p_rangee, const int p_colonne)
{
	return (p_rangee >= 0) and (p_rangee < 3) and (p_colonne >= 0) and (p_colonne < 3);
}

/**
 * Vérifie si une case a déjà été jouée.
 *
 * \param[in] p_rangee le numéro de rangée
 * \param[in] p_colonne le numéro de colonne
 * \return false si la case est occupée
 */
bool TicTacToe::carreEstLibre(const int p_rangee, const int p_colonne) const
{
	return m_grille[p_rangee][p_colonne] == 0;
}

/**
 * Vérifie si toutes les cases ont été jouées
 *
 * \return true si toutes les cases sont occupées
 */
bool TicTacToe::grilleEstRemplie() const
{
	bool remplie = true;

	for (int i = 0; remplie and (i < 3); ++i)
	{
		for (int j = 0; remplie and (j < 3); ++j)
		{
			if (carreEstLibre(i, j)) remplie = false;
		}
	}
	return remplie;
}

/**
 * Vérifie que toutes les cases sont soit vides, soient occupées par un coup valide.
 *
 * \return true si toutes les cases sont soit vides, soient occupées par un coup valide.
 */
bool TicTacToe::carresSontValides() const
{
	bool valide = true;

	for (auto& rangee: m_grille)
	{
		for (auto carre: rangee)
		{
			if ((carre < 0) or (carre > 2))
			{
				valide = false;
			}
		}
	}
	return valide;
}

/**
 * Indique le joueur actif
 *
 * \return le numéro du prochain joueur à jouer.
 */
int TicTacToe::auTourDe() const
{
	int coupsDuJoueur1 = 0;
	int coupsDuJoueur2 = 0;

	for (auto& rangee: m_grille)
	{
		for (auto carre: rangee)
		{
			if (carre == 1)
			{
				++coupsDuJoueur1;
			}
			else if (carre == 2)
			{
				++coupsDuJoueur2;
			}
		}
	}

	int difference = coupsDuJoueur1 - coupsDuJoueur2;
	return 1 + difference;
}

/**
 * Vérifie que l'objet TicTacToe est valide:
 * Chacune des cases doit être soit vide, soit occupée par un 1 ou un 2.
 * Il doit y avoir un nombre égal de 1 et de 2, ou alors un 1 de plus que les 2.
 *
 * \return true si la grille est valide.
 */
bool TicTacToe::valide() const
{
    return carresSontValides() and ((auTourDe() == 1) or (auTourDe() == 2));
}

/**
 * Joue un coup pour le joueur actif.
 *
 * \param[in] p_rangee le numéro de rangée
 * \param[in] p_colonne le numéro de colonne
 * \return true si la case était vide et que le coup a été joué. Sinon false.
 * \pre Les indices doivent être valides (in bound)
 * \post La grille doit demeurer valide.
 */
bool TicTacToe::joue(int p_rangee, int p_colonne)
{
	assert(indicesSontValides(p_rangee, p_colonne));

	bool coupEstValide = false;

	if (carreEstLibre(p_rangee, p_colonne))
	{
	    m_grille[p_rangee][p_colonne] = auTourDe();
	    coupEstValide = true;
	}
	assert(valide());
	return coupEstValide;
}

/**
 * Vérifie s'il y a un tictactoe dans la colonne spécifiée.
 * \param[in] p_colonne le numéro de colonne
 * \return true si les trois éléments de la colonne sont identiques
 */
bool TicTacToe::colonneEstGagnante(const int p_colonne) const
{
	bool gagnant = true;

	assert(indicesSontValides(0, p_colonne));

	for (int i = 0; gagnant and (i < 3); ++i)
	{

        gagnant = m_grille[i][p_colonne] ? (m_grille[i][p_colonne] == m_grille[0][p_colonne]) : false;
	}
	return gagnant;
}

/**
 * Vérifie s'il y a un tictactoe dans la rangée spécifiée
 * \param[in] p_rangee le numéro de rangée
 * \return true si les trois éléments de la rangée sont identiques
 */
bool TicTacToe::rangeeEstGagnante(const int p_rangee) const
{
	bool gagnant = true;

	assert(indicesSontValides(p_rangee, 0));
	for (int j = 0; gagnant and (j < 3); ++j)
	{
        gagnant = m_grille[p_rangee][j] ? (m_grille[p_rangee][j] == m_grille[p_rangee][0]) : false;
	}
	return gagnant;
}

/**
 * Vérifie s'il y a un tictactoe dans une des diagonales
 * \param[in] p_diagonaleDuCoinSupGauche si true on vérifie la diagonale partant de 0,0 Si false
 * on vérifie la diagonale partant de 0, 2 soit le coin supérieur droit
 * \return true si la diagonale contient trois éléments identiques
 */
bool TicTacToe::diagonaleEstGagnante(const bool p_diagonaleDuCoinSupGauche) const
{
	int colonneDepart = p_diagonaleDuCoinSupGauche ? 0 : 2;
	int pas = p_diagonaleDuCoinSupGauche ? 1 : -1;
	bool gagnant = true;

	for(int i = 0, j = colonneDepart; gagnant and (i < 3); ++i, j += pas)
	{
		gagnant = m_grille[i][j] ? (m_grille[i][j] == m_grille[1][1]) : false;
	}
	return gagnant;
}

/**
 * Vérifie qu'il y a un tictactoe et donc un joueur a gagné.
 * \return true si une rangée une colonne ou une diagonale a un tictactoe.
 */
bool TicTacToe::partieEstGagnee() const
{
	bool gagnee = false;

	for (int i = 0; !gagnee and (i < 3); ++i)
	{
		gagnee = rangeeEstGagnante(i) or colonneEstGagnante(i);
	}
	return gagnee or diagonaleEstGagnante(0) or diagonaleEstGagnante(1);
}

/**
 * Vérifie que la partie est nulle
 * \return true si la grille est pleine et qu'il n'y a pas de tictactoe
 */
bool TicTacToe::partieEstNulle() const
{
	return grilleEstRemplie() and !partieEstGagnee();
}

/**
 * Vérifie que la partie est terminée
 * \return true si il y a un tictactoe ou si la grille est pleine
 */
bool TicTacToe::partieEstTerminee() const
{
	return partieEstGagnee() or partieEstNulle();
}

/**
 * Retourne le numéro du gagnant
 * \return le numéro du gagnant
 */
int TicTacToe::reqGagnant() const
{
	int gagnant = 0;

	if (partieEstGagnee())
	{
		gagnant = (auTourDe() == 1) ? 2 : 1;
	}
	return gagnant;
}

/**
 * Permet l'affichage d'une grille de jeu.
 * \param[in] symboles un tableau contenant le symbole d'une case vide, le symbole du joueur 1 et
 * le symbole du joueur 2.
 * \return un objet string représentant l'état du jeu
 */
std::string TicTacToe::reqGrilleFormattee(const char symboles[3]) const
{
	static const std::string formattage[] = {
			"\033[65;1m", "\033[1;31m", "\033[1;34m"
	};

	static const std::string reset = "\033[0m";

	std::ostringstream os;

	for (auto& rangee: m_grille)
	{
		for (auto carre: rangee)
		{
			os <<  formattage[carre] << std::setw(15) <<symboles[carre] << reset;
		}
		os << std::endl;
	}
	return os.str();
}

/**
 * Fonction de débogage pour l'affichage du jeu
 */
void TicTacToe::affiche() const
{
	for (auto& rangee: m_grille)
	{
		for (auto carre: rangee)
		{
			std::cout << std::setw(5) << carre;
		}
		std::cout << std::endl;
	}
}



} /* namespace lab7 */
