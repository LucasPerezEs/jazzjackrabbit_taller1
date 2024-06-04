#ifndef GAMELIST_H
#define GAMELIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>

class GameList : public QWidget {
public:
    GameList(QWidget *parent = nullptr);
    ~GameList();

    void updateGameList(const QStringList &games);

private:
    QListWidget *gameList;
    QPushButton *refreshButton;

    void init();
};

#endif // GAMELISTWIDGET_H