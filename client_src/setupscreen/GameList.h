#ifndef GAMELIST_H
#define GAMELIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QStringList>

class GameList : public QWidget {
    Q_OBJECT

public:
    explicit GameList(QWidget *parent = nullptr);
    virtual ~GameList();

    void updateGameList(const QStringList &games);

signals:
    void refreshRequested();

private:
    QListWidget *gameList;
    QPushButton *refreshButton;

    void init();
};

#endif // GAMELIST_H
