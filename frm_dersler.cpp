#include "frm_dersler.h"
#include "ui_frm_dersler.h"

frm_dersler::frm_dersler(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_dersler)
{
    ui->setupUi(this);
}

frm_dersler::~frm_dersler()
{
    delete ui;
}
