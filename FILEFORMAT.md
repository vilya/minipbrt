The PBRT v3 File Format
=======================

The canonical reference for the file format is its implementation in
[PBRT v3](https://github.com/mmp/pbrt-v3).

There is a page documenting the file format here:

https://www.pbrt.org/fileformat-v3.html

However there are cases where that document doesn't match the PBRT
implementation. Some details are incorrect, some are missing. Details of those
are below.


General parsing
---------------

* Brackets are allowed around arg lists, e.g. for Transform the 16 floats can
  be enclosed in '[' and ']' characters.

* PBRT itself doesn't seem to allow forward references to named items, but
  some of the scenes in the pbrt-v3-scenes collection do this, specifically 
  for materials.

* Errors get logged but usually don't prevent the file from loading.


Curve shapes
------------

* The `P` array does not hold 4 points, as the doc suggests. It holds a number 
  determined by the number of curve segments, with different rules for bezier 
  and bspline curves.

* The `N` array holds `degree + 1` normals, not 2 as per the doc.


Textures
--------

There is an additional texture type, "ptex", which isn't mentioned in the
docs. It has two parameters:
* `"string filename"` - the name of a PTex file on the local disk
* `"float gamma"` - a gamma value to apply to colours from the PTex file.

Float textures exist in a different namespace to spectrum textures. You can 
have a float texture and a spectrum texture both called "foo". PBRT hardcodes
which namespace to do the lookup in for any given parameter.


Integrators
-----------

* Parameters for the Whitted integrator are not documented.
* PBRT supports two additional integrator types which aren't mentioned in the doc:
  * `"volpath"`
  * `"ao"`


Coordinate Systems
------------------

* The Camera statement defines a coordinate system called "camera" as a side
  effect.


Objects
-------

* ObjectBegin does an implicit AttributeBegin. Likewise ObjectEnd does an 
  implicit AttributeEnd.

* ObjectBegin calls cannot be nested.

* No nested instancing: it's an error to use ObjectInstance inside an
  ObjectBegin/End block.


Named items
-----------

These are all the different things that can be referenced by name:
* Material
* Medium
* Object
* Texture
* Coordinate system

Material and texture names are scoped to the current AttributeBegin/End block
(ObjectBegin/End counts for this purpose as well). Medium and Object names are
global, as are Coordinate Systems.

There are no forward references/late binding of any names. Whenever we
encounter a reference, it's resolved to the object it refers to at that time.
If the name is later redefined, this has no effect on any references which
occur before that point.

Behaviour with undefined names:
* If a NamedMaterial directive refers to a material name that hasn't been
  defined yet, PBRT reports an error and leaves the current material unchanged.
* Where a MixMaterial refers to a material name that hasn't been defined yet, 
  it uses a default-initialised MatteMaterial instead.
* If a material parameter uses a texture name that hasn't been defined yet, it
  simply creates an unnamed ConstantTexture with the default value for that
  parameter instead.
* If an ObjectInstance directive refers to an object name that hasn't been
  defined yet, PBRT reports an error and doesn't add anything to the scene.
* If a CoordSysTransform directive uses a name that hasn't been defined yet, a
  warning (not an error) is reported and the current transform is left 
  unchanged.

Redefining names:
* Redefining a texture or material name causes a warning in PBRT, not an error.
* Redefining a medium, object or coordinate system name is silently accepted.


Other
-----

* There is one case where a `scale` parameter has type `spectrum`, where the
  docs say it should be `float`, but I can't remember where that was just now.

