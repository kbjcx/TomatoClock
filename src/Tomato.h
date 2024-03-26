#pragma once
#include <QMainWindow>

#include "mainWidget.h"
#include "remindWidget.h"

class Tomato : public QMainWindow {
    Q_OBJECT

public:
    explicit Tomato(QWidget* parent = nullptr);
    ~Tomato() override;

private slots:
    void hideRemind();

public:
    static void showRemindCallback(void*);
    void showRemind();

private:
    MainWidget* mainWidget;
    RemindWidget* remindWidget;
    QTimer* timer;
};
