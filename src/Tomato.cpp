#include "Tomato.h"

#include <QVBoxLayout>

Tomato::Tomato(QWidget* parent)
    : QMainWindow(parent) {
    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);
}

Tomato::~Tomato() {}
