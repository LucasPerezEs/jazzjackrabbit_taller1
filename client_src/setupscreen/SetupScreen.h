#ifndef JAZZJACKRABBIT_SETUPSCREEN_H
#define JAZZJACKRABBIT_SETUPSCREEN_H

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialog>

#include "ConnectMenu.h"
#include "MultiplayerMenu.h"



class SetupScreen : public QDialog {
public:
    explicit SetupScreen(QWidget *parent = 0);
    virtual ~SetupScreen();

    QString getIp() const { return connectMenu.getIp(); }
    QString getPort() const { return connectMenu.getPort(); }



    void ShowConnectMenu();
    void ShowMultiplayerMenu();
    bool AcceptedConnection();

private slots:
    void acceptInput();
    void onConnectClicked();

private:
    ConnectMenu connectMenu;
    MultiplayerMenu multiplayerMenu;

    void init();

};


#endif  // JAZZJACKRABBIT_SETUPSCREEN_H
