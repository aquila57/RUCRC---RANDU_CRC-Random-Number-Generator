/*
rucrcpat.c Version 0.1.0 - Generate Random Data Pattern
Copyright (C) 2020 aquila57 at github.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to:

	Free Software Foundation, Inc.
	59 Temple Place - Suite 330
	Boston, MA  02111-1307, USA.
*/

/* press 'r' to reset */
/* press 'q' to exit */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include "rucrc.h"

#define SCRW 80.0
#define SCRH 24.0

void initcrss()
   {
   initscr();
   cbreak();
   noecho();
   nonl();
   intrflush(stdscr,FALSE);
   nodelay(stdscr,TRUE);
   } /* initcrss */

int main()
   {
   int ch,x,y;
   rufmt *ru;
   ru = (rufmt *) rucrcinit();
   initcrss();
   while(1)
      {
      y = rucrcint(ru,SCRH);
      if (y == 23)
         x = rucrcint(ru,SCRW-1);
      else
         x = rucrcint(ru,SCRW);
      move(y,x);
      ch = rucrcint(ru,95) + 33;
      addch(ch);
      refresh();
      ch = getch();
      if (ch == 0x1b) /* ESCAPE */
         break;
      if (ch == 'q') /* quit */
         break;
      if (ch == 'r') /* reset */
         {
         clear();
         refresh();
         } /* reset */
      }
   endwin();
   free(ru->state);
   free(ru);
   return(0);
   } /* main */
