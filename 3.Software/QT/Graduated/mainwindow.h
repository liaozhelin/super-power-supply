#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

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
    void on_btn_output_clicked();

    void on_btn_connect_clicked();

    void on_btn_flash_clicked();

    void on_btn_disconnect_clicked();

    void on_dial_vout_actionTriggered(int action);

private:
    Ui::MainWindow *ui;

    QSerialPort global_port;

    void system_init(void);
};
#endif // MAINWINDOW_H
