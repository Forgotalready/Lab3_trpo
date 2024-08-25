#include "ChartCreator.h"

ChartCreator::ChartCreator()
{
    chartView = nullptr;
}

QChartView *ChartCreator::createPieChart(QString &title, StatisticModel *model)
{
    QChart* chart = new QChart();
    chart->setTitle(title);

    QPieSeries* pieSeries = new QPieSeries();
    for(int i = 0;i < model->rowCount(QModelIndex());i++)
    {
        QString title = model->data(model->index(i, 0)).toString();
        double precentage = model->data(model->index(i, 1)).toDouble();

        pieSeries->append(title, precentage);
    }

    foreach(QPieSlice* slice, pieSeries->slices())
    {
        slice->setLabel(slice->label() + " " + QString::number(slice->percentage(), 'f', 2));
    }

    chart->legend()->show();

    chart->addSeries(pieSeries);

    chartView = new QChartView(chart);
    return chartView;
}

QChartView *ChartCreator::createBarChart(QString &title, StatisticModel *model)
{
    QChart* chart = new QChart();
    chart->setTitle(title);

    QBarSeries* barSeries = new QBarSeries();
    QList<QBarSet*> listSet;

    for(int i = 0;i < model->rowCount(QModelIndex());i++)
    {
        QString title = model->data(model->index(i, 0)).toString();
        double precentage = model->data(model->index(i, 1)).toDouble();

        QBarSet* barSet = new QBarSet(title);
        *barSet << precentage;
        listSet.append(barSet);
    }

    barSeries->append(listSet);
    chart->addSeries(barSeries);
    chart->createDefaultAxes();

    chart->legend()->show();
    chartView = new QChartView(chart);
    return chartView;
}
