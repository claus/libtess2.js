#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libtess2/Include/tesselator.h"
#include "tesselator.h"


void* poolAlloc(void* userData, unsigned int size) {
	MemPool* pool = (MemPool*)userData;
	if (pool->size + size < pool->cap) {
		unsigned char* ptr = pool->buf + pool->size;
		pool->size += size;
		return ptr;
	}
	return 0;
}

void poolFree(void* userData, void* ptr) {
}


TESStess* newTess(int size) {
	TESStess* t = (TESStess *)malloc(sizeof(TESStess));
	t->pool = (MemPool *)malloc(sizeof(MemPool));
	t->pool->buf = (unsigned char *)malloc(size);
	t->pool->cap = size;
	t->pool->size = 0;
	t->ma = (TESSalloc *)malloc(sizeof(TESSalloc));
	memset(t->ma, 0, sizeof(TESSalloc));
	t->ma->memalloc = poolAlloc;
	t->ma->memfree = poolFree;
	t->ma->userData = (void*)t->pool;
	t->ma->extraVertices = 256; // realloc not provided, allow 256 extra vertices.
	t->tess = tessNewTess(t->ma);
	if (t->tess == 0) {
		deleteTess(t);
		return NULL;
	}
	return t;
}

void deleteTess(TESStess* t) {
	tessDeleteTess(t->tess);
	free(t->ma);
	free(t->pool->buf);
	free(t->pool);
	free(t);
}

void addContour(TESStess* t, int size, const void* pointer, int stride, int count) {
	tessAddContour(t->tess, size, pointer, stride, count);
}

int tesselate(TESStess* t, int windingRule, int elementType, int polySize, int vertexSize, const TESSreal* normal) {
	return tessTesselate(t->tess, windingRule, elementType, polySize, vertexSize, normal);
}

int getVertexCount(TESStess *t) {
	return tessGetVertexCount(t->tess);
}

const TESSreal* getVertices(TESStess *t) {
	return tessGetVertices(t->tess);
}

const TESSindex* getVertexIndices(TESStess *t) {
	return tessGetVertexIndices(t->tess);
}

int getElementCount(TESStess *t) {
	return tessGetElementCount(t->tess);
}

const TESSindex* getElements(TESStess *t) {
	return tessGetElements(t->tess);
}

/*
int main(void) {

	float verts[8];
	verts[0] = 0;   verts[1] = 0;
	verts[2] = 100; verts[3] = 0;
	verts[4] = 100; verts[5] = 100;
	verts[6] = 0;   verts[7] = 100;

	TESStess* t = newTess(1024*512);

	if (t) {
		addContour(t, 2, verts, sizeof(float) * 2, 4);
		tesselate(t, TESS_WINDING_POSITIVE, TESS_POLYGONS, 3, 2, 0);
		printf("[results] verts:%d, elems:%d\n", getVertexCount(t), getElementCount(t));
		deleteTess(t);
	}

}
*/
