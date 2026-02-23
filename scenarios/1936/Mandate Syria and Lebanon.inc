 
 ############################## 
 # Country definition for U04 French Mandate for Syria and the Lebanon # 
 ############################## 
  
 ##################### 
 # Country main data # 
 ##################### 

 country = 
 {  tag                    = U04 
    capital                = 1794 #if capital is Damascus, for some reason the puppet auto-convoy system doesn't work. But it works if the capital is Beirut.
    puppet                 = VIC 
	#control				  = VIC
	ai_settings			   = { flags = { RESInit = 1 puppetLevel9 = 1 ideology = 5 } }
	# Resource Reserves 
	energy                 = 60
	metal                  = 30
	rare_materials         = 15
	oil                    = 500 
	supplies               = 2000 
	money                  = 50 
	manpower               = 60 
	transports             = 100 
	escorts                = 10 
      
  free = { 
	ic = 2 
	energy = 2
	metal = 1 
	supplies = 1 
	transport = 0.1500 
	manpower = 0.0040 
  } 
  extra_tc = 5 
  SpyInfo                = { country = "U04" NumberOfSpies = 1 }
  diplomacy = 
   {   
   relation = {  tag = VIC value = 50 access = yes  }  
    } 
  
   claimedprovinces 	  = { 4146 1855 4125
							  1792 1795 2883 1863 2884 1862 2885 1861 2019 1793 1794 4152 4151 4150 1159 2876 7276 7277 7278 7279 7280 7281 7353 7354 7355 7356 7357 7358 7359 7360
   }
   nationalprovinces      = {  } 
   ownedprovinces         = { 1792 1795 2883 4150 2885 4151 1863 2884 1159 1862 1861 4152 2019 1793 1794 7276 7277 7278 7279 7280 7281 7353 7354 7355 7356 7357 7358 7359 7360 } 
   controlledprovinces    = { 1792 1795 2883 4150 2885 4151 1863 2884 1159 1862 1861 4152 2019 1793 1794 7276 7277 7278 7279 7280 7281 7353 7354 7355 7356 7357 7358 7359 7360 } 
   
  # VIC 1936 techs 
   # ###################### 
   techapps               = {  
#Great War Infantry Division  
1010  1020 1030 1040 1050 1060    
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240  
#1930 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 1350 1360 1370

#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960

#Basic Armoured Car  
2860 2870 2880 2020

#Great War Heavy Field Artillery 
2290 2300 2310 
#Early Anti-Tank Artillery 
#2400
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
# Interwar Bomber 
4600 4610 4620 4630 4120

#Improved Construction Engineering 
5800 5080 
 
#Engineers
1830 1840 
#Firepower Focus Doctrine 
6010 
#Grand Battleplan Doctrine 
6030
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810
#Medicine
5600
# Land Doctrines WW1 - Entente (default)
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
     political_left    = 5 
     free_market       = 2
     freedom           = 3 
     professional_army = 2 
     defense_lobby     = 3 
     interventionism   = 3 
    } 

    landunit = 
   {  id       = {  type = 13501 id = 1001  } 
     name     = "Troupes du Levant" 
     location = 1792 
     Division = 
     {  id       = {  type = 13501 id = 1002  } 
       name     = "Forces supplétives du Levant" 
	   model    = 3
       strength = 50 
       type     = militia
      } 
     Division = 
     {  id       = {  type = 13501 id = 1003  } 
       name     = "Subdivision de Damas" 
       strength = 100 
       type     = militia
	   model    = 4
      } 
	Division = 
     {  id       = {  type = 13501 id = 1004  } 
       name     = "Subdivision de Alep" 
       strength = 100 
       type     = militia
	   model    = 4
      } 
    } 
    landunit = 
   {  id       = {  type = 13501 id = 1005  } 
     name     = "Subdivision de Beyrouth" 
     location = 1792 
     Division = 
     {  id       = {  type = 13501 id = 1006  } 
       name     = "Subdivision de Beyrouth" 
       strength = 100 
       type     = militia
	   model    = 4
      } 
    } 
	
	#It will unfortunately be wiped out by event during the French surrender. Not sure if there is a way to prevent that. Plus there are just a whole host of potential problems.
	#airunit = {
	#	id = { type = 13501 id = 5000 }
	#	name = "Armee de l'Air 1"
	#	control  = "VIC"
	#	location = 1794
	#	base = 1794 
	#	division = { id = { type = 13501 id = 5002 } name = "Gr. de Chasse I/7"						type = interceptor 		model = 8 strength = 60 }	#1937 Morane-Saulnier MS.406	
	#	division = { id = { type = 13501 id = 5003 } name = "Es. de Chasse 6" 						type = multi_role 		model = 5 strength = 60 }	#1940 Dewoitine D.520
	#}
	#airunit = {
	#	id = { type = 13501 id = 5001 }
	#	name = "Armee de l'Air 2"
	#	control  = "VIC"
	#	location = 1794
	#	base = 1794 
	#	division = { id = { type = 13501 id = 5004 } name = "Gr. de Bombardement I/39" 				type = tactical_bomber  model = 8 strength = 60 } 	#1938 Martin 167F
	#	division = { id = { type = 13501 id = 5005 } name = "Es. de Bombardement dAssaut 4/595" 	type = cas				model = 2 strength = 60 } 	#1940 Breguet 693/Potez 63-11
	#	division = { id = { type = 13501 id = 5006 } name = "Es. 4S" 								type = naval_bomber		model = 2 strength = 60 } 	#1938 Loire-Nieuport LN.411
	#}
	
	airdivision = { dormant = yes id = { type = 13501 id = 5002 } name = "Gr. de Chasse I/7"					type = interceptor 		model = 8 strength = 60 }	#1937 Morane-Saulnier MS.406	
	airdivision = { dormant = yes id = { type = 13501 id = 5003 } name = "Es. de Chasse 6" 						type = multi_role 		model = 5 strength = 60 }	#1940 Dewoitine D.520
	airdivision = { dormant = yes id = { type = 13501 id = 5004 } name = "Gr. de Bombardement I/39" 			type = tactical_bomber  model = 8 strength = 60 } 	#1938 Martin 167F
	airdivision = { dormant = yes id = { type = 13501 id = 5005 } name = "Es. de Bombardement dAssaut 4/595" 	type = cas				model = 2 strength = 60 } 	#1940 Breguet 693/Potez 63-11
	airdivision = { dormant = yes id = { type = 13501 id = 5006 } name = "Es. 4S" 								type = naval_bomber		model = 2 strength = 60 } 	#1938 Loire-Nieuport LN.411

}
