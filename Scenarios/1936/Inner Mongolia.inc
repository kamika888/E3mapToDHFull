#####################
# Country main data #
#####################

country =
{ tag                    = MEN
  regular_id             = MON
  puppet                 = JAP
  #control                = JAP
  ai_settings			 = { flags = { puppetLevel7 = 1 } }
  ai					 = "exp_0.ai"
  intrinsic_gov_type     = fascist
  capital                = 5629
	# Resource Reserves 
	energy                 = 240
	metal                  = 120
	rare_materials         = 60
	oil                    = 100 
	supplies               = 800 
	money                  = 50 
    manpower               = 120
  diplomacy =
  { relation = { tag = CHC value = -100 }
    relation = { tag = CHI value = -100 }
    relation = { tag = CSX value = -75 }
    relation = { tag = CXB value = -75 }
    relation = { tag = CYN value = -75 }
    relation = { tag = CGX value = -75 }
    relation = { tag = GER value = 20 }
    relation = { tag = JAP value = 200 access = yes }
	relation = { tag = MAN value = 200 access = yes }
	relation = { tag = U87 value = 200 access = yes }
    relation = { tag = SIA value = 75 }
    relation = { tag = USA value = 1 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 1 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 1 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 2 }
  SpyInfo                = { country = "GER" NumberOfSpies = 1 }
  SpyInfo                = { country = "CHI" NumberOfSpies = 3 }
  SpyInfo                = { country = "JAP" NumberOfSpies = 1 }
  SpyInfo                = { country = "CYN" NumberOfSpies = 1 }
  SpyInfo                = { country = "CSX" NumberOfSpies = 1 }
  SpyInfo                = { country = "CXB" NumberOfSpies = 1 }
  nationalprovinces      = { 1404 1420 1419 1434 1438 1385 1208 1386 1439 1273 1272 2246 1382
3762 3763 3764 3765 3766 3767 3768 3769 3770 3771 3772 3773
3756 3757 3758 3595 3761 3750 3751 3752 3753 3754
5472 5473 5474 5475 5476 5477 5478 5479 5480
3740 1421 5502 3741 3744 5493 5528 5542 5541 5622
5624 5625 5623 5631 5632 5628 5629 5630
5636 5633 5658 5657 5681 1387 5677 5680
1380 5661 5660 5665 5663 5659
7917 7918 2486
3579 1413 3571 3592 3578
  }
  claimedprovinces 		 = { 
5497 5504 5503 3742 1206 5626 5565 1209
3759 3760 5662 5664 5679 5676 5675 2344 2348 3755 2317 1397 2318 1388 5635 5627 1398 1207 2337 2504 5549
1418 3594 
1414 3583 3584 3593 1412 3569 3570 1384 3572
  }
  ownedprovinces         = { 3753 3754 1386 5627 5628 5629 5630 5631 5632 
  }
  controlledprovinces    = { 3753 3754 1386 5627 5628 5629 5630 5631 5632 
  }

  # Group E 1936 techs
  # ######################
  # GW fighter
	techapps = { 	
	# Manufacturing
	5810 5820 5050
	# Construction Engineering
	5800 5080
	# Crypto - Up to 1923
	5316 5326 5327
	# Infantry Division
	1010 1020 1030 1040 1050 1060 1070 1080 
	# Mountain Division
	1160 1170 1180 1190 1200 1210 1220
	# Cavalry Division  
	13060 13070 13080 1310 1320 1330 1340
	# Engineers
	1830
	# Supply 
	1910 1920 1930 1940 1950 1960
	# Armoured Car  
	2860 2870
	# Field Artillery 
	2290 2300 2310 2900 2910
	# Manpower Focus
	6570
	# Hospital System
	14000 14010 14020
	# Great War Land Doctrines (entente)
	6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
	# Destroyers
	3010 
	# Light Cruiser 
	3110 3120 3130 3140
	# Heavy Cruiser 
	3210 3220
	# Troopships
	3810
	#Early Torpedoes
	3720 3730
	#Early Battleship
	3410 3420
	# Naval Doctrines
	8010 8020 8050 8060 8070 8080
	# Interceptor Fighter  
	4500 4510 4520 4530 4540  
	# Multirole Fighter
	4300 4310 4320 
	# Tactical Bomber 
	4600 4610 4620 4630 
	# Strategic Bomber
	4800 4810 
	# Naval Bomber
	4700 
	# Seaplane
	4740 4750 4760
	# Air Doctrines - ww2 techs
	27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 
	}

 inventions = { 3000027 }
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 7 
     political_left    = 3 
     freedom           = 3 
     free_market       = 1
     professional_army = 7 
     defense_lobby     = 5 
     interventionism   = 7 
  }
   headofstate            = {  type = 9 id = 700001 } 
   headofgovernment       = {  type = 9 id = 700002 } 
   foreignminister        = {  type = 9 id = 700003 } 
   armamentminister       = {  type = 9 id = 700004 } 
   ministerofsecurity     = {  type = 9 id = 700005 } 
   ministerofintelligence = {  type = 9 id = 700006 } 
   chiefofstaff           = {  type = 9 id = 700007 } 
   chiefofarmy            = {  type = 9 id = 700008 } 
   chiefofnavy            = {  type = 9 id = 700009 } 
   chiefofair             = {  type = 9 id = 700010 } 

 landunit = {
	id = { type = 11855 id = 1 }
	name = "Mongolian Army"
	location = 3753 	    
	division = { id = { type = 11855 id = 2 } name = "1. Cavalry Division"			type = cavalry model = 7 strength = 40 extra = artillery brigade_model = 7 max_strength = 50 } 
	division = { id = { type = 11855 id = 3 } name = "2. Cavalry Division"			type = cavalry model = 7 strength = 40 max_strength = 50 } 
	division = { id = { type = 11855 id = 4 } name = "3. Cavalry Division"			type = cavalry model = 7 strength = 40 max_strength = 50 } 
	division = { id = { type = 11855 id = 5 } name = "9. Infantry Division"			type = infantry model = 7 strength = 20 max_strength = 50 } 
 }	
 landunit = {
	id = { type = 11855 id = 10 }
	name = "Grand Han Righteous Army"
	location = 3753 	    
	division = { id = { type = 11855 id = 11 } name = "Grand Han Righteous Army"	type = militia model = 4 strength = 30 max_strength = 50 } 
 }
 landunit = {
	id = { type = 11855 id = 12 }
	name = "Reserve Army"
	location = 5627 	    
	division = { id = { type = 11855 id = 13 } name = "Teh Wang's Army"				type = militia model = 4 strength = 40 max_strength = 50 } 
 }	
 airunit = {
    id = { type = 11855 id = 14 }
    name = "Japanese Volunteer Group"
    location = 5628
    base = 5628 
		division = { id = { type = 11855 id = 15 } name = "JVG Fighter Wing"		type = multi_role model = 4 strength = 30 max_strength = 40 }		
    }
}  
 
 