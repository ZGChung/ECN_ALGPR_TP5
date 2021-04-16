/*************************************************************

 Auteur: ZHONG Zijie, HAN Tengfei
 Date: 15/04/2021
 But: TP5 contient des diverses fonctions pour traiter(ajouter, affichier, ecrire/lire les documents et les stocker dans une liste) les structures dans le fichier type.h

*************************************************************/

#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include "type.h"
#include "tri.h"

using namespace std;

//Function: ajoutFin
//add a elementObjet to a list of objets
//input: eleObj want to add, list to add to
//return: list added
elementObjet* ajoutFin(elementObjet *eleObj, elementObjet *liste);

//Funciton: lireObjets
//read a file and stock in a list of objets
//input: filename, number of objets in the file
//return: elementObjet* list readed
elementObjet* lireObjets(string nomFichier, int nomMax);

//Function: ecrireObjets
//write a list of objets into a file
//input: the list of objets, filename want to output
//return: non(the generated file)
void ecrireObjets(elementObjet* liste, string nomFichierGene);

//Function: afficherListe
//Display the first nb_max elements in the liste to help debug
void afficherListe(elementObjet* eleFocus, int max);

//Function: calculRetard
//calculate the late days and the penality
//Input: list sorted
//Return: struct Result
Result calculRetard1(elementObjet* liste);

#endif // UTILS_INCLUDED