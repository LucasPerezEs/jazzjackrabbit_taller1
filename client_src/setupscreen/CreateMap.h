
#ifndef CREATEMAP_H
#define CREATEMAP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class CreateMap : public QWidget {
    Q_OBJECT

public:
    explicit CreateMap(QWidget *parent = nullptr);
    virtual ~CreateMap();

signals:
    void createMapRequested();

private:
    QPushButton *createMapButton;

    void init();
};

#endif // CREATEMAP_H