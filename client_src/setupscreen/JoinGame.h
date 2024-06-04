#ifndef JOINGAME_H
#define JOINGAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class JoinGame : public QWidget {
public:
    JoinGame(QWidget *parent = nullptr);
    ~JoinGame();

private:
    QLineEdit *gameIdInput;
    QPushButton *joinButton;

    void init();
};

#endif // JOINGAME_H
