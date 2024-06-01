#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MenuDialog : public QDialog {
    Q_OBJECT

public:
    MenuDialog(QWidget *parent = nullptr);

    QString getIp() const { return ipEdit->text(); }
    int getPort() const { return portEdit->text().toInt(); }

private slots:
    void acceptInput();

private:
    QLineEdit *ipEdit;
    QLineEdit *portEdit;
};

#endif // MENUDIALOG_H
