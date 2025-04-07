#####################
# Country main data #
#####################

country =
{ tag                    = MON
  puppet                 = SOV
  control				 = SOV
  ai_settings			 = { flags = { puppetLevel8 = 1 } }
  ai                     = "exp_0.ai"
	# Resource Reserves 
	energy                 = 300
	metal                  = 150
	rare_materials         = 75
	oil                    = 200 
	supplies               = 500 
	money                  = 10 
	manpower               = 10 
  capital                = 1404
  diplomacy =
  { relation = { tag = CHC value = 25 }
    relation = { tag = MON value = 150 }
    relation = { tag = TAN value = 200 }
  }
  SpyInfo                = { country = "SOV" NumberOfSpies = 2 }
  SpyInfo                = { country = "CHI" NumberOfSpies = 1 }
  SpyInfo                = { country = "MAN" NumberOfSpies = 1 }
  SpyInfo                = { country = "CHI" NumberOfSpies = 1 }
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

  ownedprovinces         = { 1404 1420 1419 1434 1438 1385
3762 3763 3764 3765 3766 3767 3768 3769 3771 3772 3773
5476 5477 5478 5479 5480 
7917 7918 3761 3770
  }
  controlledprovinces    = { 1404 1420 1419 1434 1438 1385
3762 3763 3764 3765 3766 3767 3768 3769 3771 3772 3773
5476 5477 5478 5479 5480
7917 7918 3761 3770
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
#SW Tank 
7600 7610
#Early Infantry Division  
1010  1020 1030 1040 1050 1060 1070
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 1970
#1916 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Agriculture
5700 


#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470
# Land Doctrines WW1 - Entente Line (Default)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Land Doctrines WW2 - none

 } 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 9 
     freedom           = 3 
     free_market       = 1
     professional_army = 2 
     defense_lobby     = 4 
     interventionism   = 4
  }
 inventions = { 3000027 }
   headofstate            = {  type = 9 id = 300001  } 
   headofgovernment       = {  type = 9 id = 300002  } 
   foreignminister        = {  type = 9 id = 300003  } 
   armamentminister       = {  type = 9 id = 300004  } 
   ministerofsecurity     = {  type = 9 id = 300005  } 
   ministerofintelligence = {  type = 9 id = 300006  } 
   chiefofstaff           = {  type = 9 id = 300007  } 
   chiefofarmy            = {  type = 9 id = 300008  } 
   chiefofnavy            = {  type = 9 id = 300009  } 
   chiefofair             = {  type = 9 id = 300010  } 

   landunit = 
   {  location = 1404 
     name     = "Armija Mongol Nayramdakh" 
     id       = {  type = 30500 id = 1  } 
     Division = 
     {  id   = {  type = 30500 id = 2  } 
       name = "1. Nayramdakh Pekhotnaya Div." 
	   strength     = 50
       type = infantry 
	   model    = 6
      } 
     Division = 
     {  id   = {  type = 30500 id = 3  } 
       name = "2. Nayramdakh Kavaleriyskaya Div." 
	   strength     = 10
       type = cavalry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 30500 id = 4  } 
       name = "3. Nayramdakh Opolcheniya Div." 
	   strength     = 10
       type = militia 
	   model    = 3
      } 
     Division = 
     {  id   = {  type = 30500 id = 5  } 
       name = "4. Nayramdakh Opolcheniya Div." 
	   strength     = 10
       type = militia 
	   model    = 3
      } 
    } 
  } 
 
