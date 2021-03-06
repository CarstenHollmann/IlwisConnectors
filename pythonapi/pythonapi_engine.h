#ifndef PYTHONAPI_ENGINE_H
#define PYTHONAPI_ENGINE_H

#include "pythonapi_object.h"

typedef struct _object PyObject;

namespace pythonapi {
    class Catalog;
    class Engine{
    public:
        Engine();
        static Object* _do(std::string output_name, std::string operation,std::string c3 = "",std::string c4 = "",std::string c5 = "",std::string c6 = "",std::string c7="", std::string c8="", std::string c9="");
        static void setWorkingCatalog(const std::string& location);
        static std::string getLocation();
        PyObject* operations(const std::string& filter = "*");
        std::string operationMetaData(const std::string& name);
        static PyObject* _catalogItems();
    };

}
#endif // PYTHONAPI_ENGINE_H
