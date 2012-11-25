//###############################################
//                                             ##
//  Hannu Ranta 			                   ##
//                                             ##
//  Sankari-luokan toteutus                    ##
//                                             ##  
//###############################################

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include "sankari.hh"
#include "tiedot.hh"

using namespace std;

//Oletusrakentaja Sankarille
Sankari::Sankari(): elama_(PERUSELAMA), toimintapisteet_(PERUSTOIMINTA), 
                    voimabonus_(PERUSBONUS), puolustusbonus_(PERUSBONUS), 
                    kukkulabonus_(PERUSBONUS), nako_(PERUSNAKO), 
                    tarkkuus_(PERUSJOUSI), ammukset_(PERUSNUOLET), 
                    koordX_(0),koordY_(0),linnoitettu_(false), kruunu_(false)
{
}

//Funktio joka tulostaa sankarin 
//sis‰isiin tietorakenteisiin talletetut tiedot kuten
//sankarin elaman ja toimintapisteet.
void Sankari::tulostaTiedot(ostream& virta, bool maella)
{
   if (elama_ > 0)
   { 
      virta << " (" << koordX_ << ", " << koordY_ << ") ";
      virta <<  "terveys " << elama_ << "/100" << endl;
      virta << "Toimintapisteit‰: " << toimintapisteet_ << endl;
      virta << "Voimabonus: " << voimabonus_ << endl;
      virta << "Puolustusbonus: " << puolustusbonus_ << endl;
      virta << "Kukkulabonus: " << kukkulabonus_ << endl;
      if (maella == true)
      {
         virta << "N‰kˆkyky: " << (nako_ + 1) <<  endl;
      }
      else
      {
         virta << "N‰kˆkyky: " << nako_  <<  endl;
      }
      
      virta << "Jousen tarkkuus: " << tarkkuus_ << endl;
      virta << "Ammuksia: " << ammukset_ << endl;
      
      if (linnoitettu_ == true)
      {
         virta << "Linnoitettu" << endl;
      }
      
      if (kruunu_ == true)
      {
         virta << "Kuninkaiden Kruunu!" << endl;
      }
   }
   
   else
   {
      virta << " (" << koordX_ << ", " << koordY_ << ") ";
      virta << "terveys " << elama_ << "/100" << endl;
   }
}

//Funktio joka p‰ivitt‰‰ sankarin sis‰iset koordinaatit
//parametrina syˆtettyihin
void Sankari::paivitaKoordinaatit(int paikkaX, int paikkaY)
{
   koordX_ = paikkaX;
   koordY_ = paikkaY;
}

//Funktio joka palauttaa sankarin n‰kˆs‰teen
int Sankari::palautaNakosade()
{
   return nako_;
}

//Funktio joka palauttaa sankarin el‰m‰n
int Sankari::palautaElama()
{
   return elama_;
}

//Funktio joka v‰hent‰‰ sankarin el‰m‰pisteit‰
void Sankari::vahennaElamaa(int maara)
{
   elama_ = elama_ - maara;
   
   if (elama_ < 0)
   {
      elama_ = 0;
   }
}

//Funktio joka palauttaa sankarin toimintapisteet
int Sankari::palautaToimintapisteet()
{
   return toimintapisteet_;
}

//Funktio joka muuttaa sankarin toimintapisteit‰
//parametrina annetun m‰‰r‰n verran
void Sankari::muutaToimintapisteita(int maara)
{
   toimintapisteet_ = toimintapisteet_ - maara;
}

//Funktio joka asettaa toimintapisteet oletukseen
void Sankari::nollaaToimintapisteet()
{
   toimintapisteet_ = 3;
}

//Funktio joka muuttaa sis‰isen kruunu_ muuttujan 
//arvon todeksi
void Sankari::kruunuLoytyi()
{
   kruunu_ = true;
}

//Funktio joka palauttaa sankarin x-koordinaatin
int Sankari::palautaX()
{
   return koordX_;
}

//Funktio joka palauttaa sankarin y-koordinaatin
int Sankari::palautaY()
{
   return koordY_;
}

//Funktio joka palauttaa totuusarvon sen mukaan
//onko sankarilla kruunu hallussa vai ei
bool Sankari::onkoKruunu()
{
   if (kruunu_ == true)
   {
      return true;
   }
   
   return false;
}

//Funktio joka parantaa sankaria 20 pistett‰ ja
//tarkistaa ettei el‰m‰ ylit‰ 100:aa
void Sankari::paranna()
{
   const int KAKSIKYMMENTA = 20;
   const int SATA = 100;
   
   elama_ = elama_ + KAKSIKYMMENTA;
   
   if (elama_ > SATA)
   {
      elama_ = SATA;
   }
}

//Funktio joka palauttaa sankarin ammusten m‰‰r‰n
int Sankari::palautaAmmukset()
{
   return ammukset_;
}

//Funktio joka palauttaa sankarin jousen tarkkuuden
int Sankari::palautaTarkkuus()
{
   return tarkkuus_;
}

//Funktio joka palauttaa sankarin voimabonuksen arvon
int Sankari::palautaVoima()
{
   return voimabonus_;
}

//Funktio joka palauttaa sankarin kukkulabonuksen
int Sankari::palautaKukkula()
{
   return kukkulabonus_;
}

//Funktio joka palauttaa sankarin puolustusbonuksen
int Sankari::palautaPuolustus()
{
   return puolustusbonus_;
}

//Funktio joka palauttaa tiedon onko sankari 
//linnoittautuneena
bool Sankari::palautaLinnoitus()
{
   return linnoitettu_;
}

//Funktio joka linnoittaa sankarin tai
//poistaa linnoituksen parametrin mukaan
void Sankari::linnoita(bool paalle)
{
   linnoitettu_ = paalle;
}

//Funktio joka asettaa sankarin ker‰‰m‰t bonukset
//sankarin sis‰isiin tietoihin
void Sankari::keraaBonus(int jousi, int ammus, int voima, int kukkula,
                         int puolustus, int toiminta, int nako)
{
   tarkkuus_ = tarkkuus_ - jousi;
   if (tarkkuus_ < 0)
   {
      tarkkuus_ = 0;
      ammukset_ = ammukset_ + 1;
   }
   
   ammukset_ = ammukset_ + ammus;
   voimabonus_ = voimabonus_ + voima;
   kukkulabonus_ = kukkulabonus_ + kukkula;
   puolustusbonus_ = puolustusbonus_ + puolustus;
   toimintapisteet_ = toimintapisteet_ + toiminta;
   nako_ = nako_ + nako;
}
