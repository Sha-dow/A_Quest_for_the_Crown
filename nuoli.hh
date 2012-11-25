//############################################
//                                            
//  Hannu Ranta				                  
//                                            
//  Nuoli-luokan otsikkotiedosto              
//                                            
//############################################

#ifndef NUOLI_HH
#define NUOLI_HH

#include <iostream>
#include <vector>

#include "tiedot.hh"

using namespace std;

// Luokka: Nuoli 
// K‰yttˆ: Pelin nuolien kuvaaminen

class Nuoli
{   
 public:
   
   // Funktio:    Nuoli()
   // Parametrit: -
   // Toiminta:   Rakentaja: Nuoli-luokan oletusrakentaja
  
   Nuoli();
   
   // Funktio:    paivitaTiedot()
   // Parametrit: int maaliX
   //             int maaliY
   //             int sijaintiX
   //             int sijaintiY
   //             int voima
   //             char merkki
   // Toiminta:   P‰ivitt‰‰ nuolen sis‰iset tiedot oikeiksi 
   //             parametreina annettujen tietojen mukaan.
  
   void paivitaTiedot(int maaliX, int maaliY, int sijaintiX, int sijaintiY,
                      int voima, char merkki);
   
   // Funktio:    talletaReitti()
   // Parametrit: int xKoord
   //             int yKoord
   // Toiminta:   Tallettaa nuolen reittivektoriin kaikki 
   //             x- ja y-koordinaatit joihin nuoli liikkuu
   
   void talletaReitti(int xKoord, int yKoord);
   
   // Funktio:    koordinaatit()
   // Parametrit: int koordX
   //             int koordY
   //             bool maali
   // Toiminta:   Palauttaa nuolen sis‰isest‰ tietorakenteesta
   //             seuraavat koordinaatit ja tiedon ollaanko
   //             maalissa
   
   void koordinaatit(int& koordX, int& koordY, bool& maali);
   
   // Funktio:    paivitaPaikka()
   // Parametrit: int koordX
   //             int koordY
   // Toiminta:   P‰ivitt‰‰ nuolen koordinaatit oikeiksi
   
   void paivitaPaikka(int koordX, int koordY);
   
   // Funktio:    piirretaanko()
   // Parametrit: -
   // Toiminta:   Palauttaa tiedon siit‰ onko nuoli
   //             viel‰ olemassa vai ei
   
   bool piirretaanko();
   
   // Funktio:    paivitaPiirto()
   // Parametrit: bool arvo
   // Toiminta:   P‰ivitt‰‰ nuolen olemassaolotiedon
   //             nuoleen
   
   void paivitaPiirto(bool arvo);
   
   // Funktio:    palautaPaikka()
   // Parametrit: int koordX
   //             int koordY
   // Toiminta:   Palauttaa nuolen tuoreimman paikan
   
   void palautaPaikka(int& koordX, int& koordY);
   
   // Funktio:    piirraMerkki()
   // Parametrit: -
   // Toiminta:   Piirt‰‰ oikean merkin nuolelle
   
   void piirraMerkki();
   
   // Funktio:    palautaVoima()
   // Parametrit: -
   // Toiminta:   Palauttaa nuolen voimabonuksen
   
   int palautaVoima();
   
 private:

   // luokan sis‰iset tiedot
   int maaliX_;
   int maaliY_;
   char merkki_;
   int paikkaX_;
   int paikkaY_;
   int voimabonus_;
   bool piirretaan_;
   
   struct Suunnat 
   {
      int dx;
      int dy;
   };
      
   vector<Suunnat> koordinaatit_;
};

#endif
