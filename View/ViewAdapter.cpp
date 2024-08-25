#include "ViewAdapter.h"

ViewAdapter::ViewAdapter() {}

TableView::TableView()
    : ViewAdapter()
{
    tableView = nullptr;
}

TableView::~TableView()
{
    if(tableView != nullptr)
    {
        delete tableView;
        tableView = nullptr;
    }
}

QWidget *TableView::updateView(StatisticModel *model)
{
    if(tableView != nullptr)
    {
        delete tableView;
        tableView = nullptr;
    }
    tableView = new QTableView();
    tableView->setModel(model);

    return tableView;
}

PieChart::PieChart()
{
    chartView = nullptr;
}

PieChart::~PieChart()
{
    if(chartView != nullptr)
    {
        delete chartView;
        chartView = nullptr;
    }
}

QWidget *PieChart::updateView(StatisticModel *model)
{
    if(chartView != nullptr)
    {
        delete chartView;
        chartView = nullptr;
    }

    PieChartCreator pieChartCreator;
    QString title = "Pie Chart";
    chartView = pieChartCreator.createChartView(title, model);
    return chartView;
}

BarChart::BarChart()
{
    chartView = nullptr;
}

BarChart::~BarChart()
{
    if(chartView != nullptr)
    {
        delete chartView;
        chartView = nullptr;
    }
}

QWidget *BarChart::updateView(StatisticModel *model)
{
    if(chartView != nullptr)
    {
        delete chartView;
        chartView = nullptr;
    }

    BarChartCreator barChartCreator;
    QString title = "Pie Chart";
    chartView = barChartCreator.createChartView(title, model);
    return chartView;
}
