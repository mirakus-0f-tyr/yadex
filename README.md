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

Some things I would like to see happen with yadex, while retaining (mostly) the
same overall workflow:

- have everything in the menus actually work (i.e. texture alignment by X/Y)

- reconfigurable keys via the config file (no GUI needed, just edit the config
  file)

- drag the map ala eureka (like in eureka, you hold down the a key and then drag
  with pointer to move map smoothly)

- move camera to position ala eureka (yes, I'm keeping the 3d preview patch)

- change size of 3d preview to configurable size

- drawing with mouse (at this point it won't really feel like DEU/Yadex anymore,
  but using the keyboard and drawing verts is really clunky). The ability to
  edit using the "classic" controls should still be available, if one is so
  inclined.

The workflow might go something like this: left-click to draw verts, left-drag
to select wanted verts, right-click to Insert, select all lines, right-click to
create sector. If we just wanted to draw lines and have sectors automatically
created we'd just use a new editor!

- Add a more portable build system (autotools)

The configure and GNUMakefile setup originally provided is pretty nice, but
adding a newer build system will help find compilers/libraries and allow use of
standard environment variables during configure. I understand a lot of people
prefer CMake these days, but I'd prefer to use autotools.

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

