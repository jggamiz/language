/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file LEARN.cpp
 * @author Jorge García Gámiz <jorgegarciag@correo.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>

#include<sstream>
#include <regex>
        
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
    outputStream << "LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> .... ]" << endl;
    outputStream << "           learn the model for the language languageId from the text files <text1.txt> <text2.txt> <text3.txt> ..." << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-l languageId: language identifier (unknown by default)" << endl;
    outputStream << "-o outputFilename: name of the output file (output.bgr by default)" << endl;
    outputStream << "<text1.txt> <text2.txt> <text3.txt> ....: names of the input files (at least one is mandatory)" << endl;
}

/**
 * This program learns a Language model from a set of input tex files (tex1.txt,
 * tex2.txt, ...
 * Running example:
 * > LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> ....]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

int main(int argc, char *argv[]) {
    char mode='t';
    string languageId = "unknown";
    string outputFile = "output.bgr";
    
    int firstInputFile=-1, nFilesToLearn;
    bool hasBeenReadInitialParameter=false;
    
    
    if (argc==1){
        showEnglishHelp(cerr);
        return 1;
    }
    
    for (int i=1; i<argc && !hasBeenReadInitialParameter; ++i){
        if (argv[i][0]=='-'){
            if (strcmp(argv[i],"-b")==0){
                mode='b';
            } else if (strcmp(argv[i],"-l")==0){
                if (argc>i+1){
                    languageId = argv[i+1];
                    i++;
                }
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
    
    nFilesToLearn = argc-firstInputFile;
    
    if (firstInputFile<0){
        showEnglishHelp(cerr);
        return 1;       
    }
    
    
    BigramCounter F;
    
    for (int i=firstInputFile; i<argc; ++i){
        F.calculateFrequencies(argv[i]);
    }
    
    Language language_base = F.toLanguage();
    language_base.setLanguageId(languageId);
    
    language_base.save(outputFile.c_str(), mode);
    

    return 0;
}

/* Ejecuta los test del TestReport.md
     * A la izquierda se muestra la salida del programa y a la derecha del operador se muestra lo que debería de salir
     * Se ha dividido la ejecución en 3 partes porque sino se llena la memoria y deja de ejecutar en algunos ordenadores (como el mío)
     * Para seleccionar la sección se deberá cambiar la variable test con los valores 1, 2 y 3.
     * Hay algunos tests que están comentados porque lanzan excepciones o porque no se tienen que probar manualmente
     * Para comprobar los test que deberían lanzar alguna excepción se deberán descomentar 
     *  
     * 
     * Habrá que añadir al programa los siguientes includes:
     * 
     * #include<sstream>
     * #include <regex>
     * 
     * Para poder ejecutarlo se deberá comentar entero alguno de los main creados (por ejemplo CLASSIFY), pegar el código a continuación y compilarlo. Se ejecuta sin argumentos o desde el botón de run.
     */
//int main (int argc, char *argv[]) {    
//    //Variables para facilitar los Tests
//    string operador=" :: ";
//    string validCharacters="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";
//    int test = 1;
//    
//    if (test==1) {
//    
//        //Tests del bigram
//        /*01*/ Bigram ab("ab");cout<<"1) "<<ab.toString()<<operador<<"ab"<<endl;
//        /*02*/ Bigram gg("__");cout<<"2) "<<gg.toString()<<operador<<"__"<<endl;
//        /*03*/ Bigram b1("abcd");cout<<"3) "<<b1.toString()<<operador<<"__"<<endl;
//        /*04*/ Bigram b2("");cout<<"4) "<<b2.toString()<<operador<<"__"<<endl;
//        /*05*/ Bigram b3('a', 'a');cout<<"5) "<<b3.toString()<<operador<<"aa"<<endl;
//        /*06*/ Bigram b4("ab");cout<<"6) "<<b4.at(0)<<operador<<"a"<<endl;
//        /*07*/ Bigram b5("ab");cout<<"7) "<<b5.at(1)<<operador<<"b"<<endl;
//        /*08*/ Bigram b6("ab");cout<<"8) "<<b6.getText()<<operador<<"ab"<<endl;
//
//
//
//        //Tests de BigramFreq
//        /*09*/ BigramFreq bf1; cout<<"9) "<<bf1.toString()<<operador<<"__ 0"<<endl;
//        /*10*/ BigramFreq bf2; cout<<"10) "<<bf2.toString()<<operador<<"__ 0"<<endl;
//        /*11*/ BigramFreq bf3; cout<<"11) "<<bf3.getFrequency()<<operador<<"0"<<endl;
//        /*12*/ BigramFreq bf4; cout<<"12) "<<bf4.getBigram().toString()<<operador<<"__"<<endl;
//
//        //Test de Language
//        /*13*/ Language lang1; cout<<"13) "<<lang1.getLanguageId()<<operador<<"unknown"<<endl;
//        /*14*/ Language lang2; cout<<"14) "<<lang2.getSize()<<operador<<"0"<<endl;
//        /*15*/ Language lang3; cout<<"15) "<<lang3.toString()<<operador<<"unknown 0 "<<endl;
//        /*16*/ Language lang4(2); cout<<"16) "<<lang4.getLanguageId()<<operador<<"unknown"<<endl;
//        /*17*/ Language lang5(2); cout<<"17) "<<lang5.getSize()<<operador<<"2"<<endl;
//        /*18*/ Language lang6(2); cout<<"18) "<<lang6.toString()<<operador<<"unknown 2 __ 0 __ 0"<<endl;
//        /*19*/ Language lang7; lang7.setLanguageId("english"); cout<<"19) "<<lang7.getLanguageId()<<operador<<"english"<<endl;
//
//
//        //Tests varios
//        /*20*/ Bigram b7("XY"); BigramFreq bf5; bf5.setBigram(b7); bf5.setFrequency(10); Language lang8; lang8.append(bf1);cout<<"20) "<<lang8.getSize()<<operador<<"1"<<endl;
//        /*21*/ Bigram b8("XY"); BigramFreq bf6; bf6.setBigram(b8); bf6.setFrequency(10); Language lang9; lang9.append(bf6);lang9.append(bf6);cout<<"21) "<<lang9.getSize()<<operador<<"1"<<endl;
//        /*22*/ Bigram b9("XY"); Bigram b10("ZZ"); BigramFreq bf7; bf7.setBigram(b9); bf7.setFrequency(10); Language lang10; lang10.append(bf3); bf7.setBigram(b10); lang10.append(bf7);cout<<"22) "<<lang10.getSize()<<operador<<"2"<<endl;
//        /*23*/ Bigram b11("XY"); Language lang11; cout<<"23) "<<lang11.findBigram(b11)<<operador<<"-1"<<endl;
//        /*24*/ Bigram b12("XY"); Bigram b13("ZZ"); BigramFreq bf8; bf8.setBigram(b12); bf8.setFrequency(10); Language lang12; lang12.append(bf8); bf8.setBigram(b9); lang12.append(bf8);cout<<"24) "<<lang12.findBigram(b12)<<operador<<"0"<<endl;
//
//        /*25*/ Bigram b14("XY"); Bigram b15("ZZ"); BigramFreq bf9; bf9.setBigram(b14); bf9.setFrequency(10); Language lang13; lang13.append(bf9); bf9.setBigram(b15); lang13.append(bf9); cout<<"25) "<<lang13.findBigram(b15)<<operador<<"1"<<endl;
//        /*26*/ Bigram b16("XY"); Bigram b17("ZZ");Bigram b22("YY"); BigramFreq bf10; bf10.setBigram(b16); bf10.setFrequency(10); Language lang14; lang14.append(bf10); bf10.setBigram(b17); lang14.append(bf10); cout<<"26) "<<lang14.findBigram(b22)<<operador<<"-1"<<endl;
//        /*27*/ Bigram b18("XY"); BigramFreq bf11; bf11.setBigram(b18); bf11.setFrequency(10); Language lang15; lang15.append(bf11); cout<<"27) "<<lang15.at(0).toString()<<operador<<"XY 10"<<endl;
//        /*28*/ Bigram b19("XY"); BigramFreq bf12; bf12.setBigram(b19); bf12.setFrequency(10); Language lang16; lang16.append(bf12);lang16.append(bf12); cout<<"28) "<<lang16.at(0).toString()<<operador<<"XY 20"<<endl;
//        /*29*/ Bigram b20("XY"); Bigram b21("ZZ"); BigramFreq bf13; bf13.setBigram(b20); bf13.setFrequency(10); Language lang17; lang17.append(bf13); bf13.setBigram(b21); lang17.append(bf13); cout<<"29) "<<lang17.at(0).toString()<<operador<<"XY 10"<<endl;
//
//        /*30*/ Bigram b23("XY"); Bigram b24("ZZ"); BigramFreq bf14; bf14.setBigram(b23); bf14.setFrequency(10); Language lang18; lang18.append(bf14); bf14.setBigram(b24); lang18.append(bf14); cout<<"30) "<<lang18.at(1).toString()<<operador<<"ZZ 10"<<endl;
//        /*31*/ Language l1; char c1='a'; BigramFreq bf15; Bigram b25(c1,c1); for(int i=1; i < 4; i++) { bf15.setBigram(b25); bf15.setFrequency(10*i); l1.append(bf15); b25.at(1)=c1+i; } l1.sort(); cout<<"31) "<<l1.toString()<<operador<<"unknown 3 ac 30 ab 20 aa 10"<<endl;
//
//    } else if (test==2) {
//         
//    
//        //Tests BigramCouter 
//        /*32*/ cout<<"32) Se debe comprobar manualmente"<<endl;  //BigramCounter bc;cout<<(bc._ValidCharacters==BigramCounter::DEFAULT_VALID_CHARACTERS)<<endl;
//        /*33*/ cout<<"33) Se debe comprobar manualmente"<<endl;  //const string validChars = "ABCD"; BigramCounter bc(validChars);bc._validCharacters==validChars
//        /*34*/ const string validChars1 = "ABCD"; BigramCounter bc4(validChars1);cout<<"34) "<<bc4.toLanguage().toString()<<operador<<"0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "<<endl;
//        /*35*/ const string validChars2 = "ABCD"; Bigram b26("AA"); BigramCounter bi1(validChars2); BigramCounter bc1(bi1);bc1.setFrequency(b26,10); cout<<"35) "<<bi1.toLanguage().toString()<<operador<<"0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "<<endl;
//        /*36*/ const string validChars3 = "ABCD"; Bigram b27("AA"); BigramCounter bi2(validChars3); BigramCounter bc2(bi2);bc2.setFrequency(b27,10); cout<<"36) "<<bc2.toLanguage().toString()<<operador<<"10 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "<<endl;
//        /*37*/ const string validChars4 = "ABCD"; Bigram b28("AA"); BigramCounter bi3(validChars4); BigramCounter bc3; bc3 = bi3; bc3.setFrequency(b28,10); cout<<"37) "<<bi3.toLanguage().toString()<<operador<<"0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "<<endl;
//
//        /*38*/ const string validChars5 = "ABCD"; Bigram b29("AA"); BigramCounter bi4(validChars5); BigramCounter bc5; bc5 = bi4; bc5.setFrequency(b28,10);cout<<"38) "<<bc5.toLanguage()<<operador<<"10 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "<<endl;
//        /*39*/ const string validChars6 = "ABCD"; Bigram b30("AA"); BigramCounter bi5(validChars6);cout<<"39) "<<bi5.getNumberActiveBigrams()<<operador<<"0"<<endl;
//        /*40*/ const string validChars7 = "ABCD"; BigramCounter bi6(validChars7); for(int i=0; i < bi6.getSize(); i++) { Bigram b31(validChars7[i],validChars7[i]); bi6.setFrequency(b31,10); }cout<<"40) "<<bi6.getNumberActiveBigrams()<<operador<<"4"<<endl;
//        /*41*/ const string validChars8 = "ABCD"; BigramCounter bi7(validChars8); int isInside1=0; for(int i=0; i < bi7.getSize(); i++) { Bigram b32(validChars8[i],validChars8[i]); if (bi7.setFrequency(b32,10)) isInside1++; }cout<<"41) "<<isInside1<<operador<<"4"<<endl;
//        /*42*/ const string validChars9 = "ABCD"; BigramCounter bi8(validChars9); int isInside2=0; for(int i=0; i < bi8.getSize(); i++) { Bigram b33(validChars9[i]+validChars9.size(),validChars9[i]+ validChars9.size()); if (bi8.setFrequency(b33,10)) isInside2++; }cout<<"42) "<<isInside2<<operador<<"0"<<endl;            
//
//        /*43*/ const string validChars10 = "ABCD"; BigramCounter bi9(validChars10); for(int i=0; i < bi9.getSize(); i++) { Bigram b34(validChars10[i],validChars10[i]); bi9.increaseFrequency(b34,5); } cout<<"43) "<<bi9.toLanguage()<<operador<<"5 0 0 0 0 5 0 0 0 0 5 0 0 0 0 5 "<<endl; 
//        /*44*/ const string validChars11 = "ABCD"; BigramCounter bi10(validChars11); for(int i=0; i < bi10.getSize(); i++) for(int j=0; j < bi10.getSize(); j++) { Bigram b35(validChars11[i],validChars11[j]); bi10.increaseFrequency(b35); } cout<<"44) "<<bi10.toLanguage()<<operador<<"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 "<<endl; 
//
//        //Tests operadores
//        /*45*/ /*DESCOMENTAR PARA EJECUTAR*/ //Bigram b36("ab");cout<<"45) "<<b36.at(20)<<operador<<"should THROW an exception std::out_of_range"<<endl;       
//        /*46*/ Bigram b37("ab"); b37.at(0) = 'd';cout<<"46) "<<b37.toString()<<operador<<"db"<<endl;  
//        /*47*/ Bigram b38("ab"); b38.at(1) = 'd';cout<<"47) "<<b38.toString()<<operador<<"ad"<<endl;  
//        /*48*/ char c2='a';cout<<"48) "<<boolalpha<<isValidCharacter(c2,validCharacters)<<operador<<"true"<<endl;  
//        /*49*/ char c3='@';cout<<"49) "<<isValidCharacter(c3,validCharacters)<<operador<<"false"<<endl;  
//
//        /*50*/ Bigram bigram1("ab");bigram1.toUpper();cout<<"50) "<<bigram1.toString()<<operador<<"AB"<<endl;
//        /*51*/ Bigram b39("XY");BigramFreq bf16;bf16.setBigram(b39); cout<<"51) "<<bf16.getBigram().toString()<<operador<<"XY"<<endl;
//        /*52*/ BigramFreq bf17; bf17.setFrequency(10); cout<<"52) "<<bf17.getFrequency()<<operador<<"10"<<endl;
//        /*53*/ /*DESCOMENTAR PARA EJECUTAR*/ //BigramFreq bf18;bf18.setFrequency(-10); cout<<"53) "<<"should THROW an exception std::out_of_range"<<endl;
//        /*54*/ const int DIM_VECTOR_BIGRAM_FREQ1 = 2000; Language lang19; int i1; int n1= DIM_VECTOR_BIGRAM_FREQ1; BigramFreq bf19; bf19.setFrequency(10); for ( i1 = 0; i1 < n1; i1++) { Bigram b40(char((i1/100)+'A'),char((i1 % 100)+'A')); bf19.setBigram(b40); lang19.append(bf19);} lang19.append(bf19);cout<<"54) "<<lang19.getSize()<<operador<<"2000"<<endl;
//
//        /*55*/ const int DIM_VECTOR_BIGRAM_FREQ2 = 2000; int i2; int n2= DIM_VECTOR_BIGRAM_FREQ2; Language lang20; BigramFreq bf20; bf20.setFrequency(10); for ( i2 = 0; i2 < n2; i2++) { Bigram b41(char((i2/100)+'A'),char((i2 % 100)+'A')); bf20.setBigram(b41); lang20.append(bf20); } Bigram b42(char((i2/100)+'A'),char((i2 % 100)+'A')); bf20.setBigram(b42); lang20.append(bf20);cout<<"55) "<<lang20.getSize()<<operador<<"2001"<<endl;
//        /*56*/ /*DESCOMENTAR PARA EJECUTAR*/ //Language lang21; BigramFreq bf21; bf21.setFrequency(10); for (int i = 0; i < 10; i++) { Bigram b43(char((i/100)+'A'),char((i % 100)+'A')); bf21.setBigram(b43); lang21.append(bf21);}cout<<"56) "<<lang21.at(-1)<<operador<<"should THROW an exception std::out_of_range"<<endl;
//        /*57*/ /*DESCOMENTAR PARA EJECUTAR*/ //Language lang22; BigramFreq bf22; bf22.setFrequency(10); for (int i = 0; i < 10; i++) { Bigram b44(char((i/100)+'A'),char((i % 100)+'A')); bf22.setBigram(b44); lang22.append(bf22);}cout<<"57) "<<lang22.at(10)<<operador<<"should THROW an exception std::out_of_range"<<endl;
//        /*58*/ Bigram b45("XY"); Bigram b46("ZZ"); BigramFreq bf23; bf23.setBigram(b45); bf23.setFrequency(10); Language lang23; lang23.append(bf23); lang23.append(bf23); bf23.setBigram(b46); lang23.append(bf23);cout<<"58) "<<lang23<<operador<<"unknown 2 XY 20 ZZ 10 "<<endl;
//        /*59*/ Bigram b47("aa"); Bigram b48("bb"); Bigram b49("cc"); Bigram b50("dd"); BigramFreq bf24; bf24.setFrequency(10); Language l2; Language l3; bf24.setBigram(b47); l2.append(bf24); bf24.setBigram(b48); l2.append(bf24); bf24.setBigram(b49); l3.append(bf24); bf24.setBigram(b50); l3.append(bf24); int initialSize1 = l2.getSize(); l2 += l3;cout<<"59) "<<l2.getSize()<<operador<<"4"<<endl;  
//
//        /*60*/ Bigram b51("aa"); Bigram b52("bb"); Bigram b53("cc"); Bigram b54("dd"); BigramFreq bf25; bf25.setFrequency(10); Language l4; Language l5; bf25.setBigram(b51); l4.append(bf25); l5.append(bf25); bf25.setBigram(b52); l4.append(bf25); l5.append(bf25); bf25.setBigram(b53); l4.append(bf25); l5.append(bf25); bf25.setBigram(b54); l4.append(bf25); l5.append(bf25); l4+=l5; int sum=0; for (int i= 0; i < l4.getSize(); i++) sum += l4.at(i).getFrequency();cout<<"60) "<<l4.getSize()*20<<operador<<"80"<<endl; 
//        /*61*/ Language l6; Language l7 ;l6.setLanguageId("Test1"); char c4='a'; BigramFreq bf26; Bigram b55(c4,c4); for(int i=0; i < 10; i++) { bf26.setBigram(b55); bf26.setFrequency(10-i); l6.append(bf26); b55.at(1)=c4+i; bf26.setBigram(b55); bf26.setFrequency(10-i); l6.append(bf26); } l6.sort(); const char* fileName1 = "tests/output/test_save1.bgr"; l6.save(fileName1); l7.load(fileName1); bool iguales1=true; iguales1 = l6.toString() == l7.toString();cout<<"61) "<<iguales1<<operador<<"true "<<endl;
//        /*62*/ Language l8; char c5='a'; BigramFreq bf27; Bigram b56(c5,c5); for(int i=1; i < 4; i++) { bf27.setBigram(b56); bf27.setFrequency(10); l8.append(bf27); b56.at(1)=c5+i; } l8.sort(); cout<<"62) "<<l8.toString()<<operador<<"unknown 3 aa 10 ab 10 ac 10 "<<endl;
//        /*63*/ Language l9; char c6='a'; BigramFreq bf28; Bigram b57(c6,c6); for(int i=1; i < 4; i++) { bf28.setBigram(b57); bf28.setFrequency(10*i); l9.append(bf28); b57.at(1)=c6+i; } bf28.setBigram(b57); l9.append(bf28); l9.sort(); cout<<"63) "<<l9.toString()<<operador<<"unknown 4 ac 30 ad 30 ab 20 aa 10 "<<endl;
//        /*64*/ Bigram b58("aa"); Bigram b59("bb"); Bigram b60("cc"); Bigram b61("dd"); BigramFreq bf29; bf29.setFrequency(10); Language l10; bf29.setBigram(b58); l10.append(bf29); bf29.setBigram(b59); l10.append(bf29); bf29.setBigram(b60); l10.append(bf29); bf29.setBigram(b61); l10.append(bf29); cout<<"64) "<<l10.getDistance(l10)<<operador<<"0.000000"<<endl;
//
//        /*65*/ Bigram b62("aa"); Bigram b63("bb"); Bigram b64("cc"); Bigram b65("dd"); BigramFreq bf30; bf30.setFrequency(10); Language l11; Language empty1; bf30.setBigram(b62); l11.append(bf30); bf30.setBigram(b63); l11.append(bf30); bf30.setBigram(b64); l11.append(bf30); bf30.setBigram(b65); l11.append(bf30);cout<<"65) "<<l11.getDistance(empty1)<<operador<<"0.625000"<<endl;
//        /*66*/ Bigram b66("aa"); Bigram b67("bb"); Bigram b68("cc"); Bigram b69("dd"); BigramFreq bf31; bf31.setFrequency(10); Language l12; Language l13; bf31.setBigram(b66); l12.append(bf31); bf31.setBigram(b67); l12.append(bf31); bf31.setBigram(b68); l12.append(bf31); bf31.setBigram(b69); l12.append(bf31); bf31.setBigram(b69); l13.append(bf31); bf31.setBigram(b68); l13.append(bf31); bf31.setBigram(b67); l13.append(bf31); bf31.setBigram(b66);l13.append(bf31);cout<<"66) "<< l12.getDistance(l13)<<operador<<"0.500000"<<endl;
//        /*67*/ Language l14; char c7='a'; BigramFreq bf32; Bigram b70(c7,c7); for(int i=1; i < 4; i++) { bf32.setBigram(b70); bf32.setFrequency(10); l14.append(bf32); b70.at(1)=c7+i; } Language lc1; lc1=l14; lc1.at(0).setFrequency(20);cout<<"67) "<<lc1<<operador<<"unknown 3 aa 20 ab 10 ac 10 "<<endl;  
//        /*68*/ Language l15; char c8='a'; BigramFreq bf33; Bigram b71(c8,c8); for(int i=1; i < 4; i++) { bf33.setBigram(b71); bf33.setFrequency(10); l15.append(bf33); b71.at(1)=c8+i; } Language lc2; lc2=l15; lc2.at(0).setFrequency(20);cout<<"68) "<<l15<<operador<<"unknown 3 aa 10 ab 10 ac 10 "<<endl;
//        /*69*/ Language l16; char c9='a'; BigramFreq bf34; Bigram b72(c9,c9); for(int i=1; i < 4; i++) { bf34.setBigram(b72); bf34.setFrequency(10); l16.append(bf34); b72.at(1)=c9+i; } Language lc3(l16); lc3.at(0).setFrequency(20);cout<<"69) "<<l16<<operador<<"unknown 3 aa 10 ab 10 ac 10 "<<endl;
//
//        /*70*/ Language l17; char c10='a'; BigramFreq bf35; Bigram b73(c10,c10); for(int i=1; i < 4; i++) { bf35.setBigram(b73); bf35.setFrequency(10); l17.append(bf35); b73.at(1)=c10+i; } Language lc4(l17); lc4.at(0).setFrequency(20);cout<<"70) "<<lc4<<operador<<"unknown 3 aa 20 ab 10 ac 10 "<<endl;
//        /*71*/ const string validChars12 = "ABCD"; BigramCounter bi11(validChars12); for(int i=0; i < bi11.getSize(); i++) for(int j=0; j < bi11.getSize(); j++) { Bigram b74(validChars12[i],validChars12[j]); bi11.setFrequency(b74,3); } bi11 += bi11; cout<<"71) "<<bi11.toLanguage()<<operador<<"6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 "<<endl;
//        /*72*/ // NO SE PUEDE PASAR // const char nfE1[50] = "../Books/test_EN.txt"; const char nfS1[50] = "../Books/test_EN.bgr"; BigramCounter bi12; bi12.calculateFrequencies(nfE1); Language l18; l18.load(nfS1); string s1; int posi1; int posj1; int freq1; int freql1; bool iguales2 = true; if (bi12.getNumberActiveBigrams() != l18.getSize()) iguales2= false; for(int i=0; i < l18.getSize() && iguales2; i++){ s1 = l18.at(i).getBigram().toString(); posi1 = validCharacters.find(s1[0]); posj1 = validCharacters.find(s1[1]); freql1 = l18.at(i).getFrequency(); freq1 = bi12._frequency[posi1][posj1]; if (freq1 != freql1) iguales2 = false; }cout<<"72) "<<iguales2<<operador<<"true"<<endl;
//        /*73*/ // NO SE PUEDE PASAR // const char nfE2[50] = "../Books/test_ES.txt"; const char nfS2[50] = "../Books/test_ES.bgr"; BigramCounter bi13; bi13.calculateFrequencies(nfE2); Language l19; l19.load(nfS2); string s2; int posi2; int posj2; int freq;2 int freql2; bool iguales3 = true; if (bi13.getNumberActiveBigrams() != l19.getSize()) iguales3= false; for(int i=0; i < l19.getSize() && iguales3; i++){ s2 = l19.at(i).getBigram().toString(); posi2 = validCharacters.find(s2[0]); posj2 = validCharacters.find(s2[1]); freql2 = l19.at(i).getFrequency(); freq2 = bi13._frequency[posi2][posj2]; if (freq2 != freql2) iguales3 = false; }cout<<"73) "<<iguales3<<operador<<"true"<<endl;
//        /*74*/ // NO SE PUEDE PASAR // const char nfE3[50] = "../Books/test_EN.txt"; const char nfS3[50] = "../Books/test_EN.bgr"; BigramCounter bi14; bi14.calculateFrequencies(nfE3); Language lr1; Language lo1; lr1.load(nfS); lo1 = bi14.toLanguage(); bool iguales4 = true; if (lr1.getSize() != lo1.getSize()) iguales4= false; for(int i=0; i < lo1.getSize() && iguales4; i++){ if ((lr1.at(i).getBigram().toString() != lo1.at(i).getBigram().toString()) || (lr1.at(i).getFrequency() != lo1.at(i).getFrequency())) iguales4 =false; }cout<<"74) "<<iguales4<<operador<<"true"<<endl;
//     
//
//        /*75*/ // NO SE PUEDE PASAR // const char nfS4[50] = "../Books/test_EN.bgr"; BigramCounter bi15; bool iguales5 = true; string s3; int posi2; int posj2; int freq2; int freql2; Language lr2; lr2.load(nfS); bi15.fromLanguage(lr2); if (bi15.getNumberActiveBigrams() != lr2.getSize()) iguales4= false; for(int i=0; i < lr2.getSize() && iguales4; i++){ s3 = lr2.at(i).getBigram().toString(); posi2 = bi15._validCharacters.find(s[0]); posj = bi15._validCharacters.find(s3[1]); freql2 = lr2.at(i).getFrequency(); freq2 = bi15._frequency[posi2][posj2]; if (freq2 != freql2) iguales4 = false; }cout<<"75) "<<iguales4<<operador<<"true"<<endl;
//        /*76*/ // NO SE PUEDE PASAR // const string validChars13 = "ABCD"; Bigram b75("AD"); BigramCounter bi16(validChars13); bi16.setFrequency(b75,10);cout<<"76) "<<bi16(validChars13.find('A') ,validChars13.find('D'))<<operador<<"10"<<endl;
//
//        /*77*/ Bigram b76("AA"); Bigram b77("FF"); BigramFreq bf36; BigramFreq bf37; bf36.setBigram(b76); bf37.setBigram(b77); bf36.setFrequency(10); bf37.setFrequency(20);cout<<"77) "<<(bf37>bf36)<<operador<<"true"<<endl;
//        /*78*/ Bigram b78("AA"); Bigram b79("FF"); BigramFreq bf38; BigramFreq bf39; bf38.setBigram(b78); bf39.setBigram(b79); bf38.setFrequency(10); bf39.setFrequency(10);cout<<"78) "<<(bf38>bf39)<<operador<<"true"<<endl;
//        /*79*/ Bigram b80("AA"); BigramFreq bf40; BigramFreq bf41; bf40.setBigram(b80); bf41.setBigram(b80); bf40.setFrequency(10); bf41.setFrequency(10);cout<<"79) "<<(bf40==bf41)<<operador<<"true"<<endl;
//
//    
//    } else if(test==3) {
//
//    
//        /*80*/ Bigram b81; std::string sin1="aa"; std::istringstream ssin1(sin1); ssin1 >> b81;cout<<"80) "<<b81.toString()<<operador<<"aa"<<endl;
//        /*81*/ BigramFreq bfr1; std::string sin2="aa 10"; istringstream ssin2(sin2); ssin2 >> bfr1; cout<<"81) "<<bfr1.toString()<<operador<<"aa 10"<<endl;
//        /*82*/ // Language l18; std::string sin3="unknown 3 aa 10 ab 10 ac 10 "; istringstream ssin3(sin3); ssin3 >> l18;cout<<"82) "<<l18<<operador<<"unknown 3 aa 10 ab 10 ac 10 "<<endl;
//        /*83*/ std::string sout1; ostringstream ssout1; Bigram b82("aa"); ssout1 << b82; sout1 = ssout1.str();cout<<"83) "<<sout1<<operador<<"aa"<<endl;
//        /*84*/ std::string sout2; ostringstream ssout2; Bigram b83("aa"); BigramFreq bf42; bf42.setBigram(b83); bf42.setFrequency(10); ssout2 << bf42; sout2 = ssout2.str();cout<<"84) "<<sout2<<operador<<"aa 10"<<endl;
//
//        /*85*/ std::string sout3; ostringstream ssout3; Bigram b84("XY"); Bigram b85("ZZ"); BigramFreq bf43; bf43.setBigram(b84); bf43.setFrequency(10); Language lang24; lang24.append(bf43); lang24.append(bf43); bf43.setBigram(b85); lang24.append(bf43); std::streambuf *old1 = std::cout.rdbuf(ssout3.rdbuf()); ssout3 << lang24; sout3 = ssout3.str(); sout3 = std::regex_replace(sout3, std::regex("\n"), " "); std::cout.rdbuf(old1);cout<<"85) "<<sout3<<operador<<"unknown 2 XY 20 ZZ 10 "<<endl;
//        /*86*/ Bigram b86("XY"); BigramFreq bf44; bf44.setBigram(b86); bf44.setFrequency(10); Language lang25; lang25.append(bf44);cout<<"86) "<<lang25[0]<<operador<<"XY 10"<<endl;
//        /*87*/ Bigram b87("XY"); Bigram b88("ZZ"); BigramFreq bf45; bf45.setBigram(b87); bf45.setFrequency(10); Language lang26; lang26.append(bf45); bf45.setBigram(b88); lang26.append(bf45);cout<<"87) "<<lang26[0]<<operador<<"XY 10"<<endl;
//        /*88*/ Language l27; Language l28; l27.setLanguageId("Test1"); char c11='a'; BigramFreq bf46; Bigram b89(c11,c11); for(int i=0; i < 10; i++) { bf46.setBigram(b89); bf46.setFrequency(10-i); l27.append(bf46); b89.at(1)=c11+i; bf46.setBigram(b89); bf46.setFrequency(10-i); l27.append(bf46); } l27.sort(); const char* fileName2 = "tests/output/test_save1.bgr"; l27.save(fileName2,'t'); l28.load(fileName2); bool iguales6=true; iguales6 = (l27.toString() == l28.toString());cout<<"88) "<<boolalpha<<iguales6<<operador<<"true"<<endl;
//        /*89*/ Language l29; Language l30; l29.setLanguageId("Testb"); char c12='a'; BigramFreq bf47; Bigram b90(c12,c12); for(int i=0; i < 10; i++) { bf47.setBigram(b90); bf47.setFrequency(10-i); l29.append(bf47); b90.at(1)=c12+i; bf47.setBigram(b90); bf47.setFrequency(10-i); l29.append(bf47); } l29.sort(); const char* fileName3 = "tests/output/testb_save.bgr"; l29.save(fileName3,'b'); l30.load(fileName3); bool iguales7=true; iguales7 = (l29.toString() == l30.toString());cout<<"89) "<<iguales7<<operador<<"true"<<endl;
//
//    }
//    
//    
//    return 0;
//}