#####################
# Country main data #
#####################

country =
{ tag                    = SCH
  capital                = 532
	manpower               = 11
	# Resource Reserves
	energy                 = 840
	metal                  = 420
	rare_materials         = 210
	oil                    = 500 
	supplies               = 500 
	money                  = 25 

  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 5 
     freedom           = 10 
     free_market       = 1
     professional_army = 3 
     defense_lobby     = 3 
     interventionism   = 4
  }
  nationalprovinces      = { 532 530 533 372 3213 3214 3215 3216 6524 }
  ownedprovinces         = { 532 530 533 372 3213 3214 3215 3216 6524 }
  controlledprovinces    = { 532 530 533 372 3213 3214 3215 3216 6524 }
  # Western Minor Tech '36
  # Group C 1936 techs
  # ######################
   techapps               = {  
#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Multirole fighter
4300 4310 4320 4330
#Early Anti-Tank Artillery 
#2400
#Basic Armoured Car  
2860 2870 2880 2020
#Great War Heavy Field Artillery 
2290 2300 2310
#Early Static Anti-Air Artillery 
2800 2450 21180 21190 21200
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Great War Infantry Division  
1010  1020 1030 1040 1050 1060 1070 1080
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 1970 1980
#Great War Cavalry Division  
13060 13070 13080 1310 1320 1330 1340
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240
#Engineers
1830 1840 1850 1860
#Manufactoring
5810 5820 5050 5830
#Mechanized Agriculture 
5700 5710 5010 5020
#Computers & cryptografi
5310 54010 54020 54030 5316 5326
#Improved Construction Engineering 
5800 5080  5090
#Basic Oil Refining 
#5190
#Firepower Focus Doctrine 6
6010 6020
#Great War Tank 
7600 7610 2620 2010 2630  
#Medicine
5600 5610 5620 5630
# Land Doctrines WWI - Entente Line
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Landdoctrine WWII - none?

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010

    } 
	inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = ENG value = 50  } 
     relation = {  tag = FRA value = 1  } 
     relation = {  tag = GER value = 50  } 
     relation = {  tag = AUS value = 50  } 
     relation = {  tag = ITA value = 1  } 
     relation = {  tag = SCH value = 1  } 
     relation = {  tag = USA value = 1  } 
    } 
   SpyInfo                = {  country = "SCH" NumberOfSpies = 6  } 
   headofstate            = {  type = 9 id = 80001  } 
   headofgovernment       = {  type = 9 id = 80002  } 
   foreignminister        = {  type = 9 id = 80003  } 
   armamentminister       = {  type = 9 id = 80004  } 
   ministerofsecurity     = {  type = 9 id = 80005  } 
   ministerofintelligence = {  type = 9 id = 80006  } 
   chiefofstaff           = {  type = 9 id = 80007  } 
   chiefofarmy            = {  type = 9 id = 80008  } 
   chiefofnavy            = {  type = 9 id = 80009  } 
   chiefofair             = {  type = 9 id = 80010  } 
  # Superior Firepower
  # ####################
  # ###Swiss 36OOB####
  # ####################
   
   landunit = 
   {  id       = {  type = 30600 id = 1  } 
     location = 532 
     name     = "Ite Armeekorps" 
     Division = 
     {  id       = {  type = 30600 id = 2  } 
       name     = "1. Felddivision" 
       strength = 5 
       type     = infantry
	   model = 8
       extra    = artillery 
	   brigade_model = 6
      } 
    } 
   # ############################ 
   # ############################# 
   landunit = 
   {  id       = {  type = 30600 id = 3  } 
     location = 532 
     name     = "II�me Corps d'Arm�e Suisse" 
     Division = 
     {  id       = {  type = 30600 id = 4  } 
       name     = "2�me Division d'Infanterie" 
       strength = 5 
       type     = infantry 
	   model = 8
       extra    = anti_air 
	   brigade_model =1
      } 
     Division = 
     {  id       = {  type = 30600 id = 5  } 
       name     = "1. Alpenj�gerdivision" 
       strength = 5 
	   model = 7
       type     = bergsjaeger 
      } 
	 Division = 
     {  id       = {  type = 30600 id = 19  } 
       name     = "2. Brigade di Alpinisti" 
       strength = 5
       type     = bergsjaeger
		model    = 6  
      }  
    } 
   # ########################### 
   # ############################ 
   landunit = 
   {  id       = {  type = 30600 id = 6  } 
     location = 532 
     name     = "III Corpa di Armata" 
     Division = 
     {  id       = {  type = 30600 id = 7  } 
       name     = "3. Divisione di Fanteria" 
       strength = 5 
	   model = 8
       type     = infantry 
       extra    = artillery 
	   brigade_model = 5
      } 
     Division = 
     {  id       = {  type = 30600 id = 8  } 
       name     = "4. Felddivisionen" 
       strength = 5 
       type     = infantry 
	   model = 8
      } 
     Division = 
     {  id       = {  type = 30600 id = 9  } 
       name     = "2�me Div. d'Infanterie de Montagne" 
       strength = 5 
       type     = bergsjaeger
		model = 7	   
		extra    = artillery
      } 
	 Division = 
     {  id       = {  type = 30600 id = 18  } 
       name     = "3. Brigade di Alpinisti" 
       strength = 5
       type     = bergsjaeger
		model    = 6  
      }  
    } 
   # ############################### 
   # ############################### 
   landunit = 
   {  id       = {  type = 30600 id = 10  } 
     location = 532
     name     = "IV Armeekorps" 
     Division = 
     {  id       = {  type = 30600 id = 11  } 
       name     = "5�me Division d'Infanterie" 
       strength = 5
       type     = infantry 
	   model    = 8
       extra    = engineer 
	   brigade_model = 3
      } 
     Division = 
     {  id       = {  type = 30600 id = 12  } 
       name     = "6. Divisione di Fanteria" 
       strength = 5
       type     = infantry 
	   model    = 8
      } 
     Division = 
     {  id       = {  type = 30600 id = 13  } 
       name     = "3. Divisione di Alpinisti" 
       strength = 5
       type     = bergsjaeger
		model    = 7  
		extra    = artillery
      } 
	 Division = 
     {  id       = {  type = 30600 id = 17  } 
       name     = "1. Brigade di Alpinisti" 
       strength = 5
       type     = bergsjaeger
		model    = 6  
      }  
    } 
   airunit = 
   {  id       = {  type = 30600 id = 14  } 
     location = 532 
     base     = 532 
     name     = "Heeres Luftwaffe Abteilung 1" 
     Division = 
     {  id       = {  type = 30600 id = 15  } 
       name     = "Taktikkampfgeschwader 1" 
       strength = 20 
       type     = tactical_bomber 
       model    = 4
      } 
 
    } 
  } 
 
