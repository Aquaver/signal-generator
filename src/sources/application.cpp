#include "src/headers/application.h"
#include "ui_application.h"

Application::Application(QWidget* parent) : QMainWindow(parent), ui(new Ui::Application) {
  ui -> setupUi(this);

  initValues(); // Must be first to prepare all values for chart initialization.
  initChartField();
  initSlots();
  initToolbar();
  initTabOrder();
}

Application::~Application() {
  delete ui;
}
