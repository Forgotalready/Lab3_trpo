#include "Context.h"

Context::Context() {}

void Context::setStrategy(ITraversal *newStrategy)
{
    strategy = newStrategy;
}

QMap<QString, long long> Context::executeStrategy(QString &path)
{
    if(strategy != nullptr)
        return strategy->execute(path);
    else{
        qWarning() << "Strategy not initilized";
        return QMap<QString, long long>();
    }
}
