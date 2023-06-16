#include "frm_notlar.h"
#include "ui_frm_notlar.h"
#include "mainwindow.h"

frm_notlar::frm_notlar(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_notlar)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(db);

   listele();
   listele_notlar();
}

void frm_notlar::listele()
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

    sorgu->prepare("select * from tblOgrenci");

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Ok");
        return;
    }

    model2 = new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->tableView_ogrenciler->setModel(model2);


}

void frm_notlar::listele_notlar()
{
    sorgu->prepare("select * from tblNotlar");

    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Ok");
        return;
    }

    model3 = new QSqlQueryModel();
    model3->setQuery(*sorgu);
    ui->tableView_notlar->setModel(model3);




}


frm_notlar::~frm_notlar()
{
    delete ui;
}

void frm_notlar::on_tableView_ogrenciler_clicked(const QModelIndex &index)
{
    ui->lineEdit_ogr_no->setText(model2->index(index.row(),0).data().toString());
}


void frm_notlar::on_tableView_ders_clicked(const QModelIndex &index)
{
    ui->lineEdit_dersKodu->setText(model->index(index.row(),0).data().toString());
}


void frm_notlar::on_pushButton_kayitEkle_clicked()
{
    if (ui->lineEdit_ogr_no->text() == "" or ui->lineEdit_dersKodu->text() =="" or ui->lineEdit_vize->text() =="" or ui->lineEdit_final->text() =="")
    {
        QMessageBox::critical(this,"Hata!","Gerekli alanları doldurunuz!","Ok");
    }
    else
    {
        int kayitSayisi;

        kayitSayisi = kontrolEt(ui->lineEdit_ogr_no->text().toInt(), ui->lineEdit_dersKodu->text().toInt());

        if (kayitSayisi >0)
        {
            QMessageBox::critical(this,"Hata","Bu öğrenci üzerinde bu ders zaten tanımlı!","Okay");
        }
        else
        {
            sorgu->prepare("insert into tblNotlar(ogr_no, ders_kodu, vize_not, final_not, gecme_notu) values(?,?,?,?,?)");
            sorgu->addBindValue(ui->lineEdit_ogr_no->text());
            sorgu->addBindValue(ui->lineEdit_dersKodu->text());
            sorgu->addBindValue(ui->lineEdit_vize->text().toInt());
            sorgu->addBindValue(ui->lineEdit_final->text().toInt());
            int gecmeNotu = (ui->lineEdit_vize->text().toInt())*0.4 + (ui->lineEdit_final->text().toInt())*0.6;
            sorgu->addBindValue(gecmeNotu);

            if(!sorgu->exec())
            {
                QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
            }

            listele_notlar();
        }
    }
}

int frm_notlar::kontrolEt(int ogr_no, int ders_kodu)
{

    QSqlQuery query;

    query.prepare("SELECT COUNT (ders_kodu) FROM tblNotlar WHERE ogr_no = ? AND ders_kodu = ?");
    query.addBindValue(ogr_no);
    query.addBindValue(ders_kodu);
    query.exec();
    query.next();

    int sayac= query.value(0).toString().toInt();

    return sayac;
}

void frm_notlar::closeEvent(QCloseEvent *event)
{

        this->close();
        MainWindow *dialog = new MainWindow();
        dialog->show();


}
