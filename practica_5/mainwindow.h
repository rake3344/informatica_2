#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "QGraphicsRectItem"
#include <QVector>
#include <QHash>

#include "bomberman.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectangulo;

    QVector<QGraphicsRectItem*> solidBlocks; // Bloques solidos (invisibles)
    QVector<QGraphicsRectItem*> destructibleBlocks; // Bloques desctructibles

    QHash<QGraphicsRectItem*, QGraphicsPixmapItem*> destructibleMap; // elementos desctructibles

    Bomberman* bomberman;

    void setupMap();
    void generateDesctructibleBlocks();
    void addEnemies(int count);

};
#endif // MAINWINDOW_H
