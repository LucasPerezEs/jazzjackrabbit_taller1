#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>

#include "../../common_src/headers/cheat_commands.h"

class CreateGame: public QWidget {
    Q_OBJECT

public:
    explicit CreateGame(QWidget* parent = nullptr);
    virtual ~CreateGame();

signals:
    void createGameRequested(const QString& gameName, const uint32_t& maxPlayers,
                             const std::vector<uint32_t>& cheats);

private:
    QLabel* gameNameLabel;
    QLineEdit* gameNameInput;

    QLabel* maxPlayersLabel;
    QLineEdit* maxPlayersInput;

    QLabel* cheatsLabel;
    QCheckBox* inmortalCheckBox;
    QCheckBox* oneShotOneKillCheckBox;
    QCheckBox* moonGravityCheckBox;
    QCheckBox* hardEnemiesCheckBox;
    QCheckBox* extraTimeCheckBox;


    QPushButton* createButton;

    void init();
    std::vector<uint32_t> saveCheats();
};

#endif  // CREATEGAME_H
