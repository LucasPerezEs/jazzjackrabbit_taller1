#include "CreateGame.h"

CreateGame::CreateGame(QWidget *parent) :
        QWidget(parent)
{
    init();
}

void CreateGame::init() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    gameNameInput = new QLineEdit(this);
    createButton = new QPushButton("Create Game", this);

    layout->addWidget(gameNameInput);
    layout->addWidget(createButton);

    connect(createButton, &QPushButton::clicked, this, [this]() {
        // Lógica para crear el juego usando el nombre ingresado
        QString gameName = gameNameInput->text();
        // ...
    });
}

CreateGame::~CreateGame() {}
