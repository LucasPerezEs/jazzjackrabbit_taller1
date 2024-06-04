#include "GameList.h"

GameList::GameList(QWidget *parent) :
        QWidget(parent)
{
    init();
}

void GameList::init() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    gameList = new QListWidget(this);
    refreshButton = new QPushButton("Refresh", this);

    layout->addWidget(gameList);
    layout->addWidget(refreshButton);

    connect(refreshButton, &QPushButton::clicked, this, [this]() {
        // Lógica para actualizar la lista de juegos
        // ...
    });
}

void GameList::updateGameList(const QStringList &games) {
    gameList->clear();
    gameList->addItems(games);
}

GameList::~GameList() {}
