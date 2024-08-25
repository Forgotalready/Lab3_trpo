#include "ChartCreator.h"

AbstractChartCreator::AbstractChartCreator()
{
    chartView = nullptr;
}

QChartView *AbstractChartCreator::createChartView(QString &title, StatisticModel *model)
{
    QChart* chart = new QChart();
    chart->setTitle(title);

    addSeries(chart, model);

    chart->legend()->show();
    chartView = new QChartView(chart);
    return chartView;
}


PieChartCreator::PieChartCreator()
    : AbstractChartCreator(){}

void PieChartCreator::addSeries(QChart *chart, StatisticModel *model)
{
    QPieSeries* pieSeries = new QPieSeries();
    for(int i = 0;i < model->rowCount(QModelIndex());i++)
    {
        QString title = model->data(model->index(i, 0)).toString();
        double precentage = model->data(model->index(i, 1)).toDouble();

        pieSeries->append(title, precentage);
    }

    foreach(QPieSlice* slice, pieSeries->slices())
    {
        slice->setLabel(slice->label() + " " + QString::number(100 * slice->percentage(), 'f', 2));
    }
    chart->addSeries(pieSeries);
}


BarChartCreator::BarChartCreator()
    : AbstractChartCreator(){}

void BarChartCreator::addSeries(QChart *chart, StatisticModel *model)
{

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
}
