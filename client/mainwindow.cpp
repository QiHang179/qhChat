#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "resetdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dlg = new LoginDialog(this);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);
    //_login_dlg->show();

    //连接登录界面注册信号
    connect(_login_dlg, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    //连接登录界面忘记密码信号
    connect(_login_dlg, &LoginDialog::switchReset, this, &MainWindow::SlotSwitchReset);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    _register_dlg = new RegisterDialog(this);
    _register_dlg->hide();
    _register_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    connect(_register_dlg,&RegisterDialog::sigSwitchLogin,this,&MainWindow::SlotSwitchLogin);
    setCentralWidget(_register_dlg);
    _login_dlg->hide();
    _register_dlg->show();
}

void MainWindow::SlotSwitchLogin()
{
    _login_dlg = new LoginDialog(this);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);

    _register_dlg->hide();
    _login_dlg->show();
    //连接登录界面注册信号
    connect(_login_dlg,&LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);
    //连接登录界面忘记密码信号
    connect(_login_dlg,&LoginDialog::switchReset,this,&MainWindow::SlotSwitchReset);
    //连接登录界面忘记密码信号
    connect(_login_dlg,&LoginDialog::switchReset,this,&MainWindow::SlotSwitchReset);
}

void MainWindow::SlotSwitchLogin2()
{
    _login_dlg = new LoginDialog(this);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);

    _reset_dlg->hide();
    _login_dlg->show();

    //连接登录界面注册信号
    connect(_login_dlg,&LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);
    //连接登录界面忘记密码信号
    connect(_login_dlg,&LoginDialog::switchReset,this,&MainWindow::SlotSwitchReset);
}

void MainWindow::SlotSwitchReset()
{
    _reset_dlg = new ResetDialog(this);
    _reset_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_reset_dlg);

    _login_dlg->hide();
    _reset_dlg->show();
    //注册返回登录的信号和槽函数、
    connect(_reset_dlg,&ResetDialog::switchLogin,this,&MainWindow::SlotSwitchLogin2);
}
