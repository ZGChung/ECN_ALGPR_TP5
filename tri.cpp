#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "type.h"
#include "utils.h"
#include "tri.h"//verify
using namespace std;

//ajoutTri()
elementObjet* ajoutTri(elementObjet* eleAdd, elementObjet* liste){
  eleAdd->suivant = NULL;
  elementObjet* eleFocusAvant;
  eleFocusAvant = NULL;
  bool breakMark = 0;
  if (liste == NULL){
    //cout << "Enter ajoutTri(), liste is NULL" << endl;
    liste = eleAdd;
  }
  else{
    //cout << "Enter ajoutTri(), liste not NULL" << endl;
    elementObjet* eleFocus;//current elementObjet
    eleFocus = liste;
    if(eleFocus->date >= eleAdd->date){
      eleAdd->suivant = liste;
      liste = eleAdd;
      return liste;
    }
    else{

    }
    while (eleFocus->date < eleAdd->date)
    {//until eleAdd reach the end of list or the right position in the middle
      //cout << "eleFocus < eleAdd" << endl;
      //cout << "eleFocus" << eleFocus->date <<endl;
      //cout << "eleAdd" << eleAdd->date <<endl;
      if(eleFocus->suivant == NULL){//reach the end of list
        //cout << "Next element of eleFocus is NULL" << endl;
        breakMark = 1;
        break; //end while
      }
      else{//go next to compare the date
      //cout << "eleFocus >= eleAdd" << endl;
        eleFocusAvant = eleFocus;
        //save the eleFocus before it moves
        eleFocus = eleFocus->suivant;
      }
    }
    if(breakMark){//reach the end of list
      //cout << "During while, reached the end of liste" << endl;
      eleFocus->suivant = eleAdd;
    }
    else{//find the right position in the middle
      // eleFocus->date >= eleAdd->date
      // insert the eleAdd one term before
      //cout << "During while, NEVER reached the end of liste" << endl;
      eleFocusAvant->suivant = eleAdd;
      //cout<<"current eleFocusAvant" << eleFocusAvant->nomObjet <<endl;
      eleAdd->suivant = eleFocus;
      //cout<<"current eleFocus" << eleFocus->nomObjet <<endl;
    }
  }
  return liste;
}

//triInsertionRecursif()
elementObjet* triInsertionRecursif(elementObjet* listNoTri, elementObjet* listTri, elementObjet* eleAdd){
	if(listNoTri == NULL){
    //cout << "Enter triInsertionRecursif(), listeNoTri is NULL" << endl;
		return listTri;
  }
  else{
      eleAdd = listNoTri;
      //cout << "Enter triInsertionRecursif(), listeNoTri not NULL" << endl;
      //cout << "listeNoTri          " << listNoTri << endl;
      //cout << "listNoTri->suivant  "<<listNoTri->suivant << endl;
      //eleAdd->suivant = NULL;//first

      listNoTri = listNoTri->suivant;//next
      listTri = ajoutTri(eleAdd, listTri);
      //cout << "ajoutTri() finished, current listeTriee is:" << endl;
      //afficherListe(listTri);

      listTri = triInsertionRecursif(listNoTri, listTri, eleAdd);//recursion
      return listTri;
      //cout << "ptd" << endl;
  }
}


//suppressionDebut
elementObjet* suppressionDebut(elementObjet* liste){
  if (liste == NULL){
    return liste;//no modification if liste is empty
  }
  else{
    liste = liste->suivant;//just move the HEAD to the second element
    return liste;
  }
}

//ajoutDebut
elementObjet* ajoutDebut(elementObjet* eleAdd, elementObjet* liste){
  eleAdd->suivant = liste;
  liste = eleAdd;
  return liste;
}

// 我感觉不必使用concaList函数。这个函数每次都遍历一遍l1，我觉得浪费很多时间-ZGC
/*
//concaListe
elementObjet* concaListe(elementObjet* l1, elementObjet* l2){
  if(l1 == NULL){
    return l2;
  }
  else{
    if(l2 == NULL){
      return l1;
    }
    else{
      elementObjet* eleFocus;
      elementObjet* eleFocusAvant;
      eleFocusAvant = NULL;
      eleFocus = l1;
      while (eleFocus!=NULL){
        eleFocusAvant = eleFocus;//save before move
        eleFocus = eleFocus->suivant;
      }
      // at the end of while loop:
      // eleFocus = NULL
      // eleFocusAvant = pointer to last element non null
      eleFocusAvant->suivant = l2;
      return l1;
    }
  }
}
*/

//triRapide
elementObjet* triRapide(elementObjet* liste)
 {
    elementObjet* infListe;
    elementObjet* supListe;
    elementObjet* pivot;
    elementObjet* eleFocus;
    elementObjet* tailInfListe;
    infListe = NULL;
    supListe = NULL;
    pivot = NULL;
    eleFocus = NULL;
    tailInfListe = NULL;

    if ((liste == NULL)||(liste->suivant == NULL)) 
        return liste;
        //if there is 1 or 0 element, it is sorted
    else 
    {
      //select the 1st element as the pivot
      pivot = liste;
      //pick out the 1st element
      liste = suppressionDebut(liste);
      eleFocus = liste;
      while(eleFocus != NULL){
        if(eleFocus->date < pivot->date){
          //put the element in the infListe if it is less than pivot
          if(infListe == NULL){
            //this is the first element being added to the infListe
            tailInfListe = eleFocus->suivant;
          }
          infListe = ajoutDebut(eleFocus, infListe);
        }
        else if(eleFocus->date >= pivot->date){
          //similar with larger elements
          supListe = ajoutDebut(eleFocus, supListe);
        }
      }
      //concat infListe and pivot
      tailInfListe = pivot;
      //concat (infListe,pivot) and supListe
      pivot->suivant = supListe;
      //return the concatinated list
      //return concaListe(concaListe(infListe, pivot),supListe);
      return infListe;
    }
 }
