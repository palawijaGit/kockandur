#include "sgf_tree.h"

inline void SgfTree::setRoot(SgfSequence * seq) {
          root = seq;
      }

SgfTree::SgfTree() {}

SgfTree::~SgfTree() {
    delete root;
    for (QList<SgfTree*>::iterator i = nodes.begin(); i != nodes.end(); i++)
        delete *i;
}
