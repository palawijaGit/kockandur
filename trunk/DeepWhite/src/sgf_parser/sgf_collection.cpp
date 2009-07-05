#include "sgf_collection.h"

void SgfCollection::addSgfTree(SgfTree * tree) {
         collection.append(tree);
     }

SgfCollection::~SgfCollection() {
   for ( QList<SgfTree*>::iterator i = collection.begin(); i != collection.end(); i++)
        delete *i;
}

SgfCollection::SgfCollection() {

}
