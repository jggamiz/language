/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file CLASSIFY.cpp
 * @author Jorge García Gámiz <jorgegarciag@correo.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>

#include "Bigram.h"
#include "BigramFreq.h"
#include "Language.h"
#include "BigramCounter.h"

using namespace std;

/**
 * Gets the position of the minimun distance to the Language language
 * @param language The language we are going to compare with, array An array of Language
 * objects from where we are going to extract the languages to compare with the one given 
 * in the first place, nElements Size of the array
 * @return The index of the Language with the minimun distance 
 */
int posMinLanguage(const Language& language, const Language array[], int nElements){
    double distance=1;
    int index=0;
    
    for (int i=0; i<nElements; i++){
        if (language.getDistance(array[i]) < distance){
            distance = language.getDistance(array[i]);
            index = i;
        }
    }
       
    return index;    
}

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "CLASSIFY <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ....]" << endl;
    outputStream << "          Obtains the identifier of the closest language to the input text file" << endl;
    outputStream << endl;
}

/**
 * This program print the language identifier of the closest language 
 * for an input text file (<text.txt>) among the set of provided models:
 * <lang1.bgr>, <lang2.bgr>, ...
 * 
 * Running example:
 * > CLASSIFY  <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ...]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char *argv[]) {
    
    if (argc<3){
        showEnglishHelp(cerr);
        return 1;
    }
    
    int nFilesToCompare=argc-2;
    
    // Creation of the objects we are going to work with
    BigramCounter text;
    text.calculateFrequencies(argv[1]);
    
    Language implicit;
    implicit = text.toLanguage();

    Language* otherLanguages=nullptr;
    otherLanguages = new Language[nFilesToCompare];
    
    double distances[nFilesToCompare];
    
    // Now we read all the others
    int tam=0;
    for (int i=2; i<argc; ++i){
        otherLanguages[tam].load(argv[i]);
        tam++;
    }
    
    // Calculation of the distances
    for (int i=0; i<tam; i++){
        distances[i] = implicit.getDistance(otherLanguages[i]);
    }
    
    // Selection of the minimun of the distances
    int index = posMinLanguage(implicit, otherLanguages, tam);
     
    cout << "Final decision: language " << otherLanguages[index].getLanguageId() 
         << " with a distance of " << distances[index] << endl;
    
    delete[] otherLanguages;


    return 0;
}