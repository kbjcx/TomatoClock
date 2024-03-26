#pragma once
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QTimer>

#include "remindWidget.h"

class MainWidget : public QWidget {
    Q_OBJECT

public:
    enum TomatoStatus {
        FOCUS = 0,
        SHORT_REST = 1,
        LONG_REST = 2
    };

    using TimeOutCallback = void (*)(void*);

public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

    void showTime();
    void setTimeOutCallback(TimeOutCallback, void*);

private slots:
    void countDownTime();
    void startTimer();
    void giveUpTimer();
    void startRest();
    void giveUpRest();

private:
    void showFocus();
    void showRest();

private:
    QTimer* timer;
    int countDownSeconds;
    QLabel* countDownClockLabel;
    QPushButton* startFocusButton;
    QPushButton* startRestButton;
    QPushButton* giveUpFocusButton;
    QPushButton* giveUpRestButton;
    int focusTime;
    int shortRestTime;
    int longRestTime;
    TomatoStatus status;
    int focusCount;
    TimeOutCallback callback;
    void* arg;
};
