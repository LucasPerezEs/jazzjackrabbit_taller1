#include "MultiplayerMenu.h"

MultiplayerMenu::MultiplayerMenu(QWidget* parent, Client* client):
        QDialog(parent),
        clientNameWidget(new ClientName()),
        createGameWidget(new CreateGame()),
        joinGameWidget(new JoinGame()),
        gameListWidget(new GameList()) {
    exit = 1;
    createGameWidget->setClient(client);
    createGameWidget->init();
    init();
}

void MultiplayerMenu::init() {

    //createGameWidget->setClient(client);
    //createGameWidget->init();

    QVBoxLayout* layout = new QVBoxLayout(this);

    createGameButton = new QPushButton("Create Game", this);
    joinGameButton = new QPushButton("Join", this);
    refreshButton = new QPushButton("Refresh", this);
    createMapButton = new QPushButton("CreatMap", this);
    back = new QPushButton("Return", this);

    // createGameButton->setEnabled(false);
    // refreshButton->setEnabled(false);

    layout->addWidget(createGameButton);
    layout->addWidget(joinGameButton);
    layout->addWidget(createMapButton);
    layout->addWidget(back);
    // layout->addWidget(refreshButton);

    layout->addWidget(clientNameWidget);
    layout->addWidget(createGameWidget);
    layout->addWidget(gameListWidget);
    layout->addWidget(joinGameWidget);

    createGameButton->hide();
    joinGameButton->hide();
    createMapButton->hide();
    refreshButton->hide();
    back->hide();
    createGameWidget->hide();
    gameListWidget->hide();
    joinGameWidget->hide();


    connect(createGameButton, &QPushButton::clicked, this, &MultiplayerMenu::onCreateGameClicked);
    connect(joinGameButton, &QPushButton::clicked, this, &MultiplayerMenu::onJoinGameClicked);
    connect(refreshButton, &QPushButton::clicked, this, &MultiplayerMenu::onRefreshClicked);
    connect(createMapButton, &QPushButton::clicked, this, &MultiplayerMenu::onCreateMapClicked);
    connect(back, &QPushButton::clicked, this, &MultiplayerMenu::onReturnClicked);

    connect(clientNameWidget, &ClientName::ClientNameRequested, this,
            &MultiplayerMenu::ClientNameRequested);
    connect(createGameWidget, &CreateGame::createGameRequested, this,
            &MultiplayerMenu::createGameRequested);
    connect(joinGameWidget, &JoinGame::joinGameRequested, this,
            &MultiplayerMenu::joinGameRequested);
    connect(gameListWidget, &GameList::refreshRequested, this, &MultiplayerMenu::refreshRequested);

    connect(gameListWidget, &GameList::gameSelected, joinGameWidget, &JoinGame::setGameId);

}

void MultiplayerMenu::nameSet() {
    createGameButton->show();
    joinGameButton->show();
    createMapButton->show();

    clientNameWidget->hide();
}

void MultiplayerMenu::onReturnClicked() {
    createGameButton->show();
    joinGameButton->show();
    createMapButton->show();

    back->hide();
    refreshButton->hide();
    createGameWidget->hide();
    joinGameWidget->hide();
    gameListWidget->hide();
}


void MultiplayerMenu::onCreateGameClicked() {
    back->show();
    createGameWidget->show();

    createGameButton->hide();
    joinGameButton->hide();
    createMapButton->hide();
    // joinGameWidget->hide();
    // gameListWidget->hide();
}

void MultiplayerMenu::onJoinGameClicked() {
    back->show();
    // refreshButton->show();
    gameListWidget->show();
    joinGameWidget->show();

    createGameButton->hide();
    joinGameButton->hide();
    createMapButton->hide();
}

void MultiplayerMenu::onRefreshClicked() {
    // createGameWidget->hide();
    // joinGameWidget->hide();
    // gameListWidget->show();
    emit refreshRequested();
}

void MultiplayerMenu::onCreateMapClicked() {
    createGameWidget->hide();
    joinGameWidget->hide();
    gameListWidget->hide();
    emit createMapRequested();
}

void MultiplayerMenu::setClient(Client* client){
    createGameWidget->setClient(client);
}


void MultiplayerMenu::updateGameList(const std::vector<std::string>& gameList) {
    QStringList qStringList;
    for (const auto& str: gameList) {
        qStringList.append(QString::fromStdString(str));
    }
    gameListWidget->updateGameList(qStringList);
}

void MultiplayerMenu::showGameCreatedMessage() {
    QMessageBox::information(this, "Game Created", "The game was created successfully!");
}

void MultiplayerMenu::showGameCreationFailedMessage() {
    QMessageBox::critical(this, "Game Creation Failed", "Failed to create the game.");
}

void MultiplayerMenu::showJoinGameFailedMessage() {
    QMessageBox::critical(this, "Join Game Failed", "Failed to join the game.");
}

void MultiplayerMenu::showSetNameFailedMessage() {
    QMessageBox::critical(this, "Save Name Failed", "Name already in use.");
}

MultiplayerMenu::~MultiplayerMenu() {}
