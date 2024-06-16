
#include "CreateMap.h"

CreateMap::CreateMap(QWidget *parent) : QWidget(parent) {
    init();
}

void CreateMap::init() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    createMapButton = new QPushButton("Create Map", this);

    layout->addWidget(createMapButton);

    connect(joinButton, &QPushButton::clicked, this, [this]() {
        emit createMapRequested();
    });
}

CreateMap::~CreateMap() {}