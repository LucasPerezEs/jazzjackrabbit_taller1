#ifndef JAZZJACKRABBIT_MULTIPLAYERMENU_H
#define JAZZJACKRABBIT_MULTIPLAYERMENU_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include <QMessageBox>

#include "CreateGame.h"
#include "JoinGame.h"
#include "GameList.h"
#include "CreateMap.h"

class MultiplayerMenu : public QDialog {
    Q_OBJECT

public:
    explicit MultiplayerMenu(QWidget *parent = nullptr);
    void updateGameList(const std::vector<std::string>& gameList);
    void showGameCreatedMessage();
    void showGameCreationFailedMessage();
    void showJoinGameFailedMessage();
    virtual ~MultiplayerMenu();

signals:
    void refreshRequested();
    void createGameRequested(const QString &gameName, const uint32_t maxPlayers);
    void joinGameRequested(const QString &gameID, const int elegido);
    void createMapRequested();



private:
    QPushButton *createGameButton;
    QPushButton *joinGameButton;
    QPushButton *refreshButton;
    QPushButton *createMapButton;

    CreateGame *createGameWidget;
    JoinGame  *joinGameWidget;
    GameList *gameListWidget;

    void init();
    void onCreateGameClicked();
    void onJoinGameClicked();
    void onRefreshClicked();
    void onCreateMapClicked();
};

#endif // JAZZJACKRABBIT_MULTIPLAYERMENU_H
