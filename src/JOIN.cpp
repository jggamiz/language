/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file JOIN.cpp
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
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>] " << endl;
    outputStream << "       join the Language files <file1.bgr> <file2.bgr> ... into <outputFile.bgr>" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-o <outputFile.bgr>: name of the output file (output.bgr by default)" << endl;
    outputStream << "<file*.bgr>: each one of the files to be joined" << endl;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally, the resulting Language is saved in an output file. The 
 * program must have at least an output file. 
 * Running example:
 * >  JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char* argv[]) {
    char mode='t';
    string outputFile = "output.bgr";
    
    int firstInputFile=-1;
    bool hasBeenReadInitialParameter=false;
    
    
    if (argc==1){
        showEnglishHelp(cerr);
        return 1;
    }
    
    for (int i=1; i<argc && !hasBeenReadInitialParameter; ++i){
        if (argv[i][0]=='-'){
            if (strcmp(argv[i],"-b")==0){
                mode='b';
            } else if (strcmp(argv[i],"-o")==0){
                if (argc>i+1){
                    outputFile = argv[i+1];
                    i++;
                }        
            } else if (strcmp(argv[i],"-t")==0){
                mode = 't';        
            } else {
                showEnglishHelp(cerr);
                return 1;
            }
        } else {
            hasBeenReadInitialParameter=true;
            firstInputFile=i;
        }
    }
        
    if (firstInputFile<0){
        showEnglishHelp(cerr);
        return 1;
    }
    
    
    // Similar to Language2
    
    Language language_base, language_tmp;
        
    language_base.load(argv[firstInputFile]);
    string id_base = language_base.getLanguageId();

    
    for (int i=firstInputFile+1; i<argc; ++i){
        language_tmp.load(argv[i]);
        language_base+=language_tmp;
    }

    language_base.sort();

    language_base.save(outputFile.c_str(), mode);        
    
    return 0;
}
