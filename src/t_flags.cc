/*
 *	t_flags.cc
 *	AYM 1998-12-21
 */


/*
This file is part of Yadex.

Yadex incorporates code from DEU 5.21 that was put in the public domain in
1994 by Rapha�l Quinet and Brendon Wyber.

The rest of Yadex is Copyright � 1997-2000 Andr� Majorel.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307, USA.
*/


#include "yadex.h"
#include "levels.h"
#include "selectn.h"
#include "wstructs.h"


/*
 *	frob_things_flags
 *	For all the things in <list>, apply the operator <op>
 *	with the operand <operand> on the flags field.
 */
void frob_things_flags (SelPtr list, int op, int operand)
{
SelPtr cur;
i16 mask;

if (op == YO_CLEAR || op == YO_SET || op == YO_TOGGLE)
   mask = 1 << operand;
else
   mask = operand;

for (cur = list; cur; cur = cur->next)
   {
   if (op == YO_CLEAR)
      Things[cur->objnum].when &= ~mask;
   else if (op == YO_SET)
      Things[cur->objnum].when |= mask;
   else if (op == YO_TOGGLE)
      Things[cur->objnum].when ^= mask;
   else
      fatal_error ("frob_things_flags: op=%02X", op);
   }
}


