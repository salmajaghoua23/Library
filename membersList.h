#ifndef MEMBERSLIST_H
#define MEMBERSLIST_H
#include <QObject>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>
#include <QLabel>
namespace Ui {
class membersList;
}

class membersList : public QDialog
{
  //  Q_OBJECT

public:
    explicit membersList(QWidget *parent = nullptr);
    ~membersList();

private slots:

    void on_value_textEdited(const QString &arg1);
    // membersList.h
private slots:
    void setupTableView();  // Ajoutez cette ligne
   // void on_value_textEdited(const QString &text);
private:
    Ui::membersList *ui;
    QLabel *statusLabel;
};

#endif // MEMBERSLIST_H
