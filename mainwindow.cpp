#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDirIterator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString scrDir = ui->lineEdit->text();
    QString desDir = ui->lineEdit_2->text();
    QDirIterator it(scrDir, QStringList() << ("*"+ui->lineEdit_3->text()), QDir::Files, QDirIterator::Subdirectories);
    //QDirIterator it("scrDir",QDirIterator::Subdirectories);
    //int n = it.
    while (it.hasNext())
    {
        //scrDir=scrDir;
        //desDir = it.fileName();
        QString dest = desDir;
        QStringList list = it.fileName().split(".").at(0).split("_");
        if(list.length()>=4)
        {
            //dest.append("\\");
            dest.append(list.at(0));
            dest.append("\\");
            dest.append(list.at(3));
            dest.append("\\");
            dest.append(list.at(1));
            dest.append("\\");
            QDir dstDr(dest);
            if(!dstDr.exists())
            {
                dstDr.mkpath(dest);
            }
            dest.append(list.at(2));
            dest.append(ui->lineEdit_3->text());
            QString scr = scrDir + it.fileName();
            QFile fileScr(scr);
            QFile fileDst(dest);
            if(fileDst.exists()&&(!ui->radioButton->isChecked()))
            {
                it.next();
                continue;
            }
            fileScr.copy(dest);
        }
        it.next();
    }
}
