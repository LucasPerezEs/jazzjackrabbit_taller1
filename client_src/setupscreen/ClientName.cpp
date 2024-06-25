#include "ClientName.h"

ClientName::ClientName(QWidget* parent): QWidget(parent) { init(); }

void ClientName::init() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    clientNameInput = new QLineEdit(this);
    clientNameInput->setObjectName("clientNameInput");
    clientNameInput->setFixedSize(200, 30);
    clientNameInput->setPlaceholderText("Enter your name here:");
    layout->addWidget(clientNameInput);
    layout->setAlignment(clientNameInput, Qt::AlignHCenter);
    // layout->setAlignment(clientNameInput, Qt::AlignBottom);

    sendButton = new QPushButton("Enter your name", this);
    sendButton->setObjectName("saveNameButton");
    sendButton->setFixedSize(200, 30);
    layout->addWidget(sendButton);
    layout->setAlignment(sendButton, Qt::AlignHCenter);
    // layout->setAlignment(sendButton, Qt::AlignBottom);

    layout->setAlignment(Qt::AlignBottom);
    layout->setSpacing(10);


    connect(sendButton, &QPushButton::clicked, this, [this]() {
        QString clientName = clientNameInput->text();
        emit ClientNameRequested(clientName);
    });
}

ClientName::~ClientName() {}
