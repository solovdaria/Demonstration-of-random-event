#include "widget.h"
#include "ui_widget.h"
#include <QtCore>
#include <QtGui>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFont>
#include "plots.h"

#define CIRCLE_SIZE 70

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, 600, 600, this);
    QColor c = QColor(Qt::yellow).lighter(170);
    scene->setBackgroundBrush(QBrush(c));
    setFixedSize(850, 650);
    ui->graphicsView->setScene(scene);

    QGraphicsRectItem* rect2=new QGraphicsRectItem;
    QColor color2= QColor(255, 230, 255);
    rect2->setBrush(color2);
    rect2->setRect(0, 0, 225, 200);
    rect2->setPos(0,0);
    scene->addItem(rect2);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, scene, &QGraphicsScene::advance);

    generatorTimer = new QTimer(this);

    connect(generatorTimer, &QTimer::timeout, this, &Widget::onGenerate);

    frame = new QGraphicsSimpleTextItem();
    frame1 = new QGraphicsSimpleTextItem();frame2 = new QGraphicsSimpleTextItem();frame3 = new QGraphicsSimpleTextItem();
    frame4 = new QGraphicsSimpleTextItem();frame5 = new QGraphicsSimpleTextItem();
    frame1->setX(3); frame2->setX(3);frame3->setX(3);frame4->setX(3);frame5->setX(3);frame->setX(25);
    frame->setY(0);frame1->setY(25);frame2->setY(50);frame3->setY(75);frame4->setY(100);frame5->setY(125);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::onGenerate()
{
    int counter=0;
    while (counter != N)
    {

      auto circle = new FallingCircle(scene->sceneRect().width(), N);
      arr.push_back(circle);
            if(circle->colour==QColor(Qt::red)) ++countColor[0];
            else if (circle->colour==QColor(Qt::yellow)) ++countColor[1];
            else if (circle->colour==QColor(Qt::green)) ++countColor[2];
            else if (circle->colour==QColor(Qt::blue)) ++countColor[3];
            else if (circle->colour==QColor(Qt::magenta)) ++countColor[4];
      scene->addItem(circle);

      counter++;
    }
    for(int i = 0; i<5; ++i)
    {
        colorsCount[i].push_back(countColor[i]);
        qDebug()<<colorsCount[i];
    }
    qDebug()<<"";

    generatorTimer->stop();

    scene->addItem(new Box());

    auto *proxy = new QGraphicsProxyWidget();
    btn = new QPushButton("Get ball");


    connect(btn, &QPushButton::clicked, this, [this]
    {
        if(arr.isEmpty()){ QMessageBox::information(this, "Info", "Box is empty"); return;}
        scene->addItem(arr[0]);
        if (arr[0]->colour==QColor(Qt::red)){ --countColor[0]; ++counterR;}
        else if (arr[0]->colour==QColor(Qt::yellow)){ --countColor[1]; ++counterY;}
        else if (arr[0]->colour==QColor(Qt::green)){ --countColor[2]; ++counterG;}
        else if (arr[0]->colour==QColor(Qt::blue)){ --countColor[3]; ++counterB;}
        else if (arr[0]->colour==QColor(Qt::magenta)){ --countColor[4]; ++counterM;}

        for(int i = 0; i<5; ++i)
        {
            colorsCount[i].push_back(countColor[i]);
            qDebug()<<colorsCount[i];
        }
        qDebug()<<"";



        QString text1;QString text2;QString text3;QString text4;QString text5;QString text6;
        QString text="GOT BALLS:";
        QFont newfont("Courier", 12, QFont::Bold, true);
        frame1->setFont(newfont); frame2->setFont(newfont); frame3->setFont(newfont); frame4->setFont(newfont);
         frame5->setFont(newfont); frame->setFont(newfont);
        text1 = "RED "+QString::number(counterR); text2="YELLOW "+QString::number(counterY);
        text3="GREEN "+QString::number(counterG);text4="BLUE "+QString::number(counterB);
        text5="PURPLE "+QString::number(counterM);

        scene->addItem(frame1);scene->addItem(frame2);scene->addItem(frame3);scene->addItem(frame4);scene->addItem(frame5);
frame1->setText(text1);frame2->setText(text2);frame3->setText(text3);frame4->setText(text4);frame5->setText(text5);
       scene->addItem(frame);frame->setText(text);





        arr[0]->setRect(275, 200, CIRCLE_SIZE, CIRCLE_SIZE);
//        animationTimer->stop();
        arr[0]->setYspeed(0);
        arr[0]->setPos(0, 0);
        if(current)
        delete current;
        current = arr[0];
        arr.pop_front();
    });

    btn->setGeometry(240, 425, 120, 100);

    proxy->setWidget(btn);
    scene->addItem(proxy);
}


FallingCircle::FallingCircle(int xspread, int &N): QGraphicsEllipseItem(nullptr), N(N)
{
    colour = color[rand()%5];
    QColor col=colour;
    setBrush(col);
    qDebug()<<(this->colour.name());
    setRect(150, 0, CIRCLE_SIZE, CIRCLE_SIZE);
    setPos(rand()%(xspread-CIRCLE_SIZE-300), 0);
}

void FallingCircle::advance(int phase)
{
     if(phase)
     {
           moveBy(0, yspeed);
     }
}

void FallingCircle::setYspeed(int value)
{
    yspeed = value;
}

Box::Box(): QGraphicsRectItem(nullptr)
{
    QColor color1 = QColor(165, 100, 0);
    setBrush(color1);
    setRect(100, 350, 400, 250);
    setPos(0,0);

    auto* btn=new QPushButton("Get ball");
    btn->setGeometry(300, 475, 50, 50);
}


void Widget::on_pushButton_clicked()
{
   N = QInputDialog::getInt(this, "Adding balls", "Enter number of balls");
   animationTimer->start(1000/60);
   generatorTimer->start(1000);
   for(int i =0; i<5; ++i){ colorsCount[i].clear(); countColor[i] = 0;}
   counterB = counterG = counterM = counterR = counterY = 0;
   frame1->setText("");
   frame2->setText("");
   frame3->setText("");
   frame4->setText("");
   frame5->setText("");
}


int Widget::getN() const
{
    return N;
}



void Widget::on_pushButton_2_clicked()
{
    delete current;
    current = nullptr;
    for(int i = 0; i<arr.size(); ++i) delete arr[i];
    auto plotWindow = new plots(colorsCount);
    plotWindow->show();
}
