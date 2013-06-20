#include "dialog.h"
#include "ui_dialog.h"
#include <QColorDialog>

myDialog::myDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDialog)
{
    ui->setupUi(this);
    area_w = 120;
    area_h = 100;
    area_s = 100;
    areaColor = Qt::black;
    cellColor = Qt::green;
    QRegExp rx("\\d+");
    numValidator = new QRegExpValidator(rx,NULL);
    ui->widthLineEdit->setValidator(numValidator);
    ui->heightLineEdit->setValidator(numValidator);
    ui->widthLineEdit->setText(QString::number(area_w));
    ui->heightLineEdit->setText(QString::number(area_h));
    ui->speedLineEdit->setText(QString::number(area_s));
}


myDialog::~myDialog()
{
    delete numValidator;
    delete ui;
}

void myDialog::on_buttonBox_accepted()
{
    int w = ui->widthLineEdit->text().toInt();
    int h = ui->heightLineEdit->text().toInt();
    if(area_w == w && area_h == h)
    {
        areaSizeChanged = false;
    }
    else
    {
        areaSizeChanged = true;
        area_w = w;
        area_h = h;
    }
    area_s = ui->speedLineEdit->text().toInt();
}

void myDialog::on_buttonBox_rejected()
{
    ui->widthLineEdit->setText(QString::number(area_w));
    ui->heightLineEdit->setText(QString::number(area_h));
    ui->speedLineEdit->setText(QString::number(area_s));
}

int myDialog::getAreaWidth()
{
    return area_w;
}

int myDialog::getAreaHeight()
{
    return area_h;
}

int myDialog::getAreaSpeed()
{
    return area_s;
}

bool myDialog::sizeChanged()
{
    return areaSizeChanged;
}

void myDialog::on_cellColorButton_clicked()
{
    QColor c = QColorDialog::getColor(cellColor);
    if(c.isValid())
        cellColor = c;
}

void myDialog::on_areaColorButton_clicked()
{
    QColor c = QColorDialog::getColor(areaColor);
    if(c.isValid())
        areaColor = c;
}

QColor myDialog::getAreaColor()
{
    return areaColor;
}

QColor myDialog::getCellColor()
{
    return cellColor;
}


