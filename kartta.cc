//###################################################################
//                                                                 ##
// Hannu Ranta				                                       ##
//                                                                 ##
// kartta-rajapinnan toteutus                                      ##
//                                                                 ##
// ##################################################################

//määritellään include-direktiivit.
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <fstream>

//linkataan otsikkotiedosto
#include "kartta.hh"
#include "tiedot.hh"
#include "apufunktiot.hh"
#include "sankari.hh"

//avataan oletusnimiavaruus käyttöön
using namespace std;

//Funktio joka tarkistaa saako karttatiedostoa avattua
//ja palauttaa tämän mukaisesti totuusarvon.
bool saakoAvattua(string& kartta, ifstream& virta)
{
   virta.open(kartta.c_str());
   
   if (not virta)
   {
      cerr << "Virhe: Tiedostoa " << kartta << " ei saatu avattua." << endl;
      return false;
   }
   
   return true;
}

//Funktio joka tarkistaa kartan mitat ja niiden oikeellisuuden
//sekä sen onko kartta tiedostossa annettujen mittojen mukainen.
bool tarkistaMitat(string& rivi, unsigned int& leveys, unsigned int& korkeus)
{
   bool tieto_1 = false;
   bool tieto_2 = false;
   bool vali_1 = false;
   bool vali_2 = false;
   
   for (unsigned int loop = 0; loop < rivi.size(); ++loop)
   {
      if ((not isdigit(rivi[loop])) and (not isspace(rivi[loop])))
      { 
         cerr << "Virhe: Virheellinen karttatiedosto." << endl;
         return false;
      }
      
      if ((isdigit(rivi[loop])) and (tieto_1 == false))
      {
         tieto_1 = true;
      }
      
      if ((isspace(rivi[loop])) and (tieto_1 == true))
      {
         vali_1 = true;
      }
      
      if ((isdigit(rivi[loop])) and (tieto_1 == true) and (vali_1 == true))
      {
         tieto_2 = true;
      }
      
      if ((isspace(rivi[loop])) and (tieto_2 == true))
      {
         vali_2 = true;
      }
      
      if ((isdigit(rivi[loop])) and (vali_2 == true))
      {
         cerr << "Virhe: Virheellinen karttatiedosto." << endl;
         return false;
      }
   }
   
   if (tieto_2 == false)
   {
      cerr << "Virhe: Virheellinen karttatiedosto." << endl;
      return false;
   }
   
   stringstream virta;
   virta << rivi;
   
   virta >> leveys;
   virta >> korkeus;
   
   return true;
}

//Funktio joka laskee kartalta camelotit, kruunut ja sankarit
//niiden piirtomerkkien mukaisesti.
bool tulkitseMerkit(string& temp, int& kruunu, int& camelot,
                    int& sankarit_innoccius, int& sankarit_tyrannid)
{
   for (unsigned int loop = 0; loop < temp.size(); ++loop)
   {
      bool laillinen = false;
      
      for (unsigned int loop_2 = 0; loop_2 < sizeof(ALKUMERKIT); ++loop_2)
      {
         if (temp[loop] == ALKUMERKIT[loop_2])
         {
            laillinen = true;
         }
      }
      
      if (laillinen == false)
      {
         return false;
      }
      
      if (temp[loop] == ALKUMERKIT[0])
      {
            ++kruunu;
      }
         
      if (temp[loop] == ALKUMERKIT[1])
      {
         ++camelot;
      }
      
      if (temp[loop] == ALKUMERKIT[5])
      {
         ++sankarit_innoccius;
      }
         
      if (temp[loop] == ALKUMERKIT[6])
      {
         ++sankarit_tyrannid;
      }
   }
   
   return true;
}

//Funktio joka tarkistaa karttatiedoston oikeellisuuden ja
//palauttaa totuusarvona oliko kartta oikeanlainen
bool tarkistaKartta(string& kartta, unsigned int& leveys, 
                    unsigned int& korkeus)
{
   ifstream data;
   string alkurivi = "";
   int camelot = 0;
   int kruunu = 0;
   int sankarit_innoccius = 0;
   int sankarit_tyrannid = 0;
   unsigned int kierros = 0;
   
   if (saakoAvattua(kartta, data) == false)
   {
      return false;
   }
   
   getline(data, alkurivi);
   
   if (tarkistaMitat(alkurivi, leveys, korkeus) == false)
   { 
      return false;
   }
   
   while (true)
   {
      string temp = "";   
      getline(data, temp);
      
      if (tulkitseMerkit(temp, kruunu, camelot, sankarit_innoccius,
                         sankarit_tyrannid) == false)
      {
         cerr << "Virhe: Virheellinen karttatiedosto." << endl;
         return false;
      }
      
      if (data.eof())
      {
         break;
      }
      
      if (temp.size() != leveys)
      {
         cerr << "Virhe: Virheellinen karttatiedosto." << endl;
         return false;
      }
 
      ++kierros;
   }
   
   if ((kruunu != 1) or (camelot < 1) 
       or ((sankarit_innoccius < 1) and (sankarit_tyrannid < 1))
       or (sankarit_innoccius > 10) or (sankarit_tyrannid > 10)
       or (kierros != korkeus))
   {
      cerr << "Virhe: Virheellinen karttatiedosto." << endl;
      return false;
   }
   
   return true;
}

//Funktio joka lukee tiedot karttatiedostosta lauta-vectoriin
//ja alustaa jokaisen kartan solun tiedot oikeiksi
void alustaLauta(vector<vector<KartanSolu> >& lauta, string& kartta, 
                 vector<Sankari>& innoccius, vector<Sankari>& tyrannid,
                 Tila debug)
{
   string rivi = "";
   ifstream data;
   vector<KartanSolu> sarake;
   
   saakoAvattua(kartta, data);
   getline(data, rivi);
   
   while (!data.eof())
   {
      getline(data, rivi);
      if (rivi.size() != 0)
      {
         for (unsigned int loop = 0; loop < rivi.size(); ++loop)
         {
            KartanSolu temp; 
            temp.kuninkaidenKruunu = false; 
            temp.maasto = TASANKO;  
            temp.innoccius = TUTKIMATON; 
            temp.tyrannid = TUTKIMATON;
            temp.puoli = EISANKARIA;
            temp.jarjestys = 0;
            temp.nuoli = false;
            
            if (debug == ON)
            {
               temp.innoccius = NAKOKENTASSA;
               temp.tyrannid = NAKOKENTASSA;
            }
            
            if (rivi[loop] == ALKUMERKIT[0])
            {
               temp.kuninkaidenKruunu = true;
            }
            
            if (rivi[loop] == ALKUMERKIT[1])
            {
               temp.maasto = CAMELOT;
            }
            
            if (rivi[loop] == ALKUMERKIT[2])
            {
               temp.maasto = VUORI;
            }
            
            if (rivi[loop] == ALKUMERKIT[3])
            {
               temp.maasto = KUKKULA;
            }
            
            if (rivi[loop] == ALKUMERKIT[5])
            {
               innoccius.push_back(Sankari());
               temp.innoccius = NAKOKENTASSA;
               temp.puoli = INNOCCIUS;
               temp.jarjestys = (innoccius.size() - 1);
            }
            
            if (rivi[loop] == ALKUMERKIT[6])
            {
               tyrannid.push_back(Sankari());
               temp.tyrannid = NAKOKENTASSA;
               temp.puoli = TYRANNID;
               temp.jarjestys = (tyrannid.size() - 1);
            }
            
            if (rivi[loop] == ALKUMERKIT[7])
            {
               Bonus tempBonus = TYHJA;
               int arvottu = 0;
               arvottu = arpa(0,6);
               switch (arvottu)
               { 
                case 0:
                  tempBonus = JOUSI;
                  temp.bonus.push_back(tempBonus);
                  break;
                case 1:
                  tempBonus = AMMUS;
                  temp.bonus.push_back(tempBonus);
                  break;
                case 2:
                  tempBonus = VOIMA;
                  temp.bonus.push_back(tempBonus);
                  break;
                case 3:
                  tempBonus = KUKKULABONUS;
                  temp.bonus.push_back(tempBonus);
                  break;
                case 4:
                  tempBonus = PUOLUSTUS;
                  temp.bonus.push_back(tempBonus);
                  break;
                case 5:
                  tempBonus = TOIMINTAPISTE;
                  temp.bonus.push_back(tempBonus);
                  break;
                case 6:
                  tempBonus = NAKO;
                  temp.bonus.push_back(tempBonus);
                  break;
                default:
                  tempBonus = TYHJA;
                  temp.bonus.push_back(tempBonus);
                  break;
               }
            }
            sarake.push_back(temp);
         }
         lauta.push_back(sarake);
         sarake.clear();
      }  
   }
}
