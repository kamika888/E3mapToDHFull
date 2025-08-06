#####################
# Country main data #
#####################

country =
{ tag                    = SOV
  regular_id             = RUS
  intrinsic_gov_type     = leninist
  capital                = 1907
	# Resource Reserves 
	energy                 = 86000 
	metal                  = 40000 
	rare_materials         = 20000 
	oil                    = 4000 
	supplies               = 500 
	money                  = 30 
	manpower               = 1553 #mob 5 instead of 6
	dissent                = 12 
	transports             = 300 
	escorts                = 20 

  nationalprovinces      = { 1907 7308 3489 }
  ownedprovinces         = { 1907 7308 3489 }
  controlledprovinces    = { 1907 7308 3489 }
  # Rocket Test and Research Facility
  # Air Doctrines 1936
  # ################
	techapps               = {
		#1931 Infantry Division  
		1010 1020 1030 1040 1050 1060 1070 1080 1090
		#1930 Mountain Division 
		1160 1170 1180 1190 1200 1210 1220 1230 1240
		#SEMI-MOTORIZED CAVALRY 
		13060 13070 13080 1310 1320 1330 1340 1350 1360 1370 1380 1390
		#1935 Motorized Inf
		1396
		# Airborne Inf
		1670
		#Engineers
		1830 1840 1850
		#Interbellum 1930 Supply 
		1910 1920 1930 1940 1950 1960 1970
		#Early Tank 
		7600 7610 2620 2010 2630 2640 2646 2650 2030 2100
		#Basic Armoured Car  
		2860 2870 2880 2020
		#Early Field Artillery 
		2290 2300 2310 2900 2910 2920 2930 2940
		#Early Static Anti-Air Artillery 
		2800 2450 21180
		#Anti-Air Artillery Brigade
		2810 2820 
 
		#Improved Destroyer 
		3010 3020 3030 3040 3050 3060
		#Interwar Light Cruiser 
		3110 3120 3130 3140 3150 3160
		#Improved Heavy Cruiser 
		3210 3220 3230 3240 3250 3260
		#Great War Battlecruiser  
		3310 3320 3330 3340
		#Early Battleship 
		3410 3420 3430 3440 3450 3456 3460
		#Short Range Submarine 
		3610 3620 3630 3640 3650
		#Seaplane Carrier
		12100
		#Torpedo & ASW 18
		3720 3730 3736 3740 3750 3900
		#Troopships
		3810
	
		#Early Fighter  
		4500 4510 4520 4530 4540 4550 4010 4020
		#Early CAS
		4400
		#Early Bomber 
		4600 4610 4620 4630 4120 4130
		#Multirole fighter
		4300 4310 4320 4330 4340
		#ww1 strategic bomber
		4800 4810 4820
		#ww1 navalbomber
		4700 4710
		# Transports
		4290
		#SEAPLANES
		4740 4750 4760 4770
	
		#Modern Agriculture  
		5700 5710
		#Computers & cryptografi
		5310 54010 54020 54030 5316 5326
		#manufactoring
		5810 5820
		#Construction Engineering 
		5800 5080
		#Basic Oil Refining 
		5190
		#Medicine
		5600 5610 5620 
		#Exp. Rocket
		5560

		#Great War Hospital System 
		14000
		# Great War Land Doctrines (central powers)
		6500 6510 6530 6550 6590 6600 6620 6650 6670 6610 6680 6690 6700 6710 6910
		#Land Doctrines
		6570 6300 6900

		# Naval Doctrines 
		# Theory
		8010 8020 8030 8040 8050 8060 8070 8080
		# Amphib
		82300
		# Logistics
		82500
		# Naval Interdiction
		8500 8510 8550 8560 8600 8610
		# Indirect Approach
		81300 81310 81320 81330 81340
		# Naval Supremacy
		8100 8110 8120 8150 8160 8200

		#Air Doctrines - ww2 techs
		27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010 9040
 
	}
dormant_leaders        = {  30819 }	
blueprints             = {   } 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 9 
     freedom           = 5 
     free_market       = 4
     professional_army = 4 
     defense_lobby     = 3 
     interventionism   = 5 
  }
inventions = { 3000027 }
   headofstate            = {  type = 9 id = 30001  } # Kalinin 
   headofgovernment       = {  type = 9 id = 30016  } # Molotov 
   foreignminister        = {  type = 9 id = 30003  } 
   armamentminister       = {  type = 9 id = 30004  } 
   ministerofsecurity     = {  type = 9 id = 30005  } 
   ministerofintelligence = {  type = 9 id = 30006  } 
   chiefofstaff           = {  type = 9 id = 30153  } 
   chiefofarmy            = {  type = 9 id = 30008  } 
   chiefofnavy            = {  type = 9 id = 30009  } 
   chiefofair             = {  type = 9 id = 30010  } 
  
landunit = 
   {  id       = {  type = 10848 id =  1 } 
     name     = "Raboche-Krest'yanskaya Krasnaya Armyia" 
     location = 1907
     Division = 
     {  id       = {  type = 10848 id = 2  } 
       name     = "Generalnyi Shtab RKKA" 
       strength = 100
       type     = HQ
	   model    = 2
	   } 
 } 
landunit = { 
	id = { type = 10848 id = 3 }
	name = "Vozdushno Desantnye Voiska" 
	location = 3489

	division = { 
	id = { type = 10848 id = 4 } 
		name = "1-i Vozdushno-Desantnyi Korpus" 
		strength = 25 
		type = paratrooper
		model = 0
		} 
	}
landunit = { 
	id = { type = 10848 id = 5 }
	name = "Voiska NKVD" 
	location = 3489

	division = { 
	id = { type = 10848 id = 6 } 
		name = "1-ya Konvoynaya Diviziya NKVD" 
		strength = 100 
		type = garrison 
		model = 4
			} 
	division = { 
	id = { type = 10848 id = 7 } 
		name = "Diviziya o. n. Dzerzhinskogo" 
		strength = 100 
		type = motorized 
		model = 0 
		extra = armored_car
		brigade_model = 3
		} 
	}

   landunit = 
   {  id       = {  type = 10848 id =  8 } 
     name     = "Leningradskyi Voennyi Okrug" 
     location = 3489
     Division = 
     {  id       = {  type = 10848 id = 9  } 
       name     = "Leningradskyi Voennyi Okrug" 
       strength = 100 
       type     = HQ
	   model    = 2
	   extra    = anti_air
	   brigade_model = 0
	   } 
     Division = 
     {  id       = {  type = 10848 id =  10 } 
       name     = "25-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = heavy_armor
	brigade_model = 1
      } 
      Division = 
     {  id       = {  type = 10848 id = 11  } 
       name     = "7-i Mekhanizirovannyi Korpus" 
       strength = 100 
       type     = light_armor
	   model    = 0
	   extra    = heavy_armor
	   brigade_model    = 1	   
      } 	  
 } 
   landunit = 
   {  id       = {  type = 10848 id =  12 } 
     name     = "1-i Strelkovyi Korpus" 
     location = 3489
     Division = 
     {  id       = {  type = 10848 id = 13  } 
       name     = "16-ya Ulianovskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	   extra    = artillery
	   brigade_model    = 7		   
      }
     Division = 
     {  id       = {  type = 10848 id = 14  } 
       name     = "18-ya Yaroslavskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	   extra    = artillery
	   brigade_model = 7
      }
     Division = 
     {  id       = {  type = 10848 id = 15  } 
       name     = "20-ya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	   extra    = heavy_armor
	   brigade_model = 1
      }
 } 
   landunit = 
   {  id       = {  type = 10848 id =  16 } 
     name     = "19-i Strelkovyi Korpus" 
     location = 1907
     Division = 
     {  id       = {  type = 10848 id = 17  } 
       name     = "4-ya Turkestanskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	   extra    = artillery
	   brigade_model = 6
      }
     Division = 
     {  id       = {  type = 10848 id = 18  } 
       name     = "56-ya Moskovskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
      }
 }
 }	
