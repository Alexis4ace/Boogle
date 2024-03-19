# Boogle
Programme de génération des mots possibles selon un dictionnaire pour le Boogle dans un fichier texte.

Un fichier makefile est disponible pour générer l'exécutable. Puis dans un terminale vous pouvez l'exécuter :
  .\boggle.exe p h q g h u m e a y l n l f d x

  Ce programme parcours une grille ( carré ) et pour chaque case vas chercher tous les mots possibles avec les lettres adjacentes ( mots valide ou non ).
 
  Dans un deuxième temps à partir d'un dictionnaire de mot fournis dans le fichier texte, on crée un arbre avec 26 fils correspondant aux lettres de l’alphabet. 
  On remplis cette arbre avec tout les mots, ce qui nous permet pendant la recherche d'être plus efficace.

  Pour tous les mots trouvés à la première étape, on cherche si il y est dans l'arbre. Si oui on l'ajoute au fichier de sortis soution.txt 
