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
    void setGameId(const QString &gameId);
    virtual ~JoinGame();

signals:
    void joinGameRequested(const QString &gameID, const int elegido);

private:
    QLineEdit *gameIdInput;
    QPushButton *joinButton;
    QPushButton *jazz;
    QPushButton *lori;
    QPushButton *spaz;
    QString elegidoGameId;
    int elegido;

    void init();
};

#endif // JOINGAME_H
