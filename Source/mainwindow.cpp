#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainform.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->PassLine->setEchoMode(QLineEdit::Password);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data/Clients.db");
    db.open();
    if(!db.isOpen())
    {
        ui->statusBar->showMessage("Подключение отсутствует!");
    }
    else
    {
        ui->statusBar->showMessage("Соединение с базой данных установлено!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_F1:
        QDesktopServices::openUrl(QUrl::fromLocalFile("data/Help.chm"));
        break;
    }
}

void MainWindow::on_Info_triggered()
{
    bool temp = QDesktopServices::openUrl(QUrl::fromLocalFile("data/Help.chm"));
    qDebug() << temp;
}

void MainWindow::on_exit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_LoginButton_clicked()
{
    QString login = ui->LoginLine->text();
    QString pass = ui->PassLine->text();
    QString ln;
    QString pn;
    QSqlQuery query;
    int temp = 0;
    int atemp = 0;

    if(login == "Admin")
    {
        QString aName;
        QString aPass;
        query.exec("SELECT Name, Password FROM User");
        while(query.next())
        {
            aName = query.value(0).toString();
            aPass = query.value(1).toString();
            if(aName == "Admin" && pass == aPass)
            {
                QMessageBox::information(this, "Авторизация", "Авторизация администратора выполнена!");
                AW = new AdminWindow();
                AW->show();
                this->close();
                ++atemp;
            }
        }
        if(atemp == 0)
        {
            QMessageBox::critical(this, "Авторизация", "Ошибка ввода данных!");
            ui->LoginLine->clear();
            ui->PassLine->clear();
        }
    }
    else
    {
        query.exec("SELECT Login, Password FROM User");
        while(query.next())
        {
            ln = query.value(0).toString();
            pn = query.value(1).toString();
            if(ln == login && pn == pass)
            {
                QMessageBox::information(this, "Авторизация", "Авторизация выполнена успешно!");
                main = new mainform();
                main->show();
                main->start(login, pass);
                hide();
                temp = 1;
                break;
            }
        }
        if (temp == 0)
        {
            QMessageBox::critical(this, "Авторизация", "Неправильно введены данные!");
            ui->LoginLine->clear();
            ui->PassLine->clear();
            qDebug() << query.lastError() << endl;
        }
    }
}

void MainWindow::on_RegButton_clicked()
{
    reg = new Registration();
    connect(reg, &Registration::mainWin, this, &MainWindow::show);

    reg->show();
    hide();
}
