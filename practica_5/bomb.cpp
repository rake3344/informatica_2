#include "bomb.h"

Bomb::Bomb(QGraphicsScene* scene, int blockSize, QVector<QGraphicsRectItem*>& destructibleBlocks,QHash<QGraphicsRectItem*, QGraphicsPixmapItem*> destructibleMap)
    : scene(scene), blockSize(blockSize), destructibleBlocks(destructibleBlocks), destructibleMap(destructibleMap)
{

    qDebug() << "Bomb creada con blockSize: " << blockSize;
    qDebug() << "Numero de bloques destructibles: " << destructibleBlocks.size();
    //qDebug() << "Bloques destructibles: " << destructibleBlocks;
    //qDebug() << "Mapa: " << destructibleMap;

    QPixmap bombSprite(":/sprites/assets/bomb.png");
    setPixmap(bombSprite.scaled(blockSize, blockSize));

    QTimer::singleShot(2000, this, &Bomb::explode); // explota despues de 2 segundos
}

void Bomb::setExplosionRange(int range) {
    explosionRange = range;
}

void Bomb::explode() {
    // Calcular la posición central de la bomba
    int bombX = static_cast<int>(x()) / blockSize;
    int bombY = static_cast<int>(y()) / blockSize;

    // Calcular el área de explosión
    QVector<QPoint> affectedCells;
    for (int i = 0; i <= explosionRange; ++i) {
        affectedCells.append(QPoint(bombX + i, bombY)); // Derecha
        affectedCells.append(QPoint(bombX - i, bombY)); // Izquierda
        affectedCells.append(QPoint(bombX, bombY + i)); // Abajo
        affectedCells.append(QPoint(bombX, bombY - i)); // Arriba
    }

    qDebug() << "Posición de la bomba: " << bombX << bombY;
    qDebug() << "Celdas afectadas: ";
    for (const QPoint& p : affectedCells) {
        qDebug() << p;
    }

    // Hacemos una copia de destructibleBlocks para evitar modificar el contenedor mientras lo recorremos
    QVector<QGraphicsRectItem*> blocksToDestroy = destructibleBlocks;

    for (auto* block : blocksToDestroy) {
        int blockX = 0;
        int blockY = 0;

        // Verificar si el bloque está en el mapa
        if (destructibleMap.contains(block)) {
            QGraphicsPixmapItem* value = destructibleMap.value(block);
            blockX = static_cast<int>(value->x()) / blockSize;
            blockY = static_cast<int>(value->y()) / blockSize;
        }

        qDebug() << "blockX: " << blockX << " blockY: " << blockY;

        // Si el bloque está en las celdas afectadas
        if (affectedCells.contains(QPoint(blockX, blockY))) {
            // Elimino el sprite asociado
            if (destructibleMap.contains(block)) {
                QGraphicsPixmapItem* sprite = destructibleMap.value(block);
                scene->removeItem(sprite);
                delete sprite;
                destructibleMap.remove(block);
            }

            // Elimino el bloque destructible
            scene->removeItem(block);
            delete block;
            destructibleBlocks.removeOne(block); // Modifico destructibleBlocks solo después de eliminarlo
        }
    }

    // Remuevo la bomba de la escena
    scene->removeItem(this);
    delete this;
}
