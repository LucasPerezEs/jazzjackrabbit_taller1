#include "SetupScreen.h"

SetupScreen::SetupScreen(QWidget* parent) : QDialog(parent), appMenu() {
    init();
}

void SetupScreen::init() {
    this->setObjectName("Main");
    this->setWindowTitle("Editor");
}


void SetupScreen::ShowAppMenu() {
    appMenu.show();
    appMenu.exec();
}


SetupScreen::~SetupScreen() {}
