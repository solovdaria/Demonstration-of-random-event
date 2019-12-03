#ifndef PLOTS_H
#define PLOTS_H

#include <QWidget>
#include <QVector>

namespace Ui {
class plots;
}

class plots : public QWidget
{
    Q_OBJECT

public:
    explicit plots(QVector<double>* matr, QWidget *parent = nullptr);
    ~plots();

private:
    Ui::plots *ui;
    QVector<double> x;
};

#endif // PLOTS_H
