#include <QApplication>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QPixmap>

#include "Map.h"
#include "Globals.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);

	QMainWindow* mainWindow = new QMainWindow();
	QGraphicsView* view = new QGraphicsView(mainWindow);
	mainWindow->setCentralWidget(view);

	QGraphicsScene * scene = new QGraphicsScene();
	view->setScene(scene);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			QGraphicsRectItem * path = new QGraphicsRectItem(j * 20, i * 20, 20, 20);
			path->setBrush(QBrush(Qt::black));
			scene->addItem(path);
			if (MapTemplate[i][j] == 1) {
				QGraphicsRectItem * wall = new QGraphicsRectItem(j * 20, i * 20, 20, 20);
				wall->setBrush(QBrush(Qt::darkBlue));
				scene->addItem(wall);
			} else if (MapTemplate[i][j] == 2) {
				QGraphicsEllipseItem* coin = new QGraphicsEllipseItem((j*20)+(20/2)-(6/2), (i*20)+(20/2)-(6/2), 6, 6);
				coin->setBrush(QBrush(Qt::magenta));
				scene->addItem(coin);
			} else if (MapTemplate[i][j] == 3) {
				QGraphicsEllipseItem * specialCoin = new QGraphicsEllipseItem(j*20 + 20/2 - 14/2, i * 20 + 20/2 - 14/2, 14, 14);
				specialCoin->setBrush(QBrush(Qt::darkMagenta));
				scene->addItem(specialCoin);
			} else if (MapTemplate[i][j] == 4) {
				QGraphicsEllipseItem * pacman = new QGraphicsEllipseItem(j*20 + 20/2 - 18/2, i * 20 + 20/2 - 18/2, 18, 18);
				pacman->setBrush(QBrush(Qt::yellow));
				scene->addItem(pacman);
			}
		}
	}

	scene -> setSceneRect(0, 0, MAP_WIDTH * 20, MAP_HEIGHT * 20);
	mainWindow->show();
	return app.exec();
}