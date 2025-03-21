# 🗳️ Simulation d'une Élection Présidentielle

## 📌 Présentation  
Ce projet est une **simulation de différentes méthodes de vote utilisées dans une élection présidentielle**.  
Il permet de déterminer le vainqueur en lisant un fichier **.csv** contenant :  
- Soit les **bulletins de vote des électeurs** avec leur ordre de préférence pour chaque candidat.  
- Soit une **matrice de préférences par paires**.  

Le programme applique plusieurs méthodes de scrutin pour élire le gagnant, notamment :  
1. **Élection uninominale à un tour** (utilisée au Royaume-Uni et dans le Commonwealth).  
2. **Élection uninominale à deux tours** (système en vigueur en France).  
3. **Méthode Minimax (Condorcet)**.  
4. **Méthode Schulze (Condorcet)**.  

Les deux dernières méthodes sont inspirées des travaux du **marquis de Condorcet**, qui visait à mieux refléter les préférences des électeurs dans son *"Essai sur l'application de l'analyse à la probabilité des décisions rendues à la pluralité des voix"*.  

Ce projet a été réalisé dans le cadre de mes **études de licence en informatique** (premier semestre de la deuxième année).  

---

## ⚙️ Prérequis  

Avant d'exécuter le programme, assurez-vous de respecter les conditions suivantes :  
✔️ **Effectuer un `make clean` avant d'exécuter le programme** pour éviter les conflits d'anciens fichiers compilés.  
✔️ **Utiliser un environnement Linux ou macOS** (Windows n'est pas supporté car le développement a été réalisé sur macOS).  

---


Enfin, ce projet fait partie de mes études de licence en informatique (premier semestre de la deuxième année).





