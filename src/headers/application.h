#pragma once

#include "src/headers/compound-signal.h"
#include "src/headers/signal.h"

#include <QGraphicsItemGroup>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
  class Application;
}
QT_END_NAMESPACE

enum class MenuActions {
    MENU_ACTION_ADD, MENU_ACTION_SUBTRACT
};

class Application : public QMainWindow {
  Q_OBJECT
};
