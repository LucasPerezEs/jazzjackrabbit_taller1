#ifndef JOINGAME_H
#define JOINGAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class JoinGame : public QWidget {
    Q_OBJECT

public:
    explicit JoinGame(QWidget *parent = nullptr);
    virtual ~JoinGame();

signals:
    void joinGameRequested(const QString &gameID);

private:
    QLineEdit *gameIdInput;
    QPushButton *joinButton;

    void init();
};

#endif // JOINGAME_H
