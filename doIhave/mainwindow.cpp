#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QWidget>
#include <QSplashScreen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //--------------------------Graphics---------------------------------------------------------------
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");
    ui->statusBar->setStyleSheet("background-color: rgb(0, 162, 232);");
    ui->menuBar->setStyleSheet("background-color: white");
    ui->mainToolBar->setStyleSheet("background-color: white;");
    ui->lineEdit->setStyleSheet("border-color: rgb(0, 162, 232);");
    ui->tableView->setVisible(false);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);      //Removes Maximize Window option. I want the window to remain the same size
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);       // Minimize Window
    setWindowIcon(QIcon(":/new/prefix1/dIh.ico"));                      //Window App Icon

    //--------------------------SQL--------------------------------------------------------------------
   /* connOpen();
    if (!mydb.open())
        ui->statusBar->showMessage("Failed to connect to database...");
    else
        ui->statusBar->showMessage("Connected...",6000);
*/
    //--------------------------Table and Sql-------------------------------------------------------

    ui->statusBar->showMessage("Searching...",2000);
    if(!connOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }
    connOpen();
        if (!mydb.open())
            ui->statusBar->showMessage("Failed to connect to database...");
        else
            ui->statusBar->showMessage("Connected...",6000);

        modPerson= new QSqlRelationalTableModel(this);          //Setting Relational table in order to make a connection with the search filter
        modPerson->setTable("data");
        modPerson->select();
        modPerson->setRelation(modPerson->fieldIndex("data"),QSqlRelation("data","Category","Title"));

        proxymod = new QSortFilterProxyModel(this);
        proxymod->setSourceModel(modPerson);                            //Setting the filter source to the Relational table
        proxymod->setFilterCaseSensitivity(Qt::CaseInsensitive);            //Filter is case insensitive
        proxymod->setFilterKeyColumn(-1);
        ui->comboBox->addItems(QStringList() << "Category" << "Title" << "Author" << "Year");       //Connecting columns to the ComboBox filter
        ui->tableView->resizeColumnsToContents();
        ui->pushButton_exit->setVisible(false);
        ui->tableView->setModel(proxymod);          //Setting the table wwith the filtered model
    }






MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCategories_triggered()
{
    //-------------------------Category Window---------------------------------------------------------
   //this->hide();
   Dialog1 secwindow;
   secwindow.setModal(true);
   secwindow.exec();
   this->hide();
}

void MainWindow::on_pushButton_Search_clicked()
{   //Search
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::critical(this,tr("Error"),tr("No input detected..."));
        ui->tableView->setVisible(false);                //table and the pushButton to hide it are visible when this button is clicked
        ui->pushButton_exit->setVisible(false);
    } else {
    ui->tableView->setVisible(true);                //table and the pushButton to hide it are visible when this button is clicked
    ui->pushButton_exit->setVisible(true);
    }
}

void MainWindow::on_actionSave_triggered()
{
    ui->statusBar->showMessage("Saved...",1000);
}

void MainWindow::on_actionExit_triggered()
{
   //Close
    QMessageBox msgBox;             // ask if the user really wants to Exit
    msgBox.setWindowTitle("Exit doIhave ?");
    msgBox.setText("Are you sure you want to exit doIhave? ");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes)
        QApplication::quit();

}

void MainWindow::on_actionAdd_List_triggered()
{
    //open the add Window
    editing addwindow;
    addwindow.setModal(true);
    addwindow.exec();
    connClose();        //Connection to the sql database is only allowed in 1 window,this closes the sql in the main window to open in the add window
    ui->statusBar->showMessage("",1000);
}

void MainWindow::on_pushButton_catwindow_clicked()
{
    //-------------------------Category Window---------------------------------------------------------
   this->hide();
   Dialog1 secwindow;
   secwindow.setModal(true);
   secwindow.exec();
}



void MainWindow::on_actionCredits_triggered()
{   //Show splash screen when credits button is triggered
    QSplashScreen *splashe = new QSplashScreen();
    splashe->setPixmap(QPixmap(":/new/prefix1/Imagens/doIhave_Credits.png"));       //Uses image in the resources
    splashe->show();
    splashe->showMessage("Starting...");
    //QSplashScreen splash(pixmap,Qt::WindowStaysOnTopHint);
    QTimer::singleShot(4000,splashe,SLOT(close()));                 //Time in ms
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    proxymod->setFilterFixedString(arg1);       //Connect Text written by the user to the search filter
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    proxymod->setFilterKeyColumn(index);        //Connect search filter with comboBox

}

void MainWindow::on_pushButton_exit_clicked()
{   // Hides table and this button. Clears the LineEdit
    ui->pushButton_exit->setVisible(false);
    ui->tableView->setVisible(false);
    ui->lineEdit->clear();
}


