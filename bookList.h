#ifndef BOOKLIST_H
#define BOOKLIST_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>
#include <QDialog>
#include<QFormLayout>

namespace Ui {
class bookList;
}
class bookList : public QDialog
{
    Q_OBJECT

public:
    explicit bookList(QWidget *parent = nullptr);
    ~bookList();
private slots:
    //void on_value_textEdited(const QString &arg1);
    void showBookDetails(const QString &bookId); // Nouvelle fonction
    void addCreativeDetailRow(QGridLayout *layout, const QString &label, const QString &value, int row, int col, const QString &color);
private:
    void addDetailRow(QFormLayout *layout, const QString &label, const QString &value); // Nouvelle fonction helper
private slots:
    void on_value_textEdited(const QString &arg1);
    void showInfo();

private:
    Ui::bookList *ui;
};

#endif // BOOKLIST_H
