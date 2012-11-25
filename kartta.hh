//#################################################################
//                                                                 
// Hannu Ranta				                                       
//                                                                 
// Kartta-rajapinnan otsikkotiedosto, joka m‰‰rittelee             
// kartan oikeellisuuden tarkistamiseen ja kartan alustamiseen     
// liittyv‰t toiminnot                                             
//                                                                 
// ################################################################


#ifndef KARTTA_HH
#define KARTTA_HH

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

#include "tiedot.hh"
#include "sankari.hh"

using namespace std;

//Tarkistaa saako karttatiedoston avattua ja jos saa niin avaa sen 
//parametrina annettuun virtaan
bool saakoAvattua(string& kartta, ifstream& virta);

//Tarkistaa karttatiedoston mitat ja ensimm‰isen rivin oikeellisuuden
bool tarkistaMitat(string& rivi, unsigned int& leveys, 
                   unsigned int& korkeus);

//Tulkitsee kartan merkit ja laskee kartalla olevat
//camelotit, sankarin ja kruunu(n/t). 
bool tulkitseMerkit(string& temp, int& kruunu, int& camelot,
                    int& sankarit_innoccius, int& sankarit_tyrannid);

//Tarkistaa kartan oikeellisuuden
bool tarkistaKartta(string& kartta, unsigned int& leveys, 
                    unsigned int& korkeus);

//Alustaa lauta-vektorin karttatiedoston tietojen mukaan
void alustaLauta(vector<vector<KartanSolu> >& lauta, string& kartta,
                 vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                 Tila debug);
#endif
