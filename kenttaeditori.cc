#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <fstream>
#include <cctype>

using namespace std;

int arpa(int ala, int yla)                                        
{  
   double r = rand();                                                           
   double RMAX = RAND_MAX;                                                      
   RMAX += 1;                                                                   
   r = r * (yla - ala + 1);                                                     
   r = r / RMAX;                                                                
   r = r + ala;                                                                 
   return static_cast<int>(r);                                                  
}

int main()
{
   int leveys = 0;
   int korkeus = 0;
   int camelot_max = 0;
   int camelot = 0;
   int innoccius_max = 0;
   int innoccius = 0;
   int tyrannid_max = 0;
   int tyrannid = 0;
   int siemenluku = 0;
   bool kruunu = false;
   string tiedosto = "";
   ofstream virta;
   
   cout << "Syötä leveys: " << endl;
   cin >> leveys;
   cout << "Syötä korkeus: " << endl;
   cin >> korkeus;
   cout << "Syötä Camelot-ruutujen suurin määrä: " << endl;
   cin >> camelot_max;
   cout << "Syötä Innocciuksen sankareitten yläraja: " << endl;
   cin >> innoccius_max;
   cout << "Syötä Tyrannidin sankareitten yläraja: " << endl;
   cin >> tyrannid_max;
   cout << "Syötä haluttu karttatiedoston nimi: " << endl;
   cin >> tiedosto;
   cout << "Syötä arvan siemenluku: " << endl;
   cin >> siemenluku;
   
   srand(siemenluku);
   virta.open(tiedosto.c_str());
   if (not virta)
   {
      cerr << "Tiedostoa ei saatu avattua!" << endl;
      return EXIT_FAILURE;
   }
   
   virta << leveys << " " << korkeus << endl;
   
   for (int loop = 0; loop < korkeus; ++loop)
   {
      string temp = "";
      
      for (int loop_2 = 0; loop_2 < leveys; ++loop_2)
      {
         int arvottu = 0;
         arvottu = arpa(1,25);
         
         if ((arvottu == 1)
             or (arvottu == 2) 
             or (arvottu == 3) 
             or (arvottu == 4) 
             or (arvottu == 4) 
             or (arvottu == 5) 
             or (arvottu == 20)
             or (arvottu == 21)) 
         {
            temp = temp + '.';
         }
         
         if ((arvottu == 6)
             or (arvottu == 7)
             or (arvottu == 8) 
             or (arvottu == 9)
             or (arvottu == 10)
             or (arvottu == 22) 
             or (arvottu == 23)) 
         {
            temp = temp + '~';
         }
         
         if ((arvottu == 11)
             or (arvottu == 12) 
             or (arvottu == 13)
             or (arvottu == 14)
             or (arvottu == 24) 
             or (arvottu == 25))
         {
            temp = temp + '^';
         }
         
         if (arvottu == 15)
         {
            temp = temp + '*';
         }
         
         if (arvottu == 16) 
         {
            if (camelot <= camelot_max)
            {
               ++camelot;
               temp = temp + 'C';
            }
            else
            {
               temp = temp + '.';
            }
         }
         
         if (arvottu == 17) 
         {
            if (kruunu == false)
            {
               kruunu = true;
               temp = temp + '@';
            }
            else
            {
               temp = temp + '.';
            }
         }
         
         if (arvottu == 18) 
         {
            if (innoccius < innoccius_max)
            {
               ++innoccius;
               temp = temp + 'I';
            }
            else
            {
               temp = temp + '.';
            }
         }
         
         if (arvottu == 19) 
         {
            if (tyrannid < tyrannid_max)
            {  
               ++tyrannid;
               temp = temp + 'T';
            }
            else
            {
               temp = temp + '.';
            }
         }
      }
      
      virta << temp << endl;
      temp.clear();
   }
   
   return EXIT_SUCCESS;
}
