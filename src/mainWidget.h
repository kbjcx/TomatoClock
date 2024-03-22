#pragma once
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QTimer>

class MainWidget : public QWidget {
    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

private slots:
    void showTime();
    void startTimer();
    void giveUpTimer();

private:
    QTimer* timer;
    int countDownSeconds;
    QLabel* countDownClockLabel;
    QPushButton* startFocusButton;
    QPushButton* startRestButton;
    QPushButton* giveUpFocusButton;
    QPushButton* giveUpRestButton;
};
