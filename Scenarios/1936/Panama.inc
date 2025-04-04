#####################
# Country main data #
#####################

country =
{ tag                    = PAN
  puppet				 = USA
  ai_settings			 = { flags = { puppetLevel8 = 1 } }
	# Resource Reserves 
	energy                 = 240
	metal                  = 120
	rare_materials         = 60
	transports = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	manpower               = 0 
  capital                = 888
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 5 
     freedom           = 5 
     free_market       = 1
     professional_army = 1 
     defense_lobby     = 2 
     interventionism   = 3
  }
  nationalprovinces      = { 889 888 723 4286 4287 4288 4289 }
  ownedprovinces         = { 888 723 4286 4287 4288 4289 }
  controlledprovinces    = { 888 723 4286 4287 4288 4289 }
  # ROTW Minor Tech '36
  # Group E 1936 techs
  # ######################
  # GW fighter
   techapps               = {  
#Interwar Fighter  
4500 4510 4520 4530
#Interwar Armoured Car  
2860
#Light Field Artillery  
2290
#SW Tank 
7600 7610
#1916 lgt. Infantry Division  
1010  1020 1030 1040 1050 1060
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 
#1916 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Medicine
5600
# Modern Agriculture
5700 5710 5010
  
#Engineers
1830 1840 
# Basic Construction Engineering
5800 5080 
# Improved Construction Engineering 
5090 
# Land Doctrines WW1 - Entente (default)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Land Doctrines WW2 - none

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 

  } 
  inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = USA value = 175  } 
     relation = {  tag = COL value = 50  } 
    } 
   SpyInfo                = {  country = "PAN" NumberOfSpies = 2  } 
   headofstate            = {  type = 9 id = 405001  } 
   headofgovernment       = {  type = 9 id = 405002  } 
   foreignminister        = {  type = 9 id = 405003  } 
   armamentminister       = {  type = 9 id = 405004  } 
   ministerofsecurity     = {  type = 9 id = 405005  } 
   ministerofintelligence = {  type = 9 id = 405006  } 
   chiefofstaff           = {  type = 9 id = 405007  } 
   chiefofarmy            = {  type = 9 id = 405008  } 
   chiefofnavy            = {  type = 9 id = 405009  } 
   chiefofair             = {  type = 9 id = 405010  } 

}
