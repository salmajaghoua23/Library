#include "cart.h"
#include "ui_cart.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QSqlError>
Cart::Cart(QWidget *parent, QSqlDatabase db, int userId) :
    QDialog(parent),
    ui(new Ui::Cart),
    db(db),
    userId(userId)
{
    ui->setupUi(this);
    QString gradientStyle = R"(
QPushButton {
    background-color: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #FF69B4, stop:1 #8A2BE2
    );
    color: white;
    border-radius: 12px;
    padding: 10px 16px;
    font-size: 16px;
    font-weight: bold;
    border: 1px solid #DA70D6;
}

QPushButton:hover {
    background-color: qlineargradient(
        x1:0, y1:0, x2:1, y2:0,
        stop:0 #FF85C1, stop:1 #9F5DE2
    );
    border: 1px solid #FFD700;
}

QPushButton:pressed {
    background-color: #7B1FA2;
}

QTableView {
    background-color: #FFF0F5;
    color: #4A148C;
    font-size: 14px;
    font-family: 'Segoe UI', sans-serif;
    selection-background-color: #FFDDEE;
    selection-color: #4A148C;
    gridline-color: #E1BEE7;
    border: 1px solid #BA55D3;
    border-radius: 8px;
}

QTableView::item:hover {
    background-color: #F3E5F5;
}

QHeaderView::section {
    background-color: #DA70D6;
    color: white;
    font-weight: bold;
    padding: 6px;
    border: 1px solid #BA55D3;
}
)";

    ui->btnRemoveSelected->setStyleSheet(gradientStyle);
    ui->btnClearCart->setStyleSheet(gradientStyle);
    ui->btnBorrowAll->setStyleSheet(gradientStyle);
    ui->borrowButton->setStyleSheet(gradientStyle);
    ui->voirMonPanierButton->setStyleSheet(gradientStyle);
    ui->tableView->setStyleSheet(gradientStyle);
    chargerPanier();
   // showCart(); // Charger le panier à l'ouverture
    QLabel *welcomeLabel = new QLabel("📚 Ready to borrow? Review your selected books below!", this);
    welcomeLabel->setStyleSheet("color: #8A2BE2; font-size: 16px; font-style: italic; padding: 8px;");
    // Style pour les boutons
    QString buttonStyle = R"(
QPushButton {
    background-color: #2C5E2A;  /* Violet foncé */
    color: white;
    border-radius: 10px;
    font-size: 16px;
    padding: 10px;
    border: 2px solid #FFD700;  /* Doré */
    background-size: cover;  /* Couvre toute la zone du bouton */
    background-position: center;  /* Centre l'image */
    background-repeat: no-repeat;  /* Empêche l'image de se répéter */
    transition: all 0.3s ease;  /* Pour des transitions douces */
}

QPushButton:hover {
    background-color: rgba(142, 36, 170, 0.7);  /* Violet clair avec transparence */
    border: 2px solid #8A9B68;  /* Doré clair */
}

QPushButton:pressed {
    background-color: #8A9B68;  /* Violet foncé */
    background-image: none;  /* Enlève l'image de fond quand pressé */
}

    )";
    ui->btnRemoveSelected->setStyleSheet(buttonStyle);
    ui->btnClearCart->setStyleSheet(buttonStyle);
    ui->btnBorrowAll->setStyleSheet(buttonStyle);
    ui->borrowButton->setStyleSheet(buttonStyle);
    ui->voirMonPanierButton->setStyleSheet(buttonStyle);
    // Style pour QTableView
    QString tableStyle = R"(
QTableView {
    background-color: beige;  /* Violet très clair */
    color: #4A148C;  /* Violet foncé */
    border: 1px solid #6A1B9A;  /* Violet foncé pour la bordure */
    font-size: 14px;
    font-family: Arial, sans-serif;
    selection-background-color: #FFEB3B;  /* Doré clair pour la sélection */
    selection-color: #4A148C;  /* Violet foncé pour le texte sélectionné */
}

QTableView::item {
    padding: 8px;
    border-bottom: 1px solid #6A1B9A;  /* Bordure entre les lignes */
    transition: background-color 0.3s ease, color 0.3s ease;
}

QTableView::item:selected {
    background-color: #FFEB3B;  /* Doré clair */
    color: #4A148C;  /* Violet foncé */
}

QHeaderView::section {
    background-color: #6A1B9A;  /* Violet foncé */
    color: white;  /* Texte blanc pour une meilleure lisibilité */
    font-size: 16px;
    padding: 5px;
    font-weight: bold;  /* Pour donner un peu plus de présence aux titres de colonnes */
}

QHeaderView::section:horizontal {
    border: 1px solid #6A1B9A;  /* Bordure entre les colonnes */
}

/* Effet de survol pour les lignes */
QTableView::item:hover {
    background-color: #D1C4E9;  /* Violet clair quand on survole une ligne */
    color: #4A148C;  /* Violet foncé pour le texte */
}

    )";
    connect(ui->btnRemoveSelected, &QPushButton::clicked, this, &Cart::on_btnRemoveSelected_clicked);
    connect(ui->btnClearCart, &QPushButton::clicked, this, &Cart::on_btnClearCart_clicked);
    connect(ui->btnBorrowAll, &QPushButton::clicked, this, &Cart::on_btnBorrowAll_clicked);
    connect(ui->borrowButton, &QPushButton::clicked, this, &Cart::on_borrowButton_clicked);
    connect(ui->voirMonPanierButton, &QPushButton::clicked, this, &Cart::on_voirMonPanierButton_clicked);

    ui->tableView->setStyleSheet(tableStyle);
}

Cart::~Cart()
{
    delete ui;
}
void Cart::setUserId(int id) {
    userId = id;
}
void Cart::setDatabase(const QSqlDatabase &database) {
    db = database;
}

void Cart::chargerPanier()
{
    QSqlQuery query(db);
    query.prepare("SELECT book_id, name, author, added_at FROM cart WHERE user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Impossible d'afficher le panier.\n\n" + query.lastError().text());
        return;
    }

    QSqlQueryModel *cartModel = new QSqlQueryModel(this);
    cartModel->setQuery(query);

    cartModel->setHeaderData(1, Qt::Horizontal, "Titre");
    cartModel->setHeaderData(2, Qt::Horizontal, "Auteur");
    cartModel->setHeaderData(3, Qt::Horizontal, "Date ajoutée");

    ui->tableView->setModel(cartModel);
}



void Cart::on_btnRemoveSelected_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    if (row != -1) {
        int bookId = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();
        QSqlQuery query(db);
        query.prepare("DELETE FROM cart WHERE user_id = :userId AND book_id = :bookId");
        query.bindValue(":userId", userId);
        query.bindValue(":bookId", bookId);
        if (query.exec()) {
            chargerPanier();  // Rafraîchir le panier
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible de supprimer le livre du panier.");
        }
    }
}

void Cart::on_btnClearCart_clicked()
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM cart WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (query.exec()) {
        chargerPanier();  // Rafraîchir le panier
        QMessageBox::information(this, "Succès", "Panier vidé.");
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression du panier.");
    }
}

// Emprunter tous les livres
void Cart::on_btnBorrowAll_clicked()
{
    QSqlQuery select(db), update(db);
    select.prepare("SELECT book_id, name FROM cart WHERE user_id = :userId AND borrowed = 0");

    select.bindValue(":userId", userId);

    if (select.exec()) {
        bool success = true;  // Variable pour suivre si toutes les opérations ont réussi

        while (select.next()) {
            int bookId = select.value("book_id").toInt();
            QString title = select.value("name").toString();

            // Marquer le livre comme emprunté dans la table cart
            update.prepare("UPDATE cart SET borrowed = 1 WHERE user_id = :userId AND book_id = :bookId AND borrowed = 0");
            update.bindValue(":userId", userId);
            update.bindValue(":bookId", bookId);

            if (!update.exec() || update.numRowsAffected() == 0) {
                success = false;  // Si l'opération échoue pour un livre, on garde la variable en échec
                break;
            }

            // Enregistrer l'emprunt dans l'historique
            QFile file("historique_reservations.txt");
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);
                QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
                out << date << " - " << title << " emprunté par l'utilisateur " << userId << "\n";
                file.close();
            }
        }

        // Rafraîchir le panier si tout a été emprunté avec succès
        if (success) {
            chargerPanier();
            QMessageBox::information(this, "Succès", "Tous les livres ont été empruntés.");
        } else {
            QMessageBox::warning(this, "Erreur", "Échec lors de l'emprunt de tous les livres.");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les livres du panier.");
    }
}

void Cart::on_voirMonPanierButton_clicked()
{
    // Affiche le panier
    chargerPanier();

    // Masque le bouton "Voir mon panier" après l'avoir cliqué
    ui->voirMonPanierButton->setVisible(true);
}

void Cart::showCart()
{
    QSqlQuery query(db);
    query.prepare("SELECT name, author, added_at FROM cart WHERE user_id = :user_id");

    query.bindValue(":user_id", userId);

    if (query.exec()) {
        QSqlQueryModel *cartModel = new QSqlQueryModel(this);
        cartModel->setQuery(query);

        cartModel->setHeaderData(0, Qt::Horizontal, "Titre");
        cartModel->setHeaderData(1, Qt::Horizontal, "Auteur");
        cartModel->setHeaderData(2, Qt::Horizontal, "Date ajoutée");

    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'afficher le panier.");
    }
}

void Cart::on_borrowButton_clicked()
{
    QAbstractItemModel* model = ui->tableView->model();
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucun livre chargé.");
        return;
    }

    QModelIndex selectedIndex = ui->tableView->selectionModel()->currentIndex();
    if (!selectedIndex.isValid()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un livre.");
        return;
    }

    int row = selectedIndex.row();
    int bookId = model->data(model->index(row, 0)).toInt(); // Colonne 0 = ID
    QString nomLivre = model->data(model->index(row, 1)).toString(); // Colonne 1 = title

    QSqlQuery query(db);
    query.prepare("UPDATE cart SET borrowed = 1 WHERE user_id = :userId AND book_id = :bookId AND borrowed = 0");
    query.bindValue(":userId", userId);
    query.bindValue(":bookId", bookId);

    if (query.exec() && query.numRowsAffected() > 0) {
        QMessageBox::information(this, "Succès", "Livre emprunté avec succès.");

        // Enregistrer l'historique dans un fichier
        QFile file("historique_reservations.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            out << date << " - " << nomLivre << " emprunté par l'utilisateur " << userId << "\n";
            file.close();
        }

        // Rafraîchir le panier pour refléter l'emprunt
        chargerPanier();
    } else {
        QMessageBox::warning(this, "Erreur", "Ce livre est déjà emprunté ou indisponible.");
    }
}

int Cart::getUserId()
{
    // Exemple statique, tu devras adapter selon ton système d'authentification
    return 1;  // ID fictif de l'utilisateur
}
void Cart::removeBookFromCart(int rowIndex)
{
    int bookId = ui->tableView->model()->data(ui->tableView->model()->index(rowIndex, 0)).toInt();
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
