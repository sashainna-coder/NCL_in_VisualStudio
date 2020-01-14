/*********************************************************************
**    NAME         :  nupmill.c
**       CONTAINS: User interface routines for port surfaces milling.
**
**       nclu_pmill()
**
**    COPYRIGHT 2019 (c) NCCS Inc.  All Rights Reserved.
**    MODULE NAME AND RELEASE LEVEL
**       
**    DATE AND TIME OF LAST MODIFICATION
**       
*********************************************************************/

#include "usysdef.h"
#include "wsgl.h"
#include "udebug.h"
#include "uhep.h"
#include "dasnog.h"
#include "dasg.h"
#include "dselmask.h"
#include "class.h"
#include "mdrel.h"
#include "mdpick.h"
#include "mxxx.h"
#include "modef.h"
#include "mdcoord.h"
#include "mdcpln.h"
#include "mcrv.h"
#include "msrf.h"
#include "mdeval.h"
#include "udforms.h"

#include "nccs.h"
#include "ncl.h"
#include "nclcmd.h"
#include "nclfc.h"
#include "nclinp.h"
#include "nclx.h"
#include "nkeywd.h"
#include "nclmodals.h"
#include "nclvx.h"
#include "driver.h"
#include "mgeom.h"
#include "lcom.h"
#include "nclmplay.h"
#include "nclx.h"
#include "nclxmdl.h"
#include "nclxmot.h"

#define MXLAB NCL_MAX_LABEL+1
#define EDGTO 0
#define EDGPAST 1
#define EDGON 2
#define CONTCT 3
/*
.....PMill
*/
#define MILLRG1		0
#define MILLRG2		1
#define MILLRG3		2
/*
.....Motion Type
*/
#define MOTIONTRG1		3 //type choice
#define MOTIONTRG2		4 //rad text input
#define MOTIONTRG3		5 //orientation choice
#define MOTIONTRG4		6 //step text input
#define MOTIONTRG5		7 //Tolerance choice
#define MOTIONTRG6		8 //Tolerance text input
/*remove #define MOTIONTRG7		9 //Direction set to 'planes' only, make it dis-active */
#define MOTIONTRG8		9 //sf1 text input
#define MOTIONTRG9		10 //sf1 select button
#define MOTIONTRG10		11 //sf2 text input
#define MOTIONTRG11		12 //sf2 select button
#define MOTIONTRG12		13 // Retract choice
#define MOTIONTRG13		14 // Retract
#define MOTIONTRG14		15 // Retract
#define MOTIONTRG15		16 // Fedrat choice
#define MOTIONTRG16		17 // Fedrat
/*
......Boundaries
*/
#define BOUNDRG4	18
#define BOUNDRG5	19
/*
.....Entry /Exit
*/
#define ENEXTRG1	20
#define ENEXTRG2	21
#define ENEXTRG3	22
#define ENEXTRG4	23
#define ENEXTRG5	24
#define ENEXTRG6	25
#define ENEXTRG7	26
#define ENEXTRG8	27
#define ENEXTRG9	28
#define ENEXTRG10	29
#define ENEXTRG11	30
#define ENEXTRG12	31
#define ENEXTRG13	32
/*
.....Colors
*/
#define CLRRG1	33
#define CLRRG2	34
#define CLRRG3	35
#define CLRRG4	36
#define CLRRG5	37
#define CLRRG6	38
#define CLRRG7	39
#define CLRRG8	40
/*
.....Action Buttons
*/
#define FAPV	41
#define FAPY	42
#define FARS	43
#define FAPB	44
#define FAVE	45
#define FAGE	46
#define FAVW	47
#define FVIDEO	48

#define HIDE_KEY 0
#define CONTOUR_KEY 1
extern int NCL_preview_mot;
/*
.....Section definitions
*/
enum {PMill, MotionT, Boundary, Entry, Colors};
static char *Smode[]={"PMill", "Motion Type", "Boundaries", "Entry / Exit", "Colors"};
static int Sred[3]={180,0,0}, Syellow[3]={180,148,0}, Sgreen[3]={0,180,0};
static int Sblack[3]={0,0,0};
static int *Ssecol[]={Sblack,Sblack,Sblack,Sblack,Sblack,Sblack};
static int Sacc[6];
static char Sfeed_valuestr[80], Sav_valuestr[80], Sav_valuestr1[80],Sav_valuestr2[80];
static int Ssav_fchc, Ssav_fchc1, Ssav_fchc2;

extern int NAUTIPV;
extern UD_METHOD UD_initfrm_intry;

static UU_LIST Skey_list;
static int Snkeys;
static UU_LOGICAL Skey_init;
static int Sfrm;
static UU_LOGICAL Sactive = UU_FALSE;

static UU_LIST Ssurf;
static int Snsurf = 0;
static int Scolor;
static int Tcolor;
static int Tstptclr, Tdirclr, Tclnclr, Tretclr, Tpassclr,
	Sstptclr, Sdirclr, Sclnclr, Sretclr, Spassclr, Spassclr;
static int Tgeotog, Tgeocol, Sgeotog, Sgeocol;

static UU_LOGICAL Sgeo_init;
static UU_LOGICAL Sgeo_redraw;

static UM_sgeo Sgsf,Sgspt, Sgrap, Sgret, SgLrap, Sgdrv1, Sgdrv2;

static UU_LOGICAL Spmfrm_init = UU_FALSE;

static char Sptnam[MXLAB];
static char Sraptoval[MXLAB];
static char Sretrctval[MXLAB];
static char SLraptoval[MXLAB];
static char Sdirval1[MXLAB];
static char Sdirval2[MXLAB];

static char Tptnam[MXLAB];
static char Traptoval[MXLAB];
static char Tretrctval[MXLAB];
static char TLraptoval[MXLAB];
static char Tdirval1[MXLAB];
static char Tdirval2[MXLAB];

static int Sstarttyp=0, /*Sdir=0, */ Stoltyp=0, Sedgetyp = 0;
static int Smethod=0, SLraptotyp=0, SLraptofed=0;
static int Sraptotyp=0, Sraptofed=0, Sretrcttyp=0, Sretrctfed=0;
static UU_REAL Sstp=0.0, Stoler=0.0;
static UU_REAL Trad=0.0, Srad=0.0;
static int Tstarttyp=0, /*Tdir=0,*/ Ttoltyp=0, Tedgetyp = 0;
static int Tmethod=0, Torient=0,       TLraptotyp=0, TLraptofed=0;
static int Traptotyp=0, Traptofed=0, Tretrcttyp=0, Tretrctfed=0;
static int Signore=0, Tignore=0;

static UN_motseg *Smptr=0,Smotatt;
static UN_mot_vpbox_struc Smvpbox[UV_NVPORTS];

static char Sstp_str[65]="0.0", Srad_str[65]="0.0",
		Stoler_str[65]="0.0",
		Sraptofrv_str[65]="0.0", Sretrctfrv_str[65]="0.0",
		SLraptofrv_str[65]="0.0";
static char Tstp_str[65]="0.0", Trad_str[65]="0.0",
		Ttoler_str[65]="0.0",
		Traptofrv_str[65]="0.0", Tretrctfrv_str[65]="0.0",
		TLraptofrv_str[65]="0.0", Tcmd_str[8][65];

static int SfrmPlay=0;
static int Serrflg,Spreviewflg,Schgmade,Smenu_ch[14];
static UD_FSTAT OnColors(), OnAction(), OnVideo();
static UD_FSTAT OnPText(), OnPButton();
static UD_FSTAT OnMChcPick(), OnMText(), OnMButton();
static UD_FSTAT OnBChcPick(), OnBChkPick();
static UD_FSTAT OnEChcPick(), OnEText(), OnEButton();
static void S_unhilite_all(), S_hilite_entity(), S_hilite_entities(),
		S_init_form(), S_create_key_list(), S_add_key(), S_section_changed(),
		S_form_invis(), S_update_answers(), S_unhilite_entities();
static int S_build_command();
//static int Sseltyp = 0, Tseltyp = 0;
static char Sselsrf[NCL_MAX_LABEL_AND_SUBSCRIPT] = "", Tselsrf[NCL_MAX_LABEL_AND_SUBSCRIPT] = ""; 

static int *Sanswers[] = {
/*
.....PMill  3
*/
		&Tselsrf, UU_NULL, UU_NULL,
/*
......Motion Type 16
*/
		&Tmethod, &Trad, &Torient, (int *)&Tstp_str, 
		&Ttoltyp,(int *)&Ttoler_str,
		/*&Tdir, */(int *)&Tdirval1,  UU_NULL,
			(int *)&Tdirval2,  UU_NULL, 
		&TLraptotyp, (int *)&TLraptoval,  UU_NULL,
		&TLraptofed, (int *)&TLraptofrv_str,
/*
.....Boundaries
*/
		&Tedgetyp, &Tignore,
/*
.....Entry/Exit
*/
		&Tstarttyp, (int *)&Tptnam, UU_NULL, 			
		&Traptotyp, (int *)&Traptoval,  UU_NULL,
		&Traptofed, (int *)&Traptofrv_str,
		&Tretrcttyp, (int *)&Tretrctval, UU_NULL,
		&Tretrctfed, (int *)Tretrctfrv_str,
/*
.....Colors
*/
		&Tcolor, &Tstptclr, &Tdirclr, &Tclnclr, &Tretclr, 
		&Tpassclr, &Tgeotog, &Tgeocol,
		UU_NULL, UU_NULL, UU_NULL, UU_NULL, UU_NULL, UU_NULL, UU_NULL,UU_NULL
	};
/*********************************************************************
**    I_FUNCTION     : S_enable_buttons()
**			Determines which fields should be enabled and which buttons
**       marked as necessary, but unfulfilled based on the Part, Drive,
**       and Check surface selections.
**    PARAMETERS   
**       INPUT  :
**          none.
**       OUTPUT :  
**          none.
**    RETURNS      : UU_TRUE if Check Surface is satisfied.
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static UU_LOGICAL S_enable_buttons()
{
	int nc, nc1, nc2, nc3, nc5, nc6, nc7, nc8;
	char label[2*65];
	UU_REAL rval;
	UU_LOGICAL sect11, sect2, sect20, sect21, sect22, sect23, sect24, sect25, sect26,
		sect41, sect42, sect43;
	UU_LOGICAL ifl;
//	UM_real8 pahismill, stessmill,rptsmill,rtrsmill,dpesmill,fresmill,tolsmill, fdrrptsmill, fdrrtrsmill;   
//	int sc10_3;
	char buf[10];
//need pmill parameter function
//	smillpar(&pahismill, &stessmill,&rptsmill,&rtrsmill,&sc10_3,&dpesmill,&fresmill,&tolsmill, &fdrrptsmill, &fdrrtrsmill );
/*
......PMill
*/
	Snsurf = UU_LIST_LENGTH(&Ssurf);
	if (Snsurf<=0)
		sect11 = UU_FALSE;
	else
		sect11 = UU_TRUE;
	if (sect11)
	{
		ud_dispfrm_set_attribs(0,MILLRG1,UM_BLACK,UM_WHITE);
		ud_dispfrm_set_attribs(0,MILLRG2,UM_BLACK,Tcolor);
	}
	else
	{
		ud_dispfrm_set_attribs(0,MILLRG1,UM_WHITE,UM_RED);
		ud_dispfrm_set_attribs(0,MILLRG2,UM_WHITE,UM_RED);
	}
/*
.......motion type
*/
	sect2 = UU_TRUE;
	sect20 = UU_TRUE;
	if (Tmethod==2)
	{
		nc = (int)strlen(Trad_str);
		ul_strip_blanks(Trad_str, &nc);
		if (nc<0)
			sect20 = UU_FALSE;
		rval = atof(Trad_str);
		if (rval<=0)
			sect20 =  UU_FALSE;
		if (sect20) 
			ud_dispfrm_set_attribs(0, MOTIONTRG2, UM_BLACK, UM_WHITE);
		else 
		{
			ud_dispfrm_set_attribs(0, MOTIONTRG2,UM_WHITE,UM_RED);
		}
	}
	sect21 = UU_TRUE;
	nc = (int)strlen(Tstp_str);
	ul_strip_blanks(Tstp_str, &nc);
	if (nc<0)
		sect21 = UU_FALSE;
	rval = atof(Sstp_str);
	if (rval<=0)
		sect21 =  UU_FALSE;
	if (sect21) 
		ud_dispfrm_set_attribs(0, MOTIONTRG4, UM_BLACK, UM_WHITE);
	else 
	{
		ud_dispfrm_set_attribs(0, MOTIONTRG4,UM_WHITE,UM_RED);
	}
	sect22 = UU_TRUE;
	nc = (int)strlen(Ttoler_str);
	ul_strip_blanks(Ttoler_str, &nc);
	if (nc<=0)
	{
		ud_dispfrm_set_attribs(0,MOTIONTRG6,UM_WHITE,UM_RED);
		sect22 = UU_FALSE;
	}
	else
	{
		if (Ttoltyp!=0)
		{
			rval = atof(Ttoler_str);
			if (rval<0)
				sect22 =  UU_FALSE;
			if (sect22) 
				ud_dispfrm_set_attribs(0, MOTIONTRG6, UM_BLACK, UM_WHITE);
			else 
			{
				ud_dispfrm_set_attribs(0, MOTIONTRG6,UM_WHITE,UM_RED);
			}
		}
		else
			ud_dispfrm_set_attribs(0, MOTIONTRG6, UM_BLACK, UM_WHITE);
	}
	sect23 = UU_TRUE;
	nc = (int)strlen(Tdirval1);
	ul_strip_blanks(Tdirval1, &nc);
	if (nc<=0)
	{
		ud_dispfrm_set_attribs(0,MOTIONTRG8,UM_WHITE,UM_RED);
		ud_dispfrm_set_attribs(0,MOTIONTRG9,UM_WHITE,UM_RED);
		sect23 = UU_FALSE;
	}
	else
	{
		ud_dispfrm_set_attribs(0, MOTIONTRG8, UM_BLACK, UM_WHITE);
		ud_dispfrm_set_attribs(0,MOTIONTRG9, UM_BLACK, Tdirclr);
		sect23 = UU_TRUE;
	}
	sect24 = UU_TRUE;
/*	if (Tdir==0)  */
	{
		nc = (int)strlen(Tdirval2);
		ul_strip_blanks(Tdirval2, &nc);
		if (nc<=0)
		{
			ud_dispfrm_set_attribs(0,MOTIONTRG10,UM_WHITE,UM_RED);
			ud_dispfrm_set_attribs(0,MOTIONTRG11,UM_WHITE,UM_RED);
			sect24 = UU_FALSE;
		}
		else
		{
			ud_dispfrm_set_attribs(0, MOTIONTRG10, UM_BLACK, UM_WHITE);
			ud_dispfrm_set_attribs(0,MOTIONTRG11, UM_BLACK, Tdirclr);
			sect24 = UU_TRUE;
		}
	}
/*
	else
	{
		ud_dispfrm_set_attribs(0, MOTIONTRG10, UM_BLACK, UM_WHITE);
		ud_dispfrm_set_attribs(0, MOTIONTRG11, UM_BLACK, Tdirclr);
	}
*/
	sect25 = UU_TRUE;
	sect26 = UU_TRUE;
	if (TLraptotyp==0)
	{
		ud_dispfrm_set_attribs(0, MOTIONTRG14, UM_BLACK, Tpassclr);
		ud_dispfrm_set_attribs(0, MOTIONTRG13, UM_BLACK, UM_WHITE);
		ud_dispfrm_set_attribs(0, MOTIONTRG16,UM_BLACK, UM_WHITE);
	}
	else 
	{
		nc = (int)strlen(TLraptoval);
		ul_strip_blanks(TLraptoval, &nc);
		if (nc<=0)
		{
			ud_dispfrm_set_attribs(0,MOTIONTRG13,UM_WHITE,UM_RED);
			if (TLraptotyp==2)
				ud_dispfrm_set_attribs(0,MOTIONTRG14,UM_WHITE,UM_RED);
			else
				ud_dispfrm_set_attribs(0, MOTIONTRG14, UM_BLACK, Tpassclr);
			sect25 = UU_FALSE;
		}
		else
		{
			if (TLraptotyp==1)
			{
//temp				if(dpesmill!=0)
//				{
//					ncl_sprintf(SLraptoval,&dpesmill,1);
//					strcpy(TLraptoval,SLraptoval);
//				}
				rval = atof(TLraptoval);
				if (rval<=0)
					sect25 =  UU_FALSE;
				if (sect25) 
				{
					ud_dispfrm_set_attribs(0, MOTIONTRG14, UM_BLACK, Tpassclr);
					ud_dispfrm_set_attribs(0, MOTIONTRG13, UM_BLACK, UM_WHITE);
				}
				else 
				{
					ud_dispfrm_set_attribs(0, MOTIONTRG13, UM_WHITE,UM_RED);
				}
			}
			else
			{
				ud_dispfrm_set_attribs(0, MOTIONTRG14, UM_BLACK, Tpassclr);
				ud_dispfrm_set_attribs(0, MOTIONTRG13, UM_BLACK, UM_WHITE);
			}
		}
		if (TLraptofed==2)
		{
			nc = (int)strlen(TLraptofrv_str);
			ul_strip_blanks(TLraptofrv_str, &nc);
			if (nc<=0)
			{
				ud_dispfrm_set_attribs(0,MOTIONTRG16,UM_WHITE,UM_RED);
				sect26 = UU_FALSE;
			}
			else
			{
				rval = atof(TLraptofrv_str);
				if (rval<=0)
					sect26 =  UU_FALSE;
				if (sect26) 
					ud_dispfrm_set_attribs(0, MOTIONTRG16, UM_BLACK, UM_WHITE);
				else 
				{
					ud_dispfrm_set_attribs(0, MOTIONTRG16,UM_WHITE,UM_RED);
				}
			}
		}
		else
			ud_dispfrm_set_attribs(0, MOTIONTRG16, UM_BLACK, UM_WHITE);
	}
/*
......Entry /Exit
*/
	sect41 = UU_TRUE;
	sect42 = UU_TRUE;
	sect43 = UU_TRUE;
	if (Tstarttyp==1)
	{
		nc = (int)strlen(Tptnam);
		ul_strip_blanks(Tptnam, &nc);
		if (nc<=0)
		{
			ud_dispfrm_set_attribs(0,ENEXTRG3, UM_WHITE, UM_RED);
			ud_dispfrm_set_attribs(0, ENEXTRG2, UM_WHITE, UM_RED);
			sect41 = UU_FALSE;
		}
		else
		{
			ud_dispfrm_set_attribs(0,ENEXTRG3,UM_BLACK,Tstptclr);
			ud_dispfrm_set_attribs(0, ENEXTRG2, UM_BLACK, UM_WHITE);
			sect41 = UU_TRUE;
		}
	}
	else
	{
		ud_dispfrm_set_attribs(0, ENEXTRG2, UM_BLACK, UM_WHITE);
		ud_dispfrm_set_attribs(0, ENEXTRG3, UM_BLACK, Tstptclr);
	}
	if (Traptotyp==0)
	{
		ud_dispfrm_set_attribs(0, ENEXTRG5, UM_BLACK, UM_WHITE);
		ud_dispfrm_set_attribs(0, ENEXTRG6, UM_BLACK, Tclnclr);
		sect42 = UU_TRUE;
	}
	else
	{
		nc = (int)strlen(Traptoval);
		ul_strip_blanks(Traptoval, &nc);
		if (nc<=0)
		{
			ud_dispfrm_set_attribs(0, ENEXTRG5, UM_WHITE, UM_RED);
			if (Traptotyp==2)
				ud_dispfrm_set_attribs(0, ENEXTRG6, UM_WHITE, UM_RED);
			else
				ud_dispfrm_set_attribs(0, ENEXTRG6, UM_BLACK, Tclnclr);
			sect42 = UU_FALSE;
		}
		else
		{
			if (Traptotyp==1)
			{
				rval = atof(Traptoval);
				if (rval<=0)
					sect42 =  UU_FALSE;
			}
			if (sect42) 
			{
				ud_dispfrm_set_attribs(0, ENEXTRG5, UM_BLACK, UM_WHITE);
				ud_dispfrm_set_attribs(0, ENEXTRG6, UM_BLACK, Tclnclr);
			}
			else 
			{
				ud_dispfrm_set_attribs(0, ENEXTRG5,UM_WHITE,UM_RED);
				if (Traptotyp==2)
					ud_dispfrm_set_attribs(0, ENEXTRG6, UM_WHITE, UM_RED);
				else
					ud_dispfrm_set_attribs(0, ENEXTRG6, UM_BLACK, Tclnclr);
			}
		}
		if (Traptofed==2)
		{
			nc = (int)strlen(Traptofrv_str);
			ul_strip_blanks(Traptofrv_str, &nc);
			if (nc<=0)
			{
				ud_dispfrm_set_attribs(0,ENEXTRG8,UM_WHITE,UM_RED);
				sect42 = UU_FALSE;
			}
			else
			{
				rval = atof(Traptofrv_str);
				if (rval<=0)
				{
					sect42 =  UU_FALSE;
					ud_dispfrm_set_attribs(0, ENEXTRG8,UM_WHITE,UM_RED);
				}
				else 
					ud_dispfrm_set_attribs(0, ENEXTRG8, UM_BLACK, UM_WHITE);
			}
		}
		else
			ud_dispfrm_set_attribs(0, ENEXTRG8, UM_BLACK, UM_WHITE);
	}

	if (Tretrcttyp==0)
	{
		ud_dispfrm_set_attribs(0, ENEXTRG10, UM_BLACK, UM_WHITE);
		ud_dispfrm_set_attribs(0, ENEXTRG11, UM_BLACK, Tretclr);
		ud_dispfrm_set_attribs(0, ENEXTRG13, UM_BLACK, UM_WHITE);
		sect43 = UU_TRUE;
	}
	else
	{
		nc = (int)strlen(Tretrctval);
		ul_strip_blanks(Tretrctval, &nc);
		if (nc<=0)
		{
			ud_dispfrm_set_attribs(0, ENEXTRG10, UM_WHITE, UM_RED);
			ud_dispfrm_set_attribs(0, ENEXTRG11, UM_WHITE, UM_RED);
			if (Tretrcttyp==2)
				ud_dispfrm_set_attribs(0, ENEXTRG11, UM_WHITE, UM_RED);
			else
				ud_dispfrm_set_attribs(0, ENEXTRG11, UM_BLACK, Tretclr);
			sect43 = UU_FALSE;
		}
		else
		{
			if (Tretrcttyp==1)
			{
				rval = atof(Tretrctval);
				if (rval<=0)
					sect43 =  UU_FALSE;
			}
			if (sect43) 
			{
				ud_dispfrm_set_attribs(0, ENEXTRG10, UM_BLACK, UM_WHITE);
				ud_dispfrm_set_attribs(0, ENEXTRG11, UM_BLACK, Tretclr);
			}
			else 
			{
				ud_dispfrm_set_attribs(0, ENEXTRG10,UM_WHITE,UM_RED);
				ud_dispfrm_set_attribs(0, ENEXTRG11,UM_WHITE,UM_RED);
				if (Traptotyp==2)
					ud_dispfrm_set_attribs(0, ENEXTRG11, UM_WHITE, UM_RED);
				else
					ud_dispfrm_set_attribs(0, ENEXTRG11, UM_BLACK, Tretclr);
			}
		}
		if (Tretrctfed==2)
		{
			nc = (int)strlen(Tretrctfrv_str);
			ul_strip_blanks(Tretrctfrv_str, &nc);
			if (nc<=0)
			{
				ud_dispfrm_set_attribs(0,ENEXTRG13,UM_WHITE,UM_RED);
				sect43 = UU_FALSE;
			}
			else
			{
				rval = atof(Tretrctfrv_str);
				if (rval<=0)
				{
					sect43 =  UU_FALSE;
					ud_dispfrm_set_attribs(0, ENEXTRG13,UM_WHITE,UM_RED);
				}
				else 
					ud_dispfrm_set_attribs(0, ENEXTRG13, UM_BLACK, UM_WHITE);
			}
		}
		else
			ud_dispfrm_set_attribs(0, ENEXTRG13, UM_BLACK, UM_WHITE);
	}
/*
.....Set section color
*/
	if (sect11)
	{
		if (Sacc[PMill]==0)
		{
			Ssecol[PMill] = Sblack;
			S_section_changed(PMill,UU_FALSE);
		}
		else
		{	
			Ssecol[PMill] = Sgreen; 
			S_section_changed(PMill,UU_TRUE);
		}
	}
	else
	{
		Ssecol[PMill] = Sred; 
		S_section_changed(PMill,UU_FALSE);
	}
	if ((sect2)&&(sect20)&&(sect21)&&(sect22)
		&&(sect23)&&(sect24)&&(sect25)&&(sect26))
	{
		if (Sacc[MotionT]==0)
		{
			Ssecol[MotionT] = Sblack;
			S_section_changed(MotionT,UU_FALSE);
		}
		else
		{	
			Ssecol[MotionT] = Sgreen; 
			S_section_changed(MotionT,UU_TRUE);
		}
	}
	else
	{
		Ssecol[MotionT] = Sred; 
		S_section_changed(MotionT,UU_FALSE);
	}
		
	if (Sacc[Boundary]==0)
	{
		Ssecol[Boundary] = Sblack;
		S_section_changed(Boundary,UU_FALSE);
	}
	else
	{
		Ssecol[Boundary] = Sgreen; 
		S_section_changed(Boundary,UU_TRUE);
	}

	if ((sect41)&&(sect42)&&(sect43))
	{
		if (Sacc[Entry]==0)
		{
			Ssecol[Entry] = Sblack;
			S_section_changed(Entry,UU_FALSE);
		}
		else
		{
			Ssecol[Entry] = Sgreen; 
			S_section_changed(Entry,UU_TRUE);
		}
	}
	else
	{
		Ssecol[Entry] = Sred; 
		S_section_changed(Entry,UU_FALSE);
	}
	if (Sacc[Colors]==0)
	{
		Ssecol[Colors] = Sblack;
		S_section_changed(Colors,UU_FALSE);
	}
	else
	{
		Ssecol[Colors] = Sgreen; 
		S_section_changed(Colors,UU_TRUE);
	}
/*
.....Set Action Buttons
*/
	ifl = (sect11) && (sect2)&&(sect21)&&(sect22)&&(sect23)&&(sect24)&&(sect25)&&(sect26);
	ifl = ifl && (sect41)&&(sect42)&&(sect43);
	ud_frm_enable_ok(ifl);
	ud_set_traverse_mask(FAPV,ifl);
	ud_set_traverse_mask(FAPY,ifl);

	ifl = Sacc[PMill] + Sacc[MotionT] + Sacc[Boundary] + Sacc[Entry] + Sacc[Colors];
	ud_set_traverse_mask(FARS,ifl);
/*
.....if geom entered
*/
	nc8 = UU_LIST_LENGTH(&Ssurf);
	ul_to_upper(Tdirval1);
	strcpy(label, Tdirval1);
	nc1 = (int)strlen(label);
	ul_strip_blanks(label,&nc1);
	nc2 = 0;
/*	if (Tdir==0) */
	{
		ul_to_upper(Tdirval2);
		strcpy(label, Tdirval2);
		nc2 = (int)strlen(label);
		ul_strip_blanks(label,&nc2);
	}
	nc3 = 0;
	if (TLraptotyp==2)
	{
		ul_to_upper(SLraptoval);
		strcpy(label, SLraptoval);
		nc3 = (int)strlen(label);
		ul_strip_blanks(label,&nc3);
	}
	nc5 = 0;
	if (Tstarttyp==1)
	{
		ul_to_upper(Tptnam);
		strcpy(label, Tptnam);
		nc5 = (int)strlen(label);
		ul_strip_blanks(label,&nc5);
	}
	nc6 = 0;
	if (Traptotyp==2)
	{
		ul_to_upper(Traptoval);
		strcpy(label, Traptoval);
		nc6 = (int)strlen(label);
		ul_strip_blanks(label,&nc6);
	}
	nc7 = 0;
	if (Tretrcttyp==2)
	{
		ul_to_upper(Tretrctval);
		strcpy(label, Tretrctval);
		nc7 = (int)strlen(label);
		ul_strip_blanks(label,&nc7);
	}
	if ((nc1>0)||(nc2>0)||(nc3>0)||(nc5>0)
		||(nc6>0)||(nc7>0)||(nc8>0))
	{
		ud_set_traverse_mask(FAGE,1);
	}
	else
		ud_set_traverse_mask(FAGE,0);

	if (sect11)
		ud_set_traverse_mask(MILLRG3, UU_TRUE);
	else
		ud_set_traverse_mask(MILLRG3, UU_FALSE);

	return UU_TRUE;
}

/*********************************************************************
**    I_FUNCTION     : S_form_vis()
**       Redisplays all Rmill forms.
**    PARAMETERS
**       INPUT  :
**          none.
**       OUTPUT :
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_form_vis()
{
	ud_form_vis();
}
/*********************************************************************
**    S_FUNCTION     :  S_unhilite_entity(sfpt)
**       Unhighlights the selected geometry.
**    PARAMETERS
**       INPUT  :
**          sfpt     Pointer to selected geometry structure.
**       OUTPUT :
**          none
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_unhilite_entity(sfpt)
UM_sgeo *sfpt;
{
	struct NCL_fixed_databag e;
/*
.....Save geometry color
*/
	if (sfpt->color != -1)
	{
		if (sfpt->key != 0)
		{
			e.key = sfpt->key;
			if (ncl_retrieve_data_fixed(&e) != 0) return;
			if (sfpt->color == -1) ncl_get_geo_color (e.key,&sfpt->color);
/*
.....Unhighlight entity
*/
			if (Sgeo_redraw) ncl_remove_override_geo(e.key);
			ncl_update_geo_color(e.key,sfpt->color,UU_FALSE);
			uc_display(&e);
			ug_wflush();
		}
	}
/*
.....Reset geometry structure
*/
	sfpt->key = 0;
	sfpt->color = -1;
	sfpt->label[0] = '\0';
}


/*********************************************************************
**    S_FUNCTION     :  S_init_geo(sfpt,label,color)
**       Initializes a picked geometry structure using a user entered
**       label.
**    PARAMETERS
**       INPUT  :
**          sfpt     Pointer to selected geometry structure.
**          label    Label of entity to store.
**          color    Color to highlight the picked entity.
**                   -1 = Don't highlight entity.
**       OUTPUT :
**          none
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_init_geo (sfpt,label,color)
UM_sgeo *sfpt;
char *label;
int color;
{
	int nc;
	UM_f77_str f77_str;
/*
.....Same geometry as picked before
*/
	nc = strlen(label);
	ul_strip_blanks(label,&nc);
	if (strcmp(label,sfpt->label) == 0) return;
/*
.....Unhilite the previous entity
*/
	S_unhilite_entity(sfpt);
/*
.....Store and hilite the new entity
*/
	if (nc != 0)
	{
		UM_init_f77_str(f77_str,label,nc);
		getkey(UM_addr_of_f77_str(f77_str),&sfpt->key);
		strncpy(sfpt->label,label, NCL_MAX_LABEL);
		S_hilite_entity(sfpt,color);
	}
}
/*********************************************************************
**    I_FUNCTION     :  S_hilite_entities(sflst,color)
**       Highlights the selected geometry entities.
**    PARAMETERS
**       INPUT  :
**          sflst    Pointer to list of selected geometry structures.
**          color    Color to highlight entities.
**       OUTPUT :
**          none
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_hilite_entities(sflst,color)
UU_LIST *sflst;
{
	int i;
	UM_sgeo *geo;
/*
.....Loop through list
*/
	geo = (UM_sgeo *)UU_LIST_ARRAY(sflst);
	for (i=0;i<UU_LIST_LENGTH(sflst);i++) S_hilite_entity(&geo[i],color);
}

/*********************************************************************
**    S_FUNCTION     :  S_hilite_entity(sfpt,color)
**       Highlights the selected geometry.
**    PARAMETERS
**       INPUT  :
**          sfpt     Pointer to selected geometry structure.
**          color    Color to highlight the picked entity.
**                   -1 = Don't highlight entity.
**       OUTPUT :
**          none
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_hilite_entity (sfpt,color)
UM_sgeo *sfpt;
int color;
{
	struct NCL_fixed_databag e;
/*
.....Save geometry color
*/
	if (color != -1)
	{
		if (sfpt->key != 0)
		{
			e.key = sfpt->key;
			if (ncl_retrieve_data_fixed(&e) != 0) return;
			if (sfpt->color == -1) ncl_get_geo_color (e.key,&sfpt->color);
/*
.....Highlight entity
*/
			if (Sgeo_redraw) ncl_add_override_geo(e.key);
			ncl_update_geo_color(e.key,color,UU_TRUE);
			uc_display(&e);
			ug_wflush();
		}
	}
}
/*********************************************************************
**    I_FUNCTION     : S_save_form()
**       Saves the Profile Machining form variables.
**    PARAMETERS
**       INPUT  :
**          none.
**       OUTPUT :
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_save_form()
{
/*
.....Save main form settings
*/
	Scolor = Tcolor;
	Sstptclr = Tstptclr;
	Sdirclr = Tdirclr;
	Sclnclr = Tclnclr;
	Sretclr = Tretclr;
	Spassclr = Tpassclr;
	strcpy(Sselsrf, Tselsrf);
	Smethod = Tmethod;
	strcpy(Sstp_str, Tstp_str);
/*	Sdir = Tdir; */
	strcpy(Sdirval1, Tdirval1);
/*	if (Tdir==0) */
	{
		strcpy(Sdirval2, Tdirval2);
	}
	SLraptotyp = TLraptotyp;
	strcpy(SLraptoval, TLraptoval);
	if ((TLraptotyp!=0)&&(TLraptofed==2))
	{
		strcpy(SLraptofrv_str, TLraptofrv_str);
	}
	Sedgetyp = Tedgetyp;
	Signore = Tignore;
	Sstarttyp = Tstarttyp;
	strcpy(Sptnam, Tptnam);
	Sraptotyp = Traptotyp;
	strcpy(Sraptoval, Traptoval);
	Sraptofed = Traptofed;
	if ((Traptotyp!=0)&&(Traptofed==2))
	{
		strcpy(Sraptofrv_str, Traptofrv_str);
	}
	Sretrcttyp = Tretrcttyp;
	strcpy(Sretrctval, Tretrctval);
	Sretrctfed = Tretrctfed;
	if ((Tretrcttyp!=0)&&(Tretrctfed==2))
	{
		strcpy(Sretrctfrv_str, Tretrctfrv_str);
	}
/*
.....Save geometry colors
*/
	UN_unused_geo_flag = Tgeotog;
	UN_unused_geo_color = Tgeocol;
	nclu_save_preview_modals();
}

/*********************************************************************
**    I_FUNCTION     : S_enter_form(fieldno,val,stat)
**       Method called when the Form is first displayed.
**    PARAMETERS
**       INPUT  :
**          fieldno  -1 if routine is called from a form field.
**          val      Current field value.
**          stat     Field status.
**       OUTPUT :
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static UD_FSTAT S_enter_form(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	int i;
/*
.....Set the Section colors
*/
	if (!Serrflg)
	{
		Ssecol[PMill] = Sred;

		ud_frm_enable_ok(UU_FALSE);
		if (*fieldno != -1)
		{
			for (i=PMill;i<=Colors;i++)
				S_section_changed(i,UU_FALSE);
		}
		ud_frm_enable_ok(UU_FALSE);
	}
	else
		S_enable_buttons();
/*
.....Set the mandatory fields to red
*/
//	if (Tseltyp==0)
	{
		ud_dispfrm_set_attribs(0, MILLRG2, UM_WHITE,UM_RED);
	}
/*
.....Set Pick buttons to correct color
*/
	ud_dispfrm_set_attribs(0,CLRRG1,UM_BLACK,Tcolor);
	ud_dispfrm_set_attribs(0,CLRRG2,UM_BLACK,Tstptclr);
	ud_dispfrm_set_attribs(0,CLRRG3,UM_BLACK,Tdirclr);
	ud_dispfrm_set_attribs(0,CLRRG4,UM_BLACK,Tclnclr);
	ud_dispfrm_set_attribs(0,CLRRG5,UM_BLACK,Tretclr);
	ud_dispfrm_set_attribs(0,CLRRG6,UM_BLACK,Tpassclr);
	ud_dispfrm_set_attribs(0,CLRRG8,UM_BLACK,Tgeocol);
	S_enable_buttons();
	return(UD_FLDOK);
}

/*********************************************************************
**    S_FUNCTION     :  S_deselect_all()
**       Deselects all geometry in the Geomtry section.  The associated
**       text fields will be cleared and the geometry will be unhighlighted.
**    PARAMETERS
**       INPUT  : none
**       OUTPUT : none
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_deselect_all()
{
	S_unhilite_all();
/*
.....Initialize geomtry variables
*/
	Sgspt.key = Sgrap.key = Sgret.key = SgLrap.key = 0;
	Sgdrv1.key = Sgdrv2.key = 0;
	Sgspt.color = Sgrap.color = Sgret.color = SgLrap.color = -1;
	Sgdrv1.color = Sgdrv2.color = -1;
	Sgspt.label[0] = Sgrap.label[0] = Sgret.label[0] = SgLrap.label[0] = '\0';
	Sgdrv1.label[0] = Sgdrv2.label[0] = '\0';
	Tdirval1[0] = '\0';
	Tdirval2[0] = '\0';
	ud_update_answer(MOTIONTRG8,(int *)Tdirval1);
	ud_update_answer(MOTIONTRG10,(int *)Tdirval2);
	if (TLraptotyp==2)
	{
		TLraptoval[0] = '\0';			
		ud_update_answer(MOTIONTRG13,(int *)TLraptoval);
	}
	if (Tstarttyp==1)
	{
		Tptnam[0] = '\0';
		ud_update_answer(ENEXTRG2,(int *)Tptnam);
	}
	if (Traptotyp==2)
	{
		Traptoval[0] = '\0';
		ud_update_answer(ENEXTRG5,(int *)Traptoval);
	}
	if (Tretrcttyp==2)
	{
		Tretrctval[0] = '\0';
		ud_update_answer(ENEXTRG10,(int *)Tretrctval);
	}
}
/*********************************************************************
**    S_FUNCTION     :  S_unhilite_all()
**       Unhighlights all geometry entities used in this form.
**    PARAMETERS
**       INPUT  :
**          none
**       OUTPUT :
**          none
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_unhilite_all()
{
	S_unhilite_entities(&Ssurf);
	Snsurf = 0; 
	S_unhilite_entity(&Sgspt);
	S_unhilite_entity(&Sgrap);
	S_unhilite_entity(&Sgret);
	S_unhilite_entity(&SgLrap);
	S_unhilite_entity(&Sgdrv1);
	S_unhilite_entity(&Sgdrv2);
}
/*********************************************************************
**    S_FUNCTION     :  S_unhilite_entities(sflst)
**       Unhighlights the selected geometry entities.
**    PARAMETERS
**       INPUT  :
**          sflst    Pointer to list of selected geometry structures.
**       OUTPUT :
**          none
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_unhilite_entities(sflst)
UU_LIST *sflst;
{
	int i;
	UM_sgeo *geo;
/*
.....Loop through list
*/
	if (Sgeo_init)
	{
		geo = (UM_sgeo *)UU_LIST_ARRAY(sflst);
		for (i=0;i<UU_LIST_LENGTH(sflst);i++) S_unhilite_entity(&geo[i]);
		uu_list_free(sflst);
		Sgeo_init = UU_FALSE;
	}
}

/*********************************************************************
**    I_FUNCTION     : OnAction(fieldno,val,stat)
**       Method called when the View button is pressed.
**    PARAMETERS
**       INPUT  :
**          fieldno  Field number being changed.
**          val      Current field value.
**          stat     Field status.
**       OUTPUT :
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static UD_FSTAT OnAction(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	int status,i,flag= 0;

	switch (*fieldno)
	{
/*
.....Preview command
*/
	case FAPV:
/*
.....Reset motion settings if preview was already pressed
*/
		if (Spreviewflg) moinfr(&flag);
		Spreviewflg = UU_FALSE;
		Schgmade = UU_FALSE;
		Serrflg = 0;
/*
.....Erase last previewed motion
*/
		if (Smptr != UU_NULL) ncl_erase_mdisplay(&Smptr,&Smotatt,Smvpbox);
		Smptr = UU_NULL;
		moinfs();
		ncl_mark_mdisplay(&Smptr,&Smotatt,Smvpbox,UU_TRUE);
		status = S_build_command(UU_FALSE);
		if (status != UU_SUCCESS) 
			moinfr(&flag);
		else
		{
			Spreviewflg = UU_TRUE;
			ud_set_traverse_mask(FAPB,1);
			ud_set_traverse_mask(FAVE,NAUTIPV);
		}
		break;
/*
.....APPLY
.....A curve must be selected
*/
	case FAPY:
/*
........Output command
*/
/*
.....Modified by KC, used the same method as shown in the ngoto.c modified by Eduard
*/
 /*       if (Smptr != UU_NULL) ncl_erase_mdisplay(&Smptr,&Smotatt,Smvpbox);
	    Smptr = UU_NULL;
	    if (Spreviewflg) moinfr(&flag);
        Spreviewflg = UU_FALSE;
*/
		if (Spreviewflg)
		{
			if (!Schgmade && Serrflg == 0) flag = UU_TRUE;
			else flag = UU_FALSE;
			moinfr(&flag);
		}
/*
.....End modification by KC
*/
		status = S_build_command(UU_TRUE);
		Spreviewflg = UU_FALSE;
		Smptr = UU_NULL;
		if (status != UU_SUCCESS) 
		{
			break;
		}
		S_deselect_all();
		for (i=FAPV;i<FAVW;i++) 
			ud_set_traverse_mask(i,0);
		i = -1;
		S_enter_form(&i, val, stat);
		break;
/*
.....Reset form
.....Unselect all geometry
.....Erase Preview motion
*/
	case FARS:
		if (Sgeo_redraw)
			ncl_hide_geo(-1,-1,-1,-1,UU_TRUE,UU_NULL,0);
		S_unhilite_all();
		if (Smptr != UU_NULL) 
			ncl_erase_mdisplay(&Smptr,&Smotatt,Smvpbox);
		Smptr = UU_NULL;
		if (Spreviewflg) moinfr(&flag);
		S_init_form();
		S_enter_form(fieldno,val,stat);
		for (i=FAPV;i<FAVW;i++) ud_set_traverse_mask(i,0);
		S_update_answers();
		Schgmade = Spreviewflg = UU_FALSE;
		Sacc[PMill] = Sacc[MotionT] = Sacc[Boundary] = Sacc[Entry] = Sacc[Colors] = 0;
		break;
/*
.....Playback motion
*/
	case FAPB:
		SfrmPlay = nclu_playback_preview();
/*
..... Added to force mainform displaying back if encountered error
*/
		if (SfrmPlay>0)
		{
			S_form_invis();
			uw_ntdspfrm_vis(SfrmPlay);
		}
		break;
/*
.....Verify motion
*/
	case FAVE:
		S_create_key_list(CONTOUR_KEY);
		SfrmPlay = ul_ipv_playback_preview(&Skey_list,Snkeys);
/*
..... Added to force mainform displaying back if encountered error
*/
		if (SfrmPlay>0)
		{
			S_form_invis();
			uw_ntdspfrm_vis(SfrmPlay);
		}
		break;
/*
.....Toggle geometry display
*/
	case FAGE:
		if (!Sgeo_redraw)
		{
			S_create_key_list(HIDE_KEY);
			ncl_hide_geo(Tgeotog,Tgeocol,UM_DASHSPC_LINE,20,UU_TRUE,UU_NULL,0);
			Sgeo_redraw = UU_TRUE;
		}
		else
		{
			ncl_hide_geo(-1,-1,-1,-1,UU_TRUE,UU_NULL,0);
			Sgeo_redraw = UU_FALSE;
		}
		break;
/*
.....Enter viewing mode
*/
	case FAVW:
		S_form_invis();
		uz_dyn_mouse();
		S_form_vis();
		break;
	}
	S_enable_buttons();
	return(UD_FLDOK);
}

/*********************************************************************
**    I_FUNCTION     : OnColors(fieldno, val, stat)
**			Color change callback.  Changes the color of all entities.
**    PARAMETERS   
**       INPUT  : 
**          fieldno  Field number being changed.
**          val      Current field value.
**          stat     Field status.
**       OUTPUT :  
**          none.
**    RETURNS      : UU_SUCCESS
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static UD_FSTAT OnColors(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	int fno;

	ud_default_method(fieldno, val, stat);
	switch (*fieldno)
	{
	case CLRRG1:
		S_hilite_entities(Ssurf,Tcolor);
		break;
	case CLRRG2:
		S_hilite_entity(&Sgspt,Tstptclr);
		break;
	case CLRRG3:
		S_hilite_entity(&Sgdrv1,Tdirclr);
		S_hilite_entity(&Sgdrv2,Tdirclr);
		break;
	case CLRRG4:
		S_hilite_entity(Sgrap,Tclnclr);
		break;
	case CLRRG5:
		S_hilite_entity(Sgret,Tretclr);
		break;
	case CLRRG6:
		S_hilite_entity(&SgLrap,Tpassclr);
		break;
	case CLRRG7:
		Tgeotog = val->frmint[0];
	case CLRRG8:
		if (Sgeo_redraw)
		{
			Sgeo_redraw = UU_FALSE;
			fno = FAGE;
			OnAction(&fno,val,stat);
		}
		break;
	}
	Sacc[Colors] = 1;
	S_enable_buttons();
	return (UD_FLDOK);
}
/*********************************************************************
**    I_FUNCTION     : OnVideo(fieldno,val,stat)
**       Method called when an Video button is pressed.
**		Video button will play default video file, but we can change the file
**		doing nothing now exepect play default file, but put here in case we need it later
**    PARAMETERS
**       INPUT  :
**          fieldno  Field number being changed.
**          val      Current field value.
**          stat     Field status.
**       OUTPUT :
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static UD_FSTAT OnVideo(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	return(UD_FLDOK);
}
static UD_FSTAT OnPText(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	switch (*fieldno)
	{
		case MILLRG1:
			break;
	}
	Sacc[PMill] = 1;
	S_enable_buttons();
	return(UD_FLDOK);
}

/*********************************************************************
**    S_FUNCTION     : OnDeselect(fieldno, val, stat)
**       Method called when the DeSelect ALL button is pushed.
**    PARAMETERS
**       INPUT  :
**          fieldno  Field number being changed.
**          val      Current field value.
**          stat     Field status.
**       OUTPUT :
**          none
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static UD_FSTAT OnDeselect(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
/*
.....Check for change since preview
*/
	Snsurf = UU_LIST_LENGTH(&Ssurf);
	if (Snsurf > 0)
	{
		S_unhilite_entities(&Ssurf);
		Snsurf = 0;
		if (Spreviewflg) Schgmade = 1;
	}
	ud_set_traverse_mask(MILLRG3, UU_FALSE);
	Tselsrf[0] = '\0';
	ud_update_answer(MILLRG1,&Tselsrf);
	return (UD_FLDOK);
}

static UD_FSTAT OnPButton(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	int pr, *mask;
	int j1 = 0;
	int status;
/*
.....Set the appropriate selection mask and prompt
*/
	if (*fieldno == MILLRG2)
	{
		mask = (int *)UD_ncl_allsfsh;
		pr = 478;
		status = S_select_geo(&Sgsf,&Ssurf,mask,0,pr,Tcolor,0,MILLRG1,Tselsrf);
		Snsurf = UU_LIST_LENGTH(&Ssurf);
		if (Snsurf>0)
			ud_set_traverse_mask(MILLRG3, UU_TRUE);
	}
	else if (*fieldno == MILLRG3)
	{
		OnDeselect(fieldno, val, stat);
		ud_set_traverse_mask(MILLRG3, UU_FALSE);
	}
	Sacc[PMill] = 1;
	S_enable_buttons();
	return(UD_FLDOK);
}

static UD_FSTAT OnMChcPick(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	char valuestr[80];
	switch (*fieldno)
	{
	case MOTIONTRG1:
/*
		if (*(val->frmint) != 2)
		{
			ud_set_traverse_mask(MOTIONTRG12,UU_FALSE);
			ud_set_traverse_mask(MOTIONTRG13,UU_FALSE);
			ud_set_traverse_mask(MOTIONTRG14,UU_FALSE);
			ud_set_traverse_mask(MOTIONTRG15,UU_FALSE);
			ud_set_traverse_mask(MOTIONTRG16,UU_FALSE);
			ud_set_traverse_mask(CLRRG6,UU_FALSE);
		}
		else
		{
			ud_set_traverse_mask(MOTIONTRG12,UU_TRUE);
			if (TLraptotyp==0)
			{
				ud_set_traverse_mask(MOTIONTRG13,UU_FALSE);
				ud_set_traverse_mask(MOTIONTRG14,UU_FALSE);
				ud_set_traverse_mask(CLRRG6,UU_FALSE);
				ud_set_traverse_mask(MOTIONTRG15,UU_FALSE);
				ud_set_traverse_mask(MOTIONTRG16,UU_FALSE);
			}
			else if (TLraptotyp==1)
			{
				ud_set_traverse_mask(MOTIONTRG13,UU_TRUE);
				ud_set_traverse_mask(MOTIONTRG14,UU_FALSE);
				ud_set_traverse_mask(CLRRG6,UU_FALSE);
				ud_set_traverse_mask(MOTIONTRG15,UU_TRUE);
				ud_set_traverse_mask(MOTIONTRG16,UU_TRUE);
			}
			else
			{
				ud_set_traverse_mask(MOTIONTRG13,UU_TRUE);
				ud_set_traverse_mask(MOTIONTRG14,UU_TRUE);
				ud_set_traverse_mask(CLRRG6,UU_TRUE);
				ud_set_traverse_mask(MOTIONTRG15,UU_TRUE);
				ud_set_traverse_mask(MOTIONTRG16,UU_TRUE);
			}
		}
*/
		if (*(val->frmint) == 2) //Arc
		{
			ud_set_display_mask(UD_INPUTF, MOTIONTRG3, 0);
			ud_set_display_mask(UD_INPUTF, MOTIONTRG2, 1);
		}
		else
		{
			ud_set_display_mask(UD_INPUTF, MOTIONTRG2, 0);
			ud_set_display_mask(UD_INPUTF, MOTIONTRG3, 1);
		}
		Smenu_ch[6] = *(val->frmint);
		break;
	case MOTIONTRG5:
		if (*(val->frmint)==0)
		{
			ud_set_traverse_mask(MOTIONTRG6,UU_FALSE);
		}
		else
		{
			ud_set_traverse_mask(MOTIONTRG6,UU_TRUE);
		}
		Smenu_ch[5] = *(val->frmint);
		break;
/*removed
	case MOTIONTRG7:
		if (*(val->frmint)==1)
		{
			ud_set_traverse_mask(MOTIONTRG10,UU_FALSE);
			ud_set_traverse_mask(MOTIONTRG11,UU_FALSE);
		}
		else
		{
			ud_set_traverse_mask(MOTIONTRG10,UU_TRUE);
			ud_set_traverse_mask(MOTIONTRG11,UU_TRUE);
		}
		Smenu_ch[2] = *(val->frmint);
		break;
*/
	case MOTIONTRG12:
		if (*(val->frmint)==0)
		{
			TLraptoval[0] = '\0';	
			ud_update_answer(MOTIONTRG13,(int *)TLraptoval);
			ud_set_traverse_mask(MOTIONTRG13,UU_FALSE);
			ud_set_traverse_mask(MOTIONTRG14,UU_FALSE);
			ud_set_traverse_mask(CLRRG6,UU_FALSE);
			ud_set_traverse_mask(MOTIONTRG15,UU_FALSE);
			ud_set_traverse_mask(MOTIONTRG16,UU_FALSE);
		}
		else if (*(val->frmint)==1)
		{
			strcpy(TLraptoval, "0.0");	
			ud_update_answer(MOTIONTRG13,(int *)TLraptoval);
			ud_set_traverse_mask(MOTIONTRG13,UU_TRUE);
			ud_set_traverse_mask(MOTIONTRG14,UU_FALSE);
			ud_set_traverse_mask(CLRRG6,UU_FALSE);
			ud_set_traverse_mask(MOTIONTRG15,UU_TRUE);
			if (TLraptofed==2)
				ud_set_traverse_mask(MOTIONTRG16,UU_TRUE);
			else
				ud_set_traverse_mask(MOTIONTRG16,UU_FALSE);
		}
		else
		{
			strcpy(TLraptoval, SgLrap.label);	
			ud_update_answer(MOTIONTRG13,(int *)TLraptoval);
			ud_set_traverse_mask(MOTIONTRG13,UU_TRUE);
			ud_set_traverse_mask(MOTIONTRG14,UU_TRUE);
			ud_set_traverse_mask(CLRRG6,UU_TRUE);
			ud_set_traverse_mask(MOTIONTRG15,UU_TRUE);
			if (TLraptofed==2)
				ud_set_traverse_mask(MOTIONTRG16,UU_TRUE);
			else
				ud_set_traverse_mask(MOTIONTRG16,UU_FALSE);
		}
		Smenu_ch[7] = *(val->frmint);
		break;
	case MOTIONTRG15:
		if (*(val->frmint)==2)
		{
			ud_set_traverse_mask(MOTIONTRG16,UU_TRUE);
			strcpy(TLraptofrv_str, Sav_valuestr);
			ud_dispfrm_update_answer(0,MOTIONTRG16,(int *)TLraptofrv_str);
		}
		else
		{
			ud_set_traverse_mask(MOTIONTRG16,UU_FALSE);
			if (*(val->frmint)==0)
			{
				strcpy(valuestr, Sfeed_valuestr);
				if (Ssav_fchc==2)
					strcpy(Sav_valuestr, TLraptofrv_str);
				ud_dispfrm_update_answer(0,MOTIONTRG16,(int *)valuestr);
			}
			if (*(val->frmint)==1)
			{
/*
.....rapid
*/
				if (Ssav_fchc==2)
					strcpy(Sav_valuestr, TLraptofrv_str);
				valuestr[0] = '\0';
				ud_dispfrm_update_answer(0,MOTIONTRG16,(int *)valuestr);
			}
		}
		Smenu_ch[8] = *(val->frmint);
		Ssav_fchc = *(val->frmint);
		break;
	}
	Sacc[MotionT] = 1;
	S_enable_buttons();
	return(UD_FLDOK);
}
static UD_FSTAT OnMText(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	switch(*fieldno)
	{
	case MOTIONTRG3: 
		break;
	}
	Sacc[MotionT] = 1;
	S_enable_buttons();
	return(UD_FLDOK);
	return(UD_FLDOK);
}
static UD_FSTAT OnMButton(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	int pr, namfld, *mask;
	char *namp;
	int status=-1;
	if (*fieldno == MOTIONTRG9)
	{
/*		if (Tdir == 0) */
		{
			mask = (int *)UD_ncl_allsfpl;
			pr = 707;
		}
/*
		else if (Tdir == 1)
		{
		    mask = (int *)UD_ncl_vepvln;
		    pr = 709;
		}
*/
		namp = Tdirval1;
		namfld = MOTIONTRG8;
		status = S_select_geo(&Sgdrv1,UU_NULL,mask,0,pr,Tdirclr,0,namfld,namp);
	}
	else if (*fieldno == MOTIONTRG11)
	{
		mask = (int *)UD_ncl_allsfpl;
		pr = 708;
		namp = Tdirval2;
		namfld = MOTIONTRG10;
		status = S_select_geo(&Sgdrv2,UU_NULL,mask,0,pr,Tdirclr,0,namfld,namp);
	}
	else if (*fieldno == MOTIONTRG14)
	{
		mask = (int *)UD_ncl_allsfpl;
		pr = 663;
		namp = TLraptoval;
		namfld = MOTIONTRG13;
		status = S_select_geo(&SgLrap,UU_NULL,mask,0,pr,Spassclr,0,namfld,namp);
	}
	if (status==0)
	{
		Sacc[MotionT] = 1;
		S_enable_buttons();	
	}
	return(UD_FLDOK);
}

static UD_FSTAT OnBChcPick(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	Sacc[Boundary] = 1;
	S_enable_buttons();	
	return(UD_FLDOK);
}

static UD_FSTAT OnBChkPick(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	Sacc[Boundary] = 1;
	S_enable_buttons();	
	return(UD_FLDOK);
}

static UD_FSTAT OnEChcPick(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	char valuestr[80];
	switch (*fieldno)
	{
	case ENEXTRG1:
		if (*(val->frmint) == 0)
		{
			ud_set_traverse_mask(ENEXTRG2,UU_FALSE);
			ud_set_traverse_mask(ENEXTRG3,UU_FALSE);
		}
		else
		{
			ud_set_traverse_mask(ENEXTRG2,UU_TRUE);
			ud_set_traverse_mask(ENEXTRG3,UU_TRUE);
		}
		Smenu_ch[1] = *(val->frmint);
		break;
	case ENEXTRG4:
		if (*(val->frmint) == 0)
		{
			ud_set_traverse_mask(ENEXTRG5,UU_FALSE);
			ud_set_traverse_mask(ENEXTRG6,UU_FALSE);
			ud_set_traverse_mask(ENEXTRG7,UU_FALSE);
			ud_set_traverse_mask(ENEXTRG8,UU_FALSE);
		}
		else
		{
			ud_set_traverse_mask(ENEXTRG5,UU_TRUE);
			ud_set_traverse_mask(ENEXTRG7,UU_TRUE);
			if (*(val->frmint) == 1)
			{
				ud_set_traverse_mask(ENEXTRG6,UU_FALSE);
				ud_set_traverse_mask(CLRRG4,UU_FALSE);
			}
			else
			{
				ud_set_traverse_mask(ENEXTRG6,UU_TRUE);
				ud_set_traverse_mask(CLRRG4,UU_TRUE);
			}
			if (Traptofed==2)
				ud_set_traverse_mask(ENEXTRG8,UU_TRUE);
			else
				ud_set_traverse_mask(ENEXTRG8,UU_FALSE);
		}
		Smenu_ch[9] = *(val->frmint);
		break;
	case ENEXTRG9:
		if (*(val->frmint) == 0)
		{
			ud_set_traverse_mask(ENEXTRG10,UU_FALSE);
			ud_set_traverse_mask(ENEXTRG11,UU_FALSE);
			ud_set_traverse_mask(ENEXTRG12,UU_FALSE);
			ud_set_traverse_mask(ENEXTRG13,UU_FALSE);
		}
		else
		{
			ud_set_traverse_mask(ENEXTRG10,UU_TRUE);
			ud_set_traverse_mask(ENEXTRG12,UU_TRUE);
			if (*(val->frmint) == 1)
			{
				ud_set_traverse_mask(ENEXTRG11,UU_FALSE);
				ud_set_traverse_mask(CLRRG5,UU_FALSE);
			}
			else
			{
				ud_set_traverse_mask(ENEXTRG11,UU_TRUE);
				ud_set_traverse_mask(CLRRG5,UU_TRUE);
			}
			if (Tretrctfed==2)
				ud_set_traverse_mask(ENEXTRG13,UU_TRUE);
			else
				ud_set_traverse_mask(ENEXTRG13,UU_FALSE);
		}
		Smenu_ch[11] = *(val->frmint);
		break;
	case ENEXTRG7:
		if (*(val->frmint)==2)
		{
			ud_set_traverse_mask(ENEXTRG8,UU_TRUE);
			strcpy(Traptofrv_str, Sav_valuestr1);
			ud_dispfrm_update_answer(0,ENEXTRG8,(int *)Traptofrv_str);
		}
		else
		{
			ud_set_traverse_mask(ENEXTRG8,UU_FALSE);
			if (*(val->frmint)==0)
			{
				strcpy(valuestr, Sfeed_valuestr);
				if (Ssav_fchc1==2)
					strcpy(Sav_valuestr1, Traptofrv_str);
				ud_dispfrm_update_answer(0,ENEXTRG8,(int *)valuestr);
			}
			if (*(val->frmint)==1)
			{
/*
.....rapid
*/
				if (Ssav_fchc1==2)
					strcpy(Sav_valuestr1, Traptofrv_str);
				valuestr[0] = '\0';
				ud_dispfrm_update_answer(0,ENEXTRG8,(int *)valuestr);
			}
		}
		Smenu_ch[10] = *(val->frmint);
		Ssav_fchc1 = *(val->frmint);
		break;
	case ENEXTRG12:
		if (*(val->frmint)==2)
		{
			ud_set_traverse_mask(ENEXTRG13,UU_TRUE);
			strcpy(Tretrctfrv_str, Sav_valuestr2);
			ud_dispfrm_update_answer(0,ENEXTRG13,(int *)Tretrctfrv_str);
		}
		else
		{
			ud_set_traverse_mask(ENEXTRG13,UU_FALSE);
			if (*(val->frmint)==0)
			{
				strcpy(valuestr, Sfeed_valuestr);
				if (Ssav_fchc2==2)
					strcpy(Sav_valuestr2, Tretrctfrv_str);
				ud_dispfrm_update_answer(0,ENEXTRG13,(int *)valuestr);
			}
			if (*(val->frmint)==1)
			{
/*
.....rapid
*/
				if (Ssav_fchc2==2)
					strcpy(Sav_valuestr2, Tretrctfrv_str);
				valuestr[0] = '\0';
				ud_dispfrm_update_answer(0,ENEXTRG13,(int *)valuestr);
			}
		}
		Smenu_ch[12] = *(val->frmint);
		Ssav_fchc2 = *(val->frmint);
		break;
	}
	Sacc[Entry] = 1;
	S_enable_buttons();	
	return(UD_FLDOK);
}
static UD_FSTAT OnEText(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	Sacc[Entry] = 1;
	S_enable_buttons();	
	return(UD_FLDOK);
}
static UD_FSTAT OnEButton(fieldno, val, stat)
int *fieldno;
UD_DDATA *val;
UD_FSTAT stat;
{
	int pr, namfld, *mask;
	char *namp;
	int status=-1;
	if (*fieldno == ENEXTRG3)
	{
		mask = (int *)UD_ncl_pt;
		pr = 658;
		namp = Tptnam;
		namfld = ENEXTRG2;
		status = S_select_geo(&Sgspt,UU_NULL,mask,0,pr,Tstptclr,0,namfld,namp);
	}
	else if (*fieldno == ENEXTRG6)
	{
		mask = (int *)UD_ncl_allsfpl;
		pr = 659;
		namp = Traptoval;
		namfld = ENEXTRG5;
		status = S_select_geo(&Sgrap,UU_NULL,mask,0,pr,Tclnclr,0,namfld,namp);
	}
	else if (*fieldno == ENEXTRG11)
	{
		mask = (int *)UD_ncl_allsfpl;
		pr = 660;
		namp = Tretrctval;
		namfld = ENEXTRG10;
		status = S_select_geo(&Sgret,UU_NULL,mask,0,pr,Tretclr,0,namfld,namp);
	}
	if (status==0)
	{
		Sacc[Entry] = 1;
		S_enable_buttons();	
	}
	return(UD_FLDOK);
}

/*********************************************************************
**    I_FUNCTION     : S_free_repaint (listptr)
*********************************************************************/
/*********************************************************************
**    E_FUNCTION     : S_build_command(flg)
**       Build the PMill statement.
**    PARAMETERS
**       INPUT  : flag    = UU_TRUE = output command to source file.
**			                   UU_FALSE = Preview command only.
**       OUTPUT :
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static int S_build_command(flg)
UU_LOGICAL flg;
{
	int i;
	NCL_cmdbuf cmdbuf;
	char buf[64];

	if (flg)
		NCL_preview_mot = 0;
	else
		NCL_preview_mot = 1;
	Snsurf = UU_LIST_LENGTH(&Ssurf);
	ncl_init_cmdbuf(&cmdbuf);

	if (!flg) ncl_add_token(&cmdbuf, "*", NCL_nocomma);

	ncl_add_token(&cmdbuf, NCL_pmill, NCL_nocomma);

	if (Snsurf > 0)
	{
		UM_sgeo *geo = (UM_sgeo *) UU_LIST_ARRAY(&Ssurf);
		for (i = 0; i < Snsurf; i++)
		{
			ncl_add_token(&cmdbuf, geo[i].label, NCL_comma);
		}
	}
//added edge type back Yurong
	if (Tedgetyp > 0)
	{
		if (Tedgetyp == EDGPAST)
			ncl_add_token(&cmdbuf, NCL_past, NCL_comma);
		else if (Tedgetyp == EDGON)
			ncl_add_token(&cmdbuf, NCL_on, NCL_comma);
		else if (Tedgetyp == CONTCT)
			ncl_add_token(&cmdbuf, NCL_contct, NCL_comma);
	}
	else
		ncl_add_token(&cmdbuf, NCL_to, NCL_comma);

/*	if (Tdir == 0) */
	{		
		if (Tdirval1[0])
			ncl_add_token(&cmdbuf, Tdirval1, NCL_comma);
		if (Tdirval2[0])	
			ncl_add_token(&cmdbuf, Tdirval2, NCL_comma);
	}
/*
	else
	{	
		if (Tdirval1[0])
			ncl_add_token(&cmdbuf, Tdirval1, NCL_comma);
	}
*/
	ncl_add_token(&cmdbuf, NCL_run_step, NCL_comma);
	strcpy(buf, Tstp_str);
	ncl_add_token(&cmdbuf, buf, NCL_comma);

	if (Tstarttyp)
	{
		if (Tstarttyp == 1 && Tptnam[0])
		{
			ncl_add_token(&cmdbuf, NCL_start, NCL_comma);
			ncl_add_token(&cmdbuf, Tptnam, NCL_comma);
		}
	}

	if (Tmethod == 1)
	{
		ncl_add_token(&cmdbuf, NCL_combin, NCL_comma);
	}
	else if (Tmethod == 2)
	{
		ncl_add_token(&cmdbuf, NCL_lace, NCL_comma);
		if (TLraptotyp && TLraptoval[0])
		{
			ncl_add_token(&cmdbuf, TLraptoval, NCL_comma);
			if (TLraptofed == 1)
				ncl_add_token(&cmdbuf, NCL_rapid, NCL_comma);
			else if (TLraptofed == 2)			
				ncl_add_token(&cmdbuf, TLraptofrv_str, NCL_comma);
		}
	}

	if (Ttoltyp > 0)
	{
		ncl_add_token(&cmdbuf, NCL_show_toler, NCL_comma);
		strcpy(buf, Ttoler_str);
		ncl_add_token(&cmdbuf, buf, NCL_comma);
	}

	if (Traptotyp && Traptoval[0])
	{
		ncl_add_token(&cmdbuf, NCL_rapto, NCL_comma);
		ncl_add_token(&cmdbuf, Traptoval, NCL_comma);
		if (Traptofed == 1)
			ncl_add_token(&cmdbuf, NCL_rapid, NCL_comma);
		else if (Traptofed == 2)
			ncl_add_token(&cmdbuf, Traptofrv_str, NCL_comma);
	}

	if (Tretrcttyp && Tretrctval[0])
	{
		ncl_add_token(&cmdbuf, NCL_retrct, NCL_comma);
		ncl_add_token(&cmdbuf, Tretrctval, NCL_comma);
		if (Tretrctfed == 1)
			ncl_add_token(&cmdbuf, NCL_rapid, NCL_comma);
		else if (Tretrctfed == 2)
			ncl_add_token(&cmdbuf, Tretrctfrv_str, NCL_comma);
	}
//added Tignore type back Yurong
	if (Tignore) ncl_add_token(&cmdbuf,"OMIT,IN",NCL_comma);

	ncl_set_cmdmode(UU_TRUE);
	ncl_add_cmdbuf(&cmdbuf);
/*
.....Insert the command at the current line, but do not execute
.......Only need to write the command if Preview was already pressed
.......and no changes were made since the command was already executed
*/
	if (Spreviewflg && !Schgmade) ncl_call_input(&cmdbuf,UU_TRUE);
/*
.....Execute command if a change has been made since the last preview or no
.....preview was created
*/
	else Serrflg = ncl_call(&cmdbuf);

	NCL_preview_mot = 1;
				ud_updatews(UG_SUPPRESS);
				uw_ntflush_paint();
				uw_ntflush_win();

	return 0;
}
/*********************************************************************
**    S_FUNCTION     :  S_storvals()
**       Method called to store current settings as basis for later
**       comparisons.
**    PARAMETERS
**       INPUT  :
**          none
**       OUTPUT :
**          none
**    RETURNS      : UU_SUCCESS
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static UD_FSTAT S_storvals()
{
/*
.....Store values to check for changes  temp for PMILL
*/
	Smenu_ch[1] = Sstarttyp;
/*	Smenu_ch[2] = Sdir; */
	Smenu_ch[5] = Stoltyp;
	Smenu_ch[6] = Smethod;
	Smenu_ch[7] = SLraptotyp;
	Smenu_ch[8] = SLraptofed;;
	Smenu_ch[9] = Sraptotyp;
	Smenu_ch[10] = Sraptofed;
	Smenu_ch[11] = Sretrcttyp;
	Smenu_ch[12] = Sretrctfed;

	return(UD_FLDOK);
}
/*********************************************************************
**    I_FUNCTION     : S_init_form()
**       Initializes the Flowline Milling form variables.
**    PARAMETERS
**       INPUT  :
**          none.
**       OUTPUT :
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_init_form()
{
	UM_real8 tol, feedrate;
	NCLX_mot_feedrate fedrat;

//	UM_real8 pahismill, stessmill,rptsmill,rtrsmill,dpesmill,fresmill,tolsmill, fdrrptsmill, fdrrtrsmill;   
	int sc10_3;
	char buf[10];
/*need get pmill value  all temp values this function
	smillpar(&pahismill, &stessmill,&rptsmill,&rtrsmill,&sc10_3,&dpesmill,&fresmill,&tolsmill, &fdrrptsmill, &fdrrtrsmill );
*/
/*
.....Initialize the form settings
*/
	if (!Spmfrm_init)
	{
		Spmfrm_init = UU_TRUE;
		Snsurf = 0;

		Sstarttyp = 0;
/*		Sdir = 0; */
		Stoltyp = 0;
		Smethod = 2; 
		SLraptotyp = 0;
		SLraptofed = 0;
		Sraptotyp = 0;
		Sraptofed = 0;
		Sretrcttyp = 0;
		Sretrctfed = 0;
		Sstp = 0.0;
//		if (stessmill!=0)
//			Sstp = stessmill;
		Stoler = 0.0;
//		if(tolsmill!=0)
//			Stoler = tolsmill;
		Scolor = NCLX_BROWN;
		Sclnclr = NCLX_LT_BLUE;
		Sstptclr = NCLX_SEA_GREEN;
		Sretclr = NCLX_PINK;
		Spassclr = NCLX_PURPLE;
		Sdirclr = NCLX_GREY;
		strcpy(Sstp_str, "0.01");
//		if (stessmill!=0)
//			ncl_sprintf(Sstp_str, &stessmill,1);
//		ncl_sprintf(Sstp_str, &Sstp,1);
		ncl_sprintf(Stoler_str,&Stoler,1);
	}
/*
.....always empty for surfaces per Ken
*/
	Sptnam[0] = '\0';
	Sraptoval[0] = '\0';
//	ncl_sprintf(Sraptoval,&rptsmill,1);
//	strcpy(Traptoval, Sraptoval);
	Sretrctval[0] = '\0';
//	ncl_sprintf(Sretrctval,&rtrsmill,1);
	strcpy(Tretrctval, Sretrctval);
	
	Sdirval2[0] = '\0';
	Sdirval1[0] = '\0';
	SLraptoval[0] = '\0';
	if (SLraptotyp==1)
	{
//		ncl_sprintf(SLraptoval,&dpesmill,1);
		strcpy(TLraptoval,SLraptoval);
	}
	Stoler = atof(Stoler_str);
	if (Stoler < UM_DFUZZ)
	{
		gettol(&tol);
		Stoler = tol;
	}
	Sstp = atof(Sstp_str);
	if (Sstp < UM_DFUZZ)
	{
		Sstp = 10.*Stoler;
	}
//	if(tolsmill!=0.0)
//		Stoler = tolsmill;
	if (Stoler < UM_DFUZZ)
	{
		gettol(&tol);
		Stoler = tol;
	}
//	if(stessmill!=0)
//		Sstpov = stessmill;
	ncl_sprintf(Sstp_str, &Sstp,1);
	ncl_sprintf(Stoler_str,&Stoler,1);
	Tstarttyp = Sstarttyp;
/*	Tdir = Sdir; */
	Ttoltyp = Stoltyp;
	Tmethod = Smethod; 
	TLraptotyp = SLraptotyp;
	TLraptofed = SLraptofed;
	Traptotyp = Sraptotyp;
	Traptofed = Sraptofed;
	Tretrcttyp = Sretrcttyp;
	Tretrctfed = Sretrctfed;
	strcpy(Ttoler_str, Stoler_str);
	strcpy(Tstp_str, Sstp_str);

	NclxMotGetFeedrate(&fedrat);
	feedrate = fedrat.base_feedrate;
//	ncl_val2str (fdrrptsmill, Sraptofrv_str);
//	ncl_val2str (fdrrtrsmill, Sretrctfrv_str);
//	ncl_val2str (fresmill, SLraptofrv_str);
	strcpy(Sav_valuestr,SLraptofrv_str);
	strcpy(TLraptofrv_str, SLraptofrv_str);

	if (Traptofed == 1)
		Traptofrv_str[0] = '\0';
	else	
		strcpy(Traptofrv_str, Sraptofrv_str);
	if (Tretrctfed == 1)
		Tretrctfrv_str[0] = '\0';
	else
		strcpy(Tretrctfrv_str, Sretrctfrv_str);
	strcpy(Sav_valuestr1,Sraptofrv_str);
	strcpy(Sav_valuestr2,Sretrctfrv_str);

	Tcolor = Scolor;
	Tclnclr = Sclnclr;
	Tstptclr = Sstptclr;
	Tretclr = Sretclr;
	Tpassclr = Spassclr;
	Tdirclr = Sdirclr;
	Tgeotog = UN_unused_geo_flag;
	Tgeocol = UN_unused_geo_color;
}

static void S_init_traverse(display,traverse)
char *display,*traverse;
{	
	int i;
	traverse[MILLRG1] = 1;
//	if (Tseltyp==0)
	{
		traverse[MILLRG2] = 1;
		traverse[CLRRG1] = 1;
	}
/*	else
	{
		traverse[MILLRG2] = 0;
		traverse[CLRRG1] = 0;
	}
*/
	traverse[MOTIONTRG1] = 1;
	if (Tmethod==2)
	{
		traverse[MOTIONTRG12] = 1;
		traverse[MOTIONTRG15] = 1;
		if (TLraptotyp==0)
		{
			traverse[MOTIONTRG13] = 0;
			traverse[MOTIONTRG14] = 0;
			traverse[CLRRG6] = 0;
			traverse[MOTIONTRG15] = 0;
			traverse[MOTIONTRG16] = 0;
		}
		else if (TLraptotyp==1)
		{
			traverse[MOTIONTRG13] = 1;
			traverse[MOTIONTRG14] = 0;
			traverse[CLRRG6] = 0;
			traverse[MOTIONTRG15] = 1;
			traverse[MOTIONTRG16] = 1;
			if (SLraptofed==2)
				traverse[MOTIONTRG16] = 1;
			else
				traverse[MOTIONTRG16] = 0;		}
		else
		{
			traverse[MOTIONTRG13] = 1;
			traverse[MOTIONTRG14] = 1;
			traverse[CLRRG6] = 1;
			traverse[MOTIONTRG15] = 1;
			traverse[MOTIONTRG16] = 1;
			if (SLraptofed==2)
				traverse[MOTIONTRG16] = 1;
			else
				traverse[MOTIONTRG16] = 0;
		}
	}
	else
	{
		traverse[MOTIONTRG12] = 0;
		traverse[MOTIONTRG13] = 0;
		traverse[MOTIONTRG14] = 0;
		traverse[MOTIONTRG15] = 0;
		traverse[MOTIONTRG16] = 0;
		traverse[CLRRG6] = 0;
	}

	traverse[MOTIONTRG2] = 1; 
	traverse[MOTIONTRG5] = 1;
	if (Ttoltyp==0)
		traverse[MOTIONTRG6] = 0;
	else
		traverse[MOTIONTRG6] = 1;
		
/*remove	traverse[MOTIONTRG7] = 0; //plane always */
	traverse[MOTIONTRG8] = 1;
	traverse[MOTIONTRG9] = 1;
/*	if (Tdir == 1)
	{
		traverse[MOTIONTRG10] = 0;
		traverse[MOTIONTRG11] = 0;
	}
	else
*/
	{			
		traverse[MOTIONTRG10] = 1;
		traverse[MOTIONTRG11] = 1;
	}
	traverse[CLRRG3] = 1;
/*
.....Entry/Exit
*/
	traverse[ENEXTRG1] = 1;
	if (Sstarttyp==0)
	{
		traverse[ENEXTRG2] = 0;
		traverse[ENEXTRG3] = 0;
	}
	else
	{
		traverse[ENEXTRG2] = 1;
		traverse[ENEXTRG3] = 1;
	}
	traverse[ENEXTRG4] = 1;
	if (Traptotyp == 0)
	{
		traverse[ENEXTRG5] = 0;
		traverse[ENEXTRG6] = 0;
		traverse[ENEXTRG7] = 0;
		traverse[ENEXTRG8] = 0;
	}
	else 
	{
		traverse[ENEXTRG5] = 1;
		traverse[ENEXTRG7] = 1;
		if (Traptotyp == 1)
		{
			traverse[ENEXTRG6] = 0; 
			traverse[CLRRG4] = 0;
		}
		else
		{
			traverse[ENEXTRG6] = 1; 
			traverse[CLRRG4] = 1;
		}
		if (Traptofed==2)
			traverse[ENEXTRG8] = 1;
		else
			traverse[ENEXTRG8] = 0;
	}

	traverse[ENEXTRG9] = 1;
	if (Tretrcttyp == 0)
	{
		traverse[ENEXTRG10] = 0;
		traverse[ENEXTRG11] = 0;
		traverse[ENEXTRG12] = 0;
		traverse[ENEXTRG13] = 0;
	}
	else 
	{
		traverse[ENEXTRG10] = 1;
		traverse[ENEXTRG12] = 1;
		if (Tretrcttyp == 1)
		{
			traverse[ENEXTRG11] = 0; 
			traverse[CLRRG5] = 0;
		}
		else
		{
			traverse[ENEXTRG11] = 1; 
			traverse[CLRRG5] = 1;
		}
		if (Tretrctfed==2)
			traverse[ENEXTRG8] = 1;
		else
			traverse[ENEXTRG8] = 0;
	}
/*
.....Action item fields
*/
	for (i=FAPV;i<FAVW;i++) traverse[i] = 0; 
	if (Tmethod == 2)
	{
		display[MOTIONTRG2+1] = 1;
		display[MOTIONTRG3+1] = 0;
	}
	else
	{
		display[MOTIONTRG2+1] = 0;
		display[MOTIONTRG3+1] = 1;
	}
}

/*********************************************************************
**    E_FUNCTION     : nclu_pmill()
**       Processes the NCL Port Surface Milling form.
**    PARAMETERS
**       INPUT  :
**          none.
**       OUTPUT :
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
void nclu_pmill()
{
	int flag,ifl,val;
	UU_LOGICAL cmdreject;
	UD_METHOD save_entry;
/*
.....Set up form fields
*/
	static UD_METHOD methods[] = {
/*
.....PMill
*/
		OnPText, OnPButton, OnPButton,
/*
......Motion Type
*/
		OnMChcPick, OnMText, OnMChcPick,
		OnMText, 
		OnMChcPick, OnMText,
		/*OnMChcPick, */ OnMText, OnMButton, 
					OnMText, OnMButton,
		OnMChcPick, OnMText, OnMButton, 
		OnMChcPick, OnMText, 
/*
.....Boundaries
*/
		OnBChcPick, OnBChkPick, 
/*
.....Entry / Exit
*/
		OnEChcPick, OnEText, OnEButton, 
		OnEChcPick, OnEText, OnEButton, 
		OnEChcPick, OnEText,
		OnEChcPick, OnEText, OnEButton, 
		OnEChcPick, OnEText,
/*
.....Colors
*/
		OnColors, OnColors, OnColors, OnColors, 
		OnColors, OnColors, OnColors, 
		OnColors, 
		OnAction,OnAction,OnAction,
		OnAction,OnAction,OnAction,OnAction,OnVideo
	};


	static char traverse[]= {
		1,1,1,
		1,1,1,1,1,1,1,1,1, 
		1,1,1,1,1,1,
		1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1};
	static char called[]  = {
		6,6,6,
		6,6,6,6,6,6,6,6,6, 
		6,6,6,6,6,6,
		6,6,
		6,6,6,6,6,6,6,6,6,6,6,6,6,
		6,6,6,6,6,6,6,6,
		6,6,6,6,6,6,6,6};
	static char display[] = {
		1,1,1,
		1,1,1,1,1,1,1,1,1, 
		1,1,1,1,1,1,
		1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1};
/*
.....Initialize routine
*/
	Serrflg = 0;
	Spreviewflg = 0;
	Schgmade = 0;
/*
.....Initialize form answers
*/
	S_init_form();
	S_storvals();
	Serrflg = 0;
	Spreviewflg = UU_FALSE;
	Schgmade = UU_FALSE;
	save_entry = UD_initfrm_intry;
	SfrmPlay = 0;
	Skey_init = UU_FALSE;
	Snkeys = 0;
	Sacc[PMill] = Sacc[MotionT] = Sacc[Boundary] = Sacc[Entry] = Sacc[Colors] = 0;
/*
.....Trap Reject Op
*/
	UD_MARK(cmdreject,UU_FALSE);
	if (cmdreject != 0) 
		goto done;
/*
..... Initialize answers
*/
	uu_list_init(&Ssurf,sizeof(UM_sgeo),50,50);
	Tselsrf[0] = '\0';
	S_init_traverse(display,traverse);
/*
.....Display the Form
*/
repeat:
	NCL_preview_mot = 1;
	UD_initfrm_intry = S_enter_form;
	Sfrm = ud_form1("npmill.frm", Sanswers, Sanswers,methods,called,display,traverse);
	
	if (Smptr != UU_NULL && (!Spreviewflg || Schgmade || Sfrm == -1))
		ncl_erase_mdisplay(&Smptr,&Smotatt,Smvpbox);
	else if (Spreviewflg)
		ncl_step_displayed(2,0,UU_NULL);
	Smptr = UU_NULL;
/*
.....Free the motion settings created during preview if a change has been
.....made and ok was pressed or if cancel was pressed
*/
	if (Spreviewflg)
	{
		if (!Schgmade && Sfrm != -1 && Serrflg == 0) flag = UU_TRUE;
		else flag = UU_FALSE;
		moinfr(&flag);
	}
	if (Sfrm == -1) goto done;
	Snsurf = UU_LIST_LENGTH(&Ssurf);
/*
.....Save the form settings
*/
	S_save_form();
/*
.....Output the command
*/
	S_build_command(UU_TRUE);
done:;
	if (Sgeo_redraw)
		ncl_hide_geo(-1,-1,-1,-1,UU_TRUE,UU_NULL,0);
	if (Skey_init)
		uu_list_free(&Skey_list);
	Skey_init = UU_FALSE;
	S_unhilite_all();
/*
.....Reset ignore inner boundary flag
*/
//	ifl = 394; val = 0; setifl(&ifl,&val);
	NCL_preview_mot = 0;
	UD_UNMARK(cmdreject);
	return;
}
/*********************************************************************
**    I_FUNCTION     : S_create_key_list(which)
**			Creates the key lists of geometry used in this form.
**    PARAMETERS   
**       INPUT  :
**          which     = HIDE_KEY = Create Override geometry list.  Used
**                      for hiding geometry.
**                      CONTOUR_KEY = Create Contour Stock (local) list.
**       OUTPUT :  
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_create_key_list(which)
int which;
{
	int i, n;
	UM_sgeo *mgeo;
/*
.....Free local key list
*/
	if (which == CONTOUR_KEY && Skey_init)
	{
		UU_LIST_EMPTY(&Skey_list);
		Snkeys = 0;
	}
/*
.....Add all geometry to the list
*/
	n = UU_LIST_LENGTH(&Ssurf);
	mgeo = (UM_sgeo *)UU_LIST_ARRAY(&Ssurf);
	for (i=0;i<n;i++) S_add_key(which,mgeo[i].key);
	S_add_key(which, Sgspt.key);
	S_add_key(which, Sgrap.key);
	S_add_key(which, Sgret.key);
	S_add_key(which, SgLrap.key);
	S_add_key(which, Sgdrv1.key);
	S_add_key(which, Sgdrv2.key);
}
/*********************************************************************
**    I_FUNCTION     : S_add_key(which,key)
**			Adds a key to either the Override_Geo key list or Contour Stock
**       key list.
**    PARAMETERS   
**       INPUT  :
**          which     = HIDE_KEY = Create Override geometry list.  Used
**                      for hiding geometry.
**                      CONTOUR_KEY = Create Contour Stock (local) list.
**          key       = Key to add to the list.
**       OUTPUT :  
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_add_key(which,key)
UU_KEY_ID key;
int which;
{
	int rel;
	if (key != 0)
	{
		if (which == HIDE_KEY) ncl_add_override_geo(key);
		else
		{
			if (!Skey_init)
			{
        		uu_list_init(&Skey_list,sizeof(UU_KEY_ID),50,50);
				Skey_init = UU_TRUE;
			}
			ur_retrieve_data_relnum(key,&rel);
			if (uc_super_class(rel) == UC_SURFACE_CLASS)
			{
				uu_list_push(&Skey_list,&key);
				Snkeys++;
			}
		}
	}
}

/*********************************************************************
**    I_FUNCTION     : S_section_changed(section, reset)
**			Updates all answers in the form.
**    PARAMETERS   
**       INPUT  :
**          section   = Label of section that changed.
**          reset     = UU_TRUE = Enable Reset button.
**       OUTPUT :  
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_section_changed(section,reset)
int section;
UU_LOGICAL reset;
{
	UU_LOGICAL bold;
/*
.....Change color of section label
*/
	bold = Ssecol[section] != Sblack;
	ud_form_section_color(0, Smode[section], Ssecol[section], bold);
/*
.....Enable Reset button
*/
	if (reset) ud_set_traverse_mask(FARS,UU_TRUE);
}

/*********************************************************************
**    I_FUNCTION     : S_form_invis()
**       Takes down all Rmill forms.
**    PARAMETERS
**       INPUT  :
**          none.
**       OUTPUT :
**          none.
**    RETURNS      : none
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_form_invis()
{
	ud_form_invis();
}
/*********************************************************************
**    I_FUNCTION     : S_update_answers()
**			Updates all answers in the form.
**    PARAMETERS   
**       INPUT  :
**          none.
**       OUTPUT :  
**          none.
**    RETURNS      : UU_SUCCESS
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static void S_update_answers()
{
	int i;
	for (i=0;i<sizeof(Sanswers)/sizeof(int *);i++)
		if (Sanswers[i] != UU_NULL) ud_update_answer(i,Sanswers[i]);
}

/*********************************************************************
**    I_FUNCTION     :  S_select_geo(sfpt,sflst,mask,multi,prmno,color,frm,
**                                   fieldno,label)
**       Routine to select geometry for the form.  The associated
**       text field will be updated with the geometry label and
**       the geometry will be highlighted.
**    PARAMETERS
**       INPUT  :
**          mask     Picking mask.
**          multi    0 = Single selection, 1 = multiple selection,
**                   2 = Single selection (calling routine handles invisibling
**                   of form).
**					3: multiple selection, not erase the old selection, but add into it.
**          prmno    Prompt number to use while in pick mode.
**          color    Color to highlight the picked entity.
**                   -1 = Don't highlight entity.
**          frm      Form number that the field resides on. 0 = Main form.
**          fieldno  Text field to update with label of selected entity.
**                   -1 = No field to updated.
**          label    Text buffer that belongs to 'fieldno'.
**       OUTPUT :
**          sfpt     Pointer to selected geometry structure for single entity.
**          sflst    Pointer to selected geometry structure list when
**                   multiple entities can be picked (multi).
**    RETURNS      : UU_SUCCESS if an entity is picked.  UU_FAILURE otherwise.
**    SIDE EFFECTS : none
**    WARNINGS     : none
*********************************************************************/
static int S_select_geo(sfpt,sflst,mask,multi,prmno,color,frm,fieldno,label)
UM_sgeo *sfpt;
UU_LIST *sflst;
unsigned int *mask;
UU_LOGICAL multi;
int prmno,color,fieldno,frm;
char *label;
{
	int numint,iret,nc;
	unsigned int *imask;
	UU_LOGICAL init;
	struct NCL_fixed_databag e;
	UM_PLOCREC pick;
	UU_LOGICAL cmdreject,doend;
	UM_int4 sfkey;
	UM_int2 primtyp;
/*
.....Take down form
*/
	iret = UU_SUCCESS;
	if (multi != 2) S_form_invis();
/*
.....Trap Reject Op
*/
	UD_MARK (cmdreject, UU_TRUE);
	if (cmdreject != 0) goto failed;
/*
.....Set the appropriate selection mask
*/
	imask = mask;
	if (imask == UD_ncl_pl) imask = UD_ncl_allsfpl;
/*
.....Unhighlight the previous selection
*/
	if ((multi != 2)&&(multi != 3))
	{
		if (sfpt != UU_NULL) S_unhilite_entity(sfpt);
		if (sflst != UU_NULL) S_unhilite_entities(sflst);
	}
	else if (multi!=3)
	{
		sfpt->key = 0;
		sfpt->color = -1;
		sfpt->label[0] = '\0';
	}
/*
.....Get the next geometry selection
*/
repeat:;
	do
	{
		doend = UU_TRUE;
		ud_lgeo(UU_TRUE,imask);
/*
.....Single selection
*/
		if ((multi != 1)&&(multi != 3))
		{
			ua_dl_pldas(UD_DASPCKLOC,UA_NCL,prmno,&pick,1,&numint,1);
			if (numint == 0) goto failed;
			e.key = um_get_pickkey(&(pick.pent),1);
/*
........Screen location picked
*/
			if (e.key == 0)
				strcpy(label,pick.ploc.label);
/*
........Check for planar surface
*/
			else
			{
				if (ncl_retrieve_data_fixed(&e) != 0) goto done;
				if (mask == UD_ncl_pl && e.rel_num != NCL_PLN_REL)
				{
					sfkey = e.key;
					ncl_get_sf_primtyp (&sfkey,&primtyp);
					if (primtyp != NCLSF_PLANE)
					{
						ud_wrerr("Entity Picked is not Planar.");
						doend = UU_FALSE;
					}
				}
			}
		}
/*
.....Multiple selection
*/
		else
		{
			ud_ldas(UD_DASSELECT,UA_NCL,prmno,NULL,1,&numint,UD_NODEFAULT);
			if (numint == 0) goto failed;
			doend = UU_TRUE;
		}
	} while (!doend);
/*
.....Single selection
*/
	if ((multi != 1)&&(multi != 3))
	{
/*
........Store the entity's data
*/
		sfpt->key = e.key;
		sfpt->relnum = e.rel_num;
		if (sfpt->key != 0) ncl_get_label(&e,sfpt->label);
		else strcpy(sfpt->label,label);
/*
........Highlight the selected entity
*/
		S_hilite_entity(sfpt,color);
/*
........Update the text field with the entity label
*/
		if (fieldno != -1)
		{
			strcpy(label,sfpt->label);
			if (frm == 0) ud_update_answer(fieldno,(int *)label);
			else ud_dispfrm_update_answer(frm,fieldno,(int *)label);
		}
		if (sflst!=UU_NULL)
		{
			if(sflst->data==UU_NULL)
				uu_list_init(sflst,sizeof(UM_sgeo),numint,10);
			uu_list_push(sflst,sfpt);
			Sgeo_init = UU_TRUE;
		}
	}
/*
.....Multiple selection
*/
	else
	{
/*
........Unhighlight the previous selections
*/
		if (multi != 3)
		{
			S_unhilite_entities(sflst);
		}
/*
........Store the entities' data
*/
		if(sflst->data==UU_NULL)
			uu_list_init(sflst,sizeof(UM_sgeo),numint,10);
		Sgeo_init = UU_TRUE;
		init = UU_TRUE;
		while (ud_gnxt(init,UU_NULL,&e.key,1))
		{
			init = UU_FALSE;
			if (e.key != 0)
			{
				if (ncl_retrieve_data_fixed(&e) != 0) goto done;
				sfpt->key = e.key;
				sfpt->relnum = e.rel_num;
				sfpt->color = -1;
				ncl_get_label(&e,sfpt->label);
/*
........CADD Text is not allowed
*/
				nc = (int)strlen(sfpt->label);
				ul_strip_blanks(sfpt->label,&nc);
/*
........Highlight the selected entity
*/
				if (nc != 0)
				{
					S_hilite_entity(sfpt,color);
/*
........Push the entity onto the stack
*/
					uu_list_push(sflst,sfpt);
				}
			}
		}
/*
........No entities selected
*/
		if (UU_LIST_LENGTH(sflst) == 0)
		{
			ud_wrerr("No CAM entities selected.");
			uu_list_free(sflst);
			goto repeat;
		}
/*
........Update the text field with the entity label
*/
		else if (fieldno != -1)
		{
			sfpt = (UM_sgeo *)UU_LIST_ARRAY(sflst);
			strcpy(label,sfpt->label);
			if (UU_LIST_LENGTH(sflst) > 1) strcat(label,",...");
			if (frm == 0) ud_update_answer(fieldno,(int *)label);
			else ud_dispfrm_update_answer(frm,fieldno,(int *)label);
		}
	}
/*
.....End of routine
.....Redisplay form
*/
done:;
	ud_unlimit();
	if (multi != 2) S_form_vis();
	UD_UNMARK(cmdreject);
	return(iret);
/*
.....User did not select anything
*/
failed:
	iret = UU_FAILURE;
	goto done;
}