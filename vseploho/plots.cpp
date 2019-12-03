#include "plots.h"
#include "ui_plots.h"
#include <QPen>

plots::plots(QVector<double> *matr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plots)
{
    ui->setupUi(this);
    for(int i = 0; i<=matr[0].size(); ++i)
    {
        x.push_back(i);
    }
    for(int i = 0; i<5; ++i)
    {
        ui->widgetPlots->addGraph();
        ui->widgetPlots->graph(i)->setData(x, matr[i]);
    }
    ui->widgetPlots->graph(0)->setPen(QPen(Qt::red));
    ui->widgetPlots->graph(1)->setPen(QPen(Qt::green));
    ui->widgetPlots->graph(2)->setPen(QPen(Qt::blue));
    ui->widgetPlots->graph(3)->setPen(QPen(Qt::yellow));
    ui->widgetPlots->graph(4)->setPen(QPen(Qt::magenta));

    auto max = 0;
    for(int i = 0; i<5; ++i)
        if(max < matr[i][0]) max = matr[i][0];
    ui->widgetPlots->yAxis->setRange(0, max);
    ui->widgetPlots->xAxis->setRange(0, matr[0].size());
    ui->widgetPlots->yAxis2->setRange(0, max);
    ui->widgetPlots->xAxis2->setRange(0, matr[0].size());


}

plots::~plots()
{
    delete ui;
}
