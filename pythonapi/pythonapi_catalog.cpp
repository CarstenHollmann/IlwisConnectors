#include "../../IlwisCore/core/identity.h"
#include "../../IlwisCore/core/kernel.h"
#include "../../IlwisCore/core/ilwisobjects/ilwisdata.h"
#include "../../IlwisCore/core/catalog/resource.h"
#include "../../IlwisCore/core/catalog/catalogview.h"

#include "pythonapi_catalog.h"

#include "pythonapi_pyobject.h"
#include "pythonapi_error.h"

namespace pythonapi {

    Catalog::Catalog(const std::string& url, const std::string& filter){
        Ilwis::CatalogView* cat = new Ilwis::CatalogView();
        cat->prepare(QUrl(QString::fromStdString(url)), QString::fromStdString(filter));
        this->_data.reset(cat);
    }

    Catalog::~Catalog(){
    }

    bool Catalog::__bool__() const{
        return this->_data->isValid();
    }

    std::string Catalog::__str__(){
        if (this->__bool__())
            return "Catalog";
        else
            return "invalid Catalog";
    }

    IlwisTypes Catalog::ilwisType(){
        return itCATALOG;
    }

    PyObject* Catalog::items(){
        if (this->__bool__()){
            std::vector<Ilwis::Resource> itms = this->_data->items();
            PyObject* ret = newPyTuple(itms.size());
            int i = 0;
            for(auto it = itms.begin(); it < itms.end(); it++ ){
                if (!setTupleItem(ret, i, PyUnicodeFromString(it->name().toStdString().data()))){
                    throw InvalidObject("invalid recource in catalog items");
                }
                i++;
            }
            return ret;
        }else{
            return newPyTuple(0);
        }
    }



} // namespace pythonapi
