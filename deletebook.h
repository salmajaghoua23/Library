#ifndef DELETEBOOK_H
#define DELETEBOOK_H
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>
#include <QObject>
// ...existing code...
#include <QTableWidget> // Ajoute cette ligne en haut si tu utilises QTableWidget


namespace Ui {
class deleteBook;
}

class deleteBook : public QDialog
{
    Q_OBJECT

public:
    explicit deleteBook(QWidget *parent = nullptr);
    ~deleteBook();

private slots:
    void on_deleteBookBtn_clicked();
private:
    QTableWidget *booksTable; // Nouvelle table pour afficher les livres
    QPushButton *deleteBtn;   // Bouton supprimer
    int selectedBookId = -1;  // ID du livre sélectionné
// ...existing code...
private:
    Ui::deleteBook *ui;
};

#endif // DELETEBOOK_H
