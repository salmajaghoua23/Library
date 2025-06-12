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
#include <QSqlError>
#include <QtConcurrent/QtConcurrent>
#include <QSqlDatabase>
#include <QDebug>
#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QWidget>

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
    setupModernUI();
    setupConnections();
}
void studentLibrary::setupModernUI()
{
    // Fenêtre plus compacte
    this->setWindowTitle("📚 Bibliothèque Numérique - Espace Étudiant");
    this->resize(1000, 650);
    this->setMinimumSize(800, 500);

    this->setStyleSheet(R"(
    QDialog {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
            stop:0 #fbeffb, stop:1 #a18cd1);
        color: #3d246c;
        font-family: 'Segoe UI', Arial, sans-serif;
    }

    QGroupBox {
        background: rgba(255, 255, 255, 0.85);
        border: 2px solid #d291bc;
        border-radius: 15px;
        margin-top: 15px;
        padding-top: 18px;
        font-size: 15px;
        font-weight: 600;
        color: #7c3aed;
    }

    QGroupBox::title {
        subcontrol-origin: margin;
        left: 15px;
        padding: 0 10px;
        background: #fbc2eb;
        border-radius: 8px;
        color: #a21caf;
    }

    QLabel {
        background: transparent;
        border: none;
        font-size: 15px;
        color: #a21caf;
        font-weight: 600;
        letter-spacing: 0.5px;
    }

    QLineEdit {
        background: #fbeffb;
        border: 2px solid #d291bc;
        border-radius: 10px;
        padding: 12px 16px;
        font-size: 16px;
        color: #7c3aed;
        min-height: 32px;
        font-weight: 600;
    }

    QLineEdit:focus {
        border: 2px solid #a18cd1;
        background: #fff0f6;
        color: #a21caf;
    }

    QLineEdit::placeholder {
        color: #d291bc;
        font-style: italic;
    }

    QPushButton {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
            stop:0 #fbc2eb, stop:1 #a18cd1);
        color: #7c3aed;
        border: none;
        border-radius: 10px;
        padding: 10px 18px;
        font-size: 15px;
        font-weight: 700;
        min-width: 110px;
        transition: all 0.3s ease;
    }

    QPushButton:hover {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
            stop:0 #a18cd1, stop:1 #fbc2eb);
        color: #a21caf;
        box-shadow: 0 4px 12px #d291bc;
    }

    QPushButton#searchButton {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
            stop:0 #fbc2eb, stop:1 #a18cd1);
        color: #a21caf;
    }

    QPushButton#searchButton:hover {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
            stop:0 #a18cd1, stop:1 #fbc2eb);
        color: #7c3aed;
    }

    QPushButton#borrowButton, QPushButton#addToCartButton {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
            stop:0 #fbc2eb, stop:1 #a18cd1);
        color: #fff;
    }

    QPushButton#borrowButton:hover, QPushButton#addToCartButton:hover {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
            stop:0 #a18cd1, stop:1 #fbc2eb);
        color: #fff0f6;
    }

    QPushButton#backButton, QPushButton#btnCart, QPushButton#btnHistorique {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
            stop:0 #fbeffb, stop:1 #d291bc);
        color: #a21caf;
    }

    QPushButton#backButton:hover, QPushButton#btnCart:hover, QPushButton#btnHistorique:hover {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
            stop:0 #d291bc, stop:1 #fbeffb);
        color: #7c3aed;
    }

    QTableView {
        background: #fbeffb;
        border: 1px solid #d291bc;
        border-radius: 10px;
        alternate-background-color: #fbc2eb;
        selection-background-color: #a18cd1;
        selection-color: #a21caf;
        font-size: 14px;
        color: #7c3aed;
        gridline-color: #fbc2eb;
    }

    QHeaderView::section {
        background: #a18cd1;
        color: #fff;
        padding: 10px;
        font-size: 15px;
        font-weight: 600;
        border: none;
        border-right: 1px solid #fbc2eb;
    }

    QTableView::item {
        padding: 8px;
        border-bottom: 1px solid #fbc2eb;
    }

    QTableView::item:hover {
        background: #fbc2eb;
    }

    QTableView::item:selected {
        background: #a18cd1;
        color: #fff0f6;
    }

    QScrollBar:vertical {
        background: #fbc2eb;
        width: 10px;
        border-radius: 5px;
    }

    QScrollBar::handle:vertical {
        background: #a18cd1;
        border-radius: 5px;
        min-height: 20px;
    }

    QScrollBar::handle:vertical:hover {
        background: #d291bc;
    }
)");
    // Layout principal avec espacement moderne
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(16);

    // Partie gauche - Recherche et liste
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->setSpacing(12);

    // Groupe de recherche avec icône
    QGroupBox *searchGroup = new QGroupBox("🔍 Rechercher dans la collection", this);
    QHBoxLayout *searchLayout = new QHBoxLayout(searchGroup);
    searchLayout->setSpacing(8);

    ui->searchLineEdit->setPlaceholderText("Rechercher par titre, auteur, genre ou ID...");
    ui->searchButton->setText("🔎");
    ui->searchButton->setObjectName("searchButton");

    searchLayout->addWidget(ui->searchLineEdit, 3);
    searchLayout->addWidget(ui->searchButton);
    leftLayout->addWidget(searchGroup);

    // Groupe de la liste des livres
    QGroupBox *booksGroup = new QGroupBox("📚 Catalogue des ouvrages", this);
    QVBoxLayout *booksLayout = new QVBoxLayout(booksGroup);

    ui->bookListView->setAlternatingRowColors(true);
    ui->bookListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bookListView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->bookListView->setSortingEnabled(true);

    booksLayout->addWidget(ui->bookListView);
    leftLayout->addWidget(booksGroup, 1);

    // Partie droite - Détails et actions
    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(12);

    // Groupe des détails du livre
    QGroupBox *detailsGroup = new QGroupBox("📖 Détails du livre sélectionné", this);
    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsGroup);

    ui->bookDetailsText->setWordWrap(true);
    ui->bookDetailsText->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->bookDetailsText->setMinimumHeight(220);
    ui->bookDetailsText->setText(
        "<div style='text-align: center; padding: 30px; color: #b0b0c3;'>"
        "<h3>📚 Sélectionnez un livre</h3>"
        "<p>Cliquez sur un livre dans la liste pour voir ses détails complets</p>"
        "</div>"
        );

    detailsLayout->addWidget(ui->bookDetailsText, 1);

    // Boutons d'action principaux
    QHBoxLayout *actionLayout = new QHBoxLayout();
    actionLayout->setSpacing(8);

    ui->addToCartButton->setText("🛒 Ajouter au panier");
    ui->addToCartButton->setObjectName("addToCartButton");
    ui->borrowButton->setText("📖 Emprunter maintenant");
    ui->borrowButton->setObjectName("borrowButton");

    // Initialement cachés
    ui->addToCartButton->setVisible(false);
    ui->borrowButton->setVisible(false);

    actionLayout->addWidget(ui->addToCartButton);
    actionLayout->addWidget(ui->borrowButton);
    actionLayout->addStretch();
    detailsLayout->addLayout(actionLayout);

    rightLayout->addWidget(detailsGroup, 1);

    // Boutons de navigation
    QHBoxLayout *navLayout = new QHBoxLayout();
    navLayout->setSpacing(8);

    ui->btnHistorique->setText("📜 Mon historique");
    ui->btnHistorique->setObjectName("btnHistorique");
    ui->btnCart->setText("🛍️ Mon panier");
    ui->btnCart->setObjectName("btnCart");
    ui->backButton->setText("🏠 Retour accueil");
    ui->backButton->setObjectName("backButton");

    navLayout->addWidget(ui->btnHistorique);
    navLayout->addWidget(ui->btnCart);
    navLayout->addStretch();
    navLayout->addWidget(ui->backButton);

    rightLayout->addLayout(navLayout);

    // Assemblage final
    mainLayout->addLayout(leftLayout, 60);
    mainLayout->addLayout(rightLayout, 40);

    // Configuration du panier (caché par défaut)
    cartTableView = new QTableView(this);
    cartTableView->setStyleSheet(ui->bookListView->styleSheet());
    cartTableView->hide();
}

void studentLibrary::setupConnections()
{
    connect(ui->searchButton, &QPushButton::clicked, this, &studentLibrary::on_searchButton_clicked);
    connect(ui->backButton, &QPushButton::clicked, this, &studentLibrary::on_backButton_clicked);
    connect(ui->bookListView, &QTableView::clicked, this, &studentLibrary::on_bookListView_clicked);
    connect(ui->borrowButton, &QPushButton::clicked, this, &studentLibrary::on_borrowButton_clicked);
    connect(ui->addToCartButton, &QPushButton::clicked, this, &studentLibrary::on_addToCartButton_clicked);
   // connect(ui->btnCart, &QPushButton::clicked, this, &studentLibrary::on_btnCart_clicked);
   // connect(ui->btnHistorique, &QPushButton::clicked, this, &studentLibrary::on_btnHistorique_clicked);

    // Recherche en temps réel
    connect(ui->searchLineEdit, &QLineEdit::returnPressed, this, &studentLibrary::on_searchButton_clicked);
}

// Amélioration de la fonction showBookDetails avec un design moderne
void studentLibrary::showBookDetails(int bookId)
{
    QSqlQuery query(db);
    query.prepare("SELECT name, author, genre, publisher, description, price, quantity, resume FROM books WHERE ID = :bookId");
    query.bindValue(":bookId", bookId);

    if (query.exec() && query.next()) {
        QString name = query.value("name").toString();
        QString author = query.value("author").toString();
        QString genre = query.value("genre").toString();
        QString publisher = query.value("publisher").toString();
        QString description = query.value("description").toString();
        double price = query.value("price").toDouble();
        int quantity = query.value("quantity").toInt();
        QString resume = query.value("resume").toString();

        // Statut de disponibilité avec couleur
        QString availability = quantity > 0 ?
                                   QString("<span style='color: #4CAF50; font-weight: bold;'>✅ %1 exemplaire(s) disponible(s)</span>").arg(quantity) :
                                   "<span style='color: #F44336; font-weight: bold;'>❌ Non disponible</span>";

        QString details = QString(R"(
    <div style='line-height: 1.8;'>
        <div style='background: rgba(161,140,209,0.08); padding: 15px; border-radius: 10px; margin-bottom: 15px; border-left: 4px solid #a18cd1;'>
            <h2 style='color: #a18cd1; margin: 0 0 10px 0; font-size: 20px;'>📚 %1</h2>
            <p style='margin: 5px 0; font-size: 14px;'><strong style='color: #fbc2eb;'>👤 Auteur:</strong> %2</p>
            <p style='margin: 5px 0; font-size: 14px;'><strong style='color: #fbc2eb;'>🏷️ Genre:</strong> %3</p>
            <p style='margin: 5px 0; font-size: 14px;'><strong style='color: #fbc2eb;'>🏢 Éditeur:</strong> %4</p>
        </div>
        <div style='display: flex; justify-content: space-between; margin-bottom: 15px;'>
            <div style='background: rgba(251,194,235,0.12); padding: 10px; border-radius: 8px; flex: 1; margin-right: 10px;'>
                <p style='margin: 0; text-align: center;'><strong style='color: #a18cd1;'>💰 Prix</strong></p>
                <p style='margin: 5px 0 0 0; text-align: center; font-size: 18px; font-weight: bold; color: #a18cd1;'>%5 €</p>
            </div>
            <div style='background: rgba(161,140,209,0.08); padding: 10px; border-radius: 8px; flex: 1;'>
                <p style='margin: 0; text-align: center;'><strong style='color: #a18cd1;'>📦 Disponibilité</strong></p>
                <p style='margin: 5px 0 0 0; text-align: center;'>%6</p>
            </div>
        </div>
        <div style='background: rgba(251,194,235,0.08); padding: 15px; border-radius: 10px; margin-bottom: 15px;'>
            <h3 style='color: #a18cd1; margin: 0 0 10px 0; font-size: 16px;'>📝 Description</h3>
            <p style='margin: 0; font-size: 13px; line-height: 1.6;'>%7</p>
        </div>
        <div style='background: rgba(251,194,235,0.08); padding: 15px; border-radius: 10px;'>
            <h3 style='color: #fbc2eb; margin: 0 0 10px 0; font-size: 16px;'>📖 Résumé</h3>
            <p style='margin: 0; font-size: 13px; line-height: 1.6;'>%8</p>
        </div>
    </div>
)").arg(
                                  name.toHtmlEscaped(),
                                  author.toHtmlEscaped(),
                                  genre.toHtmlEscaped(),
                                  publisher.toHtmlEscaped(),
                                  QString::number(price, 'f', 2),
                                  availability,
                                  description.toHtmlEscaped(),
                                  resume.toHtmlEscaped()
                                  );

        ui->bookDetailsText->setTextFormat(Qt::RichText);
        ui->bookDetailsText->setText(details);

        // Afficher les boutons d'action
        ui->addToCartButton->setVisible(true);
        ui->borrowButton->setVisible(quantity > 0); // N'afficher le bouton emprunt que si disponible
    } else {
        QMessageBox::critical(this, "❌ Erreur", "Impossible d'afficher les détails du livre: " + query.lastError().text());
    }
}

// [Garder toutes les autres fonctions existantes inchangées]
void studentLibrary::on_borrowButton_clicked()
{
    if (currentBookId == -1) {
        QMessageBox::warning(this, "⚠️ Attention", "Aucun livre sélectionné.");
        return;
    }

    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT quantity FROM books WHERE ID = :bookId");
    checkQuery.bindValue(":bookId", currentBookId);

    if (!checkQuery.exec() || !checkQuery.next()) {
        QMessageBox::critical(this, "❌ Erreur", "Impossible de vérifier la disponibilité du livre.");
        return;
    }

    int quantity = checkQuery.value(0).toInt();
    if (quantity <= 0) {
        QMessageBox::information(this, "📵 Indisponible", "Ce livre n'est plus disponible pour emprunt.");
        return;
    }

    QSqlQuery checkBorrowedQuery(db);
    checkBorrowedQuery.prepare("SELECT COUNT(*) FROM emprunts WHERE user_id = :userId AND book_id = :bookId AND return_date IS NULL");
    checkBorrowedQuery.bindValue(":userId", userId);
    checkBorrowedQuery.bindValue(":bookId", currentBookId);

    if (checkBorrowedQuery.exec() && checkBorrowedQuery.next() && checkBorrowedQuery.value(0).toInt() > 0) {
        QMessageBox::information(this, "📚 Déjà emprunté", "Vous avez déjà emprunté ce livre et ne l'avez pas encore rendu.");
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

        QMessageBox::information(this, "✅ Succès",
                                 QString("Livre emprunté avec succès!\n"
                                         "📅 Date de retour prévue: %1")
                                     .arg(returnDate.toString("dd/MM/yyyy")));

        // Rafraîchir les détails du livre
        showBookDetails(currentBookId);

    } catch (const std::exception& e) {
        db.rollback();
        QMessageBox::critical(this, "❌ Erreur", e.what());
    }
}

// [Garder toutes les autres fonctions existantes...]

studentLibrary::~studentLibrary()
{
    delete ui;
}

// [Toutes les autres fonctions restent identiques à l'original]
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
    ui->borrowButton->setVisible(true);
    ui->backButton->setVisible(true); // Affichez aussi le bouton retour
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

        // Vérifier si le livre est déjà dans le panier
        QSqlQuery checkQuery(db);
        checkQuery.prepare("SELECT COUNT(*) FROM cart WHERE user_id = :user_id AND book_id = :book_id");
        checkQuery.bindValue(":user_id", userId);
        checkQuery.bindValue(":book_id", bookId);
        checkQuery.exec();
        checkQuery.next();
        if (checkQuery.value(0).toInt() > 0) {
            QMessageBox::information(this, "Déjà présent", "Ce livre est déjà dans votre panier.");
            return;
        }

        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO cart (user_id, book_id, name, author) "
                            "VALUES (:user_id, :book_id, :name, :author)");
        insertQuery.bindValue(":user_id", userId);
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
