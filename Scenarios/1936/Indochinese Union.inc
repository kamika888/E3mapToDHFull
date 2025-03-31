 
 ############################## 
 # Country definition for U03 INDOCHINESUNION # 
 ############################## 
  
 country = 
 { tag                    = U03 
   capital                = 1333 
   puppet                 = FRA 
   ai_settings			 = { flags = { puppetLevel7 = 1 } }
	# Resource Reserves 
	energy                 = 420
	metal                  = 210
	rare_materials         = 105
	oil                    = 500 
	supplies               = 2000 
	money                  = 50 
	manpower               = 26 
	transports             = 100 
	escorts                = 10 
      
   diplomacy = 
   {   
   relation = {  tag = FRA value = 50 access = yes  }  
    } 
   SpyInfo                = {  country = "U03" NumberOfSpies = 3  } 
  
    
   nationalprovinces      = {  } 
   ownedprovinces         = { 1333 1326 1328 1334 1335 1337 1338 1306 1329 1332 1589 1336 1340 1339 1341 3121 3122 3120 3116 3117 3119 3118 2950 2949 2948 2947 2946 3129 2944 2945 2943 5836 5873 5891 5892 5893 5872 7024 7025 7026 7027 7028 7029 7030 7031 7032 7906 7907 7908 7909 7910 7987 7988 7989 7990 } 
   controlledprovinces    = { 1333 1326 1328 1334 1335 1337 1338 1306 1329 1332 1589 1336 1340 1339 1341 3121 3122 3120 3116 3117 3119 3118 2950 2949 2948 2947 2946 3129 2944 2945 2943 5836 5873 5891 5892 5893 5872 7024 7025 7026 7027 7028 7029 7030 7031 7032 7906 7907 7908 7909 7910 7987 7988 7989 7990 } 
   claimedprovinces 	  = { 5836 5873 5891 5892 5893 5872 
   1333 1326 1328 1334 1335 1337 1338 1306 1329 1332 1589 1336 1340 1339 1341 3121 3122 3120 3116 3117 3119 3118 2950 2949 2948 2947 2946 3129 2944 2945 2943 7024 7025 7026 7027 7028 7029 7030 7031 7032 7906 7907 7908 7909 7910 7987 7988 7989 7990
   }
   
  # FRA 1936 techs 
   # ###################### 
   techapps               = {  
 #Great War Infantry Division  
 1010  1020 1030 1040 1050 1060   
 #Early Mountain Division 
 1160  1170 1180 1190 1200 1210 1220 1230 1240  
 #Interbellum 1930 Supply 
 1910 1920 1930 1940 1950 1960 

 #1930 Cavalry Division  
 13060 13070 13080 1310 1320 1330 1340 1350 1360 1370  
 #Basic Armoured Car  
 2860 2870 2880 2020  
 #Great War Heavy Field Artillery 
 2290 2300 2310 
#Early Static Anti-Air Artillery 
2800 2450
#SW Tank 
7600 7610
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
#Improved Construction Engineering
5800 5080  
#Engineers
1830 1840 

#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810
#Medicine
5600 5610
# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Naval Doctrines
8010 8020 8050 
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
  } 
 inventions = { 3000027 }
   policy = 
   {  date              = {  year = 0 month = january day = 0  } 
     democratic        = 1 
     political_left    = 4 
     free_market       = 1
     freedom           = 3
     professional_army = 2 
     defense_lobby     = 3 
     interventionism   = 3
    } 

  # ################# 
   # ### OOB #### 
   # ################# 
     
    landunit = 
   {  id       = {  type = 13500 id = 2001  } 
     name     = "Division du Tonkin" 
     location = 1333 
     Division = 
     {  id       = {  type = 13500 id = 2002  } 
       name     = "Division du Tonkin" 
	   model    = 7
       strength = 100 
       type     = infantry 
       extra    = engineer 
	   brigade_model = 2
      } 
     } 
    landunit = 
   {  id       = {  type = 13500 id = 2003  } 
     name     = "Division de Cochinchine-Cambodge" 
     location = 1333 
    Division = 
     {  id       = {  type = 13500 id = 2004  } 
       name     = "Division de Cochinchine-Cambodge" 
       strength = 100 
       type     = garrison
	   model    = 6
      } 
  } 
    landunit = 
   {  id       = {  type = 13500 id = 2005  } 
     name     = "Brigade d'Annam" 
     location = 1333 
     Division = 
     {  id       = {  type = 13500 id = 2006  } 
       name     = "Tirailleurs annamites" 
       strength = 100 
       type     = militia
	   model    = 4
      }  
     Division = 
     {  id       = {  type = 13500 id = 2007  } 
       name     = "Tirailleurs tonkinois" 
       strength = 100 
       type     = militia
	   model    = 4
      }  
	Division = 
     {  id       = {  type = 13500 id = 2008  } 
       name     = "Tirailleurs cambodgiens" 
       strength = 100 
       type     = militia
	   model    = 4
      }  
    } 
  }