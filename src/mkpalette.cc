/*
 *	mkpalette.cc
 *	Generate palette files from lump PLAYPAL.
 *	AYM 1998-12-29
 */


/*
This file is part of Yadex.

Yadex incorporates code from DEU 5.21 that was put in the public domain in
1994 by Rapha�l Quinet and Brendon Wyber.

The rest of Yadex is Copyright � 1997-1999 Andr� Majorel.

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
#include "mkpalette.h"
#include "gfx.h"
#include "rgb.h"


/*
 *	make_gimp_palette
 *	Generate a Gimp palette file for the <playpalnum>th
 *	palette in the PLAYPAL entry.
 *	Return 0 on success, non-zero on failure.
 */
int make_gimp_palette (int playpalnum, const char *filename)
{
MDirPtr dir;
u8	*dpal;
FILE	*output_fd;

dir = FindMasterDir (MasterDir, "PLAYPAL");
if (dir == NULL)
   {
   warn ("PLAYPAL lump not found.\n");
   return 1;
   }

int playpal_count = dir->dir.size / (3 * DOOM_COLOURS);
if (playpalnum < 0 || playpalnum >= playpal_count)
   {
   warn ("playpalnum %d out of range (0-%d). Using #0 instead.\n",
      playpalnum, playpal_count - 1);
   playpalnum = 0;
   }

output_fd = fopen (filename, "w");
if (output_fd == NULL)
   {
   warn ("can't open \"%s\" (%s)\n", filename, strerror (errno));
   warn ("giving up.\n");
   return 1;
   }
fprintf (output_fd,
   "GIMP Palette\n"
   "# Generated by Yadex %s\n", yadex_version);

dpal = (u8 *) GetFarMemory (3 * DOOM_COLOURS);
wad_seek (dir->wadfile, dir->dir.start + (long) playpalnum * 3 * DOOM_COLOURS);
wad_read_bytes (dir->wadfile, dpal, 3 * DOOM_COLOURS);
for (size_t n = 0; n < DOOM_COLOURS; n++)
   fprintf (output_fd, "%3d %3d %3d  Index = %d (%02Xh)   RGB = %d, %d, %d\n",
      dpal[3 * n],
      dpal[3 * n + 1],
      dpal[3 * n + 2],
      n,
      n,
      dpal[3 * n],
      dpal[3 * n + 1],
      dpal[3 * n + 2]);
FreeFarMemory (dpal);

if (fclose (output_fd))
   return 1;
else
   return 0;
}


/*
 *	make_palette_ppm
 *	Generate a 256 x 128 raw PPM image showing all the
 *	colours in the palette.
 *	Return 0 on success, non-zero on failure.
 */

int make_palette_ppm (int playpalnum, const char *filename)
{
MDirPtr dir;
u8	*dpal;
FILE	*output_fd;

dir = FindMasterDir (MasterDir, "PLAYPAL");
if (dir == NULL)
   {
   warn ("PLAYPAL lump not found.\n");
   return 1;
   }

int playpal_count = dir->dir.size / (3 * DOOM_COLOURS);
if (playpalnum < 0 || playpalnum >= playpal_count)
   {
   warn ("playpalnum %d out of range (0-%d). Using #0 instead.\n",
      playpalnum, playpal_count - 1);
   playpalnum = 0;
   }

output_fd = fopen (filename, "wb");
if (output_fd == NULL)
   {
   warn ("can't open \"%s\" (%s)\n", filename, strerror (errno));
   warn ("giving up.\n");
   return 1;
   }

const int width = 128;
const int height = 128;
const int columns = 16;

fputs ("P6", output_fd);
fnewline (output_fd);
fprintf (output_fd, "# Generated by Yadex %s", yadex_version);
fnewline (output_fd);
fprintf (output_fd, "%d %d", width, height);
fnewline (output_fd);
fputs ("255\n", output_fd);  // Always \n (must be a single character)

int rect_w = width / columns;
int rect_h = height / (DOOM_COLOURS / columns);

dpal = (u8 *) GetFarMemory (3 * DOOM_COLOURS);
wad_seek (dir->wadfile, dir->dir.start + (long) playpalnum * 3 * DOOM_COLOURS);
wad_read_bytes (dir->wadfile, dpal, 3 * DOOM_COLOURS);
for (size_t n = 0; n < DOOM_COLOURS; n += columns)
   for (int subrow = 0; subrow < rect_h; subrow++)
      for (int c = 0; c < columns; c++)
         for (int subcol = 0; subcol < rect_w; subcol++)
	    {
	    if (subrow == 0 && subcol == 0)
	       {
	       putc (0, output_fd);
	       putc (0, output_fd);
	       putc (0, output_fd);
	       }
	    else
	       {
	       putc (dpal[3 * (n + c)],     output_fd);
	       putc (dpal[3 * (n + c) + 1], output_fd);
	       putc (dpal[3 * (n + c) + 2], output_fd);
	       }
	    }
FreeFarMemory (dpal);

if (fclose (output_fd))
   return 1;
else
   return 0;
}


/*
 *	make_palette_ppm_2
 *	Make a wide PPM containing all the colours in the palette
 */

int make_palette_ppm_2 (int playpalnum, const char *filename)
{
MDirPtr dir;
u8	*dpal;
FILE	*output_fd;

dir = FindMasterDir (MasterDir, "PLAYPAL");
if (dir == NULL)
   {
   warn ("PLAYPAL lump not found.\n");
   return 1;
   }

int playpal_count = dir->dir.size / (3 * DOOM_COLOURS);
if (playpalnum < 0 || playpalnum >= playpal_count)
   {
   warn ("playpalnum %d out of range (0-%d). Using #0 instead.\n",
      playpalnum, playpal_count - 1);
   playpalnum = 0;
   }

output_fd = fopen (filename, "wb");
if (output_fd == NULL)
   {
   warn ("can't open \"%s\" (%s)\n", filename, strerror (errno));
   warn ("giving up.\n");
   return 1;
   }

const int width = DOOM_COLOURS;
const int height = DOOM_COLOURS;

fputs ("P6", output_fd);
fnewline (output_fd);
fprintf (output_fd, "# Generated by Yadex %s", yadex_version);
fnewline (output_fd);
fprintf (output_fd, "%d %d", width, height);
fnewline (output_fd);
fputs ("255\n", output_fd);  // Always \n (must be a single character)

dpal = (u8 *) GetFarMemory (3 * DOOM_COLOURS);
wad_seek (dir->wadfile, dir->dir.start + (long) playpalnum * 3 * DOOM_COLOURS);
wad_read_bytes (dir->wadfile, dpal, 3 * DOOM_COLOURS);
for (int l = 0; l < height; l++)
   for (int c = 0; c < width; c++)
      {
      putc (dpal[3 * ((c + l) % DOOM_COLOURS)    ], output_fd);
      putc (dpal[3 * ((c + l) % DOOM_COLOURS) + 1], output_fd);
      putc (dpal[3 * ((c + l) % DOOM_COLOURS) + 2], output_fd);
      }
FreeFarMemory (dpal);

if (fclose (output_fd))
   return 1;
else
   return 0;
}


