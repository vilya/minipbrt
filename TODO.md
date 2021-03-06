TO DO
=====

Features
--------

Expose the API for extracting data from PLY files to end users.

Add functions for converting other shapes into a TriangleMesh:
* [ ] Cone
* [ ] Curve
* [ ] Cylinder
* [ ] Disk
* [ ] Hyperboloid
* [ ] Paraboloid
* [ ] Sphere

Strict mode vs. permissive mode
* Strict mode errors on unknown statements/parameters, permissive mode ignores
  them.
* Both still error on malformed tokens, missing args & required params, etc.

Callback-based parsing interface
* For use if you have your own scene data model that you want to populate and
  don't want to create our data model as an intermediate step.
* Separate the existing scene construction code into a SceneBuilder class,
  Parser should only invoke callbacks. SceneBuilder should be the default 
  callback handler.


Performance
-----------

Reduce memory usage while parsing large attribute values, e.g. the vertex and
index arrays for a large triangle mesh.

Reduce memory usage for the in-memory scene representation:
- Transforms are represented by a pair of matrices, but we only need one
  matrix if the scene isn't animated.
- Many transform matrices will have a bottom row of 0,0,0,1 - perhaps can we use a 4x3 matrix instead, for those cases?
- Try using a packed (compressed?) representation, with decoding done in
  accessor methods?
- Use a disk cache.

Reduce overall number of memory allocations.
- Parsing itself doesn't do very many, but constructing the scene representation does a lot.

Improve IO performance:
- Use a background thread and/or async I/O calls to load the next buffer while
  we're parsing the current buffer.


Code structure
--------------

Factor out checks for required params into a function.

`pbrtinfo` example
* Rename main.cpp to pbrtinfo.cpp & move into an `examples` directory.

Code clean-up:
* Merge the tokenizer class into the parser class.
* Move as much as possible out of the header and into the cpp file.
* Make `set_error()` return bool so it can be used as part of a return statement.
* Remove any unused code.
