#include <iterator>

#include "../../IlwisCore/core/kernel.h"
#include "../../IlwisCore/core/ilwisobjects/ilwisdata.h"

#include "../../IlwisCore/core/ilwisobjects/coverage/coverage.h"
#include "../../IlwisCore/core/util/numericrange.h"
#include "../../IlwisCore/core/ilwisobjects/domain/numericdomain.h"
#include "../../IlwisCore/core/ilwisobjects/table/columndefinition.h"
#include "../../IlwisCore/core/ilwisobjects/table/table.h"
#include "../../IlwisCore/core/ilwisobjects/table/attributerecord.h"
#include "../../IlwisCore/core/util/polygon.h"
#include "../../IlwisCore/core/ilwisobjects/coverage/geometry.h"
#include "../../IlwisCore/core/ilwisobjects/coverage/feature.h"
#include "../../IlwisCore/core/ilwisobjects/coverage/featurecoverage.h"
#include "../../IlwisCore/core/ilwisobjects/coverage/featureiterator.h"

#include "pythonapi_featureiterator.h"

using namespace pythonapi;

FeatureIterator::FeatureIterator(FeatureCoverage* fc):  _coverage(fc),_ilwisFeatureIterator(new Ilwis::FeatureIterator((*fc->ptr()))){
}

Feature FeatureIterator::next(){
    std::unique_ptr<Ilwis::FeatureInterface>& f = (*(*this->_ilwisFeatureIterator));
    (*this->_ilwisFeatureIterator)++;
    return Feature(f, this->_coverage);
}

bool FeatureIterator::hasNext(){
    return ((*this->_ilwisFeatureIterator) != this->_ilwisFeatureIterator->end());
}
