#include "mapviewer.h"
#include <QJsonDocument>
#include <QFile>
#include <QDir>

// MapViewer::MapViewer(QWidget *parent)
//     : QWebEngineView(parent)
// {
//     this->load(QUrl("qrc:/html/map.html"));

// }

// void MapViewer::setLibraryData(const QJsonArray &data)
// {
//     QJsonDocument doc(data);
//     QString jsonString = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
//     QString jsCode = QString("addLibraries('%1');").arg(jsonString.replace("'", "\\'"));

//     connect(this, &QWebEngineView::loadFinished, this, [=](bool ok) {
//         if (ok) {
//             this->page()->runJavaScript(jsCode);
//         }
//     });
// }

