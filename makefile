prog: main.o dico.o boggle.o
	g++ -o  boggle main.o dico.o boggle.o
main.o: main.cpp
	g++ -c -std=c++17 main.cpp
dico.o: dico.cpp
	g++ -c -std=c++17 dico.cpp
boggle.o: boggle.cpp
	g++ -c -std=c++17 boggle.cpp
	


	
