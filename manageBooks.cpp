#include "manageBooks.h"
#include "ui_manageBooks.h"
#include "digitalLibrary.h"
#include "addBook.h"
#include "editBook.h"
#include <QMessageBox>
#include <QDebug>
manageBooks::manageBooks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manageBooks)
{
    ui->setupUi(this);

    // Style général pastel/violet moderne appliqué à tous les widgets
    this->setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #fbeffb, stop:1 #a18cd1);
        }
        QLabel {
            color: #7c3aed;
            font-size: 18px;
            font-weight: bold;
            background: transparent;
            border: none;
        }
        QLineEdit {
            background: #fff;
            border: 2px solid #d291bc;
            border-radius: 10px;
            padding: 10px 16px;
            font-size: 16px;
            color: #7c3aed;
            font-weight: 600;
        }
        QLineEdit:focus {
            border: 2px solid #a18cd1;
            background: #fff0f6;
            color: #a21caf;
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #fbc2eb, stop:1 #a18cd1);
            color: #fff;
            border: none;
            border-radius: 15px;
            padding: 10px 24px;
            font-size: 16px;
            font-weight: bold;
            margin: 0 8px;
            min-width: 100px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #ede7f6, stop:1 #a18cd1);
            color: #7c3aed;
        }
        QTableView {
            background: #fbeffb;
            border: 1px solid #d291bc;
            border-radius: 10px;
            font-size: 14px;
            color: #7c3aed;
            gridline-color: #fbc2eb;
            alternate-background-color: #fbc2eb;
            selection-background-color: #a18cd1;
            selection-color: #fff;
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
    )");

    // Ajoute un bouton de retour en haut à gauche (emoji ←)
    QPushButton *btnRetour = new QPushButton("← Retour", this);
    btnRetour->setStyleSheet(
        "QPushButton {"
        " background: transparent;"
        " color: #a18cd1;"
        " font-size: 18px;"
        " font-weight: bold;"
        " border: none;"
        " padding: 6px 18px;"
        " border-radius: 10px;"
        " min-width: 90px;"
        "}"
        "QPushButton:hover {"
        " background: #ede7f6;"
        " color: #7c3aed;"
        "}"
        );
    btnRetour->setCursor(Qt::PointingHandCursor);

    // Place le bouton de retour dans le layout principal (horizontalLayout_6)
    if (QHBoxLayout *mainLayout = qobject_cast<QHBoxLayout*>(this->layout())) {
        mainLayout->insertWidget(0, btnRetour, 0, Qt::AlignLeft | Qt::AlignTop);
    } else {
        this->layout()->addWidget(btnRetour);
    }
    connect(btnRetour, &QPushButton::clicked, this, &manageBooks::close);

    // --- Le reste de ton code (modèle, validators, etc.) ---
    digitalLibrary lib;
    auto db = lib.db;
    model = new QSqlQueryModel;

    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM genres"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from genres";
    model->setQuery(select);
    ui->genreTableView->setModel(model);

    //Validator for ID
    QRegularExpression ID("[0-9]{1000}");
    QRegularExpressionValidator *valID = new QRegularExpressionValidator(ID, this);
    ui->ID->setValidator(valID);

    //Validator for name
    QRegularExpression Name("^[A-Za-z][A-Za-z_-]{7,29}$");
    QRegularExpressionValidator *valName = new QRegularExpressionValidator(Name, this);
    ui->Name->setValidator(valName);
}
manageBooks::~manageBooks()
{
    delete ui;
    delete model;
}

void manageBooks::on_add_clicked()
{
    //retrieve content
    QString ID = ui->ID->text();
    QString name = ui->Name->text();

    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //define query
    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM genres"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from genres";

    //insert the new genre in the db genres table, otherwise update it
    if(!ID.isEmpty() & !name.isEmpty())
    {
        auto search = QSqlQuery(db);
        QString searchIDName = {"SELECT * FROM genres WHERE ID = '"+ID+"'"};
        if(!search.exec(searchIDName))
            qDebug() << "Cannot select from genres";
        int count = 0;
        while(search.next())
            count++;
        if(count >= 1)
        {
            auto query = QSqlQuery(db);
            QString update = {"UPDATE genres SET  name = '"+name+"'"
                              "WHERE ID = '"+ID+"'"};
            if(!query.exec(update))
                qDebug() << "Cannot select from genres";

            //Afficher les genres dans QTableView
            model->setQuery(select);
            ui->genreTableView->setModel(model);
        }
        else{
            auto query = QSqlQuery(db);
            QString addGenre = {"INSERT INTO genres (ID, name) VALUES ('%1', '%2')"};

            if(!query.exec(addGenre.arg(ID.toInt()).arg(name)))
                qDebug() << "Cannot add genre";
            else
            {
                QMessageBox::information(this, "SUCCESS", "Genre added successfully");
            }

            //Afficher les genres dans QTableView
            model->setQuery(select);
            ui->genreTableView->setModel(model);
        }
    }
    else
       QMessageBox::warning(this, "Empty", "Fields are empty!");
}


void manageBooks::on_edit_clicked()
{
    QModelIndexList selectedRow = ui->genreTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);

        //get the content of each column
        QString ID = ui->genreTableView->model()->data(ui->genreTableView->model()->index(row.row(), 0)).toString();
        QString name = ui->genreTableView->model()->data(ui->genreTableView->model()->index(row.row(), 1)).toString();

        //set the ID and the name in te correspondant lienEdit
        ui->ID->setText(ID);
        ui->Name->setText(name);
    }
}


void manageBooks::on_deleteButton_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //to update the value of genres (QcomboBox)
    addBook book;
    editBook editBook;

    QModelIndexList selectedRow = ui->genreTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);
        QString name = ui->genreTableView->model()->data(ui->genreTableView->model()->index(row.row(), 1)).toString();

        auto select = QSqlQuery(db);
        QString selectAll = {"SELECT * FROM genres"};
        if(!select.exec(selectAll))
            qDebug() << "Cannot select from genres";

        auto deleteQuery = QSqlQuery(db);
        QString deleteGenre = {"DELETE FROM genres WHERE name= '"+name+"'"};
        if(!deleteQuery.exec(deleteGenre))
            qDebug() << "Cannot delete from genres";

        model->setQuery(select);
        ui->genreTableView->setModel(model);
    }
}

