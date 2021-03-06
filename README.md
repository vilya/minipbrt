minipbrt - a simple and fast parser for PBRT v3 files
=====================================================

minipbrt is a fast and easy-to-use parser for [PBRT v3](https://www.pbrt.org/fileformat-v3.html)
files, written in c++ 11. The entire parser is a single header and cpp file
which you can copy into your own project. The parser creates an in-memory
representation of the scene.


Features
--------

- *Small*: just a single .h and .cpp file which you can copy into your project.
- *Fast*: parses Disney's enormous Moana island scene (36 GB of data across
  491 files) in just 138 seconds. Many sample scenes take just a few tens of
  milliseconds.
- *Complete*: supports the full PBRTv3 file format and can load triangle mesh 
  data from any valid PLY file (ascii, little endian or big endian).
- *Thread-friendly*: designed so that PLY files can be loaded, or shapes
   turned into triangle meshes, on multiple threads; and can be integrated 
   easily with your own threading system of choice.
- *Cross platform*: works on Windows, macOS and Linux.
- Converts spectrum values to RGB at load time using the CIE XYZ response 
  curves.
- Utility functions for converting shapes into triangle meshes.
- PLY loading automatically triangulates polygons with more than 3 vertices.
- Gives useful error info if a file fails to parse, including the line and 
  column number where it failed.
- MIT Licensed.


Getting started
---------------

- Copy `minipbrt.h` and `minipbrt.cpp` into your project.
- Add `#include <minipbrt.h>` wherever necessary.

The CMake file in this directory is just for building the examples.


Loading a file
--------------

Simply create a `minipbrt::Loader` object and call it's `load()` method,
passing in the name of the file you want to parse. The method will return
`true` if parsing succeeded or `false` if there was an error. 

If parsing succeeded, call `loader.take_scene()` or `loader.borrow_scene()` to
get a pointer to a `minipbrt::Scene` object describing the scene. The
`take_scene` method transfers ownership of the scene object to the caller,
meaning you must delete it yourself when you're finished with it; whereas
`borrow_scene` lets you use the scene object temporarily, but it will be
deleted automatically by the loader's destructor.

If loading failed, call `loader.error()` to get a `minipbrt::Error` object
describing what went wrong. The object includes the filename, line number and
column number where the error occurred. This will be exact for syntactic
errors, but may give the location of the token immediately *after* the error
for semantic errors. The error object remains owned by the loader, so you
never have to delete it yourself.

Example code:
```cpp
minipbrt::Loader loader;
if (loader.load(filename)) {
	minipbrt::Scene* scene = loader.take_scene();
	// ... process the scene, then delete it ...
	delete scene;
}
else {
  // If parsing failed, the parser will have an error object.
  const minipbrt::Error* err = loader.error();
  fprintf(stderr, "[%s, line %lld, column %lld] %s\n",
      err->filename(), err->line(), err->column(), err->message());
  // Don't delete err, it's still owned by the parser.
}
```


Loading triangle meshes from external PLY files, single threaded
----------------------------------------------------------------

If you're happy with loading all the PLY files on a single thread, it's a
single method call:

```cpp
  // Assuming we've already loaded the scene successfully
  minipbrt::Scene* scene = /* ... */;
  scene->load_all_ply_meshes();
```

The `load_all_ply_meshes()` method will replace all PLYMesh shapes in the
scenes shape list with corresponding TriangleMesh shapes. This function is
provided as a convenience, but note that it's single-threaded. Some scenes 
reference a lot of PLY files and loading them in parallel can give a big speed
up. See below for more info on that.


Loading triangle meshes from external PLY files, multi-threaded
---------------------------------------------------------------

minipbrt does not provide any built-in multithreaded code, however the 
`to_triangle_mesh` method can be safely called from multiple threads so it's 
easy to integrate into your own threading system. 

Here's a simple example using `std::thread`:

```cpp
  // Assuming we've already loaded the scene successfully
  minipbrt::Scene* scene = /* ... */;

  std::atomic_uint nextShape(0);
  const uint32_t endShape = uint32_t(scene->shapes.size());
  const uint32_t numThreads = std::thread::hardware_concurrency();
  std::vector<std::thread> loaderThreads;
  loaderThreads.reserve(numThreads);
  for (uint32_t i = 0; i < numThreads; i++) {
    loaderThreads.push_back(std::thread([scene, &nextMesh, endMesh]() {
      uint32_t shape = nextShape++;
      while (shape < endShape) {
        if (scene->shapes[shape]->type() == minipbrt::ShapeType::PLYMesh) {
          scene->to_triangle_mesh(shape);
        }
        shape = nextShape++;
      }
    }));
  }
  for (std::thread& th : loaderThreads) {
    th.join();
  }
```

Note that this example doesn't ensure that all PLY files loaded successfully -
some may have failed to load. A more robust implementation should check for
this, either by checking the return value of `scene->to_triangle_mesh` or by
scanning `scene-shapes` a second time to see whether it still contains any
PLYMesh shapes.


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

See PERFORMANCE.md for parsing times on a wide range of input files. 

The [pbrt-parsing-perf](https://github.com/vilya/pbrt-parsing-perf) project
has a detailed performance comparison against pbrt-parser, the only other
open-source PBRT parsing library for C++ that I know of.


Feedback, suggestions and bug reports
-------------------------------------

GitHub Issues: https://github.com/vilya/minipbrt/issues
