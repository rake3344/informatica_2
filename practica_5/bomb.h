#ifndef BOMB_H
#define BOMB_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QVector>
#include <QGraphicsRectItem>
#include <QHash>

class Bomb : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bomb(QGraphicsScene* scene, int blockSize, QVector<QGraphicsRectItem*>& destructibleBlocks, QHash<QGraphicsRectItem*, QGraphicsPixmapItem*> destructibleMap);
    void setExplosionRange(int range);

private slots:
    void explode();

private:
    QGraphicsScene* scene;
    QVector<QGraphicsRectItem*>& destructibleBlocks;
    QHash<QGraphicsRectItem*, QGraphicsPixmapItem*> destructibleMap;
    int blockSize;
    int explosionRange = 2;
};

#endif // BOMB_H
