#include "renderarea.h"
#include <QPainter>
#include <QStatusBar>
#include <fileparse.h>
#include "seed.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent), seed()
{
    fullMode = false;
    area_w = 100;
    area_h = 100;
    fileName = ":/patterns/mypattern.l";
    FileParse p(area_w, area_h, fileName);
    seed = new Seed(area_w, area_h, p.get()); //FIXME
    rectArray = new QRectF[area_w*area_h]; //FIXME
}

void RenderArea::setAreaSize(int w, int h)
{
    area_w = w;
    area_h = h;
    FileParse p(area_w, area_h, fileName);
    delete seed;
    seed = new Seed(area_w, area_h, p.get());
    delete rectArray;
    rectArray = new QRectF[area_w*area_h];
}

void RenderArea::setFile(QString f)
{
    fileName = f;
    FileParse p(area_w, area_h, fileName);
    delete seed;
    seed = new Seed(area_w, area_h, p.get());
    delete rectArray;
    rectArray = new QRectF[area_w*area_h];
}

void RenderArea::setBar(QStatusBar* b)
{
    bar = b;
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{

    double d;
    double ws = 0;
    double hs = 0;
    if (double(area_w)/(this->width()) < double(area_h)/(this->height()))
    {
        d = double(this->height())/area_h;
        ws = (double(this->width()) - d*area_w)/2;
    }
    else
    {
        d = double(this->width())/area_w;
        hs = (double(this->height()) - d*area_h)/2;
    }


    QPainter painter(this);
    painter.setBrush(cellColor);
    painter.fillRect(QRectF(ws+0,hs+0,d*area_w,d*area_h), QBrush(areaColor));
    const bool* p = seed->get();
    const int* ch = seed->getCangedCells();
    int size = seed->getChangedSize();
    long int k = 0;
    painter.setPen(cellColor);
    painter.setBrush(cellColor);
    for(int i=0;i<size;++i)
    {
        if(p[ch[i]])
        {
            rectArray[k]=QRectF(ws+d*(ch[i]%area_w), hs+d*(ch[i]/area_w), d, d);
            ++k;
        }

    }
    painter.drawRects(rectArray, k);



}

void RenderArea::next_generation()
{
    seed->next_generation();
    bar->showMessage(trUtf8("Поколение: ")+QString::number(seed->getGen())+trUtf8(" Клеток: ")+QString::number(seed->getCells()));
    update();
}

void RenderArea::setAreaColor(QColor c)
{
    areaColor = c;
}

void RenderArea::setCellColor(QColor c)
{
    cellColor = c;
}

void RenderArea::mouseDoubleClickEvent(QMouseEvent* /*event*/)
{
    doubleClick();
}
