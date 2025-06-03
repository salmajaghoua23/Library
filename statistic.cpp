#include "statistic.h"
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "statistic.h"
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>

Statistic::Statistic(QSqlDatabase db, QWidget *parent) : QWidget(parent),
    m_db(db),
    popularityChartView(new QChartView),
    quantityChartView(new QChartView),
    statButton(new QPushButton("📊 Afficher les statistiques")),
    bookStatsWindow(nullptr), membersChartView(new QChartView),
    memberStatsWindow(nullptr), chartWindow(nullptr)
{
    membersChartView->setRenderHint(QPainter::Antialiasing);
    setupUI();
}

void Statistic::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // Style du bouton principal
    statButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #6A0DAD;"
        "   color: white;"
        "   border-radius: 15px;"
        "   padding: 12px 24px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7A288A;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #4B0082;"
        "}"
        );

    // Ajout d'un effet d'ombre
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(15);
    shadowEffect->setXOffset(3);
    shadowEffect->setYOffset(3);
    shadowEffect->setColor(QColor(0, 0, 0, 100));
    statButton->setGraphicsEffect(shadowEffect);

    QLabel *label = new QLabel("📈 Visualisation des données de la bibliothèque");
    label->setStyleSheet("font-size: 18px; color: #333; font-weight: bold;");
    label->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(label);
    mainLayout->addWidget(statButton, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    setLayout(mainLayout);
    setStyleSheet("background-color: #f8f9fa;");
}
void Statistic::loadAndShowStats() {
    if (!m_db.isOpen()) {
        if (!m_db.open()) {
            qDebug() << "❌ Erreur de connexion DB:" << m_db.lastError();
            return;
        }
    }

    QMap<QString, int> bookPopularity;
    QMap<QString, int> quantityByCategory;
    QMap<QString, int> membersByType;
    QSqlQuery query(m_db);

    // Répartition des membres par rôle
    query.prepare("SELECT role, COUNT(*) FROM accounts GROUP BY role");
    if (!query.exec()) {
        qDebug() << "❌ Erreur requête membres:" << query.lastError();
    } else {
        while (query.next()) {
            membersByType[query.value(0).toString()] = query.value(1).toInt();
        }
    }

    // Livres les plus empruntés (depuis la table emprunt)
    query.prepare("SELECT books.name, COUNT(*) AS borrow_count "
                  "FROM emprunt "
                  "JOIN books ON emprunt.id_book = books.ID "
                  "GROUP BY books.name "
                  "ORDER BY borrow_count DESC LIMIT 5");
    if (!query.exec()) {
        qDebug() << "❌ Erreur requête popularité (emprunt):" << query.lastError();
    } else {
        while (query.next()) {
            bookPopularity[query.value(0).toString()] = query.value(1).toInt();
        }
    }

    // Quantité de livres par genre
    query.prepare("SELECT genre, SUM(quantity) FROM books GROUP BY genre");
    if (!query.exec()) {
        qDebug() << "❌ Erreur requête quantité par genre:" << query.lastError();
    } else {
        while (query.next()) {
            quantityByCategory[query.value(0).toString()] = query.value(1).toInt();
        }
    }

    // Génération des graphiques
    createPopularityChart(bookPopularity);
    createQuantityChart(quantityByCategory);
    createMembersChart(membersByType);

    // Fenêtre des statistiques
    QDialog *statsDialog = new QDialog(this);
    statsDialog->setWindowTitle("📊 Tableau de bord - Statistiques");
    statsDialog->setStyleSheet("background-color: #f8f9fa;");

    QVBoxLayout *mainLayout = new QVBoxLayout(statsDialog);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    QLabel *titleLabel = new QLabel("Statistiques de la Bibliothèque");
    titleLabel->setStyleSheet("font-size: 22px; color: #6A0DAD; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QHBoxLayout *chartsLayout = new QHBoxLayout();
    chartsLayout->setSpacing(20);

    popularityChartView->setMinimumSize(300, 300);
    quantityChartView->setMinimumSize(300, 300);
    membersChartView->setMinimumSize(300, 300);

    QGraphicsDropShadowEffect *chartShadow = new QGraphicsDropShadowEffect;
    chartShadow->setBlurRadius(20);
    chartShadow->setXOffset(5);
    chartShadow->setYOffset(5);
    chartShadow->setColor(QColor(0, 0, 0, 60));

    popularityChartView->setGraphicsEffect(chartShadow);
    quantityChartView->setGraphicsEffect(chartShadow);
    membersChartView->setGraphicsEffect(chartShadow);

    chartsLayout->addWidget(popularityChartView);
    chartsLayout->addWidget(quantityChartView);
    chartsLayout->addWidget(membersChartView);

    mainLayout->addLayout(chartsLayout);

    QPushButton *backButton = new QPushButton("← Retour à la bibliothèque");
    backButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #6A0DAD;"
        "   color: white;"
        "   border-radius: 10px;"
        "   padding: 10px 20px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   min-width: 200px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #7A288A;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #4B0082;"
        "}"
        );

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(backButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    connect(backButton, &QPushButton::clicked, statsDialog, &QDialog::accept);

    statsDialog->setLayout(mainLayout);
    statsDialog->resize(1200, 600);
    statsDialog->exec();
}



void Statistic::createMembersChart(const QMap<QString, int>& data) {
    if (data.isEmpty()) {
        qDebug() << "Aucune donnée disponible pour les membres.";
        return;
    }

    QPieSeries *series = new QPieSeries();
    series->setPieSize(0.7);

    // Couleurs pastel
    QList<QColor> colors = {
        QColor("#6A0DAD"), QColor("#FF69B4"), QColor("#32CD32"),
        QColor("#FFD700"), QColor("#1E90FF"), QColor("#FF6347")
    };

    int colorIndex = 0;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());
        slice->setColor(colors[colorIndex % colors.size()]);
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);
        slice->setLabelArmLengthFactor(0.1);
        slice->setLabelFont(QFont("Arial", 9));
        colorIndex++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des membres");
    chart->setTitleBrush(QBrush(QColor("#1E90FF")));
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setBackgroundRoundness(10);

    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("Arial", 9));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setMargins(QMargins(5, 5, 5, 5));

    membersChartView->setChart(chart);
    membersChartView->setRenderHint(QPainter::Antialiasing);
    membersChartView->setStyleSheet("border-radius: 10px; background: white;");
}
void Statistic::createPopularityChart(const QMap<QString, int>& data) {
    if (data.isEmpty()) {
        qDebug() << "Aucune donnée disponible pour la popularité des livres.";
        return;
    }

    QPieSeries *series = new QPieSeries();
    series->setPieSize(0.7);

    // Couleurs pastel harmonieuses
    QList<QColor> colors = {
        QColor("#6A0DAD"), QColor("#9B59B6"), QColor("#8E44AD"),
        QColor("#7D3C98"), QColor("#6C3483")
    };

    int colorIndex = 0;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        QString label = QString("%1 (%2)").arg(it.key()).arg(it.value());
        QPieSlice *slice = series->append(label, it.value());
        slice->setColor(colors[colorIndex % colors.size()]);
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);
        slice->setLabelArmLengthFactor(0.1);
        slice->setLabelFont(QFont("Arial", 9));
        colorIndex++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Popularité des livres (Top 5)");
    chart->setTitleBrush(QBrush(QColor("#6A0DAD")));
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setBackgroundRoundness(10);

    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("Arial", 9));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setMargins(QMargins(5, 5, 5, 5));

    popularityChartView->setChart(chart);
    popularityChartView->setRenderHint(QPainter::Antialiasing);
    popularityChartView->setStyleSheet("border-radius: 10px; background: white;");
}

void Statistic::createQuantityChart(const QMap<QString, int>& data) {
    if (data.isEmpty()) {
        qDebug() << "Aucune donnée disponible pour les quantités par catégorie.";
        return;
    }

    QPieSeries *series = new QPieSeries();
    series->setPieSize(0.7);

    // Couleurs pastel différentes du premier graphique
    QList<QColor> colors = {
        QColor("#FF69B4"), QColor("#FF8E9E"), QColor("#FFA07A"),
        QColor("#FFB6C1"), QColor("#FFC0CB")
    };

    int colorIndex = 0;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        QString label = QString("%1 (%2)").arg(it.key()).arg(it.value());
        QPieSlice *slice = series->append(label, it.value());
        slice->setColor(colors[colorIndex % colors.size()]);
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);
        slice->setLabelArmLengthFactor(0.1);
        slice->setLabelFont(QFont("Arial", 9));
        colorIndex++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Quantité par catégorie");
    chart->setTitleBrush(QBrush(QColor("#FF69B4")));
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setBackgroundRoundness(10);

    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("Arial", 9));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setMargins(QMargins(5, 5, 5, 5));

    quantityChartView->setChart(chart);
    quantityChartView->setRenderHint(QPainter::Antialiasing);
    quantityChartView->setStyleSheet("border-radius: 10px; background: white;");
}
