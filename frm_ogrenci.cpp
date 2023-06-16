#include "frm_ogrenci.h"
#include "ui_frm_ogrenci.h"
#include "mainwindow.h"

frm_ogrenci::frm_ogrenci(QSqlDatabase db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frm_ogrenci)
{
    ui->setupUi(this);

    sorgu = new QSqlQuery(db);

   listele();
}


void frm_ogrenci::listele()
{
    sorgu->prepare("select * from tblOgrenci");

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Ok");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_ogrenciler->setModel(model);

}


frm_ogrenci::~frm_ogrenci()
{
    delete ui;

}

void frm_ogrenci::on_tableView_ogrenciler_clicked(const QModelIndex &index)
{
    ui->lineEdit_no->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_ad->setText(model->index(index.row(),1).data().toString());
    ui->lineEdit_soyad->setText(model->index(index.row(),2).data().toString());
}


void frm_ogrenci::on_pushButton_yeni_clicked()
{

    if (ui->lineEdit_ad->text() == "" or ui->lineEdit_soyad->text() =="" )
    {
        QMessageBox::critical(this,"Hata!","Gerekli alanları doldurunuz!","Ok");
    }
    else
    {
        sorgu->prepare("insert into tblOgrenci(ogr_ad, ogr_soyad) values(?,?)");
        sorgu->addBindValue(ui->lineEdit_ad->text());
        sorgu->addBindValue(ui->lineEdit_soyad->text());

        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
        }

        listele();

        ui->lineEdit_ad->setText("");
        ui->lineEdit_soyad->setText("");
        ui->lineEdit_no->setText("");
    }

}


void frm_ogrenci::on_pushButton_guncelle_clicked()
{
    if (ui->lineEdit_ad->text() == "" or ui->lineEdit_soyad->text() =="" )
    {
        QMessageBox::critical(this,"Hata!","Gerekli alanları doldurunuz!","Ok");
    }
    else
    {

        sorgu->prepare("update tblOgrenci set ogr_ad=?,ogr_soyad=? where ogr_no=?");
        sorgu->addBindValue(ui->lineEdit_ad->text());
        sorgu->addBindValue(ui->lineEdit_soyad->text());
        sorgu->addBindValue(ui->lineEdit_no->text().toInt());

        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
        }

        listele();

        ui->lineEdit_ad->setText("");
        ui->lineEdit_soyad->setText("");
        ui->lineEdit_no->setText("");
     }
}

int frm_ogrenci::kontrolEt(int ogr_no)
{

    QSqlQuery query;

    query.prepare("SELECT COUNT (ogr_no) FROM tblNotlar WHERE ogr_no = ?");
    query.addBindValue(ogr_no);
    query.exec();
    query.next();

    int sayac= query.value(0).toString().toInt();

    return sayac;
}

void frm_ogrenci::on_pushButton_sil_clicked()
{
    if (ui->lineEdit_no->text() == "")
    {
        QMessageBox::critical(this,"Hata!","Listeden bir kayıt seçiniz!","Ok");
    }
    else
    {
        int kayitSayisi;

        kayitSayisi = kontrolEt(ui->lineEdit_no->text().toInt());



        if (kayitSayisi > 0)
        {
            QMessageBox::critical(this,"Hata","Öğrenci silinemez. Bu öğrencinin üzerine tanımlanmış dersler vardır!","Okay");
        }
        else
        {

            sorgu->prepare("delete from tblOgrenci where ogr_no=?");
            sorgu->addBindValue(ui->lineEdit_no->text().toInt());

            if(!sorgu->exec())
            {
                QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
            }

            listele();

            ui->lineEdit_ad->setText("");
            ui->lineEdit_soyad->setText("");
            ui->lineEdit_no->setText("");


        }


    }
}



void frm_ogrenci::closeEvent(QCloseEvent *event)
{

        this->close();
        MainWindow *dialog = new MainWindow();
        dialog->show();


}

