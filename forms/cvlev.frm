#HEADER#
/TITLE/ Current Status
/POSITION/ 20,30
/SIZE/280,180

#LISTBOX#
/LABEL/
/POSITION/ 10,15
/SIZE/ 250,90
/TYPE/ UD_DASSTRING

#CHECKBOX#
/LABEL/ Show All Intersections
/POSITION/ 22,105
/SIZE/85,15
/TYPE/UD_DASSTRING

#CHOICEBOX#
/LABEL/
/POSITION/ 120,105
/SIZE/80,40
/TYPE/UD_DASSTRING
/CHOICES/ "Erase Surfaces","Display Wireframe","Display Shaded"

#PUSHBUTTON#
/LABEL/ View
/POSITION/ 22,122
/SIZE/ 55,14
/TYPE/ UD_DASSTRING

#PUSHBUTTON#
/LABEL/ Fit
/POSITION/ 120,122
/SIZE/ 55,14
/TYPE/ UD_DASSTRING

#FRAME#
/TITLE/ Error Control
/POSITION/ 10,95
/SIZE/ 260,50

#HELP#

This form allows you to monitor the SPLINE/INTOF,COMPOS command.

In the case of a connection error:

   The unfinished contour is displayed in ORANGE,
   the nearest unconnected intersection is displayed in RED.

   If you check the box "Show All Intersections": 
   The remaining unconnected intersections will be drawn in PURPLE,
   the finished closed contours will be drawn in GREEN.

