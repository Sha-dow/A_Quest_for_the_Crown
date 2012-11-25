//##############################################
//                                            ##
//  Hannu Ranta 			                  ##
//                                            ##
//  Sankari-luokan otsikkotiedosto            ##
//                                            ##
//##############################################

#ifndef SANKARI_HH
#define SANKARI_HH

#include <iostream>
#include <vector>

#include "tiedot.hh"

using namespace std;

// Luokka: Sankari 
// K�ytt�: Pelin sankarien kuvaaminen
class Sankari 
{   
 public:
   
   // Funktio:    Sankari()
   // Parametrit: -
   // Toiminta:   Rakentaja Sankari-luokan oletusrakentaja
   Sankari();
   
   // Funktio:    tulostaTiedot()
   // Parametrit: ostream& virta
   // Toiminta:   Tulostaa sankarin tiedot annettuun virtaan
   void tulostaTiedot(ostream& virta, bool maella);
   
   // Funktio:    paivitaKoordinaatit()
   // Parametrit: int paikkaX 
   //             int paikkaY
   // Toiminta:   P�ivitt�� sankarin sis�iseen tietorakenteeseen
   //             oikeat koordinaatit.
   void paivitaKoordinaatit(int paikkaX, int paikkaY);
   
   // Funktio:    palautaNakosade()
   // Parametrit: -
   // Toiminta:   Palauttaa sankarin n�k�s�teen
   int palautaNakosade();
   
   // Funktio:    palautaElama()
   // Parametrit: -
   // Toiminta:   Palauttaa sankarin el�m�pisteet
   int palautaElama();
   
   // Funktio:    vahennaElamaa()
   // Parametrit: int maara
   // Toiminta:   V�hent�� sankarin el�m�pisteit� 
   //             parametrina sy�tetyn m��r�n
   void vahennaElamaa(int maara);
   
   // Funktio:    palautaToimintapisteet()
   // Parametrit: -
   // Toiminta:   Palauttaa sankarin toimintapisteet
   int palautaToimintapisteet();
   
   // Funktio:    muutaToimintapisteita()
   // Parametrit: int maara
   // Toiminta:   Muuttaa toimintapisteita parametrina annetun
   //             m��r�n verran
   void muutaToimintapisteita(int maara);
   
   // Funktio:    nollaaToimintapisteet()
   // Parametrit: -
   // Toiminta:   Palauttaa toimintapisteet oletukseen
   void nollaaToimintapisteet();
   
   // Funktio:    kruunuLoytyi()
   // Parametrit: -
   // Toiminta:   V�litt�� sankarille tiedon kruunun l�ytymisest�
   //             jotta sankari voi poimia sen talteen
   void kruunuLoytyi();
   
   // Funktio:    palautaX()
   // Parametrit: -
   // Toiminta:   Palauttaa sankarin t�m�nhetkisen x-koordinaatin
   int palautaX();
   
   // Funktio:    palautaY()
   // Parametrit: -
   // Toiminta:   Palauttaa sankarin t�m�nhetkisen y-koordinaatin
   int palautaY();
   
   // Funktio:    onkoKruunu()
   // Parametrit: -
   // Toiminta:   palauttaa tiedon kantaako sankari kruunua vai ei
   bool onkoKruunu();
   
   // Funktio:    paranna()
   // Parametrit: -
   // Toiminta:   Parantaa sankaria
   void paranna();
   
   // Funktio:    palautaAmmukset()
   // Parametrit: -
   // Toiminta:   Palauttaa sankarin ammusten m��r�n
   int palautaAmmukset();
   
   // Funktio:    palautaTarkkuus()
   // Parametrit: -
   // Toiminta:   Palauttaa jousen tarkkuuden
   int palautaTarkkuus();
   
   // Funktio:    palautaVoima()
   // Parametrit: -
   // Toiminta:   Palauttaa voimabonuksen
   int palautaVoima();
   
   // Funktio:    palautaKukkula()
   // Parametrit: -
   // Toiminta:   Palauttaa kukkulabonuksen
   int palautaKukkula();
   
   // Funktio:    palautaPuolustus()
   // Parametrit: -
   // Toiminta:   Palauttaa puolustusbonuksen
   int palautaPuolustus();
   
   //Funktio:     palautaLinnoitus
   //Parametrit:  -
   //Toiminta:    Palauttaa tiedon onko sankari linnoitettuna
   bool palautaLinnoitus();
   
   // Funktio:    linnoita()
   // Parametrit: bool paalle
   // Toiminta:   Linnoittaa sankarin tai poistaa sankarin
   //             linnoituksen sen mukaan mik� arvo parametrina
   //             on annettu.
   void linnoita(bool paalle);
   
   // Funktio:    keraaBonus()
   // Parametrit: int jousi
   //             int ammus
   //             int voima
   //             int kukkula
   //             int puolustus
   //             int toiminta
   //             int nako
   // Toiminta:   Keraa sankarin saaman bonuksen ja muuttaa sen mukaan
   //             sankarin sis�isi� tietoja.
   void keraaBonus(int jousi, int ammus, int voima, int kukkula, 
                   int puolustus, int toiminta, int nako);
   
 private:

   // luokan sis�iset tiedot
   int elama_;
   int toimintapisteet_;
   int voimabonus_;
   int puolustusbonus_;
   int kukkulabonus_;
   int nako_;
   int tarkkuus_;
   int ammukset_;
   int koordX_;
   int koordY_;
   bool linnoitettu_;
   bool kruunu_;
};

#endif
