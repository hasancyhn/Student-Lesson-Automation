#include "frm_ders.h"
#include "ui_frm_ders.h"
#include "mainwindow.h"

frm_ders::frm_ders(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_ders)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);

   listele();
}

void frm_ders::listele()
{
    sorgu->prepare("select * from tblDersler");

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Ok");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_ders->setModel(model);


}

frm_ders::~frm_ders()
{
    delete ui;
}

void frm_ders::on_pushButton_yeni_clicked()
{
    if (ui->lineEdit_dersKodu->text() == "" or ui->lineEdit_dersAdi->text() =="" )
    {
        QMessageBox::critical(this,"Hata!","Gerekli alanları doldurunuz!","Ok");
    }
    else
    {
        int kayitSayisi;

        kayitSayisi = kontrolEt(ui->lineEdit_dersKodu->text().toInt());

        if (kayitSayisi > 0)
        {
            QMessageBox::critical(this,"Hata","Bu kodda başka ders vardır. Farklı kodda ders ekleyiniz!","Okay");
        }
        else
        {


            sorgu->prepare("insert into tblDersler(ders_kodu, ders_adi) values(?,?)");
            sorgu->addBindValue(ui->lineEdit_dersKodu->text().toInt());
            sorgu->addBindValue(ui->lineEdit_dersAdi->text());

            if(!sorgu->exec())
            {
                QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
            }

            listele();

            ui->lineEdit_dersKodu->setText("");
            ui->lineEdit_dersAdi->setText("");
          }

    }
}


int frm_ders::kontrolEt(int ders_kodu)
{

    QSqlQuery query;

    query.prepare("SELECT COUNT (ders_kodu) FROM tblDersler WHERE ders_kodu = ?");
    query.addBindValue(ders_kodu);
    query.exec();
    query.next();

    int sayac= query.value(0).toString().toInt();

    return sayac;
}

int frm_ders::notTablosuKontrolEt(int ders_kodu)
{
    QSqlQuery query;

    query.prepare("SELECT COUNT (ders_kodu) FROM tblNotlar WHERE ders_kodu = ?");
    query.addBindValue(ders_kodu);
    query.exec();
    query.next();

    int sayac= query.value(0).toString().toInt();

    return sayac;


}


void frm_ders::on_pushButton_guncelle_clicked()
{
    if (ui->lineEdit_dersKodu->text() == "" or ui->lineEdit_dersAdi->text() =="" )
    {
        QMessageBox::critical(this,"Hata!","Gerekli alanları doldurunuz!","Ok");
    }
    else
    {
        sorgu->prepare("update tblDersler set ders_kodu=?,ders_adi=? where ders_kodu=?");
        sorgu->addBindValue(ui->lineEdit_dersKodu->text().toInt());
        sorgu->addBindValue(ui->lineEdit_dersAdi->text());
        sorgu->addBindValue(ui->lineEdit_dersKodu->text().toInt());

        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
        }

        listele();

        ui->lineEdit_dersKodu->setText("");
        ui->lineEdit_dersAdi->setText("");
     }
}


void frm_ders::on_pushButton_sil_clicked()
{
    if (ui->lineEdit_dersKodu->text() == "")
    {
        QMessageBox::critical(this,"Hata!","Silinecek ders kodunu giriniz!","Ok");
    }
    else
    {
        int kayitSayisi;

        kayitSayisi = notTablosuKontrolEt(ui->lineEdit_dersKodu->text().toInt());

        if (kayitSayisi >0)
        {
            QMessageBox::critical(this,"Hata","Bu ders silinemez. Bu derse kayıtlı öğrenciler vardır!","Okay");
        }
        else
        {



            sorgu->prepare("delete from tblDersler where ders_kodu=?");
            sorgu->addBindValue(ui->lineEdit_dersKodu->text().toInt());

            if(!sorgu->exec())
            {
                QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
            }

            listele();

            ui->lineEdit_dersKodu->setText("");
            ui->lineEdit_dersAdi->setText("");
        }
    }
}




void frm_ders::on_tableView_ders_clicked(const QModelIndex &index)
{
    ui->lineEdit_dersKodu->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_dersAdi->setText(model->index(index.row(),1).data().toString());

    sorgu->prepare("select * from tblNotlar where ders_kodu=?");
    sorgu->addBindValue(ui->lineEdit_dersKodu->text().toInt());

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Ok");
        return;
    }

    model2 = new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->tableView_dersOgrenci->setModel(model2);


}

void frm_ders::closeEvent(QCloseEvent *event)
{

        this->close();
        MainWindow *dialog = new MainWindow();
        dialog->show();


}

