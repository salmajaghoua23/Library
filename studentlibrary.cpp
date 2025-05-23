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

studentLibrary::studentLibrary(QWidget *parent, QSqlDatabase db, int userId) :
    QDialog(parent),
    ui(new Ui::studentLibrary),
    db(db),
    model(new QSqlQueryModel(this)),
    currentBookId(-1),
    userId(userId)
{
    ui->setupUi(this);
    if (!db.isOpen()) {
        qDebug() << "Database connection is not open!";
        if (!db.open()) {
            qDebug() << "Failed to reopen database:" << db.lastError();
        }
    }
    // Style général avec fond dégradé et ombres
    this->setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #E0F7FA, stop:1 #B2EBF2);
        }
    )");
    this->setWindowTitle("📚 Bibliothèque Étudiante - Explorer les Livres");
    this->resize(800, 600);

    // Réorganiser le layout principal
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QVBoxLayout *rightLayout = new QVBoxLayout();

    // Zone de recherche (côté gauche)
    QGroupBox *searchGroup = new QGroupBox("🔍 Recherche Avancée", this);
    searchGroup->setStyleSheet(R"(
        QGroupBox {
            background: rgba(255,255,255,0.9);
            border: 2px solid #a5d8ff;
            border-radius: 15px;
            margin-top: 10px;
            padding-top: 15px;
            font-size: 16px;
            font-weight: bold;
            color: #3a4a5a;
        }
    )");

    QHBoxLayout *searchLayout = new QHBoxLayout(searchGroup);
    ui->searchLineEdit->setPlaceholderText("Titre, Auteur, Genre...");
    ui->searchLineEdit->setStyleSheet(R"(
        QLineEdit {
            background: white;
            border: 2px solid #d6e4ff;
            border-radius: 12px;
            padding: 10px;
            font-size: 14px;
            min-width: 250px;color:black;
        }
    )");

    ui->searchButton->setText("Rechercher");
    ui->searchButton->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #4facfe, stop:1 #00f2fe);
            color: white;
            border-radius: 12px;
            padding: 10px 20px;
            font-size: 14px;
            font-weight: bold;
            border: none;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #3aa0f6, stop:1 #00d2ff);
        }
    )");

    searchLayout->addWidget(ui->searchLineEdit);
    searchLayout->addWidget(ui->searchButton);
    leftLayout->addWidget(searchGroup);

    // Liste des livres (côté gauche)
    QGroupBox *booksGroup = new QGroupBox("📖 Résultats de Recherche", this);
    booksGroup->setStyleSheet(searchGroup->styleSheet());

    QVBoxLayout *booksLayout = new QVBoxLayout(booksGroup);
    ui->bookListView->setStyleSheet(R"(
        QTableView {
            background: white;
            border: 1px solid #d6e4ff;
            border-radius: 10px;
            alternate-background-color:white;
            selection-background-color:white ;
            font-size: 10px; color:blue;
        }
        QHeaderView::section {
           background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #E0F7FA, stop:1 #B2EBF2);
            color: black;
            padding: 10px;
            font-weight: bold;
            border: none;
        }
    )");
    booksLayout->addWidget(ui->bookListView);
    leftLayout->addWidget(booksGroup);

    // Détails du livre (côté droit)
    QGroupBox *detailsGroup = new QGroupBox("📚 Détails du Livre", this);
    detailsGroup->setStyleSheet(searchGroup->styleSheet());

    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsGroup);
    ui->bookDetailsText->setStyleSheet(R"(
        QLabel {
            background: white;
            border: 2px solid #d6e4ff;
            border-radius: 10px;
            padding: 15px;
            font-size: 14px;
            color: blue;
            min-height: 200px;
        }
    )");
    detailsLayout->addWidget(ui->bookDetailsText);

    // Boutons d'action
    QHBoxLayout *actionButtons = new QHBoxLayout();

    QString actionButtonStyle = R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #38ef7d, stop:1 #11998e);
            color: white;
            border-radius: 10px;
            padding: 10px 15px;
            font-size: 14px;
            font-weight: bold;
            min-width: 120px;
            border: none;
            margin: 5px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #2fd673, stop:1 #0d857a);
        }
    )";

    ui->addToCartButton->setText("🛒 Ajouter au Panier");
    ui->borrowButton->setText("📖 Emprunter");
    ui->addToCartButton->setStyleSheet(actionButtonStyle);
    ui->borrowButton->setStyleSheet(actionButtonStyle);

    actionButtons->addWidget(ui->addToCartButton);
    actionButtons->addWidget(ui->borrowButton);
    detailsLayout->addLayout(actionButtons);

    rightLayout->addWidget(detailsGroup);

    // Boutons de navigation
    QHBoxLayout *navButtons = new QHBoxLayout();

    QString navButtonStyle = R"(
        QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
            stop:0 #3498DB, stop:1 #2ECC71);
            color:white;
            border-radius: 10px;
            padding: 10px 20px;
            font-size: 14px;
            font-weight: bold;
            min-width: 150px;
            border: none;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #e67e00, stop:1 #e03000);
        }
    )";

    ui->btnHistorique->setText("🕒 Historique");
    ui->btnCart->setText("🛍 Voir le Panier");
    ui->backButton->setText("🔙 Retour");

    ui->btnHistorique->setStyleSheet(navButtonStyle);
    ui->btnCart->setStyleSheet(navButtonStyle);
    ui->backButton->setStyleSheet(navButtonStyle);

    navButtons->addWidget(ui->btnHistorique);
    navButtons->addWidget(ui->btnCart);
    navButtons->addWidget(ui->backButton);
    rightLayout->addLayout(navButtons);


    mainLayout->addLayout(leftLayout, 50);
    mainLayout->addLayout(rightLayout, 40);
    // Configuration du panier (caché par défaut)
    cartTableView = new QTableView(this);
    cartTableView->setStyleSheet(ui->bookListView->styleSheet());
    cartTableView->hide();
    //  connect(ui->borrowButton, &QPushButton::clicked, this, &studentLibrary::on_borrowButton_clicked);
    // Connexions
    connect(ui->searchButton, &QPushButton::clicked, this, &studentLibrary::on_searchButton_clicked);
    connect(ui->backButton, &QPushButton::clicked, this, &studentLibrary::on_backButton_clicked);
    // connect(ui->btnHistorique, &QPushButton::clicked, this, &studentLibrary::on_btnHistorique_clicked);
    // connect(ui->btnCart, &QPushButton::clicked, this, &studentLibrary::on_btnCart_clicked);
    connect(ui->bookListView, &QTableView::clicked, this, &studentLibrary::on_bookListView_clicked);
}
void studentLibrary::on_borrowButton_clicked()
{
    if (currentBookId == -1) {
        QMessageBox::warning(this, "Erreur", "Aucun livre sélectionné.");
        return;
    }
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT quantity FROM books WHERE ID = :bookId");
    checkQuery.bindValue(":bookId", currentBookId);

    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::critical(this, "Erreur", "Impossible de vérifier la disponibilité du livre.");
        return;
    }

    int quantity = checkQuery.value(0).toInt();
    if (quantity <= 0) {
        QMessageBox::information(this, "Indisponible", "Ce livre n'est plus disponible pour emprunt.");
        return;
    }
    QSqlQuery checkBorrowedQuery(db);
    checkBorrowedQuery.prepare("SELECT COUNT(*) FROM emprunts WHERE user_id = :userId AND book_id = :bookId AND return_date IS NULL");
    checkBorrowedQuery.bindValue(":userId", userId);
    checkBorrowedQuery.bindValue(":bookId", currentBookId);

    if (checkBorrowedQuery.exec() && checkBorrowedQuery.next() && checkBorrowedQuery.value(0).toInt() > 0) {
        QMessageBox::information(this, "Déjà emprunté", "Vous avez déjà emprunté ce livre et ne l'avez pas encore rendu.");
        return;
    }

    // Calculer les dates d'emprunt et de retour (par exemple, 2 semaines)
    QDate borrowDate = QDate::currentDate();
    QDate returnDate = borrowDate.addDays(14); // 2 semaines

    // Démarrer une transaction
    db.transaction();

    try {
        // 1. Ajouter l'emprunt dans la table emprunts
        QSqlQuery borrowQuery(db);
        borrowQuery.prepare("INSERT INTO emprunts (user_id, book_id, borrow_date, return_date) "
                            "VALUES (:userId, :bookId, :borrowDate, :returnDate)");
        borrowQuery.bindValue(":userId", userId);
        borrowQuery.bindValue(":bookId", currentBookId);
        borrowQuery.bindValue(":borrowDate", borrowDate.toString("yyyy-MM-dd"));
        borrowQuery.bindValue(":returnDate", returnDate.toString("yyyy-MM-dd"));
        qDebug() << "Requête SQL:" << borrowQuery.lastQuery();
        qDebug() << "Valeurs liées:"
                 << userId << currentBookId
                 << borrowDate.toString("yyyy-MM-dd")
                 << returnDate.toString("yyyy-MM-dd");
        if (!borrowQuery.exec()) {
            throw std::runtime_error("Erreur lors de l'ajout de l'emprunt: " +
                                     borrowQuery.lastError().text().toStdString());
        }

        // 2. Décrémenter la quantité disponible
        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE books SET quantity = quantity - 1 WHERE ID = :bookId");
        updateQuery.bindValue(":bookId", currentBookId);

        if (!updateQuery.exec()) {
            throw std::runtime_error("Erreur lors de la mise à jour de la quantité: " +
                                     updateQuery.lastError().text().toStdString());
        }

        // Tout s'est bien passé, valider la transaction
        db.commit();

        QMessageBox::information(this, "Succès",
                                 QString("Livre emprunté avec succès!\n"
                                         "Date de retour prévue: %1")
                                     .arg(returnDate.toString("dd/MM/yyyy")));

        // Rafraîchir les détails du livre
        showBookDetails(currentBookId);

    } catch (const std::exception& e) {
        db.rollback();
        QMessageBox::critical(this, "Erreur", e.what());
    }
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
    Historique *hist = new Historique(userId, db, this);
    hist->show();
}

int studentLibrary::getUserId()
{
    return userId;
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
                                        "border: 1px solid black;"
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

        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO cart (user_id, book_id, name, author) "
                            "VALUES (:user_id, :book_id, :name, :author)");
        insertQuery.bindValue(":user_id", userId); // L’ID de l’utilisateur connecté
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
// Dans studentLibrary.cpp
void studentLibrary::setCurrentUserId(int id) {
    userId = id;
}
