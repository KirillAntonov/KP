#include "mainform.h"
#include "mainwindow.h"
#include "ui_mainform.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

mainform::mainform(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainform)
{
    ui->setupUi(this);
}

mainform::~mainform()
{
    delete ui;
}

void mainform::start(QString Login, QString Pass)
{
    login = Login;
    pass = Pass;

    qDebug() << login << " " << pass << endl;

    out_information(login, pass);
    course();
}

void mainform::out_information(QString Login, QString Pass)
{

    query.exec("SELECT * FROM User WHERE Login = '"+Login+"' AND Password = '"+Pass+"'");
    while(query.next())
    {
        QString login;

        id = query.value(0).toString();
        Name = query.value(1).toString();
        Surname = query.value(2).toString();
        ThirdName = query.value(3).toString();
        Number = query.value(4).toString();
        Date = query.value(5).toString();
        Type = query.value(6).toString();
        Balance = query.value(7).toString();
        login = query.value(8).toString();
        password = query.value(9).toString();
    }

    ui->BalanceLabel->setText("Ваш баланс: " +Balance+ " BYN");
    ui->ownerLabel->setText("Добро пожаловать, "+Surname +" " + Name + " " + ThirdName +"!");
    ui->CardHolder->setText(Surname+" "+Name);
    ui->DateLabel->setText(Date);

    if(Type == "Visa")
    {
        ui->logoLabel->setText("VISA");
    }
    else
    {
        ui->logoLabel->setText("MasterCard");
    }

    qDebug() << Name << " " << Surname << endl;
}

void mainform::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_F1:
        QDesktopServices::openUrl(QUrl::fromLocalFile("data/Help.chm"));
        break;
    }
}

void mainform::history(QString date, QString Name, QString Type, QString Number, float sum)
{
    query.prepare("INSERT INTO History(id, Получатель, Тип_операции, Дата, Номер_счета_телефона_договора, Сумма) "
                  "VALUES(?,?,?,?,?,?)");

    query.addBindValue(id);
    query.addBindValue(Name);
    query.addBindValue(Type);
    query.addBindValue(date);
    query.addBindValue(Number);
    query.addBindValue(QString::number(sum));

    qDebug() << query.exec();
    qDebug() << query.lastError();
}

void mainform::updateInfo(QString id)
{
    QSqlQuery query;
    QString temp;
    query.exec("SELECT Balance FROM User WHERE id = "+id+"");
    while(query.next())
    {
        temp = query.value(0).toString();
    }
    ui->BalanceLabel->setText("Ваш баланс: " +temp+ " BYN");
}

void mainform::course()
{
    QDate Date;
    QString byUSD;
    QString soldUSD;
    QString byEUR;
    QString soldEUR;
    QString byRUB;
    QString soldRUB;
    query.exec("SELECT * FROM Course WHERE Дата = '"+Date.currentDate().toString("dd.MM.yyyy")+"'");
    while(query.next())
    {
        byUSD = query.value(1).toString();
        soldUSD = query.value(2).toString();
        byEUR = query.value(3).toString();
        soldEUR = query.value(4).toString();
        byRUB = query.value(5).toString();
        soldRUB = query.value(6).toString();
    }

    ui->label_13->setText(Date.currentDate().toString("dd.MM.yyyy"));
    ui->byUSD->setText(byUSD);
    ui->soldUSD->setText(soldUSD);
    ui->byEUR->setText(byEUR);
    ui->soldEUR->setText(soldEUR);
    ui->byRUB->setText(byRUB);
    ui->soldRUB->setText(soldRUB);
}

void mainform::on_exit_triggered()
{
    QApplication::quit();
}

void mainform::on_ChanBalBut_clicked()
{
    ref = new refill();
    connect(ref, &refill::mainForm, this, &mainform::show);
    connect(ref, &refill::update, this, &mainform::updateInfo);
    connect(ref, &refill::updateHistory, this, &mainform::history);

    ref->show();
    ref->start_refill(id);
    close();
}

void mainform::on_SendButton_clicked()
{
    send = new sendForm();
    connect(send, &sendForm::mainForm, this, &mainform::show);
    connect(send, &sendForm::update, this, &mainform::updateInfo);
    connect(send, &sendForm::updateHistory, this, &mainform::history);

    send->show();
    send->start_send(id);
    close();
}

void mainform::on_OrgButton_clicked()
{
    org = new Organisation();
    connect(org, &Organisation::mainForm, this, &mainform::show);
    connect(org,&Organisation::update, this, &mainform::updateInfo);
    connect(org, &Organisation::UPH, this, &mainform::history);

    org->show();
    org->start_organisation(id);
    close();
}

void mainform::on_myInfo_triggered()
{
    UInfo = new UserInformation();
    connect(UInfo, &UserInformation::mainForm, this, &mainform::show);

    UInfo->show();
    UInfo->start_userInformation(id);
    close();
}

void mainform::on_historyButton_clicked()
{
    HList = new HistoryList();
    connect(HList, &HistoryList::mainForm, this, &mainform::show);

    HList->show();
    HList->start_history(id);
    close();
}

void mainform::on_help_triggered()
{
    bool temp = QDesktopServices::openUrl(QUrl::fromLocalFile("data/Help.chm"));
    qDebug() << temp;
}
