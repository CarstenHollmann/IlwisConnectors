#ifndef GDALCONNECTOR_H
#define GDALCONNECTOR_H

#include "gdalconnector_global.h"

namespace Ilwis{
namespace Gdal {

class GDALCONNECTORSHARED_EXPORT GdalConnector : public IlwisObjectConnector
{
public:
    GdalConnector(const Ilwis::Resource &resource, bool load=true);
    virtual ~GdalConnector();
    static IlwisTypes ilwisType(const QString &name);

    bool loadMetaData(IlwisObject* data);

    QString provider() const;
    void format(const QString&);
    QString format() const;
protected:
    static GDALDataType ilwisType2GdalType(IlwisTypes tp) ;
    static OGRFieldType ilwisType2GdalFieldType(IlwisTypes tp);
    QString constructOutputName(GDALDriverH hdriver) const;
    QUrl _filename;
    QString _internalPath;
    QString _gdalShortName;
    GdalHandle* _handle;
};
}
}

#endif // GDALCONNECTOR_H
