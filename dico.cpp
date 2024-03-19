#include "dico.h"
//arbre vide
dico::dico() {
	
	label = nullptr;
	fils = nullptr;
	fin = false;
	
}

//initialisation du premier noeud
dico::dico(const char& letter) {

	label = new char;
	*label = letter;

	fils = new dico[26];
	loaddico("dico.txt");
	fin = false;
}

dico::~dico()
{
	delete []fils;
	delete label;
}

//ajout un noeud 
void dico::add_arbre( char letter,  dico* tree) {

	//recupere le numero de la lettre ASCII et trouve sa postion dans l'alphabet 0 a 25
	
	if (   isEmpty(    tree->getFils( letter -97)   )        ) { // si pas noeud on le creer
		tree->getFils(letter - 97).label = new char(letter);
		tree->getFils(letter - 97).fils = new dico[26];
	}
	
}

//ajoute un mot du dictionnaire dans l arbre 
void dico::add_mot(const string& mot ,  dico & tree )
{
	
	const unsigned short& taille_mot = ( unsigned short ) mot.size();
	
	if (taille_mot <= 0){
		tree.fin = true;  // fin du mot 
		return;
	}
		
	else if (mot[0] == '-') // si tiret on passe au caractere suivant
		return add_mot(mot.substr(1, taille_mot - 1), tree );
	
	else {
		
		const char& letter_miniscule = mot[0] < 123 && mot[0] > 96 ?  mot[0] :  mot[0]  + 32 ; // exclusion des majuscules
		const int& letter_pos = letter_miniscule - 97   ; // conversion en chiffre de 0 a 25
		
		if (isEmpty(tree.fils[letter_pos]))  // si vide on creer un noeud 
			add_arbre(letter_miniscule, &tree);

		add_mot(mot.substr(1, taille_mot - 1), tree.fils[letter_pos ]); //prochaine lettre , changement de noeud 
	}
}



bool dico::label_in_arbre(const string& mot,  dico& tree) {
	
	if (mot.empty() )
		return tree.fin; // verifie qu on se trouve sur la fin d un mot 

	if (isEmpty(tree))
		return false;
	
	if( mot[0] == '-' )
		return label_in_arbre(mot.substr(1, mot.size() - 1), tree);
	
	else{
		const char& letter_miniscule = mot[0] < 123 && mot[0] > 96 ? mot[0] : mot[0] + 32; // transformation des majuscules en minuscule
		const int& letter_pos = letter_miniscule - 97;
			
		return label_in_arbre(mot.substr(1, mot.size() - 1), tree.getFils(letter_pos));
	}

}

bool dico::isEmpty( dico& tree)
{
	return tree.label == nullptr;
}

// retourne le fils 
dico& dico::getFils(unsigned short pos)
{
	if (pos >= 0 && pos < 26)
		return fils[pos];
	else {
		cout << "error fils inexistants " << endl;
		return fils[-1]; 
	}
	
}

// charge le dictionnaire dans un arbre
void dico::loaddico(const string& name)
{
	auto start = chrono::high_resolution_clock::now();
	ifstream monDico(name);
	int nb = 0;
	if (monDico) {

		string ligne;
		while (!monDico.eof()) {
			
			monDico >> ligne;
			this->add_mot(ligne, *this);
			nb++;
		}
	}
	else
		cout << "error chargement dico" << endl;

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> float_ms = end - start;

	cout << " fin chargement du dico avec : " << nb << " mots " ;
	cout << " temp : " << float_ms.count() << "  milliseconds" << endl;
}
