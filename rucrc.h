/* rucrc.h - rucrc random number generator header file Version 0.1.0 */
/* Copyright (C) 2021 aquila57 at github.com */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

/* The subroutines below are called billions of times     */
/* in a single run.                                       */
/* Parameters to the subroutines must be validated by     */
/* the calling program, to maximize efficiency            */
/* and minimize redundant editing.                        */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <math.h>

typedef struct rustruct {
   int states;                /* number of states = 16384 */
   unsigned int seed;         /* RANDU seed */
   unsigned int octet;        /* hi order 8 bits of seed */
   unsigned int crc;          /* crc based on seed */
   unsigned int crctbl[256];  /* 32 bit crc table */
   unsigned int ofst;         /* offset into state array */
   unsigned int out;          /* current output state */
   unsigned int prev;         /* prev output state */
   unsigned int pprev;        /* prev prev output state */
   double maxint;             /* 2^32 */
   unsigned int *state;       /* state array of 1024 members */
   } rufmt;

#define STATES (16384)

#define EMM (65539)

#define POLY (0xEDB88320)

#define MASK (0xffffffff)

#define OCTETMSK (0x000000ff)

#define RANDU (ru->seed *= EMM)

#define OCTET (ru->octet = ru->seed >> 24)

#define UPDTCRC (ru->crc = (ru->crc >> 8) ^ \
   ru->crctbl[(ru->crc ^ ru->octet) & OCTETMSK])

#define RND (RANDU, OCTET, UPDTCRC)

#define MAXINT (65536.0 * 65536.0)

rufmt *rucrcinit(void);                 /* initialization routine */
rufmt *rucrcstrt(unsigned int seed);    /* initialization routine */
void bldcrctbl(unsigned int *tbl);      /* buile crc32 table */
unsigned int rucrc(rufmt *ru);          /* random uint generator */
int rucrcbit(rufmt *ru);                /* random bit generator */
double rucrcunif(rufmt *ru);            /* random uniform number 0-1 */
double rucrcfrac(rufmt *ru);            /* random uniform number 0-1 */
int rucrcint(rufmt *ru, int limit);     /* random integer 0 up to limit */
unsigned int rucrcpwr(rufmt *ru, int bits); /* random # 1-32 bits */
void rucrcdspl(rufmt *ru, int option);    /* display rucrc state */
void rucrcabt(void);                    /* rucrc license summary */
unsigned int rucrcprm(void);            /* prime number generator */
