#include "remindWidget.h"

RemindWidget::RemindWidget(QWidget* parent)
    : QWidget(parent) {
    setWindowTitle(tr("提醒"));
    showFullScreen();
    textRemindLabel = new QLabel(tr("该休息啦"), this);
    textRemindLabel->setScaledContents(true);
    textRemindLabel->setAlignment(Qt::AlignCenter);
}
