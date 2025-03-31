
##############################
# Country definition for TIB #
##############################

country =
{ tag                    = TIB
	# Resource Reserves 
	energy                 = 300
	metal                  = 150
	rare_materials         = 75
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	manpower               = 0 
  capital                = 1452
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 4 
     freedom           = 2 
     free_market       = 1
     professional_army = 2 
     defense_lobby     = 3 
     interventionism   = 3 
  }
  nationalprovinces      = { 1283 1448 1450 1451 1452 1453 1406 1444 1442 5205 1878 1877
5505 5506 5507 5508 5509 5510 5511 5512 5513 5514 5515 5516 5517 5518 5519 5520 5521 5522 5523 5524 5525 5526
5527 5528 5529 5530 5531 5532 5533 5534 5535 5536 5537 5538 5539 5540
5577 5578 5579 5580 5581 5582 5583 5584 5585 5586 5587 5588 5589
5602 5603 5550 5557 5556
1430 2835 5337 5336 5255 6922 6923 2043 5180 1455 7304
  }
  ownedprovinces         = { 1283 1448 1450 1451 1452 1453 1406
5505 5506 5507 5508 5509 5510 5511 5512 5513 5514 5515 5516 5517 5518 5519 5520 5521 5522 5523 5524 5525 5526
  }
  controlledprovinces    = { 1283 1448 1450 1451 1452 1453 1406
5505 5506 5507 5508 5509 5510 5511 5512 5513 5514 5515 5516 5517 5518 5519 5520 5521 5522 5523 5524 5525 5526
  }
  claimedprovinces 		 = { 5488 5491 1443 }  
  
  
  # ROTW Minor Tech '36
  # Group E 1936 techs
  # ######################
  # Basic Armoured Car
   techapps = { 
	
	# Construction Engineering
	5800

	# Crypto - Up to 1922
	5316 5326

	# Infantry Division
	1010 1020 1030 1040 
	# Mountain Division
	1160 1170 1180 1190 1200 1210 
	# Cavalry Division  
	13060 13070 13080 1310
	# Supply 
	1910 1920 1930

	# Field Artillery 
	2290

	# Hospital System
	14000
	# Great War Land Doctrines (entente)
	6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670

	} 

blueprints = {
	# Medicine (most were still imported)
	5600

	# Artillery
	2300
	
	# Infantry
	1050 1060
	
	# Mountain
	1220
	
	# Entente Land Doctrine
	6540 6910
 
}
inventions = { 3000027 }
   SpyInfo                = {  country = "TIB" NumberOfSpies = 4  } 
   headofstate            = {  type = 9 id = 440001  } 
   headofgovernment       = {  type = 9 id = 440002  } 
   foreignminister        = {  type = 9 id = 440003  } 
   armamentminister       = {  type = 9 id = 440004  } 
   ministerofsecurity     = {  type = 9 id = 440005  } 
   ministerofintelligence = {  type = 9 id = 440006  } 
   chiefofstaff           = {  type = 9 id = 440007  } 
   chiefofarmy            = {  type = 9 id = 440008  } 
   chiefofnavy            = {  type = 9 id = 440009  } 
   chiefofair             = {  type = 9 id = 440010  } 
  # GW Cavalry

   landunit = 
   {  location = 1452 
     name     = "Xi'zang Jüntuan 1" 
     id       = {  type = 10700 id = 1  } 
     Division = 
     {  id    = {  type = 10700 id = 2  } 
       name  = "1 Xi'zang Shi" 
	   strength = 10
       type  = infantry 
	   model    = 5

      } 
     Division = 
     {  id   = {  type = 10700 id = 3  } 
       name = "10 Xi'zang Lü" 
       type = militia 
	   strength = 20
	   model    = 3
      } 
     Division = 
     {  id   = {  type = 10700 id = 4  } 
       name = "17 Xi'zang Lü" 
       type = militia 
	   strength = 20
	   model    = 3
      } 
    } 
  } 
 
