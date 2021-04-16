#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>
#include<QFont>
#include<QFontDialog>
#include<QColor>
#include<QColorDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    file_path="";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOPen_triggered()
{
    QString file_name=QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    file_path = file_name;
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"..","File doesnt open");
        return;
    }
    QTextStream in(&file);
    QString text=in.readAll();
    ui->textEdit->setText(text);
    file.close();

}

void MainWindow::on_actionSave_triggered()
{

    QFile file(file_path);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"..","File doesnt open");
        return;
    }
    QTextStream out(&file);
    QString text= ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"Open the file");
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"..","File doesnt open");
        return;
    }
    QTextStream out(&file);
    QString text= ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionFont_settings_triggered()
{
    bool fontSelected;
    QFont font=QFontDialog::getFont(&fontSelected,this);
    if(fontSelected){
        ui->textEdit->setFont(font);
    }
}

void MainWindow::on_actionInformation_triggered()
{
    QString about_text;
    about_text="Author: Vabhoosha\n";
    about_text+="Date: 16-04-2020";
    QMessageBox::about(this,"",about_text);
}

void MainWindow::on_actionBold_triggered()
{
    ui->textEdit->setFontWeight(QFont::Bold);
}

void MainWindow::on_actionItalics_triggered()
{
    ui->textEdit->setFontItalic(true);
}

void MainWindow::on_actionUnderline_triggered()
{
   ui->textEdit->setFontUnderline(true);
}



void MainWindow::on_actionFont_color_triggered()
{
   QColor color=QColorDialog::getColor(Qt::white,this,"Choose Color");
   if(color.isValid()){
       ui->textEdit->setTextColor(color);
   }
}

void MainWindow::on_actionBackground_color_triggered()
{
    QColor color=QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()){
        ui->textEdit->setPalette(QPalette(color));
    }
}
