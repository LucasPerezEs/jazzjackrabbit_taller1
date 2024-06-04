#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialog>


class ConnectMenu: public QDialog {


public:
    explicit ConnectMenu(QWidget *parent = 0);
    virtual ~ConnectMenu();

    QString getIp() const { return ipEdit->text(); }
    QString getPort() const { return portEdit->text(); }



private slots:
    void acceptInput();

private:
    QLineEdit *ipEdit;
    QLineEdit *portEdit;




};

#endif // MENUDIALOG_H
