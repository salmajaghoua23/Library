#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class addBook;
}

class addBook : public QDialog
{
    Q_OBJECT

public:
    explicit addBook(QWidget *parent = nullptr);
    ~addBook();

private slots:
    void on_cancelBtn_clicked();
    void on_addBookBtn_clicked();
    void on_selectImgBtn_clicked();
    void on_chooseAuthBtn_clicked();
    void on_chooseGenreBtn_clicked();

private:
    Ui::addBook *ui;
    QString coverFilename;

    void setValidator();
};

#endif // ADDBOOK_H
