/*****************************************************************************
  FileName:        integer.h
  Processor:       PIC32MM0256GPM048
  Compiler:        XC32 ver 2.10
  IDE :            MPLABX-IDE 5.10
  Created by:      http://strefapic.blogspot.com
 ******************************************************************************/
/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef _INTEGER

#if 0
#include <windows.h>
#else

/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef signed char		CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

/* Boolean type */
typedef enum { FALSE = 0, TRUE } BOOL;

#endif

#define _INTEGER
#endif
