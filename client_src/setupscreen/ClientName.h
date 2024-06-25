#ifndef CLIENTNAME_H
#define CLIENTNAME_H

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>

#include "../../common_src/headers/cheat_commands.h"

class ClientName: public QWidget {
    Q_OBJECT

public:
    explicit ClientName(QWidget* parent = nullptr);
    virtual ~ClientName();

signals:
    void ClientNameRequested(const QString& clientName);

private:
    QLineEdit* clientNameInput;
    QPushButton* sendButton;

    void init();
};

#endif  // CLIENTNAME_H
