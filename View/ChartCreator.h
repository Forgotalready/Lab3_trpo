#ifndef CHARTCREATOR_H
#define CHARTCREATOR_H

#include <QChartView>
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>

#include "Model/StatisticModel.h"

using namespace QtCharts;

class AbstractChartCreator
{
public:
    AbstractChartCreator();
    virtual ~AbstractChartCreator(){}
    QChartView* createChartView(QString& title, StatisticModel* model);
protected:
    virtual void addSeries(QChart* chart, StatisticModel* model) = 0;
private:
    QChartView* chartView;
};

class PieChartCreator : public AbstractChartCreator
{
public:
    PieChartCreator();
    ~PieChartCreator(){}
    // AbstractChartCreator interface
protected:
    void addSeries(QChart *chart, StatisticModel *model) override;
};

class BarChartCreator : public AbstractChartCreator
{
public:
    BarChartCreator();
    ~BarChartCreator(){}

    // AbstractChartCreator interface
protected:
    void addSeries(QChart *chart, StatisticModel *model) override;
};

#endif // CHARTCREATOR_H
