#ifndef JAZZJACKRABBIT_MULTIPLAYERMENU_H
#define JAZZJACKRABBIT_MULTIPLAYERMENU_H

#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <string>
#include <vector>

#include "CreateGame.h"
#include "CreateMap.h"
#include "GameList.h"
#include "JoinGame.h"

class MultiplayerMenu: public QDialog {
    Q_OBJECT

public:
    explicit MultiplayerMenu(QWidget* parent = nullptr);
    void updateGameList(const std::vector<std::string>& gameList);
    void showGameCreatedMessage();
    void showGameCreationFailedMessage();
    void showJoinGameFailedMessage();
    virtual ~MultiplayerMenu();

signals:
    void refreshRequested();
    void createGameRequested(const QString& gameName, const uint32_t maxPlayers,
                             const std::vector<uint32_t>& cheats);
    void joinGameRequested(const QString& gameID, const int elegido);
    void createMapRequested();


private:
    QPushButton* createGameButton;
    QPushButton* joinGameButton;
    QPushButton* refreshButton;
    QPushButton* createMapButton;
    QPushButton* back;

    CreateGame* createGameWidget;
    JoinGame* joinGameWidget;
    GameList* gameListWidget;

    void init();
    void onCreateGameClicked();
    void onJoinGameClicked();
    void onRefreshClicked();
    void onCreateMapClicked();
    void onReturnClicked();
};

#endif  // JAZZJACKRABBIT_MULTIPLAYERMENU_H
