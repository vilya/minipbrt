The PBRT v3 File Format
=======================

The canonical reference for the file format is its implementation in the 
[PBRT v3 renderer](https://github.com/mmp/pbrt-v3).

There is a page documenting the file format here:

https://www.pbrt.org/fileformat-v3.html

However there are cases where that document doesn't match the PBRT
implementation. Some details are incorrect, some are missing. Details of those
are below.


General parsing
---------------

* Brackets are allowed around arg lists, e.g. for Transform the 16 floats can
  be enclosed in '[' and ']' characters.


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


Integrators
-----------

* Parameters for the Whitted integrator are not documented.
* PBRT supports two additional integrator types which aren't mentioned in the doc:
  * `"volpath"`
  * `"ao"`


Other
-----

* There are some cases where a `scale` parameter has type `spectrum`, where the
  docs say it should be `float`, but I can't remember where that was just now.
