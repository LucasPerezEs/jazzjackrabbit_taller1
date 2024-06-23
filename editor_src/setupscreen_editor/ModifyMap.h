
#ifndef MODIFY_MAP_H
#define MODIFY_MAP_H

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

    QPushButton* modifyMapButton;
    QComboBox* mapComboBox;
};

#endif // CREATENAME_H