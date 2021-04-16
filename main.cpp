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
  cout << "---"<<endl;
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
    cout <<"---"<<endl;
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
  afficherListe(liste,10);

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
  afficherListe(listeTriee,10);
  cout << "---Liste sorted printing finished.---" << endl;
  cout << "To see the complete output, please check testResult_triInsertionRecursif.txt"<<endl;
  nomFichierGene = "testResult_triInsertionRecursif.txt";
  ecrireObjets(listeTriee,nomFichierGene);
  cout << "----------"<< endl;


  cout << "----------"<< endl;
  cout << "6.Test results of suppressionDebut()"<<endl;
  liste = lireObjets("data1/objetsInput_100.txt", 100);
  cout << "    a)The first 5 elements of liste now is: "<<endl; 
  afficherListe(liste,5);
  cout << "---"<<endl;
  liste = suppressionDebut(liste);
  cout << "    b)The first 5 elements of liste now is: "<<endl; 
  afficherListe(liste,5);
  cout << "---"<<endl;
  liste = suppressionDebut(liste);
  cout << "    c)The first 5 elements of liste now is: "<<endl; 
  afficherListe(liste,5);
  cout << "---"<<endl;
  liste = suppressionDebut(liste);
  cout << "    d)The first 5 elements of liste now is: "<<endl; 
  afficherListe(liste,5);
  cout << "---"<<endl;
  cout << "By comparing these listes, we confirm that the function works." << endl;
  cout << "----------"<< endl;


  cout << "----------"<< endl;
  cout << "7.Test results of ajoutDebut()"<<endl;
  liste = lireObjets("data1/objetsInput_100.txt", 100);
  cout << "Copy the 21-24th elements and add them to the beginning one by one."<<endl;
  eleFocus = liste;
  for(int i =0;i<20;i++){
    eleFocus = eleFocus->suivant;
  }
  cout << "The first 5 elements of the initial liste is :"<<endl;
  afficherListe(liste,5);
  cout << "The 4 elements to be added are: "<< endl;
  afficherListe(eleFocus,4);

  
  for (int i = 0 ; i <4 ; i++){
    eleAdd = new(elementObjet);
    *eleAdd = *eleFocus;
    cout <<"---ajoutDebut()---"<<endl;
    liste = ajoutDebut(eleAdd, liste);
    cout << "The first 5 elements of the current liste is :"<<endl;
    afficherListe(liste,5);
    eleFocus = eleFocus->suivant;
  }
  
  cout << "The function works."<< endl;
  cout << "----------"<< endl;


  cout << "----------"<< endl;
  cout << "8.Test results of concaListe()"<<endl;
  liste = lireObjets("data1/objetsInput_100.txt", 100);
  elementObjet* l1;
  elementObjet* l2;
  elementObjet* eleFocus2;

  l1 = liste;
  l2 = liste->suivant->suivant->suivant;
  l1->suivant->suivant->suivant=NULL;
  l2->suivant->suivant->suivant=NULL;
  cout << "Here are the 2 listes to be concatinated."<< endl;
  cout << "---l1---"<<endl;
  afficherListe(l1,4);
  cout << "---l2---"<<endl;
  afficherListe(l2,4);
  cout << "Here is the result of concatination."<< endl;
  l1 = concaListe(l1,l2);
  afficherListe(l1,7);
  cout <<"The function works."<<endl;

  cout << "----------"<< endl;

  cout << "----------"<< endl;
  cout << "9.Test results of triRapide()"<<endl;
  cout << "---"<<endl;
  //cout<<"Remarque : Je n'ai pas utilisé la méthode de swap que j'ai parlé pendant le cours de TP car j'ai réalisé c'est compliqué quand on travaille avec une liste chaînée simple. "<<endl;
  //cout << "---"<<endl;
  liste = lireObjets("data1/objetsInput_100.txt", 100);

  cout << "The first 10 elements of the unsorted list" <<endl;
  eleFocus = liste;
  afficherListe(liste,11);

  cout << "---Liste unsorted printing finished.---" << endl;

  //listeEmpty was defined previously
  listeEmpty = NULL;
  //eleAdd was defined previously
  eleAdd = NULL;
  //listeTriee was defined previously
  listeTriee = NULL;
  listeTriee = triRapide(liste);

  cout << "---"<<endl;
  cout << "The first 10 elements of the sorted list" <<endl;
  eleFocus = listeTriee;
  afficherListe(listeTriee,10);

  cout << "---Liste sorted printing finished.---" << endl;
  
  cout << "To see the complete output, please check testResult_triRapide.txt"<<endl<<endl;
  nomFichierGene = "testResult_triRapide.txt";
  ecrireObjets(listeTriee,nomFichierGene);
  cout<<"By comparing with the result obtained with the function triInsertionRecursif(), we found that the results are similar, except for the elements with the same dates of delivery. "<<endl<<endl;
  cout<<"The function works."<<endl;
  cout << "----------"<< endl;

  cout << "----------"<< endl;
  cout << "10.Test results of calculRetard1()"<<endl;
  liste = lireObjets("testResult_triRapide.txt", 100);
  Result res;
  res = calculRetard1(liste);

  cout<<"The hypothesis we took for this algorithm are:"<<endl;
  cout<<"    1. the list input is sorted according to the dates (early to late)"<<endl;
  cout<<"    2. all the other resources for production are abundant"<<endl;
  cout<<"    3. we can't pause in the middle of the production of one object"<<endl;
  cout<<"    4. we produce strictly in the order of the dates"<<endl;
  cout << "---"<<endl;
  cout << "The results are:"<< endl;
  cout<<"1.     Days of delay (WITHOUT multiplicity of objects)"<<endl;
  cout<<"    "<<res.jour<<" [jour(s)]" <<endl;
  cout<<"1.bis. Days of delay (WITH multiplicity of objects)"<<endl;
  cout<<"    "<<res.jour_mul<< " [jour(s)]" <<endl;
  cout<<"2.     Total penalty"<<endl;
  cout<<"    "<<res.penal<<" [unit d'argent]" <<endl;
  cout<<endl<<"More details of the log is stroed in the file log_penalty_100.txt"<<endl;
  cout<<endl<<"Function works."<<endl;
  cout << "----------"<< endl;

  cout << "----------"<< endl;
  cout << "11.Partie temps d'execution pour les deux facons de tri"<< endl;
  cout << "----------"<< endl;

  cout << "----------"<< endl;
  cout << "a.Test de temps d'execution pour la fonction triInsertionRecursif"<< endl;

  //preparation to get the nomFichier
  nomFichier="";
  numListe1={100,500,1000,5000,10000};//defined defore
  typedef vector<string> nomDossier;
  nomDossier nomDossier1;
  nomDossier1.resize(4);
  nomDossier1={"data1/","data2/","data3/","data4/"};

  for(int i=0;i<4;i++){
    for(int j=0;j<5;j++){
      //modify the nomFichier for each interation of test
      nomFichier = nomDossier1[i];
      nomFichier += "objetsInput_";
      nomFichier += to_string(numListe1[j]);
      nomFichier += ".txt";
      //write the nomFichierGene for each interation of test
      nomFichierGene = "testTemps_triInsertionRecursif/";
      nomFichierGene += nomDossier1[i];
      nomFichierGene += "objetsInput_";
      nomFichierGene += to_string(numListe1[j]);
      nomFichierGene += ".txt";

      //call the functions triInsertionRecursif()
      elementObjet* liste;
      elementObjet* listeTIR;
      listeTIR = NULL;
      eleAdd = NULL;//defined before
      liste = lireObjets(nomFichier, numListe1[j]);

      //to get the time of run
      clock_t start,end;
      start = clock();//start time
      listeTIR = triInsertionRecursif(liste, listeTIR, eleAdd);
      end = clock();//end time

      ecrireObjets(listeTIR,nomFichierGene);
      cout << nomDossier1[i] << " " << numListe1[j] << " " << (double)(end-start)/CLOCKS_PER_SEC
      <<" ms" <<endl;
      
    }
    
  }
  cout << "----------"<< endl;

  cout << "----------"<< endl;
  cout << "b.Test de temps d'execution pour la fonction triRapide"<< endl;

  //preparation to get the nomFichier
  nomFichier="";

  for(int i=0;i<4;i++){
    for(int j=0;j<5;j++){
      //modify the nomFichier for each interation of test
      nomFichier = nomDossier1[i];
      nomFichier += "objetsInput_";
      nomFichier += to_string(numListe1[j]);
      nomFichier += ".txt";
      //write the nomFichierGene for each interation of test
      nomFichierGene = "testTemps_triRapide/";
      nomFichierGene += nomDossier1[i];
      nomFichierGene += "objetsInput_";
      nomFichierGene += to_string(numListe1[j]);
      nomFichierGene += ".txt";

      //call the functions triRapide()
      elementObjet* liste;
      elementObjet* listeTIR;
      listeTIR = NULL;
      liste = lireObjets(nomFichier, numListe1[j]);

      //to get the time of run
      clock_t start,end;
      start = clock();//start time
      listeTIR = triRapide(liste);
      end = clock();//end time

      ecrireObjets(listeTIR,nomFichierGene);
      cout << nomDossier1[i] << " " << numListe1[j] << " " << (double)(end-start)/CLOCKS_PER_SEC
      <<" ms" <<endl;
      
    }
    
  }
  cout << "----------"<< endl;
  /*
  //to get the time of run
  clock_t start,end;
  start = clock();
  //function test here
  end = clock();
  cout << "Time of run of lireObjets()"
  <<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  */

}