#ifndef GAMELIST_H
#define GAMELIST_H

#include <QListWidget>
#include <QPushButton>
#include <QStringList>
#include <QVBoxLayout>
#include <QWidget>

class GameList: public QWidget {
    Q_OBJECT

public:
    explicit GameList(QWidget* parent = nullptr);
    virtual ~GameList();

    void updateGameList(const QStringList& games);

signals:
    void refreshRequested();
    void gameSelected(const QString &gameId);


private:
    QListWidget* gameList;
    QPushButton* refreshButton;
    QPushButton* joinButton;

    void init();
};

#endif  // GAMELIST_H
