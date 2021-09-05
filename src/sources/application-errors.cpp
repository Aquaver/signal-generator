#include "src/headers/application.h"

#include <QMessageBox>

void Application::errorAddingChart() {
  QMessageBox error;
  QString line1 = "Invalid signal parameter value";
  QString line2 = "One of the parameters contains invalid or empty characters";

  error.setIcon(QMessageBox::Icon::Critical);
  error.setText(line1 + '\n' + line2);
  error.setWindowTitle("Signal Generator - Error");

  error.exec();
}

void Application::errorInvalidDeadTime() {
  QMessageBox error;
  QString line1 = "Invalid dead time value";
  QString line2 = "This value must be positive or zero";

  error.setIcon(QMessageBox::Icon::Critical);
  error.setText(line1 + '\n' + line2);
  error.setWindowTitle("Signal Generator - Error");

  error.exec();
}
