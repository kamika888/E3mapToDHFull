#####################
# Country main data #
#####################

country =
{ tag                    = COL
	# Resource Reserves 
	energy                 = 660
	metal                  = 330
	rare_materials         = 165
	transports = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	manpower               = 0 
  capital                = 812
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 7 
     free_market       = 1
     freedom           = 5 
     professional_army = 4 
     defense_lobby     = 1 
     interventionism   = 2
  }
  claimedprovinces 		 = { 3875 3797 2675 3957 3964 3965 3954 2738 3788 3789 3792 3793 3791 3790 3821 2930 3820 3822 3787 
  889 888 723 4286 4287 4288 4289 }
  nationalprovinces      = { 3798 890 3800 3795 2660 3804 867 3796 3805 2926 812 3799 3806 3801 813 3807 3802 3808 803 5470 2924 3794 2927 2925 3803 868 2378 819 }
  ownedprovinces         = { 803 812 813 890 867 819 868
2660 2675 2738 2924 2925 2926 2927 2378
3788 3789 3790 3791 3792 3793 3794 3795 3796 3797 3798 3799 3800 3801 3802 3803 3804 3805 3806 3807 3808
5470
  }
  controlledprovinces    = { 803 812 813 890 867 819 868
2660 2675 2738 2924 2925 2926 2927 2378
3788 3789 3790 3791 3792 3793 3794 3795 3796 3797 3798 3799 3800 3801 3802 3803 3804 3805 3806 3807 3808
5470
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
7600 7610 2620 2010
#Great War Infantry Division
1010 1020 1030 1040 1050 1060 
#Interbellum Supply 
1910 1920 1930 1940 1950 1960
#Great War Cavalry Division
13060 13070 13080 1310 1320 1330 1340 
#Early Mountain Division
1160 1170 1180 1190 1200 1210 1220 1230 1240
#Early Static Anti-Air Artillery
2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade
2810 2820 2510
#Modern Agriculture
5700 5710 5010
#Improved Construction Engineering
5800 5080

#Engineers
1830 1840 1850 1860
#Great War Destroyer 
3010 3020 3030 3040
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810
#Medicine
5600 5610
# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Naval Doctrines
8010 8050
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
} 
 inventions = { 3000027 }
  diplomacy =
  { relation = { tag = ARG value = 10 }
    relation = { tag = BOL value = 1 }
    relation = { tag = BRA value = 10 }
    relation = { tag = CHL value = 15 }
    relation = { tag = ECU value = 20 }
    relation = { tag = GER value = -20 }
    relation = { tag = PAN value = 50 }
    relation = { tag = PAR value = 10 }
    relation = { tag = PRU value = -35 }
    relation = { tag = URU value = 10 }
    relation = { tag = USA value = 75 }
    relation = { tag = VEN value = 20 }
  }
   SpyInfo                = {  country = "COL" NumberOfSpies = 3  } 
   headofstate            = {  type = 9 id = 175001  } 
   headofgovernment       = {  type = 9 id = 175002  } 
   foreignminister        = {  type = 9 id = 175003  } 
   armamentminister       = {  type = 9 id = 175004  } 
   ministerofsecurity     = {  type = 9 id = 175005  } 
   ministerofintelligence = {  type = 9 id = 175006  } 
   chiefofstaff           = {  type = 9 id = 175007  } 
   chiefofarmy            = {  type = 9 id = 175008  } 
   chiefofnavy            = {  type = 9 id = 175009  } 
   chiefofair             = {  type = 9 id = 175010  } 

landunit = 
   {  id       = {  type = 23000 id = 40  } 
     name     = "Ejercito de Colombia" 
     location = 812 
     Division = 
     {  id       = {  type = 23000 id = 4000  } 
       name     = "1a División de Infantería" 
       strength   = 40 
       type     = infantry 
       model    = 6
       extra    = anti_air 
	   brigade_model = 1
      } 
	       Division = 
     {  id       = {  type = 23000 id = 4001  } 
       name     = "2a División de Infantería" 
       strength   = 40 
       type     = infantry 
       model    = 6
       extra    = artillery 
	   brigade_model = 4
      } 
	       Division = 
     {  id       = {  type = 23000 id = 4002  } 
       name     = "3a División de Infantería" 
       strength   = 40 
       type     = infantry 
       model    = 6
      } 
     Division = 
     {  id       = {  type = 23000 id = 4003  } 
       name     = "1a Brigada de Caballería 'Montería'" 
       strength   = 15 
       type     = cavalry 
       model    = 6
      } 
    } 
   navalunit = 
   {  id       = {  type = 23000 id = 4004  } 
     name     = "Armada de Colombia" 
     location = 890 
     base     = 890 
     Division = 
     {  id    = {  type = 23000 id = 4005  } 
       name  = "1a Flotilla de Torpedillos" 
       type  = destroyer 
       model = 1
      } 
    } 
  } 
 