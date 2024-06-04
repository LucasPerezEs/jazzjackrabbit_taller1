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

    connect(createGameButton, &QPushButton::clicked, this, &MultiplayerMenu::onCreateGameClicked);
    connect(joinGameButton, &QPushButton::clicked, this, &MultiplayerMenu::onJoinGameClicked);
    connect(refreshButton, &QPushButton::clicked, this, &MultiplayerMenu::onRefreshClicked);
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
    QStringList games = {"Game 1", "Game 2", "Game 3"}; // Esta es una lista de ejemplo
    gameListWidget->updateGameList(games);
}

MultiplayerMenu::~MultiplayerMenu() {}
