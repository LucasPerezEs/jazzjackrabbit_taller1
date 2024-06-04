#ifndef JAZZJACKRABBIT_MULTIPLAYERMENU_H
#define JAZZJACKRABBIT_MULTIPLAYERMENU_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "CreateGame.h"
#include "JoinGame.h"
#include "GameList.h"

class MultiplayerMenu : public QDialog {
public:
    explicit MultiplayerMenu(QWidget *parent = nullptr);
    virtual ~MultiplayerMenu();

private:
    QPushButton *createGameButton;
    QPushButton *joinGameButton;
    QPushButton *refreshButton;

    CreateGame *createGameWidget;
    JoinGame  *joinGameWidget;
    GameList *gameListWidget;

    void init();
    void onCreateGameClicked();
    void onJoinGameClicked();
    void onRefreshClicked();
};

#endif //JAZZJACKRABBIT_MULTIPLAYERMENU_H
