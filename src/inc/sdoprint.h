/********************************************************************* 
**  CONTAINS:
**       Macros for true double precision implementation on Iris 3130
**       developed by Silicon Graphics.   Used by sdoprnt.c and sdoscan.c
**
**  COPYRIGHT  1988  UNICAD, Inc.
**  MODULE NAME AND RELEASE LEVEL 
**       sdoprint.h , 25.1
**  DATE AND TIME OF LAST MODIFICATION
**       04/29/15 , 15:06:51
**
*********************************************************************/
/* Maximum number of digits in any integer representation */
#define MAXDIGS 11

/* Maximum total number of digitis in E format */
#define MAXECVT 17

/* Maximum number of digits after decimal point in F format */
#define MAXFCVT 60

/* Maximum siginificant figures in a floating-point number */
#define MAXFSIG 17

/* Maximum number of characters in an exponent */
#if u3b || m68000
#define MAXESIZ 5
#else
#define MAXESIZ 4
#endif

/* Maximum (positive) exponent */
#if u3b || m68000
#define MAXEXP 310 
#else
#define MAXEXP 40 
#endif

/* Data type for flags */
typedef char bool;

/* Convert a digit character to the corresponding number */
#define tonumber(x) ((x)-'0')

/* Convert a number between 0 and 9 to the corresponding digit */
#define todigit(x) ((x)+'0')

/* Max and Min macros */
#define max(a,b) ((a) > (b)? (a): (b))
#define min(a,b) ((a) < (b)? (a): (b))
