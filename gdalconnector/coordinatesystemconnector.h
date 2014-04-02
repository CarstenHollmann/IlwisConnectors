#ifndef COORDINATESYSTEMCONNECTOR_H
#define COORDINATESYSTEMCONNECTOR_H

namespace Ilwis{
namespace Gdal{

class CoordinateSystemConnector : public GdalConnector
{
public:
    CoordinateSystemConnector(const Ilwis::Resource &resource, bool load=true,const PrepareOptions& options=PrepareOptions());

    bool loadMetaData(IlwisObject *data, const PrepareOptions &options);

   // static bool canUse(const Ilwis::Resource &resource);

    IlwisObject *create() const;
    static ConnectorInterface *create(const Resource &resource, bool load=true,const PrepareOptions& options=PrepareOptions());

private:
    void setProjectionParameter(OGRSpatialReferenceH handle, const char *wkt, Projection::ProjectionParamValue parmType, IProjection &projection);
};
}
}

#endif // COORDINATESYSTEMCONNECTOR_H
