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
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
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

    // Créer un layout principal si nécessaire
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // Style général de la fenêtre avec dégradé de couleur
    this->setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #E0F7FA, stop:1 #B2EBF2);
        }
    )");
    this->setWindowTitle("🛒 Mon Panier de Livres");
    this->resize(600, 400); // Taille initiale réduite
  //  this->setMinimumSize(500, 500); // Taille minimale

    // Titre stylisé avec icône et ombre
    QLabel *titleLabel = new QLabel("🛒 Mon Panier de Livres", this);
    titleLabel->setStyleSheet(R"(
        QLabel {
            color: #00796B;
            font-size: 28px;
            font-weight: bold;
            padding: 20px;
            background-color: rgba(255, 255, 255, 0.8);
            border-radius: 15px;
            margin: 10px;
            qproperty-alignment: AlignCenter;
        }
    )");
    mainLayout->addWidget(titleLabel);
    QLabel *subtitleLabel = new QLabel("✨ Prêt à emprunter ? Voici votre sélection ✨", this);
    subtitleLabel->setStyleSheet(R"(
        QLabel {
            color: #00897B;
            font-size: 16px;
            font-style: italic;
            padding: 10px;
            qproperty-alignment: AlignCenter;
        }
    )");
    mainLayout->addWidget(subtitleLabel);

    // Ajouter le tableau existant de l'UI au layout
    mainLayout->addWidget(ui->tableView);
    // Créer un layout horizontal pour les boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(ui->btnRemoveSelected);
    buttonLayout->addWidget(ui->borrowButton);
    buttonLayout->addWidget(ui->btnBorrowAll);
    buttonLayout->addWidget(ui->btnClearCart);
    buttonLayout->addWidget(ui->voirMonPanierButton);
    buttonLayout->setSpacing(10);

    mainLayout->addLayout(buttonLayout);

    // Style moderne pour les boutons avec effets
    QString buttonStyle = R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #26A69A, stop:1 #00897B);
            color: white;
            border-radius: 10px;
            padding: 12px 20px;
            font-size: 14px;
            font-weight: bold;
            min-width: 150px;
            border: 2px solid #00796B;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #4DB6AC, stop:1 #26A69A);
            border: 2px solid #00695C;
        }
        QPushButton:pressed {
            background: #00897B;
        }
        QPushButton#btnRemoveSelected {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #EF5350, stop:1 #E53935);
            border: 2px solid #C62828;
        }
        QPushButton#btnRemoveSelected:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #E57373, stop:1 #EF5350);
        }
        QPushButton#btnBorrowAll {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #66BB6A, stop:1 #43A047);
            border: 2px solid #2E7D32;
        }
        QPushButton#btnBorrowAll:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #81C784, stop:1 #66BB6A);
        }
    )";

    ui->btnRemoveSelected->setStyleSheet(buttonStyle);
    ui->btnClearCart->setStyleSheet(buttonStyle);
    ui->btnBorrowAll->setStyleSheet(buttonStyle);
    ui->borrowButton->setStyleSheet(buttonStyle);
    ui->voirMonPanierButton->setStyleSheet(buttonStyle);
    QPushButton *btnRetour = new QPushButton("🔙 Retour", this);
    btnRetour->setObjectName("btnRetour");
    btnRetour->setStyleSheet(buttonStyle);
   buttonLayout->addWidget(btnRetour);
    // Style moderne pour le tableau (prend plus d'espace)
    QString tableStyle = R"(
        QTableView {
            background-color: white;
            border: 2px solid #B2DFDB;
            border-radius: 10px;
            alternate-background-color: #E0F2F1;
            selection-background-color: #4DB6AC;
            selection-color: white;
            font-size: 14px;
            gridline-color: #B2DFDB;color:black;
        }
        QTableView QTableCornerButton::section {
            background: #00897B;
            border: 1px solid #B2DFDB;
        }
        QHeaderView::section {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #00897B, stop:1 #00796B);
            color: white;
            padding: 12px;
            font-size: 14px;
            font-weight: bold;
            border: none;
            border-radius: 0px;
        }
        QTableView::item {
            padding: 10px;
            border-bottom: 1px solid #B2DFDB;
        }
        QTableView::item:hover {
            background: #B2EBF2;
            color:black;
        }
    )";

    ui->tableView->setStyleSheet(tableStyle);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(300);
    ui->tableView->verticalHeader()->setDefaultSectionSize(60);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setMinimumHeight(200);
    // Redimensionner pour occuper plus d'espace
    QSize screenSize = QApplication::primaryScreen()->availableSize();
    ui->tableView->setMinimumHeight(screenSize.height() * 0.6);
    buttonLayout->addWidget(btnRetour);
    // Connexions des boutons
    connect(ui->btnRemoveSelected, &QPushButton::clicked, this, &Cart::on_btnRemoveSelected_clicked);
    connect(ui->btnClearCart, &QPushButton::clicked, this, &Cart::on_btnClearCart_clicked);
    connect(ui->btnBorrowAll, &QPushButton::clicked, this, &Cart::on_btnBorrowAll_clicked);
    connect(ui->borrowButton, &QPushButton::clicked, this, &Cart::on_borrowButton_clicked);
    connect(ui->voirMonPanierButton, &QPushButton::clicked, this, &Cart::on_voirMonPanierButton_clicked);
    connect(btnRetour, &QPushButton::clicked, this, &Cart::on_btnRetour_clicked);
    // Charger le panier initial
    //chargerPanier();
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
        cartModel->setHeaderData(2, Qt::Horizontal, "Date ajoutée");
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
