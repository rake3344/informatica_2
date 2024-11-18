#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QVector>
#include <QKeyEvent>

class Bomberman : public QGraphicsPixmapItem
{
public:
    Bomberman(QGraphicsScene* scene, int blockSize, QVector<QGraphicsRectItem*> solidBlocks, QVector<QGraphicsRectItem*> destructibleBlocks);

    void move(int dx, int dy);
    void setBlockSize(int size);

private:
    QGraphicsScene* scene;
    QVector<QGraphicsRectItem*> solidBlocks; // referencia a los bloques solidos
    QVector<QGraphicsRectItem*> destructibleBlocks; // referencia a los bloques destructibles
    int blockSize; // tamaño del bloque
    bool canMoveTo(int x, int y); // verifica si puede moverse a una posición

    QVector<QPixmap> spritesUp;
    QVector<QPixmap> spritesDown;
    QVector<QPixmap> spritesLeft;
    QVector<QPixmap> spritesRight;
    int currentFrameIndex;
};

#endif // BOMBERMAN_H
