#ifndef ODFITEM_H
#define ODFITEM_H

namespace Ilwis {
namespace Ilwis3{
class ODFItem : public Resource
{
public:
    ODFItem(const QUrl& file, const UPCatalogConnector &container);
    bool resolveNames(const QHash<QString, quint64>& names);


    // bool isSystemObject(const QString &name) const;
private:
    /*!
     \brief  tries to find a id for the name found in the catalog

     All the names in the catalog have been scanned and they either have a resource already associated with them or
     they need to be associated with an existing resource. This can either be an resource in the catalog or a system object.
     Basically an object in the mastercatalog.

     \param names names found in this catalog
     \param unboundName name to be associated with an id
     \param returning id;

     \return true if the operation was succesfull. Error messages can be found on the issue stack.
    */
    bool setFileId(const QHash<QString, quint64> &names, const QString &unboundName, quint64 &fileid) const;

    QString findDomainName(const UPCatalogConnector &container) const;
    IlwisTypes findDomainType(const UPCatalogConnector &container) const;
    QString findCsyName(const UPCatalogConnector &container) const;
    IlwisTypes findCsyType(const UPCatalogConnector &container) const;
    QString findGrfName() const;
    QString findDatumName() const;
    QString findProjectionName() const;
    quint64 findSize(const UPCatalogConnector &container) const;
    quint64 objectSize(const UPCatalogConnector &container) const;
    quint64 partSize(const QUrl &file, const QString &section, const QString &key, const UPCatalogConnector& container) const;
    QString findDimensions() const;
    QString stripExtension(const QString &name) const;
    static bool isSystemObject(const QString &name);
    QString cleanName(const QString&) const;

    IniFile _odf;
    QFileInfo _file;
    QString _grfname;
    QString _domname;
    QString _csyname;
    QString _datumName;
    QString _projectionName;

    const static QString systemObjectNames;

};
}
}

#endif // ODFITEM_H
