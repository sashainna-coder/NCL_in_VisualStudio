PARTNO test
MULTAX/ON
LOADU /test.u
REDEF /SF15,PARAMS,SWAP,REVERS,0,1,PARELM,1
DRAFT /VIEW=Front,PARAMS,CENTER=67.057,0.187,2.075,NORMAL=$
-0.838183,-0.514112,0.18204,YAXIS=0.215404,-0.005416,0.97651,SCALE=$
0.746893
LOADTL/1
CU    /0.75,0.125,2.25
DC
RP,GO /ON,CVV(44),SFF(11),ON,LNN(8)
RP,GD /-1,1,1
PTE   =PT/TE
CUT
TH1=.1
RP,GT /PTE
RP,TA /NORMAL,PS
TH    /TH1+.05,0
RP,GO /LNN(8),SFF(11),ON,(PL/PTE,PA,PLY)
PSIS  /(SURF/SFF(11),SFF(476),SF15,SFF(244))
IV    /0,-1,0
TN,GF /(LN/FWD),ON,CVV(44)
$$ **STOP

REMARK/ON
Kcv1  =CV/COMPOS,cvv(44),cvv(73),cvv(79),cvv(2283),CVV(2263),$
       cvv(2267),cv35,cvv(1192)
GL    /KCV1,ON,LNN(151)
REMARK/OFF

GL    /CVV(44),TT,CVV(73)
GF    /CVV(73),TT,CVV(79)
$$ **STOP
$$ cutter flips upside down on next move
GF    /CVV(79),TT,CVV(2283)
GF    /CVV(2283),TT,CVV(2263)
GF    /CVV(2263),TT,CVV(2267)
GF    /CVV(2267),TT,CV35
$$ cutter flips back to normal at the end of next move
GF    /CV35,TT,CVV(1192)
 GF    /CVV(1192),ON,LNN(151)
SF1   =sf/out,SFF(476)
SF2   =sf/out,SFF(11)
SF3   =sf/out,SFF(244)
REDEF /SF15,PARAMS,SWAP,REVERS,0,1,PARELM,1
