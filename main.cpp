#include <iostream>
#include "boggle.h"
#include "dico.h"
using namespace std;


int main(int argc , char*argv[])
{
	//recuperation ligne commande
	if (sqrt(argc - 1) - (int)sqrt(argc - 1) > 0) {
		cout << sqrt(argc - 1) - (int)sqrt(argc - 1) << endl;
		return -1;
	}
	string* chaine = new string("");
	for (int i = 1; i < argc; i++)
		chaine->append(argv[i]);


	// initialisation boggle et dico

	
	boggle *jeu = new boggle(*chaine);
	delete chaine;
	jeu->afficheGrille();

	dico* monDico = new dico('!');
	

	// chargement des mots possibles 
	jeu->allwords();
	vector<string*> tab = jeu->getAllwords();


	// ecriture des solutions possible ( dico ) dans un fichier solution
	
	ofstream outfile("possiblewords.txt");
	vector<string*> final ;
	
	auto start = chrono::high_resolution_clock::now();
	
	for (vector<string*>::iterator it = tab.begin(); it != tab.end(); ++it) {
		
		if (monDico->label_in_arbre(**it, *monDico)) {
			final.push_back(*it);
			outfile << **it << endl;
		}
	}
	
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> float_ms = end - start;
	
	cout << "taille mot possible " << final.size() ;
	cout << " temp : " << float_ms.count() << "  milliseconds" << endl;
	
	delete jeu;
	delete monDico;
	return 0;
}
