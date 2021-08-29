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

  public:
    Application(QWidget* parent = nullptr);
    ~Application();

    QGraphicsItemGroup* gridGroup = nullptr;

  private:
    Ui::Application* ui;

    qint16 centerX = -1, centerY = -1; // Value -1 means uninitialized chart, its initialization happens in separate function.
    qint16 chartWidth = -1, chartHeight = -1;
    qint16 gridLengthX = -1, gridLengthY = -1;

    qreal chartShiftX = -1, chartShiftY = -1;
    qreal gridUnitX = -1, gridUnitY = -1;

    QColor axesColor = QColor(64, 64, 64);
    QColor gridColor = QColor(110, 110, 110);

    QVector<qreal> gridLine = {5.0, 2.5};

    QMap<QString, Signal*>* chartList = new QMap<QString, Signal*>();
    QMap<QString, QGraphicsItemGroup*>* groupList = new QMap<QString, QGraphicsItemGroup*>();
    QMap<MenuActions, QAction *>* actionList = new QMap<MenuActions, QAction*>();

    // Chart field management interface.
    void initChartField();
    void initSlots();
    void initTabOrder();
    void initToolbar();
    void initValues();
    void updateAxesLabel();
    void updateCenterLabel();

    // Calculating and drawing charts.
    void redrawAllCharts();

    // Error handling dialogs.
    void errorAddingChart();
    void errorInvalidDeadTime();
    void errorInvalidDutyCycle();
    void errorInvalidEdgeTime();
    void errorInvalidSignalCompound();

    // Helper functions.
    void createCompoundSignal(CompoundType type, QString typeName);

  private slots:
    // Interface buttons events.
    void onAddSine();
    void onAddSquare();
    void onAddTriangular();

    void onShiftCenter();
    void onShiftDown();
    void onShiftLeft();
    void onShiftRight();
    void onShiftUp();

    void onZoomIn();
    void onZoomOut();
    void onZoomReset();

    void onRemove();
    void onRename();

    // Interface menu events.
    void menuAdd();
    void menuSubtract();

    // Other events.
    void onItemSelected();
};
