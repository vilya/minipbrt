TO DO
=====

Must have (parser is not correct without them)
----------------------------------------------

Set up any missing defaults after the scene has been parsed:
* e.g. Camera params which depend on the Film settings

Allow overriding of material params in Shape statements.

Add functions for converting shapes into a TriangleMesh:
[x] PLYMesh (loads the file)
[ ] HeightField
[ ] LoopSubdiv
[ ] Nurbs

Triangulate faces with more than 4 vertices when loading a PLYMesh. I haven't
seen this come up in any PBRT scenes yet (PBRT itself only seems to handle
tris or quads), but it *could* come up so parsing isn't truly correct without
it.


Nice to have (improvements thaat don't affect correctness)
----------------------------------------------------------

Add functions for converting other shapes into a TriangleMesh:
[ ] Cone
[ ] Curve
[ ] Cylinder
[ ] Disk
[ ] Hyperboloid
[ ] Paraboloid
[ ] Sphere

Remove all hard-coded limits on string length:
* We use a lot of locally-declared char arrays as temp storage for strings,
  which give an implicit max length for the strings they deal with.
* Remove these. Enum strings should be processed in-buffer, name strings &
  filenames should be copied into the temp param data.
* The only practical limit should be the buffer length (would be nice to
  remove that limit too, but not if it reduces performance).

Strict mode vs. permissive mode
* Strict mode errors on unknown statements/parameters, permissive mode ignores
  them.
* Both still error on malformed tokens, missing args & required params, etc.

Factor out checks for required params into a function.

`pbrtinfo` example
* Rename main.cpp to pbrtinfo.cpp & move into an `examples` directory.

Code clean-up:
* Merge the tokenizer class into the parser class.
* Move as much as possible out of the header and into the cpp file.
* Make `set_error()` return bool so it can be used as part of a return statement.
* Remove any unused code.

Optional callback-based parsing interface
* For use if you have your own scene data model that you want to populate and
  don't want to create our data model as an intermediate step.
* Separate the existing scene construction code into a SceneBuilder class,
  Parser should only invoke callbacks. SceneBuilder should be the default 
  callback handler.
