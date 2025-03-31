#####################
# Country main data #
#####################

country =
{ tag                    = CAN
  puppet				 = ENG
  #control				 = ENG #AI will not autonomously suppress revolts otherwise
  ai_settings			 = { flags = { puppetLevel9 = 1 } }
   # Resource Reserves 
	energy                 = 2460
	metal                  = 1230
	rare_materials         = 615
    oil                    = 500 
    supplies               = 500 
    money                  = 20 
    manpower               = 18 
    transports             = 100 
    escorts                = 10
  capital                = 588
  diplomacy =
  { relation = { tag = AST value = 200 } # was access = yes
    relation = { tag = BEL value = 150 }
    relation = { tag = BHU value = 200 }
    relation = { tag = ENG value = 200 } # was access = yes
    relation = { tag = FRA value = 150 }
    relation = { tag = GER value = 1 }
    relation = { tag = HOL value = 80 }
    relation = { tag = IRE value = 75 }
    relation = { tag = IRQ value = 100 }
    relation = { tag = ITA value = 1 }
    relation = { tag = NEP value = 200 }
    relation = { tag = NZL value = 200 } # was access = yes
    relation = { tag = OMN value = 150 }
    relation = { tag = SAF value = 200 } # was access = yes
    relation = { tag = USA value = 175 }
    relation = { tag = YEM value = 150 }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 3 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 2 }
  SpyInfo                = { country = "SOV" NumberOfSpies = 2 }
  SpyInfo                = { country = "USA" NumberOfSpies = 5 }
  claimedprovinces       = { 6635 6636 6637 6638 6633 2736 6634 6623 6624 6625 2732 6632 6640 2735 6645 6644 6646 6598 6643 1909 6641 6642 2734 585 574 6626 6631 2733 6630 6628 6627 6629 6609 6608 }
  nationalprovinces      = {
6671 6765 6828 6700 6704 6705 6818 6706 6821 6736 2725 6647 6809 6697 6775 6835 6615 6675 6677 578 6840 6751 6702 2726 6661 6826 6802 6681 6732 590 6779 6781 6720 6808 6734 6595 6665 6733 6825 6755 6731 6814 6607 580 6797 6653 565 6650 6811 6837 6717 6756 6768 6778 6699 6791 6836 6660 2730 6822 6656 6662 6618 6742 6723 6780 6692 6617 6599 6819 6786 6760 6777 6740 6838 6648 6610 6726 2727 6668 6746 6783 6794 7015 6815 6596 6620 6824 6749 6695 6787 6764 6744 6817 6728 6663 552 6766 6689 6727 6606 6683 6801 575 558 6669 6654 6593 6687 6799 6694 6714 6829 6793 6696 576 569 588 6672 6803 6611 2731 6718 6743 6691 6614 6735 6805 6701 6666 554 6776 560 556 6752 6796 799 6741 6748 6834 6754 6686 6753 6769 6685 6693 6763 6820 6830 6767 6812 571 6639 6649 6722 6658 6790 6616 6680 6719 6782 796 6594 6788 6690 6713 798 6712 6798 6770 6807 6831 6842 6674 541 2728 6655 6784 2729 6710 6622 6738 6621 6659 6724 6679 6707 6804 6664 6684 6816 6759 6841 555 6721 6652 6785 6761 6651 579 6832 6730 6603 6827 589 564 6682 6716 6771 6772 6833 6688 6590 6676 6800 6708 6806 6792 6774 6613 6737 6657 6601 6600 6711 6823 6619 566 6810 6604 6789 6762 6839 6813 6739 6757 6678 6758 6745 6591 6698 6597 6602 797 6592 6605 6670 6703 6747 6725 6673 6667 6715 6729 6709 6795 6612 6750 6773
6633 6635 6636 6637 6638
                           }
  ownedprovinces         = { 
556 541 555 554 552 558 796 797 799 798 560 566 569 571 565 588 589 590 585 574 564 580 579 578 1909 2725 2726 2727 2728 2729 2730 2731 2732 2733 2734 2735 2736 6590 6591 6592 6593 6594 6595 6596 6597 6598 6599 6600 6601 6602 6603 6604 6605 6606 6607 6608 6609 6610 6611 6612 6613 6614 6615 6616 6617 6618 6619 6620 6621 6622 6623 6624 6625 6626 6627 6628 6629 6630 6631 6632 6633 6634 6635 6636 6637 6638 6639 6640 6641 6642 6643 6644 6645 6646 6655 6665 6666 6667 6668 6669 6670 6671 6672 6673 6674 6675 6676 6677 6678 6679 6680 6681 6682 6683 6684 6685 6686 6687 6688 6689 6690 6691 6692 6693 6694 6695 6696 6697 6698 6699 6700 6701 6702 6703 6704 6705 6706 6707 6708 6709 6710 6711 6712 6713 6714 6715 6716 6717 6718 6719 6720 6721 6722 6723 6724 6725 6726 6727 6728 6729 6730 6731 6732 6733 6734 6735 6736 6737 6738 6739 6740 6741 6742 6743 6744 6745 6746 6747 6748 6749 6750 6751 6752 6753 6754 6755 6756 6757 6758 6759 6760 6761 6762 6763 6764 6765 6766 6767 6768 6769 6770 6771 6772 6773 6774 6775 6776 6777 6778 6779 6780 6781 6782 6783 6784 6785 6786 6787 6788 6789 6790 6791 6792 6793 6794 6795 6796 6797 6798 6799 6800 6801 6802 6803 6804 6805 6806 6807 6808 6809 6810 6811 6812 6813 6814 6815 6816 6817 6818 6819 6820 6821 6822 6823 6824 6825 6826 6827 6828 6829 6830 6831 6832 6833 6834 6835 6836 6837 6838 6839 6840 6841 6842 7015 
                           }
  controlledprovinces    = { 
556 541 555 554 552 558 796 797 799 798 560 566 569 571 565 588 589 590 585 574 564 580 579 578 1909 2725 2726 2727 2728 2729 2730 2731 2732 2733 2734 2735 2736 6590 6591 6592 6593 6594 6595 6596 6597 6598 6599 6600 6601 6602 6603 6604 6605 6606 6607 6608 6609 6610 6611 6612 6613 6614 6615 6616 6617 6618 6619 6620 6621 6622 6623 6624 6625 6626 6627 6628 6629 6630 6631 6632 6633 6634 6635 6636 6637 6638 6639 6640 6641 6642 6643 6644 6645 6646 6655 6665 6666 6667 6668 6669 6670 6671 6672 6673 6674 6675 6676 6677 6678 6679 6680 6681 6682 6683 6684 6685 6686 6687 6688 6689 6690 6691 6692 6693 6694 6695 6696 6697 6698 6699 6700 6701 6702 6703 6704 6705 6706 6707 6708 6709 6710 6711 6712 6713 6714 6715 6716 6717 6718 6719 6720 6721 6722 6723 6724 6725 6726 6727 6728 6729 6730 6731 6732 6733 6734 6735 6736 6737 6738 6739 6740 6741 6742 6743 6744 6745 6746 6747 6748 6749 6750 6751 6752 6753 6754 6755 6756 6757 6758 6759 6760 6761 6762 6763 6764 6765 6766 6767 6768 6769 6770 6771 6772 6773 6774 6775 6776 6777 6778 6779 6780 6781 6782 6783 6784 6785 6786 6787 6788 6789 6790 6791 6792 6793 6794 6795 6796 6797 6798 6799 6800 6801 6802 6803 6804 6805 6806 6807 6808 6809 6810 6811 6812 6813 6814 6815 6816 6817 6818 6819 6820 6821 6822 6823 6824 6825 6826 6827 6828 6829 6830 6831 6832 6833 6834 6835 6836 6837 6838 6839 6840 6841 6842 7015 
                           }
  # Commonwealth Tech '36
  # UK 1936 techs
  # ######################
   techapps               = { 
#Early Infantry Division  
1010  1020 1030 1040 1050 1060 1070 1080 1090
#Basic Cavalry Division 
13060 13070 13080 1310 1320 1330 1340 1350 1360 1370 1380 1390
#Great War Hospital System 
14000 14010 14020
# Inf support 
1910 1920 1930 1940 1950 1960 1970 1980
#Engineers
1830 1840 1850 1860
#Great War Tank 
7600 7610 2620 2010 2630
#Basic Armoured Car  
2860 2870 2880 2020
#Great War Heavy Field Artillery 
2290 2300 2310
#Early Static Anti-Air Artillery 
2800 2450 21180 21190 21200
#Basic Anti-Air Artillery Brigade 
2810 2820 2510
#Improved Destroyer 
3010 3020 3030 3040 3050 3060
#Early Light Cruiser 
3110 3120 3130
#Early Fighter  
4500 4510 4520 4530 4540 4550 4010 4020
#Early Bomber 
4600 4610 4620 4630 4120 4130
#Multirole fighter
4300 4310 4320 4330
#ww1 strategic bomber
4800 4810 4820
#ww1 navalbomber
#SEAPLANES
4740 4750 4760 4770
# Transport planes
4290
#Mechanized Agriculture 
5700 5710 5010 5020
#Manufactoring
5810 5820 5050 5830 5060
#Improved Construction Engineering 
5800 5080 5090 
#Basic Oil Refining 
#5190
#Computers & cryptografi
5310 54010 54020 54030 5316 5326
# Submarines
3610 3620 3630 3640
#Torpedo & ASW 18
3720 3730 3736 3740 3900
#Troopships
3810 3820
#Medicine
5600 5610 5620 5630
#Exp. Rocket
5560
# Great War Land Doctrines (entente)
6500 6510 6530 6580 6600 6610 6680 6620 6630 6640 6650 6660 6670 6540 6910
# Defensive Focus Grand Battleplan Path (FRA / UK)
6560 6030
# Engagement Theories
8010 8020 8040 8050 8060 8070 8080
# Naval Supremacy
8100 8110 8120 8150 8160 8200 8210
# Naval Interdiction
8500 8510 8520 8600
# Engagement Tactics
8900 8910 8920 8930 8940

#Air Doctrines - ww2 techs
27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010  9140  
} 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 5 
     free_market       = 1
     freedom           = 8 
     professional_army = 2 
     defense_lobby     = 2 
     interventionism   = 1
  }
inventions = { 3000027 }

   headofstate            = {  type = 9 id = 220001  } 
   headofgovernment       = {  type = 9 id = 220002  } 
   foreignminister        = {  type = 9 id = 220003  } 
   armamentminister       = {  type = 9 id = 220004  } 
   ministerofsecurity     = {  type = 9 id = 220005  } 
   ministerofintelligence = {  type = 9 id = 220006  } 
   chiefofstaff           = {  type = 9 id = 220007  } 
   chiefofarmy            = {  type = 9 id = 220008  } 
   chiefofnavy            = {  type = 9 id = 220009  } 
   chiefofair             = {  type = 9 id = 220010  } 
 
   landunit = 
   {  id       = {  type = 20000 id = 1  } 
     name     = "Canadian Army" 
     location = 588 
     Division = 
     {  id       = {  type = 20000 id = 2  } 
       name     = "1st Canadian Infantry Division" 
       strength = 25 
       type     = infantry 
       model    = 7 
      } 
     Division = 
     {  id       = {  type = 20000 id = 3  } 
       name     = "2nd Canadian Infantry Division" 
       strength = 5 
       type     = infantry 
       model    = 7 
      } 
    } 
   airunit = 
   {  id       = {  type = 20000 id = 4  } 
     name     = "Royal Canadian Air Force" 
     location = 588 
     base     = 588
     Division = 
     {  id       = {  type = 20000 id = 5  } 
       name     = "No.1 Group RCAF" 
       strength = 15
       type     = multi_role
       model    = 2 
      } 
     Division = 
     {  id       = {  type = 20000 id = 6  } 
       name     = "No.2 Group RCAF" 
       strength = 15 
       type     = transport_plane
       model    = 0
      } 
    } 
	navalunit = { 
		id = { type = 20000 id = 500 } 
		name = "Canadian Transport Fleet" 
		location = 579 
		base = 579 
		division = { 
			id = { type = 30053 id = 504 } 
			name = "'Empress of Canada' Flotilla" 
			type = transport 
			model = 1
			} 
		division = { 
			id = { type = 30053 id = 505 } 
			name = "'Empress of Russia' Flotilla" 
			type = transport
			model = 1
			} 
		division = { 
			id = { type = 30053 id = 506 } 
			name = "'Empress of Asia' Flotilla" 
			type = transport 
			model = 1
			} 
		division = { 
			id = { type = 30053 id = 2279 } 
			name = "Destroyer Flotilla 2" 
			type = destroyer 
			model = 4
			} 
		division = { 
			id = { type = 30053 id = 2280 } 
			name = "Destroyer Flotilla 4" 
			type = destroyer 
			model = 3
			} 
		} 
	navalunit = { 
		id = { type = 20000 id = 7 } 
		name = "Royal Canadian Navy" 
		location = 579 
		base = 579 
		division = { 
			id = { type = 20000 id = 8 } 
			name = "Destroyer Flotilla 1" 
			type = destroyer 
			model = 4 
			} 
		division = { 
			id = { type = 30053 id = 501 } 
			name = "'Empress of Japan' Flotilla" 
			type = transport 
			model = 1
			} 
		division = { 
			id = { type = 30053 id = 502 } 
			name = "'Empress of Australia' Flotilla" 
			type = transport 
			model = 1
			} 
		division = { 
			id = { type = 30053 id = 503 } 
			name = "'Empress of Britain' Flotilla" 
			type = transport 
			model = 1
			} 
		division = { 
			id = { type = 30053 id = 2282 } 
			name = "Destroyer Flotilla 3" 
			type = destroyer 
			model = 3
			} 
		} 

	#2401840 Overlord	
	landdivision = { dormant = yes id = { type = 14800 id = 840 }  name = "3rd 'Water Rats' Division" 			type = infantry model = 11	extra = medium_armor brigade_model = 5 	}
	
	#2401860 Husky
	landdivision = { dormant = yes id = { type = 14800 id = 886 }  name = "1st Infantry Division"	 			type = infantry model = 11	extra = medium_armor brigade_model = 5 	}
  }  
 