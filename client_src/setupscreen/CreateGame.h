#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class CreateGame : public QWidget {
public:
    CreateGame(QWidget *parent = nullptr);
    ~CreateGame();

private:
    QLineEdit *gameNameInput;
    QPushButton *createButton;

    void init();
};

#endif // CREATEGAME_H
