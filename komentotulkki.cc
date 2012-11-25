//###############################################
//                                             ##
//  Hannu Ranta 							   ##
//                                             ##
//  komentotulkki.cc                           ##
//  Komentotulkki-				               ##
//  rajapinnan toteutus                        ##
//                                             ##
//###############################################

//M‰‰ritell‰‰n include-direktiivit
#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cstdio>
#include <sstream>
#include <algorithm>

#include "komentotulkki.hh"
#include "tiedot.hh"
#include "apufunktiot.hh"

//M‰‰ritell‰‰n k‰ytett‰v‰ nimiavaruus
using namespace std;


//Funktio joka poistaa komento-merkkijonon alusta turhan tyhj‰n tilan 
//ja muuttaa kaikki komento-merkkijonon merkit pieniksi.
void pienennaKirjaimet(string& komento)
{
   char kursori = ' ';
   string temp  = "";
   bool lippu = false;
   
   for (unsigned int loop = 0; loop < komento.size(); ++loop)
   {
      kursori = komento[loop];
      
      if ((isspace(kursori)) and (lippu == false))
      {
         //Poistetaan tyhj‰ tila komennon alusta
      }
      else
      {
         temp.push_back(static_cast<char>(tolower(kursori)));
         lippu = true;
      }
   }
   
   komento = temp;
}

//Etsii syˆtteest‰ mahdolliset parametrit ja parsii ne
//omaan muuttujaansa
void etsiParametrit(string& komento, string& parametrit)
{
   char kursori = ' ';
   string temp  = "";
   string temp2 = "";
   bool lippu = false;
   
   for (unsigned int loop = 0; loop < komento.size(); ++loop)
   {
      kursori = komento[loop];
      
      if (isspace(kursori) and (lippu == false))
      {
         lippu = true;
      }
      
      else
      {
         if (lippu == true)
         {
            temp2.push_back(static_cast<char>(tolower(kursori)));
         }
         else
         {
            temp.push_back(static_cast<char>(tolower(kursori)));
         }
      }
   }
   
   komento = temp;
   parametrit = temp2;
}

//Tulostaa komentorivin aputekstit.
void aputeksti()
{
   cout << endl;
   cout << "###        A quest for the crown.       ###" << endl;
   cout << "-------------------------------------------" << endl;
   cout << "Komentotulkin ymm‰rt‰m‰t komennot ja parametrit:";
   cout << endl << endl;
   
   cout << "-------------------------------------------" << endl;
   cout << "LIIKU <suunta> <m‰‰r‰> (1 toimintapiste)" << endl;
   cout << "Liikuttaa vuorossa olevaa sankaria m‰‰r‰ ruutua";
   cout << "suuntaan suunta. Suunta ilmaistaan numeroilla seuraavasti:";
   cout << endl << endl;
   cout << "7 8 9" << endl;
   cout << "4   6" << endl;
   cout << "1 2 3" << endl;
   cout << "-------------------------------------------" << endl;
   
   cout << "AMMU <x> <y> (3 toimintapistett‰)" << endl;
   cout << "Vuorossa oleva sankari ampuu kolme nuolta kohti";
   cout << "koordinaatteja (x,y). Nuolten m‰‰r‰ voi vaihdella";
   cout << "bonusten mukaan." << endl;
   cout << "-------------------------------------------" << endl;
   
   cout << "LINNOITA (1 toimintapiste/kerta)" << endl;
   cout << "Linnoittaa sankarin." << endl;
   cout << "-------------------------------------------" << endl;
   
   cout << "KARTTA" << endl;
   cout << "Tulostaa kartan." << endl;
   cout << "-------------------------------------------" << endl;
   
   cout << "TIEDOT" << endl;
   cout << "Tulostaa vuorossa olevan pelaajan sankarien tiedot.";
   cout << endl;
   cout << "-------------------------------------------" << endl;
   
   cout << "ODOTA" << endl;
   cout << "Luovuttaa pelivuoron eteenp‰in." << endl;
   cout << "-------------------------------------------" << endl;
   
   cout << "PARANNA (3 toimintapistett‰/kerta)" << endl;
   cout << "Parantaa sankaria 20 pistett‰." << endl;
   cout << "-------------------------------------------" << endl;
   
   cout << "APUA/HELP" << endl;
   cout << "Tulostaa pelin ohjetekstin." << endl;
   cout << "-------------------------------------------" << endl;
   
   cout << "LOPETA/QUIT" << endl;
   cout << "Lopettaa pelin" << endl;
   cout << "-------------------------------------------" << endl;
}

//Parsii komentorivin komennoille annetut parametrit 
//merkkijonoista.
void parsiParametrit(string& parametrit, vector<string>& parsitut)
{
   string parametri_1 = "";
   string parametri_2 = "";
   string parametri_3 = "";
   
   stringstream virta;
   
   virta << parametrit;
   virta >> parametri_1;
   virta >> parametri_2;
   virta >> parametri_3;
   
   if (parametri_1.size() > 0)
   {
      parsitut.push_back(parametri_1);
   }
   
   if (parametri_2.size() > 0)
   {
      parsitut.push_back(parametri_2);
   }
   
   if (parametri_3.size() > 0)
   {
      parsitut.push_back(parametri_3);
   }
}

//Funktio, joka tarkistaa parametrina annetun suunnan oikeellisuuden
bool tarkistaSuunta(int& suunta, string& parametri)
{  
   if (parametri.size() > 1)
   {
      return false;
   }
   
   stringstream virta;
   virta << parametri;
   virta >> suunta;
   
   if ((suunta != SUUNNAT[0]) 
       and (suunta != SUUNNAT[1])
       and (suunta != SUUNNAT[2])
       and (suunta != SUUNNAT[3])
       and (suunta != SUUNNAT[4])
       and (suunta != SUUNNAT[5])
       and (suunta != SUUNNAT[6])
       and (suunta != SUUNNAT[7]))
   {
      return false;
   }
   
   return true;
}

//Funktio, joka tarkistaa parametrina annetun m‰‰r‰n oikeellisuuden
bool tarkistaMaara(int& maara, string& parametri, bool negatiivinen)
{
   for (unsigned int loop = 0; loop < parametri.size(); ++loop)
   {
      if ((!isdigit(parametri[loop]) and (parametri[loop] != '-')))
      {
         return false;
      }
   }
   
   stringstream virta;
   virta << parametri;
   virta >> maara;
   
   if ((maara < 0) and (negatiivinen == false))
   {
      maara = 0;
   }
   
   return true;
}

//Tarkistaa ovatko koordinaatit joihin koitetaan liikkua kartalla.
bool onkoKartalla(vector<vector<KartanSolu> >& lauta, unsigned int paikkaX, 
                  unsigned int paikkaY)
{
   unsigned int nolla = 0;
   
   if ((paikkaX < nolla) or (paikkaX > (lauta.at(0).size() - 1)))
   {
      return false;
   }
   
   else
   {
      if ((paikkaY < nolla) or (paikkaY > (lauta.size() - 1)))
      {
         return false;
      }
      
      else
      {
         return true;
      }
   }
}

//Laskee kaikkien ruutujen koordinaatit, joihin sankari n‰kee ja 
//p‰ivitt‰‰ niiden tilan NAKOKENTASSA-muotoon. M‰‰ritt‰‰ ensin
//n‰kˆkent‰n "neliˆn" kulmat ja laskee siit‰ muut koordinaatit
//keh‰ kerrallaan. 
void laskeNakosade(vector<vector<KartanSolu> >& lauta, int paikkaX, 
                   int paikkaY, int sade)
{
   Suunta alkuperainen = {paikkaX, paikkaY};
   Puoli pelaaja = lauta.at(paikkaY).at(paikkaX).puoli;
   
   vector<Suunta> ruudut;
   
   for (int loop = 0; loop < sade; ++loop)
   {
      Suunta koillinen = MUUTOS[1];
      Suunta kaakko = MUUTOS[3];
      Suunta lounas = MUUTOS[5];
      Suunta luode = MUUTOS[7];
      
      koillinen.dx = alkuperainen.dx + (koillinen.dx * (loop + 1)); 
      koillinen.dy = alkuperainen.dy + (koillinen.dy * (loop + 1)); 
   
      kaakko.dx = alkuperainen.dx + (kaakko.dx * (loop + 1)); 
      kaakko.dy = alkuperainen.dy + (kaakko.dy * (loop + 1)); 
   
      lounas.dx = alkuperainen.dx + (lounas.dx * (loop + 1)); 
      lounas.dy = alkuperainen.dy + (lounas.dy * (loop + 1)); 
   
      luode.dx = alkuperainen.dx + (luode.dx * (loop + 1)); 
      luode.dy = alkuperainen.dy + (luode.dy * (loop + 1)); 
   
      for (int loop_2 = luode.dx; loop_2 < (koillinen.dx + 1); ++loop_2)
      { 
         Suunta temp = {0,0};
         temp.dx = loop_2;
         temp.dy = luode.dy;
         ruudut.push_back(temp);
      }
    
      for (int loop_2 = koillinen.dy; loop_2 < (kaakko.dy + 1); ++loop_2)
      { 
         Suunta temp = {0,0};
         temp.dx = koillinen.dx;
         temp.dy = loop_2;
         ruudut.push_back(temp);
      }
      
      for (int loop_2 = lounas.dx; loop_2 < (kaakko.dx + 1); ++loop_2)
      { 
         Suunta temp = {0,0};
         temp.dx = loop_2;
         temp.dy = lounas.dy;
         ruudut.push_back(temp);
      }
      
      for (int loop_2 = luode.dy; loop_2 < (lounas.dy + 1); ++loop_2)
      { 
         Suunta temp = {0,0};
         temp.dx = luode.dx;
         temp.dy = loop_2;
         ruudut.push_back(temp);
      }
   }
   
   for(unsigned int loop = 0; loop < ruudut.size(); ++loop)
   {
      if (onkoKartalla(lauta, ruudut.at(loop).dx, ruudut.at(loop).dy))
      {
         int koordX = ruudut.at(loop).dx;
         int koordY = ruudut.at(loop).dy;
         
         if (pelaaja == INNOCCIUS)
         {
            lauta.at(koordY).at(koordX).innoccius = NAKOKENTASSA;
         }
         else if (pelaaja == TYRANNID)
         {
            lauta.at(koordY).at(koordX).tyrannid = NAKOKENTASSA;
         }
      }
   }
}

//P‰ivitt‰‰ sankarin n‰kemiss‰teen
void paivitaNakyvyys(vector<vector<KartanSolu> >& lauta, Tila debug,
                     vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                     Puoli pelaaja)
{
   if ((debug == ON) or (pelaaja == EISANKARIA))
   {
      for (unsigned int loop = 0; loop < lauta.size(); ++loop)
      {
         for (unsigned int loop_2 = 0; loop_2 < lauta.at(loop).size(); 
              ++loop_2)
         {
            lauta.at(loop).at(loop_2).innoccius = NAKOKENTASSA;
            lauta.at(loop).at(loop_2).tyrannid = NAKOKENTASSA;
         }
      }
   }
   
   else
   {
      for (unsigned int loop = 0; loop < lauta.size(); ++loop)
      {
         for (unsigned int loop_2 = 0; loop_2 < lauta.at(loop).size();
              ++loop_2)
         {
            if (lauta.at(loop).at(loop_2).innoccius == NAKOKENTASSA)
            {
               lauta.at(loop).at(loop_2).innoccius = MUISTINVARAINEN;
            }
            
            if (lauta.at(loop).at(loop_2).tyrannid == NAKOKENTASSA)
            {
               lauta.at(loop).at(loop_2).tyrannid = MUISTINVARAINEN;
            }
         }
      }
      
      for (unsigned int loop = 0; loop < lauta.size(); ++loop)
      {
         for (unsigned int loop_2 = 0; loop_2 < lauta.at(loop).size();
              ++loop_2)
         {
            if (lauta.at(loop).at(loop_2).puoli == INNOCCIUS)
            {
               int sade = 0;
               int vuoro = 0;
               vuoro = lauta.at(loop).at(loop_2).jarjestys;
               lauta.at(loop).at(loop_2).innoccius = NAKOKENTASSA;
               sade = innoccius.at(vuoro).palautaNakosade();
      
               if (lauta.at(loop).at(loop_2).maasto == KUKKULA)
               {
                  ++sade;
               }
               
               laskeNakosade(lauta, loop_2, loop, sade);
            }
            
            if (lauta.at(loop).at(loop_2).puoli == TYRANNID)
            {
               int sade = 0;
               int vuoro = 0;
               vuoro = lauta.at(loop).at(loop_2).jarjestys;
               lauta.at(loop).at(loop_2).tyrannid = NAKOKENTASSA;
               sade = tyrannid.at(vuoro).palautaNakosade();
      
               if (lauta.at(loop).at(loop_2).maasto == KUKKULA)
               {
                  ++sade;
               }
               
               laskeNakosade(lauta, loop_2, loop, sade);
            }
         }
      }
   }
}

bool tulostaNuolenmerkki(int paikkaX, int paikkaY, vector<Nuoli>& nuolet)
{
   for (unsigned int loop = 0; loop < nuolet.size(); ++loop)
   {
      int nuolenX = 0;
      int nuolenY = 0;
      
      nuolet.at(loop).palautaPaikka(nuolenX, nuolenY);
      
      if ((nuolenX == paikkaX) and (nuolenY == paikkaY))
      {
         if (nuolet.at(loop).piirretaanko() == true)
         {
            nuolet.at(loop).piirraMerkki();
            return true;
         }
      }
   }
   return false;
}

//Tulostaa sankarin n‰kˆkent‰ss‰ olevan ruudun merkin
void tulostaNakokentassa(KartanSolu temp, int paikkaX, int paikkaY, 
                         vector<Nuoli>& nuolet)
{
   bool piirrettiin = false;
   const int KYMMENEN = 10;
   const int KAKSIKYMMENTA = 20;
   
   if ((temp.kuninkaidenKruunu == true) and (piirrettiin == false))
   {
      piirrettiin = true;
      cout << MERKIT[10] << " ";
   }
   if ((temp.puoli == INNOCCIUS) and (piirrettiin == false))
   {
      piirrettiin = true;
      cout << MERKIT[KYMMENEN + 6] << " ";
   }
   if ((temp.puoli == TYRANNID) and (piirrettiin == false))
   {
      piirrettiin = true;
      cout << MERKIT[KYMMENEN + 7] << " ";
   }
   if ((temp.nuoli == true) and (piirrettiin == false))
   {
      if (tulostaNuolenmerkki(paikkaX, paikkaY, nuolet))
      {
         piirrettiin = true;
      }
   }

   if ((temp.bonus.size() != 0) and (piirrettiin == false))
   {
      piirrettiin = true;
      cout << MERKIT[KAKSIKYMMENTA + 2] << " ";
   }
   
   if (piirrettiin == false)
   {
      if (temp.maasto == TASANKO)
      {
         cout << MERKIT[KYMMENEN + 5] << " ";
      }
      if (temp.maasto == KUKKULA)
      {
         cout << MERKIT[KYMMENEN + 4] << " ";
      }
      if (temp.maasto == VUORI)
      {
         cout << MERKIT[KYMMENEN + 3] << " ";
      }
      if (temp.maasto == CAMELOT)
      {
         cout << MERKIT[KYMMENEN + 2] << " ";
      }
   }
}

//Tulostaa sankarin muistaman ruudun merkin
void tulostaMuistissa(KartanSolu temp)
{
   const int KYMMENEN = 10;
   
   if (temp.maasto == TASANKO)
   {
      cout << MERKIT[KYMMENEN + 5] << " ";
   }
   if (temp.maasto == KUKKULA)
   {
      cout << MERKIT[KYMMENEN + 4] << " ";
   }
   if (temp.maasto == VUORI)
   {
      cout << MERKIT[KYMMENEN + 3] << " ";
   }
   if (temp.maasto == CAMELOT)
   {
      cout << MERKIT[KYMMENEN + 2] << " ";
   }
}

//Tarkistaa pelin lopputilanteen eli onko molemmilla pelaajilla
//sankareita elossa tai onko kruunu viety Camelotiin.
//Mik‰li peli on saavuttanut lopputilanteen tai lopeta-komento on
//annettu tulostetaan voittaja.
bool tarkistaLopputilanne(vector<vector<KartanSolu> >& lauta, 
                          vector<Sankari>& innoccius, 
                          vector<Sankari>& tyrannid,
                          bool lopeta, vector<Nuoli>& nuolet)
{
   int innocciusElossa = 0;
   int tyrannidElossa = 0;
   int koordX = 0;
   int koordY = 0;
   unsigned int paikkaX = 0;
   unsigned int paikkaY = 0;
   Puoli pelaaja = EISANKARIA;
   
   for (unsigned int loop = 0; loop < lauta.size(); ++loop)
   {
      for (unsigned int loop_2 = 0; loop_2 < lauta.at(loop).size(); ++loop_2)
      {
         if (lauta.at(loop).at(loop_2).maasto == CAMELOT)
         {
            for (unsigned int loop_3 = 0; loop_3 < tyrannid.size(); ++loop_3)
            {
               etsiPaikat(lauta, INNOCCIUS, loop_3, koordX, koordY);
               paikkaX = koordX;
               paikkaY = koordY;
               
               if ((paikkaX == loop_2) and (paikkaY == loop)
                   and (innoccius.at(loop_3).onkoKruunu() == true))
               {
                  pelaaja = INNOCCIUS;
               }
            }
            
            for (unsigned int loop_3 = 0; loop_3 < tyrannid.size(); ++loop_3)
            {
               etsiPaikat(lauta, TYRANNID, loop_3, koordX, koordY);
               paikkaX = koordX;
               paikkaY = koordY;
               
               if ((paikkaX == loop_2) and (paikkaY == loop)
                   and (tyrannid.at(loop_3).onkoKruunu() == true))
               {
                  pelaaja = TYRANNID;
               }
            }
         }
      }
   }
   
   for (unsigned int loop = 0; loop < innoccius.size(); ++loop)
   {
      int elama = 0;
      elama = innoccius.at(loop).palautaElama();
      
      if (elama > 0)
      {
         ++innocciusElossa; 
      }
   }
   
   for (unsigned int loop = 0; loop < tyrannid.size(); ++loop)
   {
      int elama = 0;
      elama = tyrannid.at(loop).palautaElama();
      
      if (elama > 0)
      {
         ++tyrannidElossa;
      }
   }
   
   if ((tyrannidElossa == 0) and (innocciusElossa == 0))
   {
      paivitaNakyvyys(lauta,ON,innoccius,tyrannid,EISANKARIA);
      tulostaKartta(lauta,EISANKARIA,0, innoccius, tyrannid, nuolet);
      cout << "Tasapeli!" << endl;
      return true;
   }
   
   if ((tyrannidElossa == 0) or (pelaaja == INNOCCIUS))
   {
      paivitaNakyvyys(lauta,ON,innoccius,tyrannid,EISANKARIA);
      tulostaKartta(lauta,EISANKARIA,0, innoccius, tyrannid, nuolet);
      cout << "Voittaja on I!" << endl;
      return true;
   }
   
   if ((innocciusElossa == 0) or (pelaaja == TYRANNID))
   {
      paivitaNakyvyys(lauta,ON,innoccius,tyrannid,EISANKARIA);
      tulostaKartta(lauta,EISANKARIA,0, innoccius, tyrannid, nuolet);
      cout << "Voittaja on T!" << endl;
      return true;
   } 
   
   if (lopeta == true)
   {
      if (innocciusElossa > tyrannidElossa)
      {
         paivitaNakyvyys(lauta,ON,innoccius,tyrannid,EISANKARIA);
         tulostaKartta(lauta,EISANKARIA,0, innoccius, tyrannid, nuolet);
         cout << "Voittaja on I!" << endl;
      }
      else if (tyrannidElossa > innocciusElossa)
      {
         paivitaNakyvyys(lauta,ON,innoccius,tyrannid,EISANKARIA);
         tulostaKartta(lauta,EISANKARIA,0, innoccius, tyrannid,  nuolet);
         cout << "Voittaja on T!" << endl;
      }
      else
      {
         paivitaNakyvyys(lauta,ON,innoccius,tyrannid,EISANKARIA);
         tulostaKartta(lauta,EISANKARIA,0, innoccius, tyrannid, nuolet);
         cout << "Tasapeli!" << endl;
      }
   }
   
   return false;
}

//Tulostaa kartan ja koordinaattiakselit kartan yl‰puolelle ja
//vasemmalle puolelle.
void tulostaKartta(vector<vector<KartanSolu> >& lauta, Puoli pelaaja,
                   int sankari, vector<Sankari>& innoccius, 
                   vector<Sankari>& tyrannid, vector<Nuoli>& nuolet)
{
   const int KYMMENEN = 10;
   cout << "  ";
   
   for (unsigned int loop = 0; loop < lauta.at(0).size(); ++loop)
   {
      if ((loop % 10) == 0)
      {
         cout << "  ";
      }
      
      else
      {
         cout << (loop % 10) << " ";
      }
   }
   
   cout << endl;
   
   for (unsigned int loop = 0; loop < lauta.size(); ++loop)
   {
      if ((loop % 10) == 0)
      {
         cout << "  ";
      }
      
      else
      {
         cout << (loop % 10) << " ";
      }
      
      for (unsigned int loop_2 = 0; loop_2 < lauta.at(loop).size(); ++loop_2)
      {
         if (pelaaja == EISANKARIA)
         {
            int temp_sankari = 0;
            temp_sankari = lauta.at(loop).at(loop_2).jarjestys;
            if (((lauta.at(loop).at(loop_2).puoli == TYRANNID)
                   and (tyrannid.at(temp_sankari).onkoKruunu()))
                or ((lauta.at(loop).at(loop_2).puoli == INNOCCIUS)
                    and (innoccius.at(temp_sankari).onkoKruunu())))
            {
                  cout << MERKIT[10] << " ";
            }
            else
            {
               tulostaNakokentassa(lauta.at(loop).at(loop_2), loop_2, loop,
                                   nuolet);
            }
         }
         if (pelaaja == INNOCCIUS)
         {     
            if ((lauta.at(loop).at(loop_2).puoli == INNOCCIUS) 
                and (lauta.at(loop).at(loop_2).jarjestys == sankari))
            {
               cout << sankari << " ";
            }
            else
            {
               int temp_sankari = 0;
               temp_sankari = lauta.at(loop).at(loop_2).jarjestys;
               
               if ((lauta.at(loop).at(loop_2).puoli == TYRANNID)
                   and (tyrannid.at(temp_sankari).onkoKruunu()))
               {
                  cout << MERKIT[10] << " ";
               }
               else if (lauta.at(loop).at(loop_2).innoccius == NAKOKENTASSA)
               {
                  tulostaNakokentassa(lauta.at(loop).at(loop_2), loop_2, loop,
                                      nuolet);
               }
               else if (lauta.at(loop).at(loop_2).innoccius == MUISTINVARAINEN)
               {
                  tulostaMuistissa(lauta.at(loop).at(loop_2));
               }
               else
               {
                  cout << MERKIT[KYMMENEN + 1] << " ";
               }
            }
         }
         
         if (pelaaja == TYRANNID)
         {   
            if ((lauta.at(loop).at(loop_2).puoli == TYRANNID) 
                and (lauta.at(loop).at(loop_2).jarjestys == sankari))
            {
               cout << sankari << " ";
            }
            else
            {
               int temp_sankari = 0;
               temp_sankari = lauta.at(loop).at(loop_2).jarjestys;
               
               if ((lauta.at(loop).at(loop_2).puoli == INNOCCIUS)
                   and (innoccius.at(temp_sankari).onkoKruunu()))
               {
                  cout << MERKIT[10] << " ";
               }
               else if (lauta.at(loop).at(loop_2).tyrannid == NAKOKENTASSA)
               {
                  tulostaNakokentassa(lauta.at(loop).at(loop_2), loop_2, loop,
                                      nuolet);
               }
               else if (lauta.at(loop).at(loop_2).tyrannid == MUISTINVARAINEN)
               {
                  tulostaMuistissa(lauta.at(loop).at(loop_2));
               }
               else
               {
                  cout << MERKIT[KYMMENEN + 1] << " ";
               }
            }
         }
      }  
      cout << endl;
   }
}

//Etsii sankarin koordinaatit kartalta
void etsiPaikat(vector<vector<KartanSolu> >& lauta, Puoli pelaaja, int numero, 
                int& koordX, int& koordY)
{
   int lippu = false;
   
   for (unsigned int loop = 0; loop < lauta.size(); ++loop)
   {
      for (unsigned int loop_2 = 0; loop_2 < lauta.at(loop).size(); ++loop_2)
      {
         if ((lauta.at(loop).at(loop_2).puoli == pelaaja)
             and lauta.at(loop).at(loop_2).jarjestys == numero)
         {
            koordX = loop_2;
            koordY = loop;
            lippu = true;
            break;
         }
      }
      if (lippu == true)
      {
         break;
      }
   }
}

//Tulostaa vuorossa olevan pelaajan sankarien tiedot
void tulostaTiedot(vector<Sankari>& innoccius, vector<Sankari>& tyrannid, 
                   Puoli pelaaja, vector<vector<KartanSolu> >& lauta)
{
   if (pelaaja == INNOCCIUS)
   {
      int koordX = 0;
      int koordY = 0;
      bool maella = false;
      
      for (unsigned int loop = 0; loop < innoccius.size(); ++loop)
      {
         if (innoccius.at(loop).palautaElama() > 0)
         {
            etsiPaikat(lauta, pelaaja, loop, koordX, koordY);
            cout << "Pelaajan Innoccius sankari numero " << loop;
            innoccius.at(loop).paivitaKoordinaatit(koordX, koordY);
            if (lauta.at(koordY).at(koordX).maasto == KUKKULA)
            {
               maella = true;
            }
         }
         else
         {
            cout << "Pelaajan Innoccius sankari numero " << loop;
         }
         
         innoccius.at(loop).tulostaTiedot(cout, maella);
      }
   }
   
   if (pelaaja == TYRANNID)
   {
      int koordX = 0;
      int koordY = 0;
      bool maella = false;
      
      for (unsigned int loop = 0; loop < tyrannid.size(); ++loop)
      {
         if (tyrannid.at(loop).palautaElama() > 0)
         {
            etsiPaikat(lauta, pelaaja, loop, koordX, koordY);
            cout << "Pelaajan Tyrannid sankari numero " << loop;
            tyrannid.at(loop).paivitaKoordinaatit(koordX, koordY);
            if (lauta.at(koordY).at(koordX).maasto == KUKKULA)
            {
               maella = true;
            }
         }
         else
         {
            cout << "Pelaajan Tyrannid sankari numero " << loop;
         }
         
         tyrannid.at(loop).tulostaTiedot(cout, maella);
      }
   }
}

//Tulostaa pelaajan vuoron alussa tarvittavan m‰‰r‰n
//v‰lilyˆntej‰ ja odottaa rivinvaihdon painamista.
void tulostaAloitus(Puoli pelaaja)
{
   string temp = "";
   const int SEITSEMANKYMMENTA = 70;
   
   for (int loop = 0; loop < SEITSEMANKYMMENTA; ++loop)
   {
      cout << endl;
   }
   
   if (pelaaja == INNOCCIUS)
   {
      cout << "Pelaaja I paina rivinvaihtoa" << endl;
      
      while (true)
      {
         if (cin.get() == '\n')
         {
            break;
         }
      }
   }
   
   else if (pelaaja == TYRANNID)
   {
      cout << "Pelaaja T paina rivinvaihtoa" << endl;
      
      while (true)
      {
         if (cin.get() == '\n')
         {
            break;
         }
      }
   }
}

//Laskee sankarin seuraavan sijainnin kartalla 
//k‰ytt‰j‰n syˆtt‰mien tietojen perusteella.
void laskeKoordinaatit(int suunta, Suunta paikka, Suunta& kohde)
{
   switch (suunta)
   {
    case 1: {
       kohde.dx = paikka.dx + MUUTOS[5].dx;
       kohde.dy = paikka.dy + MUUTOS[5].dy;
       break;
    }
    case 2: {
       kohde.dx = paikka.dx + MUUTOS[4].dx;
       kohde.dy = paikka.dy + MUUTOS[4].dy;
       break;
    }
    case 3: {
       kohde.dx = paikka.dx + MUUTOS[3].dx;
       kohde.dy = paikka.dy + MUUTOS[3].dy;
       break;
    }
    case 4: {
       kohde.dx = paikka.dx + MUUTOS[6].dx;
       kohde.dy = paikka.dy + MUUTOS[6].dy;
       break;
    }
    case 6: {
       kohde.dx = paikka.dx + MUUTOS[2].dx;
       kohde.dy = paikka.dy + MUUTOS[2].dy;
       break;
    }
    case 7: {
       kohde.dx = paikka.dx + MUUTOS[7].dx;
       kohde.dy = paikka.dy + MUUTOS[7].dy;
       break;
    }
    case 8: {
       kohde.dx = paikka.dx + MUUTOS[0].dx;
       kohde.dy = paikka.dy + MUUTOS[0].dy;
       break;
    }
    case 9: {
       kohde.dx = paikka.dx + MUUTOS[1].dx;
       kohde.dy = paikka.dy + MUUTOS[1].dy;
       break;
    }
    default:
      break;
   }
}

//Tarkistaa lˆysikˆ sankari bonusta.
bool loytyikoBonus(vector<vector<KartanSolu> >& lauta, Suunta kohde)
{
   if (lauta.at(kohde.dy).at(kohde.dx).bonus.size() != 0)
   {
      return true;
   }
   
   return false;
}

//Ker‰‰ kartan ruudussa olleen bonuksen sankarille ja
//tulostaa oikean infotekstin riippuen bonuksesta.
void kokoaBonus(vector<Bonus>& bonus, Sankari& temp)
{
   for (unsigned int loop = 0; loop < bonus.size(); ++loop)
   {
      if (bonus.at(loop) == JOUSI)
      {
         cout << "Lˆysit bonuksen nimelt‰ Tarkempi Jousi joka";
         cout << " kasvatti kyseist‰ kyky‰ 1:ll‰" << endl;
         temp.keraaBonus(1,0,0,0,0,0,0);
      }
      if (bonus.at(loop) == AMMUS)
      {
         cout << "Lˆysit bonuksen nimelt‰ Enemm‰n ammuksia  joka";
         cout  <<  " kasvatti kyseist‰ kyky‰ 1:ll‰" << endl;
         temp.keraaBonus(0,1,0,0,0,0,0);
      }
      if (bonus.at(loop) == VOIMA)
      {
         cout << "Lˆysit bonuksen nimelt‰ Voimabonus joka";
         cout  <<  " kasvatti kyseist‰ kyky‰ 10%:ll‰" << endl;
         temp.keraaBonus(0,0,10,0,0,0,0);
      }
      if (bonus.at(loop) == KUKKULABONUS)
      {
         cout << "Lˆysit bonuksen nimelt‰ Kukkulabonus joka";
         cout  <<  " kasvatti kyseist‰ kyky‰ 25%:ll‰" << endl;
         const int KAKSIKYMMENTAVIISI = 25;
         temp.keraaBonus(0,0,0,KAKSIKYMMENTAVIISI,0,0,0);
      }
      if (bonus.at(loop) == PUOLUSTUS)
      {
         cout << "Lˆysit bonuksen nimelt‰ Puolustusbonus joka";
         cout  <<  " kasvatti kyseist‰ kyky‰ 25%:ll‰" << endl;
         const int KAKSIKYMMENTAVIISI = 25;
         temp.keraaBonus(0,0,0,0,KAKSIKYMMENTAVIISI,0,0);
      }
      if (bonus.at(loop) == TOIMINTAPISTE)
      {
         cout << "Lˆysit bonuksen nimelt‰ Toimintabonus joka";
         cout  <<  " kasvatti kyseist‰ kyky‰ 1:ll‰" << endl;
         temp.keraaBonus(0,0,0,0,0,1,0);
      }
      if (bonus.at(loop) == NAKO)
      {
         cout << "Lˆysit bonuksen nimelt‰ N‰kemisbonus joka";
         cout  <<  " kasvatti kyseist‰ kyky‰ 1:ll‰" << endl;
         temp.keraaBonus(0,0,0,0,0,0,1);
      }
   }
   
   bonus.clear();
}

//Tarkistaa lˆysikˆ sankari kuninkaidenkruunun.
bool loytyikoKruunu(vector<vector<KartanSolu> >& lauta, Suunta kohde)
{
   if (lauta.at(kohde.dy).at(kohde.dx).kuninkaidenKruunu == true)
   {
      lauta.at(kohde.dy).at(kohde.dx).kuninkaidenKruunu = false;
      cout << "Lˆysit Kuninkaiden Kruunun!" << endl;
      return true;
   }
   
   return false;
}

//Pudottaa sankarin kantamat bonukset mik‰li sankari kuolee
void pudotaBonukset(KartanSolu& ruutu, Sankari sankari)
{
   int toiminta = 0;
   int kukkula = 0;
   int voima = 0;
   int puolustus = 0;
   int jousi = 0;
   int nako = 0;
   int ammukset = 0;
   const int KYMMENEN = 10;
   const int KAKSIKYMMENTAVIISI = 25;
   Bonus bonus = TYHJA;
   
   toiminta = sankari.palautaToimintapisteet();
   kukkula = sankari.palautaKukkula();
   voima = sankari.palautaVoima();
   puolustus = sankari.palautaPuolustus();
   jousi = sankari.palautaTarkkuus();
   nako = sankari.palautaNakosade();
   ammukset = sankari.palautaAmmukset();
   
   toiminta = toiminta - PERUSTOIMINTA;
   kukkula = kukkula / KAKSIKYMMENTAVIISI;
   voima = voima / KYMMENEN;
   puolustus = puolustus / KAKSIKYMMENTAVIISI;
   jousi = PERUSJOUSI - jousi;
   nako = nako - PERUSNAKO;
   ammukset = ammukset - PERUSNUOLET;
   
   if (toiminta > 0)
   {
      for (int loop = 0; loop < toiminta; ++loop)
      {
         bonus = TOIMINTAPISTE;
         ruutu.bonus.push_back(bonus);
      }
   }
   
   if (kukkula > 0)
   {
      for (int loop = 0; loop < kukkula; ++loop)
      {
         bonus = KUKKULABONUS;
         ruutu.bonus.push_back(bonus);
      }
   }
   
   if (voima > 0)
   {
      for (int loop = 0; loop < voima; ++loop)
      {
         bonus = VOIMA;
         ruutu.bonus.push_back(bonus);
      }
   }
   
   if (puolustus > 0)
   {
      for (int loop = 0; loop < puolustus; ++loop)
      {
         bonus = PUOLUSTUS;
         ruutu.bonus.push_back(bonus);
      }
   }
   
   if (jousi > 0)
   {
      for (int loop = 0; loop < jousi; ++loop)
      {
         bonus = JOUSI;
         ruutu.bonus.push_back(bonus);
      }
   }
   
   if (nako > 0)
   {
      for (int loop = 0; loop < nako; ++loop)
      {
         bonus = NAKO;
         ruutu.bonus.push_back(bonus);
      }
   }
   
   if (ammukset > 0)
   {
      for (int loop = 0; loop < ammukset; ++loop)
      {
         bonus = AMMUS;
         ruutu.bonus.push_back(bonus);
      }
   }
}

void taistelu(vector<Sankari>& innoccius, vector<Sankari>& tyrannid, 
              vector<vector<KartanSolu> >& lauta, Puoli pelaaja, 
              int sankari, Suunta kohde, Suunta paikka)
{
   int puolustaja = 0;
   int muunneltuH = 0;
   int muunneltuP = 0;
   int voittoH = 0;
   int voittoP = 0;
   int kukkulaH = 0;
   int kukkulaP = 0;
   int voimaH = 0;
   int voimaP = 0;
   int elamaH = 0;
   int elamaP = 0;
   int vahinkoH = 0;
   int vahinkoP = 0;
   int puolustusP = 0;
   int kerroinP = 0;
   int arvottu = 0;
   const int KAKSIKYMMENTA = 20;
   const int SATA = 100;
   const int YSIYSI = 99;
   puolustaja = lauta.at(kohde.dy).at(kohde.dx).jarjestys;

   if (pelaaja == INNOCCIUS)
   {
      if (lauta.at(kohde.dy).at(kohde.dx).maasto == KUKKULA)
      {
         kukkulaH = innoccius.at(sankari).palautaKukkula();
      }
      
      voimaH = innoccius.at(sankari).palautaVoima();
      elamaH = innoccius.at(sankari).palautaElama();
      muunneltuH = 
        (((PERUSVOIMA * SATA) + ((PERUSVOIMA * SATA) * voimaH)) * elamaH);
      muunneltuH = muunneltuH / SATA;
   }
   if (pelaaja == TYRANNID)
   {
      if (lauta.at(kohde.dy).at(kohde.dx).maasto == KUKKULA)
      {
         kukkulaH = tyrannid.at(sankari).palautaKukkula();
      }
      
      voimaH = tyrannid.at(sankari).palautaVoima();
      elamaH = tyrannid.at(sankari).palautaElama();
      muunneltuH = 
        (((PERUSVOIMA * SATA) + ((PERUSVOIMA * SATA) * voimaH)) * elamaH);
      muunneltuH = muunneltuH / SATA;
   }

   if (lauta.at(kohde.dy).at(kohde.dx).puoli == INNOCCIUS)
   {
      if (lauta.at(kohde.dy).at(kohde.dx).maasto == KUKKULA)
      {
         kukkulaP = innoccius.at(puolustaja).palautaKukkula();
      }
      if (innoccius.at(puolustaja).palautaLinnoitus())
      {
         puolustusP = innoccius.at(puolustaja).palautaPuolustus();
      }
      
      voimaP = innoccius.at(puolustaja).palautaVoima();
      elamaP = innoccius.at(puolustaja).palautaElama();
      kerroinP = voimaP + kukkulaP + puolustusP - kukkulaH;
      
      if (kerroinP < 0)
      {
         kerroinP = SATA - kerroinP;
         muunneltuP = (((PERUSVOIMA * SATA) / kerroinP) * elamaP) / SATA;
      }
      else
      {
         muunneltuP = 
           (((PERUSVOIMA * SATA) + ((PERUSVOIMA * SATA) * kerroinP)) * elamaP);
         muunneltuP = muunneltuP / SATA;
      }
   }
   
   if (lauta.at(kohde.dy).at(kohde.dx).puoli == TYRANNID)
   {
      if (lauta.at(kohde.dy).at(kohde.dx).maasto == KUKKULA)
      {
         kukkulaP = tyrannid.at(puolustaja).palautaKukkula();
      }
      if (tyrannid.at(puolustaja).palautaLinnoitus())
      {
         puolustusP = tyrannid.at(puolustaja).palautaPuolustus();
      }
      
      voimaP = tyrannid.at(puolustaja).palautaVoima();
      elamaP = tyrannid.at(puolustaja).palautaElama();
      kerroinP = voimaP + kukkulaP + puolustusP - kukkulaH;
      
      if (kerroinP < 0)
      {
         kerroinP = SATA - kerroinP;
         muunneltuP = (((PERUSVOIMA * SATA) / kerroinP) * elamaP) / SATA;
      }
      else
      {
         muunneltuP = 
           (((PERUSVOIMA * SATA) + ((PERUSVOIMA * SATA) * kerroinP)) * elamaP);
         muunneltuP = muunneltuP / SATA;
      }
   }
   voittoH = ((muunneltuH  * SATA) / (muunneltuH + muunneltuP));
   voittoP = SATA - voittoH;
   
   vahinkoH = (KAKSIKYMMENTA * (3 * muunneltuH + muunneltuP) / 
               (3 * muunneltuP + muunneltuH));
   
   vahinkoP = (KAKSIKYMMENTA * (3 * muunneltuP + muunneltuH) / 
               (3 * muunneltuH + muunneltuP));
   
   while (true)
   {
      arvottu = arpa(0,YSIYSI);
      
      if (arvottu < voittoH)
      {
         if (lauta.at(kohde.dy).at(kohde.dx).puoli == INNOCCIUS)
         {
            innoccius.at(puolustaja).vahennaElamaa(vahinkoH);
            if (innoccius.at(puolustaja).palautaElama() == 0)
            {
               lauta.at(kohde.dy).at(kohde.dx).puoli = EISANKARIA;
               lauta.at(kohde.dy).at(kohde.dx).jarjestys = 0;
               if (innoccius.at(puolustaja).onkoKruunu())
               {
                  lauta.at(kohde.dy).at(kohde.dx).kuninkaidenKruunu = true;
               }
               pudotaBonukset(lauta.at(kohde.dy).at(kohde.dx), 
                              innoccius.at(puolustaja));
               break;
            }
         }
         if (lauta.at(kohde.dy).at(kohde.dx).puoli == TYRANNID)
         {
            tyrannid.at(puolustaja).vahennaElamaa(vahinkoH);
            if (tyrannid.at(puolustaja).palautaElama() == 0)
            {
               lauta.at(kohde.dy).at(kohde.dx).puoli = EISANKARIA;
               lauta.at(kohde.dy).at(kohde.dx).jarjestys = 0;
               if (tyrannid.at(puolustaja).onkoKruunu())
               {
                  lauta.at(kohde.dy).at(kohde.dx).kuninkaidenKruunu = true;
               }
               pudotaBonukset(lauta.at(kohde.dy).at(kohde.dx), 
                              tyrannid.at(puolustaja));
               break;
            }
         }
      }
      
      else
      {
         if (pelaaja == INNOCCIUS)
         {
            innoccius.at(sankari).vahennaElamaa(vahinkoP);
            if (innoccius.at(sankari).palautaElama() == 0)
            {
               lauta.at(paikka.dy).at(paikka.dx).puoli = EISANKARIA;
               lauta.at(paikka.dy).at(paikka.dx).jarjestys = 0;
               if (innoccius.at(sankari).onkoKruunu())
               {
                  lauta.at(paikka.dy).at(paikka.dx).kuninkaidenKruunu = true;
               }
               pudotaBonukset(lauta.at(paikka.dy).at(paikka.dx), 
                              innoccius.at(sankari));
               break;
            }
         }
         if (pelaaja == TYRANNID)
         {
            tyrannid.at(sankari).vahennaElamaa(vahinkoP);
            if (tyrannid.at(sankari).palautaElama() == 0)
            {
               lauta.at(paikka.dy).at(paikka.dx).puoli = EISANKARIA;
               lauta.at(paikka.dy).at(paikka.dx).jarjestys = 0;
               if (tyrannid.at(sankari).onkoKruunu())
               {
                  lauta.at(paikka.dy).at(paikka.dx).kuninkaidenKruunu = true;
               }
               pudotaBonukset(lauta.at(paikka.dy).at(paikka.dx), 
                              tyrannid.at(sankari));
               break;
            }
         }
      }
   }
}

//Liiku-komennon toteutus. Liikuttaa sankaria k‰ytt‰j‰n
//m‰‰ritt‰m‰‰n suuntaan oikean matkan ja v‰hent‰‰ sen mukaan 
//toimintapisteit‰. Tarkistaa myˆs saako ruutuun liikkua eli
//onko se kartalla ja onko siin‰ vuorta. 
//Mik‰li ruudussa johon liikutaan on toinen sankari
//kutsutaan taistelu()-funktiota ja suoritetaan taistelu.
void liiku(vector<vector<KartanSolu> >& lauta, Puoli pelaaja,
           int sankari, int suunta, int maara, Tila debug,
           vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
           bool& vaihda, vector<Nuoli>& nuolet)
{
   Suunta paikka = {0,0};
   Suunta kohde = {0,0};
   
   for (int loop = 0; loop < maara; ++loop)
   {
      etsiPaikat(lauta, pelaaja, sankari, paikka.dx, paikka.dy);
      laskeKoordinaatit(suunta, paikka, kohde);
      puraLinnoitus(innoccius, tyrannid, pelaaja, sankari);
      
      if (onkoKartalla(lauta, kohde.dx, kohde.dy) == false)
      {
         //Koitettiin liikkua ulos laudalta.
         break;
      }
      
      if (lauta.at(kohde.dy).at(kohde.dx).maasto == VUORI)
      {
         //Tˆrm‰ttiin vuoreen.
         break;
      }
      
      if (lauta.at(kohde.dy).at(kohde.dx).puoli != EISANKARIA)
      {
         //Taistelu
         taistelu(innoccius, tyrannid, lauta, pelaaja, sankari,
                  kohde, paikka);
         if (pelaaja == INNOCCIUS)
         {
            innoccius.at(sankari).muutaToimintapisteita(1);
            if (innoccius.at(sankari).palautaToimintapisteet() == 0)
            {
               vaihda = true;
            }
         }
         if (pelaaja == TYRANNID)
         {
            tyrannid.at(sankari).muutaToimintapisteita(1);
            if (tyrannid.at(sankari).palautaToimintapisteet() == 0)
            {
               vaihda = true;
            }
         }
         
         break;
      }
  
      else
      {
         if (((pelaaja == INNOCCIUS) 
              and (innoccius.at(sankari).palautaToimintapisteet() > 0))
             or ((pelaaja == TYRANNID) 
                 and (tyrannid.at(sankari).palautaToimintapisteet() > 0)))
         {
            lauta.at(kohde.dy).at(kohde.dx).puoli = 
              lauta.at(paikka.dy).at(paikka.dx).puoli;
            
            lauta.at(kohde.dy).at(kohde.dx).jarjestys = 
              lauta.at(paikka.dy).at(paikka.dx).jarjestys;
         
            lauta.at(paikka.dy).at(paikka.dx).puoli = EISANKARIA; 
            lauta.at(paikka.dy).at(paikka.dx).jarjestys = 0;
 
            paivitaNakyvyys(lauta, debug, innoccius, tyrannid, INNOCCIUS);
            paivitaNakyvyys(lauta, debug, innoccius, tyrannid, TYRANNID);
         
            if (pelaaja == INNOCCIUS)
            {
               innoccius.at(sankari).muutaToimintapisteita(1);
               if (innoccius.at(sankari).palautaToimintapisteet() == 0)
               {
                  vaihda = true;
               }
               if (loytyikoKruunu(lauta, kohde))
               {
                  innoccius.at(sankari).kruunuLoytyi();
               }
               if (loytyikoBonus(lauta, kohde))
               {
                  kokoaBonus(lauta.at(kohde.dy).at(kohde.dx).bonus,
                             innoccius.at(sankari));
               }
            }
            else if (pelaaja == TYRANNID)
            {
               tyrannid.at(sankari).muutaToimintapisteita(1);
               if (tyrannid.at(sankari).palautaToimintapisteet() == 0)
               {
                  vaihda = true;
               }
               if (loytyikoKruunu(lauta, kohde))
               {
                  tyrannid.at(sankari).kruunuLoytyi();
               }
               if (loytyikoBonus(lauta, kohde))
               {
                  kokoaBonus(lauta.at(kohde.dy).at(kohde.dx).bonus,
                             tyrannid.at(sankari));
               }
            }
         }
      }
   }
   
   if (((pelaaja == INNOCCIUS) 
        and (innoccius.at(sankari).palautaToimintapisteet() > 0))
       or ((pelaaja == TYRANNID) 
           and (tyrannid.at(sankari).palautaToimintapisteet() > 0)))
   {
      paivitaNakyvyys(lauta, debug, innoccius, tyrannid, INNOCCIUS);
      paivitaNakyvyys(lauta, debug, innoccius, tyrannid, TYRANNID);
      tulostaKartta(lauta, pelaaja, sankari, innoccius, tyrannid, nuolet);
   }
}

//Parantaa sankarin mik‰li toimintapisteet riitt‰v‰t komennon 
//suorittamiseen. Tarkistaa myˆs ettei el‰m‰ ylit‰ sataa.
void paranna(vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
             Puoli pelaaja, int sankari, bool& vaihda)
{
   if (pelaaja == INNOCCIUS)
   {
      if (innoccius.at(sankari).palautaToimintapisteet() < 3)
      {
         cerr << "Virhe: Liian v‰h‰n toimintapisteit‰." << endl;
      }
      else
      {
         innoccius.at(sankari).paranna();
         innoccius.at(sankari).muutaToimintapisteita(3);
         
         if (innoccius.at(sankari).palautaToimintapisteet() == 0)
         {
            vaihda = true;
         }
      }
   }
   
   else if (pelaaja == TYRANNID)
   {
      if (tyrannid.at(sankari).palautaToimintapisteet() < 3)
      {
         cerr << "Virhe: Liian v‰h‰n toimintapisteit‰." << endl;
      }
      else
      {
         tyrannid.at(sankari).paranna();
         tyrannid.at(sankari).muutaToimintapisteita(3);
         
         if (tyrannid.at(sankari).palautaToimintapisteet() == 0)
         {
            vaihda = true;
         }
      }
   }
}

//Purkaa sankarin linnoittautumisen. Tarvitaan liiku-komennon j‰lkeen.
void puraLinnoitus(vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                   Puoli pelaaja, int sankari)
{
   if (pelaaja == INNOCCIUS)
   {
      innoccius.at(sankari).linnoita(false);
   }
   
   else if (pelaaja == TYRANNID)
   {
      tyrannid.at(sankari).linnoita(false);
   }
}

//Linnoittaa sankarin ja tarkistaa onko sankarilla linnoittautumiseen
//vaadittavat toimintapisteet.
void linnoittaudu(vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                  Puoli pelaaja, int sankari, bool& vaihda)
{ 
   if (pelaaja == INNOCCIUS)
   {
      if (innoccius.at(sankari).palautaToimintapisteet() < 1)
      {
         cerr << "Virhe: Liian v‰h‰n toimintapisteit‰." << endl;
      }
      else
      {
         innoccius.at(sankari).linnoita(true);
         innoccius.at(sankari).muutaToimintapisteita(1);
         
         if (innoccius.at(sankari).palautaToimintapisteet() == 0)
         {
            vaihda = true;
         }
      }
   }
   
   else if (pelaaja == TYRANNID)
   {
      if (tyrannid.at(sankari).palautaToimintapisteet() < 1)
      {
         cerr << "Virhe: Liian v‰h‰n toimintapisteit‰." << endl;
      }
      else
      {
         tyrannid.at(sankari).linnoita(true);
         tyrannid.at(sankari).muutaToimintapisteita(1);
         
         if (tyrannid.at(sankari).palautaToimintapisteet() == 0)
         {
            vaihda = true;
         }
      }
   }
}

//Laskee nuolen todellisen osumapisteen jousen tarkkuuden mukaan.
void laskeOsumapiste(int& koordX, int& koordY, int tarkkuus)
{
   int yMuutos = 0;
   int xMuutos = 0;
   
   yMuutos = arpa(0, (2 * tarkkuus));
   xMuutos = arpa(0, (2 * tarkkuus));
   
   yMuutos = yMuutos - tarkkuus;
   xMuutos = xMuutos - tarkkuus;
   
   koordX = koordX + xMuutos;
   koordY = koordY + yMuutos;
}

//M‰‰r‰‰ nuolelle oikean piirtomerkin sen suunnan mukaan.
void maaraaMerkki(int maaliX, int maaliY, int sijaintiX, int sijaintiY,
                  char& merkki)
{
   const int KAKSIKYMMENTA = 20;
   const int KYMMENEN = 10;
   bool maaratty = false;
   
   if (maaliX == sijaintiX)
   {
      merkki = MERKIT[KAKSIKYMMENTA];
      maaratty = true;
   }
   
   if (maaliY == sijaintiY)
   {
      merkki = MERKIT[KYMMENEN + 8];
      maaratty = true;
   }
   
   if (((maaliY < sijaintiY) and (maaliX > sijaintiX))
       or ((maaliX < sijaintiX) and (maaliY > sijaintiY)))
   {
      if (maaratty == false)
      {
         merkki = MERKIT[KYMMENEN + 9];
      }
   }
   
   if (((maaliY < sijaintiY) and (maaliX < sijaintiX))
       or ((maaliX > sijaintiX) and (maaliY > sijaintiY)))
   {
      if (maaratty == false)
      {
         merkki = MERKIT[KAKSIKYMMENTA + 1];
      }
   }
}

//Funktio, joka laskee jokaiselle nuolelle lentoradan maali- ja
//paikkatietojen perusteella. M‰‰r‰‰ ensin nuolelle kulmakertoimen
//ja laskee sen avulla nuolen lent‰m‰t koordinaatit riippuen siit‰
//mihin suuntaan nuoli on lent‰m‰ss‰.
void laskeReitti(int maaliX, int maaliY, int paikkaX, int paikkaY,
                 int& kkX, int& kkY, Nuoli& nuoli, 
                 vector<vector<KartanSolu> >& lauta)
{
   int tempX = 0;
   int tempY = 0;
   int loop = 0;
   const int TUHAT = 1000;
   const int VIISISATAA = 500;
   
   tempX = maaliX - paikkaX;
   tempY = maaliY - paikkaY;
   
   if ((tempX == 0) and (tempY == 0))
   {
      nuoli.talletaReitti(paikkaX, paikkaY);
   }
   
   else
   {
      if (tempX == 0)
      {
         if (tempY > 0)
         {
            while (true)
            {
               Suunta koord = {0,0};
               koord.dx = paikkaX;
               koord.dy = paikkaY + loop;
               
               ++loop;
               
               if (onkoKartalla(lauta,koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
               
               if (koord.dy == maaliY)
               {
                  break;
               }
            }
         }
         
         else
         {
            while (true)
            {
               Suunta koord = {0,0};
               koord.dx = paikkaX;
               koord.dy = paikkaY - loop;
               
               ++loop;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
               
               if (koord.dy == maaliY)
               {
                  break;
               }
            }
         }
      }
      
      if (tempY == 0)
      {
         if (tempX > 0)
         {
            while (true)
            {
               Suunta koord = {0,0};
               koord.dy = paikkaY;
               koord.dx = paikkaX + loop;
               
               ++loop;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
               
               if (koord.dx == maaliX)
               {
                  break;
               }
            }
         }
         
         else
         {
            while (true)
            {
               Suunta koord = {0,0};
               koord.dy = paikkaY;
               
               koord.dx = paikkaX - loop;
               
               ++loop;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
               
               if (koord.dx == maaliX)
               {
                  break;
               }
            }
         }
      }
      
      if ((tempX > 0) and (tempY > 0))
      {
         if (tempY < tempX) 
         {
            tempY = tempY * TUHAT;
            kkX = tempY / tempX;
            kkY = 0;
            
            while (true)
            {
               Suunta koord = {0,0};
               int tulos = 0;
               int jako = 0;
               int jaannos = 0;
               
               tulos = loop * kkX;
               jako = tulos / TUHAT;
               jaannos = tulos % TUHAT;
               
               if (jaannos >= VIISISATAA)
               {
                  jako++;
               }
               
               koord.dx = paikkaX + loop;
               koord.dy = paikkaY + jako;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
                  
               ++loop;
               
               if (koord.dx == maaliX)
               {
                  break;
               }
            }
         }
         
         else
         {
            tempX = tempX * TUHAT;
            kkY = tempX / tempY;
            kkX = 0;
            
            while (true)
            {
               Suunta koord = {0,0};
               int tulos = 0;
               int jako = 0;
               int jaannos = 0;
               
               tulos = loop * kkY;
               jako = tulos / TUHAT;
               jaannos = tulos % TUHAT;
               
               if (jaannos >= VIISISATAA)
               {
                  jako++;
               }
               
               koord.dy = paikkaY + loop;
               koord.dx = paikkaX + jako;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
                  
               ++loop;
               
               if (koord.dy == maaliY)
               {
                  break;
               }
            }
         }
      }
      
      if ((tempX < 0) and (tempY > 0))
      {  
         if (tempY < abs(tempX)) 
         {
            tempY = tempY * TUHAT;
            kkX = tempY / abs(tempX);
            kkY = 0;
            
            while (true)
            {
               Suunta koord = {0,0};
               int tulos = 0;
               int jako = 0;
               int jaannos = 0;
               
               tulos = loop * kkX;
               jako = tulos / TUHAT;
               jaannos = tulos % TUHAT;
               
               if (abs(jaannos) >= VIISISATAA)
               {
                  jako++;
               }
               
               koord.dx = paikkaX - loop;
               koord.dy = paikkaY + jako;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
               
               ++loop;
               
               if (koord.dx == maaliX)
               {
                  break;
               }
            }
         }
         
         else
         {
            tempX = tempX * TUHAT;
            kkY = tempX / tempY;
            kkX = 0;
            
            while (true)
            {
               Suunta koord = {0,0};
               int tulos = 0;
               int jako = 0;
               int jaannos = 0;
               
               tulos = loop * kkY;
               jako = tulos / TUHAT;
               jaannos = tulos % TUHAT;
               
               if (abs(jaannos) >= VIISISATAA)
               {
                  jako--;
               }
               
               koord.dy = paikkaY + loop;
               koord.dx = paikkaX + jako;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
          
               ++loop;
               
               if (koord.dy == maaliY)
               {
                  break;
               }
            }
         }
      }
      
      if ((tempX > 0) and (tempY < 0))
      {
         if (abs(tempY) < tempX) 
         {
            tempY = tempY * TUHAT;
            kkX = tempY / tempX;
            kkY = 0;
            
            while (true)
            {
               Suunta koord = {0,0};
               int tulos = 0;
               int jako = 0;
               int jaannos = 0;
               
               tulos = loop * kkX;
               jako = tulos / TUHAT;
               jaannos = tulos % TUHAT;
               
               if (abs(jaannos) >= VIISISATAA)
               {
                  jako--;
               }
               
               koord.dx = paikkaX + loop;
               koord.dy = paikkaY + jako;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
               
               ++loop;
               
               if (koord.dx == maaliX)
               {
                  break;
               }
            }
         }
         
         else
         {
            tempX = tempX * TUHAT;
            kkY = abs(tempX) / abs(tempY);
            kkX = 0;
            
            Suunta koord = {0,0};
            int tulos = 0;
            int jako = 0;
            int jaannos = 0;
            
            while(true)
            {
               tulos = loop * kkY;
               jako = tulos / TUHAT;
               jaannos = tulos % TUHAT;
               
               if (abs(jaannos) >= VIISISATAA)
               {
                  jako++;
               }
               
               koord.dy = paikkaY - loop;
               koord.dx = paikkaX + jako;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
               
               ++loop;
               
               if (koord.dy == maaliY)
               {
                  break;
               }
            }
         }
      }
      
      if ((tempX < 0) and (tempY < 0))
      {
         if (abs(tempY) < abs(tempX)) 
         {
            tempY = abs(tempY) * TUHAT;
            kkX = tempY / abs(tempX);
            kkY = 0;
            
            while (true)
            {
               Suunta koord = {0,0};
               int tulos = 0;
               int jako = 0;
               int jaannos = 0;
               
               tulos = loop * kkX;
               jako = tulos / TUHAT;
               jaannos = tulos % TUHAT;
               
               if (jaannos >= VIISISATAA)
               {
                  jako++;
               }
               
               koord.dx = paikkaX - loop;
               koord.dy = paikkaY - jako;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
               
               ++loop;
               
               if (maaliX == koord.dx)
               {
                  break;
               }
            }
         }
         
         else
         {
            tempX = abs(tempX) * TUHAT;
            kkY = tempX / abs(tempY);
            kkX = 0;
            
            while (true)
            {
               Suunta koord = {0,0};
               int tulos = 0;
               int jako = 0;
               int jaannos = 0;
               
               tulos = loop * kkY;
               jako = tulos / TUHAT;
               jaannos = tulos % TUHAT;
               
               if (jaannos >= VIISISATAA)
               {
                  jako++;
               }
               
               koord.dy = paikkaY - loop;
               koord.dx = paikkaX - jako;
               
               if (onkoKartalla(lauta, koord.dx, koord.dy))
               {
                  nuoli.talletaReitti(koord.dx, koord.dy);
               }
               else
               {
                  break;
               }
               
               ++loop;
               
               if (maaliY == koord.dy)
               {
                  break;
               }
            }
         }
      }
   }
}

//Funktio joka poistaa turhat nuolet

void poistaTurhat(vector<Nuoli>& nuolet)
{
   vector<Nuoli>::iterator paikka;
   paikka = nuolet.begin();
   
   while (paikka != nuolet.end())
   {
      if (!paikka->piirretaanko())
      {
         paikka = nuolet.erase(paikka);
      }
      else
      {
         ++paikka;
      }
   }
}

void laskeNuolenvahinko(Nuoli nuoli, vector<Sankari>& innoccius,
                        vector<Sankari>& tyrannid, int paikkaY, int paikkaX, 
                        vector<vector<KartanSolu> >& lauta)
{
   int puolustaja = 0;
   int muunneltuH = 0;
   int muunneltuP = 0;
   int voittoH = 0;
   int voittoP = 0;
   int kukkulaP = 0;
   int voimaH = 0;
   int voimaP = 0;
   int elamaH = 0;
   int elamaP = 0;
   int vahinkoH = 0;
   int vahinkoP = 0;
   int puolustusP = 0;
   int kerroinP = 0;
   int arvottu = 0;
   const int KAKSIKYMMENTA = 20;
   const int SATA = 100;
   const int YSIYSI = 99;
   puolustaja = lauta.at(paikkaY).at(paikkaX).jarjestys;
      
   voimaH = nuoli.palautaVoima();
   elamaH = SATA;
   muunneltuH = 
     (((PERUSVOIMA * SATA) + ((PERUSVOIMA * SATA) * voimaH)) * elamaH);
   muunneltuH = muunneltuH / SATA;

   if (lauta.at(paikkaY).at(paikkaX).puoli == INNOCCIUS)
   {
      if (lauta.at(paikkaY).at(paikkaX).maasto == KUKKULA)
      {
         kukkulaP = innoccius.at(puolustaja).palautaKukkula();
      }
      if (innoccius.at(puolustaja).palautaLinnoitus())
      {
         puolustusP = innoccius.at(puolustaja).palautaPuolustus();
      }
      
      voimaP = innoccius.at(puolustaja).palautaVoima();
      elamaP = innoccius.at(puolustaja).palautaElama();
      kerroinP = voimaP + kukkulaP + puolustusP;
      
      if (kerroinP < 0)
      {
         kerroinP = SATA - kerroinP;
         muunneltuP = (((PERUSVOIMA * SATA) / kerroinP) * elamaP) / SATA;
      }
      else
      {
         muunneltuP = 
           (((PERUSVOIMA * SATA) + ((PERUSVOIMA * SATA) * kerroinP)) * elamaP);
         muunneltuP = muunneltuP / SATA;
      }
   }
   
   if (lauta.at(paikkaY).at(paikkaX).puoli == TYRANNID)
   {
      if (lauta.at(paikkaY).at(paikkaX).maasto == KUKKULA)
      {
         kukkulaP = tyrannid.at(puolustaja).palautaKukkula();
      }
      if (tyrannid.at(puolustaja).palautaLinnoitus())
      {
         puolustusP = tyrannid.at(puolustaja).palautaPuolustus();
      }
      
      voimaP = tyrannid.at(puolustaja).palautaVoima();
      elamaP = tyrannid.at(puolustaja).palautaElama();
      kerroinP = voimaP + kukkulaP + puolustusP;
      
      if (kerroinP < 0)
      {
         kerroinP = SATA - kerroinP;
         muunneltuP = (((PERUSVOIMA * SATA) / kerroinP) * elamaP) / SATA;
      }
      else
      {
         muunneltuP = 
           (((PERUSVOIMA * SATA) + ((PERUSVOIMA * SATA) * kerroinP)) * elamaP);
         muunneltuP = muunneltuP / SATA;
      }
   }
   voittoH = ((muunneltuH  * SATA) / (muunneltuH + muunneltuP));
   voittoP = SATA - voittoH;
   
   vahinkoH = (KAKSIKYMMENTA * (3 * muunneltuH + muunneltuP) / 
               (3 * muunneltuP + muunneltuH));
   
   vahinkoP = (KAKSIKYMMENTA * (3 * muunneltuP + muunneltuH) / 
               (3 * muunneltuH + muunneltuP));
   
   arvottu = arpa(0,YSIYSI);
   
   if (arvottu < voittoH)
   {
      if (lauta.at(paikkaY).at(paikkaX).puoli == INNOCCIUS)
      {
         innoccius.at(puolustaja).vahennaElamaa(vahinkoH);
         if (innoccius.at(puolustaja).palautaElama() == 0)
         {
            lauta.at(paikkaY).at(paikkaX).puoli = EISANKARIA;
            lauta.at(paikkaY).at(paikkaX).jarjestys = 0;
            if (innoccius.at(puolustaja).onkoKruunu())
            {
               lauta.at(paikkaY).at(paikkaX).kuninkaidenKruunu = true;
            }
            pudotaBonukset(lauta.at(paikkaY).at(paikkaX), 
                           innoccius.at(puolustaja));
         }
      }
      if (lauta.at(paikkaY).at(paikkaX).puoli == TYRANNID)
      {
         tyrannid.at(puolustaja).vahennaElamaa(vahinkoH);
         if (tyrannid.at(puolustaja).palautaElama() == 0)
         {
            lauta.at(paikkaY).at(paikkaX).puoli = EISANKARIA;
            lauta.at(paikkaY).at(paikkaX).jarjestys = 0;
            
            if (tyrannid.at(puolustaja).onkoKruunu())
            {
               lauta.at(paikkaY).at(paikkaX).kuninkaidenKruunu = true;
            }
            pudotaBonukset(lauta.at(paikkaY).at(paikkaX), 
                           tyrannid.at(puolustaja));
         }
      }
   }
}

void siirraNuolta(Nuoli& nuoli, vector<vector<KartanSolu> >& lauta,
                  vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                  bool kotiruutu)
{
   int paikkaX = 0;
   int paikkaY = 0;
   
   bool maali = false;
   
   nuoli.koordinaatit(paikkaX, paikkaY, maali);
   
   if (kotiruutu == false)
   {
      if (maali == true)
      {
         nuoli.paivitaPiirto(false);
      }
      
      if (not onkoKartalla(lauta, paikkaX, paikkaY))
      {
         nuoli.paivitaPiirto(false);
      }
      
      if (nuoli.piirretaanko())
      {
         if (lauta.at(paikkaY).at(paikkaX).puoli != EISANKARIA)
         {
            laskeNuolenvahinko(nuoli, innoccius, tyrannid, paikkaY, paikkaX,
                               lauta);
            nuoli.paivitaPiirto(false);
         }
      }
      
      if (nuoli.piirretaanko())
      {
         lauta.at(paikkaY).at(paikkaX).nuoli = true;
         nuoli.paivitaPaikka(paikkaX, paikkaY);
      }
   }
}

//AMMU-komennon mukaisen toiminnan toteuttava funktio. Tarkistaa 
//ensin ett‰ ampumiseen vaadittavat toimintapisteet on j‰ljell‰ ja
//t‰m‰n j‰lkeen luo kolme nuoli-oliota, m‰‰r‰‰ niille osumapisteen
//ja piirtomerkin ja laskee niiden lentoradan.
void ammu(vector<vector<KartanSolu> >& lauta, vector<Sankari>& innoccius,
          vector<Sankari>& tyrannid, Puoli pelaaja, int sankari,
          int koordX, int koordY, vector<Nuoli>& nuolet, bool& vaihda)
{
   int tarkkuus = 0;
   int ammukset = 0;
   
   if (pelaaja == INNOCCIUS)
   {
      if (innoccius.at(sankari).palautaToimintapisteet() < 3)
      {
         cerr << "Virhe: Liian v‰h‰n toimintapisteit‰." << endl;
      }
      else
      {
         innoccius.at(sankari).muutaToimintapisteita(3);
         ammukset = innoccius.at(sankari).palautaAmmukset();
         tarkkuus = innoccius.at(sankari).palautaTarkkuus();
         for (int loop = 0; loop < ammukset; ++loop)
         {
            Nuoli temp;
            int kkX = 0;
            int kkY = 0;
            int sijaintiX = 0;
            int sijaintiY = 0;
            int voima = innoccius.at(sankari).palautaVoima();
            int maaliX = koordX;
            int maaliY = koordY;
            char merkki = ' ';
            
            etsiPaikat(lauta, INNOCCIUS, sankari, sijaintiX, sijaintiY);
            laskeOsumapiste(maaliX, maaliY, tarkkuus);
            laskeReitti(maaliX, maaliY, sijaintiX, sijaintiY, kkX, kkY, temp,
                        lauta);
            maaraaMerkki(maaliX, maaliY, sijaintiX, sijaintiY, merkki);
            temp.paivitaTiedot(maaliX, maaliY, sijaintiX, sijaintiY, voima,
                               merkki);
            siirraNuolta(temp, lauta, innoccius, tyrannid, true);
            
            siirraNuolta(temp, lauta, innoccius, tyrannid, false);
            siirraNuolta(temp, lauta, innoccius, tyrannid, false);
            siirraNuolta(temp, lauta, innoccius, tyrannid, false);
            siirraNuolta(temp, lauta, innoccius, tyrannid, false);
            siirraNuolta(temp, lauta, innoccius, tyrannid, false);
  
            nuolet.push_back(temp);
         }
      }
      
      if (innoccius.at(sankari).palautaToimintapisteet() == 0)
      {
         vaihda = true;
      }
   }
   else if (pelaaja == TYRANNID)
   {
      if (tyrannid.at(sankari).palautaToimintapisteet() < 3)
      {
         cerr << "Virhe: Liian v‰h‰n toimintapisteit‰." << endl;
      }
      else
      {
         tyrannid.at(sankari).muutaToimintapisteita(3);
         ammukset = tyrannid.at(sankari).palautaAmmukset();
         tarkkuus = tyrannid.at(sankari).palautaTarkkuus();
         for (int loop = 0; loop < ammukset; ++loop)
         {
            Nuoli temp;
            
            int kkX = 0;
            int kkY = 0;
            int sijaintiX = 0;
            int sijaintiY = 0;
            int voima = tyrannid.at(sankari).palautaVoima();
            int maaliX = koordX;
            int maaliY = koordY;
            char merkki = ' ';
            
            etsiPaikat(lauta, TYRANNID, sankari, sijaintiX, sijaintiY);
            laskeOsumapiste(maaliX, maaliY, tarkkuus);
            laskeReitti(maaliX, maaliY, sijaintiX, sijaintiY, kkX, kkY, temp,
                        lauta);
            maaraaMerkki(maaliX, maaliY, sijaintiX, sijaintiY, merkki);
            temp.paivitaTiedot(maaliX, maaliY, sijaintiX, sijaintiY, voima,
                               merkki);
            siirraNuolta(temp, lauta, innoccius, tyrannid, true);
            
            siirraNuolta(temp, lauta, innoccius, tyrannid, false);
            siirraNuolta(temp, lauta, innoccius, tyrannid, false);
            siirraNuolta(temp, lauta, innoccius, tyrannid, false);
            siirraNuolta(temp, lauta, innoccius, tyrannid, false);
            siirraNuolta(temp, lauta, innoccius, tyrannid, false);
  
            nuolet.push_back(temp);
         }
      }
      
      if (tyrannid.at(sankari).palautaToimintapisteet() == 0)
      {
         vaihda = true;
      }
   }
}

//Funktio joka tulkitsee komentotulkille syˆtetyn syˆtteen. 
//Funktio tarkistaa komennon ja sille annetut parametrit ja
//tulostaa oikean virheilmoituksen mik‰li tarpeen.
//Jos kaikki on kunnossa funktio kutsuu komennon mukaista
//aliohjelmaa jolloin komennon mukainen toiminnallisuus suoritetaan. 
void tulkitseSyote(string& komento, bool& vaihda, bool& lopeta, 
                   vector<vector<KartanSolu> >& lauta, 
                   vector<Sankari>& innoccius, vector<Sankari>& tyrannid, 
                   Puoli pelaaja, Tila debug, unsigned int sankari,
                   vector<Nuoli>& nuolet)
{
   string parametrit = "";
   vector<string> parsitut;
   
   pienennaKirjaimet(komento);
   etsiParametrit(komento, parametrit);
   parsiParametrit(parametrit, parsitut);
   
   bool tunnistettiin = false;
   
   if (komento.size() == 0)
   {
      tunnistettiin = true;
   }
   
   for (unsigned int loop = 0; loop < 7; ++loop)
   {
      if (loop <= 2)
      {
         if (komento == LIIKU[loop]) //LIIKU-komento
         {
            if (parsitut.size() > 2)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else if (parsitut.size() < 2)
            {
               cerr << "Virhe: Liian v‰h‰n parametreja." << endl;
            }
            else
            {
               int suunta = 0;
               int maara = 0;
               
               if (!tarkistaMaara(maara, parsitut.at(1), false))
               {
                  cerr << "Virhe: " << parsitut.at(1);
                  cerr << " ei ole tulkittavissa kokonaislukuna." <<  endl;
               }
               else if (!tarkistaSuunta(suunta, parsitut.at(0)))
               {
                  cerr << "Virhe: " << parsitut.at(0);
                  cerr << " ei ole tulkittavissa suuntana." << endl;
               }
               else
               {
                  liiku(lauta, pelaaja, sankari, suunta, maara, debug,
                        innoccius, tyrannid, vaihda, nuolet);
               }
            }
            
            tunnistettiin = true;
         }
         
         if (komento == AMMU[loop]) //AMMU-komento
         {
            if (parsitut.size() > 2)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else if (parsitut.size() < 2)
            {
               cerr << "Virhe: Liian v‰h‰n parametreja." << endl;
            }
            else
            {
               int kohdeX = 0;
               int kohdeY = 0;
               bool virhe = false;
               
               if (!tarkistaMaara(kohdeX, parsitut.at(0), true))
               {
                  cerr << "Virhe: " << parsitut.at(0);
                  cerr << " ei ole tulkittavissa kokonaislukuna." <<  endl;
                  virhe = true;
               }
               else if (!tarkistaMaara(kohdeY, parsitut.at(1), true))
               {
                  cerr << "Virhe: " << parsitut.at(1);
                  cerr << " ei ole tulkittavissa kokonaislukuna." <<  endl;
               }
               else
               {
                  ammu(lauta, innoccius, tyrannid, pelaaja, sankari, kohdeX,
                       kohdeY, nuolet, vaihda);
               }
            }
            
            tunnistettiin = true;
         }
         
         if (komento == APUA[loop]) //APUA-komento
         {
            if (parametrit.size() != 0)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else
            {
               aputeksti();
            }
            
            tunnistettiin = true;
         }
      }
      
      if (loop <= 3)
      {
         if (komento == HELP[loop]) //HELP-komento
         {
            if (parametrit.size() != 0)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else
            {
               aputeksti();
            }
            
            tunnistettiin = true;
         }
         
         if (komento == QUIT[loop]) //QUIT-komento
         {
            if (parametrit.size() != 0)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else
            {
               lopeta = true;
            }
            
            tunnistettiin = true;
         }
      }
      
      if (loop <= 4)
      {
         if (komento == ODOTA[loop]) //ODOTA-komento
         {
            if (parametrit.size() != 0)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else
            {
               vaihda = true;
            }
            
            tunnistettiin = true;
         }
         
         if (komento == LOPETA[loop]) //LOPETA-komento
         {
            if (parametrit.size() != 0)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else
            {
               lopeta = true;
            }
            
            tunnistettiin = true;
         }
      }
      
      if (loop <= 5)
      {
         if (komento == KARTTA[loop]) //KARTTA-komento
         {
            if (parametrit.size() != 0)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else
            {
               paivitaNakyvyys(lauta, debug, innoccius, tyrannid, pelaaja);
               tulostaKartta(lauta, pelaaja, sankari, innoccius, tyrannid, 
                             nuolet);
            }
            
            tunnistettiin = true;
         }
         
         if (komento == LINNOITTAUDU[loop]) //LINNOITA-komento
         {
            if (parametrit.size() != 0)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else
            {
               linnoittaudu(innoccius, tyrannid, pelaaja, sankari, vaihda);
            }
            
            tunnistettiin = true;
         }
         
         if (komento == TIEDOT[loop]) //TIEDOT-komento
         {
            if (parametrit.size() != 0)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else
            {
               tulostaTiedot(innoccius, tyrannid, pelaaja, lauta);
            }
            
            tunnistettiin = true;
         }
      }
   
      if (loop <= 6)
      {
         if (komento == PARANNA[loop]) //PARANNA-komento
         {
            if (parametrit.size() != 0)
            {
               cerr << "Virhe: Liikaa parametreja." << endl;
            }
            else
            {
               paranna(innoccius, tyrannid, pelaaja, sankari, vaihda);
            }
            
            tunnistettiin = true;
         }
      }
   }
   
   if (tunnistettiin != true)
   {
      cerr << "Virhe: Tuntematon komento." << endl;
   }
}
