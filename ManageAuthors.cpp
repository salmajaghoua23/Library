#include "ManageAuthors.h"
#include "ui_ManageAuthors.h"
#include "digitalLibrary.h"
#include <QDebug>
#include <QMessageBox>
#include "ManageAuthors.h"
#include "ui_ManageAuthors.h"
#include <QGraphicsDropShadowEffect>
#include <QLinearGradient>
#include <QStyledItemDelegate>

// Délegate personnalisé pour la table
class AuthorTableDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);

        painter->save();

        // Fond alterné pour les lignes
        if (index.row() % 2 == 0) {
            painter->fillRect(opt.rect, QColor(250, 245, 255));
        } else {
            painter->fillRect(opt.rect, QColor(240, 235, 255));
        }

        // Style pour la sélection
        if (opt.state & QStyle::State_Selected) {
            painter->fillRect(opt.rect, QColor(106, 90, 205, 50));
            painter->setPen(QPen(QColor(106, 90, 205), 2));
            painter->drawRect(opt.rect.adjusted(1, 1, -1, -1));
        }

        painter->restore();
        QStyledItemDelegate::paint(painter, opt, index);
    }
};

ManageAuthors::ManageAuthors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageAuthors)
{
    ui->setupUi(this);

    // Configuration de base
    this->setWindowTitle("Gestion des Auteurs • Bibliothèque Digitale");
    this->setMinimumSize(1000, 700);
    this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f5f0ff, stop:1 #eef2ff);");

    // Conteneur principal
    QFrame *mainContainer = new QFrame(this);
    mainContainer->setGeometry(25, 25, this->width()-50, this->height()-50);
    mainContainer->setStyleSheet(
        "background: white;"
        "color:black;"
        "border-radius: 15px;"
        "border: 1px solid #e0d4ff;"
        );

    // Effet d'ombre
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(mainContainer);
    shadow->setBlurRadius(30);
    shadow->setOffset(0, 5);
    shadow->setColor(QColor(106, 90, 205, 80));
    mainContainer->setGraphicsEffect(shadow);

    // Header avec dégradé
    QFrame *header = new QFrame(mainContainer);
    header->setGeometry(0, 0, mainContainer->width(), 80);
    header->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #6a5acd, stop:1 #9575cd);"
        "border-top-left-radius: 15px;"
        "border-top-right-radius: 15px;"
        );

    // Titre
    QLabel *title = new QLabel("Gestion des Auteurs", header);
    title->setGeometry(30, 15, header->width()-60, 50);
    title->setStyleSheet(
        "color: white;"
        "font-family: 'Segoe UI';"
        "font-size: 24px;"
        "font-weight: bold;"
        );

    // Zone de formulaire
    QFrame *formContainer = new QFrame(mainContainer);
    formContainer->setGeometry(30, 100, 400, mainContainer->height()-180);
    formContainer->setStyleSheet("background: transparent;");

    // Style des champs
    QString fieldStyle =
        "QLineEdit, QTextEdit {"
        "   border: 2px solid #d1c4e9;"
        "   border-radius: 8px;"
        "   padding: 10px 15px;"
        "   font-size: 14px;"
        "   background: #fafaff;"
        "   font-family: 'Segoe UI';"
        "}"
        "QLineEdit:focus, QTextEdit:focus {"
        "   border: 2px solid #7e57c2;"
        "   background: white;"
        "}";

    // Positionnement des champs
    int yPos = 0;
    const int fieldHeight = 45;
    const int margin = 20;

    // ID
    QLabel *idLabel = new QLabel("ID Auteur:", formContainer);
    idLabel->setGeometry(0, yPos, 380, 20);
    idLabel->setStyleSheet("color: #5e4d9b; font-weight: bold;");
    ui->ID->setParent(formContainer);
    ui->ID->setGeometry(0, yPos+25, 380, fieldHeight);
    ui->ID->setStyleSheet(fieldStyle);
    yPos += fieldHeight + margin + 25;

    // Prénom
    QLabel *firstNameLabel = new QLabel("Prénom:", formContainer);
    firstNameLabel->setGeometry(0, yPos, 380, 20);
    firstNameLabel->setStyleSheet("color: #5e4d9b; font-weight: bold;");
    ui->firstName->setParent(formContainer);
    ui->firstName->setGeometry(0, yPos+25, 380, fieldHeight);
    ui->firstName->setStyleSheet(fieldStyle);
    yPos += fieldHeight + margin + 25;

    // Nom
    QLabel *lastNameLabel = new QLabel("Nom:", formContainer);
    lastNameLabel->setGeometry(0, yPos, 380, 20);
    lastNameLabel->setStyleSheet("color: #5e4d9b; font-weight: bold;");
    ui->lastName->setParent(formContainer);
    ui->lastName->setGeometry(0, yPos+25, 380, fieldHeight);
    ui->lastName->setStyleSheet(fieldStyle);
    yPos += fieldHeight + margin + 25;

    // Expertise
    QLabel *expertiseLabel = new QLabel("Domaine d'expertise:", formContainer);
    expertiseLabel->setGeometry(0, yPos, 380, 20);
    expertiseLabel->setStyleSheet("color: #5e4d9b; font-weight: bold;");
    ui->expertise->setParent(formContainer);
    ui->expertise->setGeometry(0, yPos+25, 380, fieldHeight);
    ui->expertise->setStyleSheet(fieldStyle);
    yPos += fieldHeight + margin + 25;

    // À propos
    QLabel *aboutLabel = new QLabel("Biographie:", formContainer);
    aboutLabel->setGeometry(0, yPos, 380, 20);
    aboutLabel->setStyleSheet("color: #5e4d9b; font-weight: bold;");
    ui->about->setParent(formContainer);
    ui->about->setGeometry(0, yPos+25, 380, 120);
    ui->about->setStyleSheet(fieldStyle + "min-height: 120px;");

    // Boutons d'action
    int buttonY = formContainer->height() - 60;
    ui->addButtton->setParent(formContainer);
    ui->addButtton->setGeometry(0, buttonY, 120, 45);
    ui->addButtton->setStyleSheet(
        "QPushButton {"
        "   background: #6a5acd;"
        "   border-radius: 8px;"
        "   color: white;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover { background: #7e57c2; }"
        );
    ui->addButtton->setText("Ajouter");

    ui->editButton->setParent(formContainer);
    ui->editButton->setGeometry(140, buttonY, 120, 45);
    ui->editButton->setStyleSheet(
        "QPushButton {"
        "   background: #9575cd;"
        "   border-radius: 8px;"
        "   color: white;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover { background: #a188d6; }"
        );
    ui->editButton->setText("Modifier");

    ui->deleteButton->setParent(formContainer);
    ui->deleteButton->setGeometry(280, buttonY, 120, 45);
    ui->deleteButton->setStyleSheet(
        "QPushButton {"
        "   background: #d32f2f;"
        "   border-radius: 8px;"
        "   color: white;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover { background: #f44336; }"
        );
    ui->deleteButton->setText("Supprimer");

    // TableView
    ui->authorTableView->setParent(mainContainer);
    ui->authorTableView->setGeometry(450, 100, mainContainer->width()-490, mainContainer->height()-180);
    ui->authorTableView->setStyleSheet(
        "QTableView {"
        "   border: 2px solid #d1c4e9;"
        "   border-radius: 8px;"
        "   background: #fafaff;"
        "   alternate-background-color: #f5f0ff;"
        "   selection-background-color: #b39ddb;"
        "color:black;"
        "}"
        "QHeaderView::section {"
        "   background: #6a5acd;"
        "   color: blue;"
        "   padding: 8px;"
        "   border: none;"
        "}"
        );

    // Appliquer le delegate personnalisé
    ui->authorTableView->setItemDelegate(new AuthorTableDelegate(this));
    ui->authorTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->authorTableView->verticalHeader()->setVisible(false);
    ui->authorTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->authorTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    // Initialisation du modèle
    model = new QSqlQueryModel(this);
    auto db = digitalLibrary::db;

    auto select = QSqlQuery(db);
    QString selectAll = "SELECT * FROM authors";
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from authors";

    model->setQuery(select);
    ui->authorTableView->setModel(model);

    setValidator();
}

// [Les autres méthodes restent inchangées]

ManageAuthors::~ManageAuthors()
{
    delete ui;
    delete  model;
}

void ManageAuthors::on_addButtton_clicked()
{
    //call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    //retrieve content
    QString ID = ui->ID->text();
    QString firstName = ui->firstName->text();
    QString lastName = ui->lastName->text();
    QString expertise = ui->expertise->text();
    QString about = ui->about->toPlainText();

    auto select = QSqlQuery(db);
    QString selectAll = {"SELECT * FROM authors"};
    if(!select.exec(selectAll))
        qDebug() << "Cannot select from authors";

    if((!ID.isEmpty() & !firstName.isEmpty())&(!lastName.isEmpty() & !expertise.isEmpty()) & !about.isEmpty())
    {
        auto search = QSqlQuery(db);
        QString searchIDAuthor = {"SELECT * FROM authors WHERE ID = '"+ID+"'"};
        if(!search.exec(searchIDAuthor))
            qDebug() << "Cannot select from authors";

        int count = 0;
        while(search.next())
            count++;

        if(count >= 1)
        {
            auto query = QSqlQuery(db);
            QString update = {"UPDATE authors SET  firstName = '"+firstName+"', lastName="
                              "'"+lastName+"', expertise='"+expertise+"', about = '"+about+"'"
                              " WHERE ID = '"+ID+"'"};
            if(!query.exec(update))
                qDebug() << "Cannot update authors";

            //Afficher les auteurs dans QTableView
            model->setQuery(select);
            ui->authorTableView->setModel(model);
        }
        else{
            auto query = QSqlQuery(db);
            QString addAuthor = {"INSERT INTO authors (ID, firstName, lastName, expertise,"
                                "about) VALUES ('%1', '%2','%3', '%4', '%5')"};

            if(!query.exec(addAuthor.arg(ID.toInt()).arg(firstName).arg(lastName).arg(expertise).arg(about)))
                qDebug() << "Cannot add authors";

            //Afficher les genres dans QTableView
            model->setQuery(select);
            ui->authorTableView->setModel(model);
        }
    }
    else
       QMessageBox::warning(this, "Empty", "Fields are empty!");
}


void ManageAuthors::on_editButton_clicked()
{
    QModelIndexList selectedRow = ui->authorTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);

        //get the content of each column
        QString ID = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 0)).toString();
        QString firstName = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 1)).toString();
        QString lastName = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 2)).toString();
        QString expertise = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 3)).toString();
        QString about = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 4)).toString();

        //set the ID and the name in te correspondant lienEdit
        ui->ID->setText(ID);
        ui->firstName->setText(firstName);
        ui->lastName->setText(lastName);
        ui->expertise->setText(expertise);
        ui->about->setText(about);
    }
}


void ManageAuthors::on_deleteButton_clicked()
{
    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    QModelIndexList selectedRow = ui->authorTableView->selectionModel()->selectedRows();

    if(!selectedRow.isEmpty())
    {
        QModelIndex row = selectedRow.at(0);

        QString ID = ui->authorTableView->model()->data(ui->authorTableView->model()->index(row.row(), 0)).toString();

        auto select = QSqlQuery(db);
        QString selectAll = {"SELECT * FROM authors"};
        if(!select.exec(selectAll))
            qDebug() << "Cannot select from authors";

        auto deleteQuery = QSqlQuery(db);
        QString deleteGenre = {"DELETE FROM authors WHERE ID= '"+ID+"'"};
        if(!deleteQuery.exec(deleteGenre))
            qDebug() << "Cannot delete from authors";

        model->setQuery(select);
        ui->authorTableView->setModel(model);
    }
}


void ManageAuthors::setValidator()
{
    //Validator for ID
    QRegularExpression ID("[0-9]{1000}");
    QRegularExpressionValidator *valID = new QRegularExpressionValidator(ID, this);
    ui->ID->setValidator(valID);

    //regx for name
    QRegularExpression Name("[a-zA-Z0-9_+-\\\\s]{1000}");
    QRegularExpressionValidator *valName = new QRegularExpressionValidator(Name, this);
    ui->firstName->setValidator(valName);
    ui->lastName->setValidator(valName);
    ui->expertise->setValidator(valName);
}
