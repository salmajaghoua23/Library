#include "cart.h"
#include "ui_cart.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QSqlError>
#include <QHeaderView>
#include <QScreen>
#include <QApplication>

Cart::Cart(QWidget *parent, QSqlDatabase db, int userId) :
    QDialog(parent),
    ui(new Ui::Cart),
    db(db),
    userId(userId)
{
    ui->setupUi(this);

    // Style général rose/violet pastel
    this->setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #fbeffb, stop:1 #a18cd1);
        }
        QLabel {
            color: #a21caf;
            font-size: 17px;
            font-weight: bold;
            padding: 10px;
            background-color: rgba(255, 255, 255, 0.8);
            border-radius: 10px;
            margin: 5px;
            qproperty-alignment: AlignCenter;
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #fbc2eb, stop:1 #a18cd1);
            color: #7c3aed;
            border-radius: 8px;
            padding: 10px 18px;
            font-size: 15px;
            font-weight: bold;
            min-width: 100px;
            max-width: 140px;
            border: none;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #a18cd1, stop:1 #fbc2eb);
            color: #a21caf;
        }
        QPushButton#btnRemoveSelected {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #fbc2eb, stop:1 #d291bc);
            color: #a21caf;
        }
        QPushButton#btnBorrowAll {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #a18cd1, stop:1 #fbc2eb);
            color: #fff;
        }
        QTableView {
            background-color: #fbeffb;
            border: 1px solid #d291bc;
            border-radius: 8px;
            font-size: 14px;
            color: #7c3aed;
            gridline-color: #fbc2eb;
            alternate-background-color: #fbc2eb;
            selection-background-color: #a18cd1;
            selection-color: #a21caf;
        }
        QHeaderView::section {
            background: #a18cd1;
            color: #fff;
            padding: 8px;
            font-size: 14px;
            font-weight: 600;
            border: none;
            border-right: 1px solid #fbc2eb;
        }
        QTableView::item {
            padding: 5px;
            border-bottom: 1px solid #fbc2eb;
        }
        QTableView::item:hover {
            background: #fbc2eb;
        }
        QTableView::item:selected {
            background: #a18cd1;
            color: #fff0f6;
        }
    )");

    this->setWindowTitle("🛒 Mon Panier de Livres");
    this->resize(800, 600);

    // Titre
    QLabel *titleLabel = new QLabel("🛒 Mon Panier", this);
    QLabel *subtitleLabel = new QLabel("Votre sélection de livres", this);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(subtitleLabel);

    // Configuration du tableau
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableView->setMinimumHeight(250);
    ui->tableView->setMaximumHeight(350);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(200);
    ui->tableView->verticalHeader()->setDefaultSectionSize(40);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    mainLayout->addWidget(ui->tableView);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(8);

    buttonLayout->addWidget(ui->btnRemoveSelected);
    buttonLayout->addWidget(ui->borrowButton);
    buttonLayout->addWidget(ui->btnBorrowAll);
    buttonLayout->addWidget(ui->btnClearCart);
    buttonLayout->addWidget(ui->voirMonPanierButton);

    QPushButton *btnRetour = new QPushButton("Retour", this);
    buttonLayout->addWidget(btnRetour);

    mainLayout->addLayout(buttonLayout);

    // Connexions
    connect(ui->btnRemoveSelected, &QPushButton::clicked, this, &Cart::on_btnRemoveSelected_clicked);
    connect(ui->btnClearCart, &QPushButton::clicked, this, &Cart::on_btnClearCart_clicked);
    connect(ui->btnBorrowAll, &QPushButton::clicked, this, &Cart::on_btnBorrowAll_clicked);
    connect(ui->borrowButton, &QPushButton::clicked, this, &Cart::on_borrowButton_clicked);
    connect(ui->voirMonPanierButton, &QPushButton::clicked, this, &Cart::on_voirMonPanierButton_clicked);
    connect(btnRetour, &QPushButton::clicked, this, &Cart::on_btnRetour_clicked);

    chargerPanier();
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
void Cart::on_btnRetour_clicked()
{
    this->close(); // Ferme la fenêtre du panier
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
    QSqlQuery select(db), deleteQuery(db);
    select.prepare("SELECT book_id, name FROM cart WHERE user_id = :userId");
    select.bindValue(":userId", userId);

    if (select.exec()) {
        bool success = true;

        while (select.next()) {
            int bookId = select.value("book_id").toInt();
            QString title = select.value("name").toString();

            // Supprimer le livre du panier (car il est "emprunté")
            deleteQuery.prepare("DELETE FROM cart WHERE user_id = :userId AND book_id = :bookId");
            deleteQuery.bindValue(":userId", userId);
            deleteQuery.bindValue(":bookId", bookId);

            if (!deleteQuery.exec() || deleteQuery.numRowsAffected() == 0) {
                success = false;
                break;
            }

            // Tu peux ajouter une insertion dans une table historique ici si nécessaire
        }

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
    query.prepare("SELECT id  name, author, added_at FROM cart WHERE user_id = :user_id");

    query.bindValue(":user_id", userId);

    if (query.exec()) {
        QSqlQueryModel *cartModel = new QSqlQueryModel(this);
        cartModel->setQuery(query);

        cartModel->setHeaderData(0, Qt::Horizontal, "id");
        cartModel->setHeaderData(1, Qt::Horizontal, "Auteur");
       // cartModel->setHeaderData(2, Qt::Horizontal, "Date ajoutée");
        cartModel->setHeaderData(3, Qt::Horizontal, "Titre");

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

    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un livre.");
        return;
    }

    int row = selectedIndexes.first().row();

  int bookId = model->data(model->index(row, 0)).toInt();
    QString bookName = model->data(model->index(row, 1)).toString();

    QSqlQuery deleteQuery(db);
    qDebug() << "Ligne sélectionnée: " << row;
    for (int i = 0; i < model->columnCount(); ++i) {
        qDebug() << "Colonne" << i << ":" << model->data(model->index(row, i)).toString();
    }

    deleteQuery.prepare("DELETE FROM cart WHERE user_id = :userId AND book_id = :bookId");
    deleteQuery.bindValue(":userId", userId);
    deleteQuery.bindValue(":bookId", bookId);

    if (!deleteQuery.exec() || deleteQuery.numRowsAffected() == 0) {
        QMessageBox::warning(this, "Erreur", "Aucun livre supprimé. Vérifiez les ID.");
        return;
    }

    // Historique
    QSqlQuery insertQuery(db);
    insertQuery.prepare("INSERT INTO borrow_history (user_id, book_id, book_name, borrowed_at) "
                        "VALUES (:userId, :bookId, :bookName, :borrowedAt)");
    insertQuery.bindValue(":userId", userId);
    insertQuery.bindValue(":bookId", bookId);
    insertQuery.bindValue(":bookName", bookName);
    insertQuery.bindValue(":borrowedAt", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    insertQuery.exec(); // Optionnel : ajouter vérification

    chargerPanier(); // ou showCart()
    QMessageBox::information(this, "Succès", "Le livre a été emprunté avec succès.");
}

int Cart::getUserId()
{
    return userId;
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
