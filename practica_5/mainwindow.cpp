#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include "QGraphicsRectItem"
#include <QRandomGenerator>
#include "bomb.h"
#include "enemy.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->view = new QGraphicsView(this); // Es lo que permite que los objetos se vean (muestra en pantalla lo que esta ocurriendo en la pantalla)
    this->scene = new QGraphicsScene(this); // Contiene los objetos que van a interactuar en la pantalla (eventos, etc..)

    view->setScene(scene);
    setCentralWidget(view);

    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    QPixmap fullImage(":/background/assets/NES - Bomberman - Playfield.png");

    QPixmap croppedMap = fullImage.copy(0, 0, fullImage.width(), fullImage.height() - 16);

    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(croppedMap);

    double scaleFactor = 2.0;
    background->setScale(scaleFactor);
    scene->addItem(background);

    setupMap();

    //añado a bomberman a la escena
    bomberman = new Bomberman(scene, 32, solidBlocks, destructibleBlocks);
    scene->addItem(bomberman);

    // Añadir los enemigos
    addEnemies(3);
}

void MainWindow::setupMap() {
    int rows = 13;
    int cols = 31;
    int blockSize = 32; // tamaño de cada bloque

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (row == 0 || row == rows - 1 || col == 0 || col == cols - 1) {
                QGraphicsRectItem* perimeterBlock = new QGraphicsRectItem(col * blockSize, row * blockSize, blockSize, blockSize);
                perimeterBlock->setBrush(Qt::NoBrush);
                perimeterBlock->setPen(Qt::NoPen);
                scene->addItem(perimeterBlock);
                solidBlocks.append(perimeterBlock);
            }
            else if ((row + 1) % 2  == 1 && (col + 1) % 2 == 1) {
                QGraphicsRectItem* solidBlock = new QGraphicsRectItem(col * blockSize, row * blockSize, blockSize, blockSize);
                solidBlock->setBrush(Qt::NoBrush);
                solidBlock->setPen(Qt::NoPen);
                scene->addItem(solidBlock);
                solidBlocks.append(solidBlock);
            }
        }
    }

    generateDesctructibleBlocks();
}

void MainWindow::generateDesctructibleBlocks() {
    int rows = 13;
    int cols = 31;
    int blockSize = 32;

    QPixmap blockSprite(":/sprites/assets/block.png");
    blockSprite = blockSprite.scaled(blockSize, blockSize);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (
                !((row + 1) % 2 == 1 && (col + 1) % 2 == 1) &&
                !(row == 0 || row == rows - 1 || col == 0 || col == cols - 1)
            ) {
                // Probabilidad del 40% de colocar un bloque
                if (QRandomGenerator::global()->bounded(100) < 30) {

                    QGraphicsRectItem* destructibleBlock = new QGraphicsRectItem(col * blockSize, row * blockSize, blockSize, blockSize);
                    destructibleBlock->setBrush(Qt::NoBrush);
                    destructibleBlock->setPen(Qt::NoPen);
                    scene->addItem(destructibleBlock);

                    QGraphicsPixmapItem* destructibleSprite = new QGraphicsPixmapItem(blockSprite);
                    destructibleSprite->setPos(col * blockSize, row * blockSize);
                    scene->addItem(destructibleSprite);

                    destructibleBlocks.append(destructibleBlock);
                    destructibleMap.insert(destructibleBlock, destructibleSprite); // se relaciona el bloque con el sprite correspondiente
                }
            }
        }
    }
}

void MainWindow::addEnemies(int count) {
    for (int i = 0; i < count; ++i) {
        Enemy* enemy = new Enemy(scene, 32, solidBlocks, destructibleBlocks);

        QVector<QPixmap> enemySprites = {
            QPixmap(":/enemy/assets/enemy_1.png").scaled(32, 32),
            QPixmap(":/enemy/assets/enemy_2.png").scaled(32, 32),
            QPixmap(":/enemy/assets/enemy_3.png").scaled(32, 32),
            QPixmap(":/enemy/assets/enemy_4.png").scaled(32, 32),
            QPixmap(":/enemy/assets/enemy_5.png").scaled(32, 32),
            QPixmap(":/enemy/assets/enemy_6.png").scaled(32, 32),
        };

        enemy->setSprites(enemySprites);

        // posicinar al enemigo de manera aleatoria
        int x = QRandomGenerator::global()->bounded(1, 30) * 32;
        int y = QRandomGenerator::global()->bounded(1, 12) * 32;

        if (enemy->canMoveTo(x, y)) {
            enemy->setPos(x, y);
            scene->addItem(enemy);
        } else {
            delete enemy; // si no puede moverse, eliminar el enemigo
            --i; // intentar de nuevo
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
        bomberman->move(0, -1); // hacia arriba
        break;
    case Qt::Key_S: // hacia abajo
        bomberman->move(0, 1);
        break;
    case Qt::Key_A: // hacia la izquierda
        bomberman->move(-1, 0);
        break;
    case Qt::Key_D: // hacia la derecha
        bomberman->move(1, 0);
        break;
    case Qt::Key_Space: {
        // Crea una bomba en la posicion actual de bomberman
        Bomb* bomb = new Bomb(scene, 32, destructibleBlocks, destructibleMap);
        bomb->setPos(bomberman->x(), bomberman->y());
        scene->addItem(bomb);
        break;
    }
    default:
        QMainWindow::keyPressEvent(event); // propago el evento si no es manejado
        break;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
