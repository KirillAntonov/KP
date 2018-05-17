#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>
#include <QDebug>

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_enterButton_clicked()
{
    QString Table = ui->comboBox->currentText();
    if(ui->sortingBox->currentText() == "Сортировка по:")
    {
        if(Table == "Пользователи")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("User");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Истории платежей")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("History");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Курс валют")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("Course");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Организации")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("Organisation");
            model->select();
            ui->tableView->setModel(model);
        }
    }
    else if(ui->sortingBox->currentText() == "id")
    {
        if(Table == "Пользователи")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("User");
            model->setFilter("id = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Истории платежей")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("History");
            model->setFilter("id = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Курс валют")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("Course");
            model->setFilter("Дата = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Организации")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("Organisation");
            model->setFilter("id = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
    }
    else if(ui->sortingBox->currentText() == "Имени")
    {
        if(Table == "Пользователи")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("User");
            model->setFilter("Name = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Истории платежей")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("History");
            model->setFilter("Получатель = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Курс валют")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("Course");
            model->setFilter("Name = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Организации")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("Organisation");
            model->setFilter("Название_Организации = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
    }
    else if(ui->sortingBox->currentText() == "Номеру счета")
    {
        if(Table == "Пользователи")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("User");
            model->setFilter("Number = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Истории платежей")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("History");
            model->setFilter("Номер_счета_телефона_договора = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Курс валют")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("Course");
            model->setFilter("Number = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Организации")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("Organisation");
            model->setFilter("Номер_счета = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
    }
    else if(ui->sortingBox->currentText() == "Типу операции")
    {
        if(Table == "Пользователи")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("User");
            model->setFilter("Тип_операции = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Истории платежей")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("History");
            model->setFilter("Тип_операции = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Курс валют")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("Course");
            model->setFilter("Тип_операции = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
        else if(Table == "Организации")
        {
            model = new QSqlTableModel(this);
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->setTable("Organisation");
            model->setFilter("Тип_операции = '"+ui->sortingEdit->text()+"'");
            model->select();
            ui->tableView->setModel(model);
        }
    }
}

void AdminWindow::on_addButton_clicked()
{
    model->insertRow(model->rowCount());
}

void AdminWindow::on_deleteButton_clicked()
{
    int selectRow = ui->tableView->currentIndex().row();
    if(selectRow >= 0)
    {
        model->removeRow(selectRow);
    }
    else
    {
        QMessageBox::critical(this, "Удаление записи", "Запись не выделена!");
    }
}

void AdminWindow::on_updateButton_clicked()
{
    model->submitAll();
}

void AdminWindow::on_revertButton_clicked()
{
    model->revertAll();
}
