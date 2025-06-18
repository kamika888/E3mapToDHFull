#####################
# Country main data #
#####################

country =
{ tag                    = ENG
  ai_settings			 = { flags = { WARDebt = 17 } }
  capital                = 19
	manpower               = 20 
	dissent 			   = 5
	energy                 = 8040
	metal                  = 4020
	rare_materials         = 2010
	oil                    = 500 
	supplies               = 500 
	money                  = 70 
	transports             = 800 
	escorts                = 150 
  #Turkish straits
  free = {
	ic = 2
	money = 2
  }
  diplomacy =
  { relation =
    { tag        = AFG
      value      = -75
      guaranteed = { day = 11 month = february year = 1934 }
    }
    relation = { tag = ARG value = 75 }
    relation = { tag = AST value = 200 } # was access = yes 
    relation =
    { tag        = AUS
      value      = 75
      guaranteed = { day = 27 month = september year = 1934 }
    }
    relation = { tag = BEL value = 150 }
    relation = { tag = BHU value = 200 access = yes }
    relation = { tag = BUL value = 20 }
    relation = { tag = CAN value = 200 } # was access = yes
    relation = { tag = CUB value = 30 }
    relation = { tag = CZE value = 125 }
    relation =
    { tag        = DEN
      value      = 100
      guaranteed = { day = 30 month = august year = 1934 }
    }
    relation = { tag = ENG value = 50 }
    relation = { tag = EST value = 65 }
    relation = { tag = ETH value = 50 }
    relation = { tag = FIN value = 85 }
    relation = { tag = FRA value = 150 }
    relation = { tag = GER value = 1 }
    relation =
    { tag        = GRE
      value      = 50
      guaranteed = { day = 11 month = february year = 1934 }
    }
    relation = { tag = GUA value = 50 }
    relation = { tag = HOL value = 125 }
    relation = { tag = HON value = 50 }
    relation = { tag = HUN value = -50 }
    relation =
    { tag        = IRE
      value      = 25
      guaranteed = { day = 11 month = february year = 1934 }
    }
    relation =
    { tag        = IRQ
      value      = 100
      access     = yes
      guaranteed = { day = 11 month = february year = 1934 }
    }
    relation = { tag = ITA value = -50 }
    relation = { tag = JAP value = -25 }
    relation = { tag = LAT value = 65 }
    relation = { tag = LIT value = 65 }
    relation = { tag = MEX value = 50 }
    relation = { tag = NEP value = 200 access = yes }
    relation =
    { tag        = NOR
      value      = 90
      guaranteed = { day = 30 month = august year = 1934 }
    }
    relation = { tag = NZL value = 200 } # was access = yes
    relation =
    { tag        = OMN
      value      = 150
      access     = yes
      guaranteed = { day = 11 month = february year = 1934 }
    }
    relation =
    { tag        = PER
      value      = 25
      guaranteed = { day = 11 month = february year = 1934 }
    }
    relation = { tag = POL value = 50 }
    relation =
    { tag        = POR
      value      = 100
      guaranteed = { day = 30 month = december year = 1935 }
    }
    relation = { tag = ROM value = 50 }
    relation = { tag = SAF value = 200 } # was access = yes
    relation =
    { tag        = SAU
      value      = 100
      guaranteed = { day = 11 month = february year = 1934 }
    }
    relation =
    { tag        = SCH
      value      = 50
      guaranteed = { day = 16 month = may year = 1935 }
    }
    relation = { tag = SIA value = 70 }
    relation = { tag = SPR value = -10 }
    relation = { tag = SOV value = -25 }
    relation =
    { tag        = SWE
      value      = 80
      guaranteed = { day = 30 month = august year = 1934 }
    }
    relation =
    { tag        = TUR
      value      = 75
      guaranteed = { day = 11 month = february year = 1934 }
    }
    relation = { tag = USA value = 150 }
    relation = { tag = VEN value = -10 }
    relation =
    { tag        = YEM
      value      = 150
      access     = yes
      guaranteed = { day = 11 month = february year = 1934 }
    }
  }
  SpyInfo                = { country = "GER" NumberOfSpies = 3 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 4 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 2 }
  SpyInfo                = { country = "CZE" NumberOfSpies = 2 }
  SpyInfo                = { country = "AUS" NumberOfSpies = 1 }
  SpyInfo                = { country = "SPR" NumberOfSpies = 2 }
  SpyInfo                = { country = "POL" NumberOfSpies = 3 }
  SpyInfo                = { country = "SWE" NumberOfSpies = 1 }
  SpyInfo                = { country = "NOR" NumberOfSpies = 5 }
  SpyInfo                = { country = "FIN" NumberOfSpies = 2 }
  SpyInfo                = { country = "YUG" NumberOfSpies = 3 }
  SpyInfo                = { country = "HUN" NumberOfSpies = 2 }
  SpyInfo                = { country = "BUL" NumberOfSpies = 2 }
  SpyInfo                = { country = "BEL" NumberOfSpies = 3 }
  SpyInfo                = { country = "DEN" NumberOfSpies = 1 }
  SpyInfo                = { country = "HOL" NumberOfSpies = 3 }
  SpyInfo                = { country = "USA" NumberOfSpies = 4 }
  SpyInfo                = { country = "ALB" NumberOfSpies = 1 }
  SpyInfo                = { country = "GRE" NumberOfSpies = 1 }
  SpyInfo                = { country = "ARG" NumberOfSpies = 1 }
  SpyInfo                = { country = "BRA" NumberOfSpies = 1 }
  SpyInfo                = { country = "JAP" NumberOfSpies = 1 }
  SpyInfo                = { country = "ROM" NumberOfSpies = 2 }
  SpyInfo                = { country = "LIT" NumberOfSpies = 2 }
  SpyInfo                = { country = "LUX" NumberOfSpies = 1 }
  SpyInfo                = { country = "POR" NumberOfSpies = 1 }
  SpyInfo                = { country = "ITA" NumberOfSpies = 2 }
  SpyInfo                = { country = "CHI" NumberOfSpies = 4 }
  SpyInfo                = { country = "MEX" NumberOfSpies = 1 }
  SpyInfo                = { country = "AST" NumberOfSpies = 2 }
  SpyInfo                = { country = "NZL" NumberOfSpies = 2 }
  SpyInfo                = { country = "CAN" NumberOfSpies = 2 }
  SpyInfo                = { country = "IRE" NumberOfSpies = 4 }
  SpyInfo                = { country = "IRQ" NumberOfSpies = 3 }
  SpyInfo                = { country = "BHU" NumberOfSpies = 1 }
  SpyInfo                = { country = "YEM" NumberOfSpies = 1 }
  SpyInfo                = { country = "ETH" NumberOfSpies = 1 }
  # GREAT BRITAIN
  nationalprovinces      = { 19 3 6 7 1166 8 9 28 29 10 2245 11 13 12 1164 14 17 16 22 20 21 23 1160 15 1409 1720 2279
3030 3031 3032 3033 3034 3035 3036 3037 3038 3039 3040 3041 3042 3043 3044 3045 3046 3047 3054 2634 348 6944
7131 7287 7288 7289 7334
#Newfoundland
6647 6648 6649 6650 6651 6652 6653 6654 6656 6657 6658 6659 6660 6661 6662 6663 6664 575 576
#Falklands
5456 866
#Cyprus
5413 5412
#Islands
538 573 2964 652 2963 2962 584 896 795 572 897 587 586 805 807 591 806 808 5 1165 
}
  # GREAT BRITAIN
  ownedprovinces         = { 3 5 6 7 8 9 10 11 12 13 14 15 16 17 19 20 21 22 23 28 29 348  31 444 
1516 1517
1799 1797 1796 404  1802 1803
406  407  1813 1814 1820 1822 1504 1798 900
1065 1066 1069 1068 1067 1029 1028 1032 1031 1030 1040 1041
1349 1350 1351 1352 1353 1644 1646 1647 1315 758  891  871  873  806  807  808  809  897  538  652 
805  896  866  1147 1148 1816 1817 1136 1815 1132 1139 1062 1140 1141 1064 1060 1061 1059 1035 1112 1111 1105
1124 1125 1104 1099 1129 1126 1128 1000 1001 1002 1008 1007 999  1009 1010 1011 1145 1085 1012 988  982  1622 1683 1684
1685 1686 1759 575  576  1614 1611
2245 1165 1166 1409 1164 1160 1720
975 700
2334 2284 2538 1906 1882 1881
1591 1554 1553
2238 2234 2085
1756 1764
1609 1610 1606 1607 1605
584 573 795 572 587 586 591 418 2279
2633 2634 2743 2744 2763 2765 2766 2767
2768 2769 2770 2771 2782 2783 2799 2800 2801 2802
2803 2804 2805 2806 2807 2808 2809 2810 2811 2812
2813 2814 2815 2816 2817
2852 2853 
2921 2923 2936 2937 2996 
2962 2963 2964 
3030 3031 3032 3033 3034 3035 3036 3037 3038 3039 3040 3041 3042 3043 3044 3045 3046 3047
3054 3132 3887 3888 3889 4166 4187 4188 4189 4197 4306
4463 4473 4474 4475 4492 4493 4494 4495 4496 4497 4498 4499 4500 4501 4502
4618 4619 4620 4621 4622 4623 4624 4625 4626 4627 4628 4629 4630 
4631 4632 4633 4634 4635 4636 4637 4638 4639 4640 4641 4642 4643 4644 4645 
4646 4647 4648 4649 4650 4651 4652 4653 4654 4655 4656 4657
4696 4697 4698 4699 4700 4701 4702 4703 4704 4705 4706 4707 4708 4709 4710 
4711 4712 4713 4714 4715 4716 4718 4719 4720 4721 4722 4723 4724 4725 4726
4733 4734 4735 4736 4737 4738 4739 4740 4741 4742 4743 4744 4745 4746 4747 
4748 4749 4750 4751 4752 4753 4754 4764 4765 4766 4767 4768 4769 4770 4771 
4772 4773 4774 4775 4776 4777 4778 4779 4780 4781 4782 4783 4784 4785 4786 
4787 4788 4789 4790 4791 4792 4793 4794 4795 4796 4797 4798 4799 4800 4801 4802 
4945 4946 4947 4948 4949 4950 4951 4952 4953 4954 4955 4956 4957 4958 4959 
4960 4961 4962 4963 4964 4965 4968 4969 4970 4971 4972 4973 4974 4975 4976 
4977 4978 4979 4980 4981 4982 4983 4984 4985 4986 4987 4988 4989 4990 4991 
4992 5092 5096 5097 5098 5099 5100 5175 5176 5411 5412 5413 5419 5421 5422 5456 5462
5734 5735 5736 5737 5738 5739 5740 5741 5742 5743 5744 5745 5746 5868 5869 5870 5871 5894
6499 6543 6565 6566 6567 6568 6569 6570 6571
6647 6648 6649 6650 6651 6652 6653 6654 6656 6657 6658 6659 6660 6661 6662 6663 6664 7004 7012 7013 6944
7128 7129 7131 7287 7288 7289 7334 
7274 7275
7033 7035 7039 7175 7203 7204 7205 7206 7214 7215 7216 7217 7218 7219 7220 7239 7240 7241 7282 7283 7284 7285 7286 7290 7292 7293 7294 7295 7328 7338 7340 7341 7342 7347 7436 7442 7443 7455 7922 7923 7348 7991
}
  # GREAT BRITAIN
  controlledprovinces    = { 3 5 6 7 8 9 10 11 12 13 14 15 16 17 19 20 21 22 23 28 29 348  31 444 
1516 1517
1799 1797 1796 404  1802 1803
406  407  1813 1814 1820 1822 1504 1798 900
1065 1066 1069 1068 1067 1029 1028 1032 1031 1030 1040 1041
1349 1350 1351 1352 1353 1644 1646 1647 1315 758  891  871  873  806  807  808  809  897  538  652 
805  896  866  1147 1148 1816 1817 1136 1815 1132 1139 1062 1140 1141 1064 1060 1061 1059 1035 1112 1111 1105
1124 1125 1104 1099 1129 1126 1128 1000 1001 1002 1008 1007 999  1009 1010 1011 1145 1085 1012 988  982  1622 1683 1684
1685 1686 1759 575  576  1614 1611
2245 1165 1166 1409 1164 1160 1720
975 700
2334 2284 2538 1906 1882 1881
1591 1554 1553
2238 2234 2085
1756 1764
1609 1610 1606 1607 1605
584 573 795 572 587 586 591 418 2279
2633 2634 2743 2744 2763 2765 2766 2767
2768 2769 2770 2771 2782 2783 2799 2800 2801 2802
2803 2804 2805 2806 2807 2808 2809 2810 2811 2812
2813 2814 2815 2816 2817
2852 2853 
2921 2923 2936 2937 2996 
2962 2963 2964 
3030 3031 3032 3033 3034 3035 3036 3037 3038 3039 3040 3041 3042 3043 3044 3045 3046 3047
3054 3132 3887 3888 3889 4166 4187 4188 4189 4197 4306
4463 4473 4474 4475 4492 4493 4494 4495 4496 4497 4498 4499 4500 4501 4502
4618 4619 4620 4621 4622 4623 4624 4625 4626 4627 4628 4629 4630 
4631 4632 4633 4634 4635 4636 4637 4638 4639 4640 4641 4642 4643 4644 4645 
4646 4647 4648 4649 4650 4651 4652 4653 4654 4655 4656 4657
4696 4697 4698 4699 4700 4701 4702 4703 4704 4705 4706 4707 4708 4709 4710 
4711 4712 4713 4714 4715 4716 4718 4719 4720 4721 4722 4723 4724 4725 4726
4733 4734 4735 4736 4737 4738 4739 4740 4741 4742 4743 4744 4745 4746 4747 
4748 4749 4750 4751 4752 4753 4754 4764 4765 4766 4767 4768 4769 4770 4771 
4772 4773 4774 4775 4776 4777 4778 4779 4780 4781 4782 4783 4784 4785 4786 
4787 4788 4789 4790 4791 4792 4793 4794 4795 4796 4797 4798 4799 4800 4801 4802 
4945 4946 4947 4948 4949 4950 4951 4952 4953 4954 4955 4956 4957 4958 4959 
4960 4961 4962 4963 4964 4965 4968 4969 4970 4971 4972 4973 4974 4975 4976 
4977 4978 4979 4980 4981 4982 4983 4984 4985 4986 4987 4988 4989 4990 4991 
4992 5092 5096 5097 5098 5099 5100 5175 5176 5411 5412 5413 5419 5421 5422 5456 5462
5734 5735 5736 5737 5738 5739 5740 5741 5742 5743 5744 5745 5746 5868 5869 5870 5871 5894
6499 6543 6565 6566 6567 6568 6569 6570 6571
6647 6648 6649 6650 6651 6652 6653 6654 6656 6657 6658 6659 6660 6661 6662 6663 6664 7004 7012 7013 6944
7128 7129 7131 7287 7288 7289 7334 
7274 7275
7033 7035 7039 7175 7203 7204 7205 7206 7214 7215 7216 7217 7218 7219 7220 7239 7240 7241 7282 7283 7284 7285 7286 7290 7292 7293 7294 7295 7328 7338 7340 7341 7342 7347 7436 7442 7443 7455 7922 7923 7348 7991
}

  claimedprovinces 		 = { 
903 2897 915 909 913 914 911 910 907 904 906 902 1800 1801 4 1025 1026 1027 1024 1023 905 1020 912 1021 2898 901 2899 4601 4602 4603 4604 4605 4606 4607 4608 4609 4610 4611 4612 4613 4614 4615 4616 4617 7298 7985
31 444 
1516 1517
1799 1797 1796 404  1802 1803
406  407  1813 1814 1820 1822 1504 1798 900
1065 1066 1069 1068 1067 1029 1028 1032 1031 1030 1040 1041
1349 1350 1351 1352 1353 1644 1646 1647 1315 758  871  873
866  1147 1148 1816 1817 1136 1815 1132 1139 1062 1140 1141 1064 1060 1061 1059 1035 1112 1111 1105
1124 1125 1104 1099 1129 1126 1128 1000 1001 1002 1008 1007 999  1009 1010 1011 1145 1085 1012 988  982  1622 1683 1684
1685 1686 1759 575  1614 1611
975 700
2334 2284 2538 1906 1882 1881
1591 1554 1553
2238 2234 2085
1756 1764
1609 1610 1606 1607 1605
95 418 
2633 2743 2744 2763 2765 2766 2767
2768 2769 2770 2771 2782 2783 2799 2800 2801 2802
2803 2804 2805 2806 2807 2808 2809 2810 2811 2812
2813 2814 2815 2816 2817
2852 2853 
2921 2923 2936 2937 2996  
3132 3887 3888 3889 4166 4187 4188 4189 4197 4306
4463 4473 4474 4475 4492 4493 4494 4495 4496 4497 4498 4499 4500 4501 4502
4618 4619 4620 4621 4622 4623 4624 4625 4626 4627 4628 4629 4630 
4631 4632 4633 4634 4635 4636 4637 4638 4639 4640 4641 4642 4643 4644 4645 
4646 4647 4648 4649 4650 4651 4652 4653 4654 4655 4656 4657
4696 4697 4698 4699 4700 4701 4702 4703 4704 4705 4706 4707 4708 4709 4710 
4711 4712 4713 4714 4715 4716 4718 4719 4720 4721 4722 4723 4724 4725 4726
4733 4734 4735 4736 4737 4738 4739 4740 4741 4742 4743 4744 4745 4746 4747 
4748 4749 4750 4751 4752 4753 4754 4764 4765 4766 4767 4768 4769 4770 4771 
4772 4773 4774 4775 4776 4777 4778 4779 4780 4781 4782 4783 4784 4785 4786 
4787 4788 4789 4790 4791 4792 4793 4794 4795 4796 4797 4798 4799 4800 4801 4802 
4945 4946 4947 4948 4949 4950 4951 4952 4953 4954 4955 4956 4957 4958 4959 
4960 4961 4962 4963 4964 4965 4968 4969 4970 4971 4972 4973 4974 4975 4976 
4977 4978 4979 4980 4981 4982 4983 4984 4985 4986 4987 4988 4989 4990 4991 
4992 5092 5096 5097 5098 5099 5100 5175 5176 5411 5419 5421 5422 5456 5462
5734 5735 5736 5737 5738 5739 5740 5741 5742 5743 5744 5745 5746 5868 5869 5870 5871 5894
6499 6543 6565 6566 6567 6568 6569 6570 6571
7128 7129 7131 7287 7288 7289 7334 
7274 7275
7033 7035 7039 7175 7203 7204 7205 7206 7214 7215 7216 7217 7218 7219 7220 7239 7240 7241 7282 7283 7284 7285 7286 7290 7292 7293 7294 7295 7328 7338 7340 7341 7342 7347 7436 7442 7443 7455 7922 7923 7348 7991
#Ireland
27 26 25 24 30 3048 3049 3050 3051 3052 3053
#Internal
7128 7129
#Carribean
809 891
  }

  # Commonwealth Tech '36
  # UK 1936 techs
  # ######################
techapps               = { 
#Early Infantry Division  
1010 1020 1030 1040 1050 1060 1070 1080 1090
#SEMI-MOTORIZED CAVALRY 
13060 13070 13080 1310 1320 1330 1340 1350 1360 1370 1380
#Early Mountain Division 
1160  1170 1180 1190 1200 1210 1220 1230 1240
#1922 NAVAL INFANTRY
1560
#Motorised Inf
1396
#Engineers
1830 1840 1850 1860
#Interbellum 1930 Supply 
1910 1920 1930 1940 1950 1960 1970 1980

#Interwar Armoured Car 
2860 2870 2880 2020
#Armor 
7600 7610 2620 2010 2630 2640 2646 2650
#Great War Heavy Field Artillery 
2290 2300 2310 2900 2910 2920
#Early Static Anti-Air Artillery 
2800 2450 21180 21190
#Basic Anti-Air Artillery Brigade 
2810 2820 2510

#Short Range Submarine 
3610 3620 3630 3640 3650
#Improved Destroyer 
3010 3020 3030 3040 3050 3060
#Basic Light Cruiser 
3110 3120 3130 3140 3150 3160
#Improved Heavy Cruiser 
3210 3220 3230 3240 3250 3260
#Interwar Battlecruiser
3310 3320 3330 3340
#Early Battleship 
3410 3420 3430 3440 3450 3456 3460 3470
#Improved Light carrier 
12100 12110 12120 12130
#Fleet Carrier 
3510 3520 3530
#Torpedo & ASW 18
3720 3730 3736 3740 3750 3900
#Troopships
3810 3820

#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Early Bomber 
4600 4610 4620 4630 4120 4130
#Multirole fighter
4300 4310 4320 4330 4340
# Transports
4290
#ww1 navalbomber
4700 4710
#CAG 34
4900 4910 4920
#Basic Strategic Bomber 
4800 4810 4820 4220
#SEAPLANES
4740 4750 4760

#Agriculture
5700 5710 5010 5020
#Manufacturing
5810 5820 5050 5830 5060 5070
#Improved Construction Engineering 
5800 5080 5090
#Basic Oil Refining
5190
#Computers
5310 54010 54020 54030 
#Cryptography
5316 5326 5327
#Basic Decimetric Radar Warning Sites 
5410 5416 
#Faculty of Atomic Research 
5470
#Exp. Rocket
5560
#Medicine
5600 5610 5620 5630

#Great War Hospital System 
14000 14010 14020

# WWI Land Doctrines - Entente line: eng fra ita usa bel hol jap 
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# WWII Land Doctrines
6560 6030 

# Naval Doctrines
# 
# Theories
8010 8020 8030 8040 8050 8060 8070 8080
# Amphib
82300
# Logistic Support
82500
# Naval Interdiction
8500 8510 8520 8550 8560 8600 8610
# Engagement Tactics
8900 8910 8920 8930 8940 8950
# Naval Supremacy
8100 8110 8120 8150 8160 8200 8210
# Carrier Doctrine
81650
# Carrier - Scouting Focus Line
81850
# Carrier - Strike Line
81700

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010 9140

} 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 5 
     freedom           = 10 
     free_market       = 1
     professional_army = 2 #UK did not introduce 6-month conscription until April 1939 
     defense_lobby     = 1 
     interventionism   = 1
  }
inventions = { 3000027 }
   headofstate            = {  type = 9 id = 10001  } 
   headofgovernment       = {  type = 9 id = 10002  } 
   foreignminister        = {  type = 9 id = 10003  } 
   armamentminister       = {  type = 9 id = 10004  } 
   ministerofsecurity     = {  type = 9 id = 10005  } 
   ministerofintelligence = {  type = 9 id = 10006  } 
   chiefofstaff           = {  type = 9 id = 10007  } 
   chiefofarmy            = {  type = 9 id = 10008  } 
   chiefofnavy            = {  type = 9 id = 10009  } 
   chiefofair             = {  type = 9 id = 10010  } 
 
landunit = 
   {  name     = "Aldershot Command" 
     location = 19 
     id       = {  type = 12700 id = 1  } 
     Division = 
     {  id       = {  type = 12700 id = 63  } 
       name     = "British Army HQ" 
       type     = hq 
       model    = 2 
       strength = 100
      } 
     Division = 
     {  id            = {  type = 12700 id = 2  } 
       name 	= "1st Infantry Division" 
       type 	= infantry
	   model 	= 8
       strength = 100
	   extra 	= light_armor_brigade
	   brigade_model = 3
      } 
     Division = 
     {  id       = {  type = 12700 id = 3  } 
       name     = "2nd Infantry Division" 
       type     = infantry
		model   = 7	   
       strength = 100
	   extra    = light_armor_brigade
	   brigade_model = 2
      } 
    } 
   landunit = 
   {  name     = "Northern Command" 
     location = 19 
     id       = {  type = 12700 id = 4  } 
     Division = 
     {  id       = {  type = 12700 id = 5  } 
       name     = "5th Infantry Division" 
       type     = infantry 
	   model    = 7
       strength = 100
      }
     Division = 
     {  id       = {  type = 12700 id = 1501  } 
       name     = "49th (West Riding) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      } 
     Division = 
     {  id       = {  type = 12700 id = 1502  } 
       name     = "50th (Northumbrian) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 1503  } 
       name     = "23rd (Northumbrian) Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
     Division = 
     {  id       = {  type = 12700 id = 1504  } 
       name     = "46th Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }   
    } 
   landunit = 
   {  name     = "Southern Command" 
     location = 19 
     id       = {  type = 12700 id = 6  } 
     Division = 
     {  id       = {  type = 12700 id = 7  } 
       name     = "3rd Infantry Division" 
       type     = infantry 
       strength = 100
	   model    = 8
	   extra    = artillery 
       brigade_model = 4
      } 
     Division = 
     {  id       = {  type = 12700 id = 505  } 
       name     = "43rd (Wessex) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 506  } 
       name     = "48th (South Midland) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 507  } 
       name     = "45th Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
     Division = 
     {  id       = {  type = 12700 id = 508  } 
       name     = "61st Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
    } 
   landunit = 
   {  name     = "Scottish Command" 
     location = 19 
     id       = {  type = 12700 id = 509  } 
     Division = 
     {  id       = {  type = 12700 id = 510  } 
       name     = "51st (Highland) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 511  } 
       name     = "52nd (Lowland) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 512  } 
       name     = "9th (Highland) Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
     Division = 
     {  id       = {  type = 12700 id = 513  } 
       name     = "15th (Scottish) Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
    } 
   landunit = 
   {  name     = "Western Command" 
     location = 19 
     id       = {  type = 12700 id = 514  } 
     Division = 
     {  id       = {  type = 12700 id = 515  } 
       name     = "42nd (East Lancashire) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 516  } 
       name     = "53rd (Welsh) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 517  } 
       name     = "55th (West Lancashire) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 518  } 
       name     = "38th (Welsh) Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
     Division = 
     {  id       = {  type = 12700 id = 519  } 
       name     = "59th (Staffordshire) Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
     Division = 
     {  id       = {  type = 12700 id = 520  } 
       name     = "66th Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
    } 
   landunit = 
   {  name     = "Eastern Command" 
     location = 19 
     id       = {  type = 12700 id = 521  } 
     Division = 
     {  id       = {  type = 12700 id = 522  } 
       name     = "4th Infantry Division" 
       type     = infantry 
       strength = 100
	   model    = 8
	   extra    = anti_air
       brigade_model = 2
      } 
     Division = 
     {  id       = {  type = 12700 id = 523  } 
       name     = "44th (Home Counties) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 524  } 
       name     = "54th (East Anglian) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 525  } 
       name     = "12th (Eastern) Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
     Division = 
     {  id       = {  type = 12700 id = 526  } 
       name     = "18th Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
    } 
   landunit = 
   {  name     = "London District" 
     location = 19 
     id       = {  type = 12700 id = 527  } 
     Division = 
     {  id       = {  type = 12700 id = 528  } 
       name     = "1st (London) Division" 
       type     = infantry 
	   model    = 5
       strength = 10
      }  
     Division = 
     {  id       = {  type = 12700 id = 529  } 
       name     = "2nd (London) Division" 
       type     = infantry 
	   model    = 5
       strength = 5
      }  
    } 
   landunit = 
   {  name     = "China Command" 
     location = 19 
     id       = {  type = 12700 id = 8  } 
     Division = 
     {  id       = {  type = 12700 id = 9  } 
       name     = "Hong Kong Defence Force" 
       type     = garrison 
	   model    = 3
       strength = 75 
      } 
    } 
   landunit = 
   {  name     = "Malaya Command" 
     location = 19 
     id       = {  type = 12700 id = 10  } 
     Division = 
     {  id       = {  type = 12700 id = 11  } 
       name     = "Singapore Fortress" 
       type     = garrison
	   model    = 3
       strength = 35 
      } 
    } 
   landunit = 
   {  name     = "Royal West African Frontier Force" 
     location = 19 
     id       = {  type = 12700 id = 282  } 
     Division = 
     {  id       = {  type = 12700 id = 283  } 
       name     = "The Nigeria Regiment" 
       type     = militia 
	   model    = 3
       strength = 70
      } 
    } 
   landunit = 
   {  name     = "British Troops on Gibraltar" 
     location = 19 
     id       = {  type = 12700 id = 12  } 
     Division = 
     {  id       = {  type = 12700 id = 13  } 
       name     = "Gibraltar Defence Force" 
       type     = garrison 
	   model    = 3
       strength = 25 
      } 
    } 
   landunit = 
   {  name     = "Ceylon Command" 
     location = 19 
     id       = {  type = 12700 id = 14  } 
     Division = 
     {  id       = {  type = 12700 id = 15  } 
       name     = "Ceylon Defence Force" 
       type     = militia 
	   model    = 3
       strength = 80
      } 
    } 
   landunit = 
   {  name     = "Malta Command" 
     location = 19 
     id       = {  type = 12700 id = 16  } 
     Division = 
     {  id       = {  type = 12700 id = 17  } 
       name     = "Malta Defence Force" 
       type     = garrison 
	   model    = 3
       strength = 35 
      } 
    } 
   landunit = 
   {  name     = "Middle East Command" 
     location = 907 
     id       = {  type = 12700 id = 18  } 
     Division = 
     {  id       = {  type = 12700 id = 19  } 
       name     = "7th Infantry Division" 
       type     = infantry 
	   model    = 8
       strength = 60
	   extra    = light_armor_brigade
	   brigade_model	= 3
	   locked   = yes
      } 
    }
   landunit = 
   {  name     = "RAF Habbaniya" 
     location = 4157 
     id       = {  type = 12700 id = 20  } 
     Division = 
     {  id       = {  type = 12700 id = 21  } 
       name     = "RAF Habbaniya force" 
       type     = infantry 
	   model    = 8
       strength = 40
	   extra    = armored_car
	   brigade_model = 3
	   locked   = yes
      } 
    }
   landunit = 
   {  name     = "RAF Shaibah" 
     location = 1823 
     id       = {  type = 12700 id = 22  } 
     Division = 
     {  id       = {  type = 12700 id = 23  } 
       name     = "RAF Shaibah force" 
       type     = infantry 
	   model    = 8
       strength = 40
	   extra    = armored_car
	   brigade_model = 3
	   locked   = yes
      } 
    }
   landunit = 
   {  name     = "British Forces in Palestine and Transjordan" 
     location = 19 
     id       = {  type = 12700 id = 530  } 
     Division = 
     {  id       = {  type = 12700 id = 531  } 
       name     = "8th Infantry Division" 
       type     = infantry 
	   model    = 8
       strength = 15
      }
    }
 landunit = 
   {  name     = "Gold Coast Defence Force" 
     location = 19 
     id       = {  type = 12700 id = 43  } 
     Division = 
     {  id       = {  type = 12700 id = 44  } 
       name     = "The Gold Coast Regiment" 
       type     = militia 
	   model    = 3
       strength = 30
      } 
    } 
   landunit = 
   {  name     = "British troops in the Sudan" 
     location = 19 
     id       = {  type = 12700 id = 45  } 
     Division = 
     {  id       = {  type = 12700 id = 46  } 
       name     = "Sudan Defence Force" 
       type     = militia 
	   model    = 3
       strength = 40
      } 
    } 
   landunit = 
   {  name     = "Southern Rhodesia Defence Force" 
     location = 19 
     id       = {  type = 12700 id = 47  } 
     Division = 
     {  id       = {  type = 12700 id = 48  } 
       name     = "Southern Rhodesia Defence Force" 
       type     = militia 
	   model    = 3
       strength = 30
      } 
    } 
   landunit = 
   {  name     = "East Africa Force" 
     location = 19 
     id       = {  type = 12700 id = 55  } 
     Division = 
     {  id       = {  type = 12700 id = 56  } 
       name     = "King's African Rifles" 
       type     = militia 
	   model    = 3
       strength = 70
      } 
    } 
   # ################# 
   # Royal Navy # 
   # ################# 
	navalunit = { 
		id = { type = 12700 id = 84 } 
		name = "Home Fleet" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 85 } 
			name = "HMS Nelson" 
			type = battleship 
			model = 6 
			experience = 20
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 86 } 
			name = "HMS Rodney" 
			type = battleship 
			model = 6 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 87 } 
			name = "HMS Royal Sovereign" 
			type = battleship 
			model = 3 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 88 } 
			name = "HMS Royal Oak" 
			type = battleship 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 89 } 
			name = "HMS Resolution" 
			type = battleship 
			model = 3 
			experience = 20 
			} 
		division = {
			id = { type = 12700 id = 255 }
			name = "HMS Pegasus"
			type = escort_carrier
			model = 0
			experience = 20
			}
		division = { 
			id = { type = 12700 id = 96 } 
			name = "HMS Cairo" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 97 } 
			name = "HMS Galatea" 
			type = light_cruiser 
			model = 4 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 98 } 
			name = "HMS Dunedin" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 99 } 
			name = "HMS Neptune" 
			type = light_cruiser 
			model = 4 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 100 } 
			name = "HMS Orion" 
			type = light_cruiser 
			model = 4 
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 104 } 
		name = "Home Fleet Carrier Force" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 105 } 
			name = "HMS Argus" 
			type = escort_carrier 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 93 } 
			name = "HMS Furious" 
			type = carrier 
			extra1 = cag 
			brigade_model1 = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 2223 } 
			name = "Destroyer Division 35" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 2224 } 
			name = "Destroyer Division 36" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 106 } 
		name = "2nd Submarine Squadron" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 107 } 
			name = "3rd Submarine Flotilla" 
			type = submarine 
			model = 3 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 108 } 
			name = "4th Submarine Flotilla" 
			type = submarine 
			model = 3 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 109 } 
			name = "5th Submarine Flotilla" 
			type = submarine 
			model = 3 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 110 } 
			name = "6th Submarine Flotilla" 
			type = submarine 
			model = 3 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 111 } 
			name = "7th Submarine Flotilla" 
			type = submarine 
			model = 2
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 112 } 
		name = "1st Transport Squadron" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 113 } 
			name = "Suffolk Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 114 } 
			name = "Trojan Star Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 2227 } 
			name = "Destroyer Division 37" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 2228 } 
			name = "Destroyer Division 38" 
			type = destroyer
			model = 3 			
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 115 } 
		name = "2nd Transport Squadron" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 116 } 
			name = "Empire Arquebus Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 117 } 
			name = "Hororata Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 122 } 
			name = "Empire Charmain Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 222 } 
			name = "HMS Dauntless" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 224 } 
			name = "Destroyer Division 31" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 118 } 
		name = "3rd Transport Squadron" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 119 } 
			name = "Clan Macauley Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 120 } 
			name = "Empire Captain Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 121 } 
			name = "Andes Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 144 } 
			name = "Destroyer Division 14" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 145 } 
			name = "Destroyer Division 15" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 123 } 
		name = "4th Transport Squadron" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 124 } 
			name = "Essex Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 125 } 
			name = "Maloja Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 2221 } 
			name = "Destroyer Division 8" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 126 } 
		name = "5th Transport Squadron" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 127 } 
			name = "Empire Splendour Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 128 } 
			name = "Sam Torch Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 129 } 
			name = "Resolution Flotilla" 
			type = transport 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 131 } 
			name = "Destroyer Division 5" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 132 } 
			name = "Destroyer Division 6" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 134 } 
		name = "Destroyer Squadron 2" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 135 } 
			name = "Destroyer Division 8" 
			type = destroyer 
			model = 5 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 136 } 
			name = "Destroyer Division 9" 
			type = destroyer 
			model = 5
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 137 } 
		name = "Destroyer Squadron 3" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 138 } 
			name = "Destroyer Division 10" 
			type = destroyer 
			model = 4
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 139 } 
			name = "Destroyer Division 11" 
			type = destroyer 
			model = 4
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 140 } 
		name = "Destroyer Squadron 4" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 141 } 
			name = "Destroyer Division 12" 
			type = destroyer 
			model = 4
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 142 } 
			name = "Destroyer Division 13" 
			type = destroyer 
			model = 4
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 147 } 
		name = "Mediterranean Fleet" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 148 } 
			name = "HMS Queen Elizabeth" 
			type = battleship 
			model = 4 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 153 } 
			name = "HMS Revenge" 
			type = battleship 
			model = 3 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 156 } 
			name = "HMS Devonshire" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 160 } 
			name = "HMS Exeter" 
			type = heavy_cruiser 
			model = 4 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 161 } 
			name = "HMS York" 
			type = heavy_cruiser 
			model = 4 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 162 } 
			name = "HMS Coventry" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 163 } 
			name = "HMS Curlew" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 164 } 
			name = "HMS Delhi" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 165 } 
			name = "HMS Despatch" 
			type = light_cruiser 
			model = 2
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 166 } 
			name = "HMS Durban" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 167 } 
			name = "HMS Arethusa" 
			type = light_cruiser 
			model = 4 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 149 } 
			name = "HMS Barham" 
			type = battleship 
			model = 4 
			experience = 20 
			extra1 = naval_anti_air_l
			extra2 = naval_fire_controll_l
			extra3 = floatplane
			brigade_model3 = 4
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 174 } 
		name = "1st Submarine Squadron" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 175 } 
			name = "1st Submarine Flotilla" 
			type = submarine 
			model = 4 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 176 } 
			name = "2nd Submarine Flotilla" 
			type = submarine 
			model = 3 
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 177 } 
		name = "America & West Indies Station" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 178 } 
			name = "HMS Dragon" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 179 } 
			name = "HMS Ajax" 
			type = light_cruiser 
			model = 4 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 180 } 
			name = "Destroyer Division 23" 
			type = destroyer 
			model = 2
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 182 } 
		name = "Africa Station" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 183 } 
			name = "HMS Leander" 
			type = light_cruiser 
			model = 4 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 184 } 
			name = "HMS Carlisle" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 185 } 
			name = "Destroyer Division 25" 
			type = destroyer 
			model = 2
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 187 } 
		name = "East Indies Station" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 188 } 
			name = "HMS Norfolk" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 189 } 
			name = "HMS Diomede" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 190 } 
			name = "HMS Emerald" 
			type = light_cruiser 
			model = 3 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 191 } 
			name = "HMS Enterprise" 
			type = light_cruiser 
			model = 3 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 192 } 
			name = "Destroyer Division 27" 
			type = destroyer 
			model = 4
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 193 } 
			name = "Destroyer Division 28" 
			type = destroyer 
			model = 4
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 194 } 
		name = "China Station" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 195 } 
			name = "HMS Eagle" 
			type = escort_carrier 
			model = 1 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 196 } 
			name = "HMS Capetown" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 197 } 
			name = "Destroyer Division 29" 
			type = destroyer 
			model = 4
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 198 } 
			name = "Destroyer Division 30" 
			type = destroyer 
			model = 4 
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 199 } 
		name = "3rd Submarine Squadron" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 200 } 
			name = "8th Submarine Flotilla" 
			type = submarine 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 201 } 
			name = "9th Submarine Flotilla" 
			type = submarine 
			model = 2 
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 239 } 
		name = "4th Submarine Squadron" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 240 } 
			name = "10th Submarine Flotilla" 
			type = submarine 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 241 } 
			name = "11th Submarine Flotilla" 
			type = submarine 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 242 } 
			name = "12th Submarine Flotilla" 
			type = submarine 
			model = 2 
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 202 } 
		name = "Reserve Fleet" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 208 } 
			name = "HMS Berwick" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 209 } 
			name = "HMS Cornwall" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 210 } 
			name = "HMS Cumberland" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 211 } 
			name = "HMS Suffolk" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 212 } 
			name = "HMS Kent" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 217 } 
			name = "HMS Colombo" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 218 } 
			name = "HMS Cardiff" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 219 } 
			name = "HMS Ceres" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 220 } 
			name = "HMS Curacao" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 221 } 
			name = "HMS Danae" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		}         
	navalunit = { 
		id = { type = 12700 id = 2219 } 
		name = "Force A" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 90 } 
			name = "HMS Ramillies" 
			type = battleship 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 91 } 
			name = "HMS Hood" 
			type = battlecruiser 
			model = 2 
			experience = 20 
			extra1 = floatplane
			extra2 = naval_fire_controll_l
			brigade_model1 = 4
			brigade_model2 = 1
			} 
		division = { 
			id = { type = 12700 id = 92 } 
			name = "HMS Renown" 
			type = battlecruiser 
			model = 1 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 94 } 
			name = "HMS Repulse" 
			type = battlecruiser 
			model = 1 
			experience = 20 
			extra1 = naval_anti_air_l
			extra2 = naval_fire_controll_l
			extra3 = naval_improved_hull_l
			extra4 = floatplane
			brigade_model4 = 4
			} 
		division = { 
			id = { type = 12700 id = 103 } 
			name = "Destroyer Division 3" 
			type = destroyer 
			model = 3 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 102 } 
			name = "Destroyer Division 2" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 95 } 
			name = "Destroyer Division 4" 
			type = destroyer 
			model = 3 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 101 } 
			name = "Destroyer Division 1" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 2229 } 
		name = "Force C" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 2231 } 
			name = "Destroyer Division 39" 
			type = destroyer
			model = 3		
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 2232 } 
			name = "Destroyer Division 40" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 154 } 
			name = "HMS Courageous" 
			type = carrier 
			extra1 = cag 
			brigade_model1 = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 155 } 
			name = "HMS Glorious" 
			type = carrier 
			extra1 = cag 
			brigade_model1 = 2 
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 2334 } 
		name = "Force B" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 203 } 
			name = "HMS Hermes" 
			type = escort_carrier 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 223 } 
			name = "HMS Achilles" 
			type = light_cruiser 
			model = 4 
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 2338 } 
		name = "Force D" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 204 } 
			name = "HMS Effingham" 
			type = heavy_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 205 } 
			name = "HMS Frobisher" 
			type = heavy_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 206 } 
			name = "HMS Dorsetshire" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 207 } 
			name = "HMS Hawkins" 
			type = heavy_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 564 } 
			name = "HMS Erebus" 
			type = heavy_cruiser 
			model = 2 
			experience = 20 
			extra1 = naval_fire_controll_s
			brigade_model1 = 0
			} 
		division = { 
			id = { type = 12700 id = 565 } 
			name = "HMS Terror" 
			type = heavy_cruiser 
			model = 2 
			experience = 20 
			extra1 = naval_fire_controll_s
			brigade_model1 = 0
			} 
		division = { 
			id = { type = 12700 id = 213 } 
			name = "HMS Caledon" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 214 } 
			name = "HMS Calypso" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 215 } 
			name = "HMS Caradoc" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 216 } 
			name = "HMS Calcutta" 
			type = light_cruiser 
			model = 2 
			experience = 20 
			} 
		} 
	navalunit = { 
		id = { type = 12700 id = 2342 } 
		name = "Force E" 
		location = 21 
		base = 21 
		division = { 
			id = { type = 12700 id = 150 } 
			name = "HMS Valiant" 
			type = battleship 
			model = 4 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 151 } 
			name = "HMS Malaya" 
			type = battleship 
			model = 4 
			experience = 20 
			extra1 = naval_anti_air_l
			extra2 = naval_fire_controll_l
			extra3 = floatplane
			brigade_model3 = 4
			} 
		division = { 
			id = { type = 12700 id = 157 } 
			name = "HMS London" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 158 } 
			name = "HMS Shropshire" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 159 } 
			name = "HMS Sussex" 
			type = heavy_cruiser 
			model = 3 
			experience = 20 
			extra1 = floatplane
			brigade_model1 = 4
			} 
		division = { 
			id = { type = 12700 id = 173 } 
			name = "Destroyer Division 22" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 172 } 
			name = "Destroyer Division 21" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 171 } 
			name = "Destroyer Division 20" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 170 } 
			name = "Destroyer Division 19" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 169 } 
			name = "Destroyer Division 18" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		division = { 
			id = { type = 12700 id = 168 } 
			name = "Destroyer Division 17" 
			type = destroyer 
			model = 3
			experience = 20 
			} 
		} 
   # ################# 
   # Royal Airforce # 
   # ################# 
   airunit = 
   {  location = 21 
     base     = 21 
     id       = {  type = 12700 id = 67  } 
     name     = "1st Tactical Wing" 
     Division = 
     {  id       = {  type = 12700 id = 64  } 
       name     = "No.1 RAF Tactical Group" 
       type     = tactical_bomber 
       model    = 5 
       strength = 20
      } 
    } 
   airunit = 
   {  location = 21 
     base     = 21 
     id       = {  type = 12700 id = 65  } 
     name     = "RAF Strategic Bomber Command" 
     Division = 
     {  id       = {  type = 12700 id = 66  } 
       name     = "No.2 RAF Strategic Group" 
       type     = strategic_bomber 
       model    = 2
       strength = 20
      } 
     Division = 
     {  id       = {  type = 12700 id = 68  } 
       name     = "no.3 RAF Strategic Group" 
       type     = strategic_bomber 
       model    = 3
       strength = 20
      } 
     Division = 
     {  id       = {  type = 12700 id = 69  } 
       name     = "no.4 RAF Strategic Group" 
       type     = strategic_bomber 
       model    = 3
       strength = 20
      } 
    } 
   airunit = 
   {  location = 21 
     base     = 21 
     id       = {  type = 12700 id = 70  } 
     name     = "2nd Tactical Wing" 
     Division = 
     {  id       = {  type = 12700 id = 71  } 
       name     = "No.5 RAF Tactical Group" 
       type     = tactical_bomber 
       model    = 5 
       strength = 20
      } 
    } 
   airunit = 
   {  location = 21 
     base     = 21 
     id       = {  type = 12700 id = 72  } 
     name     = "1st Fighter Wing" 
     Division = 
     {  id       = {  type = 12700 id = 73  } 
       name     = "No.11 RAF Fighter Group" 
       type     = interceptor 
       model    = 7
       strength = 20
      } 
    } 
   airunit = 
   {  location = 21 
     base     = 21 
     id       = {  type = 12700 id = 74  } 
     name     = "2nd Fighter Wing" 
     Division = 
     {  id       = {  type = 12700 id = 75  } 
       name     = "No.12 RAF Fighter Group" 
       type     = Multi_role
       model    = 3
       strength = 20
      } 
    } 
   airunit = 
   {  location = 21 
     base     = 21 
     id       = {  type = 12700 id = 76  } 
     name     = "3rd Fighter Wing" 
     Division = 
     {  id       = {  type = 12700 id = 77  } 
       name     = "No.13 RAF Fighter Group" 
       type     = interceptor 
       model    = 7
       strength = 20
      } 
    } 
   airunit = 
   {  location = 21 
     base     = 21 
     id       = {  type = 12700 id = 78  } 
     name     = "Middle East Air Command" 
     Division = 
     {  id       = {  type = 12700 id = 79  } 
       name     = "Middle East Group" 
       type     = tactical_bomber 
       model    = 5 
       strength = 20
      } 
    } 
   airunit = 
   {  location = 21 
     base     = 21 
     id       = {  type = 12700 id = 82  } 
     name     = "Far East Air Command" 
     Division = 
     {  id       = {  type = 12700 id = 83  } 
       name     = "Far East Group" 
       type     = tactical_bomber
       model    = 5
       strength = 20
      } 
    } 
	
	
	# Warships Under Construction# 
	division_development = {
		name  = "HMS Warspite" # 1934-37 refit
		type  = battleship 
		model = 4 
		new_model = no
		cost  = 0.5 
		unitcost = no
		id    = {  type = 12700 id = 152  } 
		date  = {  year = 1937 month = january day = 1  } 
		extra1 = naval_anti_air_l
		extra2 = naval_fire_controll_l
		extra3 = floatplane
		brigade_model3 = 4
	} 
	division_development = {
		name  = "Destroyer Division 33" 
		type  = destroyer 
		model = 5 
		cost  = 0.1 
		id    = {  type = 12700 id = 226  } 
		date  = {  year = 1936 month = march day = 1  } 
	} 
	division_development = {
		name  = "Destroyer Division 34" 
		type  = destroyer 
		model = 5 
		cost  = 0.1 
		id    = {  type = 12700 id = 227  } 
		date  = {  year = 1936 month = april day = 1  } 
	} 
   division_development = 
   {  name  = "13th Submarine Flotilla" 
     type  = submarine 
     model = 4 
     cost  = 0.1 
     id    = {  type = 12700 id = 228  } 
     date  = {  year = 1936 month = march day = 1  } 
    }
   division_development = 
   {  name  = "HMS Aurora" 
     type  = light_cruiser 
     model = 4 
     new_model = no
     cost  = 0.1 
     id    = {  type = 12700 id = 229  } 
     date  = {  year = 1937 month = november day = 12  } 
    }
   division_development = 
   {  name  = "HMS Birmingham" 
     type  = light_cruiser 
     model = 5
     new_model = no
     cost  = 0.1 
     id    = {  type = 12700 id = 230  } 
     date  = {  year = 1937 month = november day = 18  } 
    }
   division_development = 
   {  name  = "HMS Glasgow" 
     type  = light_cruiser 
     model = 5
     new_model = no
     cost  = 0.1 
     id    = {  type = 12700 id = 231  } 
     date  = {  year = 1937 month = september day = 9  } 
    }
   division_development = 
   {  name  = "HMS Newcastle" 
     type  = light_cruiser 
     model = 5
     new_model = no
     cost  = 0.1 
     id    = {  type = 12700 id = 232  } 
     date  = {  year = 1937 month = march day = 5  } 
    }
   division_development = 
   {  name  = "HMS Penelope" 
     type  = light_cruiser 
     model = 4 
     new_model = no
     cost  = 0.1 
     id    = {  type = 12700 id = 233  } 
     date  = {  year = 1936 month = november day = 13  } 
    }
   division_development = 
   {  name  = "HMS Sheffield" 
     type  = light_cruiser 
     model = 5 
     new_model = no
     cost  = 0.1 
     id    = {  type = 12700 id = 234  } 
     date  = {  year = 1937 month = august day = 25  } 
    }
   division_development = 
   {  name  = "HMS Southampton" 
     type  = light_cruiser 
     model = 5 
     new_model = no
     cost  = 0.1 
     id    = {  type = 12700 id = 235  } 
     date  = {  year = 1937 month = march day = 6  } 
    }
   division_development = 
   {  name  = "HMS Ark Royal" 
     type  = carrier 
     model = 2
     new_model = no
     cost  = 0.1
     id    = {  type = 12700 id = 236  } 
     date  = {  year = 1939 month = march day = 1  } 
      extra = cag  
      brigade_model = 2  
    } 

# Historically, these two ships were gifted to Australia.  
# Including them, because they were commissioned into the RN in 1936.
# Maybe we can add an event to transfer them, I think WIF did that.
   division_development = 
   {  name  = "HMS Amphion" 
     type  = light_cruiser 
     model = 4 
     new_model = no
     cost  = 0.1 
     id    = {  type = 12700 id = 237  } 
     date  = {  year = 1936 month = june day = 15  } 
    }
   division_development = 
   {  name  = "HMS Apollo" 
     type  = light_cruiser 
     model = 4 
     new_model = no
     cost  = 0.1 
     id    = {  type = 12700 id = 238  } 
     date  = {  year = 1936 month = january day = 13  } 
    }


	landdivision = { dormant = yes id = { type = 12700 id = 10001 }  name = "1. Home Guard"   type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10002 }  name = "2. Home Guard"   type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10003 }  name = "3. Home Guard"   type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10004 }  name = "4. Home Guard"   type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10005 }  name = "5. Home Guard"   type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10006 }  name = "6. Home Guard"   type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10007 }  name = "7. Home Guard"   type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10008 }  name = "8. Home Guard"   type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10009 }  name = "9. Home Guard"   type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10010 }  name = "10. Home Guard"  type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10011 }  name = "11. Home Guard"  type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10012 }  name = "12. Home Guard"  type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10013 }  name = "13. Home Guard"  type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10014 }  name = "14. Home Guard"  type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10015 }  name = "15. Home Guard"  type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10016 }  name = "16. Home Guard"  type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10017 }  name = "17. Home Guard"  type = garrison model = 5 extra = artillery brigade_model = 9 }
	landdivision = { dormant = yes id = { type = 12700 id = 10018 }  name = "18. Home Guard"  type = garrison model = 5 extra = artillery brigade_model = 9 }
	
	#2401800 Wilfred
	landdivision = { dormant = yes id = { type = 12700 id = 10020 }  name = "5th 'Globe Trotters' Division" 	type = infantry model = 10 											}
	landdivision = { dormant = yes id = { type = 12700 id = 10021 }  name = "49th 'West Riding' Division"  		type = infantry model = 10 											}
	landdivision = { dormant = yes id = { type = 12700 id = 10022 }  name = "1st Infantry Division"  			type = infantry model = 10 											}
	
	#2401830 Torch
	landdivision = { dormant = yes id = { type = 14800 id = 807 }	 name = "78th 'Battleaxe' Division" 		type = infantry model = 10	extra = engineer  brigade_model = 4 	} 
	landdivision = { dormant = yes id = { type = 14800 id = 808 }	 name = "1st/3rd Special Service Brigades" 	type = marine 	model = 4	strength = 80							} 
	
	#2401840 Overlord
	landdivision = { dormant = yes id = { type = 14800 id = 832 }  name = "21st Army Group HQ" 					type = hq 		model = 4										 	}
	landdivision = { dormant = yes id = { type = 14800 id = 833 }  name = "50th 'Northumbrian' Division" 		type = infantry model = 11	extra = medium_armor brigade_model = 5 	}
	landdivision = { dormant = yes id = { type = 14800 id = 834 }  name = "7th 'Desert Rats' Division"			type = armor 	model = 2	 									 	}
	landdivision = { dormant = yes id = { type = 14800 id = 835 }  name = "1st/4th Special Service Brigades" 	type = marine 	model = 5	strength = 80							} 
	landdivision = { dormant = yes id = { type = 14800 id = 836 }  name = "51st 'Highland' Division" 			type = infantry model = 11	extra = medium_armor brigade_model = 5 	} 
	landdivision = { dormant = yes id = { type = 14800 id = 837 }  name = "3rd 'Ironsides' Division" 			type = infantry model = 11											}
	landdivision = { dormant = yes id = { type = 14800 id = 838 }  name = "6th Airborne Division" 				type = paratrooper model = 2									 	}
	landdivision = { dormant = yes id = { type = 14800 id = 839 }  name = "79th 'Funnies' Division" 			type = armor 	model = 2	 									 	}
	
	#2401850 Dragoon (did not participate)
	
	#2401860 Husky
	landdivision = { dormant = yes id = { type = 14800 id = 878 }  name = "8th Army Group HQ" 					type = hq 		model = 4										 	}
	landdivision = { dormant = yes id = { type = 14800 id = 879 }  name = "1st/4th Special Service Brigades"	type = marine 	model = 5	strength = 80							} 
	landdivision = { dormant = yes id = { type = 14800 id = 880 }  name = "5th 'Globe Trotters' Division" 		type = infantry model = 11 	extra = artillery brigade_model = 10 	} 
	landdivision = { dormant = yes id = { type = 14800 id = 881 }  name = "50th 'Northumbrian' Division" 		type = infantry model = 11 	extra = medium_armor brigade_model = 5	}
	landdivision = { dormant = yes id = { type = 14800 id = 882 }  name = "51st 'Highland' Division"			type = infantry model = 11 	extra = medium_armor brigade_model = 5	}
	landdivision = { dormant = yes id = { type = 14800 id = 883 }  name = "78th 'Battleaxe' Division"			type = infantry model = 11 	extra = engineer  brigade_model = 4 	} 
	landdivision = { dormant = yes id = { type = 14800 id = 884 }  name = "1st Airborne Division"				type = paratrooper model = 11 extra = glider_artillery brigade_model = 1 } 
	landdivision = { dormant = yes id = { type = 14800 id = 885 }  name = "1st Infantry Division"				type = infantry model = 11 										 	} 
  } 
 
