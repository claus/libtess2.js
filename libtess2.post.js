
  var _newTess = Module.cwrap('newTess', 'number', ['number']);
  var _deleteTess = Module.cwrap('deleteTess', null, ['number']);
  var _addContour = Module.cwrap('addContour', null, ['number', 'number', 'number', 'number', 'number']);
  var _tesselate = Module.cwrap('tesselate', 'number', ['number', 'number', 'number', 'number', 'number', 'number']);
  var _getVertexCount = Module.cwrap('getVertexCount', 'number', ['number']);
  var _getVertices = Module.cwrap('getVertices', 'number', ['number']);
  var _getVertexIndices = Module.cwrap('getVertexIndices', 'number', ['number']);
  var _getElementCount = Module.cwrap('getElementCount', 'number', ['number']);
  var _getElements = Module.cwrap('getElements', 'number', ['number']);

  var ctor = function() {
    this.tess = null;
    this.polySize = 0;
    this.vertexSize = 0;
  };

  ctor.WINDING_ODD = 0;
  ctor.WINDING_NONZERO = 1;
  ctor.WINDING_POSITIVE = 2;
  ctor.WINDING_NEGATIVE = 3;
  ctor.WINDING_ABS_GEQ_TWO = 4;

  ctor.ELEMENT_POLYGONS = 0;
  ctor.ELEMENT_CONNECTED_POLYGONS = 1;
  ctor.ELEMENT_BOUNDARY_CONTOURS = 2;

  ctor.prototype = {
    newTess: function(mem) {
      this.tess = _newTess(mem || 1024 * 1024) || null;
      this.polySize = 0;
      this.vertexSize = 0;
    },
    deleteTess: function() {
      if (this.tess !== null) {
        _deleteTess(this.tess);
        this.tess = null;
      } else {
        throw "deleteTess: Tesselator not initialized.";
      }
    },
    addContour: function(vertices, size, stride, count) {
      if (this.tess !== null) {
        var pbuf = Module._malloc(vertices.length << 2);
        Module.HEAPF32.set(vertices, pbuf >> 2);
        _addContour(this.tess, size, pbuf, stride, count);
        Module._free(pbuf);
      } else {
        throw "addContour: Tesselator not initialized.";
      }
    },
    tesselate: function(windingRule, elementType, polySize, vertexSize, normal) {
      if (this.tess !== null) {
        normal = normal || 0;
        this.polySize = polySize;
        this.vertexSize = vertexSize;
        return _tesselate(this.tess, windingRule, elementType, polySize, vertexSize, normal);
      } else {
        throw "tesselate: Tesselator not initialized.";
      }
    },
    getVertexCount: function() {
      return _getVertexCount(this.tess);
    },
    getVertices: function() {
      var pverts = _getVertices(this.tess) >> 2;
      return new Float32Array(Module.HEAPF32.subarray(pverts, pverts + (this.getVertexCount() * this.vertexSize)));
    },
    getElementCount: function() {
      return _getElementCount(this.tess);
    },
    getElements: function() {
      var pelems = _getElements(this.tess) >> 2;
      return new Int32Array(Module.HEAP32.subarray(pelems, pelems + (this.getElementCount() * this.polySize)));
    }
  };

  return ctor;

})();
