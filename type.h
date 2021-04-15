#ifndef TYPE_INCLUDED
#define TYPE_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// create a structure for matiere
struct matiere
{
  string nom;
  float poids;
};
// a vector of matieres
typedef vector<matiere> ensMatieres;

// possible name of matieres
const string vectMatiereNom[] = {"chene","acier","verre","plastique","carton", "resine","carbone","caoutchouc"};

// possible name of objets
const string vectObjetNom[] = {"table","chaise","console","lampe","canape", "table-basse","etagere","fauteuil","desserte"};

// elementObjet for a objet
struct elementObjet
{
  string nomObjet;
  int nbObjet;//number of objets in the lot
  int date;//date souhaitee
  int dureePro;//duree of production
  int nbMati;//number of matiere needed
  ensMatieres ensMat;//ensemble of matieres
  float volume;
  elementObjet* suivant;
};
// objet is a simple list of elementObjet

// define the Result struct to return 2 values for question 5
struct Result{
    int jour;
    int penal;
};

struct retardObjet{
  elementObjet* ele;
  int jour_de_retard;
  retardObjet* suivant;
};

#endif // TYPE_INCLUDED