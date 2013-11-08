
typedef struct sMemPool {
	unsigned char* buf;
	unsigned int cap;
	unsigned int size;
} MemPool;

typedef struct sTESStess {
	TESStesselator* tess;
	TESSalloc* ma;
	MemPool* pool;
} TESStess;


TESStess* newTess(int size);

void deleteTess(TESStess* t);

void addContour(TESStess* t, int size, const void* pointer, int stride, int count);

int tesselate(TESStess* t, int windingRule, int elementType, int polySize, int vertexSize, const TESSreal* normal);

int getVertexCount(TESStess *t);

const TESSreal* getVertices(TESStess *t);

const TESSindex* getVertexIndices(TESStess *t);

int getElementCount(TESStess *t);

const TESSindex* getElements(TESStess *t);
