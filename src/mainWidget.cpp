#include "mainWidget.h"

#include <QVBoxLayout>

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent) {
    QFont font("Arial", 20);
    font.setPointSize(20);
    countDownSeconds = 60;
    countDownClockLabel = new QLabel(this);
    countDownClockLabel->setFont(font);
    countDownClockLabel->setAlignment(Qt::AlignCenter);
    countDownClockLabel->setText("hello");
    showTime();

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));

    startFocusButton = new QPushButton(tr("开始专注"), this);
    connect(startFocusButton, SIGNAL(clicked()), this, SLOT(startTimer()));
    giveUpFocusButton = new QPushButton(tr("放弃专注"));
    connect(giveUpFocusButton, SIGNAL(clicked()), this, SLOT(giveUpTimer()));

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(countDownClockLabel);
    mainLayout->addWidget(startFocusButton);
}

MainWidget::~MainWidget() {}

void MainWidget::showTime() {
    --countDownSeconds;
    int min = countDownSeconds / 60;
    int sec = countDownSeconds % 60;
    QTime countDownTime;
    countDownTime.setHMS(0, min, sec);
    QString str = countDownTime.toString("mm:ss");
    countDownClockLabel->setText(str);
    if (countDownSeconds <= 0) {
        countDownSeconds = 60;
        timer->stop();
    }
}

void MainWidget::startTimer() {
    timer->start();
}

void MainWidget::giveUpTimer() {
    timer->stop();
}
