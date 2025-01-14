/********************************************************************* 
**  FUNCTION:  
**        _doscan:   replacement for scanf written by Silicon
**        Graphics to support double precision scanning in a way 
**        compatible with standard C implementations  
**
**  COPYRIGHT  1988  UNICAD, Inc.
**  MODULE NAME AND RELEASE LEVEL 
**       sdoscan.c , 25.1
**  DATE AND TIME OF LAST MODIFICATION
**       04/29/15 , 15:11:08
**
**  PARAMETERS   
**      INPUT:  
**
**  RETURNS      :  
**  SIDE EFFECTS :  
**  WARNINGS     :  
*********************************************************************/

#include "usysdef.h"
#if UU_COMP==UU_IRIS && UU_DOUBLE
/********************************************************************/
/**                  SGI CODE                                       */
/********************************************************************/
/*LINTLIBRARY*/

/*	altered to allow caps to distinguish between
	single- and double-precision floating point 
	arguments as well as preceeding with 'l'.
	9/19/83 (GB)
*/
#include <stdio.h>
#include <ctype.h>
#include <varargs.h>
#include <values.h>

#define NCHARS	(1 << BITSPERBYTE)

extern long float _latof();
extern char *memset();
extern int ungetc();

int
_doscan(iop, fmt, va_alist)
register FILE *iop;
register unsigned char *fmt;
va_list va_alist;
{
	extern unsigned char *setup();
	char tab[NCHARS];
	register int ch;
	int nmatch = 0, len, inchar, stow, size;
	/*******************************************************
	 * Main loop: reads format to determine a pattern,
	 *		and then goes to read input stream
	 *		in attempt to match the pattern.
	 *******************************************************/
	for( ; ; ) {
		if((ch = *fmt++) == '\0')
			return(nmatch); /* end of format */
		if(isspace(ch)) {
			while(isspace(inchar = getc(iop)))
				;
			if(ungetc(inchar, iop) != EOF)
				continue;
			break;
		}
		if(ch != '%' || (ch = *fmt++) == '%') {
			if((inchar = getc(iop)) == ch)
				continue;
			if(ungetc(inchar, iop) != EOF)
				return(nmatch); /* failed to match input */
			break;
		}
		if(ch == '*') {
			stow = 0;
			ch = *fmt++;
		} else
			stow = 1;

		for(len = 0; isdigit(ch); ch = *fmt++)
			len = len * 10 + ch - '0';
		if(len == 0)
			len = MAXINT;

		if((size = ch) == 'l' || size == 'h')
			ch = *fmt++;
		if(ch == '\0' ||
		    ch == '[' && (fmt = setup(fmt, tab)) == NULL)
			return(EOF); /* unexpected end of format */
		if(isupper(ch)) { /* no longer documented */
			size = 'l';
			ch = _tolower(ch);
		}
		if(ch != 'c' && ch != '[') {
			while(isspace(inchar = getc(iop)))
				;
			if(ungetc(inchar, iop) == EOF)
				break;
		}
		if((size = (ch == 'c' || ch == 's' || ch == '[') ?
		    string(stow, ch, len, tab, iop, &va_alist) :
		    number(stow, ch, len, size, iop, &va_alist)) != 0)
			nmatch += stow;
		if(va_alist == NULL) /* end of input */
			break;
		if(size == 0)
			return(nmatch); /* failed to match input */
	}
	return(nmatch != 0 ? nmatch : EOF); /* end of input */
}

/***************************************************************
 * Functions to read the input stream in an attempt to match incoming
 * data to the current pattern from the main loop of _doscan().
 ***************************************************************/
static int
number(stow, type, len, size, iop, listp)
int stow, type, len, size;
register FILE *iop;
va_list *listp;
{
	char numbuf[64];
	register char *np = numbuf;
	register int c, base;
	int digitseen = 0, dotseen = 0, expseen = 0, floater = 0, negflg = 0;
	long lcval = 0;

	switch(type) {
/** SGI **/
	case 'e':
	case 'f':
	case 'g':
		floater++;
	case 'd':
	case 'u':
		base = 10;
		break;
	case 'o':
		base = 8;
		break;
	case 'x':
		base = 16;
		break;
	default:
		return(0); /* unrecognized conversion character */
	}
	switch(c = getc(iop)) {
	case '-':
		negflg++;
	case '+': /* fall-through */
		len--;
		c = getc(iop);
	}
	for( ; --len >= 0; *np++ = c, c = getc(iop)) {
		if(isdigit(c) || base == 16 && isxdigit(c)) {
			int digit = c - (isdigit(c) ? '0' :
			    isupper(c) ? 'A' - 10 : 'a' - 10);
			if(digit >= base)
				break;
			if(stow && !floater)
				lcval = base * lcval + digit;
			digitseen++;
			continue;
		}
		if(!floater)
			break;
		if(c == '.' && !dotseen++)
			continue;
		if((c == 'e' || c == 'E') && digitseen && !expseen++) {
			*np++ = c;
			c = getc(iop);
			if(isdigit(c) || c == '+' || c == '-')
				continue;
		}
		break;
	}
	if(stow && digitseen)
		if(floater) {
			register long float dval;
			*np = '\0';
			dval = _latof(numbuf);
			if(negflg)
				dval = -dval;
size = 'l';
			if(size == 'l')
				*va_arg(*listp, long float *) = dval;
			else
				*va_arg(*listp, float *) = (float)dval;
		} else {
			/* suppress possible overflow on 2's-comp negation */
			if(negflg && lcval != HIBITL)
				lcval = -lcval;
			if(size == 'l')
				*va_arg(*listp, long *) = lcval;
			else if(size == 'h')
				*va_arg(*listp, short *) = (short)lcval;
			else
				*va_arg(*listp, int *) = (int)lcval;
		}
	if(ungetc(c, iop) == EOF)
		*listp = NULL; /* end of input */
	return(digitseen); /* successful match if non-zero */
}

static int
string(stow, type, len, tab, iop, listp)
register int stow, type, len;
register char *tab;
register FILE *iop;
va_list *listp;
{
	register int ch;
	register char *ptr;
	char *start;

	start = ptr = stow ? va_arg(*listp, char *) : NULL;
	if(type == 'c' && len == MAXINT)
		len = 1;
	while((ch = getc(iop)) != EOF &&
	    !(type == 's' && isspace(ch) || type == '[' && tab[ch])) {
		if(stow)
			*ptr = ch;
		ptr++;
		if(--len <= 0)
			break;
	}
	if(ch == EOF || len > 0 && ungetc(ch, iop) == EOF)
		*listp = NULL; /* end of input */
	if(ptr == start)
		return(0); /* no match */
	if(stow && type != 'c')
		*ptr = '\0';
	return(1); /* successful match */
}

static unsigned char *
setup(fmt, tab)
register unsigned char *fmt;
register char *tab;
{
	register int b, c, d, t = 0;

	if(*fmt == '^') {
		t++;
		fmt++;
	}
	(void)memset(tab, !t, NCHARS);
	if((c = *fmt) == ']' || c == '-') { /* first char is special */
		tab[c] = t;
		fmt++;
	}
	while((c = *fmt++) != ']') {
		if(c == '\0')
			return(NULL); /* unexpected end of format */
		if(c == '-' && (d = *fmt) != ']' && (b = fmt[-2]) < d) {
			(void)memset(&tab[b], t, d - b + 1);
			fmt++;
		} else
			tab[c] = t;
	}
	return(fmt);
}
#endif
