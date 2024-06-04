#include "JoinGame.h"

JoinGame::JoinGame(QWidget *parent) :
        QWidget(parent)
{
    init();
}

void JoinGame::init() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    gameIdInput = new QLineEdit(this);
    joinButton = new QPushButton("Join Game", this);

    layout->addWidget(gameIdInput);
    layout->addWidget(joinButton);

    connect(joinButton, &QPushButton::clicked, this, [this]() {
        // Lógica para unirse al juego usando el ID ingresado
        QString gameId = gameIdInput->text();
        // ...
    });
}

JoinGame::~JoinGame() {}
