#HEADER#
/TITLE/ Define New Menu
/POSITION/ -10000,-10000
/SIZE/230,100

#CHOICEBOX#      
/LABEL/ Menu Type:
/POSITION/ 10,8
/SIZE/ 95,40
/TYPE/ UD_DASSTRING
/CHOICES/ "Docked", "Floating", "Popup", "Pulldown"

#CHOICE_LIST#
/LABEL/ Menu Area:
/POSITION/ 125,8
/SIZE/ 90,60
/TYPE/ UD_DASSTRING

#EDIT#
/LABEL/ Filename:
/POSITION/ 10,25
/SIZE/ 150,14
/TYPE/ UD_DASSTRING
/PREC/ 256
/LEN/ 30

#PUSHBUTTON#
/LABEL/ Browse...
/POSITION/ 175,25
/SIZE/ 40,14
/TYPE/ UD_DASSTRING

#CHECKBOX#
/LABEL/ This Menu is Dockable
/POSITION/ 8, 42
/SIZE/100,15
/TYPE/UD_DASSTRING

#CHOICEBOX#      
/LABEL/ Menu Format:
/POSITION/ 115,44
/SIZE/ 100,40
/TYPE/ UD_DASSTRING
/CHOICES/ "Icon", "Text", "Icon/Text"

#EDIT#
/LABEL/ Menu Title:
/POSITION/ 8, 59
/SIZE/ 150,14
/TYPE/ UD_DASSTRING
/PREC/ 30
/LEN/ 30
