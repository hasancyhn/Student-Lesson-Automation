#ifndef FRM_OGRENCI_H
#define FRM_OGRENCI_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class frm_ogrenci;
}

class frm_ogrenci : public QWidget
{
    Q_OBJECT

public:
    explicit frm_ogrenci(QSqlDatabase db, QWidget *parent = nullptr);
    ~frm_ogrenci();
    void listele();
    void closeEvent(QCloseEvent *event);
    int kontrolEt(int ogr_no);

private slots:
    void on_tableView_ogrenciler_clicked(const QModelIndex &index);

    void on_pushButton_yeni_clicked();

    void on_pushButton_guncelle_clicked();

    void on_pushButton_sil_clicked();

private:
    Ui::frm_ogrenci *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
};

#endif // FRM_OGRENCI_H
