//###############################################################
//***************************************************************
//                                                               
//       Hannu Ranta   				                             
//                                                               
//                                                               
//       A quest for the crown 				                     
//---------------------------------------------------------------
// Kyseess� on kahden tai useamman pelaajan v�linen vuoro-       
// pohjainen strategiapeli. Peliss� kukin pelaaja ohjaa          
// taisteluun yht� tai useampaa sankaria erilaisilla kartoilla.  
// Jokaista sankaria ohjataan yksi kerrallaan.                   
// Pelin voittaa joukkue, joka saa viety� Kuninkaiden            
// Kruunun Camelotiin tai tuhottua kaikki vastustan sankarit.    
// --------------------------------------------------------------
// **************************************************************
// ##############################################################

// M��ritell��n include-directiivit
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "apufunktiot.hh"
#include "kartta.hh"
#include "tiedot.hh"
#include "sankari.hh"
#include "komentotulkki.hh"
#include "nuoli.hh"

// Avataan std-nimiavaruus k�ytt��n
using namespace std;

//P��ohjelma.
//Muodostaa pelin rungon ja huolehtii t�rkeimmist� toiminnoista
//kuten vuoroista ja niiden vaihdosta sek� lopputilanteen 
//tarkastamisesta. Kutsuu muita funktioita eri kirjastoista tilanteen
//mukaan. Sis�lt�� muuttujien esittelyj� ja pelin 
//p��silmukan.
//Aluksi kutsuu karttatiedoston ja komentoriviparametrien
//oikeellisuuden tarkistavia aliohjelmia ja mik�li kaikki oli kunnossa 
//jatketaan ohjelman suoritusta. T�m�n j�lkeen kutsuu lopputilanteen
//tarkastavaa funktiota. Mik�li peli ei ole lopussa annetaan 
//Innocciuksen ensimm�iselle sankarille vuoro ja k�ynnistet��n pelin 
//p��silmukka josta poistutaan vain lopeta-komennolla tai 
//pelin saavuttaessa lopputilanteensa.

int main(int argc, char **argv)
{
   //Alustetaan ohjelmassa tarvitut muuttujat
   Tila debug = OFF;
   int siemenluku = 0;
   unsigned int leveys = 0;
   unsigned int korkeus = 0;
   unsigned int sankari = 0;
   int paikkaX = 0;
   int paikkaY = 0;
   string kartta = "";
   string komento = "";
   vector<vector<KartanSolu> > lauta;
   vector<Sankari> innoccius;
   vector<Sankari> tyrannid;
   vector<Nuoli> nuolet;
   Puoli pelaaja = EISANKARIA;
   bool vaihda = false;
   bool lopeta = false;
   
   //Tulostetaan  alkutekstit
   tulostaTekstit();
   
   //Tarkistetaan l�ytyyk� ohjevipu ja jos l�ytyy tulostetaan
   //ohje ja lopetetaan ohjelman suoritus arvolla EXIT_SUCCESS
   if (loytyykoOhje(argc, argv) == true)
   {
      return EXIT_SUCCESS;
   }
   
   //Tarkistetaan onko komentoriviparametrit ja karttatiedosto kunnossa.
   //Jos jotain on vialla lopetetaan ohjelma arvolla EXIT_FAILURE
   if ((tarkistaParametrit(argc, argv, siemenluku, kartta, debug) == false)
       or (tarkistaKartta(kartta, leveys, korkeus) == false))
   {
      return EXIT_FAILURE;
   }
  
   //Asetetaan satunnaisgeneraattorin siemenluku ja alustetaan 
   //kartan tiedot sis�lt�v� lauta-vektori
   srand(siemenluku);
   alustaLauta(lauta, kartta, innoccius, tyrannid, debug);
   
   //Pelin p��silmukka
   while (!cin.eof())
   {
      //Tarkistetaan ollaanko lopputilanteessa ja jos ollaan
      //lopetetaan ohjelma arvolla EXIT_SUCCESS
      if (tarkistaLopputilanne(lauta,innoccius,tyrannid,
                               false, nuolet) == true)
      {
         return EXIT_SUCCESS;
      }
      
      //Annetaan ensimm�inen vuoro Innocciukselle
      if (pelaaja == EISANKARIA)
      {
         //Tulostetaan tyhj�t rivit, asetetaan vuoro 
         //Innocciukselle, p�ivitet��n n�k�kentt� ja piirret��n
         //kartta
         tulostaAloitus(INNOCCIUS);
         pelaaja = INNOCCIUS; 
         paivitaNakyvyys(lauta,debug,innoccius,tyrannid,pelaaja);
         tulostaKartta(lauta,pelaaja,sankari, innoccius, tyrannid, nuolet);
      }

      if (pelaaja == INNOCCIUS)
      {
         //Jos sankari on kuollut siirret��n vuoro seuraavalle
         if (innoccius.at(sankari).palautaElama() == 0)
         {
            vaihda = true;
         }
         
         else
         {
            for (unsigned int loop = 0; loop < innoccius.size(); ++loop)
            {
               if (innoccius.at(loop).palautaElama() > 0)
               {
                  etsiPaikat(lauta, pelaaja, loop, paikkaX, paikkaY);
                  innoccius.at(loop).paivitaKoordinaatit(paikkaX, paikkaY);
               }
            }
            
            //Tulostetaan komentokehote ja tulkitaan k�ytt�j�n sy�tt�m�
            //komento
            cout << sankari << " > ";
            getline(cin, komento);
            tulkitseSyote(komento, vaihda, lopeta, lauta, 
                         innoccius, tyrannid, pelaaja, debug, sankari, nuolet);
         }
      }
      
      else if (pelaaja == TYRANNID)
      {
         //Jos sankari on kuollut siirret��n vuoro seuraavalle
         if (tyrannid.at(sankari).palautaElama() == 0)
         {
            vaihda = true;
         }
         
         else
         {
            for (unsigned int loop = 0; loop < tyrannid.size(); ++loop)
            {
               if (tyrannid.at(loop).palautaElama() > 0)
               {
                  etsiPaikat(lauta, pelaaja, loop, paikkaX, paikkaY);
                  tyrannid.at(loop).paivitaKoordinaatit(paikkaX, paikkaY);
               }
            }
            
            //Tulostetaan komentokehote ja tulkitaan k�ytt�j�n sy�tt�m�
            //komento
            cout << sankari << " > ";
            getline(cin, komento);
            tulkitseSyote(komento, vaihda, lopeta, lauta, 
                         innoccius, tyrannid, pelaaja, debug, sankari, nuolet);
         }
      }
         
      //Jos pelaaja haluaa lopettaa pelin tulostetaan voittaja
      //ja lopetetaan ohjelma arvolla EXIT_SUCCESS
      if (lopeta == true)
      {
         tarkistaLopputilanne(lauta,innoccius,tyrannid,true, nuolet);
         return EXIT_SUCCESS;
      }
      
      //Jos vaihda-muuttujan arvo on tosi siirret��n vuoro 
      //toiselle sankarille.
      if (vaihda == true)
      {
         ++sankari;
         vaihda = false;
         
         //Jos Innocciuksen sankarit on k�yty l�pi siirret��n vuoro
         //Tyrannidille
         if ((pelaaja == INNOCCIUS) and (sankari >= innoccius.size()))
         {
            for (unsigned int loop = 0; loop < nuolet.size(); ++loop)
            {
               siirraNuolta(nuolet.at(loop), lauta, innoccius, tyrannid, 
                            false);
               siirraNuolta(nuolet.at(loop), lauta, innoccius, tyrannid,
                            false);
               siirraNuolta(nuolet.at(loop), lauta, innoccius, tyrannid,
                            false);
               siirraNuolta(nuolet.at(loop), lauta, innoccius, tyrannid,
                            false);
               siirraNuolta(nuolet.at(loop), lauta, innoccius, tyrannid,
                            false);
            }
            
            poistaTurhat(nuolet);
            
            //Tarkistetaan ollaanko lopputilanteessa ja jos ollaan
            //lopetetaan ohjelma arvolla EXIT_SUCCESS
            if (tarkistaLopputilanne(lauta,innoccius,tyrannid,
                                     false, nuolet) == true)
            {
               return EXIT_SUCCESS;
            }
            
            //Tulostetaan tyhj�t rivit
            tulostaAloitus(TYRANNID);
            pelaaja = TYRANNID;
            sankari = 0;
            
            //Asetetaan kaikkien sankarien toimintapisteet
            //alkuarvoonsa
            for (unsigned int loop = 0; loop < tyrannid.size(); ++loop)
            {
               tyrannid.at(loop).nollaaToimintapisteet();
            }

            //P�ivitet��n sankarien n�kem�t alueet ja tulostetaan kartta
            paivitaNakyvyys(lauta,debug,innoccius,tyrannid,pelaaja);
            tulostaKartta(lauta,pelaaja,sankari, innoccius, tyrannid, nuolet);
         }
         
         //Jos kaikki Tyrannidin sankarit on k�yty l�pi annetaan 
         //vuoro Innocciukselle
         else if ((pelaaja == TYRANNID) and (sankari >= tyrannid.size())) 
         {
            for (unsigned int loop = 0; loop < nuolet.size(); ++loop)
            {
               siirraNuolta(nuolet.at(loop), lauta, innoccius, tyrannid,
                            false);
               siirraNuolta(nuolet.at(loop), lauta, innoccius, tyrannid,
                            false);
               siirraNuolta(nuolet.at(loop), lauta, innoccius, tyrannid,
                            false);
               siirraNuolta(nuolet.at(loop), lauta, innoccius, tyrannid,
                            false);
               siirraNuolta(nuolet.at(loop), lauta, innoccius, tyrannid,
                            false);
            }
            
            poistaTurhat(nuolet);
            
            //Tarkistetaan ollaanko lopputilanteessa ja jos ollaan
            //lopetetaan ohjelma arvolla EXIT_SUCCESS
            if (tarkistaLopputilanne(lauta,innoccius,tyrannid,false,
                                     nuolet) == true)
            {
               return EXIT_SUCCESS;
            }
            
            //Tulostetaan tyhj�t rivit 
            tulostaAloitus(INNOCCIUS);
            pelaaja = INNOCCIUS; 
            sankari = 0;
            
            //Asetetaan Innocciuksen sankareiden toimintapisteet
            //alkuarvoonsa
            for (unsigned int loop = 0; loop < innoccius.size(); ++loop)
            {
               innoccius.at(loop).nollaaToimintapisteet();
            }
            
            //P�ivitet��n sankarien n�k�kent�t ja tulostetaan kartta
            paivitaNakyvyys(lauta,debug,innoccius,tyrannid,pelaaja);
            tulostaKartta(lauta,pelaaja,sankari, innoccius, tyrannid, nuolet);
         }
         else
         {
            paivitaNakyvyys(lauta,debug,innoccius,tyrannid,pelaaja);
            tulostaKartta(lauta,pelaaja,sankari, innoccius, tyrannid,nuolet);
         }
      }
   }   
   
   return EXIT_SUCCESS;
}
