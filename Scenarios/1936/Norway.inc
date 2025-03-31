#####################
# Country main data #
#####################

country =
{ tag                    = NOR
	energy                 = 600
	metal                  = 300
	rare_materials         = 150
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	manpower               = 3 
	capital                = 107 
	
   # Norwegian merchant marine is INSANE! 
   transports             = 200 
   escorts                = 5 
  diplomacy =
  { relation = { tag = BEL value = 100 }
    relation = { tag = DEN value = 150 }
    relation = { tag = ENG value = 90 }
    relation = { tag = FIN value = 75 }
    relation = { tag = HOL value = 100 }
    relation = { tag = LUX value = 100 }
    relation = { tag = SWE value = 150 }
    relation = { tag = USA value = 75 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 4 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 1 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 4 }
  SpyInfo                = { country = "CZE" NumberOfSpies = 1 }
  SpyInfo                = { country = "GER" NumberOfSpies = 3 }
  SpyInfo                = { country = "SPR" NumberOfSpies = 2 }
  SpyInfo                = { country = "POL" NumberOfSpies = 2 }
  SpyInfo                = { country = "SWE" NumberOfSpies = 3 }
  SpyInfo                = { country = "FIN" NumberOfSpies = 2 }
  SpyInfo                = { country = "DEN" NumberOfSpies = 2 }
  SpyInfo                = { country = "HOL" NumberOfSpies = 1 }
  claimedprovinces       = { 7168 3315 3316 6530 7170 3340 132 3341 133 3342 134 3343 2634 1 7137 7138 7139 2632 7288 7287 1588 2078 7975 7973 2105 800 7974 3 }
  nationalprovinces      = { 107 108 109 110 111 116 117 118 124 125 128 129 114 112 104 2276
  3290	3291	3292	3293	3294	3295	3296	3297	3298	3299
7170 7171 7176 3300 2 5 1165 6530
  }
  ownedprovinces         = { 107 108 109 110 111 116 117 118 124 125 128 129 114 112 104 2276
3290	3291	3292	3293	3294	3295	3296	3297	3298	3299
7170 7171 7176
  }
  controlledprovinces    = { 107 108 109 110 111 116 117 118 124 125 128 129 114 112 104 2276
3290	3291	3292	3293	3294	3295	3296	3297	3298	3299
7170 7171 7176
  }
  # Western Minor Tech '36
  # Group C 1936 techs
  # ######################
   techapps               = { 
#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Interwar Bomber 
4600 4610 4620 4630 4120
#Basic Armoured Car  
2860 2870 2880 2020
#Tankette 
7600 7610 2620 2010 2630 2640
#Great War Heavy Field Artillery 
2290 2300 2310 
#Early Static Anti-Air Artillery 
2800 2450 21180 21190 21200
#Early Heavy Cruiser 
3210 3220 3230
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Great War Infantry Division  
1010  1020 1030 1040 1050 1060 
#Great War Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 1970 1980
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

#Great War Destroyer 
3010 3020 3030 3040
#Early Light Cruiser 
3110 3120 3130
#Great War Battleship 
3410 3420 3430 3440 3450 3456 3460
#Short Range Submarine 
3610 3620 3630
#Naval Doctrines
8010 8020 8040 8050 
#Multirole fighter
4300 4310 4320 4330
#ww1 strategic bomber
4800 4810 4820
#ww1 navalbomber
4700 4710
#Naval Infantry
#1560 1570 1580
#Engineers
1830 1840 1850 1860
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810
#Medicine
5600 5610 5620 5630
# Land Doctrines WW1 - Entente Line
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Land Doctrines WW2 - none

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
                             } 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 7 
     freedom           = 8 
     free_market       = 1
     professional_army = 4 
     defense_lobby     = 2 
     interventionism   = 1
  }
	inventions = { 3000027 }

   headofstate            = {  type = 9 id = 65001  } 
   headofgovernment       = {  type = 9 id = 65002  } 
   foreignminister        = {  type = 9 id = 65003  } 
   armamentminister       = {  type = 9 id = 65004  } 
   ministerofsecurity     = {  type = 9 id = 65005  } 
   ministerofintelligence = {  type = 9 id = 65006  } 
   chiefofstaff           = {  type = 9 id = 65007  } 
   chiefofarmy            = {  type = 9 id = 65008  } 
   chiefofnavy            = {  type = 9 id = 65140  } #Edgar Otto
   chiefofair             = {  type = 9 id = 65141  } #Edgar Otto  
   landunit = 
   {  location = 107 
     name     = "1. Divisjon" 
     id       = {  type = 12600 id = 1  } 
     Division = 
     {  id       = {  type = 12600 id = 2  } 
       name     = "1. Infanteridivisjon" 
       type     = infantry 
	   model = 5
       strength = 20 
	extra = engineer
	brigade_model = 2
      } 
    } 
   landunit = 
   {  location = 107 
     name     = "2. Divisjon" 
     id       = {  type = 12600 id = 3  } 
     Division = 
     {  id       = {  type = 12600 id = 4  } 
       name     = "2. Infanteridivisjon" 
       type     = infantry 
	   model = 5
       strength = 20 
	extra = anti_air
	brigade_model = 1
      } 
    } 
   landunit = 
   {  location = 107 
     name     = "3. Divisjon" 
     id       = {  type = 12600 id = 5  } 
     Division = 
     {  id       = {  type = 12600 id = 6  } 
       name     = "3. Infanteridivisjon" 
       type     = infantry 
	   model = 5
       strength = 10 
      } 
    } 
   landunit = 
   {  location = 107 
     name     = "4. Divisjon" 
     id       = {  type = 12600 id = 7  } 
     Division = 
     {  id       = {  type = 12600 id = 8  } 
       name     = "4. Infanteridivisjon" 
       type     = infantry 
	   model = 5
       strength = 10 
      } 
    } 
   landunit = 
   {  location = 107 
     name     = "5. Divisjon" 
     id       = {  type = 12600 id = 9  } 
     Division = 
     {  id       = {  type = 12600 id = 10  } 
       name     = "5. Infanteridivisjon" 
       type     = infantry 
	   model = 5
       strength = 20 
      } 
    } 
   landunit = 
   {  location = 107 
     name     = "6. Divisjon" 
     id       = {  type = 12600 id = 11  } 
     Division = 
     {  id       = {  type = 12600 id = 12  } 
       name     = "6. Infanteridivisjon" 
       type     = infantry 
	   model = 5
       strength = 15 
      } 
    } 
	navalunit = { 
		id = { type = 12600 id = 20 } 
		name = "2. Kystvaktdistrikt" 
		location = 2276 
		base = 2276 
		division = { 
			id = { type = 12600 id = 21 } 
			name = "1. Undervannsbåteskadre" 
			type = submarine 
			model = 1 
			} 
		division = { 
			id = { type = 12600 id = 22 } 
			name = "2. Undervannsbåteskadre" 
			type = submarine 
			model = 1 
			} 
		} 
	navalunit = { 
		id = { type = 12600 id = 25 } 
		name = "1. Kystvaktdistrikt" 
		location = 2276 
		base = 2276 
		division = { 
			id = { type = 12600 id = 26 } 
			name = "KNM Norge" 
			type = heavy_cruiser 
			model = 2 
			} 
		division = { 
			id = { type = 12600 id = 30 } 
			name = "KNM Eidsvold" 
			type = heavy_cruiser 
			model = 2 
			} 
		division = { 
			id = { type = 12600 id = 2422 } 
			name = "1. Destroyereskadre" 
			type = destroyer 
			model = 1
			} 
		division = { 
			id = { type = 12600 id = 2423 } 
			name = "2. Destroyereskadre" 
			type = destroyer 
			model = 0
			} 
		division = { 
			id = { type = 12600 id = 2424 } 
			name = "3. Destroyereskadre" 
			type = destroyer 
			model = 0
			} 
		division = { 
			id = { type = 12600 id = 2425 } 
			name = "4. Destroyereskadre" 
			type = destroyer 
			model = 0
			} 
		division = { 
			id = { type = 12600 id = 2426 } 
			name = "5. Destroyereskadre" 
			type = destroyer 
			model = 0
			} 
		} 
  } 
 
