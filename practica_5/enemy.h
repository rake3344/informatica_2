#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Enemy(QGraphicsScene* scene, int blockSize, QVector<QGraphicsRectItem*> solidBlocks, QVector<QGraphicsRectItem*> destructibleBlocks);
    void setSprites(const QVector<QPixmap>& sprites);
    bool canMoveTo(int x, int y);

private slots:
    void moveRandomly();

private:
    QGraphicsScene* scene;
    int blockSize;
    QVector<QGraphicsRectItem*> solidBlocks;
    QVector<QGraphicsRectItem*> destructibleBlocks;

    QVector<QPixmap> sprites;
    int currentFrameIndex = 0;

    QTimer* movementTimer; // temporizador para mover al enemigo


};

#endif // ENEMY_H
