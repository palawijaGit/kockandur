#include "sgf_tree.h"

inline void SgfTree::setRoot(SgfSequence * seq) {
          root = seq;
    }

inline void SgfTree::addNode(SgfTree * tree) {
          nodes.append(tree);
    }

SgfTree::SgfTree() {}

SgfTree::~SgfTree() {
    delete root;
    for (QList<SgfTree*>::iterator i = nodes.begin(); i != nodes.end(); i++)
        delete *i;
}
