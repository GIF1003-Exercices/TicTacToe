/*
 * \file main.cpp
 *
 * \brief Permet de tester rapidement la classe TicTacToe.
 * ATTENTION: Les inputs ne sont pas validés.
 *
 * Le joueur 1 joue en premier. Les coups sont entrés suivant le format suivant: "r c" où r est la rangée
 * et c est la colonne.  Des entrées non-valides font planter le programme.  Le jeu s'arrête lorsque la
 * partie est gagnée ou alors nulle.  Une tentative de jouer dans une case déjà jouée sera simplement ignorée.
 *
 * TODO Valider les entrées
 * TODO Message d'erreur lorsque joue une case déjà occupée
 * TODO Système d'entrées plus intuitif.
 *
 *  Created on: 2020-10-10
 *  \author: etudiant
 */

#include "TicTacToe.h"
#include <iostream>

using namespace std;

int main()
{
	const char symboles[3] = {'.', 'X', 'O'};
	lab7::TicTacToe partie;
	int rangee;
	int colonne;

	do
	{
		cout << partie.reqGrilleFormattee(symboles);
		cout << "C'est au tour des " << symboles[partie.auTourDe()] << endl;
		cout << "Saisir le prochain coup: ";
		cin >> rangee >> colonne;
		partie.joue(rangee, colonne);
	}
	while (!partie.partieEstTerminee());

	cout << partie.reqGrilleFormattee(symboles);
	if (partie.partieEstGagnee())
	{
		cout << "Partie remportée par les " << symboles[partie.reqGagnant()] << endl;
	}
	else if (partie.partieEstNulle())
	{
		cout << "Partie nulle!" << endl;
	}
	else
	{
		cout << "Partie terminée anormalement!" << endl;
	}

	return 0;
}



