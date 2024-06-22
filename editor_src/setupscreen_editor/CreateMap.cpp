
#include "CreateMap.h"

CreateMap::CreateMap(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Create Map");

    QVBoxLayout* layout = new QVBoxLayout(this);

    mapName = new QLabel("Map name:", this);
    layout->addWidget(mapName);
    nameLineEdit = new QLineEdit(this);
    layout->addWidget(nameLineEdit);

    widthMapLabel = new QLabel("Width map:", this);
    layout->addWidget(widthMapLabel);
    widthLineEdit = new QLineEdit(this);
    layout->addWidget(widthLineEdit);

    heightMapLabel = new QLabel("Height map:", this);
    layout->addWidget(heightMapLabel);
    heightLineEdit = new QLineEdit(this);
    layout->addWidget(heightLineEdit);

    createButton = new QPushButton("Create", this);
    layout->addWidget(createButton);

    connect(createButton, &QPushButton::clicked, this, [this]() {
        QString mapName = nameLineEdit->text();
        int width = widthLineEdit->text().toInt();
        int height = heightLineEdit->text().toInt();
        emit createMapRequested(mapName, width, height);
    });
}


CreateMap::~CreateMap() {}