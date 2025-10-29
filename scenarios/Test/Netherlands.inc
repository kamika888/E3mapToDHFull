#####################
# Country main data #
#####################

country =
{ tag                    = HOL
control = ENG
  capital                = 1019
	manpower               = 4 
	# Resource Reserves 
	energy                 = 1740
	metal                  = 870
	rare_materials         = 435
	oil                    = 500 
	supplies               = 500 
	money                  = 40 
	transports             = 250 
	escorts                = 21 
  diplomacy =
  { relation = { tag = BEL value = 150 }
    relation = { tag = CAN value = 80 }
    relation = { tag = DEN value = 100 }
    relation = { tag = ENG value = 125 }
    relation = { tag = FIN value = 100 }
    relation = { tag = FRA value = 75 }
    relation = { tag = GER value = 1 }
    relation = { tag = IRE value = 75 }
    relation = { tag = ITA value = -20 }
    relation = { tag = JAP value = -50 }
    relation = { tag = LUX value = 150 }
    relation = { tag = MEX value = 25 }
    relation = { tag = NOR value = 100 }
    relation = { tag = SWE value = 100 }
    relation = { tag = USA value = 70 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 2 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 2 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 1 }
  SpyInfo                = { country = "BEL" NumberOfSpies = 2 }
  SpyInfo                = { country = "DEN" NumberOfSpies = 1 }
  SpyInfo                = { country = "GER" NumberOfSpies = 3 }
  SpyInfo                = { country = "USA" NumberOfSpies = 1 }
  SpyInfo                = { country = "NOR" NumberOfSpies = 1 }
  SpyInfo                = { country = "LUX" NumberOfSpies = 1 }
  SpyInfo                = { country = "SPR" NumberOfSpies = 1 }
  SpyInfo                = { country = "ITA" NumberOfSpies = 1 }
  # Homeland
  nationalprovinces      = { 47 78 79 77 46 48 1019 49 1082 7043 7191 45 50 51 69 801 561 2965 4285 6502
                           }
  # Homeland
  ownedprovinces         = { 49 1019
                           }
  # Homeland
  controlledprovinces    = { 49 1019
                           }
						   
  claimedprovinces    	 = { 874 3890 3891 
  #Wallonia/Luxemburg
  52 65 7044 70 68 71
  }
						   
techapps               = { 
#Early Infantry Division  
1010 1020 1030 1040 1050 1060 1070 1080 1090
#SEMI-MOTORIZED CAVALRY 
13060 13070 13080 1310 1320 1330 1340 1350 1360 1370 1380
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240
#1922 NAVAL INFANTRY
1560
#Motorised Inf
1396
#Engineers
1830 1840 1850 1860
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 1970 1980

#Interwar Armoured Car 
2860 2870 2880 2020
#Armor 
7600 7610 2620 2010 2630 2640 2646 2650
#Great War Heavy Field Artillery 
2290 2300 2310 2900 2910 2920
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade 
2810 2820 2510

#Short Range Submarine 
3610 3620 3630 3640 3650
#Improved Destroyer 
3010 3020 3030 3040 3050 3060
#Basic Light Cruiser 
3110 3120 3130 3140 3150 3160
#Improved Heavy Cruiser 
3210 3220 3230 3240 3250 3260
#Interwar Battlecruiser
3310 3320 3330 3340
#Early Battleship 
3410 3420 3430 3440 3450 3456 3460 3470
#Improved Light carrier 
12100 12110 12120 12130
#Fleet Carrier 
3510 3520 3530
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810 3820

#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Early Bomber 
4600 4610 4620 4630 4120 4130
#Multirole fighter
4300 4310 4320 4330 4340
# Transports
4290
#ww1 navalbomber
4700 4710
#CAG 34
4900 4910 4920
#Basic Strategic Bomber 
4800 4810 4820 4220
#SEAPLANES
4740 4750 4760

#Agriculture
5700 5710 5010 5020
#Manufacturing
5810 5820 5050 5830 5060 5070
#Improved Construction Engineering 
5800 5080 5090
#Basic Oil Refining
5190
#Computers
5310 54010 54020 54030 
#Cryptography
5316 5326 5327
#Basic Decimetric Radar Warning Sites 
5410 5416 
#Faculty of Atomic Research 
5470
#Exp. Rocket
5560
#Medicine
5600 5610 5620 5630

#Great War Hospital System 
14000 14010 14020

# WWI Land Doctrines - Entente line: eng fra ita usa bel hol jap 
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# WWII Land Doctrines
6560 6030 

# Naval Doctrines
# 
# Theories
8010 8020 8030 8040 8050 8060 8070 8080
# Amphib
82300
# Logistic Support
82500
# Naval Interdiction
8500 8510 8520 8550 8560 8600 8610
# Engagement Tactics
8900 8910 8920 8930 8940 8950
# Naval Supremacy
8100 8110 8120 8150 8160 8200 8210
# Carrier Doctrine
81650
# Carrier - Scouting Focus Line
81850
# Carrier - Strike Line
81700

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010 9140

} 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 5 
     free_market       = 1
     freedom           = 9 
     professional_army = 3 
     defense_lobby     = 2 
     interventionism   = 2 
  }
inventions = { 3000027 } 

   headofstate            = {  type = 9 id = 1  } 
   headofgovernment       = {  type = 9 id = 2  } 
   foreignminister        = {  type = 9 id = 3  } 
   armamentminister       = {  type = 9 id = 56 } 
   ministerofsecurity     = {  type = 9 id = 5  } 
   #ministerofintelligence = {  type = 9 id = 6  } 
   chiefofstaff           = {  type = 9 id = 7  } 
   chiefofarmy            = {  type = 9 id = 8  } 
   chiefofnavy            = {  type = 9 id = 9  } 
   chiefofair             = {  type = 9 id = 10 } 
  

  } 
 
province = { id = 1019
   coastalfort = 5 
 } 