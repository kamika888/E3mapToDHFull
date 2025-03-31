
##############################
# Country definition for YEM #
##############################

country =
{ tag                    = YEM
  puppet                 = ENG
  control				 = ENG
  ai_settings			 = { flags = { puppetLevel6 = 1 } }
	# Resource Reserves 
	energy                 = 240
	metal                  = 120
	rare_materials         = 60
	transports = 100
	oil                    = 200 
	supplies               = 200 
	money                  = 10 
	manpower               = 1 
  capital                = 1812
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 4 
     freedom           = 1 
     free_market       = 1
     professional_army = 2 
     defense_lobby     = 3 
     interventionism   = 3 
  }
  nationalprovinces      = { 1812 1813 1814
2855 1815 2857 4185 4186 4235
4174 4187 4188 4189 6566 6567 6568 6569 6570 6571
6924 6925 6565 7450 7274 7275
  }
  ownedprovinces         = { 1812
2855 4185 4186 4235
6924 6925
  }
  controlledprovinces    = { 1812
2855 4185 4186 4235
6924 6925
  }
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
#1916 lgt. Infantry Division  
1010  1020 1030 1040 1050 1060
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960
#1916 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340
#SW Tank 
7600 7610 
#Early Agriculture
5700 
#Medicine
5600
# Land doctrines WWI - Entente line
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Landdoctrine ww2 - none?

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
  } 
  inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = AST value = 150  } 
     relation = {  tag = BHU value = 150  } 
     relation = {  tag = CAN value = 150  } 
     relation = {  tag = ENG value = 150  } 
     relation = {  tag = FRA value = 150  } 
     relation = {  tag = GER value = 1  } 
     relation = {  tag = IRQ value = 125  } 
     relation = {  tag = ITA value = 50  } 
     relation = {  tag = NEP value = 150  } 
     relation = {  tag = NZL value = 150  } 
     relation = {  tag = OMN value = 150  } 
     relation = {  tag = SAF value = 150  } 
     relation = {  tag = SAU value = 125  } 
     relation = {  tag = TUR value = 35  } 
     relation = {  tag = USA value = 100  } 
    } 
   SpyInfo                = {  country = "YEM" NumberOfSpies = 1  } 
   headofstate            = {  type = 9 id = 445001  } 
   headofgovernment       = {  type = 9 id = 445002  } 
   foreignminister        = {  type = 9 id = 445003  } 
   armamentminister       = {  type = 9 id = 445004  } 
   ministerofsecurity     = {  type = 9 id = 445005  } 
   ministerofintelligence = {  type = 9 id = 445006  } 
   chiefofstaff           = {  type = 9 id = 445007  } 
   chiefofarmy            = {  type = 9 id = 445008  } 
   chiefofnavy            = {  type = 9 id = 445009  } 
   chiefofair             = {  type = 9 id = 445010  } 

   landunit = 
   {  id       = {  type = 16800 id = 1  } 
     name     = "Royal Yemenite Army" 
     location = 1812 
     Division = 
     {  id           = {  type = 16800 id = 2  } 
       name         = "Royal Division" 
       type         = cavalry 
	   model    = 7
       strength = 60 
      } 
    } 
  } 
 
