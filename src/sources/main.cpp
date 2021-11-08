#include "src/headers/application.h"

#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  Application widget;

  widget.show();
  return application.exec();
}
