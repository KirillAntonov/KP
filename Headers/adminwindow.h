#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private slots:

    void on_enterButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_updateButton_clicked();

    void on_revertButton_clicked();

private:
    Ui::AdminWindow *ui;
    QSqlTableModel *model;
};

#endif // ADMINWINDOW_H
