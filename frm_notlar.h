#ifndef FRM_NOTLAR_H
#define FRM_NOTLAR_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class frm_notlar;
}

class frm_notlar : public QDialog
{
    Q_OBJECT

public:
    explicit frm_notlar(QSqlDatabase db, QWidget *parent = nullptr);
    ~frm_notlar();
    void listele();
    void listele_notlar();
    void closeEvent(QCloseEvent *event);
    int kontrolEt(int ogr_no, int ders_kodu);

private slots:
    void on_tableView_ogrenciler_clicked(const QModelIndex &index);

    void on_tableView_ders_clicked(const QModelIndex &index);

    void on_pushButton_kayitEkle_clicked();

private:
    Ui::frm_notlar *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlQueryModel *model2;
    QSqlQueryModel *model3;
};

#endif // FRM_NOTLAR_H
