/* rucrcinit.c - Extended rucrc initialization Version 0.1.0         */
/* Copyright (C) 2021 aquila57 at github.com                         */

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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "rucrc.h"

unsigned int calccrc(char *str, unsigned int *tbl)
   {
   int len;
   unsigned int crc;
   char *p,*q;
   len = strlen(str);
   crc = MASK;
   p = (char *) str;
   q = (char *) str + len;
   while (p < q)
      {
      crc = (crc >> 8) ^
         tbl[(crc ^ *p++) & OCTETMSK];
      } /* for each char in str */
   return(~crc);
   } /* calccrc */

void str2nbl(char *str, char *nbl)
   {
   char *p,*q,*r;
   p = (char *) str;
   q = (char *) str + strlen(str);
   r = (char *) nbl;
   while (p < q)
      {
      *r = (*p >> 4) + 0x41;
      r++;
      *r = (*p & 0x0f) + 0x41;
      r++;
      p++;
      } /* for each char in str */
   *r = '\0';
   } /* str2nbl */

void revstr(char *str, char *rev)
   {
   int len;
   char *p,*q,*r;
   len = strlen(str);
   p = (char *) str + len - 1;
   q = (char *) str;
   r = (char *) rev;
   while (p >= q) *r++ = *p--;
   *r = '\0';
   } /* revstr */

rufmt *rucrcinit(void)
   {
   int i;                      /* loop counter */
   // unsigned int crctbl[256];   /* RANDU seed for setting s1,s2,s3 */
   unsigned int *stp,*stq;     /* pointer into state array */
   time_t now;                 /* current date and time */
   struct timeval tv;
   char *timestr;
   char ctimestr[256];
   char hextimestr[256];
   char revtimestr[256];
   char msstr[256];
   char mshexstr[256];
   char revmsstr[256];
   char seedstr[512];
   rufmt *ru;                  /* rucrc structure */

   /***************************************************/
   /* allocate memory for rucrc structure */
   /***************************************************/
   ru = (rufmt *) malloc(sizeof(rufmt));
   if (ru == NULL)
      {
      fprintf(stderr,"rucrcinit: out of memory "
      "allocating rucrc structure ru\n");
      exit(1);
      } /* out of memory */
   ru->states = STATES; /* save the number of rucrc states */

   /***************************************************/
   /* allocate memory for rucrc state array           */
   /***************************************************/
   ru->state = (unsigned int *)
      malloc(sizeof(unsigned int) * STATES);
   if (ru->state == NULL)
      {
      fprintf(stderr,"rucrcinit: out of memory "
      "allocating ru->state state array\n");
      exit(1);
      } /* out of memory */

   /***************************************************/
   /* Randomize the three seeds and states            */
   /* first build the crc table                       */
   /***************************************************/
   ru->maxint = MAXINT;
   bldcrctbl(ru->crctbl);
   //---------------------------------------------------
   // check validity of crc algorithm
   //---------------------------------------------------
   // strcpy(msstr,"123456789");
   // ru->seed = calccrc(msstr, ru->crctbl);
   // printf("%08x\n", ru->seed);
   //---------------------------------------------------
   /********************************************************/
   /* create nibble strings out of date and time           */
   /********************************************************/
   /* get date & time                                      */
   /* number of seconds since the epoch                    */
   time(&now);
   /* convert to ASCII time & date string                  */
   timestr = ctime(&now);
   /* copy time & date string to local memory              */
   strcpy(ctimestr,timestr);
   /* convert time & date string to nibble string          */
   /* each nibble is converted to A to O ASCII letters     */
   /* for input to crc calculation                         */
   str2nbl(ctimestr, hextimestr);
   /* create same string in reverse order                  */
   revstr(hextimestr,revtimestr);
   /********************************************************/
   /* create nibble strings out of epoch microseconds      */
   /********************************************************/
   /* get # microseconds since the epoch                   */
   gettimeofday(&tv,NULL);
   /* convert to ASCII string                              */
   sprintf(msstr,"%u %u", (unsigned int) tv.tv_sec,
      (unsigned int) tv.tv_usec);
   /* convert ASCII string to a nibble string              */
   str2nbl(msstr,mshexstr); 
   /* convert nibble string to a reverse nibble string     */
   revstr(mshexstr, revmsstr);
   /********************************************************/
   /* concatenate date & time with epoch microseconds      */
   /* calculate crc of concatenated string                 */
   /* this crc becomes the initial value of ru->s1         */
   /* ru->s1 is the first of three Taus seeds              */
   /********************************************************/
   sprintf(seedstr,"%s %s %s %s",
      ctimestr, msstr, mshexstr, revmsstr);
   ru->seed = calccrc(seedstr, ru->crctbl);
   // fprintf(stderr,"%s %08x\n", seedstr, ru->seed);
   ru->crc  = MASK;            /* set to all f's     */

   /***************************************************/
   /* Warm up the rucrc states.                       */
   /***************************************************/
   i = 128;
   while (i--) ru->out = RND;

   /***************************************************/
   /* initialize out, prev, and prev prev             */
   /* to random values                                */
   /***************************************************/
   ru->pprev = RND;             /* set to random UINT */
   ru->prev  = RND;             /* set to random UINT */
   ru->out   = RND;             /* set to random UINT */

   /***************************************************/
   /* initialize the state array to random values     */
   /***************************************************/
   stp = (unsigned int *) ru->state;
   stq = (unsigned int *) ru->state + STATES;
   while (stp < stq)
      {
      *stp++ = RND;             /* set to random UINT */
      } /* for each member in ru->state array */

   /***************************************************/
   /* To do regression testing, use                   */
   /* rucrcstrt with one parameter.                   */
   /***************************************************/

   /***************************************************/
   /* return the rucrc structure                      */
   /***************************************************/
   return(ru);
   } /* rucrcinit subroutine */
