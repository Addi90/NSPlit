#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "nspsplitter.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* get and display source Filepath, calculate and display estimated no. of parts */
void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QString fileName = dialog.getOpenFileName(this,tr("Open NSP Source File"),
                                              "",
                                              "*.nsp");

    ui->lineEdit->setText(fileName);
    QString fileDir = fileName.left(fileName.lastIndexOf('/'));
    ui->lineEdit_2->setText(fileDir);


    NSPSplitter splitter;
    splitter.setInPath(fileName);
    size_t filesize = splitter.nspCheckFilesize();
    int parts = splitter.nspCalcParts(filesize);
    QString no_of_parts = tr("Filesize: ") + QString::number(filesize/1024/1024) + "MB  " +
            tr("Estimated Number of Parts: ") + QString::number(parts);
    ui->label_3->setText(no_of_parts);
}


void MainWindow::on_pushButton_3_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Save Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly |
                                                    QFileDialog::DontResolveSymlinks);

    ui->lineEdit_2->setText(dir);
}


void MainWindow::on_pushButton_2_clicked()
{
    NSPSplitter splitter;
    splitter.setInPath(ui->lineEdit->text());
    splitter.setOutPath(ui->lineEdit_2->text());
    splitter.nspSplit();

}

