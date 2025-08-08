#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"
/******************************************************************************
 *
 * @file       mainwindow.h
 * @brief      主窗口 Function
 *
 * @author     起航
 * @date       2025/08/05
 * @history
 *****************************************************************************/

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SlotsSwitchReg();
private:
    Ui::MainWindow *ui;
    LoginDialog* _login_dlg;
    RegisterDialog* _register_dlg;
};
#endif // MAINWINDOW_H
