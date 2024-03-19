#pragma once

#ifndef _BOGGLE_H_
#define _BOGGLE_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <chrono>
#include "dico.h"

using namespace std;

class boggle {

	unsigned short b_taille;  // taille d'un coté 4 si boggle(4) ou default

	char* grille;  //grille de jeu  : tableau à une dimension taille_grille * taille_grille 
	
	vector< string*> allWords; // touts les mots 
	

	public:

		boggle(const unsigned short& taille = 4);
		boggle(const boggle&);
		boggle(const string&);
		~boggle();

		void afficheGrille();  
		void allwords(dico& );
		void allwords();

		vector< string*> getAllwords();

	private:
		
		vector<unsigned short*> getAdjacent(unsigned short, bool&);
		
		boggle& operator=(const boggle&);
		
		char& generationLettre(const short&);
		
		void generationGrille();
		void allwords_aux(const unsigned short&, bool&, const string& , dico& );
		void allwords_aux(const unsigned short&, bool&, const string& );
		
		bool& copyBool(bool &tab);
		
};

#endif

