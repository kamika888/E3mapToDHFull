#####################
# Country main data #
#####################

country =
{ tag                    = AUS
  # HACK to make sure that Germany gets the whole manpower pool, all units and resources on annex.
  # Unwanted side-effect: Will never accept peace with Germany.
  regular_id             = GER
  capital                = 463
	manpower               = 23 
	# Resource Reserves 
	energy                 = 1140
	metal                  = 570
	rare_materials         = 285
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
  diplomacy =
  { relation = { tag = ENG value = 75 }
    relation = { tag = FIN value = 55 }
    relation = { tag = FRA value = -10 }
    relation = { tag = GER value = 100 }
    relation =
    { tag        = HUN
      value      = 100
    }
    relation = { tag = IRE value = 10 }
    relation = { tag = ITA value = 125 }
    relation = { tag = SCH value = 50 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 1 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 1 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 1 }
  SpyInfo                = { country = "CZE" NumberOfSpies = 4 }
  SpyInfo                = { country = "GER" NumberOfSpies = 4 }
  SpyInfo                = { country = "SPR" NumberOfSpies = 1 }
  SpyInfo                = { country = "POL" NumberOfSpies = 3 }
  SpyInfo                = { country = "YUG" NumberOfSpies = 3 }
  SpyInfo                = { country = "HUN" NumberOfSpies = 4 }
  SpyInfo                = { country = "BUL" NumberOfSpies = 2 }
  SpyInfo                = { country = "USA" NumberOfSpies = 1 }
  SpyInfo                = { country = "ALB" NumberOfSpies = 1 }
  SpyInfo                = { country = "ROM" NumberOfSpies = 2 }
  SpyInfo                = { country = "ITA" NumberOfSpies = 4 }
  
  nationalprovinces      = { 
							 307 208 3264 483 #Poland
							 456 3363 494 3370 495 430 3382 197 205 3715 1839 3717 3463 #Foreign germans
							 66  67  74  75  76  80  81  82  83  84  85  86  87  88  
							 89  90  296 297 298 299 300 301 302 304 308 309 310 311 312 313
                             314 315 374 375 376 473 482 510 73 71 72 316 
							 223 1779 1810 1811 1400 1623 1595
							 1405 546 547 1014 970 989 1018 1016 1015
							 303 2606 533 532 486 2381 2292 2597 1904 2370
							 2627 2647
							 3238	3239	3240	3241	3242	3243	3244	3245	3246	
							 3247	3248	3249	3250	3251	3252	3253	3254	3255	
							 3256	3257	3258	3259	3260	3261
							 3216 3214 3215 2273 373 377 1408 462 461 3217 460 2329 463 2328 2327 465 464 467 53 466 3262 471 472 3376 3375
							 6500 6519 6520 6521 6518
							 6917
							 7045 7046 7047 7177 7178 7179 7180 7181 7182 7183 7184 7185 7186 7187 7188 7189 7190 7260 7266 7986
							 7040 459
                           }
  claimedprovinces = { 91 371 470 3228 469 1888 468 3229 475 474 3263 483 3264 208 307 3265 306 6560 2628 2296 7122 
	193 194 195 196 199 1886 3286 3394 #Estonia
	205 204 203 197 202 198 3283 3284 3285 #Latvia
	380 7124 666 2326 1082 2289
	#70
  }
  ownedprovinces         = { 373 377 460 461 462 463 464 465 2327 2328 2329 3217 3375 3376 7040 }
  controlledprovinces    = { 373 377 460 461 462 463 464 465 2327 2328 2329 3217 3375 3376 7040 }

  # Western Minor Tech '36
  # Group C 1936 techs
  # ######################
   techapps               = {  
#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020   
#Interwar Bomber 
4600 4610 4620 4630 4120   
#Multirole fighter
4300 4310 4320 4330
#ww1 strategic bomber
4800 4810 4820
#Engineers
1830 1840 1850 1860
#Medicine
5600 5610 5620 5630
#Basic Armoured Car  
2860 2870 2880 2020   
#Tankette 
7600 7610 2620 2010 2630 2640   
#Great War Heavy Field Artillery 
2290 2300 2310    
#Early Static Anti-Air Artillery 
2800 2450 21180 21190  
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Great War Infantry Division  
1010  1020 1030 1040 1050 1060 
#Great War Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240 
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 1970 1980
#Great War Hospital System 
14000 14010 14020
#Mechanized Agriculture 
5700 5710 5010 5020
#Manufactoring
5810 5820 5050 5830 5060
#Improved Construction Engineering 
5800 5080 5090
#Basic Oil Refining 
#5190 
#Computers & cryptografi
5310 54010 54020 54030 5316 5326
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
# Great War Land Doctrines (central powers)
6500 6510 6530 6550 6590 6600 6620 6650 6670 6610 6680 6690 6700 6710 6910
} 
 inventions = { 3000027 }
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 2
     free_market       = 1
     freedom           = 7 
     professional_army = 2 
     defense_lobby     = 3 
     interventionism   = 5
  }
   headofstate            = {  type = 9 id = 115001  } 
   headofgovernment       = {  type = 9 id = 115002  } 
   foreignminister        = {  type = 9 id = 115003  } 
   armamentminister       = {  type = 9 id = 115004  } 
   ministerofsecurity     = {  type = 9 id = 115005  } 
   ministerofintelligence = {  type = 9 id = 115006  } 
   chiefofstaff           = {  type = 9 id = 115007  } 
   chiefofarmy            = {  type = 9 id = 115008  } 
   chiefofnavy            = {  type = 9 id = 115009  } 
   chiefofair             = {  type = 9 id = 115010  } 
   
   
   landunit = 
   {  id       = {  type = 14000 id = 9000  } 
     location = 463 
     name     = "Oberkommando des Bundesheeres" 
     Division = 
     {  id       = {  type = 14000 id = 9001  } 
       name     = "Schnelle Division" 
       type     = cavalry 
       model    = 7 
       strength = 50 
	extra = armored_car
	brigade_model = 2
      } 
     Division = 
     {  id       = {  type = 14000 id = 9002  } 
       name     = "1. Division" 
       type     = infantry 
       model    = 7 
       strength = 35
       extra    = artillery 
	   brigade_model = 6
      } 
     Division = 
     {  id       = {  type = 14000 id = 9003  } 
       name     = "2. Division" 
       type     = infantry 
       strength = 30 
       model    = 7
      } 
    } 
   landunit = 
   {  id       = {  type = 14000 id = 9004  } 
     location = 463 
     name     = "3. 'Niederösterreich' Division" 
     Division = 
     {  id       = {  type = 14000 id = 9005  } 
       name     = "3. Division" 
       type     = infantry 
	   strength = 30 
       model    = 6 
      } 
    } 
   landunit = 
   {  id       = {  type = 14000 id = 9006  } 
     location = 463 
     name     = "4. 'Oberösterreich' Division" 
     Division = 
     {  id       = {  type = 14000 id = 9007  } 
       name     = "4. Division"
       type     = infantry
       strength = 30
       model    = 7
      } 
    } 
   landunit = 
   {  id       = {  type = 14000 id = 9008  } 
     location = 463 
     name     = "5. 'Steiermark' Division" 
     Division = 
     {  id       = {  type = 14000 id = 9009  } 
       name     = "5. Division" 
       type     = bergsjaeger 
       strength = 40 
       model    = 7 
	extra = anti_air
	brigade_model = 1
      } 
    } 
   landunit = 
   {  id       = {  type = 14000 id = 9010  } 
     location = 463 
     name     = "6. 'Salzburg, Nordtirol und Vorarlberg' Division" 
     Division = 
     {  id       = {  type = 14000 id = 9011  } 
       name     = "6. Division" 
       type     = bergsjaeger
       strength = 25 
       model    = 7 
      } 
    } 
   landunit = 
   {  id       = {  type = 14000 id = 9012  } 
     location = 463 
     name     = "7. 'Kärnten und Osttirol' Division" 
     Division = 
     {  id       = {  type = 14000 id = 9013  } 
       name     = "7. Division" 
       type     = bergsjaeger 
       strength = 25 
       model    = 7 
      } 
    } 
  } 
 