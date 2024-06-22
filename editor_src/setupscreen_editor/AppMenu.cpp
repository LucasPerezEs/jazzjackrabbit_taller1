#include "AppMenu.h"

AppMenu::AppMenu(QWidget* parent) : QDialog(parent) {
    //exitFlag = 1;
    init();
}

void AppMenu::init() {

    QVBoxLayout* layout = new QVBoxLayout(this);

    createMapButton = new QPushButton("Crear Mapa", this);
    //back = new QPushButton("Volver", this);

    layout->addWidget(createMapButton);
    //layout->addWidget(back);

    //back->hide();

    connect(createMapButton, &QPushButton::clicked, this, &AppMenu::onCreateMapClicked);
    //connect(back, &QPushButton::clicked, this, &AppMenu::onReturnClicked);
}

void AppMenu::onReturnClicked() {
    createMapButton->show();
    //back->hide();
}

void AppMenu::onCreateMapClicked() {
    //back->show();
    emit createMapRequested();
}

AppMenu::~AppMenu() {}

