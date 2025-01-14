#HEADER#
/TITLE/ Command Line Modals
/POSITION/ 0,0
/SIZE/ 145,136

#EDIT#
/LABEL/ Command Length:
/POSITION/ 10,8,80,8
/SIZE/ 125,14
/TYPE/ UD_DASINT
/LEN/ 4
/PREC/ 4
/RANGE/ 40,1023

#EDIT#
/LABEL/ Comment Column:
/POSITION/ 10,25,80,25
/SIZE/ 125,14
/TYPE/ UD_DASINT
/LEN/ 4
/PREC/ 4
/RANGE/ 0,1024

#CHOICEBOX#
/LABEL/ Edit Line:
/POSITION/ 10,42,80,42
/SIZE/ 125,40
/TYPE/ UD_DASSTRING
/CHOICES/ "Off","On"

#CHOICEBOX#
/LABEL/ Keep Window Open:
/POSITION/ 10,59,80,59
/SIZE/ 125,40
/TYPE/ UD_DASSTRING
/CHOICES/ "Yes","No"

#CHOICEBOX#
/LABEL/ Window Mode:
/POSITION/ 10,76,80,76
/SIZE/ 125,40
/TYPE/ UD_DASSTRING
/CHOICES/ "No Window","Window"

#CHOICEBOX#
/LABEL/ Insert Mode:
/POSITION/ 10,93,80,93
/SIZE/ 125,40
/TYPE/ UD_DASSTRING
/CHOICES/ "Off","On","Same"

#HELP#
===================
Command Line Modals
===================
This form defines the methods and limits used with Command Line input.

Command Length:
---------------
Specifies the maximum line length that will be created when a command is
generated using the menu interface.  It also controls the length of the line
when formatting interface generated commands.  A typical value would be 72,
which is the same value previous versions of NCL defaulted to.

Comment Column:
---------------
Specifies the starting column for fixed comment text on input command lines.
A value of 0 disables any fixed column comment text causing the entire input
line to be processed as a command.  A value of 73 is the value used by previous
versions of NCL when columns 73:80 contained comment text.

Edit Line:
----------
Select 'On' at this prompt if you want a command generated by the interface to
be displayed in the Command Line prior to processing it.  This allows you to
modify the command (assign a label, etc.) prior to executing the command.  The
typical setting for this prompt is 'Off'.

Keep Window Open:
-----------------
Selecting 'Yes' at this prompt will cause the NCL Status Window to stay active
when exiting Command Line mode if it has been displayed during Command Line
input.  'No' will cause the Status Window to go away when Command Line mode is
exited.

Window Mode:
------------
Selecting 'Window' at this prompt will cause NCL to automatically display the
Status Window whenever Command Line mode is entered.  'No Window' will not
automatically open the Status Window.

Insert Mode:
------------
'On' enables Insert Mode, which causes any commands generated by the interface
to be inserted prior to the current source line.  The current source line will
not be overwritten.  'Off' enables Overstrike Mode, which causes the current
source lines to be overwitten by the interface generated commands.  'Same'
uses the insert/overstrike mode currently in effect.  The *INSERT and *CONSOL
commands are used to change the default insert/overstrike mode.

'On' is typically selected here.
