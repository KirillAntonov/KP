#include "userinformation.h"
#include "ui_userinformation.h"
#include <QDebug>
#include <QMessageBox>

UserInformation::UserInformation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserInformation)
{
    ui->setupUi(this);
    connect(this, &UserInformation::asb, this, &UserInformation::sb);
    emit asb();
}

UserInformation::~UserInformation()
{
    delete ui;
}

void UserInformation::output_information(QString id)
{
    query.exec("SELECT Name, Surname, ThirdName, Sex, Birthday, MobilePhone FROM User WHERE id = "+id+"");
    while(query.next())
    {
        Name = query.value(0).toString();
        Surname = query.value(1).toString();
        ThirdName = query.value(2).toString();
        Sex = query.value(3).toString();
        Birthday = query.value(4).toString();
        MobilePhone = query.value(5).toString();
    }

    ui->NameLabel->setText(Name);
    ui->SurnameLabel->setText(Surname);
    ui->ThirdNameLabel->setText(ThirdName);
    ui->SexLabel->setText(Sex);
    ui->BirthdayLabel->setText(Birthday);
    ui->mobileEdit->setText(MobilePhone);
}

void UserInformation::start_userInformation(QString id)
{
    output_information(id);

    _id = id;
}

void UserInformation::update_password(QString _Pass)
{
    query.exec("UPDATE User SET Password = '"+_Pass+"' WHERE id = "+_id+"");
    if(query.exec() == true)
    {
        QMessageBox::information(this, "Информация о пользователе", "Пароль успешно изменен!");
        this->close();
        emit mainForm();
    }
    else
    {
        QMessageBox::critical(this, "Информация о пользователе", "Неизвестная ошибка!");
    }
}

void UserInformation::sb()
{
    qDebug() << "OK" << endl;
}

void UserInformation::on_BackButton_clicked()
{
    this->close();
    emit mainForm();
}

void UserInformation::on_changepassButton_clicked()
{
    QString temp = ui->PassEdit->text();
    QString mobile = ui->mobileEdit->text();

    query.exec("UPDATE User SET MobilePhone = '"+mobile+"' WHERE id = '"+_id+"'");
    QMessageBox::information(this, "Информация о пользователе", "Данные сохранены!");
    if(temp != "")
    {
        update_password(temp);
    }
}
