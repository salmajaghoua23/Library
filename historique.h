#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QDialog>
#include <QTableWidget>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QGroupBox>
#include <QScrollArea>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

//QT_CHARTS_USE_NAMESPACE

    class Historique : public QDialog
{
    Q_OBJECT

public:
    explicit Historique(QWidget *parent = nullptr);
    ~Historique();

    void enregistrerReservation(const QString& livre, const QString& utilisateur);

private:
    void setupReservationsTable();
    void chargerDonnees();
    void chargerConnexions();
    void chargerReservations();
    void chargerStatsConnexions();
    void chargerStatsReservations();
    void appliquerAnimation(QWidget *widget);

    QChartView* createConnexionsChart();
    QChartView* createReservationsChart();
    QMap<QString, int> getConnexionsDataLast7Days();
    QMap<QString, int> getReservationsDataLast7Days();
    void initReservationFile();

    // Widgets
    QLabel *labelConnexions;
    QTableWidget *tableReservations;
};

#endif // HISTORIQUE_H
