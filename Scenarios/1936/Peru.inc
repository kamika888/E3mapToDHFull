#####################
# Country main data #
#####################

country =
{ tag                    = PRU
	# Resource Reserves 
	energy                 = 600
	metal                  = 300
	rare_materials         = 150
	transports = 100
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	manpower               = 167 
  capital                = 830
  diplomacy =
  { relation = { tag = ARG value = 20 }
    relation = { tag = BOL value = 30 }
    relation = { tag = BRA value = 10 }
    relation = { tag = CHL value = -25 }
    relation = { tag = COL value = -35 }
    relation = { tag = ECU value = -50 }
    relation = { tag = PAR value = 25 }
    relation = { tag = URU value = 25 }
    relation = { tag = USA value = 75 }
    relation = { tag = VEN value = 10 }
  }
  claimedprovinces 		 = { 7094 7430 7435 1835 3785 3786 817 3787 3823 3822 3821 3790 3789 3788 2738 7434 7424 3826 3824 818 3830 2997 3835 3836 829 3840 2929 3820 2930 822 3967 3961 3956 7422 }
  nationalprovinces      = { 831 830 821 816 2497 2003 1988 908 2928 2049 3825 3827 3828 3829 3831 3832 3833 3834 3837 3838 3839 7092 7421 7425 7426 7427 7432 7093 3886 839 7433 }
  ownedprovinces         = { 831 829 830 821 816 2497 2003 1988 2997 908 818 2928 2929 2930 2049 3820 3821 3824 3825 3826 3827 3828 3829 3830 3831 3832 3833 3834 3835 3836 3837 3838 3839 3840 7092 7421 7424 7425 7426 7427 7432 7434 }
  controlledprovinces    = { 831 829 830 821 816 2497 2003 1988 2997 908 818 2928 2929 2930 2049 3820 3821 3824 3825 3826 3827 3828 3829 3830 3831 3832 3833 3834 3835 3836 3837 3838 3839 3840 7092 7421 7424 7425 7426 7427 7432 7434 }
  # ROTW Minor Tech '36
  # Group D 1936 techs
  # ######################
  # GW fighter
   techapps               = {
#Interwar Fighter  
4500 4510 4520 4530 4540 4550
#Basic Armoured Car  
2860 2870 2880 2020
#Great War Heavy Field Artillery 
2290 2300 2310
#SW Tank 
7600 7610
#Great War Infantry Division  
1160  1170 1180 1190 1200 1210 1220 1230 1240 1250
#Great War Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Interbellum Supply 
1910 1920 1930 1940 1950 1960
#Modern Agriculture  
5700 5710 5010
#Improved Construction Engineering 
5800 5080 
#Early Light Cruiser 
3110 3120 3130
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Short Range Submarine 
3610 3620 3630
#Great War Destroyer 
3010 3020 3030 3040

# Naval Firepower Doctrine
8010 8020 8040 8050  
#Naval Infantry
#1560 1570
#Engineers
1830 1840 1850
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810 
#Medicine
5600 5610 
# Land Doctrines WWI - Entente line (default)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Land Doctrines WWII - none

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 
} 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 4 
     freedom           = 6 
     free_market       = 1
     professional_army = 6 
     defense_lobby     = 2 
     interventionism   = 2 
  }
inventions = { 3000027 }
   SpyInfo                = {  country = "PRU" NumberOfSpies = 4  } 
   headofstate            = {  type = 9 id = 185001  } 
   headofgovernment       = {  type = 9 id = 185002  } 
   foreignminister        = {  type = 9 id = 185003  } 
   armamentminister       = {  type = 9 id = 185004  } 
   ministerofsecurity     = {  type = 9 id = 185005  } 
   ministerofintelligence = {  type = 9 id = 185006  } 
   chiefofstaff           = {  type = 9 id = 185007  } 
   chiefofarmy            = {  type = 9 id = 185008  } 
   chiefofnavy            = {  type = 9 id = 185009  } 
   chiefofair             = {  type = 9 id = 185010  } 

landunit = 
   {  id       = {  type = 17600 id = 1  } 
     name     = "Ejercito del Peru" 
     location = 830 
     Division = 
     {  id       = {  type = 17600 id = 2  } 
       name     = "1a Div. de Inf. del Peru 'Bolognesi'" 
       strength = 30 
       type     = infantry 
	   model = 7 
	   extra    = engineer 
	   brigade_model = 3
      } 
     Division = 
     {  id       = {  type = 17600 id = 3  } 
       name     = "2a Div. de Infantería del Peru" 
       strength = 30 
       type     = infantry 
	   model = 7 
	   extra    = artillery 
	   brigade_model = 4
      } 
     Division = 
     {  id       = {  type = 17600 id = 4  } 
       name     = "3a Div. de Infantería del Peru" 
       strength = 30 
       type     = infantry 
	   model = 7
	   extra    = artillery 
	   brigade_model = 4
      } 
    } 
	navalunit = { 
		id = { type = 17600 id = 6 } 
		name = "Marina del Guerra del Peru" 
		location = 830 
		base = 830 
		division = { 
			id = { type = 17600 id = 8 } 
			name = "ARP Almirante Grau" 
			type = light_cruiser 
			model = 1 
			} 
		division = { 
			id = { type = 17600 id = 9 } 
			name = "ARP Coronel Bolognesi" 
			type = light_cruiser 
			model = 1 
			} 
		division = { 
			id = { type = 17600 id = 2433 } 
			name = "Flotilla Suliana" 
			type = destroyer
			model = 1
			} 
		} 
	navalunit = { 
		id = { type = 17600 id = 11 } 
		name = "I Flotilla de la Armada" 
		location = 830 
		base = 830 
		division = { 
			id = { type = 17600 id = 12 } 
			name = "Tacna é Flotilla" 
			type = submarine 
			model = 1 
			} 
		} 
  } 
 
