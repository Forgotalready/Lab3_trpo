#include "StatisticModel.h"

StatisticModel::StatisticModel(QMap<QString, double> Data, QObject* parent)
    : QAbstractTableModel(parent)
{
    foreach(const QString& key, Data.keys())
    {
        QVector<QString> temp;

        temp.push_back(key);
        temp.push_back(QString::number(Data[key], 'f', 2));

        m_data.push_back(temp);
    }
}


int StatisticModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int StatisticModel::columnCount(const QModelIndex &parent) const
{
    return column;
}

QVariant StatisticModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole || !index.isValid()){
        return QVariant();
    }

    return m_data[index.row()][index.column()];
}

QVariant StatisticModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole) return QVariant();

    if(orientation == Qt::Horizontal){
        if(section == 0)
            return "Path";
        else
            return "%";
    }else{
        return QString::number(section);
    }
}

void StatisticModel::onPathChange(QMap<QString, double> &newData)
{
    beginResetModel();
    m_data.clear();
    foreach(const QString& key, newData.keys())
    {
        QVector<QString> temp;

        temp.push_back(key);
        temp.push_back(QString::number(newData[key], 'f', 2));

        m_data.push_back(temp);
    }
    endResetModel();
}
