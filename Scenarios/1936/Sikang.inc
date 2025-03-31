#####################
# Country main data #
#####################

country =
{ tag                    = U05
  regular_id             = CHI
  puppet                 = CHI
  control				 = CHI
  ai_settings			 = { flags = { puppetLevel7 = 1 } }
  extra_tc               = 10
  dissent				 = 15
  # Resource Reserves
  energy                 = 200
  metal                  = 200
  rare_materials         = 100
  oil                    = 100
  supplies               = 100
  money                  = 50
  capital                = 1281 
  manpower               = 400
  diplomacy =
  { relation = { tag = CHC value = -200 }
    relation = { tag = CHI value = 200 }
    relation = { tag = CSX value = 200 }
    relation = { tag = CXB value = 200 }
    relation = { tag = CYN value = 200 }
    relation = { tag = JAP value = -75 }
    relation = { tag = MAN value = -75 }
  }

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
  ownedprovinces         = { 1281 5583 5581 5582 5580 5584 5585 5579 5578 5577 1903 5576 1282
  }
  controlledprovinces    = { 1281 5582 5580 5585 5579 5578 5577 1903 5576 1282
  }
  # Guangxi
  # ROTW Minor Tech '36
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
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 7 
     political_left    = 3 
     freedom           = 3 
     free_market       = 1
     professional_army = 7 
     defense_lobby     = 7 
     interventionism   = 7 
  }
   # Xikang
   # http://forum.paradoxplaza.com/forum/showthread.php?687389-OOB-and-information-of-China-for-moders&p=15451250&viewfull=1#post15451250
	landunit = 
   {  location = 1281 # Ya'an
     name     = "24. Corps" 
     # leader =  
     id       = {  type = 22100 id = 20  } 
     Division = 
     {  experience = 30 
       id         = {  type = 22100 id = 21  } 
       name       = "136. Division" 
       type     = infantry 
       strength   = 33
       model      = 2
	   extra1 = police
	   brigade_model1 = 1
      }
      Division = 
     {  experience = 30 
       id         = {  type = 22100 id = 22  } 
       name       = "137. Division" 
       type     = infantry
       strength   = 33
       model      = 2
	   extra1 = police
	   brigade_model1 = 1
      } 
     Division = 
     {  experience = 30 
       id         = {  type = 22100 id = 23  } 
       name       = "138. Division" 
       type       = infantry
       strength   = 33
       model      = 2
	   extra1 = police
	   brigade_model1 = 1
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22100 id = 24  } 
       name       = "30/33/34. Independent Brigades" 
       type       = infantry
       strength   = 40
       model      = 2
      }
	  Division = 
     {  experience = 30 
       id         = {  type = 22100 id = 25  } 
       name       = "1. Sikang Provincial Militia" 
       type       = militia
       strength   = 40
       model      = 1
      }
    }
  } 
  