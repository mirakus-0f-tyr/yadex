/*
 *	s_prop.cc
 *	Sector properties
 *	Some of this was originally in editobj.c. It was moved here to
 *	improve overlay granularity (therefore memory consumption).
 *	AYM 1998-02-07
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
#include "entry.h"
#include "flats.h"
#include "game.h"
#include "gfx.h"
#include "levels.h"
#include "oldmenus.h"
#include "selectn.h"


/*
 *	Prototypes of private functions
 */
static const char *PrintSt (void *ptr);


/*
 *	SectorProperties
 *	Sector properties "dialog"
 */
void SectorProperties (int x0, int y0, SelPtr obj)
{
char  *menustr[30];
char   texname[WAD_FLAT_NAME + 1];
int    n, val;
SelPtr cur;
int    subwin_y0;

for (n = 0; n < 8; n++)
   menustr[n] = (char *) GetMemory (60);
sprintf (menustr[7], "Edit sector #%d", obj->objnum);
sprintf (menustr[0], "Change floor height     (Current: %d)",
	Sectors[obj->objnum].floorh);
sprintf (menustr[1], "Change ceiling height   (Current: %d)",
	Sectors[obj->objnum].ceilh);
sprintf (menustr[2], "Change floor texture    (Current: %.*s)",
	(int) WAD_FLAT_NAME, Sectors[obj->objnum].floort);
sprintf (menustr[3], "Change ceiling texture  (Current: %.*s)",
	(int) WAD_FLAT_NAME, Sectors[obj->objnum].ceilt);
sprintf (menustr[4], "Change light level      (Current: %d)",
	Sectors[obj->objnum].light);
sprintf (menustr[5], "Change type             (Current: %d)",
	Sectors[obj->objnum].special);
sprintf (menustr[6], "Change linedef tag      (Current: %d)",
	Sectors[obj->objnum].tag);
val = DisplayMenuArray (x0, y0, menustr[7], 7, NULL, menustr, NULL, NULL, NULL);
for (n = 0; n < 8; n++)
   FreeMemory (menustr[n]);
subwin_y0 = y0 + BOX_BORDER + (2 + val) * FONTH;
switch (val)
{
case 1:
   val = InputIntegerValue (x0 + 42, subwin_y0, -32768, 32767,
      Sectors[obj->objnum].floorh);
   if (val != IIV_CANCEL)
      {
      for (cur = obj; cur; cur = cur->next)
	 Sectors[cur->objnum].floorh = val;
      MadeChanges = 1;
      }
   break;
case 2:
   val = InputIntegerValue (x0 + 42, subwin_y0, -32768, 32767,
      Sectors[obj->objnum].ceilh);
   if (val != IIV_CANCEL)
      {
      for (cur = obj; cur; cur = cur->next)
	 Sectors[cur->objnum].ceilh = val;
      MadeChanges = 1;
      }
   break;
case 3:
   {
   *texname = '\0';
   strncat (texname, Sectors[obj->objnum].floort, WAD_FLAT_NAME);
   ObjectsNeeded (0);
   char **flat_names =
      (char **) GetMemory (NumFTexture * sizeof *flat_names);
   for (size_t n = 0; n < NumFTexture; n++)
      flat_names[n] = flat_list[n].name;
   ChooseFloorTexture (x0 + 42, subwin_y0, "Choose a floor texture",
     NumFTexture, flat_names, texname);
   FreeMemory (flat_names);
   ObjectsNeeded (OBJ_SECTORS, 0);
   if (strlen (texname) > 0)
      {
      for (cur = obj; cur; cur = cur->next)
	 strncpy (Sectors[cur->objnum].floort, texname, WAD_FLAT_NAME);
      MadeChanges = 1;
      }
   break;
   }
case 4:
   {
   *texname = '\0';
   strncat (texname, Sectors[obj->objnum].ceilt, WAD_FLAT_NAME);
   ObjectsNeeded (0);
   char **flat_names =
      (char **) GetMemory (NumFTexture * sizeof *flat_names);
   for (size_t n = 0; n < NumFTexture; n++)
      flat_names[n] = flat_list[n].name;
   ChooseFloorTexture (x0 + 42, subwin_y0, "Choose a ceiling texture",
     NumFTexture, flat_names, texname);
   FreeMemory (flat_names);
   ObjectsNeeded (OBJ_SECTORS, 0);
   if (strlen (texname) > 0)
      {
      for (cur = obj; cur; cur = cur->next)
	 strncpy (Sectors[cur->objnum].ceilt, texname, WAD_FLAT_NAME);
      MadeChanges = 1;
      }
   break;
   }
case 5:
   val = InputIntegerValue (x0 + 42, subwin_y0, 0, 255,
     Sectors[obj->objnum].light);
   if (val != IIV_CANCEL)
      {
      for (cur = obj; cur; cur = cur->next)
	 Sectors[cur->objnum].light = val;
      MadeChanges = 1;
      }
   break;
case 6:
   val = 0;
   if (DisplayMenuList (x0+42, subwin_y0, "Select type", stdef, PrintSt,
    &val) < 0)
     break;
   /* KLUDGE last element of stdef means "enter value" */
   if (val == al_lcount (stdef) - 1)
     {
     val = InputIntegerValue (x0 + 84,
        subwin_y0 + BOX_BORDER + (3 + val) * FONTH,
        -32768, 32767, 0);
     if (val == IIV_CANCEL)  /* Esc */
       break;
     }
   else
     {
     if (al_lseek (stdef, val, SEEK_SET))
       fatal_error ("%s SP1 (%s)\n", msg_unexpected, al_astrerror (al_aerrno));
     val = CUR_STDEF->number;
     }
   for (cur = obj; cur; cur = cur->next)
     Sectors[cur->objnum].special = val;
   MadeChanges = 1;
   break;
case 7:
   val = InputIntegerValue (x0 + 42, subwin_y0, -32768, 32767,
     Sectors[obj->objnum].tag);
   if (val != IIV_CANCEL)
      {
      for (cur = obj; cur; cur = cur->next)
	 Sectors[cur->objnum].tag = val;
      MadeChanges = 1;
      }
   break;
}
}


/*
 *	PrintSt
 *	Used by DisplayMenuList when called by InputSectorType
 */
static const char *PrintSt (void *ptr)
{
static char buf[100];

if (ptr == NULL)
  return "PrintSt: (null)";
sprintf (buf, "[%2d] %.70s",
 ((stdef_t *)ptr)->number,
 ((stdef_t *)ptr)->longdesc);
return buf;
}


