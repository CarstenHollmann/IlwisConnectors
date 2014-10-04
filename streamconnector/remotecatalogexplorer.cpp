#include "kernel.h"
#include "connectorinterface.h"
#include "mastercatalog.h"
#include "ilwisobjectconnector.h"
#include "catalogconnector.h"
#include "ilwisobjectconnector.h"
#include "abstractfactory.h"
#include "connectorfactory.h"
#include "catalogexplorer.h"
#include "catalogconnector.h"
#include "catalog.h"
#include "ilwiscontext.h"
#include "remotecatalogexplorer.h"

using namespace Ilwis;
using namespace Stream;

RemoteCatalogExplorer::RemoteCatalogExplorer(const Ilwis::Resource &resource, const IOOptions &options) : CatalogExplorer(resource, options)
{

}

std::vector<Resource> RemoteCatalogExplorer::loadItems()
{

    ICatalog catalog(_resource.url(true));
    std::vector<Resource> items = catalog->items();

    return items;
}

bool RemoteCatalogExplorer::canUse(const Resource &resource) const
{
    QUrlQuery query(resource.url());
    if ( query.queryItemValue("service") != "ilwisobjects") // can't use anything marked as internal
        return false;
    if ( query.queryItemValue("ilwistype") != "catalog")
        return false;
    return true;
}

QString RemoteCatalogExplorer::provider() const
{
    return "ilwis"    ;
}

Ilwis::CatalogExplorer *RemoteCatalogExplorer::create(const Ilwis::Resource &resource, const Ilwis::IOOptions &options)
{
    return new RemoteCatalogExplorer(resource, options);
}
