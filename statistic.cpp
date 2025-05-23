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

Statistic::Statistic(QSqlDatabase db, QWidget *parent) : QWidget(parent),
    m_db(db),
    popularityChartView(new QChartView),
    quantityChartView(new QChartView),
    statButton(new QPushButton("Afficher les statistiques")),
    bookStatsWindow(nullptr), membersChartView(new QChartView),
    memberStatsWindow(nullptr), chartWindow(nullptr)
{
    membersChartView->setRenderHint(QPainter::Antialiasing);
    setupUI();
    //connect(statButton, &QPushButton::clicked, this, &Statistic::loadAndShowStats);
}

void Statistic::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Cliquez pour voir les statistiques :");
    mainLayout->addWidget(label);
    mainLayout->addWidget(statButton);
    setLayout(mainLayout);
}

void Statistic::updateStats(const QMap<QString, int>& bookPopularity,
                            const QMap<QString, int>& quantityByCategory)
{
    createPopularityChart(bookPopularity);
    createQuantityChart(quantityByCategory);
}
#include <QDialog>
#include <QDialogButtonBox>

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

    // Récupérer les données (comme avant)...
    query.prepare("SELECT role, COUNT(*) FROM accounts GROUP BY role");
    if (!query.exec()) {
        qDebug() << "❌ Erreur requête membres:" << query.lastError();
    } else {
        while (query.next()) {
            membersByType[query.value(0).toString()] = query.value(1).toInt();
        }
    }

    query.prepare("SELECT name, COUNT(bookStatus.Book) FROM books LEFT JOIN bookStatus ON books.ID = bookStatus.Book GROUP BY books.name ORDER BY COUNT(bookStatus.Book) DESC LIMIT 5");
    if (!query.exec()) {
        qDebug() << "❌ Erreur requête popularité:" << query.lastError();
    } else {
        while (query.next()) {
            bookPopularity[query.value(0).toString()] = query.value(1).toInt();
        }
    }

    query.prepare("SELECT genre, SUM(quantity) FROM books GROUP BY genre");
    if (!query.exec()) {
        qDebug() << "❌ Erreur requête catégories:" << query.lastError();
    } else {
        while (query.next()) {
            quantityByCategory[query.value(0).toString()] = query.value(1).toInt();
        }
    }

    createPopularityChart(bookPopularity);
    createQuantityChart(quantityByCategory);
    createMembersChart(membersByType);

    // Création d'un dialog pour afficher tout côte à côte
    QDialog *statsDialog = new QDialog(this);
    statsDialog->setWindowTitle("Statistiques");

    QHBoxLayout *chartsLayout = new QHBoxLayout();

    // Ajouter les graphiques côte à côte
    chartsLayout->addWidget(popularityChartView);
    chartsLayout->addWidget(quantityChartView);
    chartsLayout->addWidget(membersChartView);

    // Bouton retour
    QPushButton *backButton = new QPushButton("Retour à la bibliothèque");
    connect(backButton, &QPushButton::clicked, statsDialog, &QDialog::accept); // Ferme le dialog

    // Layout principal vertical
    QVBoxLayout *mainLayout = new QVBoxLayout(statsDialog);
    mainLayout->addLayout(chartsLayout);
    mainLayout->addWidget(backButton);

    statsDialog->setLayout(mainLayout);
    statsDialog->resize(900, 500);
    statsDialog->exec();  // Modal, bloque l'accès tant que pas fermé
}
void Statistic::createPopularityChart(const QMap<QString, int>& data) {
    QHorizontalBarSeries *series = new QHorizontalBarSeries();
    QBarSet *barSet = new QBarSet("Nombre d'emprunts");

    QStringList categories;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        *barSet << it.value();
        categories << it.key();
    }

    series->append(barSet);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("📊 Top 5 des livres les plus empruntés");
    chart->setTitleBrush(QBrush(QColor("#6A0DAD")));
    chart->setBackgroundBrush(QColor("#fefefe"));

    // Titre
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);

    // Axe vertical = Noms des livres
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    barSet->setColor(QColor("#FF69B4")); // rose pastel

    // Axe horizontal = Nombre d’emprunts
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Nombre d'emprunts");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Légende
    chart->legend()->setVisible(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Appliquer le rendu
    popularityChartView->setRenderHint(QPainter::Antialiasing);
    popularityChartView->setChart(chart);
}



void Statistic::createQuantityChart(const QMap<QString, int>& data) {
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Quantité");
    set->setColor(QColor("#FF69B4"));

    QStringList categories;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        *set << it.value();
        categories << it.key();
    }
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Quantité par catégorie");
    chart->setTitleBrush(QBrush(QColor("#FF69B4")));
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(16);
    chart->setTitleFont(titleFont);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    QFont labelsFont;
    labelsFont.setPointSize(12);
    axisX->setLabelsFont(labelsFont);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsFont(labelsFont);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    quantityChartView->setChart(chart);
}

void Statistic::createMembersChart(const QMap<QString, int>& data) {
    if (data.isEmpty()) {
        qDebug() << "Aucune donnée disponible pour les membres.";
        return;
    }

    QPieSeries *series = new QPieSeries();
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());
        slice->setLabelVisible(true);
        slice->setBrush(QColor::fromHsv(rand() % 360, 255, 200));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des membres par type");
    chart->setTitleBrush(QBrush(QColor("#7A288A")));

    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(16);
    chart->setTitleFont(titleFont);

    membersChartView->setChart(chart);
    membersChartView->setRenderHint(QPainter::Antialiasing);
}

void Statistic::createAnotherChart(const QMap<QString, int>& data) {
    QPieSeries *series = new QPieSeries();
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());
        slice->setBrush(QColor("#FFD700"));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Autre statistique");
    chart->setTitleBrush(QBrush(QColor("#7A288A")));

    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(16);
    chart->setTitleFont(titleFont);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if (!chartWindow) {
        chartWindow = new QWidget();
        chartWindow->setWindowTitle("Fenêtre de statistiques");
        QVBoxLayout *layout = new QVBoxLayout(chartWindow);
        layout->addWidget(popularityChartView);
        layout->addWidget(quantityChartView);
        layout->addWidget(chartView);
        chartWindow->setLayout(layout);
    } else {
        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(chartWindow->layout());
        if (layout) {
            layout->addWidget(chartView);
        }
    }
}
