#ifndef SGF_NODE_H
#define SGF_NODE_H
#include <QString>
#include <QList>
#include "sgf_property.h"

class SgfNode {
    private:
        QList<SgfProperty*> properties;
        SgfNode          *  parent;
        QList<SgfNode*>     childs;
    public:

};

#endif // SGF_NODE_H
