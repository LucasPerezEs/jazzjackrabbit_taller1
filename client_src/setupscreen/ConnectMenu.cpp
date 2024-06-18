#include "ConnectMenu.h"

ConnectMenu::ConnectMenu(QWidget *parent)
        : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    ipEdit = new QLineEdit(this);
    portEdit = new QLineEdit(this);
    QPushButton *connectButton = new QPushButton("Connect", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);

    layout->addWidget(new QLabel("IP Address:", this));
    layout->addWidget(ipEdit);
    layout->addWidget(new QLabel("Port:", this));
    layout->addWidget(portEdit);
    layout->addWidget(connectButton);
    layout->addWidget(cancelButton);

    connect(connectButton, &QPushButton::clicked, this, &ConnectMenu::acceptInput);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void ConnectMenu::acceptInput() {
    accept();
}

ConnectMenu::~ConnectMenu() {}
