/* bldcrctbl.c - Build crc32 table  Version 0.1.0                    */
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

/* This routine is based on:          */
/* https://github.com/lammertb/libcrc */

#include "rucrc.h"

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
