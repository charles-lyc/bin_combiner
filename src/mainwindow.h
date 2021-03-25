#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QtDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_3_stateChanged(int arg1);

    void on_btnGenerate_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    QFile FileDest;
    QFile FileSrc;
    QFile FileGenerate;

    uint32_t addrStart, addrStop;
    uint32_t addrInsert;

    bool GenerateFile();
};
#endif // MAINWINDOW_H
