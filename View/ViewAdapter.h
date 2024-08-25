#ifndef VIEWADAPTER_H
#define VIEWADAPTER_H

#include <QTableView>
#include <QChartView>

#include "Model/StatisticModel.h"
#include "ChartCreator.h"

using namespace QtCharts;

class ViewAdapter
{
public:
    ViewAdapter();
    virtual ~ViewAdapter(){}

    virtual QWidget* updateView(StatisticModel* model) = 0;
};


class TableView : public ViewAdapter
{
public:
    TableView();
    ~TableView() override;
    QWidget* updateView(StatisticModel* model) override;
private:
    QTableView* tableView;
};

class PieChart : public ViewAdapter
{
public:
    PieChart();
    ~PieChart() override;
    QWidget* updateView(StatisticModel* model) override;
private:
    QChartView* chartView;
};

class BarChart : public ViewAdapter
{
public:
    BarChart();
    ~BarChart() override;
    QWidget* updateView(StatisticModel* model) override;
private:
    QChartView* chartView;
};
#endif // VIEWADAPTER_H
