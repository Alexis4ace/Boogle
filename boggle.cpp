#include "boggle.h"

//           CONSTRUCTEUR OPERATEUR DESCTRUCTEUR

boggle::boggle(const unsigned short & taille)
{	
	b_taille = taille;

	grille = new  char[taille*taille];
	generationGrille();
	
}

boggle::boggle(const boggle& obj)
{
	
	b_taille = obj.b_taille;

	grille = new char[obj.b_taille * obj.b_taille];

	for (int i = 0; i < obj.b_taille*obj.b_taille; i++)
		grille[i] = obj.grille[i];
	
}

boggle::boggle(const string & chaine)
{
	b_taille = sqrt(chaine.size() ) ;

	grille = new  char[b_taille * b_taille];
	for (int i = 0; i < b_taille * b_taille; i++)
		grille[i] = chaine[i];
}

//suppression du tableau de char ( grille )
boggle::~boggle()
{
	delete []grille;
	 // touts les mots possibles
}

// constructeur recopie prive
boggle& boggle::operator=(const boggle& b)
{
	if (this != &b) {
		
		b_taille = b.b_taille;
		
		delete []grille;
		grille = new char[b.b_taille * b.b_taille];

		for (int i = 0; i < b.b_taille * b.b_taille; i++)
			grille[i] = b.grille[i];
	}

	return *this;
}



//              FONCTION UTILE


//affiche la grille
void boggle::afficheGrille() {
	for (int i = 0; i < b_taille * b_taille; i++) {

		cout << grille[i];
		if ((i + 1) % b_taille == 0)
			cout << endl;
	}
}


//renvoi une lettre au hasard
 char& boggle::generationLettre(const short& hasard) {

	char& letter = *new char( hasard + 97 );
	return  letter;
	
}

 //genere la grille de lettre au hasard
void boggle::generationGrille() {
	
	//srand(time(NULL));
	
	for (int i = 0; i < b_taille*b_taille; i++) {

		char& letter_rand = generationLettre( rand() % 26 );
		grille[i] = letter_rand;

	}
}

// fournis un tableau de 8 case des adjacent d'une position ( position centrale exclus )
vector<unsigned short*> boggle::getAdjacent( unsigned short position, bool &lettre_dispo)
{
	 vector<unsigned short*> list_adjacent ;
	 
	 unsigned short x_pos = position % b_taille;   // position actuelle
	 unsigned short y_pos = position / b_taille;

	 unsigned short x_temp;  // position des adjacents
	 unsigned short y_temp;
		
	

	for (int i = 0; i < b_taille * b_taille; i++) {
		 
		 x_temp = i % b_taille;
		 y_temp = i / b_taille;
		
		 if (position != i && (&lettre_dispo)[i]
			 && x_temp - x_pos <= 1 && x_temp - x_pos >= -1 
			 && y_pos - y_temp >= -1 && y_pos - y_temp <= 1 ) 
			 
			 list_adjacent.push_back( new unsigned short(i) ); // si c est adjacent

	 }
	 return list_adjacent;
	
}

vector<string*> boggle::getAllwords()
{
	return allWords;
}

 bool& boggle::copyBool(bool &tab)
 {
	 bool* tab_new = new bool[b_taille*b_taille];
	 for (int i = 0; i < b_taille * b_taille; i++)
		 tab_new[i] = (& tab)[i];
	
	 return *tab_new;
 }




 // FONCTION PRINCIPAL

 //                  SANS DICTIONNAIRE
 void boggle::allwords()
 {
	 auto start = chrono::high_resolution_clock::now();
	 bool* const lettre_disponible = new bool[b_taille * b_taille];

	 for (int i = 0; i < b_taille * b_taille; i++)
		 lettre_disponible[i] = true;



	 string* futur_mot;
	 char* lettre_grille;
	 for (int i = 0; i < b_taille * b_taille; i++) { // pour chaque case

		 lettre_grille = new char[2];
		 lettre_grille[0] = grille[i];
		 lettre_grille[1] = '\0';
		 futur_mot = new string(lettre_grille);

		 allwords_aux(i, *lettre_disponible, *futur_mot);
		 delete futur_mot;
		 delete []lettre_grille;
	 }
	 delete []lettre_disponible;
	
	 auto end = chrono::high_resolution_clock::now();
	 chrono::duration<double, std::milli> float_ms = end - start;

	 cout << " fin chargement allwords avec : " << allWords.size() << " mots ";
	 cout << " temp : " << float_ms.count() << "  milliseconds" << endl;

 }


 void boggle::allwords_aux(const unsigned short& position, bool& lettre_dispo, const  string& mot)
 {

	 if (mot.size() >= 3)                             // ajoute les mots superieure ou egal a 3
		 allWords.push_back(new string(mot));


	 (&lettre_dispo)[position] = false;                   // j utilise cette lettre donc false
	 bool& tab_copy = copyBool(lettre_dispo);                 // je fais une copy 
	 vector<unsigned short*> list_adjacent = getAdjacent(position, lettre_dispo);   // je trouve ces adjacents ( position  )

	 //pour chaque adjacent j'appele cette fonction avec la position voisine , le tableau de lettre possible et j ajoute la lettre au mot 
	 
	 for (vector<unsigned short*>::iterator it = list_adjacent.begin(); it != list_adjacent.end(); ++it)
		 allwords_aux(**it, tab_copy, mot + grille[**it]);

	 (&lettre_dispo)[position] = true;         //sorti de tous les ajdacents 

	 delete& tab_copy;
	
 }


 // AVEC DICTIONNAIRE


 void boggle::allwords(dico& dictionnaire)
 {
	 auto start = chrono::high_resolution_clock::now();
	 bool* const lettre_disponible = new bool[b_taille * b_taille]; // booleen des lettre utilise

	 for (int i = 0; i < b_taille * b_taille; i++)
		 lettre_disponible[i] = true;



	 string* futur_mot;
	 char* lettre_grille;
	 for (int i = 0; i < b_taille * b_taille; i++) { // pour chaque case

		 lettre_grille = new char[2];
		 lettre_grille[0] = grille[i];
		 lettre_grille[1] = '\0';
		 futur_mot = new string(lettre_grille);

		 allwords_aux(i, *lettre_disponible, *futur_mot, dictionnaire);
		 delete futur_mot;
		 delete[]lettre_grille;
	 }
	 delete[]lettre_disponible;

	 auto end = chrono::high_resolution_clock::now();
	 chrono::duration<double, std::milli> float_ms = end - start;

	 cout << " fin chargement allwords avec : " << allWords.size() << " mots ";
	 cout << " temp : " << float_ms.count() << "  milliseconds" << endl;
	
 }



 void boggle::allwords_aux( const unsigned short& position, bool &lettre_dispo, const  string &mot , dico& dictionnaire)
 {
		
	 if (mot.size() >= 3  && dictionnaire.label_in_arbre(mot , dictionnaire)  )                  // ajoute les mots superieure ou egal a 3
		 allWords.push_back(new string(mot));
			
	 
	 (&lettre_dispo)[position] = false;                  // j utilise cette lettre donc false
	 bool& tab_copy = copyBool(lettre_dispo);                  // je fais une copy 
	 vector<unsigned short*> list_adjacent = getAdjacent(position , lettre_dispo);                // je trouve ces adjacents ( position  )

	 //pour chaque adjacent j'appele cette fonction avec la position voisine , le tableau de lettre possible et j ajoute la lettre au mot 
	 
	 for (vector<unsigned short*>::iterator it = list_adjacent.begin(); it != list_adjacent.end(); ++it) 
		 allwords_aux(**it, tab_copy, mot + grille[**it] , dictionnaire );
			 
	 (&lettre_dispo)[position] = true;                  //sorti de tous les ajdacents 
	 
	 delete & tab_copy;
	
 }







