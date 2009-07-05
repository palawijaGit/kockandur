#include "sgf_sequence.h"

 inline void SgfSequence::addNode(SgfNode * node) {
            nodes.append(node);
    }

SgfSequence::SgfSequence() {}

SgfSequence::~SgfSequence() {
     for (QList<SgfNode*>::iterator i = nodes.begin(); i != nodes.end(); i++)
         delete *i;
}
