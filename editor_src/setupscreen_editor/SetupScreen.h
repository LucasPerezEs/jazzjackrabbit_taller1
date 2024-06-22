
#ifndef SETUPSCREEN_H
#define SETUPSCREEN_H

#include <QDialog>
#include "AppMenu.h"

class SetupScreen : public QDialog {
    Q_OBJECT

public:
    explicit SetupScreen(QWidget* parent = nullptr);
    ~SetupScreen();

    void init();
    void ShowAppMenu();

private:
    AppMenu appMenu;
};

#endif // SETUPSCREEN_H

