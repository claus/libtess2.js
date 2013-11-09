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

```html
<script src="libtess2.js"></script>
```

That's it, you're now ready to use libtess2. A simple example:

```js
var vertices = new Float32Array([0,0, 100,0, 100,100, 0,100]);
console.log("in vertices", vertices);

var tess = new TESS();
tess.newTess(1024 * 512);
tess.addContour(vertices, 2, 8, 4);
tess.tesselate(TESS.WINDING_ODD, TESS.ELEMENT_POLYGONS, 3, 2, null);
console.log("out vertices", tess.getVertices());
console.log("out elements", tess.getElements());
tess.deleteTess();
```

## API

The JS API is kept close to the original C API.

```js
newTess(size)
```
Creates a new tesselator.

Parameters:
* size - The memory, in bytes, to allocate.

```js
deleteTess(size)
```
Deletes a tesselator.

```js
addContour(vertices, size, stride, count)
```
Adds a contour to be tesselated.

Parameters:
* vertices - A Float32Array containing the vertices of the contour to add.
* size - The number of coordinates per vertex. Must be 2 or 3.
* stride - The offset in bytes between consecutive vertices.
* count - The number of vertices in the contour.

```js
tesselate(windingRule, elementType, polySize, vertexSize, normal)
```
Tesselates the contours.

Parameters:
* windingRule - The winding rule used for tesselation.
* elementType - The tesselation result element type.
* polySize - The maximum number of vertices per polygons if the output is polygons.
* vertexSize - The number of coordinates in tesselation result vertex, must be 2 or 3.
* normal - The normal of the input contours (optional).

Returns: 1 (success) or 0 (error)

```js
getVertexCount()
```
Returns the number of vertices in the tesselated output.

```js
getVertices()
```
Returns a Float32Array containig the vertices.

```js
getVertexIndices()
```
Returns a Int32Array containig the vertex indices.

Vertex indices can be used to map the generated vertices to the original vertices.
Every point added using addContour() will get a new index starting at 0.
New vertices generated at the intersections of segments are assigned value 0.

```js
getElementCount()
```
Returns the number of elements in the tesselated output.

```js
getElements()
```
Returns a Int32Array containig the element indices.

