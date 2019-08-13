/*********************************************************************
**
**    NAME         :  nmodify.pmu
**
**       CONTAINS:
**         ncl pop-up menus.				
**  NOTE: when adding a pop-up menu, the index for that pop-up
**        must be entered in the file nclinp.h in the inc directory. 
**        Changes to this include file require that 
**
**    MODULE NAME AND RELEASE LEVEL 
**       nmodfy.pmu , 21.2
**    DATE AND TIME OF LAST MODIFICATION
**       01/20/10 , 13:51:18
**
*********************************************************************/
#include   "dasg.h"

char	*pop_nmodfy[] = {
"X-Y MODIFIER",
"XLARGE",
"XSMALL",
"YLARGE",
"YSMALL",
"X-Y-Z MODIFIER",
"XLARGE",
"XSMALL",
"YLARGE",
"YSMALL",
"ZLARGE",
"ZSMALL",
"XYZ DIRECTION",
"POSX",
"NEGX",
"POSY",
"NEGY",
"POSZ",
"NEGZ",
"LINE RELATION",
"RIGHT",
"LEFT",
"WHICH AXIS",
"XAXIS",
"YAXIS",
"WHICH LINE",
"XAXIS",
"YAXIS",
"LINE",
"CIRCLE SIZE",
"LARGE",
"SMALL",
"CIRCLE RELATION",
"IN",
"OUT",
"VECTOR OPERATION",
"PLUS",
"MINUS",
"ROTATION PLANE",
"XY PLANE",
"YZ PLANE",
"ZX PLANE",
"CS CONDITION",
"TO",
".......NEARPT",
"ON",
".......NEARPT",
"PAST",
".......NEARPT",
"TANTO",
".......NEARPT",
"PSTAN",
".......NEARPT",
"TOOL RELATION",
"TLLFT",
"TLON",
"TLRGT",
"TLOFPS",
"TLONPS",
"DS CONDITION",
"TO",
"ON",
"PAST",
"ZSURF",
"VALUE",
"PLANE",
"NOMORE",
"REFSYS",
"MATRIX",
"NOMORE",
"WP",
"INDIRx",
"INDIRP",
"_",
"INDIRV/VE",
"_",
"INDIRV/POSX",
"INDIRV/POSY",
"INDIRV/POSZ",
"INDIRV/NEGX",
"INDIRV/NEGY",
"INDIRV/NEGZ",
"_",
"SRFVCT/",
"SAVE/LOAD",
"SAVEPP",
"LOADPP",
"FEDRAT AT",
"ONCE",
"CONTINUOUS",
"EDIT",
"DELETE",
"FIND",
"FINDTK",
"INPUT",
"INSERT",
"SKIP",
"SHOW SRC",
"SKIP",
"*SKIP/-1",
"*SKIP/+1",
"NUM of LINES",
"TO",
"TO,END",
"SHOW SRC",
"*",
"LN NUM",
"SCROLL",
"SET",
"ADISPL",
"APTSRC",
"AUTOST",
"AUTOUV",
"CASE",
"DISPLY",
"INDENT",
"LABEL",
"MOTION",
"PAUSE",
"STOP",
"INDENT",
"ALL",
"SEP",
"OFF",
"RESET",
"APTSRC",
"AUTOST",
"AUTOUV",
"CALL",
"CASE",
"DISPLY",
"INDENT",
"LABEL",
"MOTION",
"PAUSE",
"STOP",
"RUN",
"EOF",
"TO LN NUM",
"SHOW",
"GEO",
"CUTTER",
"FILE NAMES:",
"SHOW SRC",
"THICK",
"TOLER",
"TOOL",
"CLW CCLW",
"CLW",
"CCLW",
"LABELS ON/OFF",
"DRAW LABELS",
"ERASE LABELS",
"CHOOSE GEOMETRY TYPE",
"POINT",
"VECTOR",
"LINE",
"PLANE",
"CIRCLE",
"CURVE",
"SURFACE",
"PATERN",
"SHAPE",
"SOLID",
"ALL",
"MULTAX ON/OFF",
"ON",
"OFF",
"CHOOSE COLOR",
"WHITE",
"YELLOW",
"BLUE",
"RED",
"GREEN",
"MAGENTA",
"CYAN",
"DEFAULT",
"BROWN",
"TAN",
"LT BLUE",
"SEA GREEN",
"ORANGE",
"PINK",
"PURPLE",
"GREY",
"CHOOSE LINE STYLE",
"SOLID",
"SMALL DASHED",
"DOTS",
"CENTER LINE",
"PHANTOM",
"LARGE DASHED",
"DASH DOT",
"DASH SPACE",
"CHOOSE LAYER NO.",
"1",
"2",
"3",
"4",
"5",
"10",
"20",
"30",
"40",
"50",
"SPECIFY",
"PORTION TO KEEP",
"XLARGE",
"XSMALL",
"YLARGE",
"YSMALL",
"INTERSECTION MOD",
"XLARGE",
"XSMALL",
"YLARGE",
"YSMALL",
"DIRECTION TO KEEP",
"CLW",
"CCLW",
"TYPE TO CHOOSE",
"POINT",
"LINE",
"CIRCLE",
"PLANE",
"VECTOR",
"PNTVEC",
"MATRIX",
"CURVE",
"PATERN",
"SURFACE",
"SHAPE",
"SOLID",
"GOTO PATERN",
"INVERS",
"CONST",
"AVOID",
"RETAIN",
"OMIT",
"PATERN INCREMENT",
"INCR",
"INCR AT",
"SELECT GEOMETRY TYPES",
"POINTS",
"LINES",
"ARCS/CIRCLES",
"PLANES",
"VECTORS",
"POINT VECTORS",
"ALL CURVES",
"NCL CURVES",
"COMPOSITE CURVES",
"B-SPLINES",
"SURF SPLINES",
"CONICS",
"PATERNS",
"ALL SURFACES",
"NCL SURFACES",
"N SURFACES",
"REV SURFACES",
"MESH SURFACES",
"QUILT SURFACES",
"NET SURFACES",
"TRIMMED SURFACES",
"DRAFTING",
"SHAPES",
"MATRIX",
"SOLIDS",
"ANOTES",
"SHAPE MODIFIER",
"CLW",
"CCLW",
"CS MODIFIER",
"TO",
"ON",
"PAST",
"EDGE OF SURFACE",
"U = 0",
"U = 1",
"V = 0",
"V = 1",
"CHANGE VIEW",
"VIEW PARAMETERS",
"CURRENT TRACUT SYSTEM",
"CURRENT REFSYS SYSTEM",
"A PREDEFINED MATRIX",
"VIEW AXIS",
"XAXIS",
"YAXIS",
"ZAXIS",
"PERIMETER POSITION",
"IN",
"OUT",
"ON",
"FILLET RADIUS TYPE",
"SCALAR VALUES",
"CURVE",
"LIMIT GEOMETRY TYPES",
"POINTS",
"LINES",
"ARCS/CIRCLES",
"PLANES",
"VECTORS",
"POINT VECTORS",
"ALL CURVES",
"NCL CURVES",
"COMPOSITE CURVES",
"B-SPLINES",
"SURF SPLINES",
"CONICS",
"PATERNS",
"ALL SURFACES",
"NCL SURFACES",
"N SURFACES",
"REV SURFACES",
"MESH SURFACES",
"QUILT SURFACES",
"NET SURFACES",
"TRIMMED SURFACES",
"DRAFTING",
"SHAPES",
"FEATURES",
"MATRIX",
"SOLIDS",
"ANOTES",
"PICK MARK METHOD",
"HILITE",
"DIAMOND",
"NO MARK",
"APTSRC",
"CIRCUL",
"COMMENT",
"CUTTER",
"IPV",
"REMARK",
"TRACUT",
"VERIFY",
"APT CUTTER",
"APT",
"NCL",
"PPRINT",
"REDEF CURVE",
"CLOSE",
"OPEN",
"REDEF SURFACE",
"CLOSE IN U",
"CLOSE IN V",
"OPEN IN U",
"OPEN IN V",
"WRAP NOWRAP",
"WRAP",
"NOWRAP",
"REVOLVE",
"RADIAL",
"ATTACH POINT",
"START",
"MIDDLE",
"END",
"CENTER",
"AT",
"PROJ DIR",
"VECTOR",
"ANGLE(S)",
"NORMAL",
"DRIVE SRFVCT",
"SRFVCT/VE",
"SRFVCT/POSX",
"SRFVCT/POSY",
"SRFVCT/POSZ",
"SRFVCT/NEGX",
"SRFVCT/NEGY",
"SRFVCT/NEGZ",
"CHECK SRFVCT",
"SRFVCT/VE",
"SRFVCT/POSX",
"SRFVCT/POSY",
"SRFVCT/POSZ",
"SRFVCT/NEGX",
"SRFVCT/NEGY",
"SRFVCT/NEGZ",
"NCLMODE",
"NCLCAM",
"DRAWING",
"UNITS",
"Inches",
"Millimeters",
"INPUT_MODE",
"Insert",
"Overwrite",
"GENPTS TYPE",
"Forward Vectors",
"Tool Axis Vectors",
"Both Vectors",
"POINTVEC TANTO/PERPTO",
"Tanto",
"Perpto",
"POINTVEC ON/Off",
"On",
"Off",
"GET/PUT GEOMETRY TYPES",
"POINT",
"POINT-VECTOR",
"VECTOR",
"LINE",
"CIRCLE",
"PLANE",
"CURVE",
"SURF",
"PATERN",
"MATRIX",
"SOLID",
"CURVE OUT",
"Single",
"All",
"Thru",
"X-Y-Z or VECTOR",
"XLARGE",
"XSMALL",
"YLARGE",
"YSMALL",
"ZLARGE",
"ZSMALL",
"VECTOR",
"PARAM or PERCNT",
"Param",
"Percent",
"ALL or PLANAR",
"ALL",
"PLANAR",
"INTOF",
"Single",
"All",
"CURVE INTOF",
"Single",
"All",
"Nearpt",
};

UD_POPUPREC	nmodfy[]={
{5,&pop_nmodfy[0]},{7,&pop_nmodfy[5]},{7,&pop_nmodfy[12]},{3,&pop_nmodfy[19]},
{3,&pop_nmodfy[22]},{4,&pop_nmodfy[25]},{3,&pop_nmodfy[29]},
{3,&pop_nmodfy[32]},{3,&pop_nmodfy[35]},{4,&pop_nmodfy[38]},
{11,&pop_nmodfy[42]},{6,&pop_nmodfy[53]},{4,&pop_nmodfy[59]},
{4,&pop_nmodfy[63]},{4,&pop_nmodfy[67]},{13,&pop_nmodfy[71]},
{3,&pop_nmodfy[84]},{3,&pop_nmodfy[87]},{8,&pop_nmodfy[90]},
{6,&pop_nmodfy[98]},{4,&pop_nmodfy[104]},{12,&pop_nmodfy[108]},
{4,&pop_nmodfy[120]},{12,&pop_nmodfy[124]},{3,&pop_nmodfy[136]},
{8,&pop_nmodfy[139]},{3,&pop_nmodfy[147]},{3,&pop_nmodfy[150]},
{12,&pop_nmodfy[153]},{3,&pop_nmodfy[165]},{17,&pop_nmodfy[168]},
{9,&pop_nmodfy[185]},{12,&pop_nmodfy[194]},{5,&pop_nmodfy[206]},
{5,&pop_nmodfy[211]},{3,&pop_nmodfy[216]},{13,&pop_nmodfy[219]},
{6,&pop_nmodfy[232]},{3,&pop_nmodfy[238]},{27,&pop_nmodfy[241]},
{3,&pop_nmodfy[268]},{4,&pop_nmodfy[271]},{5,&pop_nmodfy[275]},
{5,&pop_nmodfy[280]},{4,&pop_nmodfy[285]},{4,&pop_nmodfy[289]},
{3,&pop_nmodfy[293]},{28,&pop_nmodfy[296]},{4,&pop_nmodfy[324]},
{8,&pop_nmodfy[328]},{4,&pop_nmodfy[336]},{3,&pop_nmodfy[340]},
{5,&pop_nmodfy[343]},{5,&pop_nmodfy[348]},{6,&pop_nmodfy[353]},
{4,&pop_nmodfy[359]},{8,&pop_nmodfy[363]},{8,&pop_nmodfy[371]},
{3,&pop_nmodfy[379]},{3,&pop_nmodfy[382]},{3,&pop_nmodfy[385]},
{4,&pop_nmodfy[388]},{3,&pop_nmodfy[392]},{3,&pop_nmodfy[395]},
{12,&pop_nmodfy[398]},{4,&pop_nmodfy[410]},{8,&pop_nmodfy[414]},
{3,&pop_nmodfy[422]},{3,&pop_nmodfy[425]},{3,&pop_nmodfy[428]},
{4,&pop_nmodfy[431]},};

nmodfy_pop()
{ return; }