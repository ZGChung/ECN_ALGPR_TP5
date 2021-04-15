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

void afficherListe(elementObjet* eleFocus){
  for (int i = 0; i < 10; i ++)
  {
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
  elementObjet* eleFocus;
  eleFocus = liste;

  while (eleFocus != NULL){
    jourAct += eleFocus->dureePro;
    if(eleFocus->dureePro < jourAct){
      jours_de_retard += ((jourAct - eleFocus->dureePro) * (eleFocus->nbObjet));
    }
    eleFocus = eleFocus->suivant;
  }
  return Result {jours_de_retard, jours_de_retard*1};
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
      retObj->ele = ajoutFin(eleFocus, retObj->ele);
    }
    eleFocus = eleFocus->suivant;
  }
  return retObj;
}

/*
elementObjet* findSolutions(elementObjet* liste,int totalRetardDays){

}
*/