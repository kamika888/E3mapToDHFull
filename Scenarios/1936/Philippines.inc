#####################
# Country main data #
#####################

country =
{ tag                    = PHI
  control                = USA
  puppet			     = USA
  #control				 = USA #AI will not autonomously suppress revolts otherwise
  ai_settings			 = { flags = { puppetLevel5 = 1 } }
	# Resource Reserves 
	energy                 = 480
	metal                  = 240
	rare_materials         = 120 
	oil                    = 200 
	supplies               = 500 
	money                  = 10 
	manpower               = 17 
	transports             = 150 
  capital                = 1737
  policy =
  { date              = { year = 0 month = january day = 0 }
    democratic        = 1
    political_left    = 6
    freedom           = 5
    free_market       = 1
    professional_army = 5
    defense_lobby     = 3
    interventionism   = 1
  }
  nationalprovinces      = { 
1735 1736 1737 1738 1739 1740 1741 1742 1743 1744 1745 1746 1747 1748 1749 1750
5715 5716 5717 5718 5719 5720 5721 5722 5723 5724 5725 5726 5727 5728 5729 5730 5731 5732 5733
1647 5744 5745 5746 7991
  }
  ownedprovinces         = { 
1735 1736 1737 1738 1739 1740 1741 1742 1743 1744 1745 1746 1747 1748 1749 1750
5715 5716 5717 5718 5719 5720 5721 5722 5723 5724 5725 5726 5727 5728 5729 5730 5731 5732 5733
  }
  controlledprovinces    = { 
1735 1736 1737 1738 1739 1740 1741 1742 1743 1744 1745 1746 1747 1748 1749 1750
5715 5716 5717 5718 5719 5720 5721 5722 5723 5724 5725 5726 5727 5728 5729 5730 5731 5732 5733
  }
	claimedprovinces = { 5836 5891 5873 5892 }
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
#1916 Cavalry Division  
13060 13070 13080 1310 1320 1330 1340 
#Early Agriculture
5700 
#Interbellum Supply 
1910 1920 1930 1940 1950 1960
#Engineers
1830 

# Basic Construction Engineering
5800 5080 
# Improved Construction Engineering 
5090  
# Land Doctrines WWI - Entente Line (default)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Land Doctrines WWII - none

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 
 } 
 inventions = { 3000027 }
   diplomacy = 
   {  relation = {  tag = AST value = 40  } 
     # relation = {  tag = CHI value = 5  } 
     relation = {  tag = JAP value = 1  } 
     relation = {  tag = LIB value = 200  } 
     relation = {  tag = NZL value = 25  } 
     relation = {  tag = USA value = 200  } 
    } 
   headofstate            = {  type = 9 id = 325001  } 
   headofgovernment       = {  type = 9 id = 325002  } 
   foreignminister        = {  type = 9 id = 325003  } 
   armamentminister       = {  type = 9 id = 325004  } 
   ministerofsecurity     = {  type = 9 id = 325005  } 
   ministerofintelligence = {  type = 9 id = 325006  } 
   chiefofstaff           = {  type = 9 id = 325007  } 
   chiefofarmy            = {  type = 9 id = 325008  } 
   chiefofnavy            = {  type = 9 id = 325009  } 
   chiefofair             = {  type = 9 id = 325010  } 

   landunit = 
   {  id       = {  type = 11804 id = 1  } 
     location = 1737 
     name     = "Manila Garrison" 
     Division = 
     {  id       = {  type = 11804 id = 2  } 
       strength = 30 
       name     = "Philippines Constabulary" 
       type     = garrison 
	   model    = 3
      } 
    } 
   navalunit = 
   {  id       = {  type = 11804 id = 5  } 
     location = 1737
     base     = 1737 
     name     = "Philippine Fleet" 
     Division = 
     {  id    = {  type = 11804 id = 6  } 
       name  = "1st Destroyer" 
       type  = destroyer 
       model = 4
      } 
     Division = 
     {  id   = {  type = 11804 id = 7  } 
       name = "1st Transport" 
       type = transport 
	   model = 1 
      } 
     Division = 
     {  id   = {  type = 11804 id = 8  } 
       name = "2nd Transport" 
       type = transport 
	   model = 1 
      } 
    } 
} 
 
