##################################################################
###															   ###
###			A Quest for the Crown							   ###
###															   ###
###			Small CLI-based adventure game					   ###
###			Hannu Ranta										   ###
###															   ###
##################################################################



Command line parameters: 
------------------------------------------------------------------
-k             Mapfile
Parameters:	   Filename for mapfile 
   
-s             Seed number definition
Parameters:	   Seed number
   
-h or --help   Help 
Parameters:	   -
   
--debug        Debug mode: Fog of War is disabled. 
Parameters:	   -
------------------------------------------------------------------

Game commands (commands are in finnish):
------------------------------------------------------------------
   LIIKU <direction> <amount> (1 action points)
   Moves a hero to direction given by numbers below a given amount of squares.
   7 8 9
   4   6
   1 2 3
   
   AMMU <x> <y> (3 action points)
   Shoots 3 arrows towards the given coordinates
      
   LINNOITA (1 action point/command)
   Fortifyes a hero (defense is increased)
      
   KARTTA
   Prints a map
   
   TIEDOT
   Prints an information of all the heros
         
   ODOTA
   Ends game turn
      
   PARANNA (3 action points/command)
   Heals a hero 20 life points
   
   APUA/HELP
   Prints a help dialog (in finnish)
 
   LOPETA/QUIT
   Ends game
   ------------------------------------------------------------------