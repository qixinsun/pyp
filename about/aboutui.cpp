#include "aboutui.h"
#include "ui_aboutui.h"

aboutui::aboutui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutui)
{
    ui->setupUi(this);
}

aboutui::~aboutui()
{
    delete ui;
}
