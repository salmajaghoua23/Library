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

Statistic::Statistic(QSqlDatabase db, QWidget *parent) : QWidget(parent),
    m_db(db),  // Initialisation de la base de données
    popularityChartView(new QChartView),
    quantityChartView(new QChartView),
    statButton(new QPushButton("Afficher les statistiques")),
    chartWindow(nullptr)
{
    setupUI();
    connect(statButton, &QPushButton::clicked, this, &Statistic::on_statsButton_clicked);
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

void Statistic::createPopularityChart(const QMap<QString, int>& data)
{
    QPieSeries *series = new QPieSeries();
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        series->append(it.key(), it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Popularité des livres");

    popularityChartView->setChart(chart);
}

void Statistic::createQuantityChart(const QMap<QString, int>& data)
{
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Quantité");
    QStringList categories;

    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        *set << it.value();
        categories << it.key();
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Quantité par catégorie");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    quantityChartView->setChart(chart);
}

void Statistic::on_statsButton_clicked()
{
    if (!chartWindow) {
        chartWindow = new QWidget();
        chartWindow->setWindowTitle("Fenêtre de statistiques");
        chartWindow->resize(800, 600);
        QVBoxLayout *layout = new QVBoxLayout(chartWindow);
        layout->addWidget(popularityChartView);
        layout->addWidget(quantityChartView);
        chartWindow->setLayout(layout);
    }

    chartWindow->show();
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

    // 1️⃣ Requête : Popularité des livres (les + empruntés)
    QSqlQuery query(m_db);
    query.prepare("SELECT l.titre, COUNT(e.id) AS emprunts "
                  "FROM livres l LEFT JOIN emprunts e ON l.id = e.livre_id "
                  "GROUP BY l.titre ORDER BY emprunts DESC LIMIT 5");

    if (!query.exec()) {
        qDebug() << "❌ Erreur requête popularité:" << query.lastError();
    } else {
        while (query.next()) {
            bookPopularity[query.value(0).toString()] = query.value(1).toInt();
        }
    }

    // 2️⃣ Requête : Quantité par catégorie
    query.prepare("SELECT categorie, COUNT(*) AS count FROM livres GROUP BY categorie");
    if (!query.exec()) {
        qDebug() << "❌ Erreur requête catégories:" << query.lastError();
    } else {
        while (query.next()) {
            quantityByCategory[query.value(0).toString()] = query.value(1).toInt();
        }
    }

    // 3️⃣ Mettre à jour les graphiques
    updateStats(bookPopularity, quantityByCategory);

    // 4️⃣ Afficher la fenêtre
    if (!chartWindow) {
        chartWindow = new QWidget();
        chartWindow->setWindowTitle("📊 Statistiques");
        QVBoxLayout *layout = new QVBoxLayout(chartWindow);
        layout->addWidget(popularityChartView);
        layout->addWidget(quantityChartView);
    }
    chartWindow->show();
    chartWindow->raise(); // Met la fenêtre au premier plan
}
