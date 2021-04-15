#ifndef TRI_INCLUDED
#define TRI_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "type.h"
#include "utils.h"
using namespace std;

//Function: ajoutTri
//add an elementAdd to the right position in a list
//Input: the elementObjet* eleAdd, elementObjet* list
//return: elementObjet* list added
elementObjet* ajoutTri(elementObjet* eleAdd, elementObjet* liste);

//Function: triInsertionRecursif
//tri with the insertion of the first elementObjet in the listNoTri into a listTri
//Input: pointers listNoTri et listTri
//return: pointer listTri 
//elementObjet* triInsertionRecursif(elementObjet* listNoTri, elementObjet* listTri);
elementObjet* triInsertionRecursif(elementObjet* listNoTri, elementObjet* listTri, elementObjet* eleAdd);

//suppressionDebut
//delete the first element of the list
//Input: a list of elementObjet
//return: the list with the first element deleted
elementObjet* suppressionDebut(elementObjet* liste);

//ajoutDebut
//add an element at the begining of the list
//Input: a list of elementObjet
//return: the list added
elementObjet* ajoutDebut(elementObjet* eleAdd, elementObjet* liste);

/*
//concaListe
//connect two list of elementObjet
//Input: two list
//Return: the final list connected
elementObjet* concaListe(elementObjet* l1, elementObjet* l2)
*/

//triRapide
//sort by a pivot, connect the less and pivot and greater
//Input: a list need to be sorted
//Return: list sorted
elementObjet* triRapide(elementObjet* liste);


#endif // TRI_INCLUDED