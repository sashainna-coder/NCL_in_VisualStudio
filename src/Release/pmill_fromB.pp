LOADU/port.u
invis/sf1,sf4,sf5,sf7,sf8,sf6, sf39
$$ invis/sf1,sf4,sf5,sf58,sf57,sf7,sf8,sf6, sf39
$$ invis/psf1
$$ CV5 = SPLINE/PSF1,3,0.1
CV3   =SPLINE/PSF1,3, 0.45
*stop
$$ CV6 = SPLINE/PSF1,3,0.1
$$ CV7 = SPLINE/PSF1,4,0.1
$$ CV5   =SPLINE/PSF1,4, 0.2
CV4   =SPLINE/OFFSET,CV3,ZS,1
PL1   =PL/(PV/ON,CV3,0.025)
$$ PL1   =PL/(PV/ON,CV4,0.0)
$$ PL2   =PL/(PV/ON,CV4,0.59538)
$$PL2   =PL/(PV/ON,CV4,0.53076)
$$PL2   =PL/(PV/ON,CV4,0.652)
PL2   =PL/(PV/ON,CV3,0.5)
PT1   =POINT/YSMALL,ENDPT,CV3
$$ PL3   =PL/(PV/ON,CV4,0.9)
TH/0.1
CU    /0.35,0.175,0.35,-89
$$ CV7=cv/intof,PSF1,pl2
OB    /PT1,X,Y,Z
PT2   =PT/X+0.25,Y-0.5,Z
GOTO  /X+3,Y-0.5,Z
GOTO/PT2
$$ sft = sf/PSF1,PL1,PL2
$$ sft = SURF/FILLET,PL1,PSF1,PL2
TA/THRU,PT2
$$ *stop
PMILL/PSF1,CONTCT,PL1,PL2,STEP,0.1,HELIX,OMIT,IN


