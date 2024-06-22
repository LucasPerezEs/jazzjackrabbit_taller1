#include "ClientName.h"

ClientName::ClientName(QWidget* parent): QWidget(parent) { init(); }

void ClientName::init() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    clientNameLabel = new QLabel("Player Name:", this);
    layout->addWidget(clientNameLabel);
    clientNameInput = new QLineEdit(this);
    layout->addWidget(clientNameInput);

    sendButton = new QPushButton("Save Name", this);
    layout->addWidget(sendButton);

    connect(sendButton, &QPushButton::clicked, this, [this]() {
        QString clientName = clientNameInput->text();
        emit ClientNameRequested(clientName);
    });
}

ClientName::~ClientName() {}