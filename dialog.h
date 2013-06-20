#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QRegExpValidator>
#include "mainwindow.h"

namespace Ui {
class myDialog;
}

class myDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit myDialog(QWidget *parent = 0);
    ~myDialog();
    int getAreaWidth();
    int getAreaHeight();
    int getAreaSpeed();
    QColor getCellColor();
    QColor getAreaColor();
    bool sizeChanged();
private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_cellColorButton_clicked();

    void on_areaColorButton_clicked();

private:

    int area_w;
    int area_h;
    int area_s;
    QColor areaColor;
    QColor cellColor;
    bool areaSizeChanged;
    Ui::myDialog *ui;
    QRegExpValidator *numValidator;
};

#endif // DIALOG_H
