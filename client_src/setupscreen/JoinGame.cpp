#include "JoinGame.h"

JoinGame::JoinGame(QWidget *parent) : QWidget(parent) {
    init();
}

void JoinGame::init() {
    elegido = 0;
    QVBoxLayout *layout = new QVBoxLayout(this);

    gameIdInput = new QLineEdit(this);
    joinButton = new QPushButton("Join Game", this);
    jazz = new QPushButton("Jazz", this);
    lori = new QPushButton("Lori", this);
    spaz = new QPushButton("Spaz", this);

    layout->addWidget(jazz);
    layout->addWidget(lori);
    layout->addWidget(spaz);
    layout->addWidget(gameIdInput);
    layout->addWidget(joinButton);
    joinButton->setEnabled(false);

    connect(joinButton, &QPushButton::clicked, this, [this]() {
        QString gameId = gameIdInput->text();
        emit joinGameRequested(gameId, elegido);

    });
    connect(jazz, &QPushButton::clicked, this, [this]() {
        elegido = 0;
        joinButton->setEnabled(true);

    });
    connect(lori, &QPushButton::clicked, this, [this]() {
        elegido = 1;
        joinButton->setEnabled(true);

    });
    connect(spaz, &QPushButton::clicked, this, [this]() {
        elegido = 2;
        joinButton->setEnabled(true);

    });
}

void JoinGame::setGameId(const QString &gameId) {
    int lastSpaceIndex = gameId.lastIndexOf(' ');
    QString gameName = gameId.left(lastSpaceIndex);
    gameIdInput->setText(gameName);
    joinButton->setEnabled(true);
}




JoinGame::~JoinGame() {}
