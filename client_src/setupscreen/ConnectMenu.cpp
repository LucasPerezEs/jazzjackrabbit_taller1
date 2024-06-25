#include "ConnectMenu.h"

ConnectMenu::ConnectMenu(QWidget* parent): QDialog(parent) {
    this->setObjectName("connectMenu");
    int id = QFontDatabase::addApplicationFont("../client_src/assets/ARCADECLASSIC.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);
    this->setFixedSize(800, 600);
    init();
}

void ConnectMenu::init() {
    QVBoxLayout* Vlayout = new QVBoxLayout(this);

    QSpacerItem* verticalSpacer =
            new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    Vlayout->addItem(verticalSpacer);

    QGridLayout* gridLayout = new QGridLayout(this);

    ipEdit = new QLineEdit(this);
    ipEdit->setFixedSize(200, 30);
    ipEdit->setPlaceholderText("Enter server ip:");
    ipEdit->setObjectName("ipEdit");

    portEdit = new QLineEdit(this);
    portEdit->setFixedSize(200, 30);
    portEdit->setPlaceholderText("Enter server port:");
    portEdit->setObjectName("portEdit");

    QPushButton* connectButton = new QPushButton("Connect", this);
    connectButton->setObjectName("connectButton");
    connectButton->setFixedSize(200, 30);

    QPushButton* cancelButton = new QPushButton("Cancel", this);
    cancelButton->setObjectName("cancelButton");
    cancelButton->setFixedSize(200, 30);

    gridLayout->setSpacing(20);
    // layout->addWidget(new QLabel("IP Address:", this));
    gridLayout->addWidget(ipEdit, 0, 0);
    gridLayout->addWidget(portEdit, 0, 1);
    gridLayout->addWidget(connectButton, 1, 0);
    gridLayout->addWidget(cancelButton, 1, 1);

    /*layout->addWidget(ipEdit);
    //layout->addWidget(new QLabel("Port:", this));
    layout->addWidget(portEdit);
    layout->addWidget(connectButton);
    layout->addWidget(cancelButton);*/

    Vlayout->addLayout(gridLayout);
    Vlayout->setAlignment(Qt::AlignCenter);

    connect(connectButton, &QPushButton::clicked, this, &ConnectMenu::acceptInput);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    loadStyleSheet();
}

void ConnectMenu::loadStyleSheet() {
    QFile file("../client_src/setupscreen/styles.qss");
    if (!file.exists()) {
        qDebug() << "Stylesheet doesn't exist.";
    }

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString stylesheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(stylesheet);
        qDebug() << "Stylesheet applied successfully.";
    } else {
        qDebug() << "Failed to load stylesheet.";
    }
}

void ConnectMenu::acceptInput() { accept(); }

ConnectMenu::~ConnectMenu() {}
