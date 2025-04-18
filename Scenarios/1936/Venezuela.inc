#####################
# Country main data #
#####################

country =
{ tag                    = VEN
	# Resource Reserves 
	energy                 = 480
	metal                  = 240
	rare_materials         = 120
	transports = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 20 
	manpower               = 37 
  capital                = 870
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 5 
     freedom           = 6 
     free_market       = 1
     professional_army = 6 
     defense_lobby     = 2 
     interventionism   = 3
  }
  claimedprovinces 		 = { 2657 3871 5423 3866 3872 3873 2658 3875 3874 5424 5425 2737 3950 871 5421 5422 3887 }
  nationalprovinces      = { 804 802 810 811 869 870 3859 3860 3861 3862 3863 3864 3865 3867 3868 3869 3870 }
  ownedprovinces         = { 804 802 810 811 869 870 2657 2658 3859 3860 3861 3862 3863 3864 3865 3866 3867 3868 3869 3870 3871 3872 3873 3874 3875 5423 }
  controlledprovinces    = { 804 802 810 811 869 870 2657 2658 3859 3860 3861 3862 3863 3864 3865 3866 3867 3868 3869 3870 3871 3872 3873 3874 3875 5423 }
  # ROTW Minor Tech '36
  # Group D 1936 techs
  # ######################
  # GW fighter
   techapps               = {
#Interwar Fighter  
4500 4510 4520 4530 4540 4550
#Medicine
5600 5610 5620
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Basic Armoured Car  
2860 2870 2880 2020
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Great War Heavy Field Artillery 
2290 2300 2310
#SW Tank 
7600 7610
#Engineers
1830 1840 1850 1860
#Great War Infantry Division  
1010 1020 1030 1040 1050 1060 
#Interbellum Supply 
1910 1920 1930 1940 1950 1960
#Early Mountain Division 
1160 1170 1180 1190 1200 1210 1220 1230 1240
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810

#Manufactoring
5810 5820 5050
#Improved Construction Engineering 
5800 5080 
#Basic Oil Refining 
#5190 
#Mechanized Agriculture 
5700 5710 5010 5020
# Land Doctrines WWI - Entente line
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Landdoctrine ww2 - none?

 #Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010 
  } 
 inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = ARG value = 10  } 
     relation = {  tag = BOL value = -15  } 
     relation = {  tag = BRA value = 10  } 
     relation = {  tag = CHL value = 20  } 
     relation = {  tag = COL value = 20  } 
     relation = {  tag = ECU value = 20  } 
     relation = {  tag = ENG value = -10  } 
     relation = {  tag = PAR value = 10  } 
     relation = {  tag = PRU value = 10  } 
     relation = {  tag = URU value = 10  } 
     relation = {  tag = USA value = 125  } 
    } 
   SpyInfo                = {  country = "VEN" NumberOfSpies = 5  } 
   headofstate            = {  type = 9 id = 180001  } 
   headofgovernment       = {  type = 9 id = 180002  } 
   foreignminister        = {  type = 9 id = 180003  } 
   armamentminister       = {  type = 9 id = 180004  } 
   ministerofsecurity     = {  type = 9 id = 180005  } 
   ministerofintelligence = {  type = 9 id = 180006  } 
   chiefofstaff           = {  type = 9 id = 180007  } 
   chiefofarmy            = {  type = 9 id = 180008  } 
   chiefofnavy            = {  type = 9 id = 180009  } 
   chiefofair             = {  type = 9 id = 180010  } 
  # Firepower
  # Rather wild estimations

landunit = 
   {  id       = {  type = 15800 id = 45  } 
     name     = "Ejercito de Venezuela" 
     location = 870
     Division = 
     {  id       = {  type = 15800 id = 4500  } 
       name     = "1a Div. de Inf. 'Eduardo Blanco'" 
       extra    = artillery 
	   brigade_model = 4
       strength = 100 
       type     = infantry
		model    = 6   
      } 
     Division = 
     {  id       = {  type = 15800 id = 4501  } 
       name     = "1a Divisi�n de Guardia Naci�nal" 
       strength = 100 
       type     = militia
		model    = 3
      } 
     Division = 
     {  id       = {  type = 15800 id = 4502  } 
       name     = "Los Caballos de Venezuela" 
       strength = 100 
       type     = cavalry
		model    = 7
       extra    = artillery 
	   brigade_model = 4
      } 
    } 
  } 
 
