#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QFileDialog>
#include "seed.h"

#include <dialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), ui->RArea, SLOT(next_generation()));
    pause = true;
    settings_dialog = new myDialog();
    ui->RArea->setAreaSize(((myDialog*)settings_dialog)->getAreaWidth(), ((myDialog*)settings_dialog)->getAreaHeight());
    ui->RArea->setBar(ui->statusBar);
    ui->RArea->setAreaColor(((myDialog*)settings_dialog)->getAreaColor());
    ui->RArea->setCellColor(((myDialog*)settings_dialog)->getCellColor());
    timerSpeed = ((myDialog*)settings_dialog)->getAreaSpeed();
    connect(ui->RArea, SIGNAL(doubleClick()), this, SLOT(fullScreenArea()));
    ui->playPauseButton->setIcon(QIcon(":/img/media-playback-start.svg"));
    fullMode = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings_dialog;
}

void MainWindow::on_next_Button_clicked()
{
    pauseArea();
    ui->RArea->next_generation();
}

void MainWindow::setAreaSize(int w, int h)
{
    ui->RArea->setAreaSize(w, h);
}

void MainWindow::on_settingsButton_clicked()
{
    pauseArea();
    if(settings_dialog->exec() == QDialog::Accepted)
    {
        if(((myDialog*)settings_dialog)->sizeChanged())
            ui->RArea->setAreaSize(((myDialog*)settings_dialog)->getAreaWidth(), ((myDialog*)settings_dialog)->getAreaHeight());
        timerSpeed=((myDialog*)settings_dialog)->getAreaSpeed();
        ui->RArea->setAreaColor(((myDialog*)settings_dialog)->getAreaColor());
        ui->RArea->setCellColor(((myDialog*)settings_dialog)->getCellColor());
    }
}

void MainWindow::on_playPauseButton_clicked()
{
    if(pause)
    {
        startArea();
    }
    else
    {
        pauseArea();
    }

}

void MainWindow::on_fileButton_clicked()
{
    pauseArea();
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if(!fileName.isEmpty())
        ui->RArea->setFile(fileName);
}

void MainWindow::pauseArea()
{
    timer->stop();
    pause = true;
    ui->playPauseButton->setIcon(QIcon(":/img/media-playback-start.svg"));
}

void MainWindow::startArea()
{
    timer->start(timerSpeed);
    pause = false;
    ui->playPauseButton->setIcon(QIcon(":/img/media-playback-pause.svg"));
}

void MainWindow::fullScreenArea()
{
    if(!fullMode)
    {
        index = ui->verticalLayout_3->indexOf(ui->RArea);
        ui->RArea->setParent(0);
        this->hide();
        ui->RArea->showFullScreen();
        fullMode = true;
    }
    else
    {
        ui->verticalLayout_3->insertWidget(index, ui->RArea);
        this->show();
        fullMode = false;
    }
}

void MainWindow::on_stopButton_clicked()
{
    pauseArea();
    ui->RArea->setAreaSize(((myDialog*)settings_dialog)->getAreaWidth(), ((myDialog*)settings_dialog)->getAreaHeight());
    ui->RArea->update();
}
