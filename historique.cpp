#include "historique.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QLabel>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

Historique::Historique(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Historique de l'utilisateur");
    resize(600, 400);

    QVBoxLayout *layout = new QVBoxLayout(this);

    labelConnexions = new QLabel(this);

    tableReservations = new QTableWidget(this);
    labelConnexions->setStyleSheet("font-size: 18px; font-weight: bold; color: darkblue;");
    labelConnexions->setAlignment(Qt::AlignCenter);

    tableReservations->setColumnCount(2);
    tableReservations->setHorizontalHeaderLabels(QStringList() << "Date" << "Livre");
    tableReservations->horizontalHeader()->setStretchLastSection(true);
    tableReservations->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableReservations->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Appliquer un style pour rendre les dates en violet
    tableReservations->setStyleSheet("QTableWidget { font-size: 14px; color: #8A2BE2; }");
    tableReservations->setAlternatingRowColors(true);

    layout->addWidget(labelConnexions);
    layout->addWidget(tableReservations);

    chargerConnexions();
    chargerReservations();
}
Historique::~Historique()
{
    // Libérer les ressources si nécessaire
}
void Historique::chargerReservations() {
    QFile file("historique_reservations.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QVector<QStringList> lignes;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" - ");
        if (parts.size() == 2) {
            lignes.append(parts);
        }
    }

    // Trier les lignes par date décroissante
    std::sort(lignes.begin(), lignes.end(), [](const QStringList &a, const QStringList &b) {
        return QDateTime::fromString(a[0], "yyyy-MM-dd HH:mm:ss") > QDateTime::fromString(b[0], "yyyy-MM-dd HH:mm:ss");
    });

    // Réinitialiser et configurer le tableau
    tableReservations->setRowCount(lignes.size());
    tableReservations->setColumnCount(2);
    tableReservations->setHorizontalHeaderLabels(QStringList() << "Date" << "Livre");

    for (int i = 0; i < lignes.size(); ++i) {
        QTableWidgetItem *dateItem = new QTableWidgetItem(lignes[i][0]);
        QTableWidgetItem *titleItem = new QTableWidgetItem(lignes[i][1]);

        // Style de la date (violet + gras)
        dateItem->setForeground(QBrush(QColor("#8A2BE2")));  // Violet
        dateItem->setFont(QFont("Arial", 10, QFont::Bold));
        dateItem->setTextAlignment(Qt::AlignCenter);

        // Style du titre du livre (bleu foncé)
        titleItem->setForeground(QBrush(QColor("#1A237E")));  // Bleu foncé
        titleItem->setFont(QFont("Arial", 10));
        titleItem->setTextAlignment(Qt::AlignCenter);

        tableReservations->setItem(i, 0, dateItem);
        tableReservations->setItem(i, 1, titleItem);
    }

    // Ajuster la hauteur et la taille automatique
    tableReservations->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableReservations->verticalHeader()->setDefaultSectionSize(35);  // Hauteur des lignes

    // Optionnel : retirer la grille pour un look plus soft
    tableReservations->setShowGrid(false);
    tableReservations->setStyleSheet("QTableWidget { background-color: #F3E5F5; border: 1px solid #D1C4E9; }");

    file.close();
}

void Historique::chargerConnexions() {
    QFile file("historique_connexions.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        labelConnexions->setText("❌ Impossible de charger les connexions.");
        return;
    }

    QTextStream in(&file);
    int nbConnexions = 0;
    QDateTime maintenant = QDateTime::currentDateTime();
    QDateTime ilYAA7Jours = maintenant.addDays(-7);

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QDateTime dateConnexion = QDateTime::fromString(ligne, "yyyy-MM-dd HH:mm:ss");
        if (dateConnexion.isValid() && dateConnexion > ilYAA7Jours) {
            nbConnexions++;
        }
    }

    QString styledText = QString(
                             "<div style='"
                             "background-color: #F0F0F0; "
                             "border: 2px solid #CCCCCC; "
                             "border-radius: 12px; "
                             "padding: 15px; "
                             "font-size: 16px; "
                             "color: #333333;'>"
                             "<b style='font-size: 18px; color: #0066CC;'>📊 Connexions récentes</b><br>"
                             "Nombre de connexions cette semaine : <b>%1</b>"
                             "</div>"
                             ).arg(nbConnexions);

    labelConnexions->setText(styledText);
    labelConnexions->setTextFormat(Qt::RichText);
    labelConnexions->setAlignment(Qt::AlignCenter);
    appliquerAnimation(labelConnexions);

    file.close();
}
void Historique::appliquerAnimation(QWidget *widget) {
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(opacityEffect);

    QPropertyAnimation *animation = new QPropertyAnimation(opacityEffect, "opacity");
    animation->setDuration(1000);  // Durée en ms
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
