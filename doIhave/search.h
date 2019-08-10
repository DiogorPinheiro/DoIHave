#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include "mainwindow.h"
#include <QtDebug>


namespace Ui {
class search;
}

class search : public QDialog
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = 0);
    ~search();

private:
    Ui::search *ui;
};

#endif // SEARCH_H
