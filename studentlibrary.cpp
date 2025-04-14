#include "studentlibrary.h"
#include "ui_studentlibrary.h"
#include "digitalLibrary.h"
#include "mapviewer.h"
#include "cart.h"
#include "historique.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QtConcurrent/QtConcurrent>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

studentLibrary::studentLibrary(QWidget *parent, QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::studentLibrary),
    db(db),
    model(new QSqlQueryModel(this)),
    currentBookId(-1)
{

    ui->setupUi(this);
   // connectDB();
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
   // connect(ui->borrowButton, &QPushButton::clicked, this, &studentLibrary::on_borrowButton_clicked);
    connect(ui->backButton, &QPushButton::clicked, this, &studentLibrary::on_backButton_clicked); // Nouvelle connexion
}
studentLibrary::~studentLibrary()
{
    delete ui;
}

// Dans le constructeur ou une méthode
void studentLibrary::on_btnHistorique_clicked() {
    Historique *h = new Historique(this);
    h->exec();
}

int studentLibrary::getUserId()
{
    // Exemple statique, tu devras adapter selon ton système d'authentification
    return 1;  // ID fictif de l'utilisateur
}
void studentLibrary::on_backButton_clicked()
{
    // Réinitialise l'interface à son état initial
    ui->searchLineEdit->clear();
    ui->bookDetailsText->clear();
    ui->addToCartButton->setVisible(false);
    ui->backButton->setVisible(false);

    // Efface la sélection dans la liste
    ui->bookListView->selectionModel()->clearSelection();

    // Optionnel: efface le modèle si vous voulez vider la liste
     model->clear();
}
void studentLibrary::on_searchButton_clicked()
{
    QString searchTerm = ui->searchLineEdit->text();
    if (searchTerm.isEmpty()) {
        QMessageBox::information(this, "Attention", "Veuillez entrer un terme de recherche.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT ID, name, author, genre, price FROM books "
                  "WHERE name LIKE :searchTerm OR author LIKE :searchTerm OR genre LIKE :searchTerm OR ID = :idSearchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");
    query.bindValue(":idSearchTerm", searchTerm.toInt());  // Convertir la recherche à un entier pour ID

    if (query.exec()) {
        model->setQuery(query);
        ui->bookListView->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la récupération des données.");
    }
}


void studentLibrary::on_bookListView_clicked(const QModelIndex &index)
{
    int bookId = model->data(model->index(index.row(), 0)).toInt();
    currentBookId = bookId;

    showBookDetails(bookId);

    // Afficher les boutons
    ui->addToCartButton->setVisible(true);
  //  ui->borrowButton->setVisible(true);
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
// void studentLibrary::on_voirMonPanierButton_clicked()
// {
//     // Affiche le panier
//     showCart();

//     // Masque le bouton "Voir mon panier" après l'avoir cliqué
//     ui->voirMonPanierButton->setVisible(false);
// }

// void studentLibrary::showCart()
// {
//     QSqlQuery query(db);
//     query.prepare("SELECT name, author, added_at FROM cart WHERE user_id = :user_id");

//     int userId = getUserId();
//     query.bindValue(":user_id", userId);

//     if (query.exec()) {
//         QSqlQueryModel *cartModel = new QSqlQueryModel(this);
//         cartModel->setQuery(query);

//         cartModel->setHeaderData(0, Qt::Horizontal, "Titre");
//         cartModel->setHeaderData(1, Qt::Horizontal, "Auteur");
//         cartModel->setHeaderData(2, Qt::Horizontal, "Date ajoutée");

//         ui->cartTableView->setModel(cartModel);

//         // Masquer les autres boutons
//         ui->searchButton->setVisible(false);

//         // Afficher le bouton retour
//         ui->backButton->setVisible(true);
//     } else {
//         QMessageBox::warning(this, "Erreur", "Impossible d'afficher le panier.");
//     }
// }
void studentLibrary::on_btnCart_clicked()
{
    int userId = getUserId();  // Assure-toi que cette fonction retourne le bon ID
    Cart *cart = new Cart(this);
    cart->setDatabase(db); // <-- transmet la connexion vivante
    cart->setUserId(userId); // si tu as ça
    cart->show();



}
// void studentLibrary::removeBookFromCart(int rowIndex)
// {
//     int bookId = ui->cartTableView->model()->data(ui->cartTableView->model()->index(rowIndex, 0)).toInt();
//     QSqlQuery query(db);
//     query.prepare("DELETE FROM cart WHERE user_id = :user_id AND book_id = :book_id");
//     query.bindValue(":user_id", getUserId());
//     query.bindValue(":book_id", bookId);

//     if (query.exec()) {
//         showCart();  // Rafraîchir l'affichage du panier
//     } else {
//         QMessageBox::warning(this, "Erreur", "Impossible de supprimer le livre.");
//     }
// }


// void MainWindow::on_btnVoirCarte_clicked()
// {
//     QJsonArray libraries;

//     QJsonObject lib1;
//     lib1["name"] = "Bibliothèque Centrale";
//     lib1["lat"] = 34.020882;
//     lib1["lng"] = -6.841650;
//     libraries.append(lib1);

//     QJsonObject lib2;
//     lib2["name"] = "Bibliothèque Faculté Sciences";
//     lib2["lat"] = 34.024563;
//     lib2["lng"] = -6.848329;
//     libraries.append(lib2);

//     MapViewer *map = new MapViewer(this);
//     map->resize(800, 600);
//     map->setLibraryData(libraries);
//     map->show();
// }

