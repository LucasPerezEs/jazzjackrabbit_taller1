
#ifndef MODIFY_MAP_H
#define MODIFY_MAP_H

#include <string>
#include <iostream>
#include <filesystem>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>

class ModifyMap : public QWidget {
    Q_OBJECT

public:
    explicit ModifyMap(QWidget* parent = nullptr);
    virtual ~ModifyMap();

    signals:
    	void modifyMapRequested(const QString& mapName);

private:
    std::vector<std::string> obtenerElementosEnCarpeta(const std::string& ruta);
    QPushButton* modifyMapButton;
    QComboBox* mapComboBox;
};

#endif // CREATENAME_H