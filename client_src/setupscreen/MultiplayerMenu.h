#ifndef JAZZJACKRABBIT_MULTIPLAYERMENU_H
#define JAZZJACKRABBIT_MULTIPLAYERMENU_H

#include <QComboBox>
#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <string>
#include <vector>

#include "../headers/client.h"

#include "ClientName.h"
#include "CreateGame.h"
#include "JoinGame.h"

class MultiplayerMenu: public QDialog {
    Q_OBJECT

public:
    int exit;
    MultiplayerMenu(QWidget* parent, Client* client);
    void init();
    void updateGameList(const std::vector<std::string>& gameList);
    void nameSet();
    void showGameCreatedMessage();
    void showGameCreationFailedMessage();
    void showJoinGameFailedMessage();
    void showSetNameFailedMessage();
    void setClient(Client* client);
    virtual ~MultiplayerMenu();

signals:
    void refreshRequested();
    void createGameRequested(const QString& gameName, const std::string& map_selected,
                             const uint32_t maxPlayers, const std::vector<uint32_t>& cheats);
    void joinGameRequested(const QString& gameID, const int elegido);
    void createMapRequested();
    void ClientNameRequested(const QString& clientName);


private:
    QPushButton* createGameButton;
    QPushButton* joinGameButton;
    // QPushButton* refreshButton;
    QPushButton* back;

    ClientName* clientNameWidget;
    CreateGame* createGameWidget;
    JoinGame* joinGameWidget;
    // GameList* gameListWidget;

    void loadStyleSheet();

    void onCreateGameClicked();
    void onJoinGameClicked();
    void onRefreshClicked();
    void onReturnClicked();
};

#endif  // JAZZJACKRABBIT_MULTIPLAYERMENU_H
