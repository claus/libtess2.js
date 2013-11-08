#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libtess2/Include/tesselator.h"
#include "libtess2.h"


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
