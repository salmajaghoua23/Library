#include "membersList.h"
#include "ui_membersList.h"
#include "addMember.h"
#include "digitalLibrary.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QHeaderView>
#include <QTimer>
#include <QLabel>  // Nouvel include pour QLabel

membersList::membersList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::membersList)
{
    ui->setupUi(this);
    this->setWindowTitle("Members List");
    setupTableView();
}

membersList::~membersList()
{
    delete ui;
}

void membersList::setupTableView()
{
    digitalLibrary lib;
    auto db = lib.db;

    if (!db.isOpen()) {
        QMessageBox::warning(this, "Database Error", "Database is not open!");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT id AS 'ID', username AS 'Username', name AS 'Name', role AS 'Role', password As 'Password' FROM accounts", db);

    if (model->lastError().isValid()) {
        QMessageBox::warning(this, "Database Error", model->lastError().text());
        return;
    }

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setVisible(false);

    QTimer::singleShot(0, this, [this]() {
        ui->tableView->resizeColumnsToContents();
    });

    // Solution 1: Utiliser un QLabel existant dans votre UI (ajoutez-le avec Qt Designer)
    ui->statusLabel->setText(QString("Total members: %1").arg(model->rowCount()));

    // Solution 2: Afficher dans la barre de status de la fenêtre
    //this->statusBar()->showMessage(QString("Total members: %1").arg(model->rowCount()));
}

void membersList::on_value_textEdited(const QString &text)
{
    digitalLibrary lib;
    auto db = lib.db;
    QSqlQueryModel *model = new QSqlQueryModel(this);

    if(text.isEmpty()) {
        model->setQuery("SELECT id AS 'ID', username AS 'Username', name AS 'Name', role AS 'Role' FROM accounts", db);
    } else {
        QString filter = "%" + text + "%";
        QSqlQuery query(db);
        query.prepare("SELECT id AS 'ID', username AS 'Username', name AS 'Name', role AS 'Role' "
                      "FROM accounts WHERE id LIKE :filter OR username LIKE :filter OR name LIKE :filter OR role LIKE :filter");
        query.bindValue(":filter", filter);
        query.exec();
        model->setQuery(query);
    }

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    // Solution 1: Utiliser un QLabel existant dans votre UI
     ui->statusLabel->setText(QString("Members found: %1").arg(model->rowCount()));

    // Solution 2: Afficher dans la barre de status de la fenêtre
    //this->statusBar()->showMessage(QString("Members found: %1").arg(model->rowCount()));
}
