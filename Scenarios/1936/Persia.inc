#####################
# Country main data #
#####################

country =
{ tag                    = PER
	# Resource Reserves 
	energy                 = 540
	metal                  = 270
	rare_materials         = 135
	transports = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	manpower               = 167 
  capital                = 1502
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 4 
     freedom           = 3 
     free_market       = 1
     professional_army = 5 
     defense_lobby     = 2 
     interventionism   = 2
  }
  nationalprovinces      = { 1859 1787 1503 1502 1789 1825 1498 1497 1499 1826 1501 1500 1496 1495
2836 2837 2838 2839 2840 2841 2842 2843 2844 2845 4198 4201 4202 4203 4204 4205 4206 4207 4208 
4209 4210 4211 4212 4213 4214 4215 4216 4217 4218 4219 4220 4221 4222 4223 4224 4227 4228 
4229 4230 4231 4232 4233 4234 6495 7014 2470 7273
1486 5386 5389 2773 4270 3424 3425 7251 2847 7252 6919 3426 3427 3428 7308 1907 7254 2848 7253 
  }
  ownedprovinces         = { 1859 1787 1503 1502 1788 1789 1825 1498 1497 1499 1826 1501 1500 1496 1495
2836 2837 2838 2839 2840 2841 2842 2843 2844 2845
2846
4198 4199 4201 4202 4203 4204 4205 4206 4207 4208 
4209 4210 4211 4212 4213 4214 4215 4216 4217 4218 
4219 4220 4221 4222 4223 4224 4225 4226 4227 4228 
4229 4230 4231 4232 4233 4234 6495
7014
  }
  controlledprovinces    = { 1859 1787 1503 1502 1788 1789 1825 1498 1497 1499 1826 1501 1500 1496 1495
2836 2837 2838 2839 2840 2841 2842 2843 2844 2845
2846
4198 4199 4201 4202 4203 4204 4205 4206 4207 4208 
4209 4210 4211 4212 4213 4214 4215 4216 4217 4218 
4219 4220 4221 4222 4223 4224 4225 4226 4227 4228 
4229 4230 4231 4232 4233 4234 6495
7014
  }
  claimedprovinces 		 = { 1788 4199 4226 2846 4225
  1906 2865 2864 1858 2850 7272 7249 1856 3429 4149 7250 4118
  3433 7247 1850 3434 1149 7246 2849 7245 7246 3435 7311 
  2869 3488 1490 1491 6493 5404 5388 5385 7983 5362 5373 5371 5372 5370 2824 
  }
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
#SW Tank 
7600 7610
#1916 lgt. Infantry Division  
1010  1020 1030 1040 1050 1060
#Interbellum Supply 
1910 1920 1930 1940 1950 1960
#Medicine
5600
#Engineers
1830 1840 
#1916 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Agriculture
5700
# Land Doctrines WWI - Entente Line (default)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Land Doctrines WW2 - none

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
 } 
 inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = AFG value = 25  } 
     relation = {  tag = DEN value = 50  } 
     relation = {  tag = ENG value = 25  } 
     relation = {  tag = IRQ value = 125  } 
     relation = {  tag = SAU value = 100  } 
     relation = {  tag = SOV value = -20  } 
     relation = {  tag = SWE value = 50  } 
     relation = {  tag = TUR value = -50  } 
    } 
   SpyInfo                = {  country = "PER" NumberOfSpies = 5  } 
   headofstate            = {  type = 9 id = 150001  } 
   headofgovernment       = {  type = 9 id = 150002  } 
   foreignminister        = {  type = 9 id = 150003  } 
   armamentminister       = {  type = 9 id = 150004  } 
   ministerofsecurity     = {  type = 9 id = 150005  } 
   ministerofintelligence = {  type = 9 id = 150006  } 
   chiefofstaff           = {  type = 9 id = 150007  } 
   chiefofarmy            = {  type = 9 id = 150008  } 
   chiefofnavy            = {  type = 9 id = 150125  } #Gholamali Bayandor
   chiefofair             = {  type = 9 id = 150010  } 

   landunit = 
   {  location = 1502 
     name     = "Lasgar Parsi" 
     id       = {  type = 16600 id = 1  } 
     Division = 
     {  id    = {  type = 16600 id = 2  } 
       name  = "1. Dastebandi Sarbaze Piyade" 
       type  = infantry 
	   model    = 7
       extra = artillery 
	   brigade_model = 5
      } 
     Division = 
     {  id   = {  type = 16600 id = 3  } 
       name = "1. Dastebandi Savareh" 
	   model    = 8
       type = cavalry 
      } 
    } 
  } 
 
