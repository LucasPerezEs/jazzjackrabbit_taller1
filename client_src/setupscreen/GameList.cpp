#include "GameList.h"

GameList::GameList(QWidget *parent) : QWidget(parent) {
    init();
}

void GameList::init() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    gameList = new QListWidget(this);
    //joinButton = new QPushButton("Join", this);
    refreshButton = new QPushButton("Refresh", this);

    layout->addWidget(gameList);
    //layout->addWidget(joinButton);
    layout->addWidget(refreshButton);

    connect(refreshButton, &QPushButton::clicked, this, [this]() {
        emit refreshRequested();
    });

    connect(gameList, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
        emit gameSelected(item->text());
    });

}

void GameList::updateGameList(const QStringList &games) {
    gameList->clear();
    gameList->addItems(games);
}


GameList::~GameList() {}
