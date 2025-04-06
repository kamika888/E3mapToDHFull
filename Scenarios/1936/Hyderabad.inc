##################### 
# Country main data # 
##################### 
 
 country = 
 {  tag                    = U37
    regular_id             = IND
	puppet                 = U02
	ai_settings			   = { flags = { puppetLevel6 = 1 } }
    capital                = 1507 

     # Resource Reserves 
   energy                 = 100 
   metal                  = 100 
   rare_materials         = 50 
   oil                    = 50 
   supplies               = 100 
   money                  = 50 
   manpower               = 200
   
   headofstate            = {  type = 9 id = 55500  } 
      
   transports             = 50 
   escorts                = 0 

   diplomacy = 
   {   
   relation = {  tag = ENG value = 80 access = no  }  
    } 
   SpyInfo                = {  country = "U06" NumberOfSpies = 3  } 
  
    
   nationalprovinces      = {  1507 702 5270 771 729 769 5269 5271 5268 697 5267 781  } 
   ownedprovinces         = {  1507 702 5270 771 729 769 5269 5271 5268 697 5267 781  } 
   controlledprovinces    = {  1507 702 5270 771 729 769 5269 5271 5268 697 5267 781  } 
   
  # FRA 1936 techs 
   # ###################### 
   techapps               = {  
#Great War Infantry Division  
1010  1020 1030 1040 1050 1060    
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240   
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 1970 1980   
#1930 Cavalry Division 
13060 13070 13080 1310 1320 1330 1340 1350 1360 1370
#Motorised Inf
1396
#Basic Armoured Car 
2860 2870 2880 2020   
#Great War Heavy Field Artillery 
2290 2300 2310 
#SW Tank 
7600 7610 2620 2010 
#Engineers
1830 1840 1850 1860
#Early Static Anti-Air Artillery 
2800 2450
#Great War Destroyer
3010 3020 3030 3040
#Interwar Light Cruiser 
3110 3120 3130 3140
#Early Heavy Cruiser 
3210 3220 3230
#Interwar Fighter 
4500 4510 4520 4530 4540 4550 4010
#Interwar Bomber 
4600 4610 4620 4630 4120
#Computers & cryptografi
5310 54010 54020 54030 5316 5326
#Manufactoring
5810 5820 5050 5830
#Improved Construction Engineering 
5800 5080 5090 
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810
#Medicine
5600
#Naval Doctrines
8010 8020 8050
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Defensive Focus Grand Battleplan Path (FRA / UK)
6560
} 
  inventions = { 3000027 }
  policy = 
   {  date              = {  year = 0 month = january day = 0  } 
     democratic        = 1 
     political_left    = 4 
     freedom           = 3 
     free_market       = 1
     professional_army = 2 # no conscription 
     defense_lobby     = 3 
     interventionism   = 3 
    } 
	
   landunit = 
   {  name     = "Hyderabad State Forces" 
     location = 1507 
     id       = {  type = 12700 id = 1049  } 
     Division = 
     {  id       = {  type = 12700 id = 1050  } 
       name     = "Hyderabad State Forces" 
       type     = militia
	   model    = 3
       strength = 100 
      } 
    }  
  }