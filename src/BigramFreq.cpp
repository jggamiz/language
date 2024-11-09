/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * File:   BigramFreq.cpp
 * Author: Jorge García Gámiz
 * 
 * Created on 2 de marzo de 2023, 10:51
 */


#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

#include "Bigram.h"
#include "BigramFreq.h"

using namespace std;

BigramFreq::BigramFreq(){
    
    for (int i=0; i<2; i++){
        _bigram.at(i) = '_';
    }
    _bigram.at(2) = '\0';
    
    _frequency = 0;
}

const Bigram& BigramFreq::getBigram() const{
    return _bigram;
}

int BigramFreq::getFrequency() const{
    return _frequency;
}

void BigramFreq::setBigram(const Bigram& bigram){
    _bigram = bigram;
}

void BigramFreq::setFrequency(int frequency){
    if (frequency < 0)
        throw std::out_of_range ("ERROR: frequency must be positive");
    else
        _frequency = frequency;
}

std::string BigramFreq::toString() const{
    string cad = _bigram.toString() + " " + to_string(_frequency);
    return cad;
}

void BigramFreq::serialize(std::ostream& outputStream){
    this->_bigram.serialize(outputStream);
    outputStream.write(reinterpret_cast<const char*>(&_frequency), sizeof(_frequency));
}

void BigramFreq::deserialize(std::istream& inputSstream){
    this->_bigram.deserialize(inputSstream);
    inputSstream.read(reinterpret_cast<char*>(&_frequency), sizeof(_frequency));
}

// ------------------------------------------------
// External functions

std::ostream& operator<<(std::ostream &os, const BigramFreq& bigramFreq){
    os << bigramFreq.getBigram() << " " << bigramFreq.getFrequency();
    return os;
}

std::istream& operator>>(std::istream &is, BigramFreq& bigramFreq){
    Bigram bigram;
    int freq;

    is >> bigram >> freq;
        
    bigramFreq.setBigram(bigram);
    bigramFreq.setFrequency(freq);
    
    return is;
}

bool operator>(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    bool greater=false;
    
    if (bigramFreq1.getFrequency() > bigramFreq2.getFrequency()){
        greater=true;
    } else if ((bigramFreq1.getFrequency() == bigramFreq2.getFrequency()) &&
               (bigramFreq1.getBigram().getText() < bigramFreq2.getBigram().getText())){
        greater=true;
    }
    
    return greater;
}

bool operator<(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    bool lower=false;
    
    if (bigramFreq1.getFrequency() < bigramFreq2.getFrequency()){
        lower=true;
    } else if ((bigramFreq1.getFrequency() == bigramFreq2.getFrequency()) &&
               (bigramFreq1.getBigram().getText() > bigramFreq2.getBigram().getText())){
        lower=true;
    }
    
    return lower;
}

bool operator==(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    bool areEqual=false;
    
    if ((bigramFreq1.getBigram().isEqual(bigramFreq2.getBigram())) && 
        (bigramFreq1.getFrequency()==bigramFreq2.getFrequency())){
        areEqual = true;
    }
        
    return areEqual;
}

bool operator!=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    return !(bigramFreq1 == bigramFreq2);
}

bool operator<=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    return !(bigramFreq1 > bigramFreq2);
}

bool operator>=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    return !(bigramFreq1 < bigramFreq2);
}
