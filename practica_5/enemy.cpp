#include "enemy.h"
#include "bomberman.h"
#include <QRandomGenerator>
#include <QPropertyAnimation>

Enemy::Enemy(QGraphicsScene* scene, int blockSize, QVector<QGraphicsRectItem*> solidBlocks, QVector<QGraphicsRectItem*> destructibleBlocks)
    : scene(scene), blockSize(blockSize), solidBlocks(solidBlocks), currentFrameIndex(0), destructibleBlocks(destructibleBlocks)
{
    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Enemy::moveRandomly);
    movementTimer->start(500); // se mueve cada 500ms
}

void Enemy::setSprites(const QVector<QPixmap>& sprites) {
    this->sprites = sprites;
    setPixmap(sprites[currentFrameIndex]);
}

void Enemy::moveRandomly() {
    // Se genera un movimiento aleatorio: -1, 0, o 1 en x o y
    int dx = QRandomGenerator::global()->bounded(3) - 1;
    int dy = QRandomGenerator::global()->bounded(3) - 1;

    if (dx != 0 || dy != 0) {
        int newX = x() + dx * blockSize;
        int newY = y() + dy * blockSize;

        if (canMoveTo(newX, newY)) {
            setPos(newX, newY);

            // Alternar los sprites
            currentFrameIndex = (currentFrameIndex + 1) % sprites.size();
            setPixmap(sprites[currentFrameIndex]);
        }
    }
}

bool Enemy::canMoveTo(int x, int y) {
    QRectF newRect(x, y, blockSize, blockSize);

    // Verifico colisiones con los bloques solidos
    for (auto* block : solidBlocks) {
        if (newRect.intersects(block->boundingRect())) {
            return false;
        }
    }

    // Verifico colisiones con los bloques destructibles
    for (auto* desBlock : destructibleBlocks) {
        // Verifico si el bloque sigue existiendo en la escena
        if (!scene->items().contains(desBlock)) {
            continue; // Saltar el bloque si ya fue eliminado
        }

        if (newRect.intersects(desBlock->boundingRect())) {
            return false;
        }
    }

    // Me aseguro de que no salga de los limites de la escena
    QRectF sceneBounds = scene->sceneRect();
    return sceneBounds.contains(newRect);
}
