#ifndef EDITBOOK_H
#define EDITBOOK_H
#include <QObject>

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>

namespace Ui {
class editBook;
}

class editBook : public QDialog
{
    Q_OBJECT

public:
    explicit editBook(QWidget *parent = nullptr);
    ~editBook();

    void setValidator();

    int count = 0;

private slots:
    void on_cancelBtn_clicked();

    void on_selectImgBtn_clicked();

    void on_editBookBtn_clicked();

    void on_searchBtn_clicked();

    void on_changeAuthorBtn_clicked();

    void on_changeGenreBtn_clicked();

private:
    Ui::editBook *ui;
    // Déclaration correcte des fonctions
        QWidget* createAuthorField(QWidget *parent);
    QWidget* createGenreField(QWidget *parent);
    void setupUI();
    //void setValidator();

    // Structure FieldConfig doit être déclarée dans la classe
    struct FieldConfig {
        QWidget* widget;
        QString label;
        int yPos;
    };
    QString coverFilename;
    bool clicked = false;
};

#endif // EDITBOOK_H
