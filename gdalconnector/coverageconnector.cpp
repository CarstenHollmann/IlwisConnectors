#include <QLibrary>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "kernel.h"
#include "coverage.h"
#include "module.h"

#include "projection.h"
#include "ilwisdata.h"
#include "numericdomain.h"
#include "numericrange.h"
#include "columndefinition.h"
#include "ellipsoid.h"
#include "geodeticdatum.h"
#include "coordinatesystem.h"
#include "conventionalcoordinatesystem.h"
#include "table.h"
#include "ilwisobjectconnector.h"
#include "catalogexplorer.h"
#include "catalogconnector.h"
#include "gdalproxy.h"
#include "gdalconnector.h"
#include "coverageconnector.h"



using namespace Ilwis;
using namespace Gdal;

CoverageConnector::CoverageConnector(const Resource& resource, bool load, const PrepareOptions &options) : GdalConnector(resource,load, options)
{
}

bool CoverageConnector::loadMetaData(Ilwis::IlwisObject *data,const PrepareOptions& options){

    if(!GdalConnector::loadMetaData(data, options))
        return false;

    Coverage *coverage = static_cast<Coverage *>(data);
    if ( coverage == nullptr)
        return false;

    QFileInfo fileinf = containerConnector()->toLocalFile(source());
    ICoordinateSystem csy = setObject<ICoordinateSystem>("coordinatesystem", QUrl::fromLocalFile(fileinf.absoluteFilePath()));
    if(!csy.isValid()) {
        QString resource = QString("code=csy:unknown");
        if (!csy.prepare(resource)) {
            kernel()->issues()->log(TR("Fallback to 'unknown' failed, corrupt system files defintion"));
            return false;
        }
    }
    coverage->coordinateSystem(csy);

    return true;
}

bool CoverageConnector::store(IlwisObject *obj, IlwisTypes type)
{
    return GdalConnector::store(obj, type);
}

OGRSpatialReferenceH CoverageConnector::createSRS(const ICoordinateSystem& coordsystem) const{
    if ( hasType(coordsystem->ilwisType(), itCONVENTIONALCOORDSYSTEM)){
        IConventionalCoordinateSystem csy = coordsystem.as<ConventionalCoordinateSystem>();
        if ( csy->projection().isValid()){
            QString proj4def = csy->projection()->toProj4();
            OGRSpatialReferenceH srsH = gdal()->newSpatialRef(0);
            OGRErr errOgr = gdal()->importFromProj4(srsH, proj4def.toLocal8Bit());
            if ( errOgr != OGRERR_NONE) {
                return 0;
            }
            return srsH;
        }
    }
    return 0;
}



