#####################
# Country main data #
#####################

country =
{ tag                    = POR
	# Resource Reserves 
	energy                 = 1020
	metal                  = 510
	rare_materials         = 255
	oil                    = 500 
	supplies               = 500 
	money                  = 15 
	manpower               = 94 
	transports             = 100 
	escorts                = 7 
  capital                = 336
  # Azores
  diplomacy =
  { relation = { tag = BEL value = -20 }
    relation = { tag = BRA value = 75 }
    relation = { tag = ENG value = 100 }
    relation = { tag = FIN value = 50 }
    relation = { tag = GER value = 75 }
    relation = { tag = IRE value = 25 }
    relation = { tag = ITA value = 65 }
    relation = { tag = SAF value = 125 access = yes }
    relation = { tag = SPR value = -50 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 3 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 2 }
  SpyInfo                = { country = "SPR" NumberOfSpies = 4 }
  SpyInfo                = { country = "ARG" NumberOfSpies = 3 }
  SpyInfo                = { country = "ITA" NumberOfSpies = 1 }
  SpyInfo                = { country = "BRA" NumberOfSpies = 4 }
  SpyInfo                = { country = "MEX" NumberOfSpies = 1 }
  # Cabinda
  nationalprovinces      = { 335 336 337 344 345 1867 1563 1163 965 3206 3207 3208 3209 3210 3211 3212 1036 6492
7166 7167 7257 7258 7981 3178 3179 7121 1537 7119 7120 334 }
  claimedprovinces		 = {
1096 5076 4921 4928 2793 4940 5073 4927 983 1100 1133 5083 2792 4931 1102 1090 4918 7363 4922 4939 5072 5085 4941
7361 4920 4929 4942 5074 1658 1123 2637 5082 4936 4924 5090 2796 1131 7441 767 2794 1097 5089 1101 4915 2636 5077
5851 5075 5081 2791 1103 5079 1138 4925 2795 2789 2790 4930 4923 1094 4934 1122 5088 7440 7362 5091 4932 1130 4935
4943 5084 5852 1512 5087 1146 4917 4937 4919 4933 1316 4938 4926 5078 4916 4914 5086 4464 5080 
  }
  ownedprovinces         = { 335 336 337 344 345 1867 1146 983 1090 1096 1097 1101 1100 1102 1103 1122 1123 1130 1131 1133 1138 1658 1316 1094
							1563 1163 965
							1036 1512
							2636 2637 2789 2790 2791 2792 2793 2794 2795 2796
							3206	3207	3208	3209	3210	3211	3212
4464 4914 4915 4916 4917 4918 4919 4920 4921 4922 
4923 4924 4925 4926 4927 4928 4929 4930 4931 4932 
4933 4934 4935 4936 4937 4938 4939 4940 4941 4942 
4943 5072 5073 5074 5075 5076 5077 5078 5079 5080 
5081 5082 5083 5084 5085 5086 5087 5088 5089 5090 5091
5851 5852 6492
7166 7167 7257 7258 
7361 7362 7363 7440 7441 767
  }

  controlledprovinces    = { 335 336 337 344 345 1867 1146 983 1090 1096 1097 1101 1100 1102 1103 1122 1123 1130 1131 1133 1138 1658 1316 1094
							1563 1163 965
							1036 1512
							2636 2637 2789 2790 2791 2792 2793 2794 2795 2796
							3206	3207	3208	3209	3210	3211	3212
4464 4914 4915 4916 4917 4918 4919 4920 4921 4922 
4923 4924 4925 4926 4927 4928 4929 4930 4931 4932 
4933 4934 4935 4936 4937 4938 4939 4940 4941 4942 
4943 5072 5073 5074 5075 5076 5077 5078 5079 5080 
5081 5082 5083 5084 5085 5086 5087 5088 5089 5090 5091
5851 5852 6492
7166 7167 7257 7258 
7361 7362 7363 7440 7441 767
  }
  # Western Minor Tech '36
  # Group C 1936 techs
  # ######################
   techapps               = {  
 #Great War Infantry Division  
 1010  1020 1030 1040 1050 1060   
 #Early Mountain Division 
 1160  1170 1180 1190 1200 1210 1220 1230 1240  
 #Great War Cavalry Division  
 13060 13070 13080 1310 1320 1330 1340   
 #Tankette 
 7600 7610 2620 2010 2630 2640  
 #Basic Armoured Car  
 2860 2870 2880 2020  
 #Great War Heavy Field Artillery 
 2290 2300 2310 
 #Early Static Anti-Air Artillery 
 2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Naval Infantry
#1560 1570 1580
#Interbellum Supply 
1910 1920 1930 1940 1950 1960
#Engineers
1830 1840 1850 1860
#Improved Destroyer 
3010 3020 3030 3040 3050 3060
#Early Light Cruiser 
3110 3120 3130
#Short Range Submarine 
3610 3620 3630 3640
#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Interwar Bomber 
4600 4610 4620 4630 4120
#Multirole fighter
4300 4310 4320 4330
#ww1 strategic bomber
4800 4810 4820
#ww1 navalbomber
4700 4710
#Modern Agriculture  
5700 5710 5010
#Computers & cryptografi
5310 54010 54020 54030 5316 5326
#Manufactoring
5810 5820 5050 5830
#Improved Construction Engineering 
5800 5080 5090  
 #Basic Oil Refining 
 #5190 
 #Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810
#Medicine
5600 5610 5620 
#Improved Great War Hospital System
14000 14010

#Land Doctrines WWI - Entente Line
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Land Doctrine WWII - Firepower Focus?  WTF?  Really?
6010 6020
#Naval Doctrines
8010 8040 8050
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
} 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 3 
     freedom           = 5 
     free_market       = 1
     professional_army = 4 
     defense_lobby     = 2 
     interventionism   = 3 
  }
inventions = { 3000027 }
   headofstate            = {  type = 9 id = 20001  } 
   headofgovernment       = {  type = 9 id = 20002  } 
   foreignminister        = {  type = 9 id = 20003  } 
   armamentminister       = {  type = 9 id = 20004  } 
   ministerofsecurity     = {  type = 9 id = 20005  } 
   ministerofintelligence = {  type = 9 id = 20006  } 
   chiefofstaff           = {  type = 9 id = 20007  } 
   chiefofarmy            = {  type = 9 id = 20008  } 
   chiefofnavy            = {  type = 9 id = 20009  } 
   chiefofair             = {  type = 9 id = 20010  } 
 
   landunit = 
   {  id       = {  type = 14000 id = 1000  } 
     location = 336 
     name     = "Exército do Portugal" 
     Division = 
     {  id       = {  type = 14000 id = 1001  } 
       name     = "1o Batalhão de Infantaria" 
       type     = infantry 
	   model    = 7
       extra    = artillery 
	   brigade_model = 6
       strength     = 35 
      } 
     Division = 
     {  id       = {  type = 14000 id = 1002  } 
       name     = "2o Batalhão de Infantaria" 
       type     = infantry 
	   model    = 6
       strength     = 35 
      } 
	      Division = 
     {  id       = {  type = 14000 id = 1003  } 
       name     = "3o Batalhão de Infantaria" 
       type     = infantry 
	   model    = 6
       strength     = 35 
      } 
	 Division = 
     {  id           = {  type = 14000 id = 1004  } 
       name         = "4o Batalhão de Infantaria" 
       type         = infantry
	   model = 6
       strength     = 35 
       organisation = 30 
      }
     Division = 
     {  id           = {  type = 14000 id = 1005  } 
       name         = "5o Batalhão de Infantaria" 
       type         = infantry 
	   model = 6
       strength     = 35 
       organisation = 30 
      }
     Division = 
     {  id           = {  type = 14000 id = 1006  } 
       name         = "6o Batalhão de Infantaria" 
       type         = infantry
	   model = 6
       strength     = 35 
       organisation = 30 
      }	  
	 Division = 
     {  id           = {  type = 14000 id = 1007  } 
       name         = "7o Batalhão de Infantaria" 
       type         = infantry
	   model = 6	   
       strength     = 35 
       organisation = 30 
      }	   
	 Division = 
     {  id           = {  type = 14000 id = 1008  } 
       name         = "8o Batalhão de Infantaria" 
       type         = garrison
	   model = 3	
       strength     = 35 
       organisation = 30 
      }	  
	 Division = 
     {  id           = {  type = 14000 id = 1009  } 
       name         = "9o Batalhão de Infantaria" 
       type         = garrison
	   model = 3	
       strength     = 35 
       organisation = 30 
      }	
	 Division = 
     {  id           = {  type = 14000 id = 1010  } 
       name         = "10o Batalhão de Infantaria" 
       type         = garrison
	   model = 3	
       strength     = 35 
       organisation = 30 
      }	
    } 
   navalunit = 
   {  id       = {  type = 19600 id = 1003  } 
     location = 336 
     base     = 336 
     name     = "Transporte de Navio do Portugal" 
     Division = 
     {  id   = {  type = 19600 id = 1004  } 
       name = "1o Flotilha de Navio de Transporte" 
       type = transport 
	   model    = 0
      } 
     Division = 
     {  id       = {  type = 19600 id = 9303  } 
       name     = "Viana do Castello Flotilha" 
       type     = destroyer 
       model    = 4
       strength     = 100 
      } 
    } 
   navalunit = 
   {  id       = {  type = 19600 id = 1005  } 
     location = 336 
     base     = 336 
     name     = "Transporte de Navio de Colonias" 
     Division = 
     {  id   = {  type = 19600 id = 1006  } 
       name = "2o Flotilha de Navio de Transporte" 
       type = transport 
	   model    = 0
      } 
     Division = 
     {  id    = {  type = 19600 id = 1007  } 
       name  = "Douro Flotilha" 
       type  = destroyer 
       model = 0 
      } 
    } 
   navalunit = 
   {  id       = {  type = 19600 id = 9302  } 
     name     = "Marinha do Portugal" 
     location = 336 
     base     = 336 
     Division = 
     {  id       = {  type = 19600 id = 9304  } 
       name     = "1o Flotilha de Submarino" 
       type     = submarine 
       model    = 3 
       strength     = 100 
      } 
    } 
   airunit = 
   {  id       = {  type = 19600 id = 9300  } 
     name     = "Aéreo do Portugal" 
     location = 336 # Lissabon 
     base     = 336 
     Division = 
     {  id       = {  type = 19600 id = 9301  } 
       name     = "1o Avião de Bombardeiro Tático" 
       type     = tactical_bomber 
       strength     = 100 
       model    = 4
      } 
    } 
  } 
 
