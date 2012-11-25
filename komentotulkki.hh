//###################################################################
//                                                                 ##
// Hannu Ranta				                                       ##
//                                                                 ##
// komentotulkki-rajapinnan otsikkotiedosto, joka määrittelee      ##
// pelin komentojen tulkitsemiseen ja toteutukseen                 ##
// liittyvät toiminnot                                             ##
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

//Funktio joka pienentää sille syötetyn merkkijonon
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

//Funktio joka laskee sankarin näkösäteen.

void laskeNakosade(vector<vector<KartanSolu> >& lauta, int paikkaX,
                   int paikkaY, int sade);

//Funktio joka päivittää innocciuksen ja tyrannidin
//sankareiden näkösäteessä olevat ruudut ja muuttaa
//niiden arvoa siten että ne piirretään oikein

void paivitaNakyvyys(vector<vector<KartanSolu> >& lauta, Tila debug,
                     vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                     Puoli pelaaja);

bool tulostaNuolenmerkki(int paikkaX, int paikkaY, vector<Nuoli>& nuolet);

//Funktio joka tulostaa oikean piirrosmerkin 
//kun ruutu on sankarin näkökentässä

void tulostaNakokentassa(KartanSolu temp, int koordX, int koordY,
                         vector<Nuoli>& nuolet);

//Funktio joka tulostaa oikean piirrosmerkin kun
//ruutu on sankarin muistissa muttei näkökentässä

void tulostaMuistissa(KartanSolu temp);

//Funktio joka tarkistaa onko pelin lopputilanne
//saavutettu ja palauttaa sen mukaan totuusarvon.

bool tarkistaLopputilanne(vector<vector<KartanSolu> >& lauta,
                          vector<Sankari>& innoccius, 
                          vector<Sankari>& tyrannid,
                          bool lopeta, vector<Nuoli>& nuolet);

//Funktio joka tulostaa kartan pelaajan senhetkisen näkökyvyn mukaan.
//Mikäli debug-vipu on annettu käynnistyksessä tulostetaan 
//kartta siten kuin jokainen ruutu olisi näkökentässä koko ajan.

void tulostaKartta(vector<vector<KartanSolu> >& lauta, Puoli pelaaja,
                   int sankari, vector<Sankari>& innoccius, 
                   vector<Sankari>& tyrannid, vector<Nuoli>& nuolet);

//Etsii sankarin koordinaatit kartalta.

void etsiPaikat(vector<vector<KartanSolu> >& lauta, Puoli pelaaja, int numero,
                int& koordX, int& koordY);

//Käy läpi kaikki vuorossa olevan pelaajan sankarit ja 
//tulostaa niiden tiedot pelaajalle.

void tulostaTiedot(vector<Sankari>& innoccius, vector<Sankari>& tyrannid, 
                   Puoli pelaaja, vector<vector<KartanSolu> >& lauta);

//Tulostaa aloituksessa vaaditut tyhjät rivit ja odottaa
//rivinvaihtomerkin syöttämistä.

void tulostaAloitus(Puoli pelaaja);

//Laskee pelaajan liikesuunnan mukaan koordinaatit joihin pelaaja 
//yrittää liikkua.

void laskeKoordinaatit(int suunta, Suunta paikka, Suunta& kohde);

//Tarkistaa löytyikö ruudusta johon pelaaja liikkui bonusta.

bool loytyikoBonus(vector<vector<KartanSolu> >& lauta, Suunta kohde);

//Jos Sankari löysi bonuksen niin funktio kokoaa sen sankarille talteen.

void kokoaBonus(vector<Bonus>& bonus, Sankari& temp);

//Tarkistaa löysikö sankari kruunua.

bool loytyikoKruunu(vector<vector<KartanSolu> >& lauta, Suunta kohde);

//Pudottaa sankarin kantamat bonukset kartan ruutuun
void pudotaBonukset(KartanSolu& ruutu, Sankari sankari);

//Suorittaa taistelun kahden eri sankarin välillä. 
//Taistelua jatketaan kunnes toinen sankari kuolee.

void taistelu(vector<Sankari>& innoccius, vector<Sankari>& tyrannid, 
              vector<vector<KartanSolu> >& lauta, Puoli pelaaja, 
              int sankari, Suunta kohde, Suunta paikka);

//Siirtää sankaria pelaajan haluamaan suuntaan pelaajan
//haluaman määrän. Tarkistaa onko siirto mahdollinen ja
//vähentää toimintapisteitä liikkeen mukaisen määrän.

void liiku(vector<vector<KartanSolu> >& lauta, Puoli pelaaja,
           int sankari, int suunta, int maara, Tila debug,
           vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
           bool& vaihda, vector<Nuoli>& nuolet);

//Parantaa vuorossa olevaa sankaria mikäli toimintapisteet riittävät.

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

//Määrää nuolelle oikean piirtomerkin sen lentosuunnan mukaisesti

void maaraaMerkki(int maaliX, int maaliY, int sijaintiX, int sijaintiY,
                  char& merkki);

//Laskee kaikki nuolen reitille osuvat koordinaatit
//ja päivittää ne  nuolen sisäiseen vektoriin.

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

//Ampuu kolme nuolta mikäli pelaajan toimintapisteet riittävät 
//ja laskee niille oikeat osumapisteet sekä muut tiedot 
//edellä esiteltyjen funktioiden avulla.

void ammu(vector<vector<KartanSolu> >& lauta, vector<Sankari>& innoccius, 
          vector<Sankari>& tyrannid, Puoli pelaaja, int sankari,
          int koordX, int koordY, vector<Nuoli>& nuolet, bool& vaihda);

//Funktio joka vastaa pelin komentotulkin toiminnasta. 
//Tarkistaa muokkausten jälkeen pelaajan syöttämän komennon 
//oikeellisuuden ja sille annettujen parametrien oikeellisuuden 
//ja mikäli kaikki on kunnossa toimii näiden mukaisesti
//kutsuen komennon toteuttavaa aliohjelmaa.

void tulkitseSyote(string& komento, bool& vaihda, bool& lopeta,
                   vector<vector<KartanSolu> >& lauta, 
                   vector<Sankari>& innoccius,
                   vector<Sankari>& tyrannid, Puoli pelaaja, Tila debug,
                   unsigned int sankari, vector<Nuoli>& nuolet);

#endif
