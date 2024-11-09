/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file Language.cpp
 * @author Jorge García Gámiz <jorgegarciag@correo.ugr.es>
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

using namespace std;

const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";
const string Language::MAGIC_STRING_B="MP-LANGUAGE-B-1.0";

Language::Language(){
    _languageId = "unknown";
    _size = 0;
    _vectorBigramFreq = nullptr;
}

Language::Language(int numberBigrams){
    _languageId = "unknown";
    
    if (numberBigrams<0){
        throw std::out_of_range ("ERROR: numberBigrams must be positive or 0");
    } else {
        allocate(numberBigrams);
    }
}

Language::Language(const Language& orig){
    allocate(orig._size);
    copy(orig);
}

Language::~Language(){
    deallocate();
}

Language& Language::operator=(const Language& orig){  
    if (this != &orig){
        deallocate();
        allocate(orig._size);
        copy(orig);
    }
    
    return *this;
}

const std::string& Language::getLanguageId() const{
    return _languageId;
}

void Language::setLanguageId(const std::string& id){
    _languageId = id;
}

const BigramFreq& Language::at(int index) const{   
    if(index<0 || index>=_size){
        throw std::out_of_range ("ERROR: index must be between 0 and " + to_string(_size));
    } else{
        return (_vectorBigramFreq[index]);
    }
}

BigramFreq& Language::at(int index){   
    if(index<0 || index>=_size){
        throw std::out_of_range ("ERROR: index must be between 0 and " + to_string(_size));
    } else{
        return (_vectorBigramFreq[index]);
    }
}

int Language::getSize() const{
    return _size;
}

double Language::getDistance(const Language& otherLanguage) const{
   
    if (_size == 0){
        throw std::invalid_argument ("ERROR: implicit object is empty");
    } else {
        double suma=0;
        int rankingsOtherLanguage[_size];

        for (int i=0; i<_size; i++){
            int var = otherLanguage.findBigram(_vectorBigramFreq[i].getBigram());
            if (var!=-1){
                rankingsOtherLanguage[i] = var;
            } else {
                rankingsOtherLanguage[i] = _size;
            }
        }

        for (int i=0; i<_size; i++){            
            suma += abs(i-rankingsOtherLanguage[i]);
        }
                
        return (suma/(_size*_size));
    }
}

int Language::findBigram(const Bigram& bigram) const{
    
    bool found = false;
    int index=0;
    
    while (index<_size && !found) {
        if (_vectorBigramFreq[index].getBigram().isEqual(bigram)){
            found = true;
        } else {
            index++;
        }
    }
    
    if (!found){
        return -1;
    } else{
        return index;
    }
}

std::string Language::toString() const{   
    std::string cad = _languageId + '\n';
    cad += to_string(_size) + '\n';
    for (int i=0; i<_size; i++){
        cad += _vectorBigramFreq[i].toString()  + '\n';
    }
    
    return cad;
}

void Language::sort(){
    for (int i=0; i<_size; i++){
        for (int j=0; j<_size; j++){
            if (_vectorBigramFreq[i]>_vectorBigramFreq[j]){
                BigramFreq aux = _vectorBigramFreq[i];
                _vectorBigramFreq[i] = _vectorBigramFreq[j];
                _vectorBigramFreq[j] = aux;      
            }
        }
    }
} 

void Language::save(const char fileName[], char mode) const{   
    ofstream output;
    
    if (mode=='t'){
        // Open the file fileName in text mode
        output.open(fileName);
        
        if (output){
            output << MAGIC_STRING_T << endl;
            output << *this;

            if (!output){
                throw std::ios_base::failure ("ERROR: during the writing to " + string(fileName));
            }

            output.close();   
        } else {
            throw std::ios_base::failure ("ERROR: cannot open " + string(fileName));
        }     
    } else if (mode=='b'){        
        // Open the file fileName in binary mode
        output.open(fileName, ios::binary);
        
        if (output){
            output << MAGIC_STRING_B << endl;

          //  output << *this;
            
            output << _languageId << endl;
            output << _size << endl;
            
            for (int i=0; i<_size; ++i){
                _vectorBigramFreq[i].serialize(output);
            }
            
            if (!output){
                throw std::ios_base::failure ("ERROR: during the writing to " + string(fileName));
            }

            output.close();
        } else {
            throw std::ios_base::failure ("ERROR: cannot open " + string(fileName));
        }
    }
}

void Language::load(const char fileName[]){
        
    ifstream input;  
    input.open(fileName, ios::binary);

    if (input){
        string id, magic_string;
        int num_bigrams;
        bool is_binary = false;
        
        input >> magic_string;
        
        if ((magic_string != MAGIC_STRING_B) && (magic_string != MAGIC_STRING_T)){
            throw std::invalid_argument ("ERROR: invalid magic string");
        } else {
            if (magic_string == MAGIC_STRING_B){
                is_binary = true;
            }
            
            input >> id;
            input >> num_bigrams;
            input.get();
            
            deallocate();
            allocate(num_bigrams);
            
            _languageId = id;
            
            string bigram_str;
            int freq;

            for (int i=0; i<_size; i++){
                if (is_binary){
                    _vectorBigramFreq[i].deserialize(input);
                } else {
                    input >> _vectorBigramFreq[i];
                }
            }
            
            if (!input){
                throw std::ios_base::failure ("ERROR: during the reading from " + string(fileName));
            }
            
            input.close();
        }
    } else {
        throw std::ios_base::failure ("ERROR: cannot open: " + string(fileName));
    }
}

void Language::append(const BigramFreq& bigramFreq){
    int var = findBigram(bigramFreq.getBigram());
    
    if (var != -1){
        int freq = _vectorBigramFreq[var].getFrequency() + bigramFreq.getFrequency();
        _vectorBigramFreq[var].setFrequency(freq);
    } else {
        reallocate(_size+1);
        _vectorBigramFreq[_size-1] = bigramFreq;
    }
}

BigramFreq& Language::operator[](int index){
    assert(index>=0 && index<_size);
    return _vectorBigramFreq[index];
}

const BigramFreq& Language::operator[](int index) const{
    assert(index>=0 && index<_size);
    return _vectorBigramFreq[index];
}

Language& Language::operator+=(const Language& language){
    for (int i=0; i<language.getSize(); ++i){
        append(language.at(i));
    }
    
    return *this;
}

void Language::clear(){
    deallocate();
}


// ------------------------------------------------
// Private methods

void Language::allocate(int nElements){
    if (nElements>0){
        _size = nElements;
        _vectorBigramFreq = new BigramFreq[_size];
    } else {
        _size = 0;
        _vectorBigramFreq = nullptr;
    }
}
    
void Language::reallocate(int newSize){
    if (newSize!=_size && newSize>0){
        BigramFreq* aux = new BigramFreq[newSize];
        for (int i=0; i<_size && i<newSize; ++i){
            aux[i] = _vectorBigramFreq[i];
        }
        
        delete[] _vectorBigramFreq;
        _vectorBigramFreq = aux;
        _size = newSize;
    }
}

void Language::deallocate(){
    delete[] _vectorBigramFreq;
    _size = 0;
    _vectorBigramFreq =  nullptr;
}

void Language::copy(const Language& other){
    this-> _languageId = other._languageId;
    this-> _size = other._size;
    for (int i=0; i<_size; ++i){
        this-> _vectorBigramFreq[i] = other._vectorBigramFreq[i];
    }
}

// ------------------------------------------------
// External functions

std::ostream& operator<<(std::ostream &os, const Language& language){
    os << language.getLanguageId() << endl;
    os << language.getSize() << endl;
    for (int i=0; i<language.getSize(); i++){
        os << language.at(i) << endl;
    }
    
    return os;
}

std::istream& operator>>(std::istream &is, Language& language){
    language.clear();
    
    string languageId;
    int size;
    
    is >> languageId >> size;
    
    if(size<0){
        throw std::out_of_range ("ERROR: the number of bigrams read is negative");
    } else {
        language.setLanguageId(languageId);

        for (int i=0; i<size; i++){
            BigramFreq bgr_freq;
            is >> bgr_freq;
            language.at(i) = bgr_freq;
        }
    }
    
    return is;
}
