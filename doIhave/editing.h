#ifndef EDITING_H
#define EDITING_H

#include <QDialog>
#include "mainwindow.h"
#include "dialog1.h"
#include <QtDebug>

namespace Ui {
class editing;
}

class editing : public QDialog
{
    Q_OBJECT

public:
    explicit editing(QWidget *parent = 0);
    ~editing();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_8_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_help_clicked();

    void on_pushButton_Right_clicked();

    void on_pushButton_Left_clicked();

    void on_pushButton_DeleteAll_clicked();


    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::editing *ui;
   };

#endif // EDITING_H
