#pragma once
#include <QMainWindow>

#include "mainWidget.h"

class Tomato : public QMainWindow {
    Q_OBJECT

public:
    Tomato(QWidget* parent = nullptr);
    ~Tomato();

private:
    MainWidget* mainWidget;
};
