#####################
# Country main data #
#####################

country =
{ tag                    = BOL
  ai_settings			 = { flags = { RESInit = 1 ideology = 6 war_preparedness = 3 } }
	manpower               = 250 
	# Resource Reserves 
	energy                 = 360
	metal                  = 180
	rare_materials         = 90
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	dissent				   = 10 #Post-Chaco war
  capital                = 832
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 6 
     free_market       = 3
     freedom           = 4 
     professional_army = 5 
     defense_lobby     = 5 
     interventionism   = 2 
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
  SpyInfo                = { country = "BOL" NumberOfSpies = 1 }
  claimedprovinces 		 = { 3842 3841 2374 838 3857 7419 3851 7418 3858 3885 5449 5448 7428 7417
  837 3814 5451 3812 3816 3818 3819 5452 3854 5453 3855 2375 3817 3815
  3850 3856 7423
  3983 5434 5433
  7421 2003 7427 3833 3967 822 3961 3956 7422
  3884 7096 840 7095
  }
  nationalprovinces      = { 836 832 828 827 3843 3844 3845 3846 3847 3848 3849 3852 3853 5454 5455 7420 }
  ownedprovinces         = { 836 838 832 828 827 2374 2375 3841 3842 3843 3844 3845 3846 3847 3848 3849 3850 3851 3852 3853 3854 3855 3856 3857 3858 5452 5454 5455 7418 7419 7420 5453
  3817 5451 3815 3816 3812 3818 3819
  }
  controlledprovinces    = { 836 838 832 828 827 2374 2375 3841 3842 3843 3844 3845 3846 3847 3848 3849 3850 3851 3852 3853 3855 3856 3857 3858 5454 5455 7418 7419 7420 5453 }
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
#Medicine
5600 5610 5620
#Engineers
1830 1840 1850 
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Modern Agriculture  
5700 5710 5010
#Improved Construction Engineering 
5800 5080 
# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
} 
 inventions = { 3000027 }
  diplomacy =
  { relation = { tag = ARG value = 50 }
    relation = { tag = BRA value = 10 }
    relation = { tag = CHL value = -50 }
    relation = { tag = COL value = 1 }
    relation = { tag = ECU value = -20 }
    relation = { tag = GER value = 15 }
    relation = { tag = PAR value = -50 }
    relation = { tag = PRU value = 30 }
    relation = { tag = URU value = 10 }
    relation = { tag = USA value = 85 }
    relation = { tag = VEN value = -15 }
  }
   headofstate            = {  type = 9 id = 205001  } 
   headofgovernment       = {  type = 9 id = 205002  } 
   foreignminister        = {  type = 9 id = 205003  } 
   armamentminister       = {  type = 9 id = 205004  } 
   ministerofsecurity     = {  type = 9 id = 205005  } 
   ministerofintelligence = {  type = 9 id = 205006  } 
   chiefofstaff           = {  type = 9 id = 205007  } 
   chiefofarmy            = {  type = 9 id = 205008  } 
   chiefofnavy            = {  type = 9 id = 205009  } 
   chiefofair             = {  type = 9 id = 205010  } 
  # Human Wave

landunit = 
   {  id       = {  type = 17000 id = 40  } 
     name     = "Ejercito de Bolivia" 
     location = 832 
     Division = 
     {  id       = {  type = 17000 id = 4000  } 
       name     = "1. Brigada de Infantería 'Bolivar'" 
       strength = 100 
       type     = infantry 
       model    = 5
       extra    = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id       = {  type = 17000 id = 4001  } 
       name     = "2. Brigada de Infantería" 
       strength = 100 
       type     = infantry 
       model    = 5
      } 
     Division = 
     {  id       = {  type = 17000 id = 4002  } 
       name     = "3. Brigada de Infantería" 
       strength = 100 
       type     = infantry 
       model    = 5
      } 
     Division = 
     {  id       = {  type = 17000 id = 4003  } 
       name     = "1. Brigada de Caballería 'Chaco'" 
       strength = 100 
       type     = cavalry 
       model    = 6
      } 
     Division = 
     {  id       = {  type = 17000 id = 4004  } 
       name     = "2. Brigada de Caballería" 
       strength = 100 
       type     = cavalry 
       model    = 6
      } 
     Division = 
     {  id       = {  type = 17000 id = 4005  } 
       name     = "4. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      } 
     Division = 
     {  id       = {  type = 17000 id = 4006  } 
       name     = "5. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      } 
     Division = 
     {  id       = {  type = 17000 id = 4007  } 
       name     = "6. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      } 
     Division = 
     {  id       = {  type = 17000 id = 4008  } 
       name     = "7. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      } 
     Division = 
     {  id       = {  type = 17000 id = 4009  } 
       name     = "8. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      } 
     Division = 
     {  id       = {  type = 17000 id = 4010  } 
       name     = "9. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      } 
     Division = 
     {  id       = {  type = 17000 id = 4011  } 
       name     = "10. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      }
     Division = 
     {  id       = {  type = 17000 id = 4012  } 
       name     = "11. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      }
     Division = 
     {  id       = {  type = 17000 id = 4013  } 
       name     = "12. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      }
     Division = 
     {  id       = {  type = 17000 id = 4014  } 
       name     = "13. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      }
     Division = 
     {  id       = {  type = 17000 id = 4015  } 
       name     = "14. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      }
     Division = 
     {  id       = {  type = 17000 id = 4016  } 
       name     = "15. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      }
     Division = 
     {  id       = {  type = 17000 id = 4017  } 
       name     = "16. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      }
     Division = 
     {  id       = {  type = 17000 id = 4018  } 
       name     = "17. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      }
     Division = 
     {  id       = {  type = 17000 id = 4019  } 
       name     = "18. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      }
     Division = 
     {  id       = {  type = 17000 id = 4020  } 
       name     = "19. Brigada de Infantería" 
       strength = 100 
       type     = militia 
       model    = 3
      }
    }
   airunit = 
   {  id       = {  type = 12000 id = 4050  } 
     name     = "Aviación del Ejército" 
     location = 832 
     base     = 832 
     Division = 
     {  id       = {  type = 12000 id = 4051  } 
       name     = "Grupo Aérea Nro. 1" 
       strength = 100 
       type     = interceptor 
       model    = 6
      } 
    } 	
  } 
 