# Documentation AES Haskell - BAS Eliot & FALCIOLA Stéphane (Binôme 22)

## Fonctionnalités :
Le programme permet d’effectuer le chiffrement et le déchiffrement AES d’un message de 128 bits.
Il permet d’utiliser au choix une clé de 128 bits, 192 bits ou 256 bits pour le chiffrement et déchiffrement du message.

Pour lancer le programme, il suffira charger le module Main.hs dans l'interprète ghci et de lancer la commande suivante : 
```haskell
main
```
ou encore de compiler le programme :
```bash
ghc Main.hs
```
puis de lancer le programme :
```bash
./Main
```
Dans le terminal, le programme vous demandera alors de choisir entre le chiffrement et le déchiffrement, puis de choisir la taille de la clé (128, 192 ou 256 bits), de rentrer la clé de chiffrement en hexadécimal et enfin le message à chiffrer/déchiffrer en hexadécimal également.

## Structure du projet :

L'ensemble du projet est constitué de 4 modules et du fichier Main.hs qui permet de lancer le programme.:  

**Structures.hs :** Classes Anneau et Corps  
**Polynomes.hs :** Polynômes, ensembles de polynômes et opérations sur les polynômes  
**AES.hs :** Algorithme AES  
**Conversion.hs :** Conversions hexadécimal/polynômes pour les tests et l'intégration finale  
**Main.hs :** Interface pour le chiffrement/déchiffrement  

## Tests : 
Les modules sont testés intensivement pour s’assurer que chaque fonction marche correctement.
Les tests sont constitués de tests sur les bornes ou valeurs particulières et de tests sur des valeurs plus aléatoires.
Un maximum des exemples présents dans le FIPS 197 ont été testés.
Des tests de bout en bout ont été ajoutés pour vérifier le bon fonctionnement de l’algorithme AES au complet.
Pour faciliter l'utilisation des tests, nous avons utilisé la conversion hexadécimal/polynômes du module Conversion.hs.

## Difficultés rencontrées :

La principale difficulté rencontrée a été de penser en "fonctionnel" en non en impératif comme on en a l'habitude, ce qui a demandé un petit temps d'adaptation.
Le fonctionnement des types en Haskell fut un peu déroutant au début, provoquant des erreurs parfois peu explicites.
L'algorithme AES prend du temps à bien être cerné sans être particulièrement complexe.
Nous n'avons pas eu choix technique de "grande ampleur" à réaliser, le langage et l'algorithme étant imposés, cependant nous avons fait quelques choix concernant l'implémentation des briques élémentaires de l'algorithme AES et la structure du projet.
Nous avons dans un premier temps implémenté les structures mathématiques dans les modules *Structures* et *Polynômes* puis nous avons implémenté l'algorithme AES à partir de ces structures mathématiques dans le module *AES*.