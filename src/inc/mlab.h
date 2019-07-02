/*********************************************************************
**    NAME         :  mlab.h
**       CONTAINS:
**    DATE AND TIME OF LAST MODIFICATION
**       04/29/15 , 15:06:31
**    DATE AND TIME OF LAST MODIFICATION
**       04/29/15 , 15:06:31
*********************************************************************/
#ifndef UM_LABEL

#include "mlabddl.h"

#ifdef  UM_MPGM
#define EXT
#else
#define EXT extern
#endif

#define UM_AUTO_LABEL 0
#define UM_USER_LABEL 1
#define UM_NO_LABEL	 2

EXT int UM_label_mode;

#undef EXT

#define UM_LABEL
#endif
