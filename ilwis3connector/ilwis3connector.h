#ifndef ILWIS3CONNECTOR_H
#define ILWIS3CONNECTOR_H

#include <QScopedPointer>
#include "Ilwis3Connector_global.h"


namespace Ilwis {

namespace Ilwis3 {

class ILWIS3CONNECTORSHARED_EXPORT Ilwis3Connector : public Ilwis::IlwisObjectConnector {
public:
    Ilwis3Connector(const Ilwis::Resource &item, bool load=true);
    //static IlwisTypes type(const QString &name);
    static IlwisTypes ilwisType(const QString &name);
    static QString name2Code(const QString &name, const QString &type);
    QString provider() const;

protected:
    QString suffix(IlwisTypes type) const;
    QUrl resolve(const Resource &resource) const;
    bool isSystemObject(const QString &filename);
    bool loadMetaData(IlwisObject* data);
    bool storeMetaData(const IlwisObject* data) const;


    QString ilwis3ClassName(IlwisTypes type) const;
    QString datum2Code(const QString& name, const QString& area) const;
    QString noExt(const QString& name);
    QString filename2FullPath(const QString &name) const;

    mutable ODF _odf;

};
}

}

#endif // ILWIS3CONNECTOR_H
