//#################################################################
//                                                                 
// Hannu Ranta						                               
//                                                                 
// apufunktiot-rajapinnan toteutus                                 
//                                                                 
// ################################################################

//määritellään include-direktiivit.
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <sstream>

//linkataan otsikkotiedosto
#include "apufunktiot.hh"

//avataan oletusnimiavaruus käyttöön
using namespace std;

//Funktio, joka tulostaa ruudulle tekijän tiedot
void tulostaTekstit()
{
   cout << "### ---------------------------" << endl;
   cout << "###         Hannu Ranta        " << endl;
}

//Funktio, joka tulostaa komentoriviaputekstin käyttäjälle
void tulostaOhje()
{
   cout << endl;
   cout << "###       A quest for the crown.        ###" << endl;
   cout << "-------------------------------------------" << endl;
   cout << "Komentoriville annettavat vivut ja parametrit:"; 
   
   cout << endl << endl << endl;
   
   cout << "-k             Karttatiedoston määritys." << endl << endl;
   cout <<  "Parametrit: Karttatiedoston tiedostonimi." << endl << endl;
   
   cout << "-s             Siemenluvun määritys." << endl << endl;
   cout <<  "Parametrit: Haluttu siemenluku." << endl << endl;
   cout << "-h tai --help  Aputekstin tulostaminen." << endl << endl;
   cout <<  "Parametrit: Ei parametreja." << endl << endl;
   
   cout << "--debug        Debuggausta varten." << endl; 
   cout << "               Jokainen ruutu piirretään," << endl;  
   cout  << "               kuin joku näkisi siihen." << endl << endl; 
   cout  << "Parametrit: Ei Parametreja." << endl;
   cout << "-------------------------------------------" << endl;
}

//Arpa-funktio, jota 
//käytetään pelissä lukujen arvonnan suoritukseen.
int arpa(int ala, int yla)
{
   double sade = rand();
   double rMax = RAND_MAX;
   
   rMax += 1;
   sade = sade * (yla - ala + 1);
   sade = sade / rMax;
   sade = sade + ala;
   
   return static_cast<int>(sade);
}

template <class tietoA, class TietoB>
bool muutaTyyppi(const tietoA &lahde, TietoB *kohde)
{
   stringstream virta;
   virta << lahde;
   virta >> *kohde;
   return virta.good();
}

bool loytyykoOhje(int maara, char **vivut)
{
   string temp = "";
   vector<string> parametrit;
   
   for (int loop = 0; loop < maara; ++loop)
   {
      temp = vivut[loop];
      parametrit.push_back(temp);
   }
   
   for (unsigned int loop = 0; loop < parametrit.size(); ++loop)
   {
      if ((parametrit.at(loop) == "--help") or (parametrit.at(loop) == "-h"))
      { 
         if ((parametrit.at(loop - 1) == "-k") 
             or (parametrit.at(loop - 1) == "-s"))
         { 
            if ((parametrit.at(loop - 2) == "-k") 
                or (parametrit.at(loop - 2) == "-s"))
            {
               tulostaOhje();
               return true;
            }
         }
         
         else
         {
            tulostaOhje();
            return true;
         }
      }
   }
   
   return false;
}

bool onkoDupplikaattivipuja(vector<string>& parametrit)
{
   int kartta = 0;
   int siemenluku = 0;
   int debug = 0;
   
   for (unsigned int loop = 0; loop < parametrit.size(); ++loop)
   {
      if (parametrit.at(loop) == "-k")
      {
         ++kartta;
      }
      
      if (parametrit.at(loop) == "-s")
      {
         ++siemenluku;
      }
      
      if (parametrit.at(loop) == "--debug")
      {
         ++debug;
      }
   }
   
   if ((debug > 1) or (kartta > 1) or (siemenluku > 1))
   {
      return false;
   }
   
   if (kartta == 0)
   {
      return false;
   }
   
   return true;
}  

bool tarkistaVivut(vector<string>& parametrit)
{
   for (unsigned int loop = 1; loop < parametrit.size(); ++loop)
   {
      if (parametrit.at(loop) != "--debug")
      {
         
         if ((parametrit.at(loop) != "-s")
             and (parametrit.at(loop) != "-k"))
         {
            if ((parametrit.at(loop - 1) != "-s")
                and (parametrit.at(loop - 1) != "-k"))
            {
               return false;
            }
         }
      }
   }
   
   for (unsigned int loop = 1; loop < parametrit.size(); ++loop)
   {
      if ((parametrit.at(loop) == "-k") or (parametrit.at(loop) == "-s"))
      {
         if (parametrit.size() <= loop +  1)
         {
            return false;
         }
         
         else if ((parametrit.at(loop + 1) == "--debug") 
                  or (parametrit.at(loop + 1) == "-k")
                  or (parametrit.at(loop + 1) == "-s")
                  or (parametrit.at(loop + 1) == "--help")
                  or (parametrit.at(loop + 1) == "-h"))
         { 
            return false;
         }
      }
   }
   
   return true;
}

bool tarkistaParametrit(int maara, char **vivut, int& siemenluku, 
                        string& kartta, Tila& debug)
{
   string temp = "";
   vector<string> parametrit;
   
   for (int loop = 0; loop < maara; ++loop)
   {
      temp = vivut[loop];
      parametrit.push_back(temp);
   }
   
   if ((onkoDupplikaattivipuja(parametrit) == false)
       or (tarkistaVivut(parametrit) == false))
   {
      cerr << "Virhe: Virheelliset komentoriviparametrit." << endl;
      return false;
   }
   
   for (unsigned int loop = 1; loop < parametrit.size(); ++loop)
   {
      if ((parametrit.at(loop) == "-k") and (parametrit.size() > loop + 1))
      {
         kartta = parametrit.at(loop + 1);
      }
      
      if ((parametrit.at(loop) == "-s") and (parametrit.size() > loop + 1))
      {
         for (unsigned int loop_2 = 0; 
              loop_2 < parametrit.at(loop).size(); ++loop_2)
         {
            if (not isdigit(parametrit.at(loop + 1)[loop_2]))
            { 
               cerr << "Virhe: Virheelliset komentoriviparametrit." << endl;
               return false;
            }
            
            muutaTyyppi(parametrit.at(loop + 1), &siemenluku);
         }
      }
      
      if(parametrit.at(loop) == "--debug")
      {
         debug = ON;
      }
      
   }

   return true;
}
