#include "mainWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)
    , focusTime(20)
    , restTime(5)
    , status(FOCUS)
    , focusCount(0) {
    QFont font("Arial", 40);
    font.setPointSize(40);
    countDownSeconds = focusTime;
    countDownClockLabel = new QLabel(this);
    countDownClockLabel->setFont(font);
    countDownClockLabel->setAlignment(Qt::AlignCenter);
    showTime();

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(countDownTime()));

    startFocusButton = new QPushButton(tr("开始专注"));
    connect(startFocusButton, SIGNAL(clicked()), this, SLOT(startTimer()));

    giveUpFocusButton = new QPushButton(tr("放弃专注"));
    giveUpFocusButton->hide();
    connect(giveUpFocusButton, SIGNAL(clicked()), this, SLOT(giveUpTimer()));

    startRestButton = new QPushButton(tr("开始休息"));
    startRestButton->hide();
    connect(startRestButton, SIGNAL(clicked()), this, SLOT(startRest()));

    giveUpRestButton = new QPushButton(tr("结束休息"));
    giveUpRestButton->hide();
    connect(giveUpRestButton, SIGNAL(clicked()), this, SLOT(giveUpRest()));

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(startFocusButton);
    buttonLayout->addWidget(giveUpFocusButton);
    buttonLayout->addWidget(startRestButton);
    buttonLayout->addWidget(giveUpRestButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(countDownClockLabel);
    mainLayout->addLayout(buttonLayout);
}

MainWidget::~MainWidget() {}

void MainWidget::showTime() {
    int min = countDownSeconds / 60;
    int sec = countDownSeconds % 60;
    QTime countDownTime;
    countDownTime.setHMS(0, min, sec);
    QString str = countDownTime.toString("mm:ss");
    countDownClockLabel->setText(str);
}

void MainWidget::countDownTime() {
    --countDownSeconds;
    showTime();
    if (countDownSeconds <= 0) {
        timer->stop();
        if (status == FOCUS) {
            ++focusCount;
            showRest();
        } else {
            showFocus();
        }
    }
}

void MainWidget::startTimer() {
    timer->start();
    startFocusButton->hide();
    giveUpFocusButton->show();
}

void MainWidget::giveUpTimer() {
    timer->stop();
    giveUpFocusButton->hide();
    showFocus();
}

void MainWidget::startRest() {
    countDownSeconds = restTime;
    timer->start();
    startRestButton->hide();
    giveUpRestButton->show();
}

void MainWidget::giveUpRest() {
    timer->stop();
    giveUpRestButton->hide();
    showFocus();
}

void MainWidget::showFocus() {
    countDownSeconds = focusTime;
    giveUpRestButton->hide();
    startFocusButton->show();
    showTime();
    status = FOCUS;
    if (status == LONG_REST) {
        focusCount = 0;
    }
}

void MainWidget::showRest() {
    callback(arg);
    if (focusCount <= 3) {
        status = SHORT_REST;
        countDownSeconds = restTime;
    } else {
        status = LONG_REST;
        countDownSeconds = restTime;
    }
    giveUpFocusButton->hide();
    startRestButton->show();
    showTime();
}

void MainWidget::setTimeOutCallback(TimeOutCallback cb, void* arg) {
    callback = cb;
    this->arg = arg;
}
