#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include "editing.h"
#include <QtDebug>
#include "mainwindow.h"
#include <QFileInfo>
#include "tableprinter.h"
#include <QPainter>
#include <QPrinter>
#include <QFileDialog>

namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = 0);
    ~Dialog1();

private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_CloseLWindow_clicked();


private:
    Ui::Dialog1 *ui;
    QSortFilterProxyModel *sort_filter;
};

#endif // DIALOG1_H
