#include "studentlibrary.h"
#include "ui_studentlibrary.h"
#include "digitalLibrary.h"
#include "mapviewer.h"
#include "cart.h"
#include"Login.h"
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
#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QVBoxLayout>
#include<QWidget>
studentLibrary::studentLibrary(QWidget *parent, QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::studentLibrary),
    db(db),
    model(new QSqlQueryModel(this)),
    currentBookId(-1)
{
    ui->setupUi(this);

    // Création de la table cart si elle n'existe pas
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
   // ui->borrowButton->setVisible(false);
    ui->backButton->setVisible(false);

    // Création du bouton Carte
    // QPushButton *btnCarte = new QPushButton("🗺️ Voir sur une carte", this);

    // // Style du bouton
    // btnCarte->setStyleSheet(R"(
    //     QPushButton {
    //         font-family: 'Georgia', serif;
    //         font-size: 20px;
    //         font-style: italic;
    //         font-weight: bold;
    //         color: #4B0082;
    //         background-color: #FFB6C1;
    //         border-radius: 12px;
    //         padding: 8px;
    //     }
    //     QPushButton:hover {
    //         background-color: #B57EDC;
    //     }
    //     QPushButton:pressed {
    //         background-color: #DDA0DD;
    //     }
    // )");

    // // Créer un layout et l'associer au frame
    // QVBoxLayout *carteLayout = new QVBoxLayout();
    // carteLayout->addWidget(btnCarte);

    // // Appliquer le layout au QFrame
    // ui->buttonLayout->setLayout(carteLayout);
    // // Connexion du bouton à la fonction
    // connect(btnCarte, &QPushButton::clicked, this, &studentLibrary::afficherCarteLivre);

    // // Création colonne "localisation" si absente
    // checkAndCreateLocalisationColumn();
    cartTableView = new QTableView(this);
    cartTableView->setGeometry(50, 400, 700, 200); // Position x, y et taille largeur, hauteur
    cartTableView->setStyleSheet("QTableView { background: white; color: #4B0082; font: 600 10pt 'Segoe UI'; border: 1px solid #FFDDEE; border-radius: 10px; }");
    cartTableView->horizontalHeader()->setStretchLastSection(true);
    cartTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    cartTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    cartTableView->hide(); // Cacher au début

    // Connexions
    connect(ui->searchButton, &QPushButton::clicked, this, &studentLibrary::on_searchButton_clicked);
    connect(ui->addToCartButton, &QPushButton::clicked, this, &studentLibrary::on_addToCartButton_clicked);
    connect(ui->backButton, &QPushButton::clicked, this, &studentLibrary::on_backButton_clicked);
    connect(ui->btnHistorique,&QPushButton::clicked, this, &studentLibrary::on_btnHistorique_clicked);
}

studentLibrary::~studentLibrary()
{
    delete ui;
}
void studentLibrary::updateBookLocalisation(int bookId, const QString& localisation)
{
    QSqlQuery query(db);
    query.prepare("UPDATE books SET localisation = :localisation WHERE id = :bookId;");
    query.bindValue(":localisation", localisation);
    query.bindValue(":bookId", bookId);

    if (query.exec()) {
        qDebug() << "Localisation mise à jour avec succès.";
    } else {
        qDebug() << "Erreur lors de la mise à jour de la localisation: " << query.lastError();
    }
}
void studentLibrary::checkAndCreateLocalisationColumn()
{
    // Vérifier si la colonne "localisation" existe déjà
    QSqlQuery query(db);
    query.prepare("PRAGMA table_info(books);");  // Pour SQLite, ajuste selon ton SGBD
    query.exec();

    bool localisationExists = false;
    while (query.next()) {
        if (query.value(1).toString() == "localisation") {
            localisationExists = true;
            break;
        }
    }

    // Si la colonne n'existe pas, on la crée
    if (!localisationExists) {
        QSqlQuery addColumnQuery(db);
        addColumnQuery.prepare("ALTER TABLE books ADD COLUMN localisation TEXT;");
        if (addColumnQuery.exec()) {
            qDebug() << "Colonne 'localisation' ajoutée avec succès.";
        } else {
            qDebug() << "Erreur lors de l'ajout de la colonne 'localisation': " << addColumnQuery.lastError();
        }
    }
}

// void studentLibrary::afficherCarteLivre() {
//     QString localisation = getLocalisationLivre(); // récupère depuis la DB
//     QDialog *carteDialog = new QDialog(this);
//     carteDialog->setWindowTitle("Localisation du livre");

//     QLabel *carte = new QLabel;
//     carte->setPixmap(QPixmap(":/images/plan_bibliotheque.png").scaled(500, 400));

//     QLabel *marker = new QLabel(carte);
//     marker->setPixmap(QPixmap(":/images/marker.png").scaled(20, 20));
//     marker->move(getCoordonnées(localisation)); // positionne le marqueur

//     QVBoxLayout *layout = new QVBoxLayout(carteDialog);
//     layout->addWidget(carte);

//     carteDialog->setLayout(layout);
//     carteDialog->exec();
// }
QPoint studentLibrary::getCoordonnées(const QString& localisation) {
    static QMap<QString, QPoint> map = {
                                        {"Section A, Étagère 1", QPoint(50, 50)},
                                        {"Section A, Étagère 2", QPoint(100, 50)},
                                        {"Section A, Étagère 3", QPoint(150, 50)},
                                        {"Section B, Étagère 1", QPoint(50, 100)},
                                        {"Section B, Étagère 2", QPoint(100, 100)},
                                        {"Section B, Étagère 3", QPoint(150, 100)},
                                        };

    QPoint coord = map.value(localisation, QPoint(-1, -1));
    if (coord == QPoint(-1, -1)) {
        qDebug() << "Localisation non trouvée dans la map : " << localisation;
    }
    return coord;
}


void studentLibrary::afficherCarteLivre()
{
    // Créer un QDialog pour la carte
    QDialog *carteDialog = new QDialog(this);
    carteDialog->setWindowTitle("📍 Localisation");

    // Créer une scène et une vue
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene, carteDialog);
    view->setFixedSize(800, 800);
    scene->setSceneRect(0, 0, 800, 800);

    // Charger l'image du plan de la bibliothèque
    QPixmap carte(":/cartLocalisation.png");
    if (carte.isNull()) {
        QMessageBox::warning(this, "Erreur", "L'image de la carte n'a pas été trouvée !");
        return;
    }

    QGraphicsPixmapItem *carteItem = scene->addPixmap(carte.scaled(800, 800, Qt::KeepAspectRatioByExpanding));
    carteItem->setZValue(0);  // fond

    // Récupérer la localisation depuis la base de données
    QSqlQuery query(db);
    query.prepare("SELECT localisation FROM books WHERE id = :id");
    query.bindValue(":id", currentBookId);

    if (query.exec() && query.next()) {
        QString localisation = query.value(0).toString();
        QPoint coord = getCoordonnées(localisation);

        if (coord != QPoint(-1, -1)) {
            // Ajouter un point rouge (ellipse) à l'emplacement du livre
            QGraphicsEllipseItem *point = scene->addEllipse(coord.x(), coord.y(), 12, 12, QPen(Qt::red), QBrush(Qt::red));
            point->setZValue(1);  // au-dessus de la carte
        } else {
            QMessageBox::information(this, "Localisation non trouvée", "Ce livre n'a pas de coordonnées définies sur la carte.");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer la localisation du livre.");
    }

    // Afficher la vue dans la boîte de dialogue
    QVBoxLayout *layout = new QVBoxLayout(carteDialog);
    layout->addWidget(view);
    carteDialog->setLayout(layout);
    carteDialog->exec();
}

void studentLibrary::on_btnLocalisation_clicked() {
    afficherCarteLivre();
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
        this->hide();
        Login login;
        login.exec();

}
void studentLibrary::on_searchButton_clicked()
{
    QString searchTerm = ui->searchLineEdit->text();

    if (searchTerm.isEmpty()) {
        QMessageBox::information(this, "Attention", "Veuillez entrer un terme de recherche.");

        // Rendre le fond de la QTableView transparent si aucun terme n'est entré
        ui->bookListView->setStyleSheet("QTableView {"
                                        "background: transparent;"
                                        "color: rgb(85, 0, 127);"
                                        "font: 600 11pt 'Segoe UI';"
                                        "border: 1px solid #dda0dd;"
                                        "border-radius: 10px;"
                                        "}");
        // Rendre le fond du QLabel transparent lorsque la recherche est vide
        ui->bookDetailsText->setStyleSheet("QLabel {"
                                       "font: 700 italic 9pt 'Segoe UI';"
                                       "color: black;"
                                       "background: transparent;"
                                       "}");
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

        // Rendre le fond de la QTableView visible après la recherche
        ui->bookListView->setStyleSheet("QTableView {"
                                        "background: white;"
                                        "color: #4B0082;"
                                        "font: 600 11pt 'Segoe UI';"
                                        "border: 1px solid #FFDDEE;"
                                        "}");
        // Rendre le fond du QLabel visible après la recherche
        ui->bookDetailsText->setStyleSheet("QLabel {"
                                       "font: 700 italic 9pt 'Segoe UI';"
                                       "color: black;"
                                       "background: white;"
                                       "}");
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
void studentLibrary::showCart()
{
    QSqlQueryModel *cartModel = new QSqlQueryModel(this);

    QSqlQuery query(db);
    query.prepare("SELECT book_id, name, author FROM cart WHERE user_id = :user_id");
    query.bindValue(":user_id", getUserId());

    if (query.exec()) {
        cartModel->setQuery(query);
        cartModel->setHeaderData(0, Qt::Horizontal, "ID Livre");
        cartModel->setHeaderData(1, Qt::Horizontal, "Nom");
        cartModel->setHeaderData(2, Qt::Horizontal, "Auteur");

        cartTableView->setModel(cartModel);
        cartTableView->show();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'afficher le panier.");
    }
}

void studentLibrary::removeBookFromCart(int rowIndex)
{
    int bookId = cartTableView->model()->data(cartTableView->model()->index(rowIndex, 0)).toInt();
    QSqlQuery query(db);
    query.prepare("DELETE FROM cart WHERE user_id = :user_id AND book_id = :book_id");
    query.bindValue(":user_id", getUserId());
    query.bindValue(":book_id", bookId);

    if (query.exec()) {
        showCart();  // Rafraîchir l'affichage du panier
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de supprimer le livre.");
    }
}
