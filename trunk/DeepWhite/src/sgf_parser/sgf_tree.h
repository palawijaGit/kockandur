#ifndef SGF_TREE_H
#define SGF_TREE_H
#include "sgf_sequence.h"

class SgfTree {
    private:
      SgfSequence * root;
      QList<SgfTree*> nodes;
    public:
      void setRoot(SgfSequence *);
      SgfTree();
      ~SgfTree();
};

#endif // SGF_TREE_H
