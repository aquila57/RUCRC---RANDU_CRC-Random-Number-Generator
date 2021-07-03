/************************************************************************/
/* rucrcencr.c  Version 0.1.0                                           */
/* Encrypt an input stream with the rucrc algorithm                     */
/* Copyright (C) 2021 aquila57 at github.com                            */

/* This program is free software; you can redistribute it and/or        */
/* modify it under the terms of the GNU General Public License as       */
/* published by the Free Software Foundation; either version 2 of       */
/* the License, or (at your option) any later version.                  */

/* This program is distributed in the hope that it will be useful,      */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/* GNU General Public License for more details.                         */

/* You should have received a copy of the GNU General Public License    */
/* along with this program; if not, write to:                           */

	/* Free Software Foundation, Inc.         */
	/* 59 Temple Place - Suite 330            */
	/* Boston, MA  02111-1307, USA.           */
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "rucrc.h"

/* length of input/output buffer */
#define BUFSZ (1024*1024)

#define POLY (0xEDB88320)

#define MASK (0xffffffff)

#define OCTETMSK (0x000000ff)

/* print the command syntax */
void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s password\n", pgm);
   fprintf(stderr,"Where password is an ASCII string\n");
   fprintf(stderr,"Example: %s abcd\n", pgm);
   fprintf(stderr,"Example: %s \"abcd efgh\"\n", pgm);
   fprintf(stderr,"Example: %s 'abcd efgh'\n", pgm);
   exit(1);
   } /* putstx */

/**************************************/
/* read one block of input from stdin */
/* return the length of the block     */
/* a partial block may be returned    */
/* maximum blocksize is BUFSZ         */
/* input may be binary data           */
/**************************************/
int getblk(unsigned char *blk)
   {
   int len;
   len = read(0,blk,BUFSZ);
   if (!len) return(EOF);
   if (len < 0)
      {
      fprintf(stderr,"getblk: read error\n");
      exit(1);
      } /* read error */
   return(len);
   } /* getblk */

/***************************************/
/* write one block of output to stdout */
/* maximum blocksize is determined by  */
/* the calling routine.                */
/* output is binary data               */
/***************************************/
void putblk(unsigned char *blk, int len)
   {
   int rslt;
   rslt = write(1,blk,len);
   if (rslt != len)
      {
      fprintf(stderr,"putblk: write error\n");
      exit(1);
      } /* write error */
   } /* putblk */

/**************************************************/
/* these crc routines are copied from rucrcinit.c */
/**************************************************/

void bldcrctbl(unsigned int *tbl)
   {
   int i;
   unsigned int crc;
   for (i=0;i<256;i++)
      {
      int j;
      crc = i;
      for (j=0;j<8;j++)
         {
	 if (crc & 1) crc = (crc >> 1) ^ POLY;
	 else crc = crc >> 1;
	 } /* for each j */
      tbl[i] = crc;
      } /* for each i */
   } /* bldcrctbl */

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

int main(int argc, char **argv)
   {
   int pswlen;                 /* length of password parameter */
   char psw[128];              /* password text */
   char pswnbl[256];           /* password text in nibbles */
   char revpswnbl[256];        /* reverse password nibbles */
   unsigned int crctbl[256];   /* crc32 table */
   unsigned int s1;            /* rucrcstrt parm */
   unsigned int s2;            /* rucrcstrt parm */
   unsigned int s3;            /* rucrcstrt parm */
   unsigned char *buf;         /* input/output buffer */
   rufmt *ru;                  /* rucrc RNG structure */
   if (argc != 2) putstx(*argv);    /* must have password parameter */
   /*******************************/
   /* validate length of password */
   /*******************************/
   pswlen = strlen(*(argv+1));    /* validate length of password */
   if (pswlen > 64)
      {
      fprintf(stderr,"main: password overflow\n");
      fprintf(stderr,"password is 1-64 bytes long\n");
      putstx(*argv);
      } /* password overflow */
   strcpy((char *) psw,*(argv+1));     /* save password */
   /*****************************************************/
   /* Alloocate memory for the input/output buffer      */
   /*****************************************************/
   buf = (unsigned char *) malloc(BUFSZ);
   if (buf == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating buf\n");
      exit(1);
      } /* out of memory */
   /*****************************************************/
   /* initialize the CRC table                          */
   /* initialize random number generator rucrc          */
   /* with rucrcstrt(s1^s2^s3)                          */
   /*****************************************************/
   bldcrctbl(crctbl);      /* initialize CRC table */
   str2nbl(psw, pswnbl);
   revstr(pswnbl, revpswnbl);
   s1 = calccrc(psw, crctbl); 
   s2 = calccrc(pswnbl, crctbl); 
   s3 = calccrc(revpswnbl, crctbl); 
   ru = rucrcstrt(s1^s2^s3);
   /*****************************************************/
   /* encrypt the stdin data stream                     */
   /* write encrypted data to stdout                    */
   /* loop terminated by end of input stream            */
   /*****************************************************/
   while (1)
      {
      int blklen;
      unsigned char *p,*q;
      blklen = getblk(buf);
      if (blklen == EOF) break;
      p = (unsigned char *) buf;
      q = (unsigned char *) buf + blklen;
      while (p < q)
         {
         *p = *p ^ rucrcpwr(ru,8);
	 p++;
	 } /* for each byte in the buffer */
      putblk(buf,blklen);
      } /* for each block encrypted */
   free(buf);
   free(ru->state);
   free(ru);
   return(0);
   } /* main */
