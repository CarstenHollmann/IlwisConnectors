/* The ILWIS SWIG interface file*/

%module(docstring="The Python API for ILWIS Objects") ilwisobjects

%feature("autodoc","1");

%include "exception.i"
%include "std_string.i"

%{
#include "pythonapi_pyobject.h"
#include "pythonapi_error.h"
#include "pythonapi_extension.h"
#include "pythonapi_object.h"
#include "pythonapi_engine.h"
#include "pythonapi_ilwisobject.h"
#include "pythonapi_coordinatesystem.h"
#include "pythonapi_table.h"
#include "pythonapi_coverage.h"
#include "pythonapi_object.h"
#include "pythonapi_util.h"
#include "pythonapi_geometry.h"
#include "pythonapi_feature.h"
#include "pythonapi_featureiterator.h"
#include "pythonapi_featurecoverage.h"
#include "pythonapi_pixeliterator.h"
#include "pythonapi_georeference.h"
#include "pythonapi_rastercoverage.h"
#include "pythonapi_range.h"
%}

%include "pythonapi_qtGNUTypedefs.h"

%init %{
    //init FeatureCreationError for Python
    pythonapi::featureCreationError = PyErr_NewException("_ilwisobjects.FeatureCreationError",NULL,NULL);
    Py_INCREF(pythonapi::featureCreationError);
    PyModule_AddObject(m, "FeatureCreationError", pythonapi::featureCreationError);//m is SWIG declaration for Python C API modul creation
    //init IlwisException for Python
    pythonapi::ilwisException = PyErr_NewException("_ilwisobjects.IlwisException",NULL,NULL);
    Py_INCREF(pythonapi::ilwisException);
    PyModule_AddObject(m, "IlwisException", pythonapi::ilwisException);//m is SWIG declaration for Python C API modul creation
    //init InvalidObjectException for Python
    pythonapi::invalidObjectException = PyErr_NewException("_ilwisobjects.InvalidObjectException",NULL,NULL);
    Py_INCREF(pythonapi::invalidObjectException);
    PyModule_AddObject(m, "InvalidObjectException", pythonapi::invalidObjectException);//m is SWIG declaration for Python C API modul creation

    //init QtCoreApllication, Ilwis library and IssueLogger connection
    try {
        if (!pythonapi::initIlwisObjects()){
            PyErr_SetString(PyExc_ImportError,"ILWIS couldn't be initiallized!");
            return NULL;
        }
    }catch (std::exception& e) {
        PyErr_SetString(pythonapi::translate_Exception_type(e),pythonapi::get_err_message(e));
        return NULL;
    }

%}
//adds the export flag to pyd library for the IlwisException
%pythoncode %{
    IlwisException = _ilwisobjects.IlwisException
    InvalidObjectException = _ilwisobjects.InvalidObjectException
    FeatureCreationError = _ilwisobjects.FeatureCreationError
%}
//catch std::exception's on all C API function calls
%exception{
    try {
        $action
    }catch (std::exception& e) {
        PyErr_SetString(pythonapi::translate_Exception_type(e),pythonapi::get_err_message(e));
        SWIG_fail;
    }
}

namespace pythonapi {
    //instead of including whole (pythonapi_extension.h)
    void disconnectIssueLogger();
    void connectIssueLogger();
}

%include "pythonapi_object.h"

%include "pythonapi_engine.h"
%extend pythonapi::Engine {
%insert("python") %{
    @staticmethod
    def do(operation,arg1="",arg2="",arg3="",arg4="",arg5="",arg6="",arg7="",out=""):
        if str(operation) != "":
            obj = Engine__do(str(out),str(operation),str(arg1),str(arg2),str(arg3),str(arg4),str(arg5),str(arg6),str(arg7))
        else:
            raise IlwisException("no operation given!")
        type = obj.ilwisType()
        if type == 8:
            return RasterCoverage.toRasterCoverage(obj)
        elif 1 <= type <= 7:
            return FeatureCoverage.toFeatureCoverage(obj)
        elif type == 524288:
            return GeoReference.toGeoReference(obj)
        elif (type == 4096) or (type == 8192):
            return CoordinateSystem.toCoordinateSystem(obj)
        elif type == 0:
            raise TypeError("unknown IlwisType")
        else:
            return obj
%}
}

%include "pythonapi_ilwisobject.h"

%include "pythonapi_coordinatesystem.h"

%include "pythonapi_table.h"

%include "pythonapi_coverage.h"

%include "pythonapi_object.h"

%include "pythonapi_util.h"

%template(Pixel) pythonapi::PixelTemplate<qint32>;
%template(PixelD) pythonapi::PixelTemplate<double>;
%template(Size) pythonapi::SizeTemplate<quint32>;
%template(SizeD) pythonapi::SizeTemplate<double>;
%template(Box) pythonapi::BoxTemplate<Ilwis::Location<qint32, false>, pythonapi::PixelTemplate<qint32>, quint32>;
%template(Envelope) pythonapi::BoxTemplate<Ilwis::Coordinate, pythonapi::Coordinate, double>;

%extend pythonapi::SizeTemplate<quint32> {
%insert("python") %{
    __swig_getmethods__["xsize"] = xsize
    __swig_getmethods__["ysize"] = ysize
    __swig_getmethods__["zsize"] = zsize
    __swig_setmethods__["xsize"] = setXsize
    __swig_setmethods__["ysize"] = setYsize
    __swig_setmethods__["zsize"] = setZsize
    if _newclass:
        xsize = property(xsize,setXsize)
        ysize = property(ysize,setYsize)
        zsize = property(zsize,setZsize)
%}
}
%extend pythonapi::SizeTemplate<double> {
%insert("python") %{
    __swig_getmethods__["xsize"] = xsize
    __swig_getmethods__["ysize"] = ysize
    __swig_getmethods__["zsize"] = zsize
    __swig_setmethods__["xsize"] = setXsize
    __swig_setmethods__["ysize"] = setYsize
    __swig_setmethods__["zsize"] = setZsize
    if _newclass:
        xsize = property(xsize,setXsize)
        ysize = property(ysize,setYsize)
        zsize = property(zsize,setZsize)
%}
}
%extend pythonapi::PixelTemplate<qint32> {//Pixel
%insert("python") %{
    __swig_getmethods__["x"] = x
    __swig_getmethods__["y"] = y
    __swig_getmethods__["z"] = z
    __swig_setmethods__["x"] = setX
    __swig_setmethods__["y"] = setY
    __swig_setmethods__["z"] = setZ
    if _newclass:
        x = property(x,setX)
        y = property(y,setY)
        z = property(z,setZ)
%}
}
%extend pythonapi::PixelTemplate<double> {//PixelD
%insert("python") %{
    __swig_getmethods__["x"] = x
    __swig_getmethods__["y"] = y
    __swig_getmethods__["z"] = z
    __swig_setmethods__["x"] = setX
    __swig_setmethods__["y"] = setY
    __swig_setmethods__["z"] = setZ
    if _newclass:
        x = property(x,setX)
        y = property(y,setY)
        z = property(z,setZ)
%}
}
%extend pythonapi::Coordinate {
%insert("python") %{
    __swig_getmethods__["x"] = x
    __swig_getmethods__["y"] = y
    __swig_getmethods__["z"] = z
    __swig_setmethods__["x"] = setX
    __swig_setmethods__["y"] = setY
    __swig_setmethods__["z"] = setZ
    if _newclass:
        x = property(x,setX)
        y = property(y,setY)
        z = property(z,setZ)
%}
}

%include "pythonapi_geometry.h"

%include "pythonapi_feature.h"

%include "pythonapi_featureiterator.h"

%include "pythonapi_featurecoverage.h"

%typemap(out) Py_buffer* {
    $result = PyMemoryView_FromBuffer($1);
}

%include "pythonapi_pixeliterator.h"

%include "pythonapi_georeference.h"

%include "pythonapi_rastercoverage.h"

%include "pythonapi_range.h"

// declaring the Const for Python side xUNDEF declarations
%pythoncode %{
    class ReadOnly(type):
        @property
        def sUNDEF(cls):
            return "?"
        @property
        def shUNDEF(cls):
            return -32767
        @property
        def iUNDEF(cls):
            return -2147483647
        @property
        def rUNDEF(cls):
            return -1e308
        @property
        def flUNDEF(cls):
            return -1e38
        @property
        def i64UNDEF(cls):
            return -9223372036854775808
    class Const(metaclass=ReadOnly):pass
%}
