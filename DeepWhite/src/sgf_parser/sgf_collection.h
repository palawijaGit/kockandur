#ifndef SGF_COLLECTION_H
#define SGF_COLLECTION_H
#include "sgf_tree.h"

class SgfCollection {
    private:
        QList<SgfTree*> collection;
    public:
        // SgfCollection();
        // ~SgfCollection();
        void addSgfTree(SgfTree * tree);
};

#endif // SGF_COLLECTION_H
