/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * File:   Bigram.cpp
 * Author: Jorge García Gámiz
 * 
 * Created on 2 de marzo de 2023, 10:51
 */

#include <iostream>
#include <string>
#include <cstring>

#include "Bigram.h"

using namespace std;

Bigram::Bigram(const std::string& text){
    if (text.size() == 2){ 
      strcpy(_text, text.c_str());
    } else{
        strcpy(_text, "__");
    }
}

Bigram::Bigram(char first, char second){
    _text[0] = first;
    _text[1] = second;
    _text[2] = '\0';
}

Bigram::Bigram(const char text[]){
    
    // We have to register the number of elements in the c-string
    int n_elements = strlen(text); 
   
    if (n_elements == 2){
        strcpy(_text, text);
    } else{
        strcpy(_text, "__");
    }
}

std::string Bigram::getText() const{
    string cad;
    for (int i=0; i<2; i++){
        cad += string (1,_text[i]);
    }
    
    return cad;
}

std::string Bigram::toString() const{
    string cad;
    for (int i=0; i<2; i++){
        cad += string (1,_text[i]);
    }
    
    return cad;
}

const char& Bigram::at(int index) const{
    if(index<0 || index>2){
        throw std::out_of_range ("ERROR: index must be between 0 and 2");
    } else{
        return (_text[index]);
    }
}

char& Bigram::at(int index){
    if(index<0 || index>2){
        throw std::out_of_range ("ERROR: index must be between 0 and 2");
    } else{
        return (_text[index]);
    }
}

void Bigram::toUpper(){ 
    _text[0] = toupper(_text[0]);
    _text[1] = toupper(_text[1]);
 }

bool Bigram::isEqual(const Bigram& bigram) const{
    bool isTheSame = true;
    
    for (int i=0; i<2 && isTheSame; i++){
        if (_text[i]!=bigram.at(i)){
            isTheSame = false;
        }
    }
    
    return isTheSame;
}

void Bigram::serialize(std::ostream& outputStream){
    outputStream.write(reinterpret_cast<const char*>(_text), sizeof(char)*2);
}

void Bigram::deserialize(std::istream& inputStream){
    inputStream.read(reinterpret_cast<char*>(_text),sizeof(char)*2);
    _text[2] = '\0';
}

// ------------------------------------------------
// External functions

bool isValidCharacter(char character, const std::string& validCharacters){
    return validCharacters.find(character)!=string::npos;
}

std::ostream& operator<<(std::ostream &os, const Bigram& bigram){
    os << bigram.at(0) << bigram.at(1);
    return os;
}

std::istream& operator>>(std::istream &is, Bigram& bigram){
    char first, second;
    is >> first >> second;
    
    bigram = Bigram(first, second);
    
    return is;
}
