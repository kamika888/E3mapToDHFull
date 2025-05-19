#####################
# Country main data #
#####################

province = { id = 49 air_base = { size = 10 current_size = 10 } naval_base = { size = 10 current_size = 10 } anti_air = 3 }
province = { id = 50 air_base = { size = 10 current_size = 10 } naval_base = { size = 10 current_size = 10 } anti_air = 3 }

country =
{ tag                    = BEL
  capital                = 51
	manpower               = 7 
	# Resource Reserves 
	energy                 = 2040
	metal                  = 1020
	rare_materials         = 510
	oil                    = 500 
	supplies               = 500 
	money                  = 20 
	transports             = 100 
	escorts                = 20 
  diplomacy =
  { relation = { tag = AST value = 75 }
    relation = { tag = CAN value = 150 }
    relation = { tag = DEN value = 100 }
    relation = { tag = ENG value = 150 }
    relation = { tag = FIN value = 100 }
    relation = { tag = FRA value = 120 }
    relation = { tag = GER value = 20 }
    relation = { tag = HOL value = 150 }
    relation = { tag = IRE value = 75 }
    relation = { tag = ITA value = -5 }
    relation = { tag = JAP value = -25 }
    relation = { tag = LUX value = 200 }
    relation = { tag = NOR value = 100 }
    relation = { tag = NZL value = 20 }
    relation = { tag = POR value = -20 }
    relation = { tag = SAF value = 35 }
    relation = { tag = SWE value = 100 }
    relation = { tag = USA value = 75 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 1 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 3 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 1 }
  SpyInfo                = { country = "GER" NumberOfSpies = 3 }
  SpyInfo                = { country = "DEN" NumberOfSpies = 1 }
  SpyInfo                = { country = "HOL" NumberOfSpies = 3 }
  SpyInfo                = { country = "LUX" NumberOfSpies = 1 }
  nationalprovinces      = { 51 45 50 52 65 68 69 70 7044 7043 1082 49 }
  claimedprovinces    	 = { 
2292 71 
1095 1142 1071 1072 1073 1074 1143 1144 1127 1098 1063 2283
2751 2752 2753 2754 2755 2756 2757 2758 2759 2760
4730 4731 4812 4813 4814 4815 4816 4817 4818 4819 
4820 4821 4822 4823 4824 4825 4826 4827 4828 4829 
4830 4831 4832 4833 4834 4835 4836 4837 4838 4839 
4840 4841 4842 4843 4844 4845 4846 4847 4848 4849 
4850 4851 4852 4853 4854 4855 4856 4857 4858 4859 
4860 4861 4862 4863 4864 4865 4866 4867 4868 4869 
4870 4871 4872 4873 4874 4875 4876 4877 4878 4879 4880
7036 7037 7038 7301 7302 7303 7364
  }
  ownedprovinces         = { 50 51
  }
  controlledprovinces    = { 50 51
  }
  
techapps               = { 
#Early Infantry Division  
1010 1020 1030 1040 1050 1060 1070 1080 1090
#SEMI-MOTORIZED CAVALRY 
13060 13070 13080 1310 1320 1330 1340 1350 1360 1370 1380
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240
#1922 NAVAL INFANTRY
1560
#Motorised Inf
1396
#Engineers
1830 1840 1850 1860
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 1970 1980

#Interwar Armoured Car 
2860 2870 2880 2020
#Armor 
7600 7610 2620 2010 2630 2640 2646 2650
#Great War Heavy Field Artillery 
2290 2300 2310 2900 2910 2920
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade 
2810 2820 2510

#Short Range Submarine 
3610 3620 3630 3640 3650
#Improved Destroyer 
3010 3020 3030 3040 3050 3060
#Basic Light Cruiser 
3110 3120 3130 3140 3150 3160
#Improved Heavy Cruiser 
3210 3220 3230 3240 3250 3260
#Interwar Battlecruiser
3310 3320 3330 3340
#Early Battleship 
3410 3420 3430 3440 3450 3456 3460 3470
#Improved Light carrier 
12100 12110 12120 12130
#Fleet Carrier 
3510 3520 3530
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810 3820

#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Early Bomber 
4600 4610 4620 4630 4120 4130
#Multirole fighter
4300 4310 4320 4330 4340
# Transports
4290
#ww1 navalbomber
4700 4710
#CAG 34
4900 4910 4920
#Basic Strategic Bomber 
4800 4810 4820 4220
#SEAPLANES
4740 4750 4760

#Agriculture
5700 5710 5010 5020
#Manufacturing
5810 5820 5050 5830 5060 5070
#Improved Construction Engineering 
5800 5080 5090
#Basic Oil Refining
5190
#Computers
5310 54010 54020 54030 
#Cryptography
5316 5326 5327
#Basic Decimetric Radar Warning Sites 
5410 5416 
#Faculty of Atomic Research 
5470
#Exp. Rocket
5560
#Medicine
5600 5610 5620 5630

#Great War Hospital System 
14000 14010 14020

# WWI Land Doctrines - Entente line: eng fra ita usa bel hol jap 
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# WWII Land Doctrines
6560 6030 

# Naval Doctrines
# 
# Theories
8010 8020 8030 8040 8050 8060 8070 8080
# Amphib
82300
# Logistic Support
82500
# Naval Interdiction
8500 8510 8520 8550 8560 8600 8610
# Engagement Tactics
8900 8910 8920 8930 8940 8950
# Naval Supremacy
8100 8110 8120 8150 8160 8200 8210
# Carrier Doctrine
81650
# Carrier - Scouting Focus Line
81850
# Carrier - Strike Line
81700

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010 9140

} 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 5 
     free_market       = 1
     freedom           = 9 
     professional_army = 3 
     defense_lobby     = 2 
     interventionism   = 2 
  }
inventions = { 3000027 } 

   headofstate            = {  type = 9 id = 1  } 
   headofgovernment       = {  type = 9 id = 2  } 
   foreignminister        = {  type = 9 id = 3  } 
   armamentminister       = {  type = 9 id = 56 } 
   ministerofsecurity     = {  type = 9 id = 5  } 
   ministerofintelligence = {  type = 9 id = 6  } 
   chiefofstaff           = {  type = 9 id = 7  } 
   chiefofarmy            = {  type = 9 id = 8  } 
   chiefofnavy            = {  type = 9 id = 9  } 
   chiefofair             = {  type = 9 id = 10 } 
 
   landunit = 
   {  id       = {  type = 11500 id = 1  } 
     location = 50 
     name     = "Ie Legerkorps" 
     Division = 
     {  id    = {  type = 11500 id = 2  } 
       name  = "1" 
	   strength     = 100
       type  = infantry 
	   model = 8 
      } 
     Division = 
     {  id   = {  type = 11500 id = 3  } 
       name = "2" 
	   strength     = 100
       type = infantry 
	   model = 8 
      } 
     Division = 
     {  id   = {  type = 11500 id = 4  } 
       name = "3" 
	   strength     = 100
       type = infantry 
	   model = 8 
      } 
     Division = 
     {  id   = {  type = 11500 id = 5  } 
       name = "4" 
	   strength     = 100
       type = infantry 
	   model = 8 
      } 
     Division = 
     {  id   = {  type = 11500 id = 6  } 
       name = "5" 
	   strength     = 100
       type = infantry 
	   model = 8 
      } 
     Division = 
     {  id   = {  type = 11500 id = 7  } 
       name = "6" 
	   strength     = 100
       type = infantry 
	   model = 8 
      } 
     Division = 
     {  id   = {  type = 11500 id = 8  } 
       name = "7" 
	   strength     = 100
       type = infantry 
	   model = 8 
      } 
     Division = 
     {  id   = {  type = 11500 id = 9  } 
       name = "8" 
	   strength     = 100
       type = infantry 
	   model = 8 
      } 
     Division = 
     {  id   = {  type = 11500 id = 10  } 
       name = "9" 
	   strength     = 100
       type = infantry 
	   model = 8 
      } 
     Division = 
     {  id   = {  type = 11500 id = 11  } 
       name = "10" 
	   strength     = 100
       type = infantry 
	   model = 8 
      } 
    } 

  } 
 
