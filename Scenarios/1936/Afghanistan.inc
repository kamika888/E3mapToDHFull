
##############################
# Country definition for AFG #
##############################

country =
{ tag                    = AFG
	# Resource Reserves 
	energy                 = 360
	metal                  = 180
	rare_materials         = 90
	oil                    = 500 
	supplies               = 500 
	money                  = 10 
	manpower               = 52 
	
  capital                = 1493
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 4 
     free_market       = 1
     freedom           = 1 
     professional_army = 5 
     defense_lobby     = 4 
     interventionism   = 1
  }
  nationalprovinces      = { 1486 1493 1492 1484
2864 2865 2866 2867
5379 5380 5381 5382 5383 5384 5385 5386 5387 5388 
5389 5390 5391 5392 5393 5394 5395 5396 5397 5398 
5399 5400 5401 5402 5403 5404 7983
  }
  ownedprovinces         = { 1486 1493 1492 1484
2864 2865 2866 2867
5379 5380 5381 5382 5383 5384 5385 5386 5387 5388 
5389 5390 5391 5392 5393 5394 5395 5396 5397 5398 
5399 5400 5401 5402 5403 5404 7983
  }
  controlledprovinces    = { 1486 1493 1492 1484
2864 2865 2866 2867
5379 5380 5381 5382 5383 5384 5385 5386 5387 5388 
5389 5390 5391 5392 5393 5394 5395 5396 5397 5398 
5399 5400 5401 5402 5403 5404 7983
  }
  claimedprovinces 		 = { 4227 }
  
	techapps = {  
		#Interwar Armoured Car  
		2860
		# Inf support 
		1910 1920 1930 1940 1950 1960
		#Light Field Artillery  
		2290
		#SW Tank 
		7600 7610	
		#1916 lgt. Infantry Division  
		1010  1020 1030 1040 1050 1060 1070 1160  1170 1180 1190 1200 1210 1220 1230 
		#1916 Cavalry Division  
		13060 13070 13080 1310 1320 1330 1340 1350
		#Early Agriculture
		5700 
		# Great War Land Doctrines (entente)
		6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
	} 
	
	inventions = { 3000027 }

  diplomacy =
  { relation = { tag = ENG value = -75 }
    relation = { tag = ITA value = 50 }
    relation = { tag = PER value = 25 }
    relation = { tag = SAU value = 50 }
    relation = { tag = SOV value = 1 }
    relation = { tag = TUR value = 50 }
  }
	headofstate            = {  type = 9 id = 155001  } 
	headofgovernment       = {  type = 9 id = 155002  } 
	foreignminister        = {  type = 9 id = 155003  } 
	armamentminister       = {  type = 9 id = 155004  } 
	ministerofsecurity     = {  type = 9 id = 155005  } 
	ministerofintelligence = {  type = 9 id = 155006  } 
	chiefofstaff           = {  type = 9 id = 155007  } 
	chiefofarmy            = {  type = 9 id = 155008  } 
	chiefofnavy            = {  type = 9 id = 155009  } 
	chiefofair             = {  type = 9 id = 155010  } 
  # GW Cavalry
  # ####################
  # ##AFGHANISTAN OOB###
  # ####################
   
   landunit = {
		id = { type = 10000 id = 1 }
		location = 1493 # Kabul
		name = "The Center Military District"

		division = {
			id = { type = 10000 id = 2 }
			name = "Royal Household Division"
			strength = 100
			type = infantry
			model = 7
			extra = cavalry_brigade 
			brigade_model = 5
		}

		division = {
			id = { type = 10000 id = 3 }
			name = "1st Infantry Division"
			strength = 20
			type = infantry
			model = 6
		}

		division = {
			id = { type = 10000 id = 4 }
			name = "2nd Infantry Division"
			strength = 20
			type = infantry
			model = 6
		}

		division = {
			id = { type = 10000 id = 5 }
			name = "4th Infantry Division"
			strength = 20
			type = infantry
			model = 6
		}
	}

	landunit = {
		id = { type = 10000 id = 6 }
		location = 1493 # Khost
		name = "The South Military District"

		division = {
			id = { type = 10000 id = 7 }
			name = "5th Infantry Division"
			strength = 20
			type = infantry
			model = 6
		}

		division = {
			id = { type = 10000 id = 8 }
			name = "6th Infantry Division"
			strength = 20
			type = infantry
			model = 6
		}

		division = {
			id = { type = 10000 id = 9 }
			name = "7th Infantry Division"
			strength = 20
			type = infantry
			model = 6
		}
	}

	landunit = {
		id = { type = 10000 id = 10 }
		location = 1493 # Chakhansur
		name = "Farah Military District"

		division = {
			id = { type = 10000 id = 11 }
			name = "Farah Cavalry"
			strength = 10
			type = cavalry 
			model = 6
		}

	}

	landunit = {
		id = { type = 10000 id = 12 }
		location = 1493 # Ghazni
		name = "Ghazni Military District"

		division = {
			id = { type = 10000 id = 13 }
			name = "Ghazni Mixed Infantry"
			strength = 20
			type = infantry
			model = 6
			extra = cavalry_brigade 
			brigade_model = 5
		}
	}

	landunit = {
		id = { type = 10000 id = 14 }
		location = 1493 # Kandahar
		name = "Kandahar Military District"

		division = {
			id = { type = 10000 id = 15 }
			name = "Kandahar Mixed Infantry"
			strength = 20
			type = infantry
			model = 6
			extra = cavalry_brigade 
			brigade_model = 5
		}
	}

	landunit = {
		id = { type = 10000 id = 16 }
		location = 1493 # Herat
		name = "Herat Military District"

		division = {
			id = { type = 10000 id = 17 }
			name = "Herat Mixed Infantry"
			strength = 20
			type = infantry
			model = 6
			extra = cavalry_brigade 
			brigade_model = 5
		}
	}

	landunit = {
		id = { type = 10000 id = 18 }
		location = 1493 # Mazar-e Sharif
		name = "Turkestan Military District"

		division = {
			id = { type = 10000 id = 19 }
			name = "Turkestan Mixed Infantry"
			strength = 20
			type = infantry
			model = 6
			extra = cavalry_brigade 
			brigade_model = 5
		}
	}

	landunit = {
		id = { type = 10000 id = 20 }
		location = 1493 # Faizabad
		name = "Kadaghan & Badakhchan Military District"

		division = {
			id = { type = 10000 id = 21 }
			name = "Kadaghan & Badakhchan Mixed Infantry"
			strength = 20
			type = infantry
			model = 6
			extra = cavalry_brigade 
			brigade_model = 5
		}
	}

	landunit = {
		id = { type = 10000 id = 22 }
		location = 1493 # Maymana
		name = "Maymeneh Military District"

		division = {
			id = { type = 10000 id = 23 }
			name = "Maymeneh Mixed Infantry"
			strength = 20
			type = infantry
			model = 6
			extra = cavalry_brigade 
			brigade_model = 5
		}
	}

	landunit = {
		id = { type = 10000 id = 24 }
		location = 1493 # Jalalabad
		name = "The East Military District"

		division = {
			id = { type = 10000 id = 25 }
			name = "The East Mixed Infantry"
			strength = 20
			type = infantry
			model = 6
			extra = cavalry_brigade 
			brigade_model = 5
		}
	}

} 