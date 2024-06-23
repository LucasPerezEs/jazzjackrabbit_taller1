
#include "ModifyMap.h"

ModifyMap::ModifyMap(QWidget* parent): QWidget(parent) {

    setWindowTitle("Modify Map");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QStringList gameOptions;
    gameOptions << "Medivo" << "Castle_Earlong";

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


ModifyMap::~ModifyMap() {}
