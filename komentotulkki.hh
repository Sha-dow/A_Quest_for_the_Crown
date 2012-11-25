//###################################################################
//                                                                 ##
// Hannu Ranta				                                       ##
//                                                                 ##
// komentotulkki-rajapinnan otsikkotiedosto, joka m��rittelee      ##
// pelin komentojen tulkitsemiseen ja toteutukseen                 ##
// liittyv�t toiminnot                                             ##
//                                                                 ##
// ##################################################################


#ifndef KOMENTOTULKKI_HH
#define KOMENTOTULKKI_HH

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

#include "tiedot.hh"

using namespace std;

//Funktio joka pienent�� sille sy�tetyn merkkijonon
//kaikki kirjaimet

void pienennaKirjaimet(string& komento);

//Funktio joka parsii parametrina annetusta merkkijonosta 
//komennon parametrit ja sijoittaa ne omaan merkkijonoon.

void etsiParametrit(string& komento, string& parametrit);

//Funktio joka tulostaa komentoriviaputekstin

void aputeksti();

//Funktio joka parsii parametrit erilleen ja sijoittaa ne 
//string-tyyppiseen vektoriin

void parsiParametrit(string& parametrit, vector<string>& parsitut);

//Funktio joka tarkistaa liiku-komennolle parametrina 
//annetun suunnan oikeellisuuden

bool tarkistaSuunta(int& suunta, string& parametri);

//Funktio joka tarkistaa numeerisen parametrin oikeellisuuden

bool tarkistaMaara(int& maara, string& parametri, bool negatiivinen);

//Funktio joka tarkistaa onko parametrina annettu
//koordinaatti kartalla vai ei

bool onkoKartalla(vector<vector<KartanSolu> >& lauta, unsigned int paikkaX, 
                  unsigned int paikkaY);

//Funktio joka laskee sankarin n�k�s�teen.

void laskeNakosade(vector<vector<KartanSolu> >& lauta, int paikkaX,
                   int paikkaY, int sade);

//Funktio joka p�ivitt�� innocciuksen ja tyrannidin
//sankareiden n�k�s�teess� olevat ruudut ja muuttaa
//niiden arvoa siten ett� ne piirret��n oikein

void paivitaNakyvyys(vector<vector<KartanSolu> >& lauta, Tila debug,
                     vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                     Puoli pelaaja);

bool tulostaNuolenmerkki(int paikkaX, int paikkaY, vector<Nuoli>& nuolet);

//Funktio joka tulostaa oikean piirrosmerkin 
//kun ruutu on sankarin n�k�kent�ss�

void tulostaNakokentassa(KartanSolu temp, int koordX, int koordY,
                         vector<Nuoli>& nuolet);

//Funktio joka tulostaa oikean piirrosmerkin kun
//ruutu on sankarin muistissa muttei n�k�kent�ss�

void tulostaMuistissa(KartanSolu temp);

//Funktio joka tarkistaa onko pelin lopputilanne
//saavutettu ja palauttaa sen mukaan totuusarvon.

bool tarkistaLopputilanne(vector<vector<KartanSolu> >& lauta,
                          vector<Sankari>& innoccius, 
                          vector<Sankari>& tyrannid,
                          bool lopeta, vector<Nuoli>& nuolet);

//Funktio joka tulostaa kartan pelaajan senhetkisen n�k�kyvyn mukaan.
//Mik�li debug-vipu on annettu k�ynnistyksess� tulostetaan 
//kartta siten kuin jokainen ruutu olisi n�k�kent�ss� koko ajan.

void tulostaKartta(vector<vector<KartanSolu> >& lauta, Puoli pelaaja,
                   int sankari, vector<Sankari>& innoccius, 
                   vector<Sankari>& tyrannid, vector<Nuoli>& nuolet);

//Etsii sankarin koordinaatit kartalta.

void etsiPaikat(vector<vector<KartanSolu> >& lauta, Puoli pelaaja, int numero,
                int& koordX, int& koordY);

//K�y l�pi kaikki vuorossa olevan pelaajan sankarit ja 
//tulostaa niiden tiedot pelaajalle.

void tulostaTiedot(vector<Sankari>& innoccius, vector<Sankari>& tyrannid, 
                   Puoli pelaaja, vector<vector<KartanSolu> >& lauta);

//Tulostaa aloituksessa vaaditut tyhj�t rivit ja odottaa
//rivinvaihtomerkin sy�tt�mist�.

void tulostaAloitus(Puoli pelaaja);

//Laskee pelaajan liikesuunnan mukaan koordinaatit joihin pelaaja 
//yritt�� liikkua.

void laskeKoordinaatit(int suunta, Suunta paikka, Suunta& kohde);

//Tarkistaa l�ytyik� ruudusta johon pelaaja liikkui bonusta.

bool loytyikoBonus(vector<vector<KartanSolu> >& lauta, Suunta kohde);

//Jos Sankari l�ysi bonuksen niin funktio kokoaa sen sankarille talteen.

void kokoaBonus(vector<Bonus>& bonus, Sankari& temp);

//Tarkistaa l�ysik� sankari kruunua.

bool loytyikoKruunu(vector<vector<KartanSolu> >& lauta, Suunta kohde);

//Pudottaa sankarin kantamat bonukset kartan ruutuun
void pudotaBonukset(KartanSolu& ruutu, Sankari sankari);

//Suorittaa taistelun kahden eri sankarin v�lill�. 
//Taistelua jatketaan kunnes toinen sankari kuolee.

void taistelu(vector<Sankari>& innoccius, vector<Sankari>& tyrannid, 
              vector<vector<KartanSolu> >& lauta, Puoli pelaaja, 
              int sankari, Suunta kohde, Suunta paikka);

//Siirt�� sankaria pelaajan haluamaan suuntaan pelaajan
//haluaman m��r�n. Tarkistaa onko siirto mahdollinen ja
//v�hent�� toimintapisteit� liikkeen mukaisen m��r�n.

void liiku(vector<vector<KartanSolu> >& lauta, Puoli pelaaja,
           int sankari, int suunta, int maara, Tila debug,
           vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
           bool& vaihda, vector<Nuoli>& nuolet);

//Parantaa vuorossa olevaa sankaria mik�li toimintapisteet riitt�v�t.

void paranna(vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
             Puoli pelaaja, int sankari, bool& vaihda);

//Purkaa sankarin mahdollisen linnoittautumisen.

void puraLinnoitus(vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                   Puoli pelaaja, int sankari);

//Linnoittaa sankarin.

void linnoittaudu(vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                  Puoli pelaaja, int sankari, bool& vaihda);

//Laskee nuolen oikean osumapisteen sankarin jousen
//tarkuuden ja halutun osumapisteen pohjalta.

void laskeOsumapiste(int& koordX, int& koordY, int tarkkuus);

//M��r�� nuolelle oikean piirtomerkin sen lentosuunnan mukaisesti

void maaraaMerkki(int maaliX, int maaliY, int sijaintiX, int sijaintiY,
                  char& merkki);

//Laskee kaikki nuolen reitille osuvat koordinaatit
//ja p�ivitt�� ne  nuolen sis�iseen vektoriin.

void laskeReitti(int maaliX, int maaliY, int paikkaX, int paikkaY,
                 int& kkX, int& kkY, Nuoli& nuoli, 
                 vector<vector<KartanSolu> >& lauta);

//Poistaa "kuolleet" nuolet

void poistaTurhat(vector<Nuoli>& nuolet);

//Laskee nuolen sankarille aiheuttamat vahingot

void laskeNuolenvahinko(Nuoli nuoli, vector<Sankari>& innoccius,
                        vector<Sankari>& tyrannid, int paikkaY, int paikkaX,
                        vector<vector<KartanSolu> >& lauta);

//Liikuttaa nuolta viisi ruutua oikeaan suuntaan.

void siirraNuolta(Nuoli& nuoli, vector<vector<KartanSolu> >& lauta,
                  vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                  bool kotiruutu);

//Ampuu kolme nuolta mik�li pelaajan toimintapisteet riitt�v�t 
//ja laskee niille oikeat osumapisteet sek� muut tiedot 
//edell� esiteltyjen funktioiden avulla.

void ammu(vector<vector<KartanSolu> >& lauta, vector<Sankari>& innoccius, 
          vector<Sankari>& tyrannid, Puoli pelaaja, int sankari,
          int koordX, int koordY, vector<Nuoli>& nuolet, bool& vaihda);

//Funktio joka vastaa pelin komentotulkin toiminnasta. 
//Tarkistaa muokkausten j�lkeen pelaajan sy�tt�m�n komennon 
//oikeellisuuden ja sille annettujen parametrien oikeellisuuden 
//ja mik�li kaikki on kunnossa toimii n�iden mukaisesti
//kutsuen komennon toteuttavaa aliohjelmaa.

void tulkitseSyote(string& komento, bool& vaihda, bool& lopeta,
                   vector<vector<KartanSolu> >& lauta, 
                   vector<Sankari>& innoccius,
                   vector<Sankari>& tyrannid, Puoli pelaaja, Tila debug,
                   unsigned int sankari, vector<Nuoli>& nuolet);

#endif
