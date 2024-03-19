#pragma once
#ifndef _H_DICO_H_
#define _H_DICO_H_
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class dico
{
	char* label;
	dico* fils;
	bool fin;

	public:
		

		dico(); 
		dico(const char&); 
		~dico();
		
		void add_mot(const string& ,  dico&); 

		bool label_in_arbre(const string&,  dico&);
		
	private:
		void add_arbre(char, dico*);
		void loaddico(const string&);

		bool isEmpty(dico&);

		dico& getFils(unsigned short);

};
#endif
