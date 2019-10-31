TO DO
=====

Must have (parser is not correct without them)
----------------------------------------------

Finish implementing:
[x] `parse_material_common()` - properties for each material type
[x] `parse_ObjectBegin()` - not implemented yet
[x] `parse_ObjectEnd()`	- not implemented yet
[x] `parse_ObjectInstance()` - not implemented yet
[ ] `parse_Texture()` - properties for each texture type
[ ] `blackbody_to_rgb()` - not implemented yet

Set up any missing defaults after the scene has been parsed:
* e.g. Camera params which depend on the Film settings

Resolve references to named items:
* PBRT allows items to be referenced by name before they're defined.
* We currently just try to resolve the references as we encounter them, which
  fails for some valid input files.

Allow overriding of material params in Shape statements.

Add functions for converting shapes into a TriangleMesh:
[ ] HeightField
[ ] LoopSubdiv
[ ] Nurbs
[ ] PLYMesh (loads the file)


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

Simpler parsing interface:
* A `pbrt_load_file()` function which returns a Scene pointer.

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
* Inline all parse_Xxx functions which only do simple processing (e.g.
  `parse_Identity()`, `parse_TransformBegin()`, etc).
* Make `set_error()` return bool so it can be used as part of a return statement.
* Remove any unused code.
