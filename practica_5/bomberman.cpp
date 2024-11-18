#include "bomberman.h"

Bomberman::Bomberman(QGraphicsScene* scene, int blockSize, QVector<QGraphicsRectItem*> solidBlocks, QVector<QGraphicsRectItem*> destructibleBlocks)
    : scene(scene), blockSize(blockSize), solidBlocks(solidBlocks), destructibleBlocks(destructibleBlocks)
{

    spritesUp = {
        QPixmap(":/bomberman/assets/bomberman_up_1.png").scaled(blockSize, blockSize),
        QPixmap(":/bomberman/assets/bomberman_up_2.png").scaled(blockSize, blockSize),
        QPixmap(":/bomberman/assets/bomberman_up_2.png").scaled(blockSize, blockSize),
    };

    spritesDown = {
        QPixmap(":/bomberman/assets/Bomberman_down_1.png").scaled(blockSize, blockSize),
        QPixmap(":/bomberman/assets/Bomberman_down_2.png").scaled(blockSize, blockSize),
        QPixmap(":/bomberman/assets/Bomberman_down_3.png").scaled(blockSize, blockSize),
    };

    spritesLeft = {
        QPixmap(":/bomberman/assets/bomberman_left_1.png").scaled(blockSize, blockSize),
        QPixmap(":/bomberman/assets/bomberman_left_2.png").scaled(blockSize, blockSize),
        QPixmap(":/bomberman/assets/bomberman_left_3.png").scaled(blockSize, blockSize),
    };

    spritesRight = {
        QPixmap(":/bomberman/assets/bomberman_right_1.png").scaled(blockSize, blockSize),
        QPixmap(":/bomberman/assets/bomberman_right_2.png").scaled(blockSize, blockSize),
        QPixmap(":/bomberman/assets/bomberman_right_3.png").scaled(blockSize, blockSize),
    };

    setPixmap(spritesDown[currentFrameIndex]);
    setPos(blockSize, blockSize);
}

void Bomberman::move(int dx, int dy) {
    int newX = x() + dx * blockSize;
    int newY = y() + dy * blockSize;

    if (canMoveTo(newX, newY)) {

        if (dx == 1 && dy == 0) {
            currentFrameIndex = (currentFrameIndex + 1) % spritesRight.size();
            setPixmap(spritesRight[currentFrameIndex]);
        } else if (dx == -1 && dy == 0) {
            currentFrameIndex = (currentFrameIndex + 1) % spritesLeft.size();
            setPixmap(spritesLeft[currentFrameIndex]);
        } else if (dx == 0 && dy == 1) {
            currentFrameIndex = (currentFrameIndex + 1) % spritesDown.size();
            setPixmap(spritesDown[currentFrameIndex]);
        } else if (dx == 0 && dy == -1) {
            currentFrameIndex = (currentFrameIndex + 1) % spritesUp.size();
            setPixmap(spritesUp[currentFrameIndex]);
        }

        setPos(newX, newY);
    }
}

bool Bomberman::canMoveTo(int x, int y) {
    // Creo un nuevo rectangulo de colision
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

