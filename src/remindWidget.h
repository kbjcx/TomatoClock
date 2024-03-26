#pragma once

#include <QDialog>
#include <QLabel>
#include <QWidget>

class RemindWidget : public QWidget {
    Q_OBJECT

public:
    explicit RemindWidget(QWidget* parent = nullptr);
    ~RemindWidget() override = default;

private:
    QLabel* textRemindLabel;
};
