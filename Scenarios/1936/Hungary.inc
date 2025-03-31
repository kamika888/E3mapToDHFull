#####################
# Country main data #
#####################

country =
{ tag                    = HUN
  capital                = 457
	manpower               = 5 
	# Resource Reserves 
	energy                 = 1740
	metal                  = 870
	rare_materials         = 435
	transports = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
  diplomacy =
  { relation =
    { tag        = AUS
      value      = 100
    }
    relation = { tag = CZE value = -50 }
    relation = { tag = ENG value = -50 }
    relation = { tag = FIN value = 75 }
    relation = { tag = FRA value = -70 }
    relation = { tag = GER value = 100 }
    relation = { tag = IRE value = 25 }
    relation = { tag = ITA value = 125 }
    relation = { tag = POL value = 50 }
    relation = { tag = ROM value = 1 }
    relation = { tag = YUG value = 80 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 3 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 3 }
  SpyInfo                = { country = "CZE" NumberOfSpies = 5 }
  SpyInfo                = { country = "AUS" NumberOfSpies = 5 }
  SpyInfo                = { country = "YUG" NumberOfSpies = 2 }
  SpyInfo                = { country = "GER" NumberOfSpies = 3 }
  SpyInfo                = { country = "BUL" NumberOfSpies = 2 }
  SpyInfo                = { country = "ALB" NumberOfSpies = 1 }
  SpyInfo                = { country = "GRE" NumberOfSpies = 1 }
  SpyInfo                = { country = "ROM" NumberOfSpies = 2 }
  SpyInfo                = { country = "ITA" NumberOfSpies = 1 }
  SpyInfo                = { country = "FIN" NumberOfSpies = 1 }
  
  nationalprovinces      = { 456 457 458 491 492 497 490 
							224 1890 2447 1889 1899 2302 
							2616	3369 	3384	498		3386
							3235	3236	3237	3363 
6513 6514 7072 7265 7300 496 428 494
  }
  ownedprovinces         = { 456 457 458 491 492 497
							224 1890 2447
							2616
							3235	3236	3237
6513 6514 7072 7265
  }
  controlledprovinces    = { 456 457 458 491 492 497
							224 1890 2447
							2616
							3235	3236	3237
6513 6514 7072 7265
  }
  claimedprovinces 		= { 2329 2289 2602 495 1403 1449 427 430 499 3233 3230 3231 1887 3232 477 478 476
							493 3370 3385 3382 6512 6561 7261 7054
  }

  # Eastern Minor Tech '36
  # Group C 1936 techs
  # ######################
   techapps               = {
#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Multirole fighter
4300 4310 4320 4330
#ww1 strategic bomber
4800 4810 4820
#ww1 navalbomber
4700 4710
#Interwar Bomber 
4600 4610 4620 4630 4120
#Basic Armoured Car  
2860 2870 2880 2020
#Tankette 
7600 7610 2620 2010 2630 2640
#Great War Heavy Field Artillery 
2290 2300 2310
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Early Anti-Tank Artillery 
#2400
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Great War Infantry Division  
1010  1020 1030 1040 1050 1060 
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960
#Great War Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240
#Mechanized Agriculture 
5700 5710 5010 5020
#Computers & cryptografi
5310 54010 54020 54030 5316 5326
#Manufactoring
5810 5820 5050 5830 5060
#Improved Construction Engineering 
5800 5080 5090 
#Basic Oil Refining 
#5190 

#Great War Hospital System 
14000 14010 14020
#Medicine
5600 5610 5620 5630
#Engineers
1830 1840 1850 1860
# Great War Land Doctrines (central powers)
6500 6510 6530 6550 6590 6600 6620 6650 6670 6610 6680 6690 6700 6710 6910
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
} 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 3 
     free_market       = 1
     freedom           = 7 
     professional_army = 2 
     defense_lobby     = 3 
     interventionism   = 4
  }
inventions = { 3000027 }
   headofstate            = {  type = 9 id = 105001  } 
   headofgovernment       = {  type = 9 id = 105002  } 
   foreignminister        = {  type = 9 id = 105003  } 
   armamentminister       = {  type = 9 id = 105004  } 
   ministerofsecurity     = {  type = 9 id = 105005  } 
   ministerofintelligence = {  type = 9 id = 105208  } #Gusztáv Hennyey
   chiefofstaff           = {  type = 9 id = 105007  } 
   chiefofarmy            = {  type = 9 id = 105008  } 
   chiefofnavy            = {  type = 9 id = 105009  } 
   chiefofair             = {  type = 9 id = 105010  }  
  
   landunit = 
   {  id       = {  type = 20500 id = 1  } 
     name     = "Magyar Kiralyi Honvédség" 
     location = 457 
	Division = 
     {  id       = {  type = 20500 id = 2  } 
       name     = "Magyar Kiralyi Honvédség Föhadiszallas" 
       strength     = 30
       type     = hq
	   model = 2
      } 
     Division = 
     {  id       = {  type = 20500 id = 3  } 
       name     = "1. Gyalogdandar" 
       strength     = 25
       type     = infantry
	   model = 7
      } 
     Division = 
     {  id       = {  type = 20500 id = 4  } 
       name     = "2. Gyalogdandar" 
       strength     = 25
       type     = infantry 
	   model = 7
      } 
     Division = 
     {  id       = {  type = 20500 id = 5  } 
       name     = "3. Gyalogdandar" 
       strength     = 25
       type     = infantry 
	   model = 7
      } 
     Division = 
     {  id       = {  type = 20500 id = 6  } 
       name     = "4. Gyalogdandar" 
       strength     = 25
       type     = infantry 
	   model = 7
      } 
     Division = 
     {  id       = {  type = 20500 id = 7  } 
       name     = "5. Gyalogdandar" 
       strength     = 25
       type     = infantry 
	   model = 7
      } 
     Division = 
     {  id       = {  type = 20500 id = 8  } 
       name     = "6. Gyalogdandar" 
       strength     = 25
       type     = infantry 
	   model = 7
      } 
     Division = 
     {  id       = {  type = 20500 id = 9  } 
       name     = "7. Gyalogdandar" 
       strength     = 25
       type     = infantry 
	   model = 7
      } 
     Division = 
     {  id       = {  type = 20500 id = 10  } 
       name     = "1. Lovasdandar" 
       strength     = 40
       type     = cavalry 
	   model = 8
      } 
     Division = 
     {  id       = {  type = 20500 id = 11  } 
       name     = "2. Lovasdandar" 
       strength     = 40
       type     = cavalry 
	   model = 8
      } 
    } 
   airunit = 
   {  id       = {  type = 20500 id = 12  } 
     name     = "I Légí Hadsereg" 
     location = 457 
     base     = 457 
     Division = 
     {  id       = {  type = 20500 id = 13  } 
       name     = "I.Vadászosztály" 
       type     = interceptor 
       model    = 5
       strength = 30 
      } 
     Division = 
     {  id       = {  type = 20500 id = 14  } 
       name     = "I.Vadászbombázó Osztály" 
       type     = tactical_bomber 
       model    = 4 
       strength = 30 
      } 
    } 
  } 
 