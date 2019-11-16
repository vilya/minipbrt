Roadmap
=======

v1.0
----

Goal: correct, complete and fast parsing of PBRT v3 files into an in-memory
data structure. 

This includes loading of mesh data from external .ply files and sampled
spectrum data from external .spd files. It also includes converting the
"special" shape types (height field, loop subdiv and nurbs) into triangle
meshes.


v2.0
----

Goal: make the in-memory scene representation optional.

Most programs will - I believe - have their own scene representation and will 
only be using ours as an intermediate step to populating theirs from. If we can
provide a way to cut out that intermediate step it will save a lot of time and 
memory.

Refactor the API to separate parsing from scene building:
* Parser invokes callbacks on a user-provided object. 
* The scene builder implements the callback interface and builds the scene from
  it.
* Expose the PLY loading code so that users can extract arbitrary data from
  the file.
