#ifndef SGF_NODE_H
#define SGF_NODE_H
#include <QString>
#include <QList>

class SgfNode {
    private:
        QString * comments;
        SgfNode * parent;
        QList<SgfNode*> childs;
    public:

};

#endif // SGF_NODE_H
