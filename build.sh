emcc -O2 libtess2/Source/bucketalloc.c libtess2/Source/dict.c libtess2/Source/geom.c libtess2/Source/mesh.c libtess2/Source/priorityq.c libtess2/Source/sweep.c libtess2/Source/tess.c -o libtess2/libtess2.bc -I./libtess2/Include
emcc -O2 libtess2/libtess2.bc libtess2.c -o libtess2.raw.js --closure 1 -s EXPORTED_FUNCTIONS="['_newTess', '_deleteTess', '_addContour', '_tesselate', '_getVertexCount', '_getVertices', '_getVertexIndices', '_getElementCount', '_getElements']"
cat libtess2.pre.js > libtess2.js
cat libtess2.raw.js >> libtess2.js
cat libtess2.post.js >> libtess2.js
rm libtess2/libtess2.bc
rm libtess2.raw.js
