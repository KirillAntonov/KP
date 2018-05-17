#include "registration.h"
#include "ui_registration.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

Registration::Registration(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    connect(this, &Registration::asb, this, &Registration::sb);

    ui->NumberEdit->setValidator(new QIntValidator(0, 1000000000, this));
    ui->NameEdit->setValidator(new QRegExpValidator( QRegExp("[А-Я][а-я]{1,15}")));
    ui->SurnameEdit->setValidator(new QRegExpValidator( QRegExp("[А-Я][а-я]{1,15}")));
    ui->ThirdNameEdit->setValidator(new QRegExpValidator( QRegExp("[А-Я][а-я]{1,15}")));

    ui->SexBox->addItem("Мужской");
    ui->SexBox->addItem("Женский");
    ui->TypeBox->addItem("Visa");
    ui->TypeBox->addItem("MasterCard");
}

Registration::~Registration()
{
    delete ui;
}

void Registration::sb()
{
    qDebug() << "OK" << endl;
}

void Registration::on_pushButton_clicked()
{
    QString Name = ui->NameEdit->text();
    QString Surname = ui->SurnameEdit->text();
    QString ThirdName = ui->ThirdNameEdit->text();
    QString Number = ui->NumberEdit->text();
    QString Type = ui->TypeBox->currentText();
    QString Login = ui->LoginEdit->text();
    QString Password = ui->PassEdit->text();
    QString Birthday = ui->dateEdit->text();
    QString Sex = ui->SexBox->currentText();

    QString date = Date.currentDate().addYears(3).toString("MM/yy");
    QString tLogin;
    QString tNumber;
    int Logintemp = 0;
    int Numbertemp = 0;
    query.exec("SELECT Login, Number FROM User");
    while(query.next())
    {
        tLogin = query.value(0).toString();
        tNumber = query.value(1).toString();
        if(tLogin == Login)
        {
            ++Logintemp;
        }
        else if(tNumber == Number)
        {
            ++Numbertemp;
        }
    }

    if(Name == "" || Surname == "" || ThirdName == "" || Type == "" || Login == "" || Password == "")
    {
        QMessageBox::critical(this, "Регистрация", "Ошибка! Все поля должны быть заполнены!");
    }
    else
    {
        if(Logintemp != 0)
        {
            QMessageBox::critical(this, "Регистрация", "Ошибка! Такой логин уже существует!");
        }
        else if(Numbertemp != 0)
        {
            QMessageBox::critical(this, "Регистрация", "Ошибка! Такой номер счета уже существует!");
        }
        else
        {
            query.prepare("INSERT INTO User(Name, Surname, ThirdName, Number, Date, Type, Balance, Login, Password, Birthday, MobilePhone, Sex) "
                          "VALUES(:Name, :Surname, :ThirdName, :Number, :Date, :Type, 0.00, :Login, :Password, :Birthday, +375, :Sex)");

            query.bindValue(":Name",Name);
            query.bindValue(":Surname",Surname);
            query.bindValue(":ThirdName",ThirdName);
            query.bindValue(":Number",Number);
            query.bindValue(":Date",date);
            query.bindValue(":Type",Type);
            query.bindValue(":Login",Login);
            query.bindValue(":Password",Password);
            query.bindValue(":Birthday",Birthday);
            query.bindValue(":Sex",Sex);

            if(query.exec() == true)
            {
                QMessageBox::information(this, "Регистрация", "Регистрация прошла успешно!");
                this->close();
                emit mainWin();
            }
            else
            {
                QMessageBox::critical(this, "Регистрация", "Ошибка базы данных!");
                qDebug() << query.exec() << endl;
                qDebug() << query.lastError() << endl;
            }
        }
    }
}
