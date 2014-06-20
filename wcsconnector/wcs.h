#ifndef WFS_H
#define WFS_H

#include <QUrl>
#include <QUrlQuery>

#include "wcsresponse.h"

namespace Ilwis {
namespace  Wcs {

class WebCoverageService
{

public:
    WebCoverageService(QUrl wfsUrl);

    QUrl url() const;
    WcsResponse *getCapabilities(bool async=false) const;
    WcsResponse *describeCoverage(QUrlQuery query, bool async=false) const;
    WcsResponse *getCoverage(QUrlQuery query, bool async=false) const;

private:
    QUrl _resource;

    WcsResponse *performRequest(QUrlQuery query, QString wfsRequest, bool async=false) const;
    WcsResponse *performSyncRequest(QUrl request) const;
    WcsResponse *performAsyncRequest(QUrl request) const;


};

}
}

#endif // WFS_H
