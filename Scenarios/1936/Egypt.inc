    ############################## 
     # Country definition for EGY - Egypt #  
      ##############################  
    
      #####################  
      # Country main data #  
      #####################  
    
      country =  
      {  tag               = EGY  
	ai_settings			   = { flags = { puppetLevel5 = 1 } }
    capital                = 903 # Cairo / Al-Qahirah  
    puppet    = ENG # UK  
	# Resource Reserves  
	energy                 = 540
	metal                  = 270
	rare_materials         = 135
	oil                    = 500  
	supplies               = 50 # No army - no supply reserves  
	money                  = 50  
	manpower               = 0 # No army - no reserves  
	dissent                = 15  
	transports             = 100  
	escorts                = 0  
         
    
        diplomacy = {   
    relation = {   tag = GER value = 80 access = no   }   
      }  
    SpyInfo                = {   country = "EGY" NumberOfSpies = 3   }  
    
	claimedprovinces 	= { 1066 1028 1029 1067 1068 1069 1030 1031 1040 1041 1065 1032 2334 2633 2852 2817 2814 2815 2816
4618 4619 4620 4621 4622 4623 4624 4625 4626 4627 4628 4629 4630 4631 4632 4633 4634 4635 4636 4637 4638 4639 4640 4641 4642 4643 4644 4645 4646 4647 4648 4649 4650 4651 4652 4653 4654 4655 4656 4657
7985 7455 7443 7347 2886 }
    nationalprovinces      = { 903 2897 915 909 913 914 911 910 907 904 906 902 1800 1801 4 1025 1026 1027 1024 1023 905 1020 912 1021 2898 2633 900 901 2899
4601 4602 4603 4604 4605 4606 4607 4608 4609 4610 4611 4612 4613 4614 4615 4616 4617 7298 7985
  }  
    ownedprovinces         = { 903 2897 915 909 913 914 911 910 907 904 906 902 1800 1801 4 1025 1026 1027 1024 1023 905 1020 912 1021 2898 901 2899
4601 4602 4603 4604 4605 4606 4607 4608 4609 4610 4611 4612 4613 4614 4615 4616 4617 7298 7985	
  }  
    controlledprovinces    = { 903 2897 915 909 913 914 911 910 907 904 906 902 1800 1801 4 1025 1026 1027 1024 1023 905 1020 912 1021 2898 901 2899 
4601 4602 4603 4604 4605 4606 4607 4608 4609 4610 4611 4612 4613 4614 4615 4616 4617 7298 7985	
  }  
     
    techapps = {  
#Great War Infantry Division  
1010  1020 1030 1040 1050 1060 
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960
#1930 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 1350 1360 1370
#Basic Armoured Car  
2860 2870 2880 2020
#Great War Heavy Field Artillery 
2290 2300 2310 
#Early Anti-Tank Artillery 
#2400
#Early Static Anti-Air Artillery 
2800 2450 
#Great War Destroyer 
3010 3020 3030 3040
#Interwar Light Cruiser 
3110 3120 3130 3140
#Early Heavy Cruiser 
3210 3220 3230
#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Improved Construction Engineering 
5800 5080 

1830 1840   
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810

#Engineers
#Medicine
5600 5610 5620


#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010
# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Defensive Focus Grand Battleplan Path (FRA / UK)
6560
#Naval Doctrines
8010 8020 8050  

 }  
     inventions = { 3000027 }    
      
    policy =  
    {   date              = {   year = 0 month = january day = 0   }  
      democratic        = 1  
      political_left    = 4  
      free_market       = 1
      freedom           = 2  
      professional_army = 3  
      defense_lobby     = 3  
      interventionism   = 2  
      }  

    headofstate            = {   type = 9 id = 340001   }  # Fuad I  
    headofgovernment       = {   type = 9 id = 340002   }  # Ali Mahir Pasha  
    foreignminister        = {   type = 9 id = 340003   }  # Ali Mahir Pasha  
    armamentminister       = {   type = 9 id = 340004   } # Mohammed al Fransawi  
    ministerofsecurity     = {   type = 9 id = 340005   } # Mustafa an-Nahhas Pasha  
    ministerofintelligence = {   type = 9 id = 340006   } # Mohammed Hilmi Issa  
    chiefofstaff           = {   type = 9 id = 340007   } # Hassan Sabry Pasha  
    chiefofarmy            = {   type = 9 id = 340008   } # Hassan Sabry Pasha  
    chiefofnavy            = {   type = 9 id = 340009   } # Abdallah Ziwar Pasha;  
    chiefofair             = {   type = 9 id = 340010   }  # Fuad I    
     
     landunit = {   
        id = {  type = 19600 id = 1  }  
        location = 903  
        name = "Royal Egyptian Army"  
           Division = {   
              id = {  type = 19600 id = 2  }  
              name = "Royal Guard"  
              strength = 12  
              max_strength = 12  
              type = infantry  
              model = 6
            experience = 20  
            }  
           Division = {   
              id = {  type = 19600 id = 3  }  
                      name = "1st Egyptian Infantry" # No army for Egypt allowed, except some 10,000 men  
              strength = 100  
              type = infantry 
				model = 5			  
            }  
         }  
    
     airunit = {   
        id = {  type = 19600 id = 4  }  
        location = 907  
		base = 907 
        name = "Egyptian Army Air Force"  
           Division = {   
              id = {  type = 19600 id = 5  }  
              name = "Egyptian Army Air Force"  
              strength = 50  
              type = interceptor
			  model = 4
            }  
                 }  
    
         }