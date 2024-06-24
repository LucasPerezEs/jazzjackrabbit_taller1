#include "MapList.h"

MapList::MapList(QWidget *parent) : QWidget(parent) {
    init();
}

void MapList::init() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    MapList = new QListWidget(this);

    refreshButton = new QPushButton("Refresh", this);

    layout->addWidget(MapList);
    layout->addWidget(refreshButton);

    connect(refreshButton, &QPushButton::clicked, this, [this]() {
        MapList->clear();
        emit refreshRequested();
    });

    connect(MapList, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
        emit mapSelected(item->text());
    });

}

void MapList::updateMapList(const QStringList &maps) {
    mapList->clear();
    mapList->addItems(maps);
}


MapList::~MapList() {}
