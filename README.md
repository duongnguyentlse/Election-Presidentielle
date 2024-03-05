# Simulation d'une élection présidentielle

**Prerequisites**

Before you continue, ensure you meet the following requirements:

* I recommend you to ```make clean``` before run the programme.
* You are using a Linux or Mac OS machine. Windows is not currently supported beacause i did on Mac.

Ce programme lit un fichier .csv contenant soit le bulletin de vote des électeurs (leurs données avec leur ordre de préférence associé pour chaque candidat) soit une matrice de préférences par paires, puis détermine le vainqueur en utilisant les méthodes suivantes :

Élection uninominale à un tour [telle qu'appliquée au Royaume-Uni et dans les pays du Commonwealth]
Élection uninominale à deux tours [comme appliquée en France]
Minimax (Condorcet)
Schulze (Condorcet)
Les deux dernières méthodes Condorcet mentionnées sont utilisées pour mieux refléter la voix et les préférences des électeurs, comme l'a souligné Nicolas de Caritat, marquis de Condorcet, dans son "Essai sur l'application de l'analyse à la probabilité des décisions rendues à la pluralité des voix".

Enfin, ce projet fait partie de mes études de licence en informatique (premier semestre de la deuxième année).





