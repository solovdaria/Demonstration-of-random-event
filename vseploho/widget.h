#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QInputDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QTimer>
#include <QMap>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class FallingCircle:public QGraphicsEllipseItem
{
public:
    FallingCircle(int xspread, int &N);
    // QGraphicsItem interface

    void advance(int phase);

QColor colour;
void setYspeed(int value);

private:
int yspeed=2;
int& N;

    QColor color[5]={Qt::red, Qt::yellow, Qt::blue, Qt::green,Qt::magenta};
};


class Box:public QGraphicsRectItem
{
public:
    Box();
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int getN() const;
    int counterR=0;
    int counterY=0;
    int counterG=0;
    int counterB=0;
    int counterM=0;
    int countColor[5] {0, 0, 0, 0, 0};
     QVector<double> colorsCount[5];
private slots:
    void onGenerate();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    int N;

    Ui::Widget *ui;
    QGraphicsScene* scene;
    QTimer* animationTimer;
    QTimer* generatorTimer;
    QVector<FallingCircle*> arr;
    QPushButton* btn;
    FallingCircle* current = nullptr;

    QGraphicsSimpleTextItem* frame;
    QGraphicsSimpleTextItem* frame1; QGraphicsSimpleTextItem* frame2; QGraphicsSimpleTextItem* frame3;
    QGraphicsSimpleTextItem* frame4; QGraphicsSimpleTextItem* frame5;
    QMap<QString, QString> colors
    {
        {QColor(Qt::red).name(), "red"},
        {QColor(Qt::green).name(), "green"},
        {QColor(Qt::blue).name(), "blue"},
        {QColor(Qt::yellow).name(), "yellow"},
        {QColor(Qt::magenta).name(), "purple"}
    }
    ;

  };
#endif // WIDGET_H
