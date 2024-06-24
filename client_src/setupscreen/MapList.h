#ifndef MAPLIST_H
#define MAPLIST_H

#include <QListWidget>
#include <QPushButton>
#include <QStringList>
#include <QVBoxLayout>
#include <QWidget>


#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QComboBox>
#include <QVBoxLayout>
#include <string>

class MapList: public QWidget {
    Q_OBJECT

public:
    explicit MapList(QWidget* parent = nullptr);
    virtual ~MapList();

    void updateMapList(const QStringList& maps);

signals:
    void refreshRequested(uint32_t& id);
    void mapSelected(const QString &mapName);


private:
    QListWidget* mapList;
    QPushButton* refreshButton;
    QPushButton* joinButton;

    void init();
};

#endif  // MAPLIST_H
