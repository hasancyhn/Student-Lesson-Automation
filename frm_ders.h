#ifndef FRM_DERS_H
#define FRM_DERS_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class frm_ders;
}

class frm_ders : public QDialog
{
    Q_OBJECT

public:
    explicit frm_ders(QSqlDatabase db, QWidget *parent = nullptr);
    ~frm_ders();
    void listele();
    void closeEvent(QCloseEvent *event);
    int kontrolEt(int ders_kodu);
    int notTablosuKontrolEt(int ders_kodu);

private slots:
    void on_pushButton_yeni_clicked();

    void on_pushButton_guncelle_clicked();

    void on_pushButton_sil_clicked();

    void on_tableView_ders_clicked(const QModelIndex &index);

private:
    Ui::frm_ders *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlQueryModel *model2;
};

#endif // FRM_DERS_H
