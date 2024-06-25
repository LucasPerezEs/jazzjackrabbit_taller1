#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "../../common_src/headers/cheat_commands.h"

class CreateGame: public QWidget {
    Q_OBJECT

public:
    explicit CreateGame(QWidget* parent = nullptr);
    virtual ~CreateGame();

signals:
    void createGameRequested(const QString& gameName, const std::string& map_selected,
                             const uint32_t& maxPlayers, const std::vector<uint32_t>& cheats);

private:
    QLineEdit* gameNameInput;

    QLineEdit* maxPlayersInput;

    QListWidget* cheatList;

    QPushButton* back;

    /*QCheckBox* inmortalCheckBox;
    QCheckBox* oneShotOneKillCheckBox;
    QCheckBox* moonGravityCheckBox;
    QCheckBox* hardEnemiesCheckBox;
    QCheckBox* extraTimeCheckBox;*/

    QPushButton* createButton;

    std::vector<std::string> obtenerElementosEnCarpeta(const std::string& ruta);
    QComboBox* mapComboBox;

    void init();
    std::vector<uint32_t> saveCheats();
};

#endif  // CREATEGAME_H
