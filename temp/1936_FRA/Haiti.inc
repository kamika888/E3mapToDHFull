#####################
# Country main data #
#####################

country =
{ tag                    = HAI
  puppet				 = USA
  ai_settings			 = { flags = { puppetLevel7 = 1 } }
	manpower               = 0 
	# Resource Reserves 
	energy                 = 240
	metal                  = 120
	rare_materials         = 60
	transports = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
  capital                = 892
  policy =
  { date              = { year = 0 month = january day = 0 }
    democratic        = 1
    political_left    = 4
    free_market       = 1
    freedom           = 1
    professional_army = 1
    defense_lobby     = 2
    interventionism   = 2
  }
  nationalprovinces      = { 892 2673 4277 7172 }
  ownedprovinces         = { 892 2673 4277 7172 }
  controlledprovinces    = { 892 2673 4277 7172 }
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
#Early Agriculture
5700 
#Medicine
5600

# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470
 } 
 inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = CUB value = 30  } 
     relation = {  tag = DOM value = -30  } 
     relation = {  tag = USA value = 100  } 
    } 
   headofstate            = {  type = 9 id = 350001  } 
   headofgovernment       = {  type = 9 id = 350002  } 
   foreignminister        = {  type = 9 id = 350003  } 
   armamentminister       = {  type = 9 id = 350004  } 
   ministerofsecurity     = {  type = 9 id = 350005  } 
   ministerofintelligence = {  type = 9 id = 350006  } 
   chiefofstaff           = {  type = 9 id = 350007  } 
   chiefofarmy            = {  type = 9 id = 350008  } 
   chiefofnavy            = {  type = 9 id = 350009  } 
   chiefofair             = {  type = 9 id = 350010  } 
 
landunit = 
   {  id       = {  type = 17500 id = 53  } 
     name     = "La Grandé Armée du Haiti" 
     location = 892 
     Division = 
     {  id       = {  type = 17500 id = 5301  } 
       name     = "1ère Brigade d'Infanterie Haitien" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
    } 
  } 
 