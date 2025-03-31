#####################
# Country main data #
#####################

country =
{ tag                    = POL
  capital                = 485
	manpower               = 124 
	# Resource Reserves 
	energy                 = 2460
	metal                  = 1230
	rare_materials         = 615
	transports = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 20 
  diplomacy =
  { relation =
    { tag        = CZE
      value      = -1
    }
    relation = { tag = ENG value = 50 }
    relation = { tag = EST value = 75 }
    relation = { tag = FIN value = 100 }
    relation = { tag = FRA value = 100 }
    relation = { tag = GER value = -10 }
    relation = { tag = GRE value = 35 }
    relation = { tag = HUN value = 50 }
    relation = { tag = LAT value = 75 }
    relation = { tag = LIT value = -75 }
    relation =
    { tag        = ROM
      value      = 40
    }
    relation = { tag = SOV value = -50 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 1 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 2 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 3 }
  SpyInfo                = { country = "CZE" NumberOfSpies = 2 }
  SpyInfo                = { country = "AUS" NumberOfSpies = 1 }
  SpyInfo                = { country = "GER" NumberOfSpies = 3 }
  SpyInfo                = { country = "LAT" NumberOfSpies = 2 }
  SpyInfo                = { country = "SWE" NumberOfSpies = 1 }
  SpyInfo                = { country = "FIN" NumberOfSpies = 1 }
  SpyInfo                = { country = "YUG" NumberOfSpies = 1 }
  SpyInfo                = { country = "HUN" NumberOfSpies = 1 }
  SpyInfo                = { country = "BUL" NumberOfSpies = 1 }
  SpyInfo                = { country = "EST" NumberOfSpies = 1 }
  SpyInfo                = { country = "LIT" NumberOfSpies = 3 }
  SpyInfo                = { country = "USA" NumberOfSpies = 1 }
  SpyInfo                = { country = "ROM" NumberOfSpies = 2 }
  nationalprovinces      = { 
  		485 306 307 479 480 481 483 484 305 486 3396 3271 1884 501 3273 
		487 489 488 504 505 1595 2296 2628 1811 3261
		508 509 209 208 213 211 222 214 1875 1876 102
		3263 3264 3265 3266 3267 3268 3269 3270 3272 3277 3278 3279 6515 6516 6517
		7048 7049 7050 7262 7263 7264 7335 7978 7979 7980
		500 8000
                           }
  ownedprovinces         = { 306 307 479 480 481 483 484 305 485 486 487 489 488 500 501 502 503 504 505 506 507 508 509 209 208 213 211 210 222
                             229 562 214
							 1875 1876 1884 1885
							 95 102
							 2628
							 3263	3264	3265	3266	3267	3268	3269	3270	3271	3272	3273	3274	3275	3276	3277	3278	3279
							3395 3396 6515 6516 6517
							7048 7049 7050 7262 7263 7264 7335 7978 7979 7980 7984 8000
                           }
  controlledprovinces    = { 306 307 479 480 481 483 484 305 485 486 487 489 488 500 501 502 503 504 505 506 507 508 509 209 208 213 211 210 222
                             229 562 214
							 1875 1876 1884 1885
							 95 102
							 2628
							 3263	3264	3265	3266	3267	3268	3269	3270	3271	3272	3273	3274	3275	3276	3277	3278	3279
							3395 3396 6515 6516 6517
							7048 7049 7050 7262 7263 7264 7335 7978 7979 7980 7984 8000
                           }
claimedprovinces = { 303 2647 267 161 507 506 502 1885 3274 3275 562 503 3395 1153 212 272 6519 7065 7984 95 3276 229 210 206 207 511 577 3280 3281 3282 7336 202 203 204 205 3283 3284 3455 1874 3399 217 218 3400 220 221 3402 3403 273 7066 274 1566 3401 225 7067 240 3406 226 227 228 231 3407 237 1154 3405 232 303 304 
238 #Kiev?
}
  # Air Doctrines
   techapps               = {
#Early Infantry Division  
1010  1020 1030 1040 1050 1060 1070 1080 1090
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240
#1930 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 1350 1360 1370
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960
#Great War Hospital System 
14000 14010 14020
#Naval Infantry
##1560
#Engineers
1830 1840 1850 1860
#Tankette 
7600 7610 2620 2010 2630 2640
#Basic Armoured Car  
2860 2870 2880 2020
#Field Artillery 
2290 2300 2310 2900 
#Early Anti-Tank Artillery
#2400
#Early Static Anti-Air Artillery 
2800 2450
#Basic Anti-Air Artillery Brigade 
2810 2820
# Heavy Cruiser
3210 3220
#Improved Destroyer 
3010 3020 3030 3040 3050 3060
#Short Range Submarine 
3610 3620 3630 3640
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810

#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Early Bomber 
4600 4610 4620 4630 4120 4130
#Multirole fighter
4300 4310 4320 4330
#ww1 strategic bomber
4800 4810
#ww1 navalbomber
#4700 4710

#Modern Agriculture  
5700 5710
#Computers & cryptografi
5310 54010 54020 5316 5326
#Manufactoring
5810 5820 5050 5830
#Improved Construction Engineering 
5800 5080 
#Basic Oil Refining 
##5190
#Medicine
5600 5610 5620 5630
# Land Doctrines WWI - Entente line (default)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Land Doctrines WWII - Defensive Focus 
6560 6030
#Naval Doctrines  
8010 8040  8050
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010 
} 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 4 
     freedom           = 5 
     free_market       = 1
     professional_army = 5 
     defense_lobby     = 4 
     interventionism   = 5 
  }
inventions = { 3000027 }
   headofstate            = {  type = 9 id = 60001  } 
   headofgovernment       = {  type = 9 id = 60002  } 
   foreignminister        = {  type = 9 id = 60003  } 
   armamentminister       = {  type = 9 id = 60004  } 
   ministerofsecurity     = {  type = 9 id = 60005  } 
   ministerofintelligence = {  type = 9 id = 60006  } 
   chiefofstaff           = {  type = 9 id = 60007  } 
   chiefofarmy            = {  type = 9 id = 60008  } 
   chiefofnavy            = {  type = 9 id = 60009  } 
   chiefofair             = {  type = 9 id = 60010  } 
   
landunit = 
   {  id       = {  type = 18600 id = 1  } 
     location = 485 
     name     = "1 Okreg Wojskowy" 
     Division = 
     {  id   = {  type = 18600 id = 2  } 
       name = "8 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
       extra = artillery 
	   brigade_model = 5
      } 
     Division = 
     {  id    = {  type = 18600 id = 3  } 
       name  = "9 Dywizja Piechoty" 
	   strength  = 50
       type  = infantry 
	   model    = 7
       extra = anti_air 
	   brigade_model = 1
      } 
     Division = 
     {  id   = {  type = 18600 id = 4  } 
       name = "28 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
       extra = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id   = {  type = 18600 id = 5  } 
       name = "1 Dywizja Kawalerii" 
	   strength  = 50
       type = cavalry 
	   model    = 6
       extra = artillery 
	   brigade_model = 3
      } 
     Division = 
     {  id   = {  type = 18600 id = 6  } 
       name = "Podlaska Brygada Kawalerii" 
	   strength  = 25
	max_strength = 60
       type = cavalry
	   model    = 8
	extra = light_armor_brigade
	brigade_model = 3	   
      } 
     Division = 
     {  id   = {  type = 18600 id = 7  } 
       name = "Mazowiecka Brygada Kawalerii" 
	   strength  = 25
	max_strength = 60
       type = cavalry
	   model    = 8
	extra = armored_car
	brigade_model = 3	   
      } 
    } 
   landunit = 
   {  id       = {  type = 18600 id = 8  } 
     location = 485 
     name     = "2 Okreg Wojskowy" 
     Division = 
     {  id   = {  type = 18600 id = 9  } 
       name = "3 Dywizja Piechoty Legionów" 
	   strength  = 50
       type = infantry 
	   model    = 8
       extra = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id    = {  type = 18600 id = 10  } 
       name  = "13 Dywizja Piechoty" 
	   strength  = 50
       type  = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 11  } 
       name = "27 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 12  } 
       name = "Wolynska Brygada Kawalerii" 
	   strength  = 30
	max_strength = 70
       type = cavalry
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 13  } 
       name = "41 Dywizja Piechoty" 
	   strength  = 5
       type = infantry 
	   model    = 6
      } 
    } 
   landunit = 
   {  id       = {  type = 18600 id = 14  } 
     location = 485 
     name     = "3 Okreg Wojskowy" 
     Division = 
     {  id   = {  type = 18600 id = 15  } 
       name = "1 Dywizja Piechoty Legionów" 
	   strength  = 50
       type = infantry 
	   model    = 8
       extra = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id   = {  type = 18600 id = 16  } 
       name = "19 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
      } 
     Division = 
     {  id    = {  type = 18600 id = 17  } 
       name  = "29 Dywizja Piechoty" 
	   strength  = 45
       type  = infantry 
	   model    = 8
      } 
     Division = 
     {  id   = {  type = 18600 id = 18  } 
       name = "Suwalska Brygada Kawalerii" 
	   strength  = 25
	max_strength = 60
       type = cavalry
	   model    = 8
      } 
     Division = 
     {  id   = {  type = 18600 id = 19  } 
       name = "Wilenska Brygada Kawalerii" 
	   strength  = 25
	max_strength = 60
       type = cavalry
	   model    = 8
      } 
     Division = 
     {  id   = {  type = 18600 id = 20  } 
       name = "39 Dywizja Piechoty" 
	   strength  = 5
       type = infantry 
	   model    = 6
      } 
     Division = 
     {  id   = {  type = 18600 id = 21  } 
       name = "35 Dywizja Piechoty" 
	   strength  = 5
       type = infantry 
	   model    = 6
      } 
     Division = 
     {  id   = {  type = 18600 id = 22  } 
       name = "33 Dywizja Piechoty" 
	   strength  = 5
       type = infantry 
	   model    = 6
      } 
    } 
   landunit = 
   {  id       = {  type = 18600 id = 23  } 
     location = 485 
     name     = "4 Okreg Wojskowy" 
     Division = 
     {  id   = {  type = 18600 id = 24  } 
       name = "7 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
       extra = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id    = {  type = 18600 id = 25  } 
       name  = "10 Dywizja Piechoty" 
	   strength  = 50
       type  = infantry 
	   model    = 7
       extra = engineer 
	   brigade_model = 3
      } 
     Division = 
     {  id    = {  type = 18600 id = 26  } 
       name  = "26 Dywizja Piechoty" 
	   strength  = 50
       type  = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 27  } 
       name = "Lodzka Brygada Kawalerii" 
	   strength  = 30
	max_strength = 70
       type = cavalry
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 28  } 
       name = "45 Dywizja Piechoty" 
	   strength  = 5
       type = infantry 
	   model    = 6
      } 
    } 
   landunit = 
   {  id       = {  type = 18600 id = 29  } 
     location = 485 
     name     = "5 Okreg Wojskowy" 
     Division = 
     {  id   = {  type = 18600 id = 30  } 
       name = "6 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
       extra = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id   = {  type = 18600 id = 31  } 
       name = "21 Dywizja Piechoty Górskiej" 
	   strength  = 50
       type = bergsjaeger
	   model    = 7
      } 
     Division = 
     {  id    = {  type = 18600 id = 32  } 
       name  = "23 Dywizja Piechoty" 
	   strength  = 50
       type  = infantry 
	   model    = 8
       extra = engineer
	   brigade_model = 3
      } 
     Division = 
     {  id   = {  type = 18600 id = 33  } 
       name = "Krakowska Brygada Kawalerii" 
	   strength  = 30
	max_strength = 70
       type = cavalry
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 34  } 
       name = "55 Dywizja Piechoty" 
	   strength  = 5
       type = infantry 
	   model    = 6
      } 
    } 
   landunit = 
   {  id       = {  type = 18600 id = 35  } 
     location = 485 
     name     = "6 Okreg Wojskowy" 
     Division = 
     {  id   = {  type = 18600 id = 36  } 
       name = "5 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
       extra = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id   = {  type = 18600 id = 37  } 
       name = "11 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 38  } 
       name = "12 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 39  } 
       name = "Podolska Brygada Kawalerii" 
	   strength  = 30
	max_strength = 70
       type = cavalry
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 40  } 
       name = "36 Dywizja Piechoty" 
	   strength  = 5
       type = infantry 
	   model    = 6
      } 
    } 
   landunit = 
   {  id       = {  type = 18600 id = 41  } 
     location = 485 
     name     = "7 Okreg Wojskowy" 
     Division = 
     {  id   = {  type = 18600 id = 42  } 
       name = "14 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
       extra = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id    = {  type = 18600 id = 43  } 
       name  = "17 Dywizja Piechoty" 
	   strength  = 50
       type  = infantry 
	   model    = 7
       extra = engineer
	   brigade_model = 3
      } 
     Division = 
     {  id   = {  type = 18600 id = 44  } 
       name = "25 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 45  } 
       name = "Wielkopolska Brygada Kawalerii" 
	   strength  = 30
	max_strength = 70
       type = cavalry
	   model    = 7
      } 
    } 
   landunit = 
   {  id       = {  type = 18600 id = 46  } 
     location = 485 
     name     = "8 Okreg Wojskowy" 
     Division = 
     {  id   = {  type = 18600 id = 47  } 
       name = "4 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
       extra = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id   = {  type = 18600 id = 48  } 
       name = "15 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 49  } 
       name = "16 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 50  } 
       name = "Pomorska Brygada Kawalerii" 
	   strength  = 30
	max_strength = 70
       type = cavalry
	   model    = 7
      } 
    } 
   landunit = 
   {  id       = {  type = 18600 id = 51  } 
     name     = "9 Okreg Wojskowy" 
     location = 485 
     Division = 
     {  id   = {  type = 18600 id = 52  } 
       name = "18 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
       extra = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id   = {  type = 18600 id = 53  } 
       name = "20 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 54  } 
       name = "30 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 55  } 
       name = "Nowogródzka Brygada Kawalerii" 
	   strength  = 30
	max_strength = 70
       type = cavalry
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 56  } 
       name = "38 Dywizja Piechoty" 
	   strength  = 5
       type = infantry 
	   model    = 6
      } 
     Division = 
     {  id   = {  type = 18600 id = 57  } 
       name = "44 Dywizja Piechoty" 
	   strength  = 5
       type = infantry 
	   model    = 6
      } 
    } 
   landunit = 
   {  id       = {  type = 18600 id = 58  } 
     location = 485 
     name     = "10 Okreg Wojskowy" 
     Division = 
     {  id   = {  type = 18600 id = 59  } 
       name = "2 Dywizja Piechoty Legionów" 
	   strength  = 50
       type = infantry 
	   model    = 8
       extra = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id   = {  type = 18600 id = 60  } 
       name = "22 Dywizja Piechoty Górskiej" 
	   strength  = 50
       type = bergsjaeger
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 61  } 
       name = "24 Dywizja Piechoty" 
	   strength  = 50
       type = infantry 
	   model    = 7
      } 
     Division = 
     {  id   = {  type = 18600 id = 62  } 
       name = "Kresowa Brygada Kawalerii" 
	   strength  = 30
	max_strength = 70
       type = cavalry
	   model    = 7
      } 
    } 
   navalunit = 
   {  id       = {  type = 18600 id = 63  } 
     name     = "Polska Flota Wojenna" 
     location = 306 
     base     = 306 
     Division = 
     {  id       = {  type = 18600 id = 64  } 
       name     = "Flotylla Niszczycieli" 
       type     = destroyer 
       model    = 3
       strength = 40 
      } 
     Division = 
     {  id       = {  type = 18600 id = 964  } 
       name     = "Flotylla Dozorowców" 
       type     = destroyer 
       model    = 0
      } 
     Division = 
     {  id    = {  type = 18600 id = 65  } 
       name  = "1 Flotylla Okretow Podwodnych" 
       type  = submarine 
       model = 3
      } 
    } 
   airunit = 
   {  id       = {  type = 18600 id = 66  } 
     name     = "Wojska Lotnicze" 
     location = 485 
     base     = 485 
     Division = 
     {  id    = {  type = 18600 id = 67  } 
       name  = "3 Korpus Lotnictwa Mysliwskiego" 
       type  = interceptor 
       model = 7
      } 
     Division = 
     {  id    = {  type = 18600 id = 68  } 
       name  = "4 Korpus Lotnictwa Szturmowego" 
       type  = interceptor 
       model = 7 
      } 
     Division = 
     {  id    = {  type = 18600 id = 69  } 
       name  = "15 Dywizja Lotnictwa Bombowego" 
       type  = tactical_bomber 
       model = 4
      } 
    } 
	
landdivision = { dormant = yes id = { type = 12700 id = 10100 }  name = "Warsaw City Center" 	type = militia  model = 6  strength = 60 }
landdivision = { dormant = yes id = { type = 12700 id = 10101 }  name = "Warsaw - North"  		type = militia  model = 6  strength = 60 }
landdivision = { dormant = yes id = { type = 12700 id = 10102 }  name = "Warsaw - South"  		type = militia  model = 6  strength = 60 }
landdivision = { dormant = yes id = { type = 12700 id = 10103 }  name = "Powisle"  				type = militia  model = 6  strength = 60 }
landdivision = { dormant = yes id = { type = 12700 id = 10104 }  name = "Zoliborz"  			type = militia  model = 6  strength = 60 }
landdivision = { dormant = yes id = { type = 12700 id = 10105 }  name = "Kampinos Forest"  		type = militia  model = 6  strength = 60 }
landdivision = { dormant = yes id = { type = 12700 id = 10106 }  name = "Kedyw Units"  			type = infantry model = 11 strength = 60 }

landdivision = { dormant = yes id = { type = 12700 id = 10110 }  name = "Underground State"		type = garrison model = 4	locked = yes }
} 
 
