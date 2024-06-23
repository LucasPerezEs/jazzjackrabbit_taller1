
#ifndef CREATE_MAP_H
#define CREATE_MAP_H

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

class CreateMap : public QWidget {
    Q_OBJECT

public:
    explicit CreateMap(QWidget* parent = nullptr);
    virtual ~CreateMap();

    signals:
    	void createMapRequested(const QString& mapName, const double& widthMap, const double& heightMap);

private:
    QLineEdit* widthLineEdit;
    QLineEdit* heightLineEdit;
    QLineEdit* nameLineEdit;
    QPushButton* createButton;

    QLabel* widthMapLabel;
    QLabel* heightMapLabel;
    QLabel* mapName;

};

#endif // CREATENAME_H
