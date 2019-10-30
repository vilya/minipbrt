minipbrt - a simple and fast parser for PBRT v3 files
=====================================================

minipbrt is a fast and easy-to-use parser for [PBRT v3](https://www.pbrt.org/fileformat-v3.html)
files, written in c++ 11. The entire parser is a single header and cpp file
which you can copy into your own project. The parser creates an in-memory
representation of the scene.


Getting started
---------------

- Copy minipbrt.h and minipbrt.cpp into your project.
- Add `#include <minipbrt.h>` wherever necessary.

The CMake file in this directory is just for building the examples.


Loading a file
--------------

```
minipbrt::Parser parser;
if (parser.parse(filename)) {
	minipbrt::Scene* scene = parser.take_scene();
	// ... process the scene, then delete it ...
	delete scene;
}
else {
  // If parsing failed, the parser will have an error object.
  const minipbrt::Error* err = parser.get_error();
  fprintf(stderr, "[%s, line %lld, column %lld] %s\n",
      err->filename(), err->line(), err->column(), err->message());
  // Don't delete err, it's still owned by the parser.
}
```


Implementation notes
--------------------

* The code is C++11. 

* Spectra are always converted to RGB at load time. (This may change in
  future; for now it simplifies things to convert them straight away).

* PLY files are not automatically loaded. Call `load_ply_mesh` to load one
  of them. You can call this for each plymesh shape in parallel, or you can
  call `load_ply_meshes` to load them all on a single thread.
  (This is not implemented yet)

* Likewise, we provide helper functions for triangulating shapes but it's
  up to you to call them.
  (These aren't implemented yet either - see TODO.md)

* Most material properties can be either a texture or a value. These
  properties are represented as structs with type `ColorTex` or `FloatTex`. In
  both structs, if the `texture` member is anything other than
  `kInvalidTexture`, the texture should be used *instead* of the `value`.

* Parsing will fail if there's a token which is longer than the input buffer, 
  like a long string or filename. You can work around this by increasing the 
  size of the input buffer, although the default (1 MB) should be fine in all 
  but the most extreme cases.


Performance
-----------

[Moana Island Scene](https://www.technology.disneyanimation.com/islandscene), island.pbrt:
* Parsing time: 					127 secs
* Peak memory use during parsing: 	?
* Post-parsing memory use:			?

[Landscape Scene](https://www.pbrt.org/scenes-v3.html) from the PBRT v3 scene collection:
* Parsing time:						< 1 second (note: not yet loading PLY meshes)
* Peak memory use during parsing:	?
* Post-parsing memory use:			?

Tested on a Windows 10 laptop with a Core i7 6700HQ CPU with 16 GB RAM and a
Samsung NVMe SSD.


Feedback, suggestions and bug reports
-------------------------------------

GitHub Issues: https://github.com/vilya/minipbrt/issues
