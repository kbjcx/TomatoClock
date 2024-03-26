#include "mainWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <iostream>

static int sWorkTime = 0;
static int sShortRestTime = 0;
static int sLongRestTime = 0;


void initConfig() {
    QFile file("E:\\CPP\\QT\\TomatoClock\\config.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray json = file.readAll();
        QJsonParseError parseError{};
        QJsonDocument doc = QJsonDocument::fromJson(json, &parseError);
        if (parseError.error == QJsonParseError::NoError) {
            QJsonObject obj = doc.object();
            sWorkTime = obj.value("focusTime").toInt();
            sShortRestTime = obj.value("shortRest").toInt();
            sLongRestTime = obj.value("longRest").toInt();
        } else {
            std::cout << "json error\n";
        }
        file.close();
    } else {
        std::cout << "json error\n";
    }
}

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)
    , status(FOCUS)
    , focusCount(0) {
    // 初始化配置
    initConfig();
    focusTime = sWorkTime * 60;
    shortRestTime = sShortRestTime * 60;
    longRestTime = sLongRestTime * 60;
    
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
}

void MainWidget::showRest() {
    callback(arg);
    if (focusCount <= 3) {
        status = SHORT_REST;
        countDownSeconds = shortRestTime;
    } else {
        status = LONG_REST;
        focusTime = 0;
        countDownSeconds = longRestTime;
    }
    giveUpFocusButton->hide();
    startRestButton->show();
    showTime();
}

void MainWidget::setTimeOutCallback(TimeOutCallback cb, void* arg) {
    callback = cb;
    this->arg = arg;
}
