#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frm_ogrenci.h"
#include "frm_ders.h"
#include "frm_notlar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db.setDatabaseName("./dbNotlar.db");
    if(!db.open())
    {
        ui->statusbar->showMessage("Veri tabanına bağlanamadı.");
    }

    else
    {
         ui->statusbar->showMessage("Veri tabanına bağlandı");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_ogrenci_clicked()
{
    this->hide();
    frm_ogrenci *ogr = new frm_ogrenci(db);
    ogr->show();
}


void MainWindow::on_btn_ders_clicked()
{
    this->hide();
    frm_ders *ders = new frm_ders(db);
    ders->show();
}



void MainWindow::on_btn_notlar_clicked()
{
    this->hide();
    frm_notlar *notlar = new frm_notlar(db);
    notlar->show();
}

