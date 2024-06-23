
#include "AppMenu.h"

AppMenu::AppMenu(QWidget* parent) : QDialog(parent), createMapWidget(new CreateMap()), modifyMapWidget(new ModifyMap()) { init(); }

void AppMenu::init() {

    QVBoxLayout* layout = new QVBoxLayout(this);

    createMapButton = new QPushButton("Create Map", this);
    modifyMapButton = new QPushButton("Modify Map", this);
    back = new QPushButton("Return", this);

    layout->addWidget(createMapButton);
    layout->addWidget(modifyMapButton);
    layout->addWidget(back);
    layout->addWidget(createMapWidget);
    layout->addWidget(modifyMapWidget);

    back->hide();
    createMapWidget->hide();
    modifyMapWidget->hide();

    connect(createMapButton, &QPushButton::clicked, this, &AppMenu::onCreateMapClicked);
    connect(modifyMapButton, &QPushButton::clicked, this, &AppMenu::OnModifyMapClicked);
    connect(back, &QPushButton::clicked, this, &AppMenu::onReturnClicked);
    connect(createMapWidget, &CreateMap::createMapRequested,this, &AppMenu::createMapRequested);
    connect(modifyMapWidget, &ModifyMap::modifyMapRequested,this, &AppMenu::modifyMapRequested);

}

void AppMenu::onCreateMapClicked() {
    back->show();
    createMapWidget->show();
    modifyMapWidget->hide();

    createMapButton->hide();
    modifyMapButton->hide();
}

void AppMenu::OnModifyMapClicked(){
    back->show();
    createMapWidget->hide();
    modifyMapWidget->show();

    createMapButton->hide();
    modifyMapButton->hide();
}

void AppMenu::onReturnClicked() {
    createMapButton->show();
    modifyMapButton->show();

    back->hide();
    createMapWidget->hide();
    modifyMapWidget->hide();

}

AppMenu::~AppMenu() {}

