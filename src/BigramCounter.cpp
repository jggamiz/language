/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramCounter.cpp
 * @author Jorge García Gámiz <jorgegarciag@correo.ugr.es>
 *
 * Created on 12 February 2023, 11:00
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <cassert>

#include "Bigram.h"
#include "BigramFreq.h"
#include "Language.h"
#include "BigramCounter.h"

using namespace std;

/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars). 
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";


BigramCounter::BigramCounter(const std::string&  validChars){
    _validCharacters = validChars;
    allocate(validChars);
    
    for (int i=0; i<getSize(); ++i){
        for (int j=0; j<getSize(); ++j)
            _frequency[i][j]=0;
    }
}

BigramCounter::BigramCounter(const BigramCounter& orig){
    allocate(orig._validCharacters);
    copy(orig);
}

BigramCounter::~BigramCounter(){
    deallocate();
}

int BigramCounter::getSize() const{
    return _validCharacters.size();
}

int BigramCounter::getNumberActiveBigrams() const{
    int numActiveBigrams=0;
    for (int i=0; i<getSize(); ++i){
        for (int j=0; j<getSize(); ++j){
            if (_frequency[i][j]>0)
                numActiveBigrams++;
        }
    }
    
    return numActiveBigrams;
}

bool BigramCounter::setFrequency(const Bigram& bigram, int frequency){
    bool found=false;

    int f = _validCharacters.find(bigram.at(0));
    int c = _validCharacters.find(bigram.at(1));  
    
    if ((f!=std::string::npos) && (c!=std::string::npos)){
        _frequency[f][c]=frequency;
        found = true;
    }
    
    return found;
}

void BigramCounter::increaseFrequency(const Bigram& bigram, int frequency){
    
    int f = _validCharacters.find(bigram.at(0));
    int c = _validCharacters.find(bigram.at(1));  
    
    if ((f!=std::string::npos) && (c!=std::string::npos)){

        if (frequency==0)
            _frequency[f][c]++;
        else
            _frequency[f][c]+=frequency;
    } else {
        throw std::invalid_argument ("ERROR: given Bigram is not valid");
    }
}

BigramCounter& BigramCounter::operator=(const BigramCounter& orig){
    if (this != &orig){
        deallocate();
        allocate(orig._validCharacters);
        copy(orig);
    }
    
    return *this;
}

BigramCounter& BigramCounter::operator+=(const BigramCounter& rhs){
    for (int i=0; i<rhs.getSize(); ++i){
        for (int j=0; j<rhs.getSize(); ++j){
            this->increaseFrequency(Bigram(rhs._validCharacters.at(i),rhs._validCharacters.at(j)),rhs(i,j));
        }
    }
    
    return *this;
}

void BigramCounter::calculateFrequencies(const char* fileName){
    ifstream input;
    
    input.open(fileName);
    
    if (input){
        string word;
        char first_char, second_char;
    
        while (input>>word){
            int i=0;
            while (i<word.size()-1){
                first_char = tolower(word.at(i));
                if (isValidCharacter(first_char, _validCharacters)){
                    second_char = tolower(word.at(i+1));
                    if (isValidCharacter(second_char, _validCharacters)){
                        increaseFrequency(Bigram(first_char, second_char));
                    } else {
                        i++;
                    }
                }
                
                i++;
            }
        }
        
        input.close();
    } else {
        throw std::ios_base::failure ("ERROR: cannot open " + string(fileName));
    }
}

Language BigramCounter::toLanguage() const{
    int numBigrams = getNumberActiveBigrams();
    int contador=0;
    
    Language lang(numBigrams);
    BigramFreq bgr_freq;
    
    for (int i=0; i<getSize(); ++i){
        for (int j=0; j<getSize(); ++j){
            if (_frequency[i][j]>0){
                bgr_freq.setBigram(Bigram(_validCharacters.at(i), _validCharacters.at(j)));
                bgr_freq.setFrequency(_frequency[i][j]);
            
                lang.at(contador)=bgr_freq;
                contador++;
            }
        }
    }
    
    lang.sort();
    
    return lang;
}


// ------------------------------------------------
// Private methods

void BigramCounter::allocate(const string& validChars){
    int nElements = validChars.size();
    
    if (nElements>0){
        _frequency = new int*[nElements];
        for (int i=0; i<nElements; ++i)
            _frequency[i] = new int[nElements];
    } else {
        _frequency = nullptr;
    }
}

void BigramCounter::deallocate(){
    for(int i=0; i<getSize(); ++i)
        delete[] _frequency[i];
    delete[] _frequency;
}

void BigramCounter::copy(const BigramCounter& other){
    this->_validCharacters = other._validCharacters;
    for (int i=0; i<_validCharacters.size(); ++i){
        for (int j=0;j<_validCharacters.size(); ++j)
            this->_frequency[i][j] = other._frequency[i][j];
    }
}

const int& BigramCounter::operator()(int row, int column) const{
    assert(row>=0 && column>=0 && row<getSize() && column<getSize());
    return _frequency[row][column];
}

int& BigramCounter::operator()(int row, int column){
    assert(row>=0 && column>=0 && row<getSize() && column<getSize());
    return _frequency[row][column]; 
}
