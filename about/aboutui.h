#ifndef ABOUTUI_H
#define ABOUTUI_H

#include <QDialog>

namespace Ui {
class aboutui;
}

class aboutui : public QDialog
{
    Q_OBJECT

public:
    explicit aboutui(QWidget *parent = 0);
    ~aboutui();

private:
    Ui::aboutui *ui;
};

#endif // ABOUTUI_H
