/*************************************************************

 Auteur: ZHONG Zijie, HAN Tengfei
 Date: 15/04/2021
 But: TP5 contient des diverses fonctions pour traiter(ajouter, affichier, ecrire/lire les documents et les stocker dans une liste) les structures dans le fichier type.h

*************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "type.h"
#include "utils.h"//verify
using namespace std;

//ajoutFin
elementObjet* ajoutFin(elementObjet *eleObj, elementObjet *liste){
  //cout << "pta1" << endl;
  if (liste == NULL){ //we add the eleObj to an empty liste
  //cout << "pta2" << endl;
    return eleObj;
  }
  else{ //we add the eleObj to an existed liste, return the exsiting liste
  //cout << "pta2" << endl;
    elementObjet* eleFocus;//current pointer
    eleFocus = liste;
    while(eleFocus->suivant != NULL){//go next until we reach the end
    //cout << "pta3" << endl;
      eleFocus = eleFocus->suivant;
    }
    //cout << "pta4" << endl;
    eleFocus->suivant = eleObj;//add eleobjet to end
    eleObj->suivant = NULL; //just to ensure
    //cout << "pta5" << endl;
    return liste;
  } 
}

//lireObjets
elementObjet* lireObjets(string nomFichier, int nomMax){
  //cout << "pta" << endl;
  fstream fichier, out;
  int iter = 0;
  elementObjet* liste;//return value
  liste = NULL;
  //open file to read objets
  fichier.open(nomFichier, ios::in);
  //read a line
  while(iter<nomMax){
    //cout << "ptb"<<endl;
    elementObjet* ele;
    ele = new(elementObjet);//stock objets
    ele->suivant = NULL;
    fichier >> ele->nomObjet;
    fichier >> ele->nbObjet;
    fichier >> ele->date;
    fichier >> ele->dureePro;
    fichier >> ele->nbMati;
    //cout << "ptc"<<endl;
    ele->ensMat.resize(ele->nbMati);
    for(int j=0;j<ele->nbMati;j++){
      fichier >> ele->ensMat[j].nom;
      fichier >> ele->ensMat[j].poids;
    }
    fichier >> ele->volume;
    //end of read a line
    //cout << "ptd"<<endl;
    liste = ajoutFin(ele,liste);
    //cout << "pte"<<endl;
    iter = iter + 1;
  }
fichier.close();
return liste;
}

//ecrireObjets
void ecrireObjets(elementObjet* liste, string nomFichierGene)
{
  fstream fichier;
  int lengthListe = 0;
  elementObjet* eleFocus;//current pointer
  eleFocus = liste;
  
  //get the lines of list(also: nbObjet)
  while(eleFocus != NULL){
    lengthListe = lengthListe + 1;
    eleFocus = eleFocus->suivant;
  }
  /*
  //write the filename
  nomFichier = "data1/objetsInputGenere_";
  nomFichier += to_string(lengthListe);
  nomFichier += ".txt";
  */
  fichier.open(nomFichierGene,ios::out);

  eleFocus = liste;
  for (int i = 0; i < lengthListe; i ++)
  {
    //write in the file
    fichier << eleFocus->nomObjet << " " 
    << eleFocus->nbObjet << " "
    << eleFocus->date << " "
    << eleFocus->dureePro << " "
    << eleFocus->nbMati << " ";
    ensMatieres ensMat;
    ensMat = eleFocus->ensMat;
    for (int k = 0; k < eleFocus->nbMati; k++){
      fichier << ensMat[k].nom << " " << ensMat[k].poids << " ";
    }
    fichier << eleFocus->volume<<endl;
    eleFocus = eleFocus->suivant;
  }

  fichier.close();
}

//short function to print several first elements of a liste to help debug
void afficherListe(elementObjet* eleFocus, int max){
  if(eleFocus == NULL){
    cout <<"EMPTY LISTE"<<endl;
  }
  else{
    for (int i = 0; i < max; i ++){
      cout << "    "<<i+1<<". "<< eleFocus->nomObjet << " "
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
      if(eleFocus->suivant != NULL){
        eleFocus = eleFocus->suivant;
      }
      else{
        break;//end the printing
      }
    }
  }
}


//calculRetard_Naive
/* 
Calculation with a "fixed" list
in this algorithm, I used these conventions or hypothesis:
1. the list input is sorted according to the dates (early to late)
2. all the other resources for production are abundant 
3. we can't pause in the middle of the production of one object
4. we produce strictly in the order of the dates
*/
Result calculRetard1(elementObjet* liste){
  int jourAct = 0;
  int jours_de_retard = 0;
  int jours_de_retard_mul = 0;
  elementObjet* eleFocus;
  eleFocus = liste;
  Result res;
  fstream fichier;
  fichier.open("log_penalty_100.txt", ios::out);
  
  fichier<<"This is the log file of the process of calculationg of penalty, related to the data in data1/objetsInput_100.txt"<<endl;

  while (eleFocus != NULL){
    jourAct += eleFocus->dureePro;
    fichier<<"---"<<endl;
    fichier<<"Current day number:"<<endl;
    fichier<<"    "<<jourAct<<endl;
    if(eleFocus->dureePro > (eleFocus->date-jourAct)){
      //since we are not sure about the meaning of "nombre des jours de retard", we calculated both 2 possibilities:
      //this is the number of days considering multiplicity of objects
      jours_de_retard_mul += ((jourAct + eleFocus->dureePro - eleFocus->date) * (eleFocus->nbObjet));
      //this is the number of days WITHOUT considering multiplicity of objects
      jours_de_retard += (jourAct + eleFocus->dureePro - eleFocus->date);
      fichier<<"Object in retard: "<<endl;
      //write that retared object
      if(eleFocus == NULL){
        fichier <<"EMPTY LISTE"<<endl;
      }
      else{
        for (int i = 0; i < 1; i ++){
          fichier << "    "<<"- "<< eleFocus->nomObjet << " "
          << eleFocus->nbObjet << " "
          << eleFocus->date << " "
          << eleFocus->dureePro << " "
          << eleFocus->nbMati << " ";
          ensMatieres ensMat;
          ensMat = eleFocus->ensMat;
          for (int k = 0; k < eleFocus->nbMati; k++){
            fichier << ensMat[k].nom << " " << ensMat[k].poids << " ";
          }
          fichier << eleFocus->volume<<endl;
        }
      }
      //end writing the retarded object

      fichier<<"Days of delay of this single object(multiplcity):"<< endl;
      fichier<<"    "<<((jourAct + eleFocus->dureePro - eleFocus->date) * (eleFocus->nbObjet))<<endl;
      fichier<<"Days of delay of this single object(without multiplicity):"<< endl;
      fichier<<"    "<<jourAct + eleFocus->dureePro - eleFocus->date<<endl;
      

    }
    else{
      fichier<<"NO DELAY TODAY"<<endl;
    }
    eleFocus = eleFocus->suivant;
  }
  res.jour = jours_de_retard;
  res.jour_mul = jours_de_retard_mul;
  res.penal = 1* jours_de_retard_mul;
  fichier.close();
  return res;
}

//calculRetard_Global
/* 
Calculation with consideration of rearrangement of the list
in this algorithm, I used these conventions or hypothesis:
1. the list input is sorted according to the dates (early to late)
2. all the other resources for production are abundant 
3. we can't pause in the middle of the production of one object
<MODIFIED> 4. we can reshedule the production of one object later
*/
/*
Brief explanation of how I construct this algorithm for searching a global optimisation of penalty

1. Suppose we are producing the products in the order of dates. We notice that obj1 will be late and we'll receive a penalty

2. We browse all the objects scheduled before obj1, trying to find one or some object(s) whose dureePro add up to a number bigger than the days of relay of obj1. We might find many possible solutions, we store them in an array solution[]

3. For each solution in solution[], we try to reschedule the objects in that solution to just behind the obj1. (Placing them earlier will not solve obj1's problem of penalty and placing them further later will increase unecessary penalty. ) For the case where there are multiple objects in one solution, we have to try with all the permutation of the objects in the solution. For example, if we have k objects in one solution, we'll have k! permutations to be tested. For each permutation, we calculate the total penalty with calculRetard1(). Then we choose the minimum as our result.

4. Now we consider the case where we have plusieur objects late according to our initial production plan. So we calculate the total days of retard for all the objects late. Then we search for solutions just as before and store them in solution[].

5. For each solution, each object in it could be resheduled just behind any of the objects retarded. That's to say, if we have n objects in one solution and we have m objects in retard, we'll have m^n possibilities for the distribution of the objects to be moved, we store all these distributions in distribution[].

6. What's even more complicated is, for each distribution, if there are multiple objects resheduled behind one object retarded, we have to try with all the permutations just as before. So we have to calculate and store the total penalty for each permutation in each distribution in each solution. Then we return the minimum as our result, which is exactly the global optimisation of penalty.
*/

/*
// pseudocode
Result calculRetard2(elementObjet* liste){
  int jourAct = 0;
  int jours_de_retard = 0;
  elementObjet* eleFocus;
  eleFocus = liste;
  int totalRetardDays = 0;

  retardObjets[]=findRetardObjets(liste);
  for x in retardObjets[]{
    totalRetardDays += x.retardDays;
  }
  solution[] = findSolutions(liste,totalRetardDays);
  distributon[] = generateDistributions(liste,retardObjets[],solutions[]);
  permutation[] = generatePermutations(liste,distribution[]);

  for y in permutation[]{
    res = calculRetard1(y);
    penalty[].append(res);
  }
  return min(penalty[]);
}
*/

retardObjet* findRetardObjets(elementObjet* liste){
  int jourAct = 0;
  int jours_de_retard = 0;
  int singleRetard = 0;
  elementObjet* eleFocus;
  eleFocus = liste;
  retardObjet* retObj;
  retObj = NULL;

  while (eleFocus != NULL){
    jourAct += eleFocus->dureePro;
    if(eleFocus->dureePro < jourAct){
      singleRetard = jourAct - eleFocus->dureePro;
      retObj->jour_de_retard = singleRetard;
      retObj->ele = ajoutDebut(eleFocus, retObj->ele);
    }
    eleFocus = eleFocus->suivant;
  }
  return retObj;
}


vector<elementObjet*> findSolutions(elementObjet* liste,retardObjet* retObj){
  // the latest object retarded is the first element of retObj
  elementObjet* endMarker = NULL;
  elementObjet* eleFocus = NULL;
  retardObjet* retObjFocus = NULL;
  int temSum = 0;
  int totalDelayDays = 0;

  retObjFocus = retObj;
  while(retObjFocus != NULL){
    totalDelayDays += retObjFocus->jour_de_retard;
    retObjFocus = retObjFocus->suivant;
  }
  cout<<"Total delay days : "<<endl;
  cout<<totalDelayDays<<endl;

  eleFocus = liste;
  while(eleFocus !=NULL && eleFocus != endMarker){
    //not yet finished
    eleFocus = eleFocus->suivant;
  }
  
}
