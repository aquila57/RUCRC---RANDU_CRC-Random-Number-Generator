/* rucrcpwr.c - rucrc random number generator Version 2.0.0          */
/* Copyright (C) 2020 aquila57 at github.com                         */

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

/* this subroutine generates a random unsigned integer     */
/* from 1 to 31 bits                                       */
/* For performance reasons the parameter must be validated */
/* by the calling program.                                 */
/* See rucrcint.c for generating a random signed integer   */

#include "rucrc.h"

unsigned int rucrcpwr(rufmt *ru, int bits)
   {
   unsigned int intgr;      /* output UINT */
   intgr = rucrc(ru) >> (32-bits);
   return(intgr);           /* return random unsigned integer */
   } /* rucrcpwr */
