#include "JoinGame.h"

JoinGame::JoinGame(QWidget* parent): QWidget(parent) { init(); }

void JoinGame::init() {
    elegido = 0;

    QGridLayout* gridLayout = new QGridLayout(this);


    joinButton = new QPushButton("Join Game", this);
    joinButton->setFixedSize(100, 30);
    joinButton->setObjectName("sendJoinGameButton");

    jazz = new QPushButton("Jazz", this);
    jazz->setFixedSize(100, 30);
    jazz->setObjectName("jazzButton");

    lori = new QPushButton("Lori", this);
    lori->setFixedSize(100, 30);
    lori->setObjectName("loriButton");

    spaz = new QPushButton("Spaz", this);
    spaz->setFixedSize(100, 30);
    spaz->setObjectName("spazButton");

    gameList = new QListWidget(this);
    gameList->setFixedSize(200, 30);
    gameList->setObjectName("gameListButton");

    refreshButton = new QPushButton("Refresh", this);
    refreshButton->setFixedSize(200, 30);
    refreshButton->setObjectName("refreshGamesButton");

    gridLayout->addWidget(gameList, 0, 0, 2, 1);
    gridLayout->addWidget(refreshButton, 1, 0, 3, 1);

    gridLayout->addWidget(jazz, 0, 1);
    gridLayout->addWidget(lori, 1, 1);
    gridLayout->addWidget(spaz, 2, 1);

    gridLayout->addWidget(joinButton, 0, 2, 3, 1);

    gridLayout->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    joinButton->setEnabled(false);

    connect(joinButton, &QPushButton::clicked, this, [this]() {
        emit joinGameRequested(elegidoGameId,
                               elegido);  // Emitir la señal con el ID de juego elegido.
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

    connect(refreshButton, &QPushButton::clicked, this, [this]() {
        gameList->clear();
        emit refreshRequested();
    });

    connect(gameList, &QListWidget::itemClicked, this,
            [this](QListWidgetItem* item) { emit gameSelected(item->text()); });
}

void JoinGame::setGameId(const QString& gameId) {
    int lastSpaceIndex = gameId.lastIndexOf(' ');
    QString gameName = gameId.left(lastSpaceIndex);
    elegidoGameId = gameName;
    joinButton->setEnabled(true);
}

void JoinGame::updateGameList(const QStringList& games) {
    gameList->clear();
    gameList->addItems(games);
}


JoinGame::~JoinGame() {}
