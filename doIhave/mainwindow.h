#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileInfo>
#include "dialog1.h"
#include "editing.h"
#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QRegExp>
#include "tableprinter.h"
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QFile>
#include <QTextStream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //-----------------------------SQL--------------------------------------------------------
    QSqlDatabase mydb;
    void connClose(){
        mydb.close();
        mydb.database(QSqlDatabase::defaultConnection);
    }

    bool connOpen(){
        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("DIH_database.db");
        if (!mydb.open()){
            qDebug()<<("Failed to connect to database...");
            return false;
        }
        else{
            qDebug()<<("Connected...");
            return true;
        }
    }
    //---------------------------------------------------------------------------------------

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionCategories_triggered();

    void on_pushButton_Search_clicked();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionAdd_List_triggered();


    void on_pushButton_catwindow_clicked();


    void on_actionCredits_triggered();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_exit_clicked();


private:
    Ui::MainWindow *ui;
    QSqlRelationalTableModel *modPerson;
    QSortFilterProxyModel * proxymod;

};


#endif // MAINWINDOW_H
