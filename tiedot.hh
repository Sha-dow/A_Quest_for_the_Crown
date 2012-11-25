//###################################################################
//                                                                 ##
// Hannu Ranta				                                       ##
//                                                                 ##
// Otsikkotiedosto, joka m‰‰rittelee kaikki                        ##
// ohjelmassa k‰ytett‰v‰t tietorakenteet.                          ##
//                                                                 ##
// ##################################################################


#ifndef TIEDOT_HH
#define TIEDOT_HH

//include-direktiivit
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

#include "sankari.hh"
#include "nuoli.hh"

//avataan standardinimiavaruus k‰yttˆˆn
using namespace std;

//Tila joko p‰‰ll‰ tai pois
enum Tila { OFF, ON };

//Maaston tyypit
enum Maasto { TASANKO, KUKKULA, VUORI, CAMELOT };

//Bonustyypit joita kartalla voi olla
enum Bonus { JOUSI, AMMUS, VOIMA, KUKKULABONUS, PUOLUSTUS, 
             TOIMINTAPISTE, NAKO, TYHJA };

//Ruudun n‰kyvyys
enum Nakyvyys { TUTKIMATON, MUISTINVARAINEN, NAKOKENTASSA };

enum Puoli { INNOCCIUS, TYRANNID, EISANKARIA };

//Sallitut liikkumissuunnat
const int SUUNNAT[] = { 1, 2, 3, 4, 6, 7, 8, 9 };

//Merkit joita kartalla voi olla pelin kuluessa
const char MERKIT[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                        '@', ' ', 'C', '^', '~', '.', 'I', 'T', '-', '/', '|',
                        '\\', '*' };

//Merkit joita kartta saa sis‰lt‰‰ alussa
const char ALKUMERKIT[] = { '@', 'C', '^', '~', '.', 'I', 'T', '*' };

//Komentotulkin sallimat merkkiyhdistelm‰t
const string LIIKU[] = { "lii", "liik", "liiku" };
const string LINNOITTAUDU[] = { "lin", "linn", "linno", "linnoi", "linnoit",
                                "linnoita" };
const string AMMU[] = { "am", "amm", "ammu" };
const string KARTTA[] = { "k", "ka", "kar", "kart", "kartt", "kartta" };
const string TIEDOT[] = { "t", "ti", "tie", "tied", "tiedo", "tiedot" };
const string ODOTA[] = { "o", "od", "odo", "odot", "odota" };
const string PARANNA[] = { "p", "pa", "par", "para", "paran", "parann",
                           "paranna" };
const string APUA[] = { "ap", "apu", "apua" };
const string HELP[] = { "h", "he", "hel", "help" };
const string LOPETA[] = { "lo", "lop", "lope", "lopet", "lopeta" };
const string QUIT[] = { "q", "qu", "qui", "quit" };

//Sankarien alkuarvot
const int PERUSVOIMA = 6;
const int PERUSNUOLET = 3;
const int PERUSNAKO = 1;
const int PERUSJOUSI = 2;
const int PERUSELAMA = 100;
const int PERUSBONUS = 0;
const int PERUSTOIMINTA = 3;

//Tietue, joka sis‰lt‰‰ kunkin kartan solun tiedot
struct KartanSolu
{
   bool kuninkaidenKruunu;
   Maasto maasto;
   vector<Bonus> bonus;
   Nakyvyys innoccius;
   Nakyvyys tyrannid;
   Puoli puoli;
   int jarjestys;
   bool nuoli;
};

//Tietue, jota k‰ytet‰‰n koordinaattien hallintaan
struct Suunta
{
   int dx;
   int dy;
};

const Suunta MUUTOS[] = {{0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1},
                         {-1,0}, {-1,-1}};

      
#endif
