#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QByteArray fw;
    fw.push_back('a');
    fw.push_back('a');
    fw.push_back('a');
    fw.push_back('a');
    firmwareStack.push_back(fw);
    fw.push_back('a');
    fw.push_back('a');
    fw.push_back('a');
    fw.push_back('a');
    firmwareStack.push_back(fw);
    fw.push_back('a');
    fw.push_back('a');
    fw.push_back('a');
    fw.push_back('a');
    firmwareStack.push_back(fw);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
//    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
//    event->acceptProposedAction();
//    QString name = event->mimeData()->urls().first().toString();
//    ui->lineEditSrcFile->setText(name);
}

Qt::GlobalColor colorPalete[] = {
    Qt::white,      // blank
    Qt::gray,       // fill value
    Qt::lightGray,
    Qt::red,
    Qt::green,
    Qt::blue,
    Qt::cyan,
    Qt::magenta,
    Qt::yellow,
};

void MainWindow::paintEvent(QPaintEvent *)
{
    qDebug() << "Paint event.\n";
//    return;

    QPen pen;
    QBrush brush;
    QPainter painter(this);
    int length = 300;
    int x = rectX, y = rectY;
    uint32_t firmwareSizeAll;

    pen.setColor(Qt::black);

    firmwareSizeAll=0;
    for (auto n:firmwareStack)
        firmwareSizeAll+=n.size();

    if (firmwareSizeAll == 0)
    {
        brush.setColor(colorPalete[0]);
        brush.setStyle(Qt::SolidPattern);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(x, y, length, 20);
    }
    else
    {
        for (int i=0; i<firmwareStack.size(); i++)
        {
            int h;

            h = (float)firmwareStack.at(i).size() / firmwareSizeAll * length;
            qDebug() << "h:" << h;

            brush.setColor(colorPalete[i+2]);
            brush.setStyle(Qt::SolidPattern);
            painter.setPen(pen);
            painter.setBrush(brush);
            painter.drawRect(x, y, h, 20);
            x+=h;
        }
    }

    qDebug() << "firmwareSizeAll:" << firmwareSizeAll;
    qDebug() << "firmwareStack:" << firmwareStack;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent" << event->pos() << endl;
    return;

}

bool MainWindow::GenerateFile()
{
    QByteArray dataDest, dataSrc, dataSrcSeg, dataGenerate;

//    FileSrc.setFileName(ui->lineEditSrcFile->text());
    FileDest.setFileName(ui->lineEditDestFile->text());

    addrStart = ui->spinAddrStart->value();
    addrStop = ui->spinAddrStop->value();
    addrInsert = ui->spinAddrInsert->value();

    if (addrStart > addrStop || addrStart > FileSrc.size() || addrStop > FileSrc.size())
        return false;
//    if (ui->checkInsert->checkState() && (int)(dataDest.size() - addrInsert) < dataSrc.size())
//        return false;

    if (!FileDest.exists() || !FileSrc.exists())
        return false;

    FileSrc.open(QFile::ReadOnly);
    FileDest.open(QFile::ReadOnly);

    dataDest = FileDest.readAll();

    FileSrc.seek(addrStart);
    dataSrc = FileSrc.read(addrStop - addrStart +1);

//    if (ui->checkInsert->checkState())
//    {
//        // insert
//        dataGenerate.resize(addrInsert + dataSrc.size());

//        if (dataDest.size() < addrInsert)
//        {
//            memcpy(dataGenerate.data(), dataDest.data(), dataDest.size());
//            memset(&dataGenerate.data()[dataDest.size()], 0xFF, addrInsert - dataDest.size());
//            memcpy(&dataGenerate.data()[addrInsert], dataSrc.data(), dataSrc.size());
//        }
//        else
//        {
//            memcpy(dataGenerate.data(), dataDest.data(), addrInsert);
//            memcpy(&dataGenerate.data()[addrInsert], dataSrc.data(), dataSrc.size());
//        }
//    }
//    else
//    {
//        if (dataDest.size() < addrInsert)
//            dataGenerate.resize(addrInsert + dataSrc.size());
//        else
//            dataGenerate.resize(dataDest.size() + dataSrc.size());

//        if (dataDest.size() < addrInsert)
//        {
//            memcpy(dataGenerate.data(), dataDest.data(), dataDest.size());
//            memset(&dataGenerate.data()[dataDest.size()], 0xFF, addrInsert - dataDest.size());
//            memcpy(&dataGenerate.data()[addrInsert], dataSrc.data(), dataSrc.size());
//        }
//        else
//        {
//            memcpy(dataGenerate.data(), dataDest.data(), addrInsert);
//            memcpy(&dataGenerate.data()[addrInsert], dataSrc.data(), dataSrc.size());
//            memcpy(&dataGenerate.data()[addrInsert+dataSrc.size()], dataDest.data(), dataDest.size() - addrInsert);
//        }
//    }

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("open bin file"),
                                                    "./",
                                                    tr("*.bin"));
    FileGenerate.setFileName(fileName);
    FileGenerate.open(QFile::ReadWrite | QFile::NewOnly);
    FileGenerate.write(dataGenerate);

    FileSrc.close();
    FileDest.close();
    FileGenerate.close();

    return true;
}

void MainWindow::on_btnGenerate_clicked()
{
    if (GenerateFile())
        ui->btnGenerate->setText("成功");
    else
        ui->btnGenerate->setText("重试");
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("open bin file"),
                                                    "./",
                                                    tr("*.bin"));
//    ui->lineEditSrcFile->setText(fileName);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("open bin file"),
                                                    "./",
                                                    tr("*.bin"));
    ui->lineEditDestFile->setText(fileName);
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if (arg1)
    {
//        FileSrc.setFileName(ui->lineEditSrcFile->text());
        if (!FileSrc.isOpen())
            FileSrc.open(QFile::ReadOnly);

        ui->spinAddrStart->setValue(0);
        ui->spinAddrStart->setEnabled(false);
        ui->spinAddrStop->setValue(FileSrc.size()-1);
        ui->spinAddrStop->setEnabled(false);

        FileSrc.close();
    }
    else
    {
        ui->spinAddrStart->setEnabled(true);
        ui->spinAddrStop->setEnabled(true);
    }
}



void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("open bin file"),
                                                    "./",
                                                    tr("*.bin"));
    ui->lineEditDestFile->setText(fileName);
}
