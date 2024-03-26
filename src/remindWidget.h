#pragma once

#include <QDialog>
#include <QLabel>
#include <QWidget>

class RemindWidget : public QWidget {
    Q_OBJECT

public:
    RemindWidget(QWidget* parent = nullptr);
    ~RemindWidget() = default;

private:
    QLabel* textRemindLabel;
};
