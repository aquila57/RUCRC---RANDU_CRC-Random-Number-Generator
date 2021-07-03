#  rucrclib.mak - Compile rucrc library  Version 0.1.0
#  Copyright (C) 2021 aquila57 at github.com
# 
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:
# 
   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

OBJ=rucrcinit.o \
	rucrcstrt.o \
	bldcrctbl.o \
	rucrc.o \
	rucrcunif.o \
	rucrcfrac.o \
	rucrcpwr.o \
	rucrcint.o \
	rucrcbit.o \
	rucrcprm.o \
	rucrcabt.o \
	rucrcdspl.o

CC=gcc

AR=ar

CFLAGS=-c -Wall -O2

LDFLAGS=-lm

librucrc.a:			$(OBJ)
		rm -f librucrc.a
		$(AR) r librucrc.a $(OBJ)

rucrcinit.o:			rucrcinit.c
		$(CC) $(CFLAGS) rucrcinit.c

rucrcstrt.o:			rucrcstrt.c
		$(CC) $(CFLAGS) rucrcstrt.c

bldcrctbl.o:			bldcrctbl.c
		$(CC) $(CFLAGS) bldcrctbl.c

rucrc.o:			rucrc.c
		$(CC) $(CFLAGS) rucrc.c

rucrcunif.o:			rucrcunif.c
		$(CC) $(CFLAGS) rucrcunif.c

rucrcfrac.o:			rucrcfrac.c
		$(CC) $(CFLAGS) rucrcfrac.c

rucrcpwr.o:			rucrcpwr.c
		$(CC) $(CFLAGS) rucrcpwr.c

rucrcint.o:			rucrcint.c
		$(CC) $(CFLAGS) rucrcint.c

rucrcbit.o:			rucrcbit.c
		$(CC) $(CFLAGS) rucrcbit.c

rucrcprm.o:			rucrcprm.c
		$(CC) $(CFLAGS) rucrcprm.c

rucrcabt.o:			rucrcabt.c
		$(CC) $(CFLAGS) rucrcabt.c

rucrcdspl.o:			rucrcdspl.c
		$(CC) $(CFLAGS) rucrcdspl.c

clean:
		rm -f $(OBJ) librucrc.a
