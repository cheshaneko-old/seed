#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "seed.h"
#include <QMainWindow>
#include<QGraphicsScene>
#include "dialog.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_next_Button_clicked();

    void on_settingsButton_clicked();

    void on_playPauseButton_clicked();

    void on_fileButton_clicked();

    void fullScreenArea();

    void on_stopButton_clicked();

private:
    bool fullMode;
    int index;
    void pauseArea();
    void startArea();
    void setAreaSize(int w, int h);
    Ui::MainWindow *ui;
    QDialog *settings_dialog;
    int timerSpeed;
    bool pause;
    QTimer *timer;
};

#endif // MAINWINDOW_H


