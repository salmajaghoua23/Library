#include "stats.h"
#include <QProgressDialog>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QtCharts>
#include <QSqlDatabase>
#include <QWidget>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QPieSeries>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QtConcurrent/QtConcurrent>
#include <QSqlQuery>
Stats::Stats(QSqlDatabase db, QWidget *parent)
    : QDialog(parent), m_db(db)
{
    setupUI();
}

void Stats::setupUI()
{
    setWindowTitle("Statistiques");
    resize(900, 700);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Titres
    layout->addWidget(new QLabel("Statistiques de la Bibliothèque", this));

    // Graphiques
    m_popularityChart = new QChartView(this);
    m_quantityChart = new QChartView(this);

    layout->addWidget(new QLabel("Livres populaires", this));
    layout->addWidget(m_popularityChart);

    layout->addWidget(new QLabel("Quantité par catégorie", this));
    layout->addWidget(m_quantityChart);

    // Bouton Fermer
    QPushButton *closeBtn = new QPushButton("Fermer", this);
    connect(closeBtn, &QPushButton::clicked, this, &Stats::close);
    layout->addWidget(closeBtn);
}

void Stats::loadAndShowStats()
{
    QProgressDialog progress("Chargement des données...", "Annuler", 0, 0, this);
    progress.setWindowModality(Qt::WindowModal);

    // Chargement dans un thread séparé
    QFuture<void> future = QtConcurrent::run([this](){
        loadData();

        QMetaObject::invokeMethod(this, [this](){
            createCharts();
        }, Qt::QueuedConnection);
    });

    progress.exec();
    exec(); // Affiche la fenêtre
}

void Stats::loadData()
{
    // Popularité
    QSqlQuery popularityQuery(m_db);
    popularityQuery.exec("SELECT b.name, COUNT(bs.Book) as count "
                         "FROM books b LEFT JOIN bookStatus bs ON b.ID = bs.Book "
                         "GROUP BY b.ID ORDER BY count DESC LIMIT 5");

    while (popularityQuery.next()) {
        m_bookPopularity[popularityQuery.value("name").toString()] =
            popularityQuery.value("count").toInt();
    }

    // Quantités
    QSqlQuery quantityQuery(m_db);
    quantityQuery.exec("SELECT genre, COUNT(*) as count FROM books GROUP BY genre");

    while (quantityQuery.next()) {
        m_quantityByCategory[quantityQuery.value("genre").toString()] =
            quantityQuery.value("count").toInt();
    }
}

void Stats::createCharts()
{
    // Graphique de popularité
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Emprunts");

    QStringList categories;
    for (const auto &[name, count] : m_bookPopularity.asKeyValueRange()) {
        *set << count;
        categories << name;
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Livres les plus populaires");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    m_popularityChart->setChart(chart);

    // Graphique de quantité
    QPieSeries *pieSeries = new QPieSeries();
    for (const auto &[genre, count] : m_quantityByCategory.asKeyValueRange()) {
        pieSeries->append(genre, count);
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("Répartition par catégorie");

    m_quantityChart->setChart(pieChart);
}
