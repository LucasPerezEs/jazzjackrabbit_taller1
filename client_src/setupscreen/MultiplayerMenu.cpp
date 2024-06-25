#include "MultiplayerMenu.h"

#include <QApplication>
#include <QFile>
#include <QFont>
#include <QFontDatabase>

MultiplayerMenu::MultiplayerMenu(QWidget* parent, Client* client):
        QDialog(parent),
        clientNameWidget(new ClientName()),
        createGameWidget(new CreateGame()),
        joinGameWidget(new JoinGame()) {
    int id = QFontDatabase::addApplicationFont("../client_src/assets/ARCADECLASSIC.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);
    this->setFixedSize(800, 600);
    this->setObjectName("multiplayerMenu");
    this->setWindowTitle("Jazz JackRabbit2");

    exit = 1;
    createGameWidget->setClient(client);
    createGameWidget->init();
    init();
}

void MultiplayerMenu::init() {
    QHBoxLayout* layout = new QHBoxLayout(this);

    createGameButton = new QPushButton("Create Game", this);
    createGameButton->setObjectName("createGameButton");
    createGameButton->setFixedSize(150, 30);

    joinGameButton = new QPushButton("Join", this);
    joinGameButton->setObjectName("joinGameButton");
    joinGameButton->setFixedSize(150, 30);

    back = new QPushButton("Return", this);
    back->setObjectName("returnButton");
    back->setFixedSize(150, 30);

    layout->addWidget(createGameButton);
    layout->addWidget(joinGameButton);
    layout->addWidget(clientNameWidget);
    layout->addWidget(createGameWidget);
    layout->addWidget(joinGameWidget);

    layout->setAlignment(Qt::AlignCenter | Qt::AlignBottom);

    createGameButton->hide();
    joinGameButton->hide();
    back->hide();
    createGameWidget->hide();
    joinGameWidget->hide();


    connect(createGameButton, &QPushButton::clicked, this, &MultiplayerMenu::onCreateGameClicked);
    connect(joinGameButton, &QPushButton::clicked, this, &MultiplayerMenu::onJoinGameClicked);
    connect(back, &QPushButton::clicked, this, &MultiplayerMenu::onReturnClicked);

    connect(clientNameWidget, &ClientName::ClientNameRequested, this,
            &MultiplayerMenu::ClientNameRequested);
    connect(createGameWidget, &CreateGame::createGameRequested, this,
            &MultiplayerMenu::createGameRequested);
    connect(joinGameWidget, &JoinGame::joinGameRequested, this,
            &MultiplayerMenu::joinGameRequested);
    connect(joinGameWidget, &JoinGame::refreshRequested, this, &MultiplayerMenu::refreshRequested);

    connect(joinGameWidget, &JoinGame::gameSelected, joinGameWidget, &JoinGame::setGameId);

    loadStyleSheet();
}

void MultiplayerMenu::nameSet() {
    createGameButton->show();
    joinGameButton->show();

    clientNameWidget->hide();
}

void MultiplayerMenu::onReturnClicked() {
    createGameButton->show();
    joinGameButton->show();

    back->hide();
    createGameWidget->hide();
    joinGameWidget->hide();
}


void MultiplayerMenu::onCreateGameClicked() {
    back->show();
    createGameWidget->show();

    createGameButton->hide();
    joinGameButton->hide();
}

void MultiplayerMenu::onJoinGameClicked() {
    back->show();
    joinGameWidget->show();

    createGameButton->hide();
    joinGameButton->hide();
}

void MultiplayerMenu::onRefreshClicked() { emit refreshRequested(); }

void MultiplayerMenu::setClient(Client* client) { createGameWidget->setClient(client); }


void MultiplayerMenu::updateGameList(const std::vector<std::string>& gameList) {
    QStringList qStringList;
    for (const auto& str: gameList) {
        qStringList.append(QString::fromStdString(str));
    }
    joinGameWidget->updateGameList(qStringList);
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

void MultiplayerMenu::loadStyleSheet() {
    QFile file("../client_src/setupscreen/styles.qss");
    if (!file.exists()) {
        qDebug() << "Stylesheet doesn't exist.";
    }

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString stylesheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(stylesheet);
        qDebug() << "Stylesheet applied successfully.";
    } else {
        qDebug() << "Failed to load stylesheet.";
    }
}

MultiplayerMenu::~MultiplayerMenu() {}
