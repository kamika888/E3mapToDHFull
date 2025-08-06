country =
{
	tag                    = U41
	puppet				   = ETH
    ai_settings			   = { flags = { ideology = 4 puppetLevel8 = 1 } }
	ai					   = "default.ai"
	# Resource Reserves 
	energy                 = 100
	metal                  = 50
	rare_materials         = 25
	oil                    = 10 
	supplies               = 100 
	money                  = 50 
	manpower               = 10 
	capital                = 4678
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1
     political_left    = 4 
     free_market       = 1
     freedom           = 2 
     professional_army = 4 
     defense_lobby     = 3 
     interventionism   = 4
  }
  claimedprovinces      = {
	1038
  }
  nationalprovinces      = { 
	4678 1049 1050
	4677
	6943 1037
  }
  ownedprovinces         = { 
	4678 1049 1050
  }
  controlledprovinces    = {
	4678 1049 1050
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
# Inf support 
1910 1920 1930 1940 1950 1960
#Early Static Anti-Air Artillery 
2800
#SW Tank 
7600 7610
#Early Infantry Division  
1010 1020 1030 1040 1050 1060 1070
#Early Mountain Division
1160  1170 1180 1190 1200 1210 1220 
#1916 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Agriculture
5700 
# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 

 }
 inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = ITA value = 50  } 
     relation = {  tag = ETH value = 5  } 
    } 
   SpyInfo                = {  country = "U41" NumberOfSpies = 2  } 

  landunit =
  {
	id  = {  type = 31001 id = 1  }
    location = 4678
    name     = "Royal guard"
    Division =
	{ 
		id       = {  type = 31001 id = 2  }
		name     = "Mohammed Yayyo division"
		type     = militia
		strength = 90
		model    = 1
	}
  }   
     

}