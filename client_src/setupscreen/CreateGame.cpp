#include "CreateGame.h"

CreateGame::CreateGame(QWidget* parent): QWidget(parent) { init(); }

std::vector<uint32_t> CreateGame::saveCheats() {
    std::vector<uint32_t> cheatVector;
    QList<QListWidgetItem*> selectedItems = cheatList->selectedItems();
    QString selectedCheat;

    for (QListWidgetItem* item: selectedItems) {
        selectedCheat = item->text();

        if (selectedCheat == "Inmortal players") {
            cheatVector.insert(cheatVector.end(), INMORTAL);
        } else if (selectedCheat == "One Shot One Kill") {
            cheatVector.insert(cheatVector.end(), ONE_SHOT_ONE_KILL);
        } else if (selectedCheat == "Moon Gravity") {
            cheatVector.insert(cheatVector.end(), MOON_GRAVITY);
        } else if (selectedCheat == "Hard Enemies") {
            cheatVector.insert(cheatVector.end(), HARD_ENEMIES);
        } else if (selectedCheat == "Extra Time") {
            cheatVector.insert(cheatVector.end(), EXTRA_TIME);
        }
    }

    return cheatVector;
}

void CreateGame::init() {
    QGridLayout* gridLayout = new QGridLayout(this);

    gameNameInput = new QLineEdit(this);
    gameNameInput->setFixedSize(160, 25);
    gameNameInput->setPlaceholderText("Insert game name:");
    gameNameInput->setObjectName("gameNameInput");

    // SeleccionarMapa
    std::string rutaCarpeta = "../server_src/maps";  // El nombre deberia pedirlo por socket.
    std::vector<std::string> listaElementos = obtenerElementosEnCarpeta(rutaCarpeta);
    QStringList gameOptions;
    gameOptions << " ";
    for (const auto& elemento: listaElementos) {
        if (elemento.find("spawn") == std::string::npos) {
            gameOptions << QString::fromStdString(elemento);
        }
    }
    mapComboBox = new QComboBox(this);
    mapComboBox->setFixedSize(160, 25);
    mapComboBox->setEditable(true);
    mapComboBox->lineEdit()->setPlaceholderText("Select map:");
    mapComboBox->addItems(gameOptions);
    mapComboBox->setObjectName("mapComboBox");


    maxPlayersInput = new QLineEdit(this);
    maxPlayersInput->setFixedSize(160, 25);
    maxPlayersInput->setPlaceholderText("Insert max players:");
    maxPlayersInput->setObjectName("maxPlayersInput");

    cheatList = new QListWidget(this);
    cheatList->addItems({"Inmortal players", "One Shot One Kill", "Moon Gravity", "Hard Enemies",
                         "Extra Time"});
    cheatList->setSelectionMode(QAbstractItemView::MultiSelection);
    cheatList->setFixedSize(140, 80);
    cheatList->setObjectName("cheatList");


    createButton = new QPushButton("Create Game", this);
    createButton->setFixedSize(100, 30);
    createButton->setObjectName("sendCreateGameButton");


    gridLayout->addWidget(gameNameInput, 0, 0);
    gridLayout->addWidget(mapComboBox, 1, 0);
    gridLayout->addWidget(maxPlayersInput, 2, 0);

    gridLayout->addWidget(cheatList, 0, 1, 3, 1);

    gridLayout->addWidget(createButton, 0, 2, 3, 1);

    gridLayout->setSpacing(20);
    gridLayout->setVerticalSpacing(2);
    gridLayout->setAlignment(Qt::AlignBottom);
    gridLayout->setAlignment(Qt::AlignHCenter);

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
        for (const auto& archivo: std::filesystem::directory_iterator(ruta)) {
            // cppcheck-suppress useStlAlgorithm
            elementos.push_back(archivo.path().filename().string());
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error al leer la carpeta: " << e.what() << std::endl;
    }

    return elementos;
}

CreateGame::~CreateGame() {}
