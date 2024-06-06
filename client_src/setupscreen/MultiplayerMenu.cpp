#include "MultiplayerMenu.h"

MultiplayerMenu::MultiplayerMenu(QWidget *parent) :
        QDialog(parent),
        createGameWidget(new CreateGame()),
        joinGameWidget(new JoinGame()),
        gameListWidget(new GameList())
{
    init();
}

void MultiplayerMenu::init() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    createGameButton = new QPushButton("Create Game", this);
    joinGameButton = new QPushButton("Join", this);
    refreshButton = new QPushButton("Refresh", this);

    layout->addWidget(createGameButton);
    layout->addWidget(joinGameButton);
    layout->addWidget(refreshButton);

    layout->addWidget(createGameWidget);
    layout->addWidget(joinGameWidget);
    layout->addWidget(gameListWidget);

    createGameWidget->hide();
    joinGameWidget->hide();
    gameListWidget->hide();

    connect(createGameButton, &QPushButton::clicked, this, &MultiplayerMenu::onCreateGameClicked);
    connect(joinGameButton, &QPushButton::clicked, this, &MultiplayerMenu::onJoinGameClicked);
    connect(refreshButton, &QPushButton::clicked, this, &MultiplayerMenu::onRefreshClicked);

    connect(createGameWidget, &CreateGame::createGameRequested, this, &MultiplayerMenu::createGameRequested);
    connect(joinGameWidget, &JoinGame::joinGameRequested, this, &MultiplayerMenu::joinGameRequested);
    connect(gameListWidget, &GameList::refreshRequested, this, &MultiplayerMenu::refreshRequested);
}

void MultiplayerMenu::onCreateGameClicked() {
    createGameWidget->show();
    joinGameWidget->hide();
    gameListWidget->hide();
}

void MultiplayerMenu::onJoinGameClicked() {
    createGameWidget->hide();
    joinGameWidget->show();
    gameListWidget->hide();
}

void MultiplayerMenu::onRefreshClicked() {
    createGameWidget->hide();
    joinGameWidget->hide();
    gameListWidget->show();
    emit refreshRequested();
}

MultiplayerMenu::~MultiplayerMenu() {}
