
#ifndef APPMENU_H
#define APPMENU_H

#include <QDialog>
#include <QPushButton>
#include <QApplication>
#include <QVBoxLayout>

class AppMenu : public QDialog {
    Q_OBJECT

public:
    explicit AppMenu(QWidget* parent = nullptr);
    ~AppMenu();

private:
    void init();

signals:
    void createMapRequested();

private slots:
    void onReturnClicked();
    void onCreateMapClicked();

private:
    QPushButton* createMapButton;
    QPushButton* back;
};

#endif // APPMENU_H

