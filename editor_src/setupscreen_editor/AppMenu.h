
#ifndef APPMENU_H
#define APPMENU_H

#include <QDialog>
#include <QPushButton>
#include <QApplication>
#include <QVBoxLayout>
#include "CreateMap.h"
#include "ModifyMap.h"

class AppMenu : public QDialog {
    Q_OBJECT

public:
    explicit AppMenu(QWidget* parent = nullptr);
    ~AppMenu();

private:
    void init();

signals:
    void createMapRequested(const QString& mapName, const int& widthMap, const int& heightMap);
    void modifyMapRequested(const QString& mapName);

private slots:
    void onCreateMapClicked();
    void OnModifyMapClicked();
    void onReturnClicked();

private:
    QPushButton* createMapButton;
    QPushButton* modifyMapButton;
    QPushButton* back;

    CreateMap* createMapWidget;
    ModifyMap* modifyMapWidget;

};

#endif // APPMENU_H

