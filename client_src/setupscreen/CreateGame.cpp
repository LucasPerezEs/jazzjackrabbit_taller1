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

    //SeleccionarMapa
    mapNameLabel = new QLabel("Map Selected:", this);
    std::string rutaCarpeta = "../server_src/maps"; //El nombre deberia pedirlo por socket.
    std::vector<std::string> listaElementos = obtenerElementosEnCarpeta(rutaCarpeta);
    QStringList gameOptions;
    for (const auto& elemento : listaElementos) {
        if (elemento.find("spawn") == std::string::npos) {
            gameOptions << QString::fromStdString(elemento); 
        }
    }
    layout->addWidget(mapNameLabel);
    mapComboBox = new QComboBox(this);
    mapComboBox->addItems(gameOptions);
    layout->addWidget(mapComboBox);


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
        QString selectedMap = mapComboBox->currentText();
        uint32_t maxPlayers = maxPlayersInput->text().toInt();
        emit createGameRequested(gameName, selectedMap.toStdString(), maxPlayers, cheatList);
    });
}

std::vector<std::string> CreateGame::obtenerElementosEnCarpeta(const std::string& ruta) {
    std::vector<std::string> elementos;

    try {
        for (const auto& archivo : std::filesystem::directory_iterator(ruta)) {
            elementos.push_back(archivo.path().filename().string());
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error al leer la carpeta: " << e.what() << std::endl;
    }

    return elementos;
}

CreateGame::~CreateGame() {}
