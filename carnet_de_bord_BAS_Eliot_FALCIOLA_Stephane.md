# Carnet de Bord BAS Eliot & FALCIOLA Stéphane (Binôme 22)

## Séance du 8/06/2023

Durant cette séance, nous avons réalisé :
- correction chiffrement et déchiffrement fichier
- correction chiffrement et déchiffrement image bitmap
- implémentation de la mesure de l'entropie
- ajout de tests
- optimisations sur le chiffrement cbc d'une image :
  - sans optimisation de compilation : 480Ko/s
  - flag -O2 -> x8
  - flag -O3 -> x10 -> 4,8Mo/s

***

## Séance du 7/06/2023

Durant cette séance, nous avons réalisé :
- Fin de l'implémentation du chiffrement ECB et CBC
- implémentation chiffrement et déchiffrement fichier
- implémentation chiffrement et déchiffrement image bitmap
- début de l'implémentation de la mesure de l'entropie

***

## Séance du 6/06/2023

Durant cette séance, nous avons réalisé :
- Finalisation de l'implémentation d'AES en C
- Génération de la Sbox et RSbox avec haskell (fichier SboxGenerator)
- Correction mixColumns et ajout de invMixColumns (et tests)
- Correction de addRoundKey (et tests)
- Ajout des fonctions cipher et invCipher (et tests pour chaque taille de clé)
- Ajout de l'implémentation du chiffrement ECB et CBC
- Création de la branche "performance" pour les optimisations
- Réflexion optimisations temps d'éxecution du code C

***

## Séance du 5/06/2023

Durant cette séance, nous avons réalisé :
- Avancement de l'implémentation d'AES en C
- Ajout des fonctions subWord et rotWord (et tests)
- Ajout de la fonction mixColumns (et tests)
- Ajout fonction AddRoundKey (et tests)
- Ajout de la fonction keyExpansion (et tests)
- Ajout de fonctions utilitaires

***

## Séance du 17/05/2023

Durant cette séance, nous avons réalisé :
- Finalisation de l'interface Haskell pour chiffrer et déchiffrer
- Ajout du chiffrement avec une clef de 256 bits
- Début de la rédaction de la documentation pour l'implémentation Haskell
- Ajout de tests pour les fonctions utilitaires en C
- Début de la fonction addRoundKey en C
- Début de la fonction mixColumns en C
- Ajout de tests pour mixColumns en C

***

## Séance du 03/05/2023

Durant cette séance, nous avons réalisé :
- Mise au point de notre avancement
- tests de shiftRows
- fonction invShiftRows et tests
- tests de addRoundKeys
- ajout de cas removeRight0 et fillRightZero
- début de KeyExpansion
- implémentation de CipherAES128

### Objectifs pour la prochaine séance :

**BAS Eliot :**  
- [X] Corriger modifications modulo
- [X] Finir KeyExpansion
- [X] Faire fonctions de conversion hexadécimal / polynômes
- [X] Finir implémentation Haskell
- [X] Tester fonctions créées et tests finaux
- [X] Commencer implémentation en C

**FALCIOLA Stéphane :**  
- [X] Finir CipherAES128
- [X] Faire invCipherAES128
- [X] Finir implémentation Haskell
- [X] Tester fonctions créées et tests finaux
- [X] Commencer implémentation en C

***

## Séance du 18/04/2023

Durant cette séance, nous avons réalisé :
- Création des types nécessaires à AES
- implémentation des fonctions stateToInput et stateToOutput
- rédaction de tests
- implémentation de la fonction subByte

### Objectifs pour la prochaine séance :

**BAS Eliot :**  
- [X] Revoir l'implémentation des polynômes => abstraction supplémentaire
- [X] Corriger les types des fonctions (PolyCoefF2 ou GF2_8)
- [X] Finir fonction subBytes, invSubBytes et tester
- [X] Faire fonction mixColumns, invMixColumns et tester

**FALCIOLA Stéphane :**  
- [X] Finir stateToOutput et tester
- [X] Faire fonction shiftRows
- [X] Faire fonction addRoundKey 
- [X] Commencer Key Expansion (rotWord et subWord)

***

## Séance du 5/04/2023

Durant cette séance, nous avons réalisé :
- Mise en place du repo sur GitLab et des repos locaux
- Correction de bugs pour le modulo de polynômes
- Ecriture de tests pour le modulo, la somme modulo et le produit modulo de pôlynomes
- Début de l'implémentation de la fonction inverse de polynômes
- Réflexions sur les structures algébriques nécessaires et sur GF(2^8) (partie 4.3)

### Objectifs pour la prochaine séance :

**BAS Eliot :**  
- [X] Revoir la fonction modulo (refactoriser)
- [X] Finir fonction inverse modulo
- [X] Tester fonction inverse modulo
- [X] Implémenter le produit de polynômes à coefficients dans GF(2^8)
- [X] Réfléchir aux futures étapes de l'algorithme et du développement

**FALCIOLA Stéphane :**  
- [X] Ajouter l'instance anneau et corps de GF(2^8)
- [X] Implémenter le type de polynômes à coefficients dans GF(2^8)
- [X] Implémenter la somme de polynômes à coefficients dans GF(2^8)
- [X] Réfléchir aux futures étapes de l'algorithme et du développement

***

## Séance du 21/03/2023

Durant cette séance, nous avons réalisé :
- Lecture du sujet ainsi que du document sur AES
- Revoir les structures algébriques : anneaux, corps, polynômes à coefficients dans un corps
- Compréhension du code donné sur chamilo.
- Définition de la classe de type pour un anneau et un corps.
- Implémentation type + des anneaux des polynômes à coeff dans un corps.

### Objectifs pour la prochaine séance :

**BAS Eliot :**  
- [X] Implémentation (types, +,-,x) des anneaux des polynômes à coefficients dans un corps.
- [X] Tests sur des polynômes à coefficients dans F2
- [X] Implémentation du calcul modulo un polynôme (+,-,x)
- [X] Réflexion sur l'implémentation de GF(2^8) à partir des éléments déjà construits
- [X] Lecture approfondie de la partie 4 du doc fips AES

**FALCIOLA Stéphane :**  
- [X] Implémentation du calcul modulo un polynôme (+,-,x)
- [X] Tests avec le polynôme m d'AES
- [ ] Implémentation de l'inverse modulo m dans F2[X]
- [X] Réflexion sur l'implémentation de GF(2^8) à partir des éléments déjà construits
- [X] Lecture approfondie de la partie 4 du doc fips AES
