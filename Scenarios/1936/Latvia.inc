#####################
# Country main data #
#####################

country =
{ tag                    = LAT
	energy                 = 420
	metal                  = 210
	rare_materials         = 105 
	transports = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	manpower               = 1 
  capital                = 197
  diplomacy =
  { relation = { tag = ENG value = 65 }
    relation =
    { tag        = EST
      value      = 150
    }
    relation = { tag = FIN value = 90 }
    relation = { tag = FRA value = 65 }
    relation = { tag = GER value = 10 }
    relation =
    { tag        = LIT
      value      = 120
    }
    relation = { tag = POL value = 75 }
    relation = { tag = SOV value = -30 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 1 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 1 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 2 }
  SpyInfo                = { country = "LIT" NumberOfSpies = 2 }
  SpyInfo                = { country = "NOR" NumberOfSpies = 1 }
  SpyInfo                = { country = "EST" NumberOfSpies = 2 }
  SpyInfo                = { country = "POL" NumberOfSpies = 3 }
  SpyInfo                = { country = "FIN" NumberOfSpies = 2 }
  SpyInfo                = { country = "SWE" NumberOfSpies = 2 }
  SpyInfo                = { country = "GER" NumberOfSpies = 1 }
  nationalprovinces      = { 205 204 203 197 202 198
  3283	3284	3285
3289

  }
  ownedprovinces         = { 205 204 203 197 202 198
3283	3284	3285
3289

  }
  controlledprovinces    = { 205 204 203 197 202 198
3283	3284	3285
3289

  }
  # Group D 1936 techs
  # ######################
  # GW fighter
   techapps               = {  
 #Interwar Fighter  
 4500 4510 4520 4530 4540 4550 4010  
 #Basic Armoured Car  
 2860 2870 2880 2020  
 #Great War Heavy Field Artillery 
 2290 2300 2310 2900
#SW Tank 
7600 7610 
#Great War Infantry Division  
1010  1020 1030 1040 1050 1060 1070 1080
#Interbellum Supply 
1910 1920 1930 1940 1950 1960
#Great War Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Mechanized Agriculture 
5700 5710 5010 5020
#Improved Construction Engineering 
5800 5080  
#Mass Production
5810 5820
#Naval Infantry
#1560 1570
#Engineers
1830 1840 1850 

#Short Range Submarine
3610 3620
#Naval Doctrines
8010 8040  
#Medicine
5600 5610
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810
# Land Doctrines WW1 - Entente Line (default)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
} 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 4 
     freedom           = 6 
     free_market       = 1
     professional_army = 5 
     defense_lobby     = 3 
     interventionism   = 3
  }
inventions = { 3000027 }

   headofstate            = {  type = 9 id = 135001  } 
   headofgovernment       = {  type = 9 id = 135002  } 
   foreignminister        = {  type = 9 id = 135003  } 
   armamentminister       = {  type = 9 id = 135004  } 
   ministerofsecurity     = {  type = 9 id = 135005  } 
   ministerofintelligence = {  type = 9 id = 135006  } 
   chiefofstaff           = {  type = 9 id = 135007  } 
   chiefofarmy            = {  type = 9 id = 135008  } 
   chiefofnavy            = {  type = 9 id = 135009  } 
   chiefofair             = {  type = 9 id = 135010  } 
   
   landunit = 
   {  id       = {  type = 24500 id = 1  } 
     location = 197 
     name     = "Latvijas Armija" 
     Division = 
     {  id       = {  type = 24500 id = 2  } 
       name     = "Kurzemes Divizija" 
       type     = infantry 
	   model    = 7
              strength     = 40
	extra = engineer
	brigade_model = 2
      } 
     Division = 
     {  id       = {  type = 24500 id = 3  } 
       name     = "Vidzemes Divizija" 
       type     = infantry
		model    = 7
       extra    = armored_car
	   brigade_model = 1
       strength     = 40
      } 
     Division = 
     {  id       = {  type = 24500 id = 4  } 
       name     = "Zemgales Divizija" 
       type     = infantry
		model    = 7   
       strength     = 40
	extra = artillery
	brigade_model = 6
      } 
     Division = 
     {  id       = {  type = 24500 id = 5  } 
       name     = "Latgales Divizija" 
       type     = infantry 
	   model    = 7
       strength     = 40
      } 
    }

airunit = 
   {  id       = {  type = 24500 id = 8  } 
     location = 197 
     base     = 197 
     name     = "Latvijas Gaisa speki" 
     Division = 
     {  id       = {  type = 24500 id = 9  } 
       name     = "I Aviacijas pulka" 
       type     = interceptor 
       model    = 6
       strength = 60 
      } 
    }

  } 
 
