#####################
# Country main data #
#####################

country =
{ tag                    = CHI
  capital                = 1235 # Nanjing
	# Resource Reserves 
	energy                 = 8100
	metal                  = 3050
	rare_materials         = 2525
	oil                    = 1000 
	supplies               = 3000 
	money                  = 10 
	manpower               = 1455 #More to warlords
	dissent                = 20
	transports             = 100 
	escorts                = 2 
  diplomacy =
  { relation = { tag = CHC value = -200 }
    relation = { tag = CGX value = 200 }
	relation = { tag = SIK value = 40 }
	relation = { tag = TIB value = 40 access = yes }
    relation = { tag = CSX value = 200 access = yes }
    relation = { tag = CXB value = 200 access = yes }
    relation = { tag = CYN value = 200 }
    relation = { tag = JAP value = -100 }
    relation = { tag = MAN value = -100 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 1 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 1 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 3 }
  SpyInfo                = { country = "GER" NumberOfSpies = 1 }
  SpyInfo                = { country = "CBX" NumberOfSpies = 2 }
  SpyInfo                = { country = "CHC" NumberOfSpies = 5 }
  SpyInfo                = { country = "JAP" NumberOfSpies = 3 }
  SpyInfo                = { country = "CYN" NumberOfSpies = 2 }
  SpyInfo                = { country = "CSX" NumberOfSpies = 2 }
  SpyInfo                = { country = "CXB" NumberOfSpies = 1 }
  # Fujian		
  nationalprovinces      = {
1275 1276 1277 1440 1441 1267 1268 1269 1270 1271
1222 1223 1224 1227 1228 1229 1230 1273 1274 1439
1207 1208 1272 1209 1225 1226 1203 1204 1205 1206
1210 1211 1212 1213 1216 1386 1398 1388 1397 1202
1377 1387 1389 1390 1394 1395 1396 1374 1375 1378
1379 1380 1381 1382 1530 1218 1221 1233 1234 1217
1219 1220 1235 1236 1237 1263 1265 1279 1280 1360
1361 1231 1232 1253 1264 1266 1238 1239 1240 1241
1262 1363 1364 1365 1255 1256 1257 1259 1260 1261
1242 1250 1251 1252 1254 1243 1244 1245 1246 1247
1294 1307 1308 1362 1281 1282 1448
1451 1442 1443 5558
1432 1433 1435 1445 1258 1311
1325 1248 1249 1312 1313 1314 1317 1318 1320
1321 1322 1323 1324 1385 1419 1420 1434 1438
1903 2559 1984 1993 2560 2551 2000 2311 1913 2561
2550 1996 2502 1997 1995 1910 1922 1921 1914
2507 2516 2515 2513 2508 1966 2556 2558 1965 1964
1939 2571 1936 1937 2572 2570 2568 2573 2574 2567
2569 1941 1938 1918
1983 674  559  720  568  570 
1880 1912 746  1923 696  1316 1315 2503 2504 2517
2518 2520 2525 2527 2526 2576 2523 2528 2534 2522
2533 2531 1215 2530 2529 1214 2318 2317 2347 2348
2349 2346 2345 2340 2341 2344 2338 2333 2487 2241
2511 2337 2246 2486 2281 2485 3133 2941 2942 3090
3110 3750 3751 3752 3753 3754 3775
3741 3743 3746 3748
3755 3756 3757 3758 3759 3760 3774 3762 3763 3764
3765 3766 3767 3769 3770 3771 3772 3773 3761
3595 5472 5473 5474 5475 5476
5477 5478 5479 5480 5559
5491 557
5492 5493 5494 5495 5496 5497 5498 5499 5501 
5502 5505 5506 5507 5508 5509 5510 5511 
5512 5513 5514 5515 5516 5517 5518 5521 
5522 5523 5524 5527 5528 5529 
5533 5534 5535 5537 5538 5539 5540 5541 
5542 5543 5544 5545 5546 5547 5548 5549 5550 5551 
5552 5553 5554 5555 5560 5561 
5562 5563 5564 5565 5566 5567 5568 5569 5570 5571 
5572 5573 5574 5575 5576 5579 5580 
5586 5588 5590 5591 5556 2505
5592 5593 5594 5595 5596 5597 5598 5599 5600 5601 
5606 5608 5609 5610 5611
5612 5614 5615 5616 5617 5618 5619 5620 5621 
5622 5623 5624 5625 5626 5627 5628 5629 5630 5631 
5632 5633 5634 5635 5636 5637 5638 5639 5640 5641 
5642 5643 5644 5645 5646 5647 5648 5649 5650 5651 
5652 5655 5656 5657 5658 5659 5660 5661 5662 5663
5664 5665 5666 5667 5668 5669 5670 5671 5672 5673
5674 5675 5676 5677 5678 5679 5680 5681 5682 5683
5684 5685 5686 5687 5688 5689 5690 5691 5692 5693
6497 6498 6916 7911 7918 7917 5486 5487 5578 5583
}
  claimedprovinces 		 = { 
1487 3485 5872 5836 5873 5891 5892 5893 6953

#internal
#xinjiang
5503 5504 3740 1421 3742 3745 5500 3747 3749 5490 1446 5489 5485 1431 3738 5482 3739 3737 5483 5488 1430 1728 6920 5481 5484 1447 3744
#zhuang
1327 5607 1310 1319 1309 695 2949 7989 5613 
#yi
1978 1928 1293 5604 5605 1905
#tibet
5536 5530 5557 5581 5584 5585 5577 5602 5603 5526 5525 1406 5520 1444 1283 5582 5519 1452 1453 1450 5587 5589
5185 6496 1898 5184 1877 1878 5531 5532 5205
#mongolia
1404 3768 1418 3594
}
  ownedprovinces         = {   1222 1218 1221 1233 1234 1217 1219 1220 1235 1236
1231 1232 1253 1264 1266 1238 1239 1240 1241 1262 1363 1364 1365
1242 1250 1251 1252 1254 1243 1244 1245 1246 1247 
1984 1993 2000 2311 1996 2502 1997
1995 1910 1966 2556 2558 1965 1964
1939 2571 1936 1937 2572 2570 2568 2573 2574 2567 2569 1941 1938
5611 5612 5613 5618 5619 5620 5621
5642 5643 5644 5645 5646 5647 5648 5649 5650 5651 6497 6498
                           }
		
  controlledprovinces    = {   1222 1218 1221 1233 1234 1217 1219 1220 1235 1236
1231 1232 1253 1264 1266 1238 1239 1240 1241 1262 1363 1364 1365
1242 1250 1251 1252 1254 1244 1245 1246 1247 
1984 1993 2000 2311 1996 2502 1997
1995 1910 1966 2556 2558 1965 1964
1939 2571 1936 1937 2572 2570 2568 2573 2574 2567 2569 1941 1938
5611 5612 5613 5618 5619 5621
5642 5643 5645 5646 5647 5648 5649 5650 5651 6497 6498
#5644
#5620
#1243
5491 5492 3748 5487 5486 1447 1728 1430 5488 5484 
                           }
  # ROTW Minor Tech '36
  # Group E 1936 techs
  # ######################
  # GW fighter
techapps = { 
	
	# Manufacturing
	5810 5820 5050
	# Construction Engineering
	5800 5080

	# Synthetic Oil
	5190

	#Computers
	5310 54010

	# Crypto - Up to 1923
	5316 5326 5327

	# Infantry Division
	1010 1020 1030 1040 1050 1060 1070 1080 
	# Mountain Division
	1160 1170 1180 1190 1200 1210 1220 1230 
	# Cavalry Division  
	13060 13070 13080 1310 1320 1330 1340 1350 1360 1370
	# Engineers
	1830 1840
	# Supply 
	1910 1920 1930 1940 1950 1960 1970

	# Armoured Car  
	2860 2870
	# Field Artillery 
	2290 2300 2310 2900 2910 2920 2930

	# Medicine
	5600 5610

	# Hospital System
	14000 14010 14020
	# Great War Land Doctrines (entente)
	6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910

	# Manpower Focus
	6570

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
	4500 4510 4520 4530 4540 4550
	# Multirole Fighter
	4300 4310 4320 
	# Tactical Bomber 
	4600 4610 4620 4630 4120
	# Strategic Bomber
	4800 4810
	# Naval Bomber
	4700 
	# Seaplane
	4740 4750 4760 4770

	# Air Doctrines - ww2 techs
	27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 
	} 

blueprints = {
	# Infantry (from GER/SOV)
	1090
	
	# Engineers
	1850

	# Industry
	5830

	# Computers
	54030

	# Agriculture
	5700
	
	# Medicine
	5620
	
	# Supply
	1980

	# Tank 
	7600 7610 2620 2010
	
	# Armored Car
	2880

	#Mobility Focus
	6210

	#Manpower Focus
	6300
	
	#Intercepter Fighter
	4010
	
	#Multi-Role Fighter
	4330

	#Close Air Support
	4400
	
	# Light Cruiser
	3150

}
	
  policy =
  { date              = { year = 0 month = january day = 0 }
    democratic        = 7
    political_left    = 3
    free_market       = 1
    freedom           = 3
    professional_army = 7
    defense_lobby     = 4
    interventionism   = 5
  }
inventions = { 3000027 }

   headofstate            = {  type = 9 id = 55022  } 
   headofgovernment       = {  type = 9 id = 55009  } 
   foreignminister        = {  type = 9 id = 55029  } 
   armamentminister       = {  type = 9 id = 55051  } 
   ministerofsecurity     = {  type = 9 id = 55065  } 
   ministerofintelligence = {  type = 9 id = 55066  } 
   chiefofstaff           = {  type = 9 id = 55013  } 
   chiefofarmy            = {  type = 9 id = 55014  } 
   chiefofnavy            = {  type = 9 id = 55019  } 
   chiefofair             = {  type = 9 id = 55035  } 
   dormant_leaders        = {  55368 55375  } 
   #######################
   # CHINA 1936/1937 OOB #
   #######################
   # TYPE = 22002
   # http://forum.paradoxplaza.com/forum/showthread.php?687389-OOB-and-information-of-China-for-moders&p=15468195&viewfull=1#post15468195
   
	######################
	# Guizhou Task Force #
	######################
	landunit = 
   {  location = 1364 # Guiyang
     name     = "25. Corps" 
     id       = {  type = 22002 id = 55  } 
     Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 56 } 
       name       = "103. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	 Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 57 } 
       name       = "102. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 59 } 
       name       = "121. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	 Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 58  } 
       name       = "New 8. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 60  } 
       name       = "New 25. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }
	landunit = 
   {  location = 1364 # Guiyang
     name     = "Guizhou Provincial Security Group" 
     id       = {  type = 22002 id = 61  } 
     Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 62 } 
       name       = "1. Guizhou Provincial Militia" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	 Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 63 } 
       name       = "2. Guizhou Provincial Militia" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	 Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 64 } 
       name       = "3. Guizhou Provincial Militia" 
       type       = militia
	   strength  = 40
       model     = 2
      }
    }
	

	##################
	# Central Forces #
	##################

	# Five Main Forces
	
	landunit = 
   {  location = 1235 # Nanjing
     name     = "New 1. Corps" 
     id       = {  type = 22002 id = 107  } 
     Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 108 } 
       name       = "50. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 141 } 
       name       = "New 30. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 250 } 
       name       = "1. Central Militia Forces" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 251 } 
       name       = "2. Central Militia Forces" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 252 } 
       name       = "3. Central Militia Forces" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	   Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 253 } 
       name       = "4. Central Militia Forces" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 254 } 
       name       = "5. Central Militia Forces" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 255 } 
       name       = "6. Central Militia Forces" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 256 } 
       name       = "7. Central Militia Forces" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 257 } 
       name       = "8. Central Militia Forces" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 258 } 
       name       = "9. Central Militia Forces" 
       type       = militia
	   strength  = 40
       model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22000 id = 259 } 
       name       = "10. Central Militia Forces" 
       type       = militia
	   strength  = 40
       model     = 2
      }
    }
	landunit = 
   {  location = 1235 # Nanjing
     name     = "New 6. Corps" 
     id       = {  type = 22002 id = 111  } 
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 113 } 
       name       = "207. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }
    }
	landunit = 
   {  location = 1235 # Nanjing
     name     = "74. Corps" 
     id       = {  type = 22002 id = 115  } 
     Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 116 } 
       name       = "51. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 117 } 
       name       = "57. Division (German)" 
       type       = infantry
	   strength  = 40
       model     = 6
	   extra1 = engineer
	   brigade_model1 = 2
	   extra2 = artillery
	   brigade_model2 = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 118 } 
       name       = "58. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model = 2
      }
    }
	landunit = 
   {  location = 1235 # Nanjing
     name     = "18. Corps" 
     id       = {  type = 22002 id = 119  } 
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 121 } 
       name       = "18. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 122 } 
       name       = "97. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }
    }
	landunit = 
   {  location = 1235 # Nanjing
     name     = "5. Corps" 
     id       = {  type = 22002 id = 123  } 
	  Division = 
     { experience 	= 30 
       id         	= {  type = 22005 id = 152  } 
       name       	= "National Revolutionary Army HQ" 
       type  		= hq 
	   strength  = 40
       model		= 2 
      } 
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 125 } 
       name       = "96. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }
    }
	landdivision = 
     {  experience = 10 
       id         = {  type = 22002 id = 126 } 
       name       = "200. Division" 
       type       = motorized
	   strength  = 40
       model     = 0
	   dormant = yes
      }

	# Attack Corps
	# 1st/2. Corps: See CGX
	# 5/74 Corps: See 5 Main Forces Above
	landunit = 
   {  location = 1235 # Nanjing
     name     = "2. Corps"  # Different than the one in CGX. Includes 9. Division from CGX po. 1937.
     id       = {  type = 22002 id = 127  } 
     Division = 
     {  experience = 30
       id         = {  type = 22002 id = 128 } 
       name       = "76. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 129 } 
       name       = "2. Preparation Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }

    }

	#Other Main Forces
	landunit = 
   {  location = 1235 # Nanjing
     name     = "13. Corps" #Includes 3. Division from CGX po. 1937
     id       = {  type = 22002 id = 130  } 
     Division = 
     {  experience = 30
       id         = {  type = 22002 id = 131 } 
       name       = "54. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }
	  Division = 
     {  experience = 30
       id         = {  type = 22002 id = 132 } 
       name       = "89. Division (German)" 
       type       = infantry
	   strength  = 40
       model     = 6
	   extra1 = engineer
	   brigade_model1 = 2
	   extra2 = artillery
	   brigade_model2 = 2
      }

    }
	landunit = 
   {  location = 1235 # Nanjing
     name     = "26. Corps" #Includes 44. Division from CGX po. 1937
     id       = {  type = 22002 id = 133  } 
     Division = 
     {  experience = 30
       id         = {  type = 22002 id = 134 } 
       name       = "41. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 135 } 
       name       = "169. Division" 
       type       = infantry
	   strength  = 40
       model     = 4
	   extra1 = artillery
	   brigade_model     = 2
      }

    }

	#Misc Other Corps/Outdated Corps (Upgraded wi. USA Arms po. 1941)
	landunit = 
   {  location = 1235 # Nanjing
     name     = "8. Corps" #Different from the CGX 8th, includes 103. Division from Guizhou po. 1937
     id       = {  type = 22002 id = 136  } 
     Division = 
     {  experience = 30
       id         = {  type = 22002 id = 137 } 
       name       = "1. Honor Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	  Division = 
     {  experience = 30
       id         = {  type = 22002 id = 138 } 
       name       = "166. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }

    }
	
	landunit = 
   {  location = 1235 # Nanjing
     name     = "53. Corps"
     id       = {  type = 22002 id = 139  } 
     Division = 
     {  experience = 30
       id         = {  type = 22002 id = 140 } 
       name       = "2. Honor Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }

	landunit = 
   {  location = 1235 # Nanjing
     name     = "54. Corps" # Includes 8. Division from CGX po. 1937
     id       = {  type = 22002 id = 143  }
	 # Division = 
     #{  experience = 30
     #  id         = {  type = 22002 id = 144 } 
     #  name       = "36. Division" 
     #  type       = infantry
	 #  strength  = 40
     #  model     = 8
	 #  extra1 = engineer
	 #  brigade_model1 = 2
	 #  extra2 = artillery
	 #  brigade_model2 = 6
     # }
	  Division = 
     {  experience = 30
       id         = {  type = 22002 id = 145 } 
       name       = "198. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }

	
	landunit = 
   {  location = 1235 # Nanjing
     name     = "71. Corps"
     id       = {  type = 22002 id = 146  }
	  Division = 
     {  experience = 30
       id         = {  type = 22002 id = 149 } 
       name       = "91. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }
	
	landunit = 
   {  location = 1235 # Nanjing
     name     = "73. Corps" # Contains 15. Division from Hunan po. 1937
     id       = {  type = 22002 id = 150  }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 151 } 
       name       = "77. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 152 } 
       name       = "193. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }
	
	landunit = 
   {  location = 1235 # Nanjing
     name     = "20. Corps" # Contains 15. Division from Hunan po. 1937
     id       = {  type = 22002 id = 153  }
	  Division = 
     {  experience = 30
       id         = {  type = 22002 id = 154 } 
       name       = "133. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 155 } 
       name       = "134. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }
	landunit = 
   {  location = 1235 # Nanjing
     name     = "28. Corps" # Different from the Hunan task force.
     id       = {  type = 22002 id = 156  }
	  Division = 
     {  experience = 30
       id         = {  type = 22002 id = 157 } 
       name       = "52. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 158 } 
       name       = "80. Division (German)" 
       type       = infantry
	   strength  = 40
       model     = 6
	   extra1 = engineer
	   brigade_model1 = 2
	   extra2 = artillery
	   brigade_model2 = 2
      }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 159 } 
       name       = "192. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }

	landunit = 
   {  location = 1235 # Nanjing
     name     = "46. Corps"
     id       = {  type = 22002 id = 160  }
	  Division = 
     {  experience = 30
       id         = {  type = 22002 id = 161 } 
       name       = "175. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22002 id = 162 } 
       name       = "188. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }

	landunit = 
   {  location = 1235 # Nanjing
     name     = "52. Corps" # Contains 2. a. 25. Division from CGX po. 1937
     id       = {  type = 22002 id = 164  }
	  Division = 
     {  experience = 30
       id         = {  type = 22002 id = 165 } 
       name       = "195. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }

	landunit = 
   {  location = 1235 # Nanjing
     name     = "62. Corps"
     id       = {  type = 22002 id = 166  }
	  Division = 
     {  experience = 30
       id         = {  type = 22002 id = 167 } 
       name       = "95. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 168 } 
       name       = "151. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 169 } 
       name       = "157. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }

	landunit = 
   {  location = 1235 # Nanjing
     name     = "64. Corps" # Contains 131. Division from Sichuan Task Force po. 1937
     id       = {  type = 22002 id = 170  }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 171 } 
       name       = "156. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 172 } 
       name       = "159. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }

	landunit = 
   {  location = 1235 # Nanjing
     name     = "92. Corps" # Contains 21. Division from CGX po. 1937
     id       = {  type = 22002 id = 173  }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 174 } 
       name       = "56. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }

	# Unassigned
	landunit = 
   {  location = 1235 # Nanjing
     name     = "9. Army Group"
     id       = {  type = 22002 id = 180  }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 181 } 
       name       = "10. Division (German)" 
       type       = infantry
	   strength  = 40
       model     = 6
	   extra1 = engineer
	   brigade_model1 = 2
	   extra2 = artillery
	   brigade_model2 = 2
      }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 183 } 
       name       = "83. Division (German)" 
       type       = infantry
	   strength  = 40
       model     = 6
	   extra1 = engineer
	   brigade_model1 = 2
	   extra2 = artillery
	   brigade_model2 = 2
      }
	  	#ID 182 is USED! See 54. Corps
	  Division = 
     {  experience = 30
       id         = {  type = 22002 id = 230 } 
       name       = "46. Division (German)" 
       type       = infantry
	   strength  = 40
       model     = 8
	   extra1 = engineer
	   brigade_model1 = 2
	   extra2 = artillery
	   brigade_model2 = 6
      }
    }

	landunit = 
   {  location = 1235 # Nanjing
     name     = "10. Corps" #Contains 3. Division from CGX after 1937
     id       = {  type = 22002 id = 184  }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 185 } 
       name       = "190. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }
    }

	landunit = 
   {  location = 1235 # Nanjing
     name     = "35. Corps"
     id       = {  type = 22002 id = 187  }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 188 } 
       name       = "32. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }

    }

	landunit = 
   {  location = 1235 # Nanjing
     name     = "NRA You. Force"
     id       = {  type = 22002 id = 189  }
	 Division = 
     {  experience = 30
       id         = {  type = 22002 id = 190 } 
       name       = "201. Division" 
       type       = infantry
	   strength  = 40
       model     = 3
      }

    }
	# Name = "60. Corps" #Contains units from Yunnan 10. Route Army

	# German Trained
	# CGX Controlled: 3rd, 6th, 9th
	# Central Controlled: 14th, 36th, 46th, 87th, 88th

	# In Progress
	# CGX Controlled: 2nd, 4th, 25. (Only in 1936), 27. (Only in 1936)
	# Central Controlled: 10th, 11th, 57th, 67th, 80th, 83rd, 89. 

	################
	# Airforce OOB #
	################
	# Main
	airunit = 
   {  location = 2569 # Nanchang
     name     = "RoC Airforce" 
     base     = 2569 # Nanchang
     id       = {  type = 22002 id = 196  } 
     Division = 
     {  id           = {  type = 22000 id = 197  } 
       name         = "1/2/3/9/10. Squadrons" 
       type         = tactical_bomber
       model        = 2
       strength     = 60
      } 
	  Division = 
     {  id           = {  type = 22000 id = 198  } 
       name         = "21/22/23/24/25. Squadrons" 
       type         = interceptor 
       model        = 3
       strength     = 48
      } 
	  Division = 
     {  id           = {  type = 22000 id = 199  } 
       name         = "4/5/15/26/27. Squadrons" 
       type         = tactical_bomber 
       model        = 1
       strength     = 46
      }
	  Division = 
     {  id           = {  type = 22000 id = 200  } 
       name         = "15/6/35. Squadron" 
       type         = multi_role
       model        = 1
       strength     = 27
      } 
	  Division = 
     {  id           = {  type = 22000 id = 203  } 
       name         = "Transport Squadron" 
       type         = transport_plane
       model        = 0
       strength     = 20
      }
    }
	
	############
	# Navy OOB #
	############
	navalunit = 
   {  location = 2529 # Qingdao 
     name     = "1. Fleet" 
     id       = {  type = 22002 id = 204  } 
     base     = 2529
	  Division = 
     {  id    = {  type = 22000 id = 205  } 
       name  = "Ninghai"
       type  = light_cruiser
	   strength = 100
       model = 3  #Interwar
      } 
	  Division = 
     {  id    = {  type = 22000 id = 206  } 
       name  = "Pinghai"
       type  = light_cruiser
	   strength = 100
       model = 3  #Interwar
      } 
	 Division = 
     {  id    = {  type = 22000 id = 207  } 
       name  = "Datong, Ziqiang" 
       type  = destroyer
	   strength = 40
       model = 0  #Gunboat
	   experience = 10
      }
	   Division = 
     {  id    = {  type = 22000 id = 208  } 
       name  = "Yixian"
       type  = light_cruiser
	   strength = 100
       model = 2  #Early Light
      } 
	  Division = 
     {  id    = {  type = 22000 id = 209  } 
       name  = "Hairong"
       type  = light_cruiser
	   strength = 100
       model = 1  #Scout Cruiser
      } 
	  Division = 
     {  id    = {  type = 22000 id = 210  } 
       name  = "Haichou"
       type  = light_cruiser
	   strength = 100
       model = 1  #Scout Cruiser
      } 
	 Division = 
     {  id           = {  type = 22000 id = 211  } 
       name  = "Yongjian, Yongji, Zhongshan, Jiankang" 
       type  = destroyer
	   strength = 80
       model = 0  #Gunboat
	   experience = 20
      }

	 Division = 
     {  id           = {  type = 22000 id = 212  } 
       name  = "Dingan, Kean" 
       type  = destroyer
	   strength = 40
       model = 0  #Gunboat
	   experience = 20
      }
	}
	navalunit = 
   {  location = 2529 # Qingdao 
     name     = "2. Fleet" 
     id       = {  type = 22002 id = 213  } 
     base     = 2529

	 Division = 
     {  id    = {  type = 22000 id = 214  } 
       name  = "Minquan, Minsheng, Xianning, Chutong, Chutai" 
       type  = destroyer
	   strength = 100
       model = 0  #Gunboat
	   experience = 10
      }
	  Division = 
     {  id    = {  type = 22000 id = 215  } 
       name  = "Chuyou, Chuguan, Chuqian, Jiangyuan, Jiangzhen" 
       type  = destroyer
	   strength = 100
       model = 0  #Gunboat
	   experience = 10
      }
	 Division = 
     {  id           = {  type = 22000 id = 216  } 
       name  = "Jiangkun, Jiangxi" 
       type  = destroyer
	   strength = 40
       model = 0  #Gunboat
	   experience = 20
      }
	 Division = 
     {  id           = {  type = 22000 id = 217  } 
       name  = "Hupeng, Hue, Huying, Hucui" 
       type  = destroyer
	   strength = 80
       model = 0  #Gunboat
	   experience = 20
      }
	}
     navalunit = 
   {  location = 2529 # Qingdao 
     name     = "Training Fleet" 
     id       = {  type = 22002 id = 218  } 
     base     = 2529
	 Division = 
     {  id    = {  type = 22000 id = 219  } 
       name  = "Yingrui"
       type  = light_cruiser
	   strength = 100
       model = 2  #Early Light
      } 
	 Division = 
     {  id    = {  type = 22000 id = 220  } 
       name  = "Tongji"
       type  = light_cruiser
	   strength = 100
       model = 2  #Early Light
      }
	}
	navalunit = 
   {  location = 2529 # Qingdao 
     name     = "3. Fleet" 
     id       = {  type = 22002 id = 221  } 
     base     = 2529
	 Division = 
     {  id    = {  type = 22000 id = 222  } 
       name  = "Zhenhai"
       type  = heavy_cruiser
	   strength = 100
       model = 1  #Armored Cruiser
      }
	 Division = 
     {  id           = {  type = 22000 id = 223  } 
       name  = "Tongan, Yongxiang, Chuyu, Jiangli" 
       type  = destroyer
	   strength = 80
       model = 0  #Gunboat
	   experience = 20
      }
	  Division = 
     {  id           = {  type = 22000 id = 224  } 
       name  = "Dinghai" 
       type  = destroyer
	   strength = 20
       model = 0  #Gunboat
	   experience = 20
      }
	}
	navalunit = 
   {  location = 2529 # Qingdao 
     name     = "RoC Naval Academy Fleet" 
     id       = {  type = 22002 id = 225  } 
     base     = 2529
	   Division = 
     {  id           = {  type = 22000 id = 226  } 
       name  = "Wen-42, Wen-88, Wen-93, Shi-34, Shi-102" 
       type  = destroyer
	   strength = 100
       model = 0  #Gunboat
	   experience = 20
      }
	  Division = 
     {  id           = {  type = 22000 id = 227  } 
       name  = "Shi-181, Yue-22, Yue-253, Yue-371" 
       type  = destroyer
	   strength = 80
       model = 0  #Gunboat
	   experience = 20
      }
	 Division = 
     {  id           = {  type = 22000 id = 228  } 
       name  = "Haijing, Junhe, Cedian, Boxian" 
       type  = destroyer
	   strength = 80
       model = 0  #Gunboat
	   experience = 20
      }
     Division = 
     {  id    = {  type = 22000 id = 229  } 
       name  = "Tongxin, Tongde, Ziyouzhongguo"
       type  = transport
	   strength = 60
       model = 0  
      } 
	}
	# ID 230 USED! See 46. Division
	division_development = {
		name = "Ping-Hai"
		type = light_cruiser
		model = 1
		cost = 0.1
		id = { type = 22002 id = 311 } 
		new_model = no
		date = { year = 1936 month = june day = 18 }
	}
	
	division_development = {
		name  = "14. Division (German)" 
		type  = infantry
		model = 8
		new_model = no
		extra1 = engineer
		brigade_model1 = 2
		extra2 = artillery
		brigade_model2 = 6
		cost  = 9
		id    = {  type = 22000 id = 142  } 
		date  = {  year = 1936 month = july day = 1  } 
	}
	division_development = {
		name  = "11. Division (German)" 
		type  = infantry
		model = 6
		new_model = no
		extra1 = engineer
		brigade_model1 = 2
		extra2 = artillery
		brigade_model2 = 4
		cost  = 9
		id    = {  type = 22000 id = 120  } 
		date  = {  year = 1936 month = september day = 1  } 
	}
	division_development = {
		name  = "CMA Training Division" 
		type  = infantry
		model = 7
		new_model = no
		extra1 = engineer
		brigade_model1 = 2
		cost  = 6
		id    = {  type = 22000 id = 43  } 
		date  = {  year = 1936 month = september day = 5  } 
	}
	division_development = {
		name  = "New 38. Division" 
		type  = infantry
		model = 6
		new_model = no
		extra1 = artillery
		brigade_model1 = 4
		cost  = 7
		id    = {  type = 22000 id = 110  } 
		date  = {  year = 1936 month = august day = 1  } 
	}
	division_development = {
		name  = "87. Division (German)" 
		type  = infantry
		model = 8
		new_model = no
		extra1 = engineer
		brigade_model1 = 2
		extra2 = artillery
		brigade_model2 = 6
		cost  = 9
		id    = {  type = 22000 id = 147  } 
		date  = {  year = 1936 month = august day = 1  } 
	}
	division_development = {
		name  = "88. Division (German)" 
		type  = infantry
		model = 8
		new_model = no
		extra1 = engineer
		brigade_model1 = 2
		extra2 = artillery
		brigade_model2 = 6
		cost  = 9
		id    = {  type = 22000 id = 148  } 
		date  = {  year = 1936 month = july day = 1  } 
	}
}