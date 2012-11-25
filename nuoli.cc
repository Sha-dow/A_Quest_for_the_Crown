//#############################################
//                                             
//  Hannu Ranta 			                   
//                                             
//  Nuoli-luokan toteutus                      
//                                               
//#############################################

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include "nuoli.hh"
#include "tiedot.hh"

using namespace std;

//Oletusrakentaja Nuolelle

Nuoli::Nuoli(): maaliX_(0), maaliY_(0), merkki_('-'), paikkaX_(0),
                paikkaY_(0), voimabonus_(0)
{
}

//Funktio joka päivittää parametreina syötetyt tiedot
//nuolen sisäisiin tietorakenteisiin

void Nuoli::paivitaTiedot(int maaliX, int maaliY, int sijaintiX, 
                          int sijaintiY, int voima, char merkki)
{
   maaliX_ = maaliX;
   maaliY_ = maaliY;
   paikkaX_ = sijaintiX;
   paikkaY_ = sijaintiY;
   merkki_ = merkki;
   voimabonus_ = voima;
   piirretaan_ = true;
}

//Funktio joka tallettaa nuolen koordinaattivektoriin
//kaikkien nuolen reitille osuvien ruutujen koordinaatit.
//Nämä koordinaatit annetaan parametrina.

void Nuoli::talletaReitti(int xKoord, int yKoord)
{
   Suunnat temp = {0,0};
   
   temp.dx = xKoord;
   temp.dy = yKoord;
   
   koordinaatit_.push_back(temp);
}

//Palauttaa nuolen seuraavan sijainnin ja tiedon siitä ollaanko maalissa

void Nuoli::koordinaatit(int& koordX, int& koordY, bool& maali)
{
   if (koordinaatit_.size() == 0)
   {
      maali = true;
   }
   
   else
   {
      Suunnat suunta = {0,0};
      suunta = koordinaatit_.at(0);
      koordX = suunta.dx;
      koordY = suunta.dy;
      koordinaatit_.erase(koordinaatit_.begin());
   }
}

//Päivittää nuolen paikan nuolen omiin muuttujiin

void Nuoli::paivitaPaikka(int koordX, int koordY)
{
   paikkaX_ = koordX;
   paikkaY_ = koordY;
}

//Palauttaa totuusarvon piirretäänkö 
//nuoli vai ei

bool Nuoli::piirretaanko()
{
   return piirretaan_;
}

//Muuttaa nuolen piirtomuuttujan arvoa

void Nuoli::paivitaPiirto(bool arvo)
{
   piirretaan_ = arvo;
}

//Palauttaa nuolen tämänhetkisen paikan

void Nuoli::palautaPaikka(int& koordX, int& koordY)
{
   koordX = paikkaX_;
   koordY = paikkaY_;
}

//Tulostaa nuolen piirtomerkin kartalle

void Nuoli::piirraMerkki()
{
   cout << merkki_ << " ";
}

//Palauttaa voimabonuksen arvon

int Nuoli::palautaVoima()
{
   return voimabonus_;
}

                     
