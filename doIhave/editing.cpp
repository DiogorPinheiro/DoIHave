#include "editing.h"
#include "ui_editing.h"
#include <QtGui>
#include <QtDebug>
#include <QMessageBox>
#include <QToolTip>

editing::editing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editing)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Removes the Help option in the window Application
    setWindowIcon(QIcon(":/new/prefix1/dIh.ico"));          //Window app Icon

    //-------------------------Graphics------------------------------------------
    ui->lineEdit->setStyleSheet("border-color: rgb(0, 162, 232);");
    ui->lineEdit_2->setStyleSheet("border-color: rgb(0, 162, 232);");
    ui->lineEdit_3->setStyleSheet("border-color: rgb(0, 162, 232);");
    ui->lineEdit_4->setStyleSheet("border-color:1px rgb(0, 162, 232);");
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_DeleteAll->setVisible(false);

    ui->comboBox->setVisible(false);
    ui->pushButton_exit->setVisible(false);
    ui->pushButton_help->setVisible(false);
    ui->comboBox_2->setVisible(false);
    ui->pushButton_10->setVisible(false);



}

editing::~editing()
{
    delete ui;
}

void editing::on_pushButton_7_clicked()
{
    //Close window
    hide();
}

void editing::on_pushButton_4_clicked()
{   //Save
    if(ui->lineEdit->text().isEmpty() &&   ui->lineEdit_4->text().isEmpty() && ui->lineEdit_2->text().isEmpty() && ui->lineEdit_3->text().isEmpty()){
        QMessageBox::critical(this,tr("Error"),tr("No input detected..."));
    }   // Doesn't allow the user to save an empty item
    else{
    MainWindow conn;
    QString Title,Author,Year,Category;
    Title=ui->lineEdit->text();
    Author=ui->lineEdit_2->text();
    Year=ui->lineEdit_3->text();
    Category=ui->lineEdit_4->text();



    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }

   conn.connOpen();             //Abrir conexão
    QSqlQuery qry;
    qry.prepare("insert into data (Title,Author,Year,Category)values('"+Title+"','"+Author+"','"+Year+"','"+Category+"')" );     //Insert into tablename (parameters)


    if(qry.exec()){
           conn.connClose();
          ui->label_StatusW3->setText("Saved...");
          hide();
          editing addwindow;            //Refresh page
          addwindow.setModal(true);
          addwindow.exec();
        }
        //QMessageBox::critical(this,tr("Save"),tr("My Data is saved!"));

    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());

    }
        }
}

void editing::on_pushButton_6_clicked()
{
    //Fazer Update na database
       MainWindow conn;
       QString Title,Author,Year,Category,rowid;
       Title=ui->lineEdit->text();
       Author=ui->lineEdit_2->text();
       Year=ui->lineEdit_3->text();
       Category=ui->lineEdit_4->text();


       if(!conn.connOpen()){
           qDebug()<<"Failed to open the database";
           return;
       }

      conn.connOpen();             //Abrir conexão
       QSqlQuery qry;
       qry.prepare("update data set Title='"+Title+"',Author='"+Author+"',Year='"+Year+"',Category='"+Category+"' where Title='"+Title+"' ");     //Insert into tablename (parameters)
        // This Sql  statement doesn't allow the user  to change the title of an item

       if(qry.exec()){
           conn.connClose();
           ui->label_StatusW3->setText("Updated...");
           hide();
           editing addwindow;               //Refresh page to display updated Data
           addwindow.setModal(true);
           addwindow.exec();
           ui->pushButton_4->setEnabled(true);         //Set Save button Inactive. User needs to click on the "Update" button to save

       }
       else{
           QMessageBox::critical(this,tr("Error::"),qry.lastError().text());

       }
}

void editing::on_pushButton_5_clicked()
{   //Delete
    MainWindow conn;
    QString Title,Author,Year,Category;
    Title=ui->lineEdit->text();
    Author=ui->lineEdit_2->text();



    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }
    conn.connOpen();
    //------------------------QMessage---------------------------------------
    QMessageBox msgBox;             // ask if the user really wants to delete item
    msgBox.setWindowTitle("Remove ?");
    msgBox.setText("Are you sure you want to remove this item? ");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        QSqlQuery qry;
        qry.prepare("Delete from data where Title='"+Title+"'and Author ='"+Author+"'");     //Insert into tablename (parameters)


        if(qry.exec()){
            //QMessageBox::critical(this,tr("Delete"),tr("Data deleted..."));
            conn.connClose();
            ui->label_StatusW3->setText("Removed...");
            hide();
            editing addwindow;
            addwindow.setModal(true);
            addwindow.exec();

        }
        else{
            QMessageBox::critical(this,tr("Error::"),qry.lastError().text());

        }
    }else {
      // do something else
    }


}

void editing::on_comboBox_currentIndexChanged(const QString &arg1)
{
   QString rowid=ui->comboBox->currentText();


    MainWindow conn;

    if(!conn.connOpen()){                               // if connection fails
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen();             //Open connection
    QSqlQuery qry;
    qry.prepare("select * from data where rowid = '"+rowid+"'" );     //Insert into tablename (parameters)


    if(qry.exec()){
        while(qry.next()){                                          //Setting the Data of the corresponding Title to the Line Edit of each parameter
            ui->lineEdit->setText(qry.value(1).toString());
            ui->lineEdit_4->setText(qry.value(0).toString());
            ui->lineEdit_2->setText(qry.value(2).toString());
            ui->lineEdit_3->setText(qry.value(3).toString());

        }
        conn.connClose();

    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());

    }

}

void editing::on_pushButton_8_clicked()
{   //Edit Button
   ui->comboBox->setVisible(true);                  //Show ComboBox and an Exit button to close the ComboBox and clear all the Line Edit
   ui->pushButton_exit->setVisible(true);
   ui->pushButton_help->setVisible(true);
    ui->pushButton_4->setEnabled(false);
   MainWindow conn;
   QSqlQueryModel *modal = new QSqlQueryModel();
   conn.connOpen();
   QSqlQuery * qry =new QSqlQuery(conn.mydb);
   qry->prepare("select  rowid from data");      //Show Titles in ComboBox
   qry->exec();
   modal->setQuery(*qry);
   ui->comboBox->setModel(modal);
   conn.connClose();                            //Opening conection to transmit values to the ComboBox
   qDebug() <<(modal->rowCount());
}

void editing::on_pushButton_exit_clicked()
{   //Close button in Edit mode
    MainWindow conn;
    conn.connClose();
    ui->comboBox->setVisible(false);
    ui->pushButton_exit->setVisible(false);
    ui->pushButton_help->setVisible(false);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();

    hide();
    editing addwindow;            //Refresh page
    addwindow.setModal(true);
    addwindow.exec();

}

void editing::on_pushButton_Clear_clicked()
{   //Clear All Button
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

void editing::on_pushButton_help_clicked()
{
    QMessageBox::information(this,"Help","1)In Edit Mode, use the 'Update' button to save your modifications;                                                                       "
                                         "2)You can't change the title of an item.");
}

void editing::on_pushButton_Right_clicked()
{
    ui->pushButton_4->setVisible(false);
    ui->pushButton_DeleteAll->setVisible(true);
    ui->pushButton_6->setVisible(false);
    ui->pushButton_8->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->pushButton_Clear->setVisible(false);
    ui->pushButton_7->setVisible(false);
    ui->pushButton_Right->setVisible(false);
}

void editing::on_pushButton_Left_clicked()
{
    ui->pushButton_4->setVisible(true);
    ui->pushButton_DeleteAll->setVisible(false);
    ui->pushButton_6->setVisible(true);
    ui->pushButton_8->setVisible(true);
    ui->pushButton_5->setVisible(true);
    ui->pushButton_Clear->setVisible(true);
    ui->pushButton_7->setVisible(true);
    ui->pushButton_Right->setVisible(true);
}

void editing::on_pushButton_DeleteAll_clicked()
{
    MainWindow conn;
    QString Title,Author,Year,Category;
    Title=ui->lineEdit->text();
    Author=ui->lineEdit_2->text();



    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }
    conn.connOpen();
    //------------------------QMessage---------------------------------------
    QMessageBox msgBox;             // ask if the user really wants to delete item
    msgBox.setWindowTitle("Remove ?");
    msgBox.setText("This will remove all the items in your list. Are you sure you want to proceed ? ");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        QSqlQuery qry;
        qry.prepare("Delete from data");     //Insert into tablename (parameters)


        if(qry.exec()){
            //QMessageBox::critical(this,tr("Delete"),tr("Data deleted..."));
            conn.connClose();
            ui->label_StatusW3->setText("All data removed... ");
            hide();
            editing addwindow;
            addwindow.setModal(true);
            addwindow.exec();

        }
        else{
            QMessageBox::critical(this,tr("Error::"),qry.lastError().text());

        }
    }else {
      // do something else
    }

}


void editing::on_comboBox_2_currentIndexChanged(int index)
{   //ComboBox connection to Category lineEdit
    QString Category=ui->comboBox_2->currentText();


     MainWindow conn;

     if(!conn.connOpen()){                               // if connection fails
         qDebug()<<"Failed to open the database";
         return;
     }

     conn.connOpen();             //Open connection
     QSqlQuery qry;
     qry.prepare("select Category from data where Category = '"+Category+"'" );     //Insert into tablename (parameters)


     if(qry.exec()){
         while(qry.next()){                                          //Setting the Data of the corresponding Title to the Line Edit of each parameter
             ui->lineEdit_4->setText(qry.value(0).toString());


         }
         conn.connClose();

     }
     else{
         QMessageBox::critical(this,tr("Error::"),qry.lastError().text());

     }

}

void editing::on_pushButton_9_clicked()
{   //Used category option
    ui->comboBox_2->setVisible(true);
    ui->pushButton_9->setVisible(false);
    ui->pushButton_10->setVisible(true);


   MainWindow conn;
   QSqlQueryModel *modal = new QSqlQueryModel();
   conn.connOpen();
   QSqlQuery * qry =new QSqlQuery(conn.mydb);
   qry->prepare("select  Category from data");
   qry->exec();
   modal->setQuery(*qry);
   ui->comboBox_2->setModel(modal);
   conn.connClose();
}

void editing::on_pushButton_10_clicked()
{   //Close used category option mode
    ui->comboBox_2->setVisible(false);
    ui->lineEdit_4->clear();
    ui->pushButton_9->setVisible(true);
    ui->pushButton_10->setVisible(false);

}
