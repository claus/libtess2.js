# libtess2.js

This is the tesselation library [libtess2](https://github.com/memononen/libtess2), compiled to JavaScript via emscripten.

Quoting the original README:

> This is refactored version of the original libtess which comes with the GLU reference implementation. The code is good quality polygon tesselator and triangulator. The original code comes with rather horrible interface and its performance suffers from lots of small memory allocations. The main point of the refactoring has been the interface and memory allocation scheme.

> Simple bucketed memory allocator (see Graphics Gems III for reference) was added which speeds up the code by order of magnitude (tests showed 15 to 50 times improvement depending on data). The API allows the user to pass his own allocator to the library. It is possible to configure the library so that the library runs on predefined chunk of memory.

> The API was changed to loosely resemble the OpenGL vertex array API. The processed data can be accessed via getter functions. The code is able to output contours, polygons and connected polygons. The output of the tesselator can be also used as input for new run. I.e. the user may first want to calculate an union all the input contours and the triangulate them.

The code is released under [SGI FREE SOFTWARE LICENSE B Version 2.0](http://oss.sgi.com/projects/FreeB/).

The original author is [Mikko Mononen](mailto:memon@inside.org).

## Getting started

First, include the library:

```js
<script src="libtess2.js"></script>
```

That's it, you're now ready to use libtess2. A simple example:

```js
var vertices = new Float32Array([0,0,  100,0,  100,100,  0,100]);
console.log("in vertices", vertices);

var tess = new TESS();
tess.newTess(1024 * 512);
tess.addContour(vertices, 2, 8, 4);
tess.tesselate(TESS.WINDING_ODD, TESS.ELEMENT_POLYGONS, 3, 2, null);
console.log("out vertices", tess.getVertices());
console.log("out elements", tess.getElements());
tess.deleteTess();
```
