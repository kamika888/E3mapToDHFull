#####################
# Country main data #
#####################

country =
{ tag                    = SOV
  regular_id             = RUS
  intrinsic_gov_type     = leninist
  ai_settings			 = { flags = { WARDebt = 8 } }
  capital                = 175
	# Resource Reserves 
	energy                 = 16000 
	metal                  = 8000 
	rare_materials         = 4000 
	oil                    = 4000 
	supplies               = 500 
	money                  = 30 
	manpower               = 1453 #mob 5 instead of 6
	dissent                = 5 
	transports             = 300 
	escorts                = 20 
  diplomacy =
  { relation =
    { tag        = AFG
      value      = 1
    }
    relation = { tag = BRA value = -50 }
    relation =
    { tag        = BUL
      value      = 15
    }
    relation = { tag = CHC value = 100 }
    relation = { tag = CZE value = 100 }
    relation = { tag = ENG value = -25 }
    relation =
    { tag        = EST
      value      = -30
    }
    relation = { tag = FIN value = 1 }
    relation =
    { tag        = FRA
      value      = 100
    }
    relation = { tag = GER value = 1 }
    relation = { tag = GRE value = 15 }
    relation = { tag = IRE value = 1 }
    relation = { tag = JAP value = -10 }
    relation =
    { tag        = LAT
      value      = -30
    }
    relation =
    { tag        = LIT
      value      = -30
    }
    relation = { tag = MON value = 150 access = yes }
    relation =
    { tag        = PER
      value      = -20
    }
    relation = { tag = POL value = -50 }
    relation = { tag = ROM value = 1 }
    relation = { tag = SAU value = 1 }
    relation = { tag = SIK value = 125 }
    relation = { tag = SPR value = -10 }
    relation =
    { tag        = TAN
      value      = 200
      access     = yes
    }
    relation =
    { tag        = TUR
      value      = 100
    }
    relation = { tag = URU value = -100 }
    relation = { tag = USA value = 35 }
    relation =
    { tag        = SCH
      value      = 1
    }
  }
  SpyInfo                = { country = "ENG" NumberOfSpies = 2 }
  SpyInfo                = { country = "FRA" NumberOfSpies = 1 }
  SpyInfo                = { country = "GER" NumberOfSpies = 1 }
  SpyInfo                = { country = "CZE" NumberOfSpies = 1 }
  SpyInfo                = { country = "AUS" NumberOfSpies = 1 }
  SpyInfo                = { country = "SPR" NumberOfSpies = 2 }
  SpyInfo                = { country = "POL" NumberOfSpies = 3 }
  SpyInfo                = { country = "SWE" NumberOfSpies = 2 }
  SpyInfo                = { country = "NOR" NumberOfSpies = 1 }
  SpyInfo                = { country = "FIN" NumberOfSpies = 3 }
  SpyInfo                = { country = "YUG" NumberOfSpies = 3 }
  SpyInfo                = { country = "HUN" NumberOfSpies = 2 }
  SpyInfo                = { country = "BUL" NumberOfSpies = 3 }
  SpyInfo                = { country = "BEL" NumberOfSpies = 1 }
  SpyInfo                = { country = "DEN" NumberOfSpies = 1 }
  SpyInfo                = { country = "CXB" NumberOfSpies = 2 }
  SpyInfo                = { country = "MON" NumberOfSpies = 3 }
  SpyInfo                = { country = "CGX" NumberOfSpies = 1 }
  SpyInfo                = { country = "USA" NumberOfSpies = 3 }
  SpyInfo                = { country = "GUA" NumberOfSpies = 1 }
  SpyInfo                = { country = "GRE" NumberOfSpies = 1 }
  SpyInfo                = { country = "CYN" NumberOfSpies = 3 }
  SpyInfo                = { country = "CSX" NumberOfSpies = 1 }
  SpyInfo                = { country = "JAP" NumberOfSpies = 3 }
  SpyInfo                = { country = "ROM" NumberOfSpies = 2 }
  SpyInfo                = { country = "LIT" NumberOfSpies = 2 }
  SpyInfo                = { country = "LUX" NumberOfSpies = 1 }
  SpyInfo                = { country = "POR" NumberOfSpies = 1 }
  SpyInfo                = { country = "ITA" NumberOfSpies = 3 }
  SpyInfo                = { country = "CHI" NumberOfSpies = 2 }
  SpyInfo                = { country = "SCH" NumberOfSpies = 1 }
  
  claimedprovinces 		 = { 
193 194 195 196 199 1886 3286 3287 3288 3394 #Estonia
207 206 511 577 3280 3281 3282 7336 #Lithuania (2606)
205 204 203 197 202 198 3283 3284 3285 3289 #Latvia
3279 7980 7263 214 509 7335 505 6516 1875 6515 #E. Poland
508 3272 305 7050 222 481 211 3267 7262 3266 480 3268 484 485 7049 7048 1876 487 504 3270 #Congress Poland
#229 3396 3273 1884 7979 501 7978 500 507 7984 1173 #Greater Galicia
#3270 3271 504 3231 3230 3233 499 #Chelm&Rusyns
6511 230 7070 434 3389 2605 #Bessarabia
103 141 142 140 143 138 139 137 131 130 132 136 148 147 144 145 146 149 123 2305 2630 2631 3323 3324 3325 3326 3327 #Finland
3328 3329 3330 3331 3332 3333 3334 3335 3336 3337 3338 3339 3340 3344 7148 7149 7150 7151 7152 7153 7154 7155 #Finland
#5389 5388 1486 5400 2867 1493 #Afghanistan
2877 3430 7068 446 4118 #Kars/Armenia

#Internal
1551 6974 6966 6977 3507 6971 1555 3506 1422 6963 6965 3503 6979 3515 6980 3516 6983 6982 3521 6989 1579 3500 6957 1587 6960 6958 6959 3501 1425 1426 3499 6954 6955 6956 1586 1585 1489 3478 3477 1488 3486 3476 3482 3479 1485 3483 3484 1487 6953 3485 3494 3480 3495 1428 6949 3496 6951 3512 3487 2868 3491 6493 1491 3492 3490 3493 3494 1584 3488 2869 3489 3475 1584 3474 6996 6995 1583 6997 6998 3519 6994 6992 3517
6517 3277 209 102 2848 7264 134 7156 3347 3717 3463 1839 3715 252 155 162 1846 3439 3438 1844 2368 7313 1847 2851 3448 7312 3436 1369 1370
  }
  nationalprovinces      = { 
#4198 1788 4201 1859 4202 2840 4206 4203 2839 #South Azerbaijan
#2838 Turkmen Persia
#5403 5404 5402 2866 1484 5399 5398 5401 5496 5397 #Afghanistan
#3738 5482 3739 5481 #China1
#3744 3742 3741 5502 5503 1421 5504 3740 3746 5498 5496 5497 #China2
#1420 7917 #Mongolia
1418 3594 3595 5472 5473 5474 5475 #Tuva
3287 3288 3289 3284 202 #Baltics
3391 435 3390 1401 #Bessarabia
7992 #Karelia
506 502 1885 3274 3275 562 503 3395 213 3278 95 210 3276 #Poland
253 251 3647 7158 1372 273 150 3574 3636 3342 2850 1581 3597 3550 173 3727 244 7002 6988 3637 7252 1773 3604 7245 234 3442 3725 3545 7160 3343 3670 3603 7273 7386 3461 3601 135 3460 1424 3596 3642 1414 3523 3530 1549 6986 228 270 164 192 1783 3614 267 3615 1413 1543 3431 154 3406 6967 3415 7308 7162 3565 3562 6937 3346 3451 1566 3529 7082 1593 6987 3654 3472 2240 7001 7310 200 3420 3585 7940 4149 3536 1845 3605 3694 3728 172 7074 3568 3408 3619 201 1571 3440 3405 184 3540 7078 287 1522 1529 3563 1412 3345 1520 1558 3557 7080 1417 216 3533 231 191 156 1596 219 1567 1836 3648 1533 181 160 7000 3705 3419 3583 3535 3706 1580 7067 7311 7383 1150 133 3624 3692 1152 7085 3731 3584 7087 3639 3643 3718 1565 1550 1907 1858 3421 1569 177 3679 3645 3572 152 183 3704 3537 3497 3612 3581 3602 259 3710 239 6968 6933 151 3669 3618 171 7159 3443 6969 3663 3541 3571 7941 7251 6919 6932 1490 243 1539 3433 1172 1777 3426 1856 3681 6929 3469 3712 233 284 237 3674 3414 7942 3553 3606 3702 225 1523 94 3700 3411 168 250 1781 1545 272 1170 3659 1574 1153 3513 3668 3666 282 1848 275 3416 3582 3729 247 3349 1527 6961 258 3577 281 3428 3657 6934 7943 3695 3693 1840 1774 1828 1546 1842 163 7157 174 1384 3733 249 276 1834 212 218 2614 7250 3560 3573 3662 3656 3508 3664 6930 7079 1564 3450 3660 256 261 7076 3688 3579 3616 3626 1573 3580 3682 2470 3453 1874 3713 1597 1526 3686 3589 1547 3684 1557 3514 3561 3714 158 238 3625 3548 3726 3658 3592 285 1534 3465 6981 1577 3441 1541 3458 3736 3534 1570 6964 1368 269 1776 169 277 7309 1176 3699 3610 3653 1556 1367 3665 242 3471 187 220 1849 3412 3620 1582 3413 3632 161 1775 165 283 157 182 1568 3724 263 1524 3588 3698 3735 3678 3518 7077 3667 3623 2847 227 257 1838 3502 5693 3511 3711 3696 1410 3575 3621 240 7086 7248 3680 3551 1594 3578 289 3527 3730 3429 7247 3607 1366 3683 7243 3341 3547 3661 1832 226 7075 1371 1562 3542 1843 1772 6494 3649 7084 1548 3409 3633 1167 1560 3425 3505 7065 180 3638 1827 3716 3652 3400 7254 3689 2615 268 286 186 6976 3590 3403 3591 3348 3608 3708 3611 185 221 3672 3520 189 3703 3719 264 3410 3600 3587 3675 1175 3593 3687 1782 3464 3732 3417 7244 3627 1542 1155 1778 3457 3559 3569 3576 6978 3635 1572 3462 260 3446 6991 3522 170 3640 3697 7073 176 3644 1429 215 1156 1383 3651 1780 188 262 2849 3622 3685 7081 3701 1427 6935 3691 6984 1416 3707 1540 1841 232 3723 6962 7003 246 190 217 3599 6999 3570 3434 3435 3437 178 1559 3549 6990 1415 1575 1423 1598 1576 3459 7066 179 274 6952 3404 1154 245 266 3423 3641 1525 3720 3468 3567 3538 1552 1829 279 236 271 3456 3628 7939 3631 6931 288 3466 3629 3444 255 1521 6970 3432 3676 1831 3470 166 3609 3424 3539 3671 235 265 3427 3586 3690 6975 1151 1538 3399 3554 3722 7083 153 1535 3407 3447 1833 3452 248 6950 1857 254 3532 3555 1411 159 3566 3402 6973 7385 1149 3709 3617 6972 7272 3630 3473 3510 7161 167 3455 3528 3634 7384 3650 3673 3677 3418 3401 1771 6993 278 1171 6936 1578 1830 1528 280 3422 3598 3454 3445 3721 3546 3449 241 1837 7249 1536 6985 1544 1850 1561 175 3544 3734 3467 3655 3543 3564 7246 2488 7387 3646 7944 3556 7253 3481

#KAZ
1424 1422 1556 1423 1425 1426 1586 1587 1555 1582 1551 1550 1581 1576 1578 1580 1579 1569 1583 1568 3499 3500 3501 3502 3503 3505 3506 3507 3508 3510 3511 3512 3513 3514 3515 3516 3517 3518 3519 3520 3521 3522 3523 6494 6954 6955 6956 6957 6958 6959 6960 6961 6962 6963 6964 6965 6966 6967 6968 6969 6970 6971 6972 6973 6974 6975 6976 6977 6978 6979 6980 6981 6982 6983 6984 6985 6986 6987 6988 6989 6990 6991 6992 6993 6994 6995 6996 6997 6998 3475 1584 1585 3476

#UZB
1427 1488 1489 1585 1584 3474 3475 3476 3477 3478 3479 3480 3486 3481 3482 1485 3483

#KYG
1429 1428 3494 3495 3496 3497 3485 6949 6950 6951 6952

#TAJ
1485 1487 3481 3482 3483 3484 3485 6953

#TRK
1490 1491 2868 2869 3487 3488 3489 3490 3491 3492 3493 6493


8001
}
  ownedprovinces         = { 
1372 1371 1370 1369 1367 1366 1527 1529 1528 1526 1523 1410 1525 1524 1167 1170 1171 1172 1175 1522 1521 1384 1383 1520 1416 1415 1414 1413 1412 1411 1417 1558 1557 1423 1556 1550 1549 1547 1546 1559 1561 1560 1562 1538 1545 1544 1548 1543 1540 1539 1536 1535 1533 1534 1156 1155 1154 1565 1564 1571 1597 1598 1555 1552 1594 1596 1573 1593 1587 1424 1586 1585 1584 1583 1581 1576 1575 1574 1572 1566 1567 1570 1577 1578 1580 1582 1579 1569 1568 1150 1151 1152 1153 1773 1772 1771 154 1840 1841 165 153 151 152 150 135 134 133 1838 1847 1857 1849 1850 1848 1845 1844 1846 1843 255 256 257 270 1842 1837 271 164 1833 1834 1836 1839 1827 1828 1829 1832 1831 1830 252 253 254 1777 1778 1776 1775 1780 1781 1782 1783 1774 163 162 161 160 159 157 156 158 155 169 168 167 179 180 166 178 177 170 171 172 173 174 175 176 181 182 183 184 190 191 189 185 186 187 188 192 200 201 212 225 226 227 228 231 232 233 234 251 250 235 236 237 238 239 240 220 272 241 273 274 275 276 277 278 279 280 281 282 283 284 249 258 259 260 248 247 243 262 261 269 268 267 266 265 264 263 1490 1491 1485 1487 1488 1427 1428 1426 1425 1429 94 215 216 217 218 219 221 242 244 245 246 285 286 287 288 289 1149 1368 1422 1489 1856 1858 1907 1541 1542 1551 1874 2470 2240 2488 2368 2614 2615 2847 2848 2849 2850 2851 2868 2869 3341 3342 3343 3345 3346 3347 3348 3349 3399 3400 3401 3402 3403 3404 3405 3406 3407 3408 3409 3410 3411 3412 3413 3414 3415 3416 3417 3418 3419 3420 3421 3422 3423 3424 3425 3426 3427 3428 3429 3431 3432 3433 3434 3435 3436 3437 3438 3439 3440 3441 3442 3443 3444 3445 3446 3447 3448 3449 3450 3451 3452 3453 3454 3455 3456 3457 3458 3459 3460 3461 3462 3463 3464 3465 3466 3467 3468 3469 3470 3471 3472 3473 3474 3475 3476 3477 3478 3479 3480 3486 3481 3482 3483 3484 3485 3487 3488 3489 3490 3491 3492 3493 3494 3495 3496 3497 3499 3500 3501 3502 3503 3505 3506 3507 3508 3510 3511 3512 3513 3514 3515 3516 3517 3518 3519 3520 3521 3522 3523 3527 3528 3529 3530 3532 3533 3534 3535 3536 3537 3538 3539 3540 3541 3542 3543 3544 3545 3546 3547 3548 3549 3550 3551 3553 3554 3555 3556 3557 3559 3560 3561 3562 3563 3564 3565 3566 3567 3568 3569 3570 3571 3572 3573 3574 3575 3576 3577 3578 3579 3580 3581 3582 3583 3584 3585 3586 3587 3588 3589 3590 3591 3592 3593 3596 3597 3598 3599 3600 3601 3602 3603 3604 3605 3606 3607 3608 3609 3610 3611 3612 3614 3615 3616 3617 3618 3619 3620 3621 3622 3623 3624 3625 3626 3627 3628 3629 3630 3631 3632 3633 3634 3635 3636 3637 3638 3639 3640 3641 3642 3643 3644 3645 3646 3647 3648 3649 3650 3651 3652 3653 3654 3655 3656 3657 3658 3659 3660 3661 3662 3663 3664 3665 3666 3667 3668 3669 3670 3671 3672 3673 3674 3675 3676 3677 3678 3679 3680 3681 3682 3683 3684 3685 3686 3687 3688 3689 3690 3691 3692 3693 3694 3695 3696 3697 3698 3699 3700 3701 3702 3703 3704 3705 3706 3707 3708 3709 3710 3711 3712 3713 3714 3715 3716 3717 3718 3719 3720 3721 3722 3723 3724 3725 3726 3727 3728 3729 3730 3731 3732 3733 3734 3735 3736 4149 5693 6493 6494 6919 6929 6930 6931 6932 6933 6934 6935 6936 6937 6949 6950 6951 6952 6953 6954 6955 6956 6957 6958 6959 6960 6961 6962 6963 6964 6965 6966 6967 6968 6969 6970 6971 6972 6973 6974 6975 6976 6977 6978 6979 6980 6981 6982 6983 6984 6985 6986 6987 6988 6989 6990 6991 6992 6993 6994 6995 6996 6997 6998 6999 7000 7001 7002 7003 7065 7066 7067 7073 7074 7075 7076 7077 7078 7079 7080 7081 7082 7083 7084 7085 7086 7087 7156 7157 7158 7159 7160 7161 7162 7243 7244 7245 7246 7247 7248 7249 7250 7251 7252 7253 7254 7272 7273 7308 7309 7310 7311 7312 7313 7383 7384 7385 7386 7387 7942 7943 7944

8001
}
  controlledprovinces    = {
1372 1371 1370 1369 1367 1366 1527 1529 1528 1526 1523 1410 1525 1524 1167 1170 1171 1172 1175 1522 1521 1384 1383 1520 1416 1415 1414 1413 1412 1411 1417 1558 1557 1423 1556 1550 1549 1547 1546 1559 1561 1560 1562 1538 1545 1544 1548 1543 1540 1539 1536 1535 1533 1534 1156 1155 1154 1565 1564 1571 1597 1598 1555 1552 1594 1596 1573 1593 1587 1424 1586 1585 1584 1583 1581 1576 1575 1574 1572 1566 1567 1570 1577 1578 1580 1582 1579 1569 1568 1150 1151 1152 1153 1773 1772 1771 154 1840 1841 165 153 151 152 150 135 134 133 1838 1847 1857 1849 1850 1848 1845 1844 1846 1843 255 256 257 270 1842 1837 271 164 1833 1834 1836 1839 1827 1828 1829 1832 1831 1830 252 253 254 1777 1778 1776 1775 1780 1781 1782 1783 1774 163 162 161 160 159 157 156 158 155 169 168 167 179 180 166 178 177 170 171 172 173 174 175 176 181 182 183 184 190 191 189 185 186 187 188 192 200 201 212 225 226 227 228 231 232 233 234 251 250 235 236 237 238 239 240 220 272 241 273 274 275 276 277 278 279 280 281 282 283 284 249 258 259 260 248 247 243 262 261 269 268 267 266 265 264 263 1490 1491 1485 1487 1488 1427 1428 1426 1425 1429 94 215 216 217 218 219 221 242 244 245 246 285 286 287 288 289 1149 1368 1422 1489 1856 1858 1907 1541 1542 1551 1874 2470 2240 2488 2368 2614 2615 2847 2848 2849 2850 2851 2868 2869 3341 3342 3343 3345 3346 3347 3348 3349 3399 3400 3401 3402 3403 3404 3405 3406 3407 3408 3409 3410 3411 3412 3413 3414 3415 3416 3417 3418 3419 3420 3421 3422 3423 3424 3425 3426 3427 3428 3429 3431 3432 3433 3434 3435 3436 3437 3438 3439 3440 3441 3442 3443 3444 3445 3446 3447 3448 3449 3450 3451 3452 3453 3454 3455 3456 3457 3458 3459 3460 3461 3462 3463 3464 3465 3466 3467 3468 3469 3470 3471 3472 3473 3474 3475 3476 3477 3478 3479 3480 3486 3481 3482 3483 3484 3485 3487 3488 3489 3490 3491 3492 3493 3494 3495 3496 3497 3499 3500 3501 3502 3503 3505 3506 3507 3508 3510 3511 3512 3513 3514 3515 3516 3517 3518 3519 3520 3521 3522 3523 3527 3528 3529 3530 3532 3533 3534 3535 3536 3537 3538 3539 3540 3541 3542 3543 3544 3545 3546 3547 3548 3549 3550 3551 3553 3554 3555 3556 3557 3559 3560 3561 3562 3563 3564 3565 3566 3567 3568 3569 3570 3571 3572 3573 3574 3575 3576 3577 3578 3579 3580 3581 3582 3583 3584 3585 3586 3587 3588 3589 3590 3591 3592 3593 3596 3597 3598 3599 3600 3601 3602 3603 3604 3605 3606 3607 3608 3609 3610 3611 3612 3614 3615 3616 3617 3618 3619 3620 3621 3622 3623 3624 3625 3626 3627 3628 3629 3630 3631 3632 3633 3634 3635 3636 3637 3638 3639 3640 3641 3642 3643 3644 3645 3646 3647 3648 3649 3650 3651 3652 3653 3654 3655 3656 3657 3658 3659 3660 3661 3662 3663 3664 3665 3666 3667 3668 3669 3670 3671 3672 3673 3674 3675 3676 3677 3678 3679 3680 3681 3682 3683 3684 3685 3686 3687 3688 3689 3690 3691 3692 3693 3694 3695 3696 3697 3698 3699 3700 3701 3702 3703 3704 3705 3706 3707 3708 3709 3710 3711 3712 3713 3714 3715 3716 3717 3718 3719 3720 3721 3722 3723 3724 3725 3726 3727 3728 3729 3730 3731 3732 3733 3734 3735 3736 4149 5693 6493 6494 6919 6929 6930 6931 6932 6933 6934 6935 6936 6937 6949 6950 6951 6952 6953 6954 6955 6956 6957 6958 6959 6960 6961 6962 6963 6964 6965 6966 6967 6968 6969 6970 6971 6972 6973 6974 6975 6976 6977 6978 6979 6980 6981 6982 6983 6984 6985 6986 6987 6988 6989 6990 6991 6992 6993 6994 6995 6996 6997 6998 6999 7000 7001 7002 7003 7065 7066 7067 7073 7074 7075 7076 7077 7078 7079 7080 7081 7082 7083 7084 7085 7086 7087 7156 7157 7158 7159 7160 7161 7162 7243 7244 7245 7246 7247 7248 7249 7250 7251 7252 7253 7254 7272 7273 7308 7309 7310 7311 7312 7313 7383 7384 7385 7386 7387 7942 7943 7944

8001
}
  # Rocket Test and Research Facility
  # Air Doctrines 1936
  # ################
	techapps               = {
		#1931 Infantry Division  
		1010 1020 1030 1040 1050 1060 1070 1080 1090
		#1930 Mountain Division 
		1160 1170 1180 1190 1200 1210 1220 1230 1240
		#SEMI-MOTORIZED CAVALRY 
		13060 13070 13080 1310 1320 1330 1340 1350 1360 1370 1380 1390
		#1935 Motorized Inf
		1396
		# Airborne Inf
		1670
		#Engineers
		1830 1840 1850
		#Interbellum 1930 Supply 
		1910 1920 1930 1940 1950 1960 1970
		#Early Tank 
		7600 7610 2620 2010 2630 2640 2646 2650 2030 2100
		#Basic Armoured Car  
		2860 2870 2880 2020
		#Early Field Artillery 
		2290 2300 2310 2900 2910 2920 2930 2940
		#Early Static Anti-Air Artillery 
		2800 2450 21180
		#Anti-Air Artillery Brigade
		2810 2820 
 
		#Improved Destroyer 
		3010 3020 3030 3040 3050 3060
		#Interwar Light Cruiser 
		3110 3120 3130 3140 3150 3160
		#Improved Heavy Cruiser 
		3210 3220 3230 3240 3250 3260
		#Great War Battlecruiser  
		3310 3320 3330 3340
		#Early Battleship 
		3410 3420 3430 3440 3450 3456 3460
		#Short Range Submarine 
		3610 3620 3630 3640 3650
		#Seaplane Carrier
		12100
		#Torpedo & ASW 18
		3720 3730 3736 3740 3750 3900
		#Troopships
		3810
	
		#Early Fighter  
		4500 4510 4520 4530 4540 4550 4010 4020
		#Early CAS
		4400
		#Early Bomber 
		4600 4610 4620 4630 4120 4130
		#Multirole fighter
		4300 4310 4320 4330 4340
		#ww1 strategic bomber
		4800 4810 4820
		#ww1 navalbomber
		4700 4710
		# Transports
		4290
		#SEAPLANES
		4740 4750 4760 4770
	
		#Modern Agriculture  
		5700 5710
		#Computers & cryptografi
		5310 54010 54020 54030 5316 5326
		#manufactoring
		5810 5820
		#Construction Engineering 
		5800 5080
		#Basic Oil Refining 
		5190
		#Medicine
		5600 5610 5620 
		#Exp. Rocket
		5560

		#Great War Hospital System 
		14000
		# Great War Land Doctrines (central powers)
		6500 6510 6530 6550 6590 6600 6620 6650 6670 6610 6680 6690 6700 6710 6910
		#Land Doctrines
		6570 6300 6900

		# Naval Doctrines 
		# Theory
		8010 8020 8030 8040 8050 8060 8070 8080
		# Amphib
		82300
		# Logistics
		82500
		# Naval Interdiction
		8500 8510 8550 8560 8600 8610
		# Indirect Approach
		81300 81310 81320 81330 81340
		# Naval Supremacy
		8100 8110 8120 8150 8160 8200

		#Air Doctrines - ww2 techs
		27480 27490 27500 27510 27520 27530 27540 27550 27570 27580 27590 27600 9030 9020 27560 27460 27470 9010 9040
 
	}
dormant_leaders        = {  30819 }	
blueprints             = {   } 
  policy =
  { date              = { year = 0 month = january day = 0 }
     democratic        = 1 
     political_left    = 9 
     freedom           = 5 
     free_market       = 1
     professional_army = 5 
     defense_lobby     = 4 
     interventionism   = 5 
  }
inventions = { 3000027 }
   headofstate            = {  type = 9 id = 30001  } # Kalinin 
   headofgovernment       = {  type = 9 id = 30016  } # Molotov 
   foreignminister        = {  type = 9 id = 30003  } 
   armamentminister       = {  type = 9 id = 30004  } 
   ministerofsecurity     = {  type = 9 id = 30005  } 
   ministerofintelligence = {  type = 9 id = 30006  } 
   chiefofstaff           = {  type = 9 id = 30007  } 
   chiefofarmy            = {  type = 9 id = 30008  } 
   chiefofnavy            = {  type = 9 id = 30009  } 
   chiefofair             = {  type = 9 id = 30010  } 
  
landunit = 
   {  id       = {  type = 10848 id =  1 } 
     name     = "Raboche-Krest'yanskaya Krasnaya Armyia" 
     location = 175 #Moscow 
     Division = 
     {  id       = {  type = 10848 id = 2  } 
       name     = "Generalnyi Shtab RKKA" 
       strength = 100
       type     = HQ
	   model    = 2
	   } 
 } 
landunit = { 
	id = { type = 10848 id = 3 }
	name = "Vozdushno Desantnye Voiska" 
	location = 175 # Moscow 	

	division = { 
	id = { type = 10848 id = 4 } 
		name = "1-i Vozdushno-Desantnyi Korpus" 
		strength = 25 
		type = paratrooper
		model = 0
		} 
	}
landunit = { 
	id = { type = 10848 id = 5 }
	name = "Voiska NKVD" 
	location = 175 # Moscow 	

	division = { 
	id = { type = 10848 id = 6 } 
		name = "1-ya Konvoynaya Diviziya NKVD" 
		strength = 100 
		type = garrison 
		model = 4
			} 
	division = { 
	id = { type = 10848 id = 7 } 
		name = "Diviziya o. n. Dzerzhinskogo" 
		strength = 100 
		type = motorized 
		model = 0 
		extra = armored_car
		brigade_model = 3
		} 
	}

   landunit = 
   {  id       = {  type = 10848 id =  8 } 
     name     = "Leningradskyi Voennyi Okrug" 
     location = 175 #Leningrad 
     Division = 
     {  id       = {  type = 10848 id = 9  } 
       name     = "Leningradskyi Voennyi Okrug" 
       strength = 100 
       type     = HQ
	   model    = 2
	   extra    = anti_air
	   brigade_model = 0
	   } 
     Division = 
     {  id       = {  type = 10848 id =  10 } 
       name     = "25-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = heavy_armor
	brigade_model = 1
      } 
      Division = 
     {  id       = {  type = 10848 id = 11  } 
       name     = "7-i Mekhanizirovannyi Korpus" 
       strength = 100 
       type     = light_armor
	   model    = 0
	   extra    = heavy_armor
	   brigade_model    = 1	   
      } 	  
 } 
   landunit = 
   {  id       = {  type = 10848 id =  12 } 
     name     = "1-i Strelkovyi Korpus" 
     location = 175 #Leningrad 
     Division = 
     {  id       = {  type = 10848 id = 13  } 
       name     = "16-ya Ulianovskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	   extra    = artillery
	   brigade_model    = 7		   
      }
     Division = 
     {  id       = {  type = 10848 id = 14  } 
       name     = "18-ya Yaroslavskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	   extra    = artillery
	   brigade_model = 7
      }
     Division = 
     {  id       = {  type = 10848 id = 15  } 
       name     = "20-ya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	   extra    = heavy_armor
	   brigade_model = 1
      }
 } 
   landunit = 
   {  id       = {  type = 10848 id =  16 } 
     name     = "19-i Strelkovyi Korpus" 
     location = 175 #Kingisepp 
     Division = 
     {  id       = {  type = 10848 id = 17  } 
       name     = "4-ya Turkestanskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	   extra    = artillery
	   brigade_model = 6
      }
     Division = 
     {  id       = {  type = 10848 id = 18  } 
       name     = "56-ya Moskovskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
      }
 } 
	landunit = 
   {  id       = {  type = 10848 id = 19  } 
     name     = "5-i Kavaleriiski Korpus" 
     location = 175 # Pskov
      Division = 
     {  id       = {  type = 10848 id = 20  } 
       name     = "3-ya Bessarabskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
      Division = 
     {  id       = {  type = 10848 id = 21  } 
       name     = "14-ya Maykopskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
      Division = 
     {  id       = {  type = 10848 id = 22  } 
       name     = "16-ya Sibirskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
 }
   landunit = 
   {  id       = {  type = 10848 id =  23 } 
     name     = "33-i Strelkovyi Korpus" 
     location = 175 # Kingisepp
     Division = 
     {  id       = {  type = 10848 id = 24  } 
       name     = "11-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      }
     Division = 
     {  id       = {  type = 10848 id = 25  } 
       name     = "158-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      }
 } 
   landunit = 
   {  id       = {  type = 10848 id =  26 } 
     name     = "29-i Strelkovyi Korpus" 
     location = 175 #Leningrad 
     Division = 
     {  id       = {  type = 10848 id = 27  } 
       name     = "54-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      }
     Division = 
     {  id       = {  type = 10848 id = 28  } 
       name     = "153-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      }
 } 

   landunit = 
   {  id       = {  type = 10848 id = 29  } 
     name     = "Severnyi Voennyi Kommissariat" 
     location = 175 # Arkhangelsk
     Division = 
     {  id       = {  type = 10848 id =  30 } 
       name     = "10-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
      Division = 
     {  id       = {  type = 10848 id =  31 } 
       name     = "88-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 

   landunit = 
   {  id       = {  type = 10848 id = 32  } 
     name     = "Uralskyi Voennyi Okrug" 
     location = 175 # Sverdlovsk
     Division = 
     {  id       = {  type = 10848 id =  34 } 
       name     = "65-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	extra = engineer
	brigade_model = 2
      } 
      Division = 
     {  id       = {  type = 10848 id =  35 } 
       name     = "82-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		extra = anti_air
		brigade_model = 0   
      } 
     Division = 
     {  id       = {  type = 10848 id = 36  } 
       name     = "85-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
      Division = 
     {  id       = {  type = 10848 id = 37  } 
       name     = "29-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 8
	extra = light_armor_brigade
	brigade_model = 2
      } 
     Division = 
     {  id       = {  type = 10848 id = 38  } 
       name     = "110-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      }
     Division = 
     {  id       = {  type = 10848 id = 39  } 
       name     = "112-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      }
     Division = 
     {  id       = {  type = 10848 id = 40  } 
       name     = "86-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      }
     Division = 
     {  id       = {  type = 10848 id = 41  } 
       name     = "87-ya Strelkovaya Diviziya" 
       strength = 5 
       type     = infantry 
	   model    = 4
      }
	} 

   landunit = 
   {  id       = {  type = 10848 id = 42  } 
     name     = "Belorusskyi Voennyi Okrug" 
     location = 175 # Minsk
     Division = 
     {  id       = {  type = 10848 id = 43  } 
       name     = "Belorusskyi Voennyi Okrug" 
       strength = 100 
       type     = HQ
	   model    = 2
	extra = anti_air
	brigade_model = 0
	   } 
      Division = 
     {  id       = {  type = 10848 id = 44  } 
       name     = "24-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = armored_car
	brigade_model = 3
      } 
      Division = 
     {  id       = {  type = 10848 id = 45  } 
       name     = "27-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 46  } 
     name     = "4-i Strelkovyi Korpus" 
     location = 175 # Minsk
     Division = 
     {  id       = {  type = 10848 id = 47  } 
       name     = "27-ya Omskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
      } 
      Division = 
     {  id       = {  type = 10848 id = 48  } 
       name     = "2-ya Belorusskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	extra = artillery
	brigade_model = 7
      } 
      Division = 
     {  id       = {  type = 10848 id = 49  } 
       name     = "8-ya Minskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
      } 
	} 	
    landunit = 
   {  id       = {  type = 10848 id = 50  } 
     name     = "5-i Strelkovyi Korpus" 
     location = 175 # Rechytsa
      Division = 
     {  id       = {  type = 10848 id = 51  } 
       name     = "4-ya Smolenskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	extra = artillery
	brigade_model = 7
      } 
     Division = 
     {  id       = {  type = 10848 id = 52  } 
       name     = "37-ya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
      } 
     Division = 
     {  id       = {  type = 10848 id = 53  } 
       name     = "43-ya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	extra = engineer
	brigade_model = 2
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 54  } 
     name     = "11-i Strelkovyi Korpus" 
     location = 175 # Vitebsk
      Division = 
     {  id       = {  type = 10848 id = 55  } 
       name     = "5-ya Vitebskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	extra = artillery
	brigade_model = 7
      } 
     Division = 
     {  id       = {  type = 10848 id = 56  } 
       name     = "29-ya Finskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
     Division = 
     {  id       = {  type = 10848 id = 57  } 
       name     = "64-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
	} 	
    landunit = 
   {  id       = {  type = 10848 id = 58  } 
     name     = "16-i Strelkovyi Korpus" 
     location = 175 # Mogilev
     Division = 
     {  id       = {  type = 10848 id = 59  } 
       name     = "33-ya Belorusskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	extra = artillery
	brigade_model = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 60  } 
       name     = "48-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
     Division = 
     {  id       = {  type = 10848 id = 61  } 
       name     = "81-ya Kaluzhskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
	} 
		landunit = 
   {  id       = {  type = 10848 id = 62  } 
     name     = "3-i Kavaleriiski Korpus" 
     location = 175 # Minsk
      Division = 
     {  id       = {  type = 10848 id = 63  } 
       name     = "7-ya Samarskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
      Division = 
     {  id       = {  type = 10848 id = 64  } 
       name     = "11-ya Orenburgskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
 }		
landunit = 
   {  id       = {  type = 10848 id = 65  } 
     name     = "6-i Kavaleriiski Korpus" 
     location = 175 # Korosten
      Division = 
     {  id       = {  type = 10848 id = 66  } 
       name     = "6-ya Changarskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
 }		
landunit = 
   {  id       = {  type = 10848 id = 67  } 
     name     = "7-i Kavaleriiski Korpus" 
     location = 175 # Slutsk
      Division = 
     {  id       = {  type = 10848 id = 68  } 
       name     = "4-ya Leningradskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
 }
    landunit = 
   {  id       = {  type = 10848 id =  69 } 
     name     = "22-i Strelkovyi Korpus" 
     location = 175 # Minsk
     Division = 
     {  id       = {  type = 10848 id = 70  } 
       name     = "63-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 71  } 
       name     = "67-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 	
    landunit = 
   {  id       = {  type = 10848 id =  72 } 
     name     = "23-i Strelkovyi Korpus" 
     location = 175 # Rechytsa
     Division = 
     {  id       = {  type = 10848 id = 73  } 
       name     = "76-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 74  } 
       name     = "155-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 	
    landunit = 
   {  id       = {  type = 10848 id =  75 } 
     name     = "24-i Strelkovyi Korpus" 
     location = 175 # Vitebsk
     Division = 
     {  id       = {  type = 10848 id = 76  } 
       name     = "150-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 77  } 
       name     = "145-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 	
    landunit = 
   {  id       = {  type = 10848 id =  78 } 
     name     = "28-i Strelkovyi Korpus" 
     location = 175 # Mogilev
     Division = 
     {  id       = {  type = 10848 id = 79  } 
       name     = "62-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 80  } 
       name     = "66-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 81  } 
       name     = "120-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 		
	
   landunit = 
   {  id       = {  type = 10848 id = 82 } 
     name     = "Moskovskyi Voennyi Okrug" 
     location = 175 #Moscow 
     Division = 
     {  id       = {  type = 10848 id =  83 } 
       name     = "Moskovskyi Voennyi Okrug" 
       strength = 100 
       type     = HQ
	   model    = 2
		extra = anti_air
		brigade_model = 0   
	 } 
      Division = 
     {  id       = {  type = 10848 id = 84  } 
       name     = "Osobaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
      Division = 
     {  id       = {  type = 10848 id = 85  } 
       name     = "30-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = engineer
	brigade_model = 2
      } 
      Division = 
     {  id       = {  type = 10848 id = 86  } 
       name     = "5-i Mekhanizirovannyi Korpus" 
       strength = 100 
       type     = light_armor
	   model    = 0
	   extra    = heavy_armor
	   brigade_model    = 1	   
      } 
     Division = 
     {  id       = {  type = 10848 id = 87  } 
       name     = "Moskovskaya Proletarskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
      } 
     Division = 
     {  id       = {  type = 10848 id = 88  } 
       name     = "126-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
  } 
    landunit = 
   {  id       = {  type = 10848 id =  89 } 
     name     = "2-i Territorialnyi Korpus" 
     location = 175 # Vladimir
      Division = 
     {  id       = {  type = 10848 id =  90 } 
       name     = "14-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		} 
      Division = 
     {  id       = {  type = 10848 id =  91 } 
       name     = "49-ya Krasnozamennaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		} 
     Division = 
     {  id       = {  type = 10848 id = 92  } 
       name     = "55-ya Kurskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	   extra    = artillery
	   brigade_model    = 5		   
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id =  93 } 
     name     = "3-i Territorialnyi Korpus" 
     location = 175 # Tula
      Division = 
     {  id       = {  type = 10848 id =  94 } 
       name     = "6-ya Orlovskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		} 
     Division = 
     {  id       = {  type = 10848 id =  95 } 
       name     = "52-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
     Division = 
     {  id       = {  type = 10848 id =  96 } 
       name     = "84-ya Tulskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	   extra    = artillery
	   brigade_model    = 5
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id =  97 } 
     name     = "10-i Territorialnyi Korpus" 
     location = 175 # Orekhovo
     Division = 
     {  id       = {  type = 10848 id =  98 } 
       name     = "17-ya Gorkovskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
     Division = 
     {  id       = {  type = 10848 id = 99  } 
       name     = "19-ya Voronezhskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	   extra    = artillery
	   brigade_model    = 5		   
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 100  } 
     name     = "20-i Strelkovyi Korpus" 
     location = 175 # Vladimir
      Division = 
     {  id       = {  type = 10848 id = 101  } 
       name     = "68-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 102  } 
       name     = "113-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 103  } 
       name     = "142-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 104  } 
     name     = "21-i Strelkovyi Korpus" 
     location = 175 # Tula
      Division = 
     {  id       = {  type = 10848 id = 105  } 
       name     = "77-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 106  } 
       name     = "38-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 107  } 
     name     = "30-i Strelkovyi Korpus" 
     location = 175 # Orekhovo
      Division = 
     {  id       = {  type = 10848 id = 108  } 
       name     = "59-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 109  } 
       name     = "39-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 110  } 
     name     = "40-i Strelkovyi Korpus" 
     location = 175 # Orekhovo
     Division = 
     {  id       = {  type = 10848 id = 111  } 
       name     = "60-ya Strelkovaya Diviziya" 
       strength = 5
       type     = infantry 
	   model    = 4
      } 
      Division = 
     {  id       = {  type = 10848 id = 112  } 
       name     = "42-ya Strelkovaya Diviziya" 
       strength = 5
       type     = infantry 
	   model    = 4
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 113  } 
     name     = "41-i Strelkovyi Korpus" 
     location = 175 # Vladimir
     Division = 
     {  id       = {  type = 10848 id = 114  } 
       name     = "127-ya Strelkovaya Diviziya" 
       strength = 5
       type     = infantry 
	   model    = 4
      } 
	} 

   landunit = 
   {  id       = {  type = 10848 id = 115 } 
     name     = "Privoljsyi Voennyi Okrug" 
     location = 175 # Kazan
      Division = 
     {  id       = {  type = 10848 id = 117  } 
       name     = "125-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 118  } 
       name     = "128-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 119  } 
       name     = "159-ya Strelkovaya Diviziya" 
       strength = 5
       type     = infantry 
	   model    = 4
      } 
      Division = 
     {  id       = {  type = 10848 id = 120  } 
       name     = "79-ya Strelkovaya Diviziya" 
       strength = 5
       type     = infantry 
	   model    = 4
      } 
  }
    landunit = 
   {  id       = {  type = 10848 id = 121  } 
     name     = "12-i Territorialnyi Korpus" 
     location = 175 # Kazan
     Division = 
     {  id       = {  type = 10848 id = 122  } 
       name     = "1-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	   extra    = artillery
	   brigade_model    = 5		   
      } 
      Division = 
     {  id       = {  type = 10848 id = 123  } 
       name     = "31-ya Stalingradskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		extra = anti_air
		brigade_model = 0   
      } 
     Division = 
     {  id       = {  type = 10848 id = 124  } 
       name     = "53-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		}
     Division = 
     {  id       = {  type = 10848 id = 125  } 
       name     = "61-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		}
     Division = 
     {  id       = {  type = 10848 id = 126  } 
       name     = "70-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		}
	} 
    landunit = 
   {  id       = {  type = 10848 id = 127  } 
     name     = "34-i Strelkovyi Korpus" 
     location = 175 # Kazan
     Division = 
     {  id       = {  type = 10848 id = 128  } 
       name     = "111-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 129  } 
       name     = "97-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 130  } 
     name     = "26-i Strelkovyi Korpus" 
     location = 175 # Kazan
     Division = 
     {  id       = {  type = 10848 id = 131  } 
       name     = "129-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 132  } 
       name     = "102-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 133  } 
     name     = "42-i Strelkovyi Korpus" 
     location = 175 # Kazan
     Division = 
     {  id       = {  type = 10848 id = 134  } 
       name     = "108-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 4
      } 
	} 

   landunit = 
   {  id       = {  type = 10848 id = 135 } 
     name     = "Kievskyi Voennyi Okrug" 
     location = 175 # Kiev 
     Division = 
     {  id       = {  type = 10848 id =  136 } 
       name     = "Kievskyi Voennyi Okrug" 
       strength = 100 
       type     = HQ
	   model    = 2
	extra = anti_air
	brigade_model = 0
	 } 
      Division = 
     {  id       = {  type = 10848 id = 137  } 
       name     = "23-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = armored_car
	brigade_model = 3
      } 
      Division = 
     {  id       = {  type = 10848 id = 138  } 
       name     = "26-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
      Division = 
     {  id       = {  type = 10848 id = 139  } 
       name     = "28-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = engineer
	brigade_model = 2
      } 
      Division = 
     {  id       = {  type = 10848 id = 140  } 
       name     = "45-i Mekhanizirovannyi Korpus" 
       strength = 100 
       type     = light_armor
	   model    = 0
	   extra    = heavy_armor
	   brigade_model    = 1	   
      } 
  } 
    landunit = 
   {  id       = {  type = 10848 id = 141  } 
     name     = "6-i Strelkovyi Korpus" 
     location = 175 # Kiev
     Division = 
     {  id       = {  type = 10848 id = 142  } 
       name     = "2-ya Kavkazskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
      } 
     Division = 
     {  id       = {  type = 10848 id = 143  } 
       name     = "24-ya Zheleznaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	   extra    = artillery
	   brigade_model    = 7		   
      } 
      Division = 
     {  id       = {  type = 10848 id = 144  } 
       name     = "46-ya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 145  } 
     name     = "8-i Strelkovyi Korpus" 
     location = 175 # Vinnitsa
     Division = 
     {  id       = {  type = 10848 id = 146  } 
       name     = "44-ya Kievskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	   extra    = artillery
	   brigade_model    = 7		   
      } 
      Division = 
     {  id       = {  type = 10848 id = 147  } 
       name     = "51-ya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
      } 
      Division = 
     {  id       = {  type = 10848 id = 148  } 
       name     = "95-ya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 149  } 
     name     = "15-i Strelkovyi Korpus" 
     location = 175 # Proskurov
     Division = 
     {  id       = {  type = 10848 id = 150  } 
       name     = "2-ya Turkestanskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		}
      Division = 
     {  id       = {  type = 10848 id = 151  } 
       name     = "99-ya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	   extra    = heavy_armor
	   brigade_model    = 1
      } 
     Division = 
     {  id       = {  type = 10848 id = 152  } 
       name     = "100-ya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	   extra    = artillery
	   brigade_model    = 6		   
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 153  } 
     name     = "17-i Strelkovyi Korpus" 
     location = 175 # Tiraspol
     Division = 
     {  id       = {  type = 10848 id = 154  } 
       name     = "7-ya Chernigovskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		}
     Division = 
     {  id       = {  type = 10848 id = 155  } 
       name     = "15-ya Sivashskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		}
      Division = 
     {  id       = {  type = 10848 id = 156  } 
       name     = "96-ya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	   extra    = artillery
	   brigade_model    = 6		
      } 
     Division = 
     {  id       = {  type = 10848 id = 157  } 
       name     = "58-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
		}
    } 
   landunit = 
   {  id       = {  type = 10848 id = 158  } 
     name     = "1-i Kavaleriiski Korpus" 
     location = 175 # Vinnitsa
     Division = 
     {  id       = {  type = 10848 id = 159  } 
       name     = "1-ya Lenina Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
     Division = 
     {  id       = {  type = 10848 id = 160  } 
       name     = "2-ya Krasnogo Znameni Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
  }
   landunit = 
   {  id       = {  type = 10848 id = 161  } 
     name     = "2-i Kavaleriiski Korpus" 
     location = 175 # Zhitomir
     Division = 
     {  id       = {  type = 10848 id = 162  } 
       name     = "5-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
     Division = 
     {  id       = {  type = 10848 id = 163  } 
       name     = "9-ya Krimskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = light_armor_brigade
	brigade_model = 3
      } 
  }
    landunit = 
   {  id       = {  type = 10848 id = 164  } 
     name     = "35-i Strelkovyi Korpus" 
     location = 175 # Kiev
     Division = 
     {  id       = {  type = 10848 id = 165  } 
       name     = "159-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 166  } 
     name     = "36-i Strelkovyi Korpus" 
     location = 175 # Vinnitsa
      Division = 
     {  id       = {  type = 10848 id = 167  } 
       name     = "160-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 168  } 
       name     = "161-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 169  } 
     name     = "27-i Strelkovyi Korpus" 
     location = 175 # Proskurov
      Division = 
     {  id       = {  type = 10848 id = 170  } 
       name     = "89-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 171  } 
       name     = "101-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 172  } 
       name     = "130-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 173  } 
     name     = "37-i Strelkovyi Korpus" 
     location = 175 # Tiraspol
     Division = 
     {  id       = {  type = 10848 id = 174  } 
       name     = "131-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 175  } 
       name     = "140-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 176  } 
       name     = "152-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 177  } 
       name     = "47-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 

   landunit = 
   {  id       = {  type = 10848 id = 178 } 
     name     = "Kharkovskyi Voennyi Okrug" 
     location = 175 #Kharkov 
      Division = 
     {  id       = {  type = 10848 id = 180  } 
       name     = "75-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	   extra    = engineer
	   brigade_model    = 2	
      } 
      Division = 
     {  id       = {  type = 10848 id = 181  } 
       name     = "151-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
  }
    landunit = 
   {  id       = {  type = 10848 id = 182  } 
     name     = "7-i Territorialnyi Korpus" 
     location = 175 # Zaporozhie
     Division = 
     {  id       = {  type = 10848 id = 183  } 
       name     = "3-ya Krimskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = infantry 
	   model    = 7
	extra = anti_air
	brigade_model = 0
      } 
      Division = 
     {  id       = {  type = 10848 id = 184  } 
       name     = "25-ya Chapaeva Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	extra = artillery
	brigade_model = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 185  } 
       name     = "41-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 186  } 
     name     = "14-i Territorialnyi Korpus" 
     location = 175 # Kharkov
      Division = 
     {  id       = {  type = 10848 id = 187  } 
       name     = "30-ya Irkutskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
      Division = 
     {  id       = {  type = 10848 id = 188  } 
       name     = "80-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
      Division = 
     {  id       = {  type = 10848 id = 189  } 
       name     = "23-ya Kharkovskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	extra = artillery
	brigade_model = 5
      } 
	} 
    landunit = 
   {  id       = {  type = 10848 id = 190  } 
     name     = "25-i Strelkovyi Korpus" 
     location = 175 # Kharkov
     Division = 
     {  id       = {  type = 10848 id = 191  } 
       name     = "72-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 192  } 
       name     = "132-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 193  } 
       name     = "83-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 194  } 
       name     = "141-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 195  } 
       name     = "69-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 196  } 
       name     = "156-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 197  } 
       name     = "134-ya Strelkovaya Diviziya" 
       strength = 5
       type     = infantry 
	   model    = 4
      } 
      Division = 
     {  id       = {  type = 10848 id = 198  } 
       name     = "139-ya Strelkovaya Diviziya" 
       strength = 5
       type     = infantry 
	   model    = 4
      } 
	} 

   landunit = 
   {  id       = {  type = 10848 id = 199 } 
     name     = "Severokavkazskyi Voennyi Okrug" 
     location =  175 # Rostov
      Division = 
     {  id       = {  type = 10848 id =  201 } 
       name     = "10-ya Severokavkazskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
	extra = engineer
	brigade_model = 2
      } 
        Division = 
     {  id       = {  type = 10848 id = 202  } 
       name     = "28-ya Gorskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = bergsjaeger
	   model    = 8
	extra = anti_air
	brigade_model = 0
      } 
	  Division = 
     {  id       = {  type = 10848 id = 203  } 
       name     = "12-ya Kubanskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 9
      } 	 
    }
 landunit = 
   {  id       = {  type = 10848 id = 204  } 
     name     = "9-i Territorialnyi Korpus" 
     location =  175 # Krasnodar
     Division = 
     {  id       = {  type = 10848 id = 205  } 
       name     = "9-ya Krasnodarskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	extra = artillery
	brigade_model = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 206  } 
       name     = "13-ya Dagestanskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	extra = cavalry_brigade
	brigade_model = 6
      } 
     Division = 
     {  id       = {  type = 10848 id = 207  } 
       name     = "22-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
     Division = 
     {  id       = {  type = 10848 id = 208  } 
       name     = "74-ya Tamanskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
      } 
	}
    landunit = 
   {  id       = {  type = 10848 id = 209  } 
     name     = "38-i Strelkovyi Korpus" 
     location = 175
     Division = 
     {  id       = {  type = 10848 id = 210  } 
       name     = "103-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
      Division = 
     {  id       = {  type = 10848 id = 211  } 
       name     = "118-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 212  } 
       name     = "119-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
     Division = 
     {  id       = {  type = 10848 id = 213  } 
       name     = "157-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
      } 
	} 

   landunit = 
   {  id       = {  type = 10848 id = 214 } 
     name     = "Zakavkazskyi Voennyi Okrug" 
     location =  175 # Tbilisi
        Division = 
     {  id       = {  type = 10848 id = 217  } 
       name     = "1-ya Gorskaya Kavkazskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = bergsjaeger
	   model    = 8
	extra = engineer
	brigade_model = 2
      } 
        Division = 
     {  id       = {  type = 10848 id = 218  } 
       name     = "3-ya Gorskaya Kavkazskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = bergsjaeger
	   model    = 8
	extra = anti_air
	brigade_model = 0
      } 
        Division = 
     {  id       = {  type = 10848 id = 219  } 
       name     = "1-ya Gorskaya Gruzinskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = bergsjaeger
	   model    = 7
      } 
        Division = 
     {  id       = {  type = 10848 id = 220  } 
       name     = "Gorskaya Azerbaidzhanskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = bergsjaeger
	   model    = 7
      } 
        Division = 
     {  id       = {  type = 10848 id = 221  } 
       name     = "Gorskaya Armianskaya Strelkovaya Diviziya" 
       strength = 40 
       type     = bergsjaeger
	   model    = 7
      } 
        Division = 
     {  id       = {  type = 10848 id = 222  } 
       name     = "2-ya Gruzinskaya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry
	   model    = 6
      }  
    }

   landunit = 
   {  id       = {  type = 10848 id = 223 } 
     name     = "Sredneaziatskyi Voennyi Okrug" 
     location =  175 
     Division = 
     {  id       = {  type = 10848 id = 225  } 
       name     = "1-ya Gorskaya Turkestanskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = bergsjaeger
	   model    = 8
	extra = engineer
	brigade_model = 2
      }	 
     Division = 
     {  id       = {  type = 10848 id = 226  } 
       name     = "3-ya Gorskaya Turkestanskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = bergsjaeger
	   model    = 8
      }	 
  Division = #SAVO
     {  id       = {  type = 10848 id = 227  } 
       name     = "18-ya Turkmenskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 8
     } 
  Division = #SAVO
     {  id       = {  type = 10848 id = 228  } 
       name     = "19-ya Turkmenskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 8
     } 
  Division = #SAVO
     {  id       = {  type = 10848 id = 229  } 
       name     = "21-ya Turkmenskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 8
     } 
  Division = #SAVO
     {  id       = {  type = 10848 id = 230  } 
       name     = "20-ya Tadzhikskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 8
     } 
 }

 landunit = 
   {  id       = {  type = 10848 id = 231  } 
     name     = "Sibirskyi Voennyi Okrug" 
     location =  175 #  Novosibirsk
     Division = 
     {  id       = {  type = 10848 id = 233  } 
       name     = "71-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
	   extra    = engineer 
	   brigade_model    = 2
     } 
     Division = 
     {  id       = {  type = 10848 id = 234  } 
       name     = "73-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
     } 
     Division = 
     {  id       = {  type = 10848 id = 235  } 
       name     = "78-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
     } 
     Division = 
     {  id       = {  type = 10848 id = 236  } 
       name     = "94-ya Strelkovaya Diviziya" 
       strength = 30 
       type     = infantry 
	   model    = 6
     } 
     Division = 
     {  id       = {  type = 10848 id = 237  } 
       name     = "133-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
     } 
     Division = 
     {  id       = {  type = 10848 id = 238  } 
       name     = "109-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
     } 
     Division = 
     {  id       = {  type = 10848 id = 239  } 
       name     = "107-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
     } 
     Division = 
     {  id       = {  type = 10848 id = 240  } 
       name     = "91-ya Strelkovaya Diviziya" 
       strength = 10 
       type     = infantry 
	   model    = 5
     } 
    }

 landunit = 
   {  id       = {  type = 10848 id = 241  } 
     name     = "Zabaikalskyi Voennyi Okrug" 
     location =  175 #  Chita
     Division = 
     {  id       = {  type = 10848 id = 243 } 
       name     = "36-ya Strelkovaya Divizija" 
       strength = 80 
       type     = infantry 
	   model    = 8
	extra = cavalry_brigade
	brigade_model = 6
     } 
     Division = 
     {  id       = {  type = 10848 id = 244 } 
       name     = "57-ya Strelkovaya Divizija" 
       strength = 80 
       type     = infantry 
	   model    = 8
	extra = anti_air
	brigade_model = 0
     } 
     Division = 
     {  id       = {  type = 10848 id = 245 } 
       name     = "93-ya Strelkovaya Divizija" 
       strength = 30 
       type     = infantry 
	   model    = 6
     } 
      Division = # ZabVO
     {  id       = {  type = 10848 id = 246  } 
       name     = "15-ya Kubanskaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 8
      } 
      Division = # ZabVO
     {  id       = {  type = 10848 id = 247  } 
       name     = "17-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 8
      } 
      Division = # ZabVO
     {  id       = {  type = 10848 id = 248  } 
       name     = "22-ya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 8
      } 
       Division = 
     {  id       = {  type = 10848 id =  249 } 
       name     = "11-i Mekhanizirovannyi Korpus" 
       strength = 100 
       type     = light_armor
	   model    = 0
	extra = engineer
	brigade_model = 2
      } 
    }


    landunit = 
   {  id       = {  type = 10848 id = 250 } 
     name     = "Osobaya Krasnozamennaya Dalnevostochnaya Armyia" 
     location =  175 #Khabarovsk
     Division = 
     {  id       = {  type = 10848 id = 251  } 
       name     = "Dalnevostochnyi Voennyi Okrug" 
       strength = 100 
       type     = HQ
	   model    = 2
	   extra    = anti_air
	   brigade_model    = 0	
     } 
     Division = 
     {  id       = {  type = 10848 id = 252  } 
       name     = "12-ya 'SibRevKoma' Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
 	   extra    = artillery
	   brigade_model = 7
	  } 
     Division = 
     {  id       = {  type = 10848 id = 253  } 
       name     = "21-ya Permskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
 	   extra    = engineer
	   brigade_model = 2
	  } 
     Division = 
     {  id       = {  type = 10848 id = 254  } 
       name     = "34-ya Srednevolzhskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	  } 
     Division = 
     {  id       = {  type = 10848 id = 255  } 
       name     = "35-ya Sibirskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	  } 
     Division = 
     {  id       = {  type = 10848 id = 256  } 
       name     = "40-ya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	  } 
      Division = 
     {  id       = {  type = 10848 id = 257  } 
       name     = "8-ya Dalnevostochnaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 8
	extra = light_armor_brigade
	brigade_model = 3
      } 
 }
    landunit = 
	{  id       = {  type = 10848 id = 258  } 
     name     = "18-i Strelkovyi Korpus" 
     location = 175 # Blagoveschensk
      Division = 
     {  id       = {  type = 10848 id = 259  } 
       name     = "1-ya Tikhookeanskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
 	   extra    = artillery
	   brigade_model = 7
	  } 
     Division = 
     {  id       = {  type = 10848 id = 260  } 
       name     = "26-ya Zlatoustovskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	  } 
     Division = 
     {  id       = {  type = 10848 id = 261  } 
       name     = "32-ya Saratovskaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	  } 
	} 	
    landunit = 
    {  id       = {  type = 10848 id = 262  } 
     name     = "Osobyi Kolkhoznyi Korpus" 
     location = 175 # Vladivostok
      Division = 
     {  id       = {  type = 10848 id = 263  } 
       name     = "1-ya Kolkhoznaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
 	   extra    = artillery
	   brigade_model = 7
	  } 
     Division = 
     {  id       = {  type = 10848 id = 264  } 
       name     = "2-ya Kolkhoznaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	  } 
     Division = 
     {  id       = {  type = 10848 id = 265  } 
       name     = "3-ya Kolkhoznaya Strelkovaya Diviziya" 
       strength = 80 
       type     = infantry 
	   model    = 8
	  } 
      Division = 
     {  id       = {  type = 10848 id = 266  } 
       name     = "Kolkhoznaya Kavaleriiskaya Diviziya" 
       strength = 100 
       type     = cavalry
	   model    = 8
      } 
	} 	


	
# Air OOB
#MVO
airunit = { 
	id = { type = 10848 id = 7000 } 
	name = "1 AviaKorpus" 
	location = 175 # Moscow 
	base = 175 # Moscow 

	division = { 
	id = { type = 10848 id = 7001 } 
		name = "403.IABR" 
		strength = 80 
		type = interceptor 
		model = 5 
			} 
	division = { 
	id = { type = 10848 id = 7002 } 
		name = "23.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			}
	}
airunit = { 
	id = { type = 10848 id = 7003 } 
	name = "11 TBABR MVO" 
	location = 175 # Voronezh 
	base = 175 # Voronezh 
 
	division = { 
	id = { type = 10848 id = 7004 } 
		name = "11.TBABR" 
		strength = 50 
		type = strategic_bomber 
		model = 2 
			}
	}

#LVO
airunit = { 
	id = { type = 10848 id = 7005 } 
	name = "4 AviaKorpus" 
	location = 175 # Leningrad 
	base = 175 # Leningrad 
	division = { 
	id = { type = 10848 id = 7006 } 
		name = "1.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			}
	division = { 
	id = { type = 10848 id = 7007 } 
		name = "2.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			}
	}
airunit = { 
	id = { type = 10848 id = 7008 } 
	name = "LVO" 
	location = 175 # Leningrad 
	base = 175 # Leningrad 

	division = { 
	id = { type = 10848 id = 7009 } 
		name = "53.LBABR" 
		strength = 70 
		type = multi_role 
		model = 3 
			} 
	division = { 
	id = { type = 10848 id = 7010 } 
		name = "100.LSHABR" 
		strength = 70 
		type = CAS 
		model = 0 
			}
	}	
airunit = { 
	id = { type = 10848 id = 7011 } 
	name = "3 ABRON LVO" 
	location = 175 # Leningrad 
	base = 175 # Leningrad 

	division = { 
	id = { type = 10848 id = 7012 } 
		name = "3.ABRON" 
		strength = 70 
		type = transport_plane 
		model = 1 
			} 
	}	
airunit = { 
	id = { type = 10848 id = 7013 } 
	name = "200 IABR LVO" 
	location = 175 # Pskov 
	base = 175 # Pskov 

	division = { 
	id = { type = 10848 id = 7014 } 
		name = "3.IABR" 
		strength = 80 
		type = interceptor 
		model = 5 
			} 
	}
	
#BVO
airunit = { 
	id = { type = 10848 id = 7015 } 
	name = "6 AviaKorpus" 
	location = 175 # Bryansk 
	base = 175 # Bryansk 
	division = { 
	id = { type = 10848 id = 7016 } 
		name = "5.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			}
	division = { 
	id = { type = 10848 id = 7017 } 
		name = "9.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			}
	division = { 
	id = { type = 10848 id = 7018 } 
		name = "402.IABR" 
		strength = 80 
		type = interceptor 
		model = 5 
			} 
		}
airunit = { 
	id = { type = 10848 id = 7019 } 
	name = "40 LBABR BVO" 
	location = 175 #  Vitebsk
	base = 175 # Vitebsk	
	division = { 
	id = { type = 10848 id = 7020 } 
		name = "40.LBABR" 
		strength = 70 
		type = multi_role 
		model = 3  
			}
		}	
airunit = { 
	id = { type = 10848 id = 7021 } 
	name = "49 TBABR BVO" 
	location = 175 #  Vitebsk
	base = 175 # Vitebsk	
	division = { 
	id = { type = 10848 id = 7022 } 
		name = "49.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			extra = escort
			brigade_model = 0
			}
		}		
airunit = { 
	id = { type = 10848 id = 7023 } 
	name = "132 IABR BVO" 
	location = 175 # Mogilyev 
	base = 175 #  Mogilyev
	division = { 
	id = { type = 10848 id = 7024 } 
		name = "132. IABR" 
		strength = 80 
		type = interceptor 
		model = 5 
			} 
		}		
airunit = { 
	id = { type = 10848 id = 7025 } 
	name = "252 LSHABR BVO" 
	location = 175 # Mogilyev 
	base = 175 #  Mogilyev
	division = { 
	id = { type = 10848 id = 7026 } 
		name = "252.LSHABR" 
		strength = 70 
		type = CAS 
		model = 0 
			} 
		}		
airunit = { 
	id = { type = 10848 id = 7027 } 
	name = "116 TBABR BVO" 
	location = 175 # Smolensk 
	base = 175 # Smolensk	
	division = { 
	id = { type = 10848 id = 7028 } 
		name = "116.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			extra = escort
			brigade_model = 0
			}
		}		
airunit = { 
	id = { type = 10848 id = 7029 } 
	name = "47 ABRON BVO" 
	location = 175 # Smolensk 
	base = 175 # Smolensk	 
	division = { 
	id = { type = 10848 id = 7030 } 
		name = "47.ABRON" 
		strength = 70 
		type = transport_plane 
		model = 1 
			}
		}
airunit = { 
	id = { type = 10848 id = 7031 } 
	name = "93 TBABR BVO" 
	location = 175 # Torzhok 
	base = 175 # Torzhok	
	division = { 
	id = { type = 10848 id = 7032 } 
		name = "93.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			extra = escort
			brigade_model = 0
			}
		}
#KVO
airunit = { 
	id = { type = 10848 id = 7033 } 
	name = "13 ABRON KVO" 
	location = 175 # Kiev
	base = 175 # Kiev
	division = { 
	id = { type = 10848 id = 7034 } 
		name = "13.ABRON" 
		strength = 70 
		type = transport_plane 
		model = 0 
			}
		}
airunit = { 
	id = { type = 10848 id = 7035 } 
	name = "5 IABR KVO" 
	location = 175 # Kiev
	base = 175 # Kiev
	division = { 
	id = { type = 10848 id = 7036 } 
		name = "5.IABR" 
		strength = 80 
		type = interceptor 
		model = 5 
			} 
		}
airunit = { 
	id = { type = 10848 id = 7037 } 
	name = "404 IABR KVO" 
	location = 175 # Zhitomir
	base = 175 # Zhitomir
	division = { 
	id = { type = 10848 id = 7038 } 
		name = "404.IABR" 
		strength = 80 
		type = interceptor 
		model = 5 
			} 
		}
airunit = { 
	id = { type = 10848 id = 7039 } 
	name = "256 LSHABR KVO" 
	location = 175 # Kiev
	base = 175 # Kiev 
	division = { 
	id = { type = 10848 id = 7040 } 
		name = "256.LSHABR" 
		strength = 70 
		type = CAS 
		model = 0 
			} 
		}	
airunit = { 
	id = { type = 10848 id = 7041 } 
	name = "10 AviaKorpus" 
	location = 175 #  Kirovograd
	base = 175 # Kirovograd	
	division = { 
	id = { type = 10848 id = 7042 } 
		name = "15.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			}
		}
airunit = { 
	id = { type = 10848 id = 7043 } 
	name = "18 TBABR KVO" 
	location = 175 # Zaporozhye 
	base = 175 # Zaporozhye 
 
	division = { 
	id = { type = 10848 id = 7044 } 
		name = "18.TBABR" 
		strength = 50 
		type = strategic_bomber 
		model = 2 
			}
		}

#KhVO
airunit = { 
	id = { type = 10848 id = 7045 } 
	name = "43 TBABR KhVO" 
	location = 175 # Kharkov 
	base = 175 # Kharkov	
	division = { 
	id = { type = 10848 id = 7046 } 
		name = "43.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			extra = escort
			brigade_model = 0
			}
		}
airunit = { 
	id = { type = 10848 id = 7047 } 
	name = "16 TBABR KhVO" 
	location = 175 # Kharkov 
	base = 175 # Kharkov	
	division = { 
	id = { type = 10848 id = 7048 } 
		name = "16.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			}
		}

#ZabVO
airunit = { 
	id = { type = 10848 id = 7049 } 
	name = "5 AviaKorpus" 
	location = 175 #  Chita
	base = 175 # Chita	
	division = { 
	id = { type = 10848 id = 7050 } 
		name = "29.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			}
	division = { 
	id = { type = 10848 id = 7051 } 
		name = "32.LSHABR" 
		strength = 70 
		type = CAS 
		model = 0 
			} 
		}

#DVO
airunit = { 
	id = { type = 10848 id = 7052 } 
	name = "26 TBABR DVO" 
	location = 175 #  Khabarovsk
	base = 175 # Khabarovsk	
	division = { 
	id = { type = 10848 id = 7053 } 
		name = "26.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			}
		}
airunit = { 
	id = { type = 10848 id = 7054 } 
	name = "50 LSHABR DVO" 
	location = 175 #  Khabarovsk
	base = 175 # Khabarovsk
	division = { 
	id = { type = 10848 id = 7055 } 
		name = "50.LSHABR" 
		strength = 70 
		type = CAS 
		model = 0 
			} 
	}

#SibVO
airunit = { 
	id = { type = 10848 id = 7056 } 
	name = "134 LSHABR  SibVO" 
	location = 175 #  Biysk
	base = 175 # Biysk
	division = { 
	id = { type = 10848 id = 7057 } 
		name = "134.LSHABR" 
		strength = 70 
		type = CAS 
		model = 0 
			} 
	}

#SKVO
airunit = { 
	id = { type = 10848 id = 7058 } 
	name = "21 TBABR SKVO" 
	location = 175 # Rostov-na-Donu
	base = 175 # Rostov-na-Donu	
	division = { 
	id = { type = 10848 id = 7059 } 
		name = "21.TBABR" 
		strength = 80 
		type = tactical_bomber 
		model = 3 
			}
		}
airunit = { 
	id = { type = 10848 id = 7080 } 
	name = "55 LBABR SKVO" 
	location = 175 # Rostov-na-Donu
	base = 175 # Rostov-na-Donu	
	division = { 
	id = { type = 10848 id = 7081 } 
		name = "55.LBABR" 
		strength = 70 
		type = multi_role 
		model = 3  
			}
		}

#TOF
airunit = { 
	id = { type = 10848 id = 7082 } 
	name = "20 TBABR TOF" 
	location = 175 #  Khabarovsk
	base = 175 # Khabarovsk
	division = { 
	id = { type = 10848 id = 7083 } 
		name = "20.TBABR" 
		strength = 80 
		type = naval_bomber 
		model = 1 
			}
		}

#CHF
airunit = { 
	id = { type = 10848 id = 7084 } 
	name = "106 TBABR CHF" 
	location = 175 #  Sevastopol
	base = 175 # Sevastopol
	division = { 
	id = { type = 10848 id = 7085 } 
		name = "106.TBABR" 
		strength = 80 
		type = naval_bomber 
		model = 1 
			}
		}
	
	
# Naval OOB
	navalunit = { # Galler L.M.
		id = { type = 10848 id = 5100 } 
		name = "Krasnoznamenny Baltijsky Flot" 
		location = 187 
		base = 187 
		division = { 
			id = { type = 10848 id = 5101 } 
			name = "Marat" 
			type = battleship 
			model = 2 
			extra1 = floatplane
			brigade_model1 = 4
			extra2 = naval_fire_controll_l
			brigade_model2 = 0			
			} 
		division = { 
			id = { type = 10848 id = 5102 } 
			name = "Oktyabrskaya Revolutsiya" 
			type = battleship 
			model = 2 
			extra1 = floatplane
			brigade_model1 = 4
			extra2 = naval_fire_controll_l
			brigade_model2 = 0		
			} 
		division = { 
			id = { type = 10848 id = 5103 } 
			name = "1 Brigada Esmintsev" 
			type = destroyer 
			model = 3 
			} 
		division = { 
			id = { type = 10848 id = 5104 } 
			name = "2 Brigada Esmintsev" 
			type = destroyer 
			model = 3 
			} 
		}  	
	navalunit = { 
		id = { type = 10848 id = 5150 } 
		name = "1ya Brigada PL KBF" 
		location = 187 
		base = 187 
		division = { 
			id = { type = 10848 id = 5151 } 
			name = "1. Divizion Podlodok" 
			type = submarine 
			model = 1
			} 
		}
	navalunit = { 
		id = { type = 10848 id = 5160 } 
		name = "2ya Brigada PL KBF" 
		location = 187 
		base = 187 
		division = { 
			id = { type = 10848 id = 5161 } 
			name = "2. Divizion Podlodok" 
			type = submarine 
			model = 3
			} 
		}		
		
	navalunit = { # Kozhanov I.K.
		id = { type = 10848 id = 5200 } 
		name = "Chernomorskiy Flot" 
		location = 253 
		base = 253 
		division = { 
			id = { type = 10848 id = 5201 } 
			name = "Parizhskaya Kommuna" 
			type = battleship 
			model = 2
			} 
		division = { 
			id = { type = 10848 id = 5202 } 
			name = "Krasni Kavkaz" 
			type = heavy_cruiser 
			model = 2 
			extra1 = floatplane
			brigade_model1 = 3
			} 
		division = { 
			id = { type = 10848 id = 5203 } 
			name = "Profintern" 
			type = light_cruiser 
			model = 2 
			} 
		division = { 
			id = { type = 10848 id = 5204 } 
			name = "Komintern" 
			type = light_cruiser 
			model = 0 
			} 
		division = { 
			id = { type = 10848 id = 5205 } 
			name = "Chervonaya Ukraina" 
			type = light_cruiser 
			model = 2 
			} 
		division = { 
			id = { type = 10848 id = 5206 } 
			name = "1. Divizion Esmintsev" 
			type = destroyer 
			model = 2
			} 
		division = { 
			id = { type = 10848 id = 5207 } 
			name = "2. Divizion Esmintsev" 
			type = destroyer 
			model = 2 
			}
		division = { 
			id = { type = 10848 id = 5208 } 
			name = "2. Transportnaya Diviziya" 
			type = transport 
			model = 1 
		} 
	} 
       
	navalunit = { # Dushenov K.I.
		id = { type = 10848 id = 5400 } 
		name = "Severnaya Voennaya Flotiliya" 
		location = 133 
		base = 133 
		division = { 
			id = { type = 10848 id = 5401 } 
			name = "3. Divizion Esmintsev" 
			type = destroyer 
			model = 2
			} 
		division = { 
			id = { type = 10848 id = 5402 } 
			name = "3. Divizion Podlodok" 
			type = submarine 
			model = 1
			} 
		} 	

	navalunit = { # Viktorov M.V.
		id = { type = 10848 id = 5500 } 
		name = "Tikhookeanskiy Flot" 
		location = 1372
		base = 1372 
		division = { 
			id = { type = 10848 id = 5501 } 
			name = "4. Divizion Esmintsev" 
			type = destroyer 
			model = 0
			} 
		division = { 
			id = { type = 10848 id = 5502 } 
			name = "5. Divizion Esmintsev" 
			type = destroyer 
			model = 0
			} 
		division = { 
			id = { type = 10848 id = 5503 } 
			name = "1. Transportnaya Diviziya" 
			type = transport 
			model = 1 
		} 
	} 
	navalunit = { 
		id = { type = 10848 id = 5550 } 
		name = "1ya Brigada PL TOF" 
		location = 187 
		base = 187 
		division = { 
			id = { type = 10848 id = 5551 } 
			name = "4. Divizion Podlodok" 
			type = submarine 
			model = 3
			} 
		} 	
	
	# Starting Build Queue
	division_development = {
		name  = "5. Flotiliya Podlodok" 
		type  = submarine 
		model = 4 
		cost  = 0.1 
		id    = {  type = 10848 id = 8501  } 
		date  = {  year = 1936 month = february day = 1  } 
	} 
	division_development = {
		name  = "6. Flotiliya Podlodok" 
		type  = submarine 
		model = 4 
		cost  = 0.1 
		id    = {  type = 10848 id = 8502  } 
		date  = {  year = 1936 month = march day = 1  } 
	} 
	division_development = {
		name  = "Kirov"
		type  = heavy_cruiser
		model = 5
		new_model = no
		extra1 = floatplane
		brigade_model1 = 3
		cost  = 0.1
		id    = { type = 10848 id = 8503 }
		date  = { year = 1938 month = september day = 23 }
	}
	division_development = {
		name  = "Voroshilov"
		type  = heavy_cruiser
		model = 5
		new_model = no
		extra1 = floatplane
		brigade_model1 = 3
		cost  = 0.1
		id    = { type = 10848 id = 8504 }
		date  = { year = 1940 month = june day = 20 }
	}
	landdivision = { dormant = yes id = { type = 10848 id = 8600 }	name = "Union of Polish Patriots"			type = garrison 	model = 4	locked = yes }
	landdivision = { dormant = yes id = { type = 10848 id = 8601 }	name = "Estonia garrison"					type = garrison 	model = 5	locked = yes }
	landdivision = { dormant = yes id = { type = 10848 id = 8602 }	name = "Latvia garrison"					type = garrison 	model = 5	locked = yes }
	landdivision = { dormant = yes id = { type = 10848 id = 8603 }	name = "Lithuania garrison"					type = garrison 	model = 5	locked = yes }
	
	airdivision  = { dormant = yes id = { type = 10848 id = 8610 }	name = "E. de ch. 1/30 Normandie-Niemen"	type = interceptor	model = 9	strength = 10 experience = 90 }
 }	
