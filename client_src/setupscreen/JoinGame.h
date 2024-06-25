#ifndef JOINGAME_H
#define JOINGAME_H

#include <QGridLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class JoinGame: public QWidget {
    Q_OBJECT

public:
    explicit JoinGame(QWidget* parent = nullptr);
    void setGameId(const QString& gameId);
    void updateGameList(const QStringList& games);
    virtual ~JoinGame();

signals:
    void joinGameRequested(const QString& gameID, const int elegido);
    void refreshRequested();
    void gameSelected(const QString& gameId);

private:
    QLineEdit* gameIdInput;
    QPushButton* joinButton;
    QPushButton* jazz;
    QPushButton* lori;
    QPushButton* spaz;
    QString elegidoGameId;
    QListWidget* gameList;
    QPushButton* refreshButton;
    int elegido;

    void init();
};

#endif  // JOINGAME_H
