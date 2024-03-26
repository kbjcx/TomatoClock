#pragma once
#include <QMainWindow>

#include "mainWidget.h"
#include "remindWidget.h"

class Tomato : public QMainWindow {
    Q_OBJECT

public:
    Tomato(QWidget* parent = nullptr);
    ~Tomato();

private slots:
    void hideRemind();

public:
    static void showRemindCallback(void*);
    void showRemind();

private:
    MainWidget* mainWidget;
    RemindWidget* remindWidget;
    QPushButton* button;
    QTimer* timer;
};
