### Yadex Doom Editor

Most people don't want to use Yadex. Newer editors handle so much of the
underlying work that working like this is considered a thing of the past. I like
it. I like the minimal dependencies (X), the launching/menu from the shell, and
the fact that everything needed can still be done in a mostly painless way
(using the keyboard where possible).

This branch is where I'm sticking work with no real purpose or direction.

If I ever take a definitive direction with the project, I may merge various
changes from this branch into it.

I have noticed and examined the cleaned up version of the yadex code found at
(farhaven/github). The changes made there have gone a long way toward cleaning
up the code and the bringing it forward. It's just not clear to me where that
repository was based. It's clearly 1.7.0, but which patches were applied? It
also seems targeted more specifically at FreeBSD. I had to install libbsd to get
that version of the code building. If I ever really dig into yadex on a real
level (actually trying to add modern QoL features), I may base off of that code.

### "Goals"
Some things I would like to see happen with yadex, while retaining (mostly) the
same overall workflow:

- have everything in the menus actually work (i.e. texture alignment by X/Y)

- reconfigurable keys via the config file (no GUI needed, just edit the config
  file)

- drag the map ala eureka (like in eureka, you hold down the a key and then drag
  with pointer to move map smoothly)

- move camera to position ala eureka (yes, I'm keeping the 3d preview patch)

- ~~change size of 3d preview to configurable size~~

- ~~inserting with the mouse~~

- ~~Add a more portable build system (autotools)~~

The configure and GNUMakefile setup originally provided is pretty nice, but
adding a newer build system will help find compilers/libraries and allow use of
standard environment variables during configure. I understand a lot of people
prefer CMake these days, but I'd prefer to use autotools.

Note: because of yadex needing to find the ygd and config files, I have added a
"make localinst" rule that will make a setup in the "app" directory. This is
good for debugging and using the app while not being installed system-wide.
- fix any serious bugs if they are found

Other things I've got on the back of my brain:

- Boom support

I'm not sure where the boom support lies in this editor. Add the rest of the
boom and mbf line types if they are not present.

- Heretic/Hexen support

Complete the work that was started in at least having basic Hexen support. Come
up with "default textures" for Heretic and Hexen the way they exist for
Doom/Doom2.

- Possible move to SDL

### Misc. Tasks

- The original configure created credits.cc dynamically from a text file located
  in docsrc. I did not bother with this when I converted to autotools, and so
  the version in the src dir is just some static version from whenever. I don't
  see a reason to change this right now, but since other dynamic files were
  added to the build process, it wouldn't hurt to do this one as well.

- include guards on ALL header files, even if it doesn't make sense for them to
  ever be included somewhere else (consistency!)

- spend more time looking at the farhaven/master branch to understand exactly
  what they have done. It seems there was quite a bit of work done formatting
  and modernizing the code. Merge where it makes sense. (This is actually a
  bigger one.)

- To fulfill curiosity, find out if this code can still be built, work on MS DOS
  (if sticking with current autotools setup, modifications will need to be
  made!).

### Known Issues

- program crashes when compiled with gcc 5.4. Everything will build fine, but
  will crash when creating a sector. This is with the gcc version from Ubuntu
  16.04. It might be specific to this Ubuntu build of gcc. I have not made a
  separate compile of 5.4 to test. I have not been able to recreate the issue on
  any other setup/compiler.

  The area where the crash occurs is objects.cc line 570 (buffer overflow as
  reported by valgrind).
