#include "SetupScreen.h"

SetupScreen::SetupScreen(QWidget* parent):
        QDialog(parent),
        connectMenu(),
        multiplayerMenu()

{

}

void SetupScreen::init() {
    this->setObjectName("Main");
    this->setWindowTitle("JazzJack Rabbit 2");
}

void SetupScreen::ShowConnectMenu(){

    connectMenu.show();

}


void SetupScreen::ShowMultiplayerMenu(){

    multiplayerMenu.show();


}


bool SetupScreen::AcceptedConnection(){
    return connectMenu.exec() == QDialog::Accepted;
}


SetupScreen::~SetupScreen() {}
