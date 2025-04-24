#include "deleteMember.h"
#include "ui_deleteMember.h"
#include "digitalLibrary.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QDebug>
#include <QHeaderView>

deleteMember::deleteMember(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::deleteMember),
    model(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Gestion des Membres");
    this->resize(800, 600);

    this->setStyleSheet(
        "QDialog { background-color: #f4f1ee; }"
        "QTableView {"
        "   background-color: #fdf6ee;"
        "   border: 1px solid #a1887f;"
        "   color: #3e2723;"
        "   selection-background-color: #a5d6a7;"
        "   selection-color: black;"
        "}"
        "QHeaderView::section {"
        "   background-color: #8d6e63;"
        "   color: white;"
        "   padding: 6px;"
        "   border: none;"
        "   font-weight: bold;"
        "}"
        "QPushButton {"
        "   background-color: #388e3c;"
        "   color: white;"
        "   padding: 10px 20px;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #2e7d32; }"
        );

    // Configuration du tableau
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setAlternatingRowColors(true);

    loadMembers();
    //QPushButton *returnBtn = new QPushButton("Retour à l'espace étudiant", this);
   // returnBtn->setObjectName("returnBtn");

    // Ajout du bouton au layout principal
    // if (ui->verticalLayout) {
    //     ui->verticalLayout->addWidget(returnBtn);
    // } else {
    //     // Création d'un nouveau layout si nécessaire
    //     QVBoxLayout *mainLayout = new QVBoxLayout(this);
    //     mainLayout->addWidget(ui->tableView);
    //     mainLayout->addWidget(ui->pushButton);
    //     mainLayout->addWidget(returnBtn);
    //     this->setLayout(mainLayout);
    // }

    loadMembers();

    connect(ui->pushButton, &QPushButton::clicked, this, &deleteMember::on_deleteMemberBtn_clicked);
    connect(ui->returnBtn, &QPushButton::clicked, this, &deleteMember::on_returnBtn_clicked);
}
deleteMember::~deleteMember()
{
    delete model;
    delete ui;
}
void deleteMember::on_returnBtn_clicked()
{
    // Ferme cette fenêtre et retourne à l'espace étudiant
    this->close();
   digitalLibrary *studentSpace = new digitalLibrary();
    studentSpace->show();
}
void deleteMember::loadMembers()
{
    digitalLibrary lib;
    QSqlDatabase db = lib.db;

    if (!db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
        return;
    }

    if (model) {
        delete model;
    }

    model = new QSqlTableModel(this, db);
    model->setTable("accounts");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(0, Qt::Horizontal, tr("username"));  // username
    model->setHeaderData(1, Qt::Horizontal, tr("name"));     // name
    model->setHeaderData(2, Qt::Horizontal, tr("Mpassword")); // password
    model->setHeaderData(3, Qt::Horizontal, tr("Role"));    // role

    if (!model->select()) {
        QMessageBox::critical(this, "Erreur", "Impossible de charger les membres: " + model->lastError().text());
        return;
    }

    ui->tableView->setModel(model);
   // ui->tableView->resizeColumnsToContents();
}

void deleteMember::on_deleteMemberBtn_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList selectedRows = selection->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner au moins un membre à supprimer");
        return;
    }

    int count = selectedRows.count();
    if (QMessageBox::question(this, "Confirmation",
                              QString("Voulez-vous vraiment supprimer %1 membre(s) ?").arg(count),
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }

    digitalLibrary lib;
    QSqlDatabase db = lib.db;
    db.transaction();

    try {
        for (const QModelIndex &index : selectedRows) {
            QString username = model->data(model->index(index.row(), 0)).toString();
            QString name = model->data(model->index(index.row(), 1)).toString();

            QSqlQuery query(db);
            query.prepare("DELETE FROM accounts WHERE username = :username AND name = :name");
            query.bindValue(":username", username);
            query.bindValue(":name", name);

            qDebug() << "Tentative de suppression de:" << username << name;

            if (!query.exec()) {
                qDebug() << "Erreur SQL:" << query.lastError().text();
                throw QString("Erreur lors de la suppression de %1 %2: %3")
                    .arg(username, name, query.lastError().text());
            }

            if (query.numRowsAffected() <= 0) {
                qDebug() << "Aucune ligne affectée pour:" << username << name;
                throw QString("Aucun membre trouvé avec le nom %1 %2").arg(username, name);
            }
        }

        if (!db.commit()) {
            throw QString("Erreur lors de la validation des modifications: %1").arg(db.lastError().text());
        }

        // Rafraîchir le modèle
        loadMembers();
        QMessageBox::information(this, "Succès", QString("%1 membre(s) supprimé(s) avec succès").arg(count));

    } catch (const QString &error) {
        db.rollback();
        QMessageBox::critical(this, "Erreur", error);
    }
}
