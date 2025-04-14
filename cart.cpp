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
    chargerPanier();  // Charger le panier à l'ouverture
    QLabel *welcomeLabel = new QLabel("📚 Ready to borrow? Review your selected books below!", this);
    welcomeLabel->setStyleSheet("color: #8A2BE2; font-size: 16px; font-style: italic; padding: 8px;");
    // Style pour les boutons
    QString buttonStyle = R"(
        QPushButton {
            background-color: #6A1B9A;  /* Violet foncé */
            color: white;
            border-radius: 10px;
            font-size: 16px;
            padding: 10px;
            border: 2px solid #FFD700;  /* Doré */
        }
        QPushButton:hover {
            background-color: #8E24AA;  /* Violet clair */
            border: 2px solid #FFEB3B;  /* Doré clair */
        }
        QPushButton:pressed {
            background-color: #4A148C;  /* Violet encore plus foncé */
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
            background-color: #F3E5F5;  /* Violet très clair */
            color: #4A148C;  /* Violet foncé */
            border: 1px solid #6A1B9A;
            font-size: 14px;
            font-family: Arial, sans-serif;
        }
        QTableView::item {
            padding: 8px;
            border-bottom: 1px solid #6A1B9A;
        }
        QTableView::item:selected {
            background-color: #FFEB3B;  /* Doré clair */
            color: #4A148C;  /* Violet foncé */
        }
        QHeaderView::section {
            background-color: #6A1B9A;
            color: black;
            font-size: 16px;
            padding: 5px;
        }
        QHeaderView::section:horizontal {
            border: 1px solid #6A1B9A;
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
    query.prepare("SELECT name, author, added_at FROM cart WHERE user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Impossible d'afficher le panier.\n\n" + query.lastError().text());
        return;
    }

    QSqlQueryModel *cartModel = new QSqlQueryModel(this);
    cartModel->setQuery(query);

    cartModel->setHeaderData(0, Qt::Horizontal, "Titre");
    cartModel->setHeaderData(1, Qt::Horizontal, "Auteur");
    cartModel->setHeaderData(2, Qt::Horizontal, "Date ajoutée");

    ui->tableView->setModel(cartModel);
}


// Supprimer un livre sélectionné
void Cart::on_btnRemoveSelected_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    if (row != -1) {
        int bookId = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();
        QSqlQuery query(db);
        query.prepare("UPDATE books SET in_cart = 0 WHERE ID = :bookId");
        query.bindValue(":bookId", bookId);
        if (query.exec()) {
            chargerPanier();
        }
    }
}

// Vider tout le panier
void Cart::on_btnClearCart_clicked()
{
    QSqlQuery query(db);
    if (query.exec("UPDATE books SET in_cart = 0 WHERE in_cart = 1")) {
        chargerPanier();
        QMessageBox::information(this, "Succès", "Panier vidé.");
    }
}

// Emprunter tous les livres
void Cart::on_btnBorrowAll_clicked()
{
    QSqlQuery select(db), update(db);
    select.prepare("SELECT ID, title FROM books WHERE in_cart = 1 AND quantity > 0");

    if (select.exec()) {
        while (select.next()) {
            int bookId = select.value("ID").toInt();
            QString title = select.value("title").toString();

            update.prepare("UPDATE books SET quantity = quantity - 1, in_cart = 0 WHERE ID = :id AND quantity > 0");
            update.bindValue(":id", bookId);
            if (update.exec()) {
                // Historique
                QFile file("historique_reservations.txt");
                if (file.open(QIODevice::Append | QIODevice::Text)) {
                    QTextStream out(&file);
                    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
                    out << date << " - " << title << "\n";
                    file.close();
                }
            }
        }
        chargerPanier();
        QMessageBox::information(this, "Succès", "Tous les livres ont été empruntés.");
    } else {
        QMessageBox::warning(this, "Erreur", "Échec lors de l'emprunt.");
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
    query.prepare("UPDATE books SET quantity = quantity - 1, in_cart = 0 WHERE ID = :bookId AND quantity > 0");
    query.bindValue(":bookId", bookId);

    if (query.exec() && query.numRowsAffected() > 0) {
        QMessageBox::information(this, "Succès", "Livre emprunté avec succès.");

        QFile file("historique_reservations.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            out << date << " - " << nomLivre << "\n";
            file.close();
        }

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
