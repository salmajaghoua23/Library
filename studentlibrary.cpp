#include "studentlibrary.h"
#include "ui_studentlibrary.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QtConcurrent/QtConcurrent>
#include <QSqlQuery>
// studentLibrary::studentLibrary(QWidget *parent, QSqlDatabase db) :
//     QDialog(parent),
//     ui(new Ui::studentLibrary),
//     db(db),
//     model(new QSqlQueryModel(this)),
//     currentBookId(-1)
// {
//     ui->setupUi(this);
//     QSqlQuery createTableQuery(db);
//     QString createTableSQL = R"(
//     CREATE TABLE IF NOT EXISTS cart (
//         id INTEGER PRIMARY KEY AUTOINCREMENT,
//         user_id INTEGER,
//         book_id INTEGER,
//         name TEXT,
//         author TEXT,
//         added_at DATETIME DEFAULT CURRENT_TIMESTAMP
//     )
//     )";
//    // this->userId = userId;
//     if (!createTableQuery.exec(createTableSQL)) {
//         QMessageBox::critical(this, "Erreur BD", "Échec de la création de la table cart :\n" + createTableQuery.lastError().text());
//     }

//     // Cacher les boutons au départ
//     ui->addToCartButton->setVisible(false);
//     ui->borrowButton->setVisible(false);

//     // Connecter les boutons
//     connect(ui->searchButton, &QPushButton::clicked, this, &studentLibrary::on_searchButton_clicked);
//     connect(ui->addToCartButton, &QPushButton::clicked, this, &studentLibrary::on_addToCartButton_clicked);
//     connect(ui->borrowButton, &QPushButton::clicked, this, &studentLibrary::on_borrowButton_clicked);
// }
studentLibrary::studentLibrary(QWidget *parent, QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::studentLibrary),
    db(db),
    model(new QSqlQueryModel(this)),
    currentBookId(-1)
{
    ui->setupUi(this);

    QSqlQuery createTableQuery(db);
    QString createTableSQL = R"(
    CREATE TABLE IF NOT EXISTS cart (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER,
        book_id INTEGER,
        name TEXT,
        author TEXT,
        added_at DATETIME DEFAULT CURRENT_TIMESTAMP
    )
    )";

    if (!createTableQuery.exec(createTableSQL)) {
        QMessageBox::critical(this, "Erreur BD", "Échec de la création de la table cart :\n" + createTableQuery.lastError().text());
    }

    // Cacher les boutons au départ
    ui->addToCartButton->setVisible(false);
    ui->borrowButton->setVisible(false);
    ui->backButton->setVisible(false); // Cachez aussi le bouton retour initialement

    // Connecter les boutons
    connect(ui->searchButton, &QPushButton::clicked, this, &studentLibrary::on_searchButton_clicked);
    connect(ui->addToCartButton, &QPushButton::clicked, this, &studentLibrary::on_addToCartButton_clicked);
    connect(ui->borrowButton, &QPushButton::clicked, this, &studentLibrary::on_borrowButton_clicked);
    connect(ui->backButton, &QPushButton::clicked, this, &studentLibrary::on_backButton_clicked); // Nouvelle connexion
}
studentLibrary::~studentLibrary()
{
    delete ui;
}
void studentLibrary::on_backButton_clicked()
{
    // Réinitialise l'interface à son état initial
    ui->searchLineEdit->clear();
    ui->bookDetailsText->clear();
    ui->addToCartButton->setVisible(false);
    ui->borrowButton->setVisible(false);
    ui->backButton->setVisible(false);

    // Efface la sélection dans la liste
    ui->bookListView->selectionModel()->clearSelection();

    // Optionnel: efface le modèle si vous voulez vider la liste
     model->clear();
}
void studentLibrary::on_searchButton_clicked()
{
    QString searchTerm = ui->searchLineEdit->text();

    QSqlQuery query(db);
    query.prepare("SELECT ID, name, author, genre, price FROM books "
                  "WHERE name LIKE :searchTerm OR author LIKE :searchTerm OR genre LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (query.exec()) {
        model->setQuery(query);
        ui->bookListView->setModel(model);
    } else {
        QMessageBox::critical(this, "Error", "Failed to retrieve book data");
    }
}

void studentLibrary::on_bookListView_clicked(const QModelIndex &index)
{
    int bookId = model->data(model->index(index.row(), 0)).toInt();
    currentBookId = bookId;

    showBookDetails(bookId);

    // Afficher les boutons
    ui->addToCartButton->setVisible(true);
    ui->borrowButton->setVisible(true);
    ui->backButton->setVisible(true); // Affichez aussi le bouton retour
}
void studentLibrary::showBookDetails(int bookId)
{
    QSqlQuery query(db);
    query.prepare("SELECT name, author, genre, publisher, description, price, quantity FROM books WHERE ID = :bookId");
    query.bindValue(":bookId", bookId);

    if (query.exec() && query.next()) {
        QString name = query.value("name").toString();
        QString author = query.value("author").toString();
        QString genre = query.value("genre").toString();
        QString publisher = query.value("publisher").toString();
        QString description = query.value("description").toString();
        double price = query.value("price").toDouble();
        int quantity = query.value("quantity").toInt();

        // Afficher dans le label de l'interface si tu en as
        ui->bookDetailsText->setText(
            "Titre : " + name + "\nAuteur : " + author + "\nGenre : " + genre +
            "\nÉditeur : " + publisher + "\nPrix : " + QString::number(price) +
            "\nDisponible : " + QString::number(quantity) +
            "\nDescription :\n" + description
            );
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'afficher les détails du livre.");
    }
}

void studentLibrary::on_addToCartButton_clicked()
{
    QSqlQuery query(db);
    query.prepare("SELECT ID, name, author FROM books WHERE ID = :id");
    query.bindValue(":id", currentBookId);

    if (query.exec() && query.next()) {
        int bookId = query.value("ID").toInt();
        QString name = query.value("name").toString();
        QString author = query.value("author").toString();
        query.prepare("INSERT INTO cart (user_id, book_id, name, author) VALUES (:user_id, :book_id, :name, :author)");
       // query.bindValue(":user_id", userId);

        // Insertion dans la table cart
        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO cart (user_id, book_id, name, author) "
                            "VALUES (:user_id, :book_id, :name, :author)");
        insertQuery.bindValue(":user_id", 1); // ou l’ID réel de l’utilisateur
        insertQuery.bindValue(":book_id", bookId);
        insertQuery.bindValue(":name", name);
        insertQuery.bindValue(":author", author);

        if (insertQuery.exec()) {
            QMessageBox::information(this, "Succès", "Livre ajouté au panier.");
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible d’ajouter au panier : " + insertQuery.lastError().text());
        }
    }
}

// void studentLibrary::showCart()
// {
//     QSqlQuery query(db);
//     query.prepare("SELECT name, author, added_at FROM cart WHERE user_id = :user_id");
//     query.bindValue(":user_id", 1); // ou utilisateur connecté

//     if (query.exec()) {
//         QSqlQueryModel *cartModel = new QSqlQueryModel(this);
//         cartModel->setQuery(query);
//         ui->cartTableView->setModel(cartModel); // un QTableView que tu ajoutes à ton UI
//     } else {
//         QMessageBox::warning(this, "Erreur", "Impossible d’afficher le panier.");
//     }
// }

void studentLibrary::on_borrowButton_clicked()
{
    QSqlQuery query(db);
    query.prepare("UPDATE books SET quantity = quantity - 1 WHERE ID = :id AND quantity > 0");
    query.bindValue(":id", currentBookId);

    if (query.exec() && query.numRowsAffected() > 0) {
        QMessageBox::information(this, "Succès", "Livre emprunté avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Le livre est indisponible.");
    }
}
