##################### 
# Country main data # 
##################### 
 
 country = 
 { tag                    = MOR 
   capital                = 2331 
   puppet				  = ENG
   name					  = MOR36
   flag_ext			      = _TIZ
   ai_settings			  = { flags = { puppetLevel7 = 1 demilitarized = 1 } }

   # Resource Reserves 
   energy                 = 100 
   metal                  = 100 
   rare_materials         = 50 
   oil                    = 50 
   supplies               = 100 
   money                  = 50 
   manpower               = 0

   SpyInfo                = {  country = "MOR" NumberOfSpies = 3  } 
  
    
   nationalprovinces      = {  2331  } 
   ownedprovinces         = {  2331  } 
   controlledprovinces    = {  2331  } 
   
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
# Inf support 
1910 1920 1930 1940 1950 1960
#Early Static Anti-Air Artillery 
2800
#SW Tank 
7600 7610
#Early Infantry Division  
1010 1020 1030 1040 1050 1060 1070
#Early Mountain Division
1160  1170 1180 1190 1200 1210 1220 
#1916 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Agriculture
5700 
# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 

 }
  inventions = { 3000027 }
  diplomacy =
  { relation = { tag = ENG value = 50 }
    relation = { tag = FRA value = 50 }
    relation = { tag = SPA value = 50 }
    relation = { tag = ITA value = 50 }
  }
 inventions = {  }  
   policy = 
   {  date              = {  year = 0 month = january day = 0  } 
     democratic        = 1 
     political_left    = 5 
     free_market       = 1
     freedom           = 2
     professional_army = 1 
     defense_lobby     = 1 
     interventionism   = 1  
    } 
 
   landunit = 
   {  location = 2331 
     name     = "International Gendarmerie" 
     id       = {  type = 31501 id = 1  } 
     Division = 
     {  id   = {  type = 31501 id = 2  } 
       name = "International Gendarmerie Div." 
	   strength = 30
       type 	= garrison 
	   model    = 5
      } 
    } 
   }