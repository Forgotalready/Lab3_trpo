#ifndef CONTEXT_H
#define CONTEXT_H

#include "Traversal/ITraversal.h"
#include <QDebug>

class Context
{
    ITraversal* strategy;
public:
    Context();
    void setStrategy(ITraversal*);
    QMap<QString, long long> executeStrategy(QString& path);
};

#endif // CONTEXT_H
