#include "CreateGame.h"

CreateGame::CreateGame(QWidget* parent): QWidget(parent) { init(); }

std::vector<uint32_t> CreateGame::saveCheats() {
    std::vector<uint32_t> cheatList;

    if (inmortalCheckBox->isChecked()) {
        cheatList.insert(cheatList.end(), INMORTAL);
    }

    if (oneShotOneKillCheckBox->isChecked()) {
        cheatList.insert(cheatList.end(), ONE_SHOT_ONE_KILL);
    }

    if (moonGravityCheckBox->isChecked()) {
        cheatList.insert(cheatList.end(), MOON_GRAVITY);
    }

    if (hardEnemiesCheckBox->isChecked()) {
        cheatList.insert(cheatList.end(), HARD_ENEMIES);
    }

    if (extraTimeCheckBox->isChecked()) {
        cheatList.insert(cheatList.end(), EXTRA_TIME);
    }

    return cheatList;
}

void CreateGame::init() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    gameNameLabel = new QLabel("Game Name:", this);
    layout->addWidget(gameNameLabel);
    gameNameInput = new QLineEdit(this);
    layout->addWidget(gameNameInput);


    maxPlayersLabel = new QLabel("Max Players:", this);
    layout->addWidget(maxPlayersLabel);
    maxPlayersInput = new QLineEdit(this);
    layout->addWidget(maxPlayersInput);

    cheatsLabel = new QLabel("Cheats:", this);
    layout->addWidget(cheatsLabel);

    inmortalCheckBox = new QCheckBox("Inmortal players", this);
    layout->addWidget(inmortalCheckBox);

    oneShotOneKillCheckBox = new QCheckBox("One Shot, One Kill", this);
    layout->addWidget(oneShotOneKillCheckBox);

    moonGravityCheckBox = new QCheckBox("Moon gravity", this);
    layout->addWidget(moonGravityCheckBox);

    hardEnemiesCheckBox = new QCheckBox("Hard enemies", this);
    layout->addWidget(hardEnemiesCheckBox);

    extraTimeCheckBox = new QCheckBox("Extra time", this);
    layout->addWidget(extraTimeCheckBox);

    createButton = new QPushButton("Create Game", this);
    layout->addWidget(createButton);

    connect(createButton, &QPushButton::clicked, this, [this]() {
        std::vector<uint32_t> cheatList = saveCheats();
        QString gameName = gameNameInput->text();
        uint32_t maxPlayers = maxPlayersInput->text().toInt();
        emit createGameRequested(gameName, maxPlayers, cheatList);
    });
}

CreateGame::~CreateGame() {}
