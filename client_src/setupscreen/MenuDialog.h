#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialog>

class MenuDialog : public QDialog {


public:
    explicit MenuDialog(QWidget *parent = 0);
    virtual ~MenuDialog();

    QString getIp() const { return ipEdit->text(); }
    int getPort() const { return portEdit->text().toInt(); }



private slots:
    void acceptInput();

private:
    QLineEdit *ipEdit;
    QLineEdit *portEdit;




};

#endif // MENUDIALOG_H
