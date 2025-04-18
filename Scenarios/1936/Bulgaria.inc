#####################
# Country main data #
#####################

country =
{ tag                    = BUL
	# Resource Reserves 
	energy                 = 1500
	metal                  = 750
	rare_materials         = 375
	oil                    = 500 
	supplies               = 500 
	money                  = 50 
	manpower               = 0 
	transports             = 100 
	escorts                = 4 
  capital                = 417
  # navalunit = {
  # id = { type = 19000 id = 15 }
  # name = "Bulgarska Flota"
  # location = 422
  # base = 422
  # division = {
  # id = { type = 19000 id = 16 }
  # name = "1-va Podvodnikova flotilija"
  # type = destroyer
  # model = 0
  # }
  # }
  transports             = 10
  escorts                = 4
  diplomacy =
  { relation = { tag = ENG value = 20 }
    relation = { tag = FIN value = 35 }
    relation = { tag = FRA value = 20 }
    relation = { tag = GER value = 25 }
    relation = { tag = GRE value = -75 }
    relation = { tag = ITA value = 150 }
    relation = { tag = ROM value = 25 }
    relation = { tag = SOV value = 15 }
    relation = { tag = TUR value = 75 }
    relation = { tag = YUG value = 25 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 1 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 1 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 1 }
  SpyInfo                = { country = "CZE" NumberOfSpies = 1 }
  SpyInfo                = { country = "AUS" NumberOfSpies = 1 }
  SpyInfo                = { country = "GER" NumberOfSpies = 1 }
  SpyInfo                = { country = "HUN" NumberOfSpies = 1 }
  SpyInfo                = { country = "ALB" NumberOfSpies = 1 }
  SpyInfo                = { country = "GRE" NumberOfSpies = 1 }
  SpyInfo                = { country = "ROM" NumberOfSpies = 1 }
  SpyInfo                = { country = "ITA" NumberOfSpies = 1 }
  nationalprovinces      = { 
417 419 420 422 421 416 413 414 410 423 2323 2324 1911 
2612 2610 3374 3397 3352 3353 3354 435 6564 6563 6505 7337 6506 6507 6510 2449
411 7319
  }
  ownedprovinces         = { 419 420 422 421 417 416 2323 2324 1911
2612
3352 3353 3354
6506 6507 6510 7337
  }
  controlledprovinces    = { 419 420 422 421 417 416 2323 2324 1911
2612
3352 3353 3354
6506 6507 6510 7337
  }
  claimedprovinces  	 = { 
1169 412 3055 3393 2321 2322 3398 436 1168 6562 6508 6511 7352 7055 2319
  }

  # Eastern Minor Tech '36
  # Group D 1936 techs
  # ######################
  # GW fighter
	techapps               = {  

	# Manufacturing
	5810 5820 5050 5830
	# Construction Engineering 
	5800 5080 5090 
	# Agriculture  
	5700 5710 5010
	# Computers & cryptography
	5310 54010 54020 54030 5316 5326
	# Medicine
	5600 5610 5620

	# Infantry Division  
	1010 1020 1030 1040 1050 1060 1070
	# Mountain Division 
	1160 1170 1180 1190 1200 1210 1220 1230 1240
	# Cavalry Division  
	13060 13070 13080 1310 1320 1330 1340 1350 1360
	# Engineers
	1830 1840 1850 
	# Supply 
	1910 1920 1930 1940 1950 1960

	# Tanks
	7600 7610 2620 2010 2630 2640 2646
	# Armoured Car  
	2860 2870 2880 
	# Field Artillery 
	2290 2300 2310 2900 2910 2920
	# Static Anti-Air Artillery 
	2800 2450 21180 21190
	# Anti-Air Artillery Brigade 
	2810 2820 2510

	# Hospital System
	14000 14010
	# Great War Land Doctrines (central powers)
	6500 6510 6530 6550 6590 6600 6620 6650 6670 6610 6680 6690 6700 6710 6910
	# Grand Battle Plan Doctrine
	6560

	# Destroyers
	3010
	# Torpedo & ASW 18
	3720 3730 3900
	# Troopships
	3810
	
	# Naval Doctrines
	8010 8020 8050 
	
	# Interceptor Fighter
	4500 4510 4520 4530 4540 4550 4010
	# Multirole Fighter
	4300 4310 4320 4330
	# Tactical Bomber
	4600 4610 4620 4630 4120
	# Strategic Bomber
	4800 4810 4820
	# Naval Bomber
	4700 4710

	# Air Doctrines - ww2 techs
	27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010

	} 

 inventions = { 3000027 }
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 4 
     free_market       = 1
     freedom           = 5 
     professional_army = 2 
     defense_lobby     = 4 
     interventionism   = 6
  }
   headofstate            = {  type = 9 id = 95001  } 
   headofgovernment       = {  type = 9 id = 95002  } 
   foreignminister        = {  type = 9 id = 95003  } 
   armamentminister       = {  type = 9 id = 95004  } 
   ministerofsecurity     = {  type = 9 id = 95060  } # Ivan Krasnovski
   ministerofintelligence = {  type = 9 id = 95006  } 
   chiefofstaff           = {  type = 9 id = 95007  } 
   chiefofarmy            = {  type = 9 id = 95008  } 
   chiefofnavy            = {  type = 9 id = 95009  } 
   chiefofair             = {  type = 9 id = 95010  } 
  # Firepower

   landunit = 
   {  id       = {  type = 19000 id = 1  } 
     location = 417 
     name     = "1-va Armija" 
     Division = 
     {  id       = {  type = 19000 id = 2  } 
       name     = "1-va Sofiiska pekhotna divizija" 
       strength = 20 
       type     = infantry 
       model    = 6
      } 

     Division = 
     {  id       = {  type = 19000 id = 4  } 
       name     = "1-va Konna divizija" 
       strength = 20 
       type     = cavalry 
       model    = 6
      } 
    } 
   landunit = 
   {  id       = {  type = 19000 id = 5  } 
     location = 417 
     name     = "2-ra Armija" 
     Division = 
     {  id       = {  type = 19000 id = 6  } 
       name     = "2-ra Trakiiska pekhotna divizija" 
       strength = 20 
       type     = infantry 
       model    = 7
      } 

     Division = 
     {  id       = {  type = 19000 id = 19  } 
       name     = "2-ra Konna divizija" 
       strength = 20 
       type     = cavalry 
       model    = 7 
      } 
    } 
   landunit = 
   {  id       = {  type = 19000 id = 9  } 
     location = 417 
     name     = "3-ta Armija" 
     Division = 
     {  id       = {  type = 19000 id = 10  } 
       name     = "3-ta Balkanska pekhotna divizija" 
       strength = 20 
       type     = infantry 
       model    = 7 
      } 

    } 
   landunit = 
   {  id       = {  type = 19000 id = 12  } 
     location = 417 
     name     = "4-ta Armija" 
     Division = 
     {  id       = {  type = 19000 id = 13  } 
       name     = "5-ta Dunavska pekhotna divizija" 
       strength = 20 
       type     = infantry 
       model    = 8 
       extra    = artillery 
	   brigade_model = 5
      } 
 
    } 
   # navalunit = {  
   # id = {  type = 19000 id = 15  } 
   # name = "Bulgarska Flota" 
   # location = 325 
   # base = 325 
   # Division = {  
   # id = {  type = 19000 id = 16  } 
   # name = "1-va Podvodnikova flotilija" 
   # type = destroyer 
   # model = 0 
   #  } 
   #  } 
  } 
 