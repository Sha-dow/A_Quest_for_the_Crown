//###################################################################
//                                                                 ##
// Hannu Ranta				                                       ##
//                                                                 ##
// Apufunktiot-rajapinnan otsikkotiedosto						   ##
//                                                                 ##
// ##################################################################


#ifndef APUFUNKTIOT_HH
#define APUFUNKTIOT_HH

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

#include "tiedot.hh"

using namespace std;

void tulostaTekstit();

void tulostaOhje();

int arpa(int ala, int yla);

template <class tietoA, class TietoB>
bool muutaTyyppi(const tietoA & lahde, TietoB * kohde);

bool loytyykoOhje(int maara, char **vivut);

bool onkoDupplikaattivipuja(vector<string>& parametrit);

bool tarkistaVivut(vector<string>& parametrit);

bool tarkistaParametrit(int maara, char **vivut, int& siemenluku,
                        string& kartta, Tila& debug);

#endif
