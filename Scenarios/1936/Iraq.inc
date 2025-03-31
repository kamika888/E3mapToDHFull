#####################
# Country main data #
#####################

country =
{ tag                    = IRQ
  puppet                 = ENG
  control				 = ENG
  ai_settings			 = { flags = { puppetLevel7 = 1 } }
	# Resource Reserves 
	energy                 = 360
	metal                  = 180
	rare_materials         = 90
	transports = 100
	oil                    = 1000 
	supplies               = 500 
	manpower               = 65 
	money                  = 10 
  capital                = 1865
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 4 
     freedom           = 3
     free_market       = 1
     professional_army = 5 
     defense_lobby     = 3 
     interventionism   = 4
  }
  claimedprovinces		 = { 4213 4156 710 7977 4154 }
  nationalprovinces      = { 1860 1864 1865 1866 1790 1824 1823 1806 1791 2496 1498 1822 4153 4155 4157 4158 4159 4160 4161 4162 4163 4164 4165 4212 6499 7349 7350 }
  ownedprovinces         = { 1860 1864 1865 1866 1790 1824 1823 1806 1791 710 2496 4153 4154 4155 4156 4157 4158 4159 4160 4161 4162 4163 4164 4165 7349 7350 7977 }
  controlledprovinces    = { 1860 1864 1865 1866 1790 1824 1823 1806 1791 710 2496 4153 4154 4155 4156 4157 4158 4159 4160 4161 4162 4163 4164 4165 7349 7350 7977 }
  # ROTW Minor Tech '36
  # Group E 1936 techs
  # ######################
  # GW fighter
   techapps               = {  
#Interwar Fighter  
4500 4510 4520 4530
#Basic Armoured Car  
2860 2870 2880 2020  
#Great War Heavy Field Artillery 
2290 2300 2310 
#1916 lgt. Infantry Division  
1010  1020 1030 1040 1050 1060
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 1970
#1916 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Agriculture
5700 
# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Defensive Focus Grand Battleplan Path (FRA / UK)
6560
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
 } 
 inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = AST value = 100  } 
     relation = {  tag = BHU value = 100  } 
     relation = {  tag = CAN value = 100  } 
     relation = {  tag = ENG value = 100  } 
     relation = {  tag = FRA value = 100  } 
     relation = {  tag = GER value = 25  } 
     relation = {  tag = ITA value = 25  } 
     relation = {  tag = NEP value = 100  } 
     relation = {  tag = NZL value = 100  } 
     relation = {  tag = OMN value = 125  } 
     relation = {  tag = PER value = 125  } 
     relation = {  tag = SAF value = 100  } 
     relation = {  tag = SAU value = 125  } 
     relation = {  tag = USA value = 120  } 
     relation = {  tag = YEM value = 125  } 
    } 
   SpyInfo                = {  country = "IRQ" NumberOfSpies = 3  } 
   headofstate            = {  type = 9 id = 365001  } 
   headofgovernment       = {  type = 9 id = 365002  } 
   foreignminister        = {  type = 9 id = 365003  } 
   armamentminister       = {  type = 9 id = 365004  } 
   ministerofsecurity     = {  type = 9 id = 365005  } 
   ministerofintelligence = {  type = 9 id = 365006  } 
   chiefofstaff           = {  type = 9 id = 365007  } 
   chiefofarmy            = {  type = 9 id = 365008  } 
   chiefofnavy            = {  type = 9 id = 365009  } 
   chiefofair             = {  type = 9 id = 365010  } 

   landunit = 
   {  id       = {  type = 22500 id = 3  } 
     name     = "Royal Iraqi Army" 
     location = 1865 
     Division = 
     {  id       = {  type = 22500 id = 4  } 
       name     = "1. Iraqi Infantry Division" 
       strength = 30 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 22500 id = 5  } 
       name     = "2. Iraqi Infantry Division" 
       strength = 30 
       type     = infantry 
	   model    = 5
      } 
	# Iraqi army in 1936 was 10,000 to 12,000 soldiers at most..
    # Division = 
    # {  id       = {  type = 22500 id = 6  } 
    #   name     = "3. Iraqi Infantry Division" 
    #   strength = 30 
    #   type     = infantry 
	#   model    = 5
    #   extra    = artillery 
	#   brigade_model = 2
    #  } 
    # Division = 
    # {  id       = {  type = 22500 id = 7  } 
    #   name     = "4. Iraqi Infantry Division" 
    #   strength = 30 
    #   type     = infantry 
	#   model    = 5
    #  } 
	}
	
   airunit = 
   {  id       = {  type = 22500 id = 8  } 
     name     = "Royal Army Air Force" 
     location = 1866 
     base     = 1866 
     Division = 
     {  id       = {  type = 22500 id = 9  } 
       name     = "1. RIAF Bomber Group" 
       strength = 30 
       type     = tactical_bomber 
       model    = 4
      } 
	 Division = 
     {  id       = {  type = 22500 id = 2  } 
       name     = "1. RIAF Fighter Group" 
       strength = 90 
       type     = interceptor 
       model    = 6
      } 
    } 
  } 
 