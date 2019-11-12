minipbrt - a simple and fast parser for PBRT v3 files
=====================================================

minipbrt is a fast and easy-to-use parser for [PBRT v3](https://www.pbrt.org/fileformat-v3.html)
files, written in c++ 11. The entire parser is a single header and cpp file
which you can copy into your own project. The parser creates an in-memory
representation of the scene.


Features
--------

- *Small*: just a single .h and .cpp file which you can copy into your project.
- *Fast*: between 4 and 30 times faster than pbrt-parser on most scenes.
- *Complete*: supports the full PBRTv3 file format, not just a subset; and can
  load mesh data from any valid PLY file (ascii, little endian or big endian).
- Provides built-in functions for loading triangle mesh data from PLY files:
  - One function which loads all .ply files
  - One function to load a single .ply file, which you can safely call from 
    multiple threads concurrently.
- Converts spectrum values to RGB at load time using the CIE XYZ response 
  curves.
- Provides detailed error info if a file fails to parse, including the line
  and column number where it failed.
- MIT Licensed.


Getting started
---------------

- Copy `minipbrt.h` and `minipbrt.cpp` into your project.
- Add `#include <minipbrt.h>` wherever necessary.

The CMake file in this directory is just for building the examples.


Loading a file
--------------

Simply create a `minipbrt::Parser` object and call it's `parse()` method,
passing in the name of the file you want to parse. The method will return
`true` if parsing succeeded or `false` if there was an error. 

If parsing succeeded, call `parser.take_scene()` or `parser.borrow_scene()` to
get a pointer to a `minipbrt::Scene` object describing the scene. The
`take_scene` method transfers ownership of the scene object to the caller,
meaning you must delete it yourself when you're finished with it; whereas
`borrow_scene` lets you use the scene object temporarily, but it will be
deleted automatically by the parser's destructor.

If parsing failed, call `parser.get_error()` to get a `minipbrt::Error` object
describing what went wrong. The object includes the filename, line number and
column number where the error occurred. This will be exact for syntactic
errors, but may give the location of the token immediately *after* the error
for semantic errors. The error object remains owned by the parser, so you
never have to delete it yourself.

Example code:
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

* PLY files are not automatically loaded. Call `Scene::load_all_ply_meshes` to
  load all of them (single threaded), or `Scene::to_triangle_mesh` to load an
  individual plymesh. You can safely call `Scene::to_triangle_mesh` from 
  multiple threads, as long as each thread is calling it with a different shape 
  index.

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

See the [pbrt-parsing-perf](https://github.com/vilya/pbrt-parsing-perf)
project for much more detailed performance info. These results are just a
quick summary to give you an idea of the performance.


| Scene                                                                                     | Parse time (secs) |
| :---------------------------------------------------------------------------------------- | ----------------: |
| Disney's [Moana island scene](https://www.technology.disneyanimation.com/islandscene)     | 177.581           |
| [Landscape scene](https://www.pbrt.org/scenes-v3.html) from the PBRT v3 scenes collection | 1.651             |


The times above are from a Windows 10 laptop with:
* Intel Core i7-6700HQ CPU, 2.6 GHz
* 16 GB Dual-channel DDR4 RAM
* Samsung MZVPV512 SSD, theoretical peak read speed of 1165 MB/s

Note that the laptop had to use swap space while parsing the Moana island
scene. Parsing completes considerably faster when you have enough free memory
to avoid swapping.


Feedback, suggestions and bug reports
-------------------------------------

GitHub Issues: https://github.com/vilya/minipbrt/issues
