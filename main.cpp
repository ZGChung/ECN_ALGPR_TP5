#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "type.h"
#include "utils.h"
#include "tri.h"
using namespace std;

int main() {
  std::cout << "Hello World!\n";
  elementObjet* liste;
  elementObjet* eleFocus;

  liste = lireObjets("data1/objetsInput_100.txt", 100);
  //cout << "pt1"<<endl;
  eleFocus = liste;
  cout << "----------"<< endl;
  cout << "1.Test result of lireObjets()"<<endl;
  for (int i = 0; i < 5; i ++)
  {
    //cout << "pt2"<<endl;
    //write in the file
    
    cout << eleFocus->nomObjet << " "
    << eleFocus->nbObjet << " "
    << eleFocus->date << " "
    << eleFocus->dureePro << " "
    << eleFocus->nbMati << " ";
    ensMatieres ensMat;
    ensMat = eleFocus->ensMat;
    // cout << "pt3"<<endl;
    for (int k = 0; k < eleFocus->nbMati; k++){
      cout << ensMat[k].nom << " " << ensMat[k].poids << " ";
    }
    cout << eleFocus->volume<<endl;
    eleFocus = eleFocus->suivant;
  }
  cout << "----------"<< endl;

  cout << "----------"<< endl;
  cout << "2.Test results of ecrireObjets()" << endl;
  cout << "New file generated in the folder testResult_ecrireObjets, named as objetsInputGenere_100.txt" << endl;
  string nomFichierGene; 
  nomFichierGene = "testResult_ecrireObjets/objetsInputGene_100.txt";
  ecrireObjets(liste,nomFichierGene);
  cout << "----------"<< endl;
  
  cout << "----------"<< endl;
  cout << "3.Calculate the execution time of lireObjets() and ecrireObjets() for the 5 datasets in data1" << endl;
  //iteration over the 5 files in data1
  typedef vector<int> numListe;
  numListe numListe1;
  numListe1.resize(5);
  numListe1={100,500,1000,5000,10000};
  string nomFichier;

  //cout << "pt1" << endl;
  for(int j=0;j<5;j++){
    //modify the nomFichier for each interation of test
    //cout << "pt2" << endl;
    nomFichier = "data1/objetsInput_";
    nomFichier += to_string(numListe1[j]);
    nomFichier += ".txt";
    //write the nomFichierGene for each interation of test
    nomFichierGene = "testResults_ecrireObjets/objetsInput_";
    nomFichierGene += to_string(numListe1[j]);
    nomFichierGene += ".txt";

    //cout << nomFichier << endl;
    //cout << nomFichierGene << endl;
    //cout << numListe1[j] << endl;
    //call the functions lireObjets() and ecrireObjets()
    elementObjet* liste;
    liste = NULL;
    //to get the time of run
    clock_t start,end;

    start = clock();//start time
    //cout << "pt3" << endl;
    liste = lireObjets(nomFichier, numListe1[j]);
    //cout << "pt4" << endl;
    ecrireObjets(liste,nomFichierGene);
    end = clock();//end time
    cout << "Total time to run lireObjets() and ecrireObjets() with "
    << nomFichier << " is" <<endl;
    cout <<(double)(end-start)/CLOCKS_PER_SEC
    <<" ms" <<endl;
  }

  /*
  //to get the time of run
  clock_t start,end;
  start = clock();
  //function test here
  end = clock();
  cout << "Time of run of lireObjets()"
  <<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  */

  cout << "----------"<< endl;
  
  cout << "----------"<< endl;
  cout << "4.Test results of ajoutTri()"<<endl;
  elementObjet* ele1;
  elementObjet* ele2;
  elementObjet* ele3;
  ele1 = new(elementObjet);
  ele2 = new(elementObjet);
  ele3 = new(elementObjet);
  ele1->nomObjet = vectObjetNom[1];
  ele2->nomObjet = vectObjetNom[2];
  ele3->nomObjet = vectObjetNom[3];
  ele1->date = 1;
  ele2->date = 3;
  ele3->date = 2;
  ele1->suivant = NULL;
  ele2->suivant = NULL;
  ele3->suivant = NULL;

  elementObjet* listeTriee;
  listeTriee = NULL;
  elementObjet* eleAAfficher;
  eleAAfficher = NULL;

  listeTriee = ajoutTri(ele1, listeTriee);
  eleAAfficher = listeTriee;
  for(int i = 0;i < 1; i++){
    cout << eleAAfficher->nomObjet <<" "<<eleAAfficher->date<<endl;

    eleAAfficher = listeTriee->suivant;
  }
  cout << "---"<<endl;

  listeTriee = ajoutTri(ele2, listeTriee);
  eleAAfficher = listeTriee;
  for(int i = 0;i < 2; i++){
    cout << eleAAfficher->nomObjet <<" "<<eleAAfficher->date<<endl;

    eleAAfficher = listeTriee->suivant;
  }
  cout << "---"<<endl;

  listeTriee = ajoutTri(ele3, listeTriee);
  eleAAfficher = listeTriee;
  for(int i = 0;i < 3; i++){
    cout << eleAAfficher->nomObjet <<" "<<eleAAfficher->date<<endl;

    eleAAfficher = eleAAfficher->suivant;
  }
  cout << "---"<<endl;
  cout << "The third element added was well placed in the second place, function works."<<endl;
  cout << "----------"<< endl;

  cout << "----------"<< endl;
  cout << "5.Test results of triInsertionRecursif()"<<endl;
  liste = lireObjets("data1/objetsInput_100.txt", 100);

  cout << "The first 10 elements of the unsorted list" <<endl;
  eleFocus = liste;
  afficherListe(liste);
  /*
  for (int i = 0; i < 10; i ++)
  {
    //write in the file
    cout <<i+1<<". "<< eleFocus->nomObjet << " "
    << eleFocus->nbObjet << " "
    << eleFocus->date << " "
    << eleFocus->dureePro << " "
    << eleFocus->nbMati << " ";
    ensMatieres ensMat;
    ensMat = eleFocus->ensMat;
    for (int k = 0; k < eleFocus->nbMati; k++){
      cout << ensMat[k].nom << " " << ensMat[k].poids << " ";
    }
    cout << eleFocus->volume<<endl;
    if(i==9){
      eleFocus->suivant = NULL;
      //cut the tail for faster test
      break;
    }
    eleFocus = eleFocus->suivant;
  }
  */
  cout << "---Liste unsorted printing finished.---" << endl;

  elementObjet* listeEmpty;
  listeEmpty = NULL;
  elementObjet* eleAdd;
  eleAdd = NULL;
  //listeTriee was defined previously
  listeTriee = NULL;
  listeTriee = triInsertionRecursif(liste, listeEmpty, eleAdd);

  cout << "---"<<endl;
  cout << "The first 10 elements of the sorted list" <<endl;
  eleFocus = listeTriee;
  afficherListe(listeTriee);
   cout << "---Liste sorted printing finished.---" << endl;
  cout << "----------"<< endl;
}