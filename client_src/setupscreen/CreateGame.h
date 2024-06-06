#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class CreateGame : public QWidget {
    Q_OBJECT

public:
    explicit CreateGame(QWidget *parent = nullptr);
    virtual ~CreateGame();

signals:
    void createGameRequested(const QString &gameName);

private:
    QLineEdit *gameNameInput;
    QPushButton *createButton;

    void init();
};

#endif // CREATEGAME_H
