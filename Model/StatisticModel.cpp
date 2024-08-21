#include "StatisticModel.h"


StatisticModel::StatisticModel(QMap<QString, double>& map, QObject *parent)
   : QAbstractTableModel(parent)
{
    foreach(QString key, map.keys()){
        QVector<QString> pair;

        pair.push_back(key);
        pair.push_back(QString::number(map[key], 'f', 2));

        m_data.push_back(pair);
    }
}

int StatisticModel::rowCount(const QModelIndex &parent) const
{
    return (int) m_data.size();
}

int StatisticModel::columnCount(const QModelIndex &parent) const
{
    return columnAmount;
}

QVariant StatisticModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole){
        return m_data[index.row()][index.column()];
    }
    return QVariant();
}

QVariant StatisticModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal){
        if(section == 0)
            return QString("Path");
        else if(section == 1)
            return QString("%");
        else
            return QVariant();
    }else if(orientation == Qt::Vertical){
        return QString::number(section);
    }else{
        return QVariant();
    }
}

void StatisticModel::onPathChange(QMap<QString, double> &newData)
{
    beginResetModel();
    m_data.clear();
    foreach(QString key, newData.keys()){
        QVector<QString> pair;

        pair.push_back(key);
        pair.push_back(QString::number(newData[key], 'f', 2));

        m_data.push_back(pair);
    }
    endResetModel();
}
