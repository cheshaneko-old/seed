#ifndef RENDERAREA_H
#define RENDERAREA_H
#include <QStatusBar>
#include <QWidget>
#include <seed.h>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    void setAreaSize(int w, int h);
    void setFile(QString f);
    void setBar(QStatusBar* b);
    void setAreaColor(QColor c);
    void setCellColor(QColor c);
signals:
    void doubleClick();
public slots:
    void next_generation();
private:
    Seed* seed;
    QRectF* rectArray;
    QStatusBar* bar;
    int area_w;
    int area_h;
    QColor areaColor;
    QColor cellColor;
    QString fileName;
    bool fullMode;
protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent*);
    
};

#endif // RENDERAREA_H
