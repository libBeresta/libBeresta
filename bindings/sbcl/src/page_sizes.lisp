;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defcenum PageSizes
  ;; Размер страницы "US Loose Letter" (216.0мм x 279.0мм)
  (:PAGE-SIZE-US-LETTER 0)

  ;; Размер страницы "US Loose Legal" (216.0мм x 356.0мм)
  (:PAGE-SIZE-US-LEGAL 1)

  ;; Размер страницы "US Loose Tabloid" (279.0мм x 432.0мм)
  (:PAGE-SIZE-US-TABLOID 2)

  ;; Размер страницы "US Loose Ledger" (432.0мм x 279.0мм)
  (:PAGE-SIZE-US-LEDGER 3)

  ;; Размер страницы "US Loose Junior Legal" (127.0мм x 203.0мм)
  (:PAGE-SIZE-US-JUNIOR-LEGAL 4)

  ;; Размер страницы "US Loose Half Letter" (140.0мм x 216.0мм)
  (:PAGE-SIZE-US-HALF-LETTER 5)

  ;; Размер страницы "US Loose Government Letter" (203.0мм x 267.0мм)
  (:PAGE-SIZE-US-GOVERNMENT-LETTER 6)

  ;; Размер страницы "US Loose Government Legal" (216.0мм x 330.0мм)
  (:PAGE-SIZE-US-GOVERNMENT-LEGAL 7)

  ;; Размер страницы "US ANSI ANSI A" (216.0мм x 279.0мм)
  (:PAGE-SIZE-US-ANSI-A 8)

  ;; Размер страницы "US ANSI ANSI B" (279.0мм x 432.0мм)
  (:PAGE-SIZE-US-ANSI-B 9)

  ;; Размер страницы "US ANSI ANSI C" (432.0мм x 559.0мм)
  (:PAGE-SIZE-US-ANSI-C 10)

  ;; Размер страницы "US ANSI ANSI D" (559.0мм x 864.0мм)
  (:PAGE-SIZE-US-ANSI-D 11)

  ;; Размер страницы "US ANSI ANSI E" (864.0мм x 1118.0мм)
  (:PAGE-SIZE-US-ANSI-E 12)

  ;; Размер страницы "US Arch Arch A" (229.0мм x 305.0мм)
  (:PAGE-SIZE-US-ARCH-A 13)

  ;; Размер страницы "US Arch Arch B" (305.0мм x 457.0мм)
  (:PAGE-SIZE-US-ARCH-B 14)

  ;; Размер страницы "US Arch Arch C" (457.0мм x 610.0мм)
  (:PAGE-SIZE-US-ARCH-C 15)

  ;; Размер страницы "US Arch Arch D" (610.0мм x 914.0мм)
  (:PAGE-SIZE-US-ARCH-D 16)

  ;; Размер страницы "US Arch Arch E" (914.0мм x 1219.0мм)
  (:PAGE-SIZE-US-ARCH-E 17)

  ;; Размер страницы "US Arch Arch E1" (762.0мм x 1067.0мм)
  (:PAGE-SIZE-US-ARCH-E1 18)

  ;; Размер страницы "US Arch Arch E2" (660.0мм x 965.0мм)
  (:PAGE-SIZE-US-ARCH-E2 19)

  ;; Размер страницы "US Arch Arch E3" (686.0мм x 991.0мм)
  (:PAGE-SIZE-US-ARCH-E3 20)

  ;; Размер страницы "ISO 216 4A0" (1682.0мм x 2378.0мм)
  (:PAGE-SIZE-4A0 21)

  ;; Размер страницы "ISO 216 2A0" (1189.0мм x 1682.0мм)
  (:PAGE-SIZE-2A0 22)

  ;; Размер страницы "ISO 216 A0" (841.0мм x 1189.0мм)
  (:PAGE-SIZE-A0 23)

  ;; Размер страницы "ISO 216 A0+" (914.0мм x 1292.0мм)
  (:PAGE-SIZE-A0-PLUS 24)

  ;; Размер страницы "ISO 216 A1" (594.0мм x 841.0мм)
  (:PAGE-SIZE-A1 25)

  ;; Размер страницы "ISO 216 A1+" (609.0мм x 914.0мм)
  (:PAGE-SIZE-A1-PLUS 26)

  ;; Размер страницы "ISO 216 A2" (420.0мм x 594.0мм)
  (:PAGE-SIZE-A2 27)

  ;; Размер страницы "ISO 216 A3" (297.0мм x 420.0мм)
  (:PAGE-SIZE-A3 28)

  ;; Размер страницы "ISO 216 A3+" (329.0мм x 483.0мм)
  (:PAGE-SIZE-A3-PLUS 29)

  ;; Размер страницы "ISO 216 A4" (210.0мм x 297.0мм)
  (:PAGE-SIZE-A4 30)

  ;; Размер страницы "ISO 216 A5" (148.0мм x 210.0мм)
  (:PAGE-SIZE-A5 31)

  ;; Размер страницы "ISO 216 A6" (105.0мм x 148.0мм)
  (:PAGE-SIZE-A6 32)

  ;; Размер страницы "ISO 216 A7" (74.0мм x 105.0мм)
  (:PAGE-SIZE-A7 33)

  ;; Размер страницы "ISO 216 A8" (52.0мм x 74.0мм)
  (:PAGE-SIZE-A8 34)

  ;; Размер страницы "ISO 216 A9" (37.0мм x 52.0мм)
  (:PAGE-SIZE-A9 35)

  ;; Размер страницы "ISO 216 A10" (26.0мм x 37.0мм)
  (:PAGE-SIZE-A10 36)

  ;; Размер страницы "ISO 216 B0" (1000.0мм x 1414.0мм)
  (:PAGE-SIZE-B0 37)

  ;; Размер страницы "ISO 216 B0+" (1118.0мм x 1580.0мм)
  (:PAGE-SIZE-B0-PLUS 38)

  ;; Размер страницы "ISO 216 B1" (707.0мм x 1000.0мм)
  (:PAGE-SIZE-B1 39)

  ;; Размер страницы "ISO 216 B1+" (720.0мм x 1020.0мм)
  (:PAGE-SIZE-B1-PLUS 40)

  ;; Размер страницы "ISO 216 B2" (500.0мм x 707.0мм)
  (:PAGE-SIZE-B2 41)

  ;; Размер страницы "ISO 216 B2+" (520.0мм x 720.0мм)
  (:PAGE-SIZE-B2-PLUS 42)

  ;; Размер страницы "ISO 216 B3" (353.0мм x 500.0мм)
  (:PAGE-SIZE-B3 43)

  ;; Размер страницы "ISO 216 B4" (250.0мм x 353.0мм)
  (:PAGE-SIZE-B4 44)

  ;; Размер страницы "ISO 216 B5" (176.0мм x 250.0мм)
  (:PAGE-SIZE-B5 45)

  ;; Размер страницы "ISO 216 B6" (125.0мм x 176.0мм)
  (:PAGE-SIZE-B6 46)

  ;; Размер страницы "ISO 216 B7" (88.0мм x 125.0мм)
  (:PAGE-SIZE-B7 47)

  ;; Размер страницы "ISO 216 B8" (62.0мм x 88.0мм)
  (:PAGE-SIZE-B8 48)

  ;; Размер страницы "ISO 216 B9" (44.0мм x 62.0мм)
  (:PAGE-SIZE-B9 49)

  ;; Размер страницы "ISO 216 B10" (31.0мм x 44.0мм)
  (:PAGE-SIZE-B10 50)

  ;; Размер страницы "ISO 216 B11" (22.0мм x 31.0мм)
  (:PAGE-SIZE-B11 51)

  ;; Размер страницы "ISO 216 B12" (15.0мм x 22.0мм)
  (:PAGE-SIZE-B12 52)

  ;; Размер страницы "ISO 216 B13" (11.0мм x 15.0мм)
  (:PAGE-SIZE-B13 53)

  ;; Размер страницы "ISO 216 C0" (917.0мм x 1297.0мм)
  (:PAGE-SIZE-C0 54)

  ;; Размер страницы "ISO 216 C1" (648.0мм x 917.0мм)
  (:PAGE-SIZE-C1 55)

  ;; Размер страницы "ISO 216 C2" (458.0мм x 648.0мм)
  (:PAGE-SIZE-C2 56)

  ;; Размер страницы "ISO 216 C3" (324.0мм x 458.0мм)
  (:PAGE-SIZE-C3 57)

  ;; Размер страницы "ISO 216 C4" (229.0мм x 324.0мм)
  (:PAGE-SIZE-C4 58)

  ;; Размер страницы "ISO 216 C5" (162.0мм x 229.0мм)
  (:PAGE-SIZE-C5 59)

  ;; Размер страницы "ISO 216 C6" (114.0мм x 162.0мм)
  (:PAGE-SIZE-C6 60)

  ;; Размер страницы "ISO 216 C7" (81.0мм x 114.0мм)
  (:PAGE-SIZE-C7 61)

  ;; Размер страницы "ISO 216 C8" (57.0мм x 81.0мм)
  (:PAGE-SIZE-C8 62)

  ;; Размер страницы "ISO 216 C9" (40.0мм x 57.0мм)
  (:PAGE-SIZE-C9 63)

  ;; Размер страницы "ISO 216 C10" (28.0мм x 40.0мм)
  (:PAGE-SIZE-C10 64)

  ;; Размер страницы "Traditional British Dukes" (140.0мм x 178.0мм)
  (:PAGE-SIZE-BRITISH-DUKES 65)

  ;; Размер страницы "Traditional British Foolscap" (203.0мм x 330.0мм)
  (:PAGE-SIZE-BRITISH-FOOLSCAP 66)

  ;; Размер страницы "Traditional British Imperial" (178.0мм x 229.0мм)
  (:PAGE-SIZE-BRITISH-IMPERIAL 67)

  ;; Размер страницы "Traditional British Kings" (165.0мм x 203.0мм)
  (:PAGE-SIZE-BRITISH-KINGS 68)

  ;; Размер страницы "Traditional British Quarto" (203.0мм x 254.0мм)
  (:PAGE-SIZE-BRITISH-QUARTO 69)

  ;; Размер страницы "US Commercial envelopes 6¼" (152.0мм x 89.0мм)
  (:PAGE-SIZE-US-ENVELOPE-6-1-4 70)

  ;; Размер страницы "US Commercial envelopes 6¾" (165.0мм x 92.0мм)
  (:PAGE-SIZE-US-ENVELOPE-6-3-4 71)

  ;; Размер страницы "US Commercial envelopes 7" (172.0мм x 95.0мм)
  (:PAGE-SIZE-US-ENVELOPE-7 72)

  ;; Размер страницы "US Commercial envelopes 7¾ Monarch" (191.0мм x 98.0мм)
  (:PAGE-SIZE-US-ENVELOPE-7-3-4-MONARCH 73)

  ;; Размер страницы "US Commercial envelopes 8⅝ " (219.0мм x 92.0мм)
  (:PAGE-SIZE-US-ENVELOPE8-5-8 74)

  ;; Размер страницы "US Commercial envelopes 9" (225.0мм x 98.0мм)
  (:PAGE-SIZE-US-ENVELOPE-9 75)

  ;; Размер страницы "US Commercial envelopes 10" (241.0мм x 104.0мм)
  (:PAGE-SIZE-US-ENVELOPE-10 76)

  ;; Размер страницы "US Commercial envelopes 11" (264.0мм x 114.0мм)
  (:PAGE-SIZE-US-ENVELOPE-11 77)

  ;; Размер страницы "US Commercial envelopes 12" (279.0мм x 121.0мм)
  (:PAGE-SIZE-US-ENVELOPE-12 78)

  ;; Размер страницы "US Commercial envelopes 14" (292.0мм x 127.0мм)
  (:PAGE-SIZE-US-ENVELOPE-14 79)

  ;; Размер страницы "US Commercial envelopes 16" (305.0мм x 152.0мм)
  (:PAGE-SIZE-US-ENVELOPE-16 80)

  ;; Размер страницы "US Announcement envelopes A1" (92.0мм x 130.0мм)
  (:PAGE-SIZE-US-ENVELOPE-A1 81)

  ;; Размер страницы "US Announcement envelopes A2 Lady Grey" (146.0мм x 111.0мм)
  (:PAGE-SIZE-US-ENVELOPE-A2-LADY-GREY 82)

  ;; Размер страницы "US Announcement envelopes A4" (159.0мм x 108.0мм)
  (:PAGE-SIZE-US-ENVELOPE-A4 83)

  ;; Размер страницы "US Announcement envelopes A6 Thompson&#039;s Standard" (165.0мм x 121.0мм)
  (:PAGE-SIZE-US-ENVELOPE-A6-THOMPSON-S-STANDARD 84)

  ;; Размер страницы "US Announcement envelopes A7 Besselheim" (184.0мм x 133.0мм)
  (:PAGE-SIZE-US-ENVELOPE-A7-BESSELHEIM 85)

  ;; Размер страницы "US Announcement envelopes A8 Carr&#039;s" (206.0мм x 140.0мм)
  (:PAGE-SIZE-US-ENVELOPE-A8-CARR-S 86)

  ;; Размер страницы "US Announcement envelopes A9 Diplomat" (222.0мм x 146.0мм)
  (:PAGE-SIZE-US-ENVELOPE-A9-DIPLOMAT 87)

  ;; Размер страницы "US Announcement envelopes A10 Willow" (241.0мм x 152.0мм)
  (:PAGE-SIZE-US-ENVELOPE-A10-WILLOW 88)

  ;; Размер страницы "US Announcement envelopes A Long" (225.0мм x 98.0мм)
  (:PAGE-SIZE-US-ENVELOPE-A-LONG 89)

  ;; Размер страницы "US Catalog envelopes 1" (229.0мм x 152.0мм)
  (:PAGE-SIZE-US-ENVELOPE-1 90)

  ;; Размер страницы "US Catalog envelopes 1¾" (241.0мм x 152.0мм)
  (:PAGE-SIZE-US-ENVELOPE-1-3-4 91)

  ;; Размер страницы "US Catalog envelopes 3" (254.0мм x 178.0мм)
  (:PAGE-SIZE-US-ENVELOPE-3 92)

  ;; Размер страницы "US Catalog envelopes 6" (267.0мм x 191.0мм)
  (:PAGE-SIZE-US-ENVELOPE-6 93)

  ;; Размер страницы "US Catalog envelopes 8" (286.0мм x 210.0мм)
  (:PAGE-SIZE-US-ENVELOPE-8 94)

  ;; Размер страницы "US Catalog envelopes 9¾" (286.0мм x 222.0мм)
  (:PAGE-SIZE-US-ENVELOPE-9-3-4 95)

  ;; Размер страницы "US Catalog envelopes 10½" (305.0мм x 229.0мм)
  (:PAGE-SIZE-US-ENVELOPE-10-1-2 96)

  ;; Размер страницы "US Catalog envelopes 12½" (318.0мм x 241.0мм)
  (:PAGE-SIZE-US-ENVELOPE-12-1-2 97)

  ;; Размер страницы "US Catalog envelopes 13½" (330.0мм x 254.0мм)
  (:PAGE-SIZE-US-ENVELOPE-13-1-2 98)

  ;; Размер страницы "US Catalog envelopes 14½" (368.0мм x 292.0мм)
  (:PAGE-SIZE-US-ENVELOPE-14-1-2 99)

  ;; Размер страницы "US Catalog envelopes 15" (381.0мм x 254.0мм)
  (:PAGE-SIZE-US-ENVELOPE-15 100)

  ;; Размер страницы "US Catalog envelopes 15½" (394.0мм x 305.0мм)
  (:PAGE-SIZE-US-ENVELOPE-15-1-2 101)

  ;; Размер страницы "ISO 269 DL" (110.0мм x 220.0мм)
  (:PAGE-SIZE-ENVELOPE-DL 102)

  ;; Размер страницы "ISO 269 B4" (250.0мм x 353.0мм)
  (:PAGE-SIZE-ENVELOPE-B4 103)

  ;; Размер страницы "ISO 269 B5" (176.0мм x 250.0мм)
  (:PAGE-SIZE-ENVELOPE-B5 104)

  ;; Размер страницы "ISO 269 B6" (125.0мм x 176.0мм)
  (:PAGE-SIZE-ENVELOPE-B6 105)

  ;; Размер страницы "ISO 269 C3" (324.0мм x 458.0мм)
  (:PAGE-SIZE-ENVELOPE-C3 106)

  ;; Размер страницы "ISO 269 C4" (229.0мм x 324.0мм)
  (:PAGE-SIZE-ENVELOPE-C4 107)

  ;; Размер страницы "ISO 269 C4M" (318.0мм x 229.0мм)
  (:PAGE-SIZE-ENVELOPE-C4M 108)

  ;; Размер страницы "ISO 269 C5" (162.0мм x 229.0мм)
  (:PAGE-SIZE-ENVELOPE-C5 109)

  ;; Размер страницы "ISO 269 C6/C5" (114.0мм x 229.0мм)
  (:PAGE-SIZE-ENVELOPE-C6-C5 110)

  ;; Размер страницы "ISO 269 C6" (114.0мм x 162.0мм)
  (:PAGE-SIZE-ENVELOPE-C6 111)

  ;; Размер страницы "ISO 269 C64M" (318.0мм x 114.0мм)
  (:PAGE-SIZE-ENVELOPE-C64M 112)

  ;; Размер страницы "ISO 269 C7/C6" (81.0мм x 162.0мм)
  (:PAGE-SIZE-ENVELOPE-C7-C6 113)

  ;; Размер страницы "ISO 269 C7" (81.0мм x 114.0мм)
  (:PAGE-SIZE-ENVELOPE-C7 114)

  ;; Размер страницы "ISO 269 CE4" (229.0мм x 310.0мм)
  (:PAGE-SIZE-ENVELOPE-CE4 115)

  ;; Размер страницы "ISO 269 CE64" (114.0мм x 310.0мм)
  (:PAGE-SIZE-ENVELOPE-CE64 116)

  ;; Размер страницы "ISO 269 E4" (220.0мм x 312.0мм)
  (:PAGE-SIZE-ENVELOPE-E4 117)

  ;; Размер страницы "ISO 269 EC45" (220.0мм x 229.0мм)
  (:PAGE-SIZE-ENVELOPE-EC45 118)

  ;; Размер страницы "ISO 269 EC5" (155.0мм x 229.0мм)
  (:PAGE-SIZE-ENVELOPE-EC5 119)

  ;; Размер страницы "ISO 269 E5" (115.0мм x 220.0мм)
  (:PAGE-SIZE-ENVELOPE-E5 120)

  ;; Размер страницы "ISO 269 E56" (155.0мм x 155.0мм)
  (:PAGE-SIZE-ENVELOPE-E56 121)

  ;; Размер страницы "ISO 269 E6" (110.0мм x 155.0мм)
  (:PAGE-SIZE-ENVELOPE-E6 122)

  ;; Размер страницы "ISO 269 E65" (110.0мм x 220.0мм)
  (:PAGE-SIZE-ENVELOPE-E65 123)

  ;; Размер страницы "ISO 269 R7" (120.0мм x 135.0мм)
  (:PAGE-SIZE-ENVELOPE-R7 124)

  ;; Размер страницы "ISO 269 S4" (250.0мм x 330.0мм)
  (:PAGE-SIZE-ENVELOPE-S4 125)

  ;; Размер страницы "ISO 269 S5" (185.0мм x 255.0мм)
  (:PAGE-SIZE-ENVELOPE-S5 126)

  ;; Размер страницы "ISO 269 S65" (110.0мм x 225.0мм)
  (:PAGE-SIZE-ENVELOPE-S65 127)

  ;; Размер страницы "ISO 269 X5" (105.0мм x 216.0мм)
  (:PAGE-SIZE-ENVELOPE-X5 128)

  ;; Размер страницы "ISO 269 EX5" (155.0мм x 216.0мм)
  (:PAGE-SIZE-ENVELOPE-EX5 129)

  ;; Размер страницы "Photography Passport" (35.0мм x 45.0мм)
  (:PAGE-SIZE-PHOTO-PASSPORT 130)

  ;; Размер страницы "Photography 2R" (64.0мм x 89.0мм)
  (:PAGE-SIZE-PHOTO-2R 131)

  ;; Размер страницы "Photography LD" (89.0мм x 119.0мм)
  (:PAGE-SIZE-PHOTO-LD 132)

  ;; Размер страницы "Photography DSC" (89.0мм x 119.0мм)
  (:PAGE-SIZE-PHOTO-DSC 133)

  ;; Размер страницы "Photography 3R" (89.0мм x 127.0мм)
  (:PAGE-SIZE-PHOTO-3R 134)

  ;; Размер страницы "Photography L" (89.0мм x 127.0мм)
  (:PAGE-SIZE-PHOTO-L 135)

  ;; Размер страницы "Photography LW" (89.0мм x 133.0мм)
  (:PAGE-SIZE-PHOTO-LW 136)

  ;; Размер страницы "Photography KGD" (102.0мм x 136.0мм)
  (:PAGE-SIZE-PHOTO-KGD 137)

  ;; Размер страницы "Photography KG" (102.0мм x 152.0мм)
  (:PAGE-SIZE-PHOTO-KG 138)

  ;; Размер страницы "Photography 4R" (102.0мм x 152.0мм)
  (:PAGE-SIZE-PHOTO-4R 139)

  ;; Размер страницы "Photography 2LD" (127.0мм x 169.0мм)
  (:PAGE-SIZE-PHOTO-2LD 140)

  ;; Размер страницы "Photography DSCW" (127.0мм x 169.0мм)
  (:PAGE-SIZE-PHOTO-DSCW 141)

  ;; Размер страницы "Photography 2L" (127.0мм x 178.0мм)
  (:PAGE-SIZE-PHOTO-2L 142)

  ;; Размер страницы "Photography 5R" (127.0мм x 178.0мм)
  (:PAGE-SIZE-PHOTO-5R 143)

  ;; Размер страницы "Photography 2LW" (127.0мм x 190.0мм)
  (:PAGE-SIZE-PHOTO-2LW 144)

  ;; Размер страницы "Photography 6R" (152.0мм x 203.0мм)
  (:PAGE-SIZE-PHOTO-6R 145)

  ;; Размер страницы "Photography 8R" (203.0мм x 254.0мм)
  (:PAGE-SIZE-PHOTO-8R 146)

  ;; Размер страницы "Photography 6P" (203.0мм x 254.0мм)
  (:PAGE-SIZE-PHOTO-6P 147)

  ;; Размер страницы "Photography 6PW" (203.0мм x 305.0мм)
  (:PAGE-SIZE-PHOTO-6PW 148)

  ;; Размер страницы "Photography S8R" (203.0мм x 305.0мм)
  (:PAGE-SIZE-PHOTO-S8R 149)

  ;; Размер страницы "Photography 11R" (279.0мм x 356.0мм)
  (:PAGE-SIZE-PHOTO-11R 150)

  ;; Размер страницы "Photography A3+ Super B" (330.0мм x 483.0мм)
  (:PAGE-SIZE-PHOTO-A3-PLUS 151)

  ;; Размер страницы "Newspaper Berliner" (315.0мм x 470.0мм)
  (:PAGE-SIZE-NEWSPAPER-BERLINER 152)

  ;; Размер страницы "Newspaper Broadsheet" (597.0мм x 749.0мм)
  (:PAGE-SIZE-NEWSPAPER-BROADSHEET 153)

  ;; Размер страницы "Newspaper US Broadsheet" (381.0мм x 578.0мм)
  (:PAGE-SIZE-NEWSPAPER-US-BROADSHEET 154)

  ;; Размер страницы "Newspaper British Broadsheet" (375.0мм x 597.0мм)
  (:PAGE-SIZE-NEWSPAPER-BRITISH-BROADSHEET 155)

  ;; Размер страницы "Newspaper South African Broadsheet" (410.0мм x 578.0мм)
  (:PAGE-SIZE-NEWSPAPER-SOUTH-AFRICAN-BROADSHEET 156)

  ;; Размер страницы "Newspaper Ciner" (350.0мм x 500.0мм)
  (:PAGE-SIZE-NEWSPAPER-CINER 157)

  ;; Размер страницы "Newspaper Compact" (280.0мм x 430.0мм)
  (:PAGE-SIZE-NEWSPAPER-COMPACT 158)

  ;; Размер страницы "Newspaper Nordisch" (400.0мм x 570.0мм)
  (:PAGE-SIZE-NEWSPAPER-NORDISCH 159)

  ;; Размер страницы "Newspaper Rhenish" (350.0мм x 520.0мм)
  (:PAGE-SIZE-NEWSPAPER-RHENISH 160)

  ;; Размер страницы "Newspaper Swiss" (320.0мм x 475.0мм)
  (:PAGE-SIZE-NEWSPAPER-SWISS 161)

  ;; Размер страницы "Newspaper Tabloid" (280.0мм x 430.0мм)
  (:PAGE-SIZE-NEWSPAPER-TABLOID 162)

  ;; Размер страницы "Newspaper Canadian Tabloid" (260.0мм x 368.0мм)
  (:PAGE-SIZE-NEWSPAPER-CANADIAN-TABLOID 163)

  ;; Размер страницы "Newspaper Norwegian Tabloid" (280.0мм x 400.0мм)
  (:PAGE-SIZE-NEWSPAPER-NORWEGIAN-TABLOID 164)

  ;; Размер страницы "Newspaper New York Times" (305.0мм x 559.0мм)
  (:PAGE-SIZE-NEWSPAPER-NEW-YOUR-TIMES 165)

  ;; Размер страницы "Newspaper Wall Street Journal" (305.0мм x 578.0мм)
  (:PAGE-SIZE-NEWSPAPER-WALL-STREET-JOURNAL 166)

  ;; Размер страницы "Book Folio" (304.8мм x 482.6мм)
  (:PAGE-SIZE-BOOK-FOLIO 167)

  ;; Размер страницы "Book Quarto" (241.3мм x 304.8мм)
  (:PAGE-SIZE-BOOK-QUARTO 168)

  ;; Размер страницы "Book Imperial Octavo" (209.6мм x 292.1мм)
  (:PAGE-SIZE-BOOK-IMPERIAL-OCTAVO 169)

  ;; Размер страницы "Book Super Octavo" (177.8мм x 279.4мм)
  (:PAGE-SIZE-BOOK-SUPER-OCTAVO 170)

  ;; Размер страницы "Book Royal Octavo" (165.1мм x 254.0мм)
  (:PAGE-SIZE-BOOK-ROYAL-OCTAVO 171)

  ;; Размер страницы "Book Medium Octavo" (165.1мм x 234.9мм)
  (:PAGE-SIZE-BOOK-MEDIUM-OCTAVO 172)

  ;; Размер страницы "Book Octavo" (152.4мм x 228.6мм)
  (:PAGE-SIZE-BOOK-OCTAVO 173)

  ;; Размер страницы "Book Crown Octavo" (136.5мм x 203.2мм)
  (:PAGE-SIZE-BOOK-CROWN-OCTAVO 174)

  ;; Размер страницы "Book 12mo" (127.0мм x 187.3мм)
  (:PAGE-SIZE-BOOK-12MO 175)

  ;; Размер страницы "Book 16mo" (101.6мм x 171.4мм)
  (:PAGE-SIZE-BOOK-16MO 176)

  ;; Размер страницы "Book 18mo" (101.6мм x 165.1мм)
  (:PAGE-SIZE-BOOK-18MO 177)

  ;; Размер страницы "Book 32mo" (88.9мм x 139.7мм)
  (:PAGE-SIZE-BOOK-32MO 178)

  ;; Размер страницы "Book 48mo" (63.5мм x 101.6мм)
  (:PAGE-SIZE-BOOK-48MO 179)

  ;; Размер страницы "Book 64mo" (50.8мм x 76.2мм)
  (:PAGE-SIZE-BOOK-64MO 180)

  ;; Размер страницы "Book A Format" (110.0мм x 178.0мм)
  (:PAGE-SIZE-BOOK-A-FORMAT 181)

  ;; Размер страницы "Book B Format" (129.0мм x 198.0мм)
  (:PAGE-SIZE-BOOK-B-FORMAT 182)

  ;; Размер страницы "Book C Format" (135.0мм x 216.0мм)
  (:PAGE-SIZE-BOOK-C-FORMAT 183)

  ;; Размер страницы "Business Card ISO 216" (74.0мм x 52.0мм)
  (:PAGE-SIZE-BUSINESS-CARD-ISO-216 184)

  ;; Размер страницы "Business Card US/Canada" (88.9мм x 50.8мм)
  (:PAGE-SIZE-BUSINESS-CARD-US-CANADA 185)

  ;; Размер страницы "Business Card European" (85.0мм x 55.0мм)
  (:PAGE-SIZE-BUSINESS-CARD-EUROPEAN 186)

  ;; Размер страницы "Business Card Scandinavia" (90.0мм x 55.0мм)
  (:PAGE-SIZE-BUSINESS-CARD-SCANDINAVIA 187)

  ;; Размер страницы "Business Card China" (90.0мм x 54.0мм)
  (:PAGE-SIZE-BUSINESS-CARD-CHINA 188)

  ;; Размер страницы "Business Card Japan" (91.0мм x 55.0мм)
  (:PAGE-SIZE-BUSINESS-CARD-JAPAN 189)

  ;; Размер страницы "Business Card Iran" (85.0мм x 48.0мм)
  (:PAGE-SIZE-BUSINESS-CARD-IRAN 190)

  ;; Размер страницы "Business Card Hungary" (90.0мм x 50.0мм)
  (:PAGE-SIZE-BUSINESS-CARD-HUNGARY 191)

  ;; Размер страницы "Business Card ISO 7810 ID-1" (85.6мм x 54.0мм)
  (:PAGE-SIZE-BUSINESS-CARD-ISO-7810-ID-1 192)

  ;; Размер страницы "ISO 217:1995 RA0" (860.0мм x 1220.0мм)
  (:PAGE-SIZE-RAW-RA0 193)

  ;; Размер страницы "ISO 217:1995 RA1" (610.0мм x 860.0мм)
  (:PAGE-SIZE-RAW-RA1 194)

  ;; Размер страницы "ISO 217:1995 RA2" (430.0мм x 610.0мм)
  (:PAGE-SIZE-RAW-RA2 195)

  ;; Размер страницы "ISO 217:1995 RA3" (305.0мм x 430.0мм)
  (:PAGE-SIZE-RAW-RA3 196)

  ;; Размер страницы "ISO 217:1995 RA4" (215.0мм x 305.0мм)
  (:PAGE-SIZE-RAW-RA4 197)

  ;; Размер страницы "ISO 217:1995 SRA0" (900.0мм x 1280.0мм)
  (:PAGE-SIZE-RAW-SRA0 198)

  ;; Размер страницы "ISO 217:1995 SRA1" (640.0мм x 900.0мм)
  (:PAGE-SIZE-RAW-SRA1 199)

  ;; Размер страницы "ISO 217:1995 SRA2" (450.0мм x 640.0мм)
  (:PAGE-SIZE-RAW-SRA2 200)

  ;; Размер страницы "ISO 217:1995 SRA3" (320.0мм x 450.0мм)
  (:PAGE-SIZE-RAW-SRA3 201)

  ;; Размер страницы "ISO 217:1995 SRA4" (225.0мм x 320.0мм)
  (:PAGE-SIZE-RAW-SRA4 202)

  ;; Размер страницы "ISO 217:1995 SRA1+" (660.0мм x 920.0мм)
  (:PAGE-SIZE-RAW-SRA1-PLUS 203)

  ;; Размер страницы "ISO 217:1995 SRA2+" (480.0мм x 650.0мм)
  (:PAGE-SIZE-RAW-SRA2-PLUS 204)

  ;; Размер страницы "ISO 217:1995 SRA3+" (320.0мм x 460.0мм)
  (:PAGE-SIZE-RAW-SRA3-PLUS 205)

  ;; Размер страницы "ISO 217:1995 SRA3++" (320.0мм x 464.0мм)
  (:PAGE-SIZE-RAW-SRA3-PLUS-PLUS 206)

  ;; Размер страницы "ISO 217:1995 A0U" (880.0мм x 1230.0мм)
  (:PAGE-SIZE-RAW-A0U 207)

  ;; Размер страницы "ISO 217:1995 A1U" (625.0мм x 880.0мм)
  (:PAGE-SIZE-RAW-A1U 208)

  ;; Размер страницы "ISO 217:1995 A2U" (450.0мм x 625.0мм)
  (:PAGE-SIZE-RAW-A2U 209)

  ;; Размер страницы "ISO 217:1995 A3U" (330.0мм x 450.0мм)
  (:PAGE-SIZE-RAW-A3U 210)

  ;; Размер страницы "ISO 217:1995 A4U" (240.0мм x 330.0мм)
  (:PAGE-SIZE-RAW-A4U 211)

  ;; Размер страницы "Billboard 1 Sheet" (508.0мм x 762.0мм)
  (:PAGE-SIZE-BILLBOARD-1-SHEET 212)

  ;; Размер страницы "Billboard 2 Sheet" (762.0мм x 1016.0мм)
  (:PAGE-SIZE-BILLBOARD-2-SHEET 213)

  ;; Размер страницы "Billboard 4 Sheet" (1016.0мм x 1524.0мм)
  (:PAGE-SIZE-BILLBOARD-4-SHEET 214)

  ;; Размер страницы "Billboard 6 Sheet" (1200.0мм x 1800.0мм)
  (:PAGE-SIZE-BILLBOARD-6-SHEET 215)

  ;; Размер страницы "Billboard 12 Sheet" (3048.0мм x 1524.0мм)
  (:PAGE-SIZE-BILLBOARD-12-SHEET 216)

  ;; Размер страницы "Billboard 16 Sheet" (2032.0мм x 3048.0мм)
  (:PAGE-SIZE-BILLBOARD-16-SHEET 217)

  ;; Размер страницы "Billboard 32 Sheet" (4064.0мм x 3048.0мм)
  (:PAGE-SIZE-BILLBOARD-32-SHEET 218)

  ;; Размер страницы "Billboard 48 Sheet" (6096.0мм x 3048.0мм)
  (:PAGE-SIZE-BILLBOARD-48-SHEET 219)

  ;; Размер страницы "Billboard 64 Sheet" (8128.0мм x 3048.0мм)
  (:PAGE-SIZE-BILLBOARD-64-SHEET 220)

  ;; Размер страницы "Billboard 96 Sheet" (12192.0мм x 3048.0мм)
  (:PAGE-SIZE-BILLBOARD-96-SHEET 221)

  ;; Размер страницы "Japanese JIS JB0" (1030.0мм x 1456.0мм)
  (:PAGE-SIZE-JAPANESE-JB0 222)

  ;; Размер страницы "Japanese JIS JB1" (728.0мм x 1030.0мм)
  (:PAGE-SIZE-JAPANESE-JB1 223)

  ;; Размер страницы "Japanese JIS JB2" (515.0мм x 728.0мм)
  (:PAGE-SIZE-JAPANESE-JB2 224)

  ;; Размер страницы "Japanese JIS JB3" (364.0мм x 515.0мм)
  (:PAGE-SIZE-JAPANESE-JB3 225)

  ;; Размер страницы "Japanese JIS JB4" (257.0мм x 364.0мм)
  (:PAGE-SIZE-JAPANESE-JB4 226)

  ;; Размер страницы "Japanese JIS JB5" (182.0мм x 257.0мм)
  (:PAGE-SIZE-JAPANESE-JB5 227)

  ;; Размер страницы "Japanese JIS JB6" (128.0мм x 182.0мм)
  (:PAGE-SIZE-JAPANESE-JB6 228)

  ;; Размер страницы "Japanese JIS JB7" (91.0мм x 128.0мм)
  (:PAGE-SIZE-JAPANESE-JB7 229)

  ;; Размер страницы "Japanese JIS JB8" (64.0мм x 91.0мм)
  (:PAGE-SIZE-JAPANESE-JB8 230)

  ;; Размер страницы "Japanese JIS JB9" (45.0мм x 64.0мм)
  (:PAGE-SIZE-JAPANESE-JB9 231)

  ;; Размер страницы "Japanese JIS JB10" (32.0мм x 45.0мм)
  (:PAGE-SIZE-JAPANESE-JB10 232)

  ;; Размер страницы "Japanese JIS JB11" (22.0мм x 32.0мм)
  (:PAGE-SIZE-JAPANESE-JB11 233)

  ;; Размер страницы "Japanese JIS JB12" (16.0мм x 22.0мм)
  (:PAGE-SIZE-JAPANESE-JB12 234)

  ;; Размер страницы "Japanese Shiroku Shiroku ban 4" (264.0мм x 379.0мм)
  (:PAGE-SIZE-JAPANESE-SHIROKU-BAN-4 235)

  ;; Размер страницы "Japanese Shiroku Shiroku ban 5" (189.0мм x 262.0мм)
  (:PAGE-SIZE-JAPANESE-SHIROKU-BAN-5 236)

  ;; Размер страницы "Japanese Shiroku Shiroku ban 6" (127.0мм x 188.0мм)
  (:PAGE-SIZE-JAPANESE-SHIROKU-BAN-6 237)

  ;; Размер страницы "Japanese Kiku Kiku 4" (227.0мм x 306.0мм)
  (:PAGE-SIZE-JAPANESE-KIKU-4 238)

  ;; Размер страницы "Japanese Kiku Kiku 5" (151.0мм x 227.0мм)
  (:PAGE-SIZE-JAPANESE-KIKU-5 239)

  ;; Размер страницы "Canadian CAN 2-9.60M P1" (560.0мм x 860.0мм)
  (:PAGE-SIZE-CANADIAN-P1 240)

  ;; Размер страницы "Canadian CAN 2-9.60M P2" (430.0мм x 560.0мм)
  (:PAGE-SIZE-CANADIAN-P2 241)

  ;; Размер страницы "Canadian CAN 2-9.60M P3" (280.0мм x 430.0мм)
  (:PAGE-SIZE-CANADIAN-P3 242)

  ;; Размер страницы "Canadian CAN 2-9.60M P4" (215.0мм x 280.0мм)
  (:PAGE-SIZE-CANADIAN-P4 243)

  ;; Размер страницы "Canadian CAN 2-9.60M P5" (140.0мм x 215.0мм)
  (:PAGE-SIZE-CANADIAN-P5 244)

  ;; Размер страницы "Canadian CAN 2-9.60M P6" (107.0мм x 140.0мм)
  (:PAGE-SIZE-CANADIAN-P6 245)

  ;; Размер страницы "German DIN 476 DIN D0" (771.0мм x 1090.0мм)
  (:PAGE-SIZE-DIN-D0 246)

  ;; Размер страницы "German DIN 476 DIN D1" (545.0мм x 771.0мм)
  (:PAGE-SIZE-DIN-D1 247)

  ;; Размер страницы "German DIN 476 DIN D2" (385.0мм x 545.0мм)
  (:PAGE-SIZE-DIN-D2 248)

  ;; Размер страницы "German DIN 476 DIN D3" (272.0мм x 385.0мм)
  (:PAGE-SIZE-DIN-D3 249)

  ;; Размер страницы "German DIN 476 DIN D4" (192.0мм x 272.0мм)
  (:PAGE-SIZE-DIN-D4 250)

  ;; Размер страницы "German DIN 476 DIN D5" (136.0мм x 192.0мм)
  (:PAGE-SIZE-DIN-D5 251)

  ;; Размер страницы "German DIN 476 DIN D6" (96.0мм x 136.0мм)
  (:PAGE-SIZE-DIN-D6 252)

  ;; Размер страницы "German DIN 476 DIN D7" (68.0мм x 96.0мм)
  (:PAGE-SIZE-DIN-D7 253)

  ;; Размер страницы "German DIN 476 DIN D8" (48.0мм x 68.0мм)
  (:PAGE-SIZE-DIN-D8 254)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E0" (878.0мм x 1242.0мм)
  (:PAGE-SIZE-SIS-E0 255)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E1" (621.0мм x 878.0мм)
  (:PAGE-SIZE-SIS-E1 256)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E2" (439.0мм x 621.0мм)
  (:PAGE-SIZE-SIS-E2 257)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E3" (310.0мм x 439.0мм)
  (:PAGE-SIZE-SIS-E3 258)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E4" (220.0мм x 310.0мм)
  (:PAGE-SIZE-SIS-E4 259)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E5" (155.0мм x 220.0мм)
  (:PAGE-SIZE-SIS-E5 260)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E6" (110.0мм x 155.0мм)
  (:PAGE-SIZE-SIS-E6 261)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E7" (78.0мм x 110.0мм)
  (:PAGE-SIZE-SIS-E7 262)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E8" (55.0мм x 78.0мм)
  (:PAGE-SIZE-SIS-E8 263)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E9" (39.0мм x 55.0мм)
  (:PAGE-SIZE-SIS-E9 264)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS E10" (27.0мм x 39.0мм)
  (:PAGE-SIZE-SIS-E10 265)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F0" (958.0мм x 1354.0мм)
  (:PAGE-SIZE-SIS-F0 266)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F1" (677.0мм x 958.0мм)
  (:PAGE-SIZE-SIS-F1 267)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F2" (479.0мм x 677.0мм)
  (:PAGE-SIZE-SIS-F2 268)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F3" (339.0мм x 479.0мм)
  (:PAGE-SIZE-SIS-F3 269)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F4" (239.0мм x 339.0мм)
  (:PAGE-SIZE-SIS-F4 270)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F5" (169.0мм x 239.0мм)
  (:PAGE-SIZE-SIS-F5 271)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F6" (120.0мм x 169.0мм)
  (:PAGE-SIZE-SIS-F6 272)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F7" (85.0мм x 120.0мм)
  (:PAGE-SIZE-SIS-F7 273)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F8" (60.0мм x 85.0мм)
  (:PAGE-SIZE-SIS-F8 274)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F9" (42.0мм x 60.0мм)
  (:PAGE-SIZE-SIS-F9 275)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS F10" (30.0мм x 42.0мм)
  (:PAGE-SIZE-SIS-F10 276)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G0" (1044.0мм x 1477.0мм)
  (:PAGE-SIZE-SIS-G0 277)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G1" (738.0мм x 1044.0мм)
  (:PAGE-SIZE-SIS-G1 278)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G2" (522.0мм x 738.0мм)
  (:PAGE-SIZE-SIS-G2 279)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G3" (369.0мм x 522.0мм)
  (:PAGE-SIZE-SIS-G3 280)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G4" (261.0мм x 369.0мм)
  (:PAGE-SIZE-SIS-G4 281)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G5" (185.0мм x 261.0мм)
  (:PAGE-SIZE-SIS-G5 282)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G6" (131.0мм x 185.0мм)
  (:PAGE-SIZE-SIS-G6 283)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G7" (92.0мм x 131.0мм)
  (:PAGE-SIZE-SIS-G7 284)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G8" (65.0мм x 92.0мм)
  (:PAGE-SIZE-SIS-G8 285)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G9" (46.0мм x 65.0мм)
  (:PAGE-SIZE-SIS-G9 286)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS G10" (33.0мм x 46.0мм)
  (:PAGE-SIZE-SIS-G10 287)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D0" (1091.0мм x 1542.0мм)
  (:PAGE-SIZE-SIS-D0 288)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D1" (771.0мм x 1091.0мм)
  (:PAGE-SIZE-SIS-D1 289)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D2" (545.0мм x 771.0мм)
  (:PAGE-SIZE-SIS-D2 290)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D3" (386.0мм x 545.0мм)
  (:PAGE-SIZE-SIS-D3 291)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D4" (273.0мм x 386.0мм)
  (:PAGE-SIZE-SIS-D4 292)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D5" (193.0мм x 273.0мм)
  (:PAGE-SIZE-SIS-D5 293)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D6" (136.0мм x 193.0мм)
  (:PAGE-SIZE-SIS-D6 294)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D7" (96.0мм x 136.0мм)
  (:PAGE-SIZE-SIS-D7 295)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D8" (68.0мм x 96.0мм)
  (:PAGE-SIZE-SIS-D8 296)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D9" (48.0мм x 68.0мм)
  (:PAGE-SIZE-SIS-D9 297)

  ;; Размер страницы "Swedish SIS 01 47 11 SIS D10" (34.0мм x 48.0мм)
  (:PAGE-SIZE-SIS-D10 298)

  ;; Размер страницы "Colombian Carta" (216.0мм x 279.0мм)
  (:PAGE-SIZE-COLOMBIAN-CARTA 299)

  ;; Размер страницы "Colombian Extra Tabloide" (304.0мм x 457.2мм)
  (:PAGE-SIZE-COLOMBIAN-EXTRA-TABLOIDE 300)

  ;; Размер страницы "Colombian Oficio" (216.0мм x 330.0мм)
  (:PAGE-SIZE-COLOMBIAN-OFICIO 301)

  ;; Размер страницы "Colombian 1/8 pliego" (250.0мм x 350.0мм)
  (:PAGE-SIZE-COLOMBIAN-1-8-PLIEGO 302)

  ;; Размер страницы "Colombian 1/4 pliego" (350.0мм x 500.0мм)
  (:PAGE-SIZE-COLOMBIAN-1-4-PLIEGO 303)

  ;; Размер страницы "Colombian 1/2 pliego" (500.0мм x 700.0мм)
  (:PAGE-SIZE-COLOMBIAN-1-2-PLIEGO 304)

  ;; Размер страницы "Colombian Pliego" (700.0мм x 1000.0мм)
  (:PAGE-SIZE-COLOMBIAN-PLIEGO 305)

  ;; Размер страницы "Chinese GB/T 148-1997 D0" (764.0мм x 1064.0мм)
  (:PAGE-SIZE-CHINESE-D0 306)

  ;; Размер страницы "Chinese GB/T 148-1997 D1" (532.0мм x 760.0мм)
  (:PAGE-SIZE-CHINESE-D1 307)

  ;; Размер страницы "Chinese GB/T 148-1997 D2" (380.0мм x 528.0мм)
  (:PAGE-SIZE-CHINESE-D2 308)

  ;; Размер страницы "Chinese GB/T 148-1997 D3" (264.0мм x 376.0мм)
  (:PAGE-SIZE-CHINESE-D3 309)

  ;; Размер страницы "Chinese GB/T 148-1997 D4" (188.0мм x 260.0мм)
  (:PAGE-SIZE-CHINESE-D4 310)

  ;; Размер страницы "Chinese GB/T 148-1997 D5" (130.0мм x 184.0мм)
  (:PAGE-SIZE-CHINESE-D5 311)

  ;; Размер страницы "Chinese GB/T 148-1997 D6" (92.0мм x 126.0мм)
  (:PAGE-SIZE-CHINESE-D6 312)

  ;; Размер страницы "Chinese GB/T 148-1997 RD0" (787.0мм x 1092.0мм)
  (:PAGE-SIZE-CHINESE-RD0 313)

  ;; Размер страницы "Chinese GB/T 148-1997 RD1" (546.0мм x 787.0мм)
  (:PAGE-SIZE-CHINESE-RD1 314)

  ;; Размер страницы "Chinese GB/T 148-1997 RD2" (393.0мм x 546.0мм)
  (:PAGE-SIZE-CHINESE-RD2 315)

  ;; Размер страницы "Chinese GB/T 148-1997 RD3" (273.0мм x 393.0мм)
  (:PAGE-SIZE-CHINESE-RD3 316)

  ;; Размер страницы "Chinese GB/T 148-1997 RD4" (196.0мм x 273.0мм)
  (:PAGE-SIZE-CHINESE-RD4 317)

  ;; Размер страницы "Chinese GB/T 148-1997 RD5" (136.0мм x 196.0мм)
  (:PAGE-SIZE-CHINESE-RD5 318)

  ;; Размер страницы "Chinese GB/T 148-1997 RD6" (98.0мм x 136.0мм)
  (:PAGE-SIZE-CHINESE-RD6 319)

  ;; Размер страницы "Transitional PA Series PA0" (840.0мм x 1120.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA0 320)

  ;; Размер страницы "Transitional PA Series PA1" (560.0мм x 840.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA1 321)

  ;; Размер страницы "Transitional PA Series PA2" (420.0мм x 560.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA2 322)

  ;; Размер страницы "Transitional PA Series PA3" (280.0мм x 420.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA3 323)

  ;; Размер страницы "Transitional PA Series PA4" (210.0мм x 280.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA4 324)

  ;; Размер страницы "Transitional PA Series PA5" (140.0мм x 210.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA5 325)

  ;; Размер страницы "Transitional PA Series PA6" (105.0мм x 140.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA6 326)

  ;; Размер страницы "Transitional PA Series PA7" (70.0мм x 105.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA7 327)

  ;; Размер страницы "Transitional PA Series PA8" (52.0мм x 70.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA8 328)

  ;; Размер страницы "Transitional PA Series PA9" (35.0мм x 52.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA9 329)

  ;; Размер страницы "Transitional PA Series PA10" (26.0мм x 35.0мм)
  (:PAGE-SIZE-TRANSITIONAL-PA10 330)

  ;; Размер страницы "Transitional F Series F0" (841.0мм x 1321.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F0 331)

  ;; Размер страницы "Transitional F Series F1" (660.0мм x 841.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F1 332)

  ;; Размер страницы "Transitional F Series F2" (420.0мм x 660.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F2 333)

  ;; Размер страницы "Transitional F Series F3" (330.0мм x 420.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F3 334)

  ;; Размер страницы "Transitional F Series F4" (210.0мм x 330.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F4 335)

  ;; Размер страницы "Transitional F Series F5" (165.0мм x 210.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F5 336)

  ;; Размер страницы "Transitional F Series F6" (105.0мм x 165.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F6 337)

  ;; Размер страницы "Transitional F Series F7" (82.0мм x 105.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F7 338)

  ;; Размер страницы "Transitional F Series F8" (52.0мм x 82.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F8 339)

  ;; Размер страницы "Transitional F Series F9" (41.0мм x 52.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F9 340)

  ;; Размер страницы "Transitional F Series F10" (26.0мм x 41.0мм)
  (:PAGE-SIZE-TRANSITIONAL-F10 341)

  ;; Размер страницы "Imperial Antiquarian" (787.0мм x 1346.0мм)
  (:PAGE-SIZE-IMPERIAL-ANTIQUARIAN 342)

  ;; Размер страницы "Imperial Atlas" (660.0мм x 864.0мм)
  (:PAGE-SIZE-IMPERIAL-ATLAS 343)

  ;; Размер страницы "Imperial Brief" (343.0мм x 406.0мм)
  (:PAGE-SIZE-IMPERIAL-BRIEF 344)

  ;; Размер страницы "Imperial Broadsheet" (457.0мм x 610.0мм)
  (:PAGE-SIZE-IMPERIAL-BROADSHEET 345)

  ;; Размер страницы "Imperial Cartridge" (533.0мм x 660.0мм)
  (:PAGE-SIZE-IMPERIAL-CARTRIDGE 346)

  ;; Размер страницы "Imperial Columbier" (597.0мм x 876.0мм)
  (:PAGE-SIZE-IMPERIAL-COLUMBIER 347)

  ;; Размер страницы "Imperial Copy Draught" (406.0мм x 508.0мм)
  (:PAGE-SIZE-IMPERIAL-COPY-DRAUGHT 348)

  ;; Размер страницы "Imperial Crown" (381.0мм x 508.0мм)
  (:PAGE-SIZE-IMPERIAL-CROWN 349)

  ;; Размер страницы "Imperial Demy" (445.0мм x 572.0мм)
  (:PAGE-SIZE-IMPERIAL-DEMY 350)

  ;; Размер страницы "Imperial Double Demy" (572.0мм x 902.0мм)
  (:PAGE-SIZE-IMPERIAL-DOUBLE-DEMY 351)

  ;; Размер страницы "Imperial Quad Demy" (889.0мм x 1143.0мм)
  (:PAGE-SIZE-IMPERIAL-QUAD-DEMY 352)

  ;; Размер страницы "Imperial Elephant" (584.0мм x 711.0мм)
  (:PAGE-SIZE-IMPERIAL-ELEPHANT 353)

  ;; Размер страницы "Imperial Double Elephant" (678.0мм x 1016.0мм)
  (:PAGE-SIZE-IMPERIAL-DOUBLE-ELEPHANT 354)

  ;; Размер страницы "Imperial Emperor" (1219.0мм x 1829.0мм)
  (:PAGE-SIZE-IMPERIAL-EMPEROR 355)

  ;; Размер страницы "Imperial Foolscap" (343.0мм x 432.0мм)
  (:PAGE-SIZE-IMPERIAL-FOOLSCAP 356)

  ;; Размер страницы "Imperial Small Foolscap" (337.0мм x 419.0мм)
  (:PAGE-SIZE-IMPERIAL-SMALL-FOOLSCAP 357)

  ;; Размер страницы "Imperial Grand Eagle" (730.0мм x 1067.0мм)
  (:PAGE-SIZE-IMPERIAL-GRAND-EAGLE 358)

  ;; Размер страницы "Imperial Imperial" (559.0мм x 762.0мм)
  (:PAGE-SIZE-IMPERIAL-IMPERIAL 359)

  ;; Размер страницы "Imperial Medium" (470.0мм x 584.0мм)
  (:PAGE-SIZE-IMPERIAL-MEDIUM 360)

  ;; Размер страницы "Imperial Monarch" (184.0мм x 267.0мм)
  (:PAGE-SIZE-IMPERIAL-MONARCH 361)

  ;; Размер страницы "Imperial Post" (394.0мм x 489.0мм)
  (:PAGE-SIZE-IMPERIAL-POST 362)

  ;; Размер страницы "Imperial Sheet, Half Post" (495.0мм x 597.0мм)
  (:PAGE-SIZE-IMPERIAL-HALF-POST 363)

  ;; Размер страницы "Imperial Pinched Post" (375.0мм x 470.0мм)
  (:PAGE-SIZE-IMPERIAL-PINCHED-POST 364)

  ;; Размер страницы "Imperial Large Post" (394.0мм x 508.0мм)
  (:PAGE-SIZE-IMPERIAL-LARGE-POST 365)

  ;; Размер страницы "Imperial Double Large Post" (533.0мм x 838.0мм)
  (:PAGE-SIZE-IMPERIAL-DOUBLE-LARGE-POST 366)

  ;; Размер страницы "Imperial Double Post" (483.0мм x 762.0мм)
  (:PAGE-SIZE-IMPERIAL-DOUBLE-POST 367)

  ;; Размер страницы "Imperial Pott" (318.0мм x 381.0мм)
  (:PAGE-SIZE-IMPERIAL-POTT 368)

  ;; Размер страницы "Imperial Princess" (546.0мм x 711.0мм)
  (:PAGE-SIZE-IMPERIAL-PRINCESS 369)

  ;; Размер страницы "Imperial Quarto" (229.0мм x 279.0мм)
  (:PAGE-SIZE-IMPERIAL-QUARTO 370)

  ;; Размер страницы "Imperial Royal" (508.0мм x 635.0мм)
  (:PAGE-SIZE-IMPERIAL-ROYAL 371)

  ;; Размер страницы "Imperial Super Royal" (483.0мм x 686.0мм)
  (:PAGE-SIZE-IMPERIAL-SUPER-ROYAL 372)

  ;; Размер страницы "French Cloche" (300.0мм x 400.0мм)
  (:PAGE-SIZE-FRENCH-CLOCHE 373)

  ;; Размер страницы "French Pot, écolier" (310.0мм x 400.0мм)
  (:PAGE-SIZE-FRENCH-POT-ECOLIER 374)

  ;; Размер страницы "French Tellière" (340.0мм x 440.0мм)
  (:PAGE-SIZE-FRENCH-TELLIERE 375)

  ;; Размер страницы "French Couronne écriture" (360.0мм x 360.0мм)
  (:PAGE-SIZE-FRENCH-COURONNE-ECRITURE 376)

  ;; Размер страницы "French Couronne édition" (370.0мм x 470.0мм)
  (:PAGE-SIZE-FRENCH-COURONNE-EDITION 377)

  ;; Размер страницы "French Roberto" (390.0мм x 500.0мм)
  (:PAGE-SIZE-FRENCH-ROBERTO 378)

  ;; Размер страницы "French Écu" (400.0мм x 520.0мм)
  (:PAGE-SIZE-FRENCH-ECU 379)

  ;; Размер страницы "French Coquille" (440.0мм x 560.0мм)
  (:PAGE-SIZE-FRENCH-COQUILLE 380)

  ;; Размер страницы "French Carré" (450.0мм x 560.0мм)
  (:PAGE-SIZE-FRENCH-CARRE 381)

  ;; Размер страницы "French Cavalier" (460.0мм x 620.0мм)
  (:PAGE-SIZE-FRENCH-CAVALIER 382)

  ;; Размер страницы "French Demi-raisin" (325.0мм x 500.0мм)
  (:PAGE-SIZE-FRENCH-DEMI-RAISIN 383)

  ;; Размер страницы "French Raisin" (500.0мм x 650.0мм)
  (:PAGE-SIZE-FRENCH-RAISIN 384)

  ;; Размер страницы "French Double Raisin" (650.0мм x 1000.0мм)
  (:PAGE-SIZE-FRENCH-DOUBLE-RAISIN 385)

  ;; Размер страницы "French Jésus" (560.0мм x 760.0мм)
  (:PAGE-SIZE-FRENCH-JESUS 386)

  ;; Размер страницы "French Soleil" (600.0мм x 800.0мм)
  (:PAGE-SIZE-FRENCH-SOLEIL 387)

  ;; Размер страницы "French Colombier affiche" (600.0мм x 800.0мм)
  (:PAGE-SIZE-FRENCH-COLOMBIER-AFFICHE 388)

  ;; Размер страницы "French Colombier commercial" (630.0мм x 900.0мм)
  (:PAGE-SIZE-FRENCH-COLOMBIER-COMMERCIAL 389)

  ;; Размер страницы "French Petit Aigle" (700.0мм x 940.0мм)
  (:PAGE-SIZE-FRENCH-PETIT-AIGLE 390)

  ;; Размер страницы "French Grand Aigle" (750.0мм x 1050.0мм)
  (:PAGE-SIZE-FRENCH-GRAND-AIGLE 391)

  ;; Размер страницы "French Grand Monde" (900.0мм x 1260.0мм)
  (:PAGE-SIZE-FRENCH-GRAND-MONDE 392)

  ;; Размер страницы "French Univers" (1000.0мм x 1130.0мм)
  (:PAGE-SIZE-FRENCH-UNIVERS 393)

  ;; Размер страницы "Russian GOST 5773-90 60x84/8" (205.0мм x 290.0мм)
  (:PAGE-SIZE-RUSSIAN-60X84-8 394)

  ;; Размер страницы "Russian GOST 5773-90 60x84/16" (145.0мм x 200.0мм)
  (:PAGE-SIZE-RUSSIAN-60X84-16 395)

  ;; Размер страницы "Russian GOST 5773-90 60x84/32" (100.0мм x 140.0мм)
  (:PAGE-SIZE-RUSSIAN-60X84-32 396)

  ;; Размер страницы "Russian GOST 5773-90 60x90/8" (220.0мм x 290.0мм)
  (:PAGE-SIZE-RUSSIAN-60X90-8 397)

  ;; Размер страницы "Russian GOST 5773-90 60x90/16" (145.0мм x 215.0мм)
  (:PAGE-SIZE-RUSSIAN-60X90-16 398)

  ;; Размер страницы "Russian GOST 5773-90 70x100/16" (170.0мм x 240.0мм)
  (:PAGE-SIZE-RUSSIAN-70X100-16 399)

  ;; Размер страницы "Russian GOST 5773-90 70x100/32" (120.0мм x 165.0мм)
  (:PAGE-SIZE-RUSSIAN-70X100-32 400)

  ;; Размер страницы "Russian GOST 5773-90 70x108/8" (265.0мм x 340.0мм)
  (:PAGE-SIZE-RUSSIAN-70X108-8 401)

  ;; Размер страницы "Russian GOST 5773-90 70x108/16" (170.0мм x 260.0мм)
  (:PAGE-SIZE-RUSSIAN-70X108-16 402)

  ;; Размер страницы "Russian GOST 5773-90 70x108/32" (130.0мм x 165.0мм)
  (:PAGE-SIZE-RUSSIAN-70X108-32 403)

  ;; Размер страницы "Russian GOST 5773-90 70x90/16" (170.0мм x 215.0мм)
  (:PAGE-SIZE-RUSSIAN-70X90-16 404)

  ;; Размер страницы "Russian GOST 5773-90 70x90/32" (107.0мм x 165.0мм)
  (:PAGE-SIZE-RUSSIAN-70X90-32 405)

  ;; Размер страницы "Russian GOST 5773-90 75x90/32" (107.0мм x 177.0мм)
  (:PAGE-SIZE-RUSSIAN-75X90-32 406)

  ;; Размер страницы "Russian GOST 5773-90 84x108/16" (205.0мм x 260.0мм)
  (:PAGE-SIZE-RUSSIAN-84X108-8 407)

  ;; Размер страницы "Russian GOST 5773-90 84x108/32" (130.0мм x 200.0мм)
  (:PAGE-SIZE-RUSSIAN-84X108-32 408)
)