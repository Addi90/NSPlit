#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "nspsplitter.h"
#include "nsp.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->progressBar->setVisible(false);

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
    NSP nsp(ui->lineEdit->text());

    size_t filesize = nsp.size();

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
    QObject::connect(&splitter, &NSPSplitter::progress,
                     ui->progressBar, &QProgressBar::valueChanged);
    NSP nsp;

    if(nsp.setPath(ui->lineEdit->text())){
        QMessageBox msgBox;
        msgBox.setText(tr("Not a valid File selected!"));
        msgBox.exec();
        return;
    }
    if(splitter.setSavePath(ui->lineEdit_2->text())){
        QMessageBox msgBox;
        msgBox.setText(tr("Not a valid Save Path!"));
        msgBox.exec();
        return;
    }
    if(splitter.nspSplit(&nsp)){
        QMessageBox msgBox;
        msgBox.setText(tr(".nsp File too small - splitting not necessary!"));
        msgBox.exec();
        return;
    }

}


void MainWindow::on_progressBar_valueChanged(int value)
{
    if(ui->progressBar->isVisible() && (value < 100)){
        ui->progressBar->setValue(value);
    }
    else if(!ui->progressBar->isVisible() && (value < 100) ){
        ui->progressBar->setVisible(true);
    }
    else{
        ui->progressBar->setVisible(false);
        ui->progressBar->setValue(0);
    }
}

