#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QFont>
#include <QFontDatabase>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>


class ConnectMenu: public QDialog {
    Q_OBJECT

public:
    explicit ConnectMenu(QWidget* parent = nullptr);
    virtual ~ConnectMenu();

    QString getIp() const { return ipEdit->text(); }
    QString getPort() const { return portEdit->text(); }


private slots:
    void acceptInput();

private:
    QLineEdit* ipEdit;
    QLineEdit* portEdit;

    void init();
    void loadStyleSheet();
};

#endif  // MENUDIALOG_H
