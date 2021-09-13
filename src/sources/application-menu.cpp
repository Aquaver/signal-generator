#include "src/headers/application.h"
#include "src/headers/compound-signal.h"
#include "ui_application.h"

#include <QInputDialog>
#include <QUuid>

void Application::createCompoundSignal(CompoundType type, QString typeName) {
  QString selectedChart = ui -> listCharts -> selectedItems().first() -> text();
  QStringList namesList = (chartList -> count() == 1) ? QStringList({""}) : QStringList();
  QInputDialog* inputDialog = new QInputDialog(this);

  for (QString chartName : chartList -> keys()) {
    if (chartName != selectedChart) {
      namesList.append(chartName);
    }
  }

  QString dialogLabelLine1 = QString("Creating new compound signal (type %1) from: %2").arg(typeName).arg(selectedChart);
  QString dialogLabelLine2 = QString("Choose second component");

  inputDialog -> setComboBoxItems(namesList);
  inputDialog -> setLabelText(dialogLabelLine1 + '\n' + dialogLabelLine2);
  inputDialog -> setWindowTitle("New compound signal");

  if (inputDialog -> exec() == QInputDialog::DialogCode::Accepted) {
    if (namesList.value(0) != "") {
      QString chartIdentifier = QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces);
      Signal* newSignal = new CompoundSignal();

      dynamic_cast<CompoundSignal*>(newSignal) -> setCompoundSignals(chartList -> value(selectedChart), chartList -> value(inputDialog -> textValue()));
      dynamic_cast<CompoundSignal*>(newSignal) -> setCompoundType(type);

      this -> chartList -> insert(chartIdentifier, newSignal);
      this -> groupList -> insert(chartIdentifier, ui -> chartField -> scene() -> createItemGroup({}));

      ui -> listCharts -> addItem(chartIdentifier);
      redrawAllCharts();
    } else {
        errorInvalidSignalCompound();
    }
  }
}
