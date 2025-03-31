#####################
# Country main data #
#####################

country =
{ tag                    = SIA
	# Resource Reserves 
	energy                 = 540
	metal                  = 270
	rare_materials         = 135
	transports = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	manpower               = 4 
  capital                = 1343
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 4 
     freedom           = 4 
     free_market       = 1
     professional_army = 5 
     defense_lobby     = 3 
     interventionism   = 4 
  }
  nationalprovinces      = { 1348 1347 1345 1343 1342 1331 1330 1344 1303 1289 2951 3124 3125 3126 3127 3128 3130 3131
7016 7017 7018 7019 7020 7021 7022 7023 7905 7915 7916
  }
  ownedprovinces         = { 1348 1347 1345 1343 1342 1331 1330 1344 1303 1289
2951 3124 3125 3126 3127 3128 3130 3131
7016 7017 7018 7019 7020 7021 7022 7023 7905 7915 7916
  }
  controlledprovinces    = { 1348 1347 1345 1343 1342 1331 1330 1344 1303 1289
2951 3124 3125 3126 3127 3128 3130 3131
7016 7017 7018 7019 7020 7021 7022 7023 7905 7915 7916
  }
	claimedprovinces  	 = { 1305 1589 3116 3122 1341 1554 1553 5737 5734 7025 1340 3121 } 
  # ROTW Minor Tech '36
  # Group D 1936 techs
  # ######################
  # GW fighter
   techapps               = {  
#Interwar Fighter  
4500 4510 4520 4530 4540 4550 4010   
#Interwar Bomber 
4600 4610 4620 4630 4120   
#Basic Armoured Car  
2860 2870 2880 2020   
#Great War Heavy Field Artillery 
2290 2300 2310  
#SW Tank 
7600 7610 
#Great War Infantry Division  
1010  1020 1030 1040 1050 1060 
#Great War Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240
#Interbellum Supply 
1910 1920 1930 1940 1950 1960
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade 
2810 2820 2510  
#Manufactoring
5810 5820 
#Improved Construction Engineering 
5800 5080 

#Great War Destroyer 
3010 3020 3030 3040 
#Early Light Cruiser 
3110 3120 3130
#Short Range Submarine 
3610 3620 
#Naval Doctrines
8010 8050  
#Naval Infantry
#1560 
#Engineers
1830 1840 
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810
#Medicine
5600 5610
#Land Doctrines WWI - Entente line
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Landdoctrine ww2 - none

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010

} 
inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = ENG value = 70  } 
     relation = {  tag = FRA value = -100  } 
     relation = {  tag = JAP value = 75  } 
     relation = {  tag = MAN value = 75  } 
    } 
   SpyInfo                = {  country = "SIA" NumberOfSpies = 5  } 
   headofstate            = {  type = 9 id = 290001  } 
   headofgovernment       = {  type = 9 id = 290002  } 
   foreignminister        = {  type = 9 id = 290003  } 
   armamentminister       = {  type = 9 id = 290007  } 
   ministerofsecurity     = {  type = 9 id = 290005  } 
   ministerofintelligence = {  type = 9 id = 290006  } 
   chiefofstaff           = {  type = 9 id = 290004  } 
   chiefofarmy            = {  type = 9 id = 290008  } 
   chiefofnavy            = {  type = 9 id = 290009  } 
   chiefofair             = {  type = 9 id = 290010  } 
 
   landunit = 
   {  location = 1343 
     name     = "Royal Thai Army" 
     id       = {  type = 23600 id = 1  } 
     Division = 
     {  id       = {  type = 23600 id = 2  } 
       name     = "1. Thai Infantry Div." 
       type     = infantry 
	   model = 7
       strength = 90 
      } 
     Division = 
     {  id       = {  type = 23600 id = 3  } 
       name     = "2. Thai Infantry Div." 
       type     = infantry 
	   model = 6
       strength = 70 
      } 
     Division = 
     {  id       = {  type = 23600 id = 4  } 
       name     = "3. Thai Infantry Div." 
       type     = infantry 
	   model = 6
       strength = 30 
      } 
     Division = 
     {  id       = {  type = 23600 id = 5  } 
       name     = "4. Thai Infantry Div." 
       type     = infantry 
	   model = 6
       strength = 30 
      } 
     Division = 
     {  id       = {  type = 23600 id = 6  } 
       name     = "6. Thai Cavalry Div." 
       type     = cavalry 
	   model = 6
       strength = 30 
      } 
    } 
   landunit = 
   {  location = 1343 
     name     = "Royal Thai Police Force" 
     id       = {  type = 23600 id = 8  } 
     Division = 
     {  id       = {  type = 23600 id = 9  } 
       name     = "1. Royal Thai Police Div." 
       type     = garrison
		model = 3 
       strength = 30 
       extra    = police 
	   brigade_model = 1
      } 
    } 
   navalunit = 
   {  location = 3128 
     base     = 3128 
     name     = "Royal Thai Navy" 
     id       = {  type = 23600 id = 10  } 
     Division = 
     {  id    = {  type = 23600 id = 11  } 
       name  = "RTNS Sri Ayuthia" 
       type  = light_cruiser 
       model = 2 
      } 
     Division = 
     {  id    = {  type = 23600 id = 12  } 
       name  = "RTNS Dhonburi" 
       type  = light_cruiser 
       model = 2 
      } 
     Division = 
     {  id    = {  type = 23600 id = 13  } 
       name  = "Phra Ruang Flotille" 
       type  = destroyer 
       model = 2
      } 
    } 
   airunit = 
   {  location = 1345 
     base     = 1345 
     name     = "Royal Thai Airforce" 
     id       = {  type = 23600 id = 20  } 
     Division = 
     {  id       = {  type = 23600 id = 21  } 
       name     = "1. RTAF Fighter Group" 
       type     = interceptor 
       model    = 4 
       strength = 50 
      } 
     Division = 
     {  id       = {  type = 23600 id = 22  } 
       name     = "1. RTAF Tactic Bomb Group" 
       type     = tactical_bomber 
       model    = 3
       strength = 44 
      } 
    } 
  } 
 
