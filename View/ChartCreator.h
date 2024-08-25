#ifndef CHARTCREATOR_H
#define CHARTCREATOR_H

#include <QChartView>
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>

#include "Model/StatisticModel.h"

using namespace QtCharts;

class ChartCreator
{
public:
    ChartCreator();

    QChartView* createPieChart(QString& title, StatisticModel* model);
    QChartView* createBarChart(QString& title, StatisticModel* model);
private:
    QChartView* chartView;
};

#endif // CHARTCREATOR_H
