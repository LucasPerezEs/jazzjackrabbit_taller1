#include "CreateGame.h"

CreateGame::CreateGame(QWidget *parent) : QWidget(parent) {
    init();
}

void CreateGame::init() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    gameNameLabel = new QLabel("Game Name:", this);
    layout->addWidget(gameNameLabel);
    gameNameInput = new QLineEdit(this);
    layout->addWidget(gameNameInput);


    maxPlayersLabel = new QLabel("Max Players:", this);
    layout->addWidget(maxPlayersLabel);
    maxPlayersInput = new QLineEdit(this);
    layout->addWidget(maxPlayersInput);

    createButton = new QPushButton("Create Game", this);
    layout->addWidget(createButton);

    connect(createButton, &QPushButton::clicked, this, [this]() {
        QString gameName = gameNameInput->text();
        uint32_t maxPlayers = maxPlayersInput->text().toInt();
        emit createGameRequested(gameName,maxPlayers);
    });
}

CreateGame::~CreateGame() {}
