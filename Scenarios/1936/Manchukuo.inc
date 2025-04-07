#####################
# Country main data #
#####################

country =
{ tag                    = MAN
  puppet                 = JAP
  control				 = JAP #AI will not autonomously suppress revolts otherwise
  ai_settings			 = { flags = { puppetLevel5 = 1 } } #min dissent 20-25
	# Resource Reserves 
	energy                 = 900
	metal                  = 450
	rare_materials         = 225
	transports = 100
	oil                    = 200 
	supplies               = 100 
	money                  = 10 
	manpower               = 8 
	dissent				   = 30
  capital                = 2241
  free                   = { energy = 14 metal = 7 rare_materials = 4 }
  diplomacy =
  { relation = { tag = CHC value = -100 }
    relation = { tag = CHI value = -100 }
    relation = { tag = CSX value = -75 }
    relation = { tag = CXB value = -75 }
    relation = { tag = CYN value = -75 }
    relation = { tag = CGX value = -75 }
    relation = { tag = GER value = 20 }
    relation = { tag = JAP value = 200 access = yes }
	relation = { tag = MEN value = 200 access = yes }
	relation = { tag = U87 value = 200 access = yes }
    relation = { tag = SIA value = 75 }
    relation = { tag = USA value = 1 }
  }
  nationalprovinces      = { 1389 1390 1377 1378 1375 1374 1379 1530 1380 1387 1382 1381 1394 1395 1396 
							2347 2349 2346 2345 2340 2341 2344 2338 2333 2487 2241 2511 2337 2246 2486 2281 2485
							1388 2348 2317 1397 2318 3110	
							3755 3756 3757 3758 3759 3760 3774 1202 3090
5633 5635 5636
5656 5657 5658 5659 5660 5661 5662 5663 5664 5665 
5666 5667 5668 5669 5670 5671 5672 5673 5674 5675 
5676 5677 5678 5679 5680 5681 5682 5683 5684 5685 
5686 5687 5688 5689 5690 5691 5692 7911
							}
  ownedprovinces         = { 1389 1390 1377 1378 1375 1374 1379 1530 1380 1387 1382 1381 1394 1395 1396 
							2347 2349 2346 2345 2340 2341 2344 2338 2333 2487 2241 2511 2337 2246 2486 2281 2485
							1388 2348 2317 1397 2318 3110			
							3755 3756 3757 3758 3759 3760 3774
5633 5635 5636
5656 5657 5658 5659 5660 5661 5662 5663 5664 5665 
5666 5667 5668 5669 5670 5671 5672 5673 5674 5675 
5676 5677 5678 5679 5680 5681 5682 5683 5684 5685 
5686 5687 5688 5689 5690 5691 5692 7911
							}
  controlledprovinces    = { 1389 1390 1377 1379 1530 1380 1387 1382 1381 1394 1395 1396 
							2347 2349 2346 2340 2341 2344 2338 2487 2241 2511 2337 2246 2486 2281
							1388 2348 2317 1397 2318 3110			
							3755 3756 3757 3758 3759 3760 3774
5633 5635 5636
5656 5657 5658 5659 5660 5661 5662 5663 5664 5665 
5666 5667 5668 5670 5671 5672 5673 5675 
5676 5677 5678 5679 5680 5681 5682 5683 5684 
5686 5691 5692
7911 2333
							}
  claimedprovinces 		 = { 
5693
		}
  # ROTW Minor Tech '36
  # Group E 1936 techs
  # ######################
  # GW fighter
   techapps               = {  
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
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 5
     political_left    = 3 
     freedom           = 3 
     free_market       = 1
     professional_army = 2 
     defense_lobby     = 5 
     interventionism   = 7 
  }
 inventions = { 3000027 }
   SpyInfo                = {  country = "MAN" NumberOfSpies = 5  } 
   headofstate            = {  type = 9 id = 235001  } 
   headofgovernment       = {  type = 9 id = 235002  } 
   foreignminister        = {  type = 9 id = 235003  } 
   armamentminister       = {  type = 9 id = 235004  } 
   ministerofsecurity     = {  type = 9 id = 235005  } 
   ministerofintelligence = {  type = 9 id = 235006  } 
   chiefofstaff           = {  type = 9 id = 235007  } 
   chiefofarmy            = {  type = 9 id = 235008  } 
   chiefofnavy            = {  type = 9 id = 235009  } 
   chiefofair             = {  type = 9 id = 235010  } 
  # Basic Construction Engineering Development Process

  landunit = 
   {  location = 2241 
     id       = {  type = 28500 id = 1  } 
     name     = "Di'1 Fang'tien Jüntuan" 
     Division = 
     {  id       = {  type = 28500 id = 2  } 
       name     = "1 Man'chu Lü" 
       type     = militia
		model = 4   
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 3  } 
       name     = "2 Man'chu Lü" 
       type     = militia
		model = 4   
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 4  } 
       name     = "3 Man'chu Lü" 
       type     = militia
		model = 4   
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 5  } 
       name     = "4 Man'chu Lü" 
       type     = militia
		model = 4   
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 6  } 
       name     = "5 Man'chu Lü" 
       type     = militia
		model = 4   
       strength = 50 
      } 
     #Division = 
     #{  id       = {  type = 28500 id = 7  } 
     #  name     = "6 Man'chu Lü" 
     #  type     = militia
	 #  model = 4   
     #  strength = 50 
     # } 
    } 
   landunit = 
   {  location = 2241 
     id       = {  type = 28500 id = 8  } 
     name     = "Di'2 Ji'lin Jüntuan" 
     Division = 
     {  id       = {  type = 28500 id = 9  } 
       name     = "7 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 10  } 
       name     = "8 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 11  } 
       name     = "9 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     #Division = 
     #{  id       = {  type = 28500 id = 12  } 
     #  name     = "10 Man'chu Lü" 
     #  type     = militia 
	 #  model = 4
     #  strength = 50 
     # } 
     Division = 
     {  id       = {  type = 28500 id = 13  } 
       name     = "1 Man'chu Qi'Bing" 
       type     = cavalry 
	   model = 7
       strength = 15 
      } 
     Division = 
     {  id       = {  type = 28500 id = 14  } 
       name     = "2 Man'chu Qi'Bing" 
       type     = cavalry 
	   model = 7
       strength = 15 
      } 
    } 
   landunit = 
   {  location = 2241 
     id       = {  type = 28500 id = 16  } 
     name     = "Di'3 Qiqihar Jüntuan" 
     Division = 
     {  id       = {  type = 28500 id = 17  } 
       name     = "11 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 18  } 
       name     = "12 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 19  } 
       name     = "13 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 20  } 
       name     = "14 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     #Division = 
     #{  id       = {  type = 28500 id = 21  } 
     #  name     = "15 Man'chu Lü" 
     #  type     = militia 
	 #  model = 4
     #  strength = 50 
     # } 
     Division = 
     {  id       = {  type = 28500 id = 22  } 
       name     = "4 Man'chu Qi'Bing" 
       type     = cavalry 
	   model = 7
       strength = 15 
      } 
    } 
   landunit = 
   {  location = 2241 
     id       = {  type = 28500 id = 23  } 
     name     = "Di'4 Harbin Jüntuan" 
     Division = 
     {  id       = {  type = 28500 id = 24  } 
       name     = "16 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 25  } 
       name     = "17 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 26  } 
       name     = "18 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 27  } 
       name     = "19 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     #Division = 
     #{  id       = {  type = 28500 id = 28  } 
     #  name     = "20 Man'chu Lü" 
     #  type     = militia 
	 #  model = 4
     #  strength = 50 
     # } 
     Division = 
     {  id       = {  type = 28500 id = 32  } 
       name     = "5 Man'chu Qi'Bing" 
       type     = cavalry 
	   model = 7
       strength = 15 
      } 
    } 
   landunit = 
   {  location = 2241 
     id       = {  type = 28500 id = 33  } 
     name     = "Di'5 Chengde Jüntuan" 
     Division = 
     {  id       = {  type = 28500 id = 29  } 
       name     = "21 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 34  } 
       name     = "24 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 35  } 
       name     = "25 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 36  } 
       name     = "26 Man'chu Lü" 
       type     = militia 
	   model = 4
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 28500 id = 37  } 
       name     = "6 Man'chu Qi'Bing" 
       type     = cavalry 
	   model = 7
       strength = 15 
      } 
    } 
  } 
 
