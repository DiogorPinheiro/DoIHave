#include "dialog1.h"
#include "ui_dialog1.h"
#include <QHeaderView>
#include <QResizeEvent>
#include <QSqlRelationalTableModel>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QPrintDialog>
#include <QtAlgorithms>

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);       // Minimize Window
    setWindowIcon(QIcon(":/new/prefix1/dIh.ico"));                      //Window Application Icon


    MainWindow conn;
    QSqlQueryModel *modal = new QSqlQueryModel();
    conn.connOpen();                                                // Open SQl connection
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("select Category,Title,Author,Year from data ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);                                 //Set table
    conn.connClose();
    ui->tableView->setVisible(false);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setVisible(true);
    qDebug() << (modal->rowCount());
    ui->tableView->setSortingEnabled(true);
    //-------------------------Column Width-------------------------
    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,500);
    ui->tableView->setColumnWidth(2,287);
    ui->tableView->setColumnWidth(3,52);
    //-----------------------Sorting column------------------------
    QSortFilterProxyModel *sort_filter = new QSortFilterProxyModel(this);
    sort_filter->setSourceModel(modal);
    sort_filter->sort (0);
    this->ui->tableView->setModel (sort_filter);

    QAbstractItemModel* tableModel=  ui->tableView->model();        //Counting Rows
    int iRows = tableModel->rowCount();
        ui->label->setText(QString("%1").arg(iRows, 2, 10, QChar('0')));        //Display value





}

Dialog1::~Dialog1()
{
    delete ui;
}


void Dialog1::on_pushButton_Add_clicked()
{       //Open Add Window
    editing addwindow;
    addwindow.setModal(true);
    addwindow.exec();
}

void Dialog1::on_pushButton_CloseLWindow_clicked()
{   //Return to Home page
    this->hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();

}


