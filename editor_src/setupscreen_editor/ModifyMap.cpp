
#include "ModifyMap.h"

ModifyMap::ModifyMap(QWidget* parent): QWidget(parent) {

    setWindowTitle("Modify Map");

    QVBoxLayout *layout = new QVBoxLayout(this);

    std::string rutaCarpeta = "../server_src/maps"; // Cambia esto a la ruta deseada
    std::vector<std::string> listaElementos = obtenerElementosEnCarpeta(rutaCarpeta);

    QStringList gameOptions;

    for (const auto& elemento : listaElementos) {
        if (elemento.find("spawn") == std::string::npos) {
            gameOptions << QString::fromStdString(elemento); 
        }
    }

    mapComboBox = new QComboBox(this);
    mapComboBox->addItems(gameOptions);

    modifyMapButton = new QPushButton("Modify map", this);

    layout->addWidget(mapComboBox);
    layout->addWidget(modifyMapButton);
    modifyMapButton->setEnabled(false);

/*
    widthMapLabel = new QLabel("Width map:", this);
    layout->addWidget(widthMapLabel);
    widthLineEdit = new QLineEdit(this);
    layout->addWidget(widthLineEdit);

    heightMapLabel = new QLabel("Height map:", this);
    layout->addWidget(heightMapLabel);
    heightLineEdit = new QLineEdit(this);
    layout->addWidget(heightLineEdit);
*/

    connect(modifyMapButton, &QPushButton::clicked, this, [this]() {
        QString selectedMap = mapComboBox->currentText();
        emit modifyMapRequested(selectedMap);//, widthLineEdit, heightLineEdit);
    });

    connect(mapComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() {
        modifyMapButton->setEnabled(true);
    });
}

std::vector<std::string> ModifyMap::obtenerElementosEnCarpeta(const std::string& ruta) {
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


ModifyMap::~ModifyMap() {}
