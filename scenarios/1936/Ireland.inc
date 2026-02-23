#####################
# Country main data #
#####################

country =
{ tag                    = IRE
  name					 = IRE36
  puppet				 = ENG
  ai_settings			 = { flags = { RESInit = 1 puppetLevel9 = 1 ideology = 6 } }
	manpower               = 0 
	# Resource Reserves 
	energy                 = 600
	metal                  = 300
	rare_materials         = 150
	transports 			   = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
    capital                = 30
  free = { 
	ic = 2 
	energy = 2
	metal = 1 
	supplies = 1 
	transport = 0.1500 
	manpower = 0.0040 
  } 
  extra_tc = 5 
  SpyInfo                = { country = "IRE" NumberOfSpies = 1 }
  diplomacy =
  { relation = { tag = ARG value = 20 }
    relation = { tag = AST value = 75 }
    relation = { tag = AUS value = 10 }
    relation = { tag = BEL value = 75 }
    relation = { tag = BRA value = 20 }
    relation = { tag = CAN value = 75 }
    relation = { tag = ENG value = 25 }
    relation = { tag = ETH value = 100 }
    relation = { tag = FIN value = 50 }
    relation = { tag = VIC value = 25 }
    relation = { tag = GER value = 15 }
    relation = { tag = HOL value = 75 }
    relation = { tag = HUN value = 25 }
    relation = { tag = ITA value = 20 }
    relation = { tag = LUX value = 75 }
    relation = { tag = MEX value = 30 }
    relation = { tag = NZL value = 75 }
    relation = { tag = POR value = 25 }
    relation = { tag = SAF value = 80 }
    relation = { tag = SOV value = 1 }
    relation = { tag = SPR value = 50 }
    relation = { tag = USA value = 75 }
  }
  claimedprovinces       = { 28 29 }
  nationalprovinces      = { 27 26 25 24 30 3048 3049 3050 3051 3052 3053 7128 7129 }
  ownedprovinces         = { 27 26 25 24 30 3048 3049 3050 3051 3052 3053 }
  controlledprovinces    = { 27 26 25 24 30 3048 3049 3050 3051 3052 3053 }
  # Western Minor Tech '36
  # Group D 1936 techs
  # ######################
  # GW fighter
   techapps               = { 
#Basic Armoured Car  
2860 2870 2880 2020 2150
#Early Tank 
7600 7610 2620 2010 2630 2640 2646 2650 
#Great War Heavy Field Artillery 
2290 2300 2310 2900
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Early Anti-Tank Artillery 
##2400
#Early Infantry Division  
1010  1020 1030 1040 1050 1060 1070 1080 1090
#1930 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 1350 1360 1370
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240
#Motorised Inf
1396
#Naval Infantry
1560
#Engineers
1830 1840 1850 1860
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 1970 1980
#Modern Agriculture 
5700 5710 5010
#Basic Machine Tools 
5810 5820 5050 5830 5060
#Improved Construction Engineering 
5800 5080 5090 
#improved Oil Refining #5190

#Computers 
5310 54010 54020 54030
#cryptografi
5316 5326
#Faculty of Atomic Research 
5470 5480
#Medicine
5600 5610 5620 5630
#Exp. Rocket
5560

#Improved Destroyer 
3010 3020 3030 3040 3050 3060 
#Basic Light Cruiser 
3110 3120 3130 3140 3150 3160
#Improved Heavy Cruiser 
3210 3220 3230 3240 3250 3260 
#Early Battleship 
3410 3420 3430 3440 3450 3456 3460 3470
#Great War Air Carrier 
3510
#Improved Light carrier 
12100 12110 12120
#Short Range Submarine 
3610 3620 3630 3640
# Battle Cruiser
3310 3320 3330 3340
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810 3820

#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Early Bomber 
4600 4610 4620 4630 4120 4130
#Multirole fighter
4300 4310 4320 4330
#SEAPLANES
4740 4750 4760 4770
#ww1 strategic bomber
4800 4810 4820
#ww1 navalbomber
4700 4710
#CAG 30
4900 4910
#Great War Hospital System 
14000 14010 14020

# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Land Doctrines
6560 6030

#Naval Doctrines
# Theories
8010 8020 8030 8040 8050 8060 8070 8080 
# Amphibious Warfare
82300
# Naval Logistics
82500
# Naval Interdiction
8500 8510 8550 8600 
# Engagement Tactic (Fleet-in-Being)
8900 8910 8920 8930 8940
# Naval Supremacy
8100 8110 8120 8150 8160 8200 8210

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010 9040

} 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 6 
     freedom           = 7 
     free_market       = 4
     professional_army = 1 
     defense_lobby     = 2 
     interventionism   = 2 
  }
inventions = { 3000027 }

   headofstate            = {  type = 9 id = 125001  } 
   headofgovernment       = {  type = 9 id = 125002  } 
   foreignminister        = {  type = 9 id = 125003  } 
   armamentminister       = {  type = 9 id = 125004  } 
   ministerofsecurity     = {  type = 9 id = 125005  } 
   ministerofintelligence = {  type = 9 id = 125006  } 
   chiefofstaff           = {  type = 9 id = 125007  } 
   chiefofarmy            = {  type = 9 id = 125098  } 
   chiefofnavy            = {  type = 9 id = 125009  } 
   chiefofair             = {  type = 9 id = 125010  } 
  # Firepower
   
   landunit = 
   {  id       = {  type = 21500 id = 1  } 
     name     = "Regiment of Rifle" 
     location = 30 
     Division = 
     {  id           = {  type = 21500 id = 2  } 
       name         = "1/2/3/4/5 Rifle Battalions" 
       strength     = 80 
       type         = infantry 
	   model    = 6
      } 
	Division = 
     {  id           = {  type = 21500 id = 3  } 
       name         = "Army Reserve" 
       strength     = 60 
       type         = infantry 
	   model    = 6
      } 
    } 
   navalunit = 
   {  id       = {  type = 21500 id = 5  } 
     name     = "Irish Republic Navy" 
     location = 30 
     base     = 30 
     # Division = {  
     # id = {  type = 21500 id = 6  } 
     # name = "1st Destroyer Flotilla" 
     # type = destroyer 
     # model = 2
     #  } 
     Division = 
     {  id    = {  type = 21500 id = 7  } 
       name  = "1st Transport Flotilla" 
       type  = transport 
       model = 0 
      } 
    } 
  } 
 