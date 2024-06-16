#include "JoinGame.h"

JoinGame::JoinGame(QWidget *parent) : QWidget(parent) {
    init();
}

void JoinGame::init() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    gameIdInput = new QLineEdit(this);
    joinButton = new QPushButton("Join Game", this);

    layout->addWidget(gameIdInput);
    layout->addWidget(joinButton);

    connect(joinButton, &QPushButton::clicked, this, [this]() {
        QString gameId = gameIdInput->text();
        emit joinGameRequested(gameId);

    });
}

JoinGame::~JoinGame() {}
