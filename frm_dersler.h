#ifndef FRM_DERSLER_H
#define FRM_DERSLER_H

#include <QDialog>

namespace Ui {
class frm_dersler;
}

class frm_dersler : public QDialog
{
    Q_OBJECT

public:
    explicit frm_dersler(QWidget *parent = nullptr);
    ~frm_dersler();

private:
    Ui::frm_dersler *ui;
};

#endif // FRM_DERSLER_H
