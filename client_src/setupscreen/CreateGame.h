#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class CreateGame: public QWidget {
    Q_OBJECT

public:
    explicit CreateGame(QWidget* parent = nullptr);
    virtual ~CreateGame();

signals:
    void createGameRequested(const QString& gameName, const uint32_t& maxPlayers);

private:
    QLabel* gameNameLabel;
    QLineEdit* gameNameInput;

    QLabel* maxPlayersLabel;
    QLineEdit* maxPlayersInput;

    QPushButton* createButton;

    void init();
};

#endif  // CREATEGAME_H
