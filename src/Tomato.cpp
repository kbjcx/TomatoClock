#include "Tomato.h"

#include <QDebug>
#include <QVBoxLayout>

Tomato::Tomato(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle(tr("Tomato"));
    setFixedSize(QSize(400, 200));
    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);
    mainWidget->setTimeOutCallback(showRemindCallback, this);

    remindWidget = new RemindWidget();
    remindWidget->hide();

    timer = new QTimer();
    timer->setInterval(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(hideRemind()));
}

Tomato::~Tomato() {}

void Tomato::showRemind() {
    remindWidget->show();
    timer->start();
}

void Tomato::hideRemind() {
    remindWidget->hide();
    timer->stop();
}

void Tomato::showRemindCallback(void* arg) {
    auto tomato = static_cast<Tomato*>(arg);
    tomato->showRemind();
}
