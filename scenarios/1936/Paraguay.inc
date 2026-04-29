#####################
# Country main data #
#####################

country =
{ tag                    = PAR
  ai_settings			 = { flags = { RESInit = 1 ideology = 5 war_preparedness = 7 } }
	# Resource Reserves 
	energy                 = 360
	metal                  = 180
	rare_materials         = 90
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	manpower               = 150 
	dissent				   = 10 #Post-Chaco war
  capital                = 846
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 5 
     freedom           = 7 
     free_market       = 5
     professional_army = 5 
     defense_lobby     = 5 
     interventionism   = 6
  }
  free = { 
	ic = 2 
	energy = 2
	metal = 1 
	supplies = 1 
	transport = 0.1500 
	manpower = 0.0040 
  } 
  extra_tc = 5 
  SpyInfo                = { country = "PAR" NumberOfSpies = 1 }
  nationalprovinces      = { 846 2991 2931 3809 3810 3811 3813
  5444 3981 2282 3982 837
  }
  ownedprovinces         = { 846 2991 3809 3810 3811 3813
  837 3814
  }
  controlledprovinces    = { 837 846
  2991 3809 3810 3811 3813 3814 3815 3817
  5451 3812 3816 3818 3819
  5452 3854
  }
  claimedprovinces       = {
  3814 5451 3812 3816 3818 3819 5452 3854 5453 3855 2375 3817 3815
  3924 5450 2554
  }
  # ROTW Minor Tech '36
  # Group D 1936 techs
  # ######################
  # GW fighter
   techapps               = { 
#Interwar Fighter  
4500 4510 4520 4530 4540 4550 4010
#Basic Armoured Car  
2860 2870 2880 2020
#Great War Heavy Field Artillery 
2290 2300 2310
#SW Tank 
7600 7610 
#Great War Infantry Division  
1010  1020 1030 1040 1050 1060 
#Interbellum Supply 
1910 1920 1930 1940 1950 1960
#Great War Cavalry Division  
13060 13070 13080 1310 1320 1330 1340
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Modern Agriculture  
5700 5710 5010
#Improved Construction Engineering 
5800 5080  

#Medicine
5600 5610
#Engineers
1830 1840 
# Land Doctrine WW1 - Entente line
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Land Doctrine WW2 - none
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
} 
inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = ARG value = 50  } 
     relation = {  tag = BRA value = 10  } 
     relation = {  tag = BOL value = -50  } 
     relation = {  tag = CHL value = 35  } 
     relation = {  tag = COL value = 10  } 
     relation = {  tag = ECU value = 25  } 
     relation = {  tag = PRU value = 25  } 
     relation = {  tag = URU value = 20  } 
     relation = {  tag = USA value = 75  } 
     relation = {  tag = VEN value = 10  } 
    } 
   headofstate            = {  type = 9 id = 200001  } 
   headofgovernment       = {  type = 9 id = 200002  } 
   foreignminister        = {  type = 9 id = 200003  } 
   armamentminister       = {  type = 9 id = 200004  } 
   ministerofsecurity     = {  type = 9 id = 200005  } 
   ministerofintelligence = {  type = 9 id = 200006  } 
   chiefofstaff           = {  type = 9 id = 200007  } 
   chiefofarmy            = {  type = 9 id = 200008  } 
   chiefofnavy            = {  type = 9 id = 200009  } 
   chiefofair             = {  type = 9 id = 200010  } 

landunit = 
   {  id       = {  type = 15600 id = 60  } 
     name     = "Ejercito de Paraguay" 
     location = 846 
     Division = 
     {  id       = {  type = 15600 id = 6001  } 
       name     = "1 División de Infantería" 
       strength   = 100 
       type     = infantry 
	   model    = 6
       extra         = artillery 
       brigade_model = 5
      } 
     Division = 
     {  id       = {  type = 15600 id = 6002  } 
       name     = "2 División de Infantería" 
       strength   = 100 
       type     = infantry 
	   model    = 6
      } 
     Division = 
     {  id       = {  type = 15600 id = 6003  } 
       name     = "3 División de Infantería" 
       strength   = 100 
       type     = infantry 
	   model    = 6
      } 
     Division = 
     {  id       = {  type = 15600 id = 6004  } 
       name     = "4 División de Infantería" 
       strength   = 100 
       type     = infantry 
	   model    = 6
      } 
     Division = 
     {  id       = {  type = 15600 id = 6005  } 
       name     = "5 División de Infantería" 
       strength   = 100 
       type     = infantry 
	   model    = 6
      } 
     Division = 
     {  id       = {  type = 15600 id = 6006  } 
       name     = "6 División de Infantería" 
       strength   = 100 
       type     = infantry 
	   model    = 6
      } 
     Division = 
     {  id       = {  type = 15600 id = 6007  } 
       name     = "7 División de Infantería" 
       strength   = 100 
       type     = militia 
	   model    = 4
      } 
     Division = 
     {  id       = {  type = 15600 id = 6008  } 
       name     = "8 División de Infantería" 
       strength   = 100 
       type     = militia 
	   model    = 4
      } 
     Division = 
     {  id       = {  type = 15600 id = 6009  } 
       name     = "9 División de Infantería" 
       strength   = 100 
       type     = militia 
	   model    = 4
      } 
     Division = 
     {  id       = {  type = 15600 id = 6010  } 
       name     = "10 División de Infantería" 
       strength   = 100 
       type     = militia 
	   model    = 4
      } 
     Division = 
     {  id       = {  type = 15600 id = 6011  } 
       name     = "11 División de Infantería" 
       strength   = 100 
       type     = militia 
	   model    = 4
      } 
     Division = 
     {  id       = {  type = 15600 id = 6012  } 
       name     = "1. Brigada de Caballería" 
       strength = 100 
       type     = cavalry 
       model    = 7
      } 
     Division = 
     {  id       = {  type = 15600 id = 6013  } 
       name     = "2. Brigada de Caballería" 
       strength = 100 
       type     = cavalry 
       model    = 7
      } 
     Division = 
     {  id       = {  type = 15600 id = 6050  } 
       name     = "CVI Brigada de Policia Nacional" 
       strength   = 100 
       type     = militia 
	   model    = 3
      } 
    } 
  } 
 
