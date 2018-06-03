#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <qmath.h>
#include <QSet>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	//input
	QFile file(FILE_NAME);
	file.open(QFile::ReadOnly | QFile::Text);
	QTextStream fin(&file);
	for (int i = 0; i < STATION_NUM; ++i){
		fin >> stationCode[i];
	}
	for (int i = 0; i < STATION_NUM; ++i){
		fin >> dis[i][i];//read station code
		for (int j = 0; j < STATION_NUM; ++j){
			fin >> dis[i][j];
		}
	}
	file.close();

	k();//Kruskal
	p();//Prim

	showMaximized();
}

MainWindow::~MainWindow()
{

}

void MainWindow::k()
{
	//! algorithm K(Kruskal) to get minimun spanning tree

	bool inSet[STATION_NUM];
	for (int i = 0; i < STATION_NUM; ++i){//init
		inSet[i] = false;
		for (int j = 0; j < STATION_NUM; ++j){
			edgeChecked[i][j] = false;
		}
	}

	QVector<QSet<int>> sets;
	while (!sets.size() || sets[0].count() != STATION_NUM){
		//! find the min edge
		double min = -1;
		int from;//min edge end point
		int to;//min edge end point
		for (int i = 0; i < STATION_NUM; ++i){
			for (int j = i; j < STATION_NUM; ++j){
				//traverse edge
				if (dis[i][j] != -1 && !edgeChecked[i][j]){
					if (!inSet[i] || !inSet[j]){
						if (min == -1 || min > dis[i][j]){
							min = dis[i][j];
							from = i;
							to = j;
						}
					} else {
						//i and j are both in set
						//judge whether they are in the same sets
						int iInWhichSet = -1;
						int jInWhichSet = -1;
						for (int ii = 0; ii < sets.size(); ++ii){
							if (sets[ii].contains(i)){
								iInWhichSet = ii;
							}
							if (sets[ii].contains(j)){
								jInWhichSet = ii;
							}
						}
						if (iInWhichSet != -1 && jInWhichSet != -1 && iInWhichSet == jInWhichSet){
							//same sets, invalid
						} else {
							if (min == -1 || min > dis[i][j]){
								min = dis[i][j];from = i;
								to = j;
							}
						}
					}
				}
			}
		}
		edgeChecked[from][to] = edgeChecked[to][from] = true;
		inSet[from] = inSet[to] = true;

		//maybe merge sets or get new set
		int fromInWhichSet = -1;
		int toInWhichSet = -1;
		for (int i = 0; i < sets.size(); ++i){
			if (sets[i].contains(from)){
				fromInWhichSet = i;
			}
			if (sets[i].contains(to)){
				toInWhichSet = i;
			}
		}
		if (fromInWhichSet == -1 && toInWhichSet == -1){
			sets.push_back(QSet<int>());
			(sets.end() - 1)->insert(from);
			(sets.end() - 1)->insert(to);
		} else if (fromInWhichSet == -1){
			sets[toInWhichSet].insert(from);
		} else if (toInWhichSet == -1){
			sets[fromInWhichSet].insert(to);
		} else {
			//in different sets
			sets[fromInWhichSet] += sets[toInWhichSet];
			sets.remove(toInWhichSet);
		}
	}

	//output
	double result = 0;
	for (int i = 0; i < STATION_NUM; ++i){
		for (int j = i; j < STATION_NUM; ++j){
			if (edgeChecked[i][j]){
				result += dis[i][j];
			}
		}
	}
	qDebug() << "(K)Min weight:";
	qDebug() << result;
}

void MainWindow::p()
{
	//! algorithm P(Prim) to get minimum spanning tree
	bool inSet[STATION_NUM];
	for (int i = 0; i < STATION_NUM; ++i){
		inSet[i] = false;
		for (int j = 0; j < STATION_NUM; ++j){
			edgeChecked[i][j] = false;
		}
	}
	inSet[0] = true;
	bool flag = true;//inSet[i] == true for all i, flag = false

	while (flag){
		//! find min edge in inSet
		double min = -1;
		int from, to;//end points of min edge
		for (int i = 0; i < STATION_NUM; ++i){
			if (inSet[i]){
				for (int j = 0; j < STATION_NUM; ++j){
					if (!inSet[j] && !edgeChecked[i][j] && dis[i][j] != -1){
						if (min == -1 || min > dis[i][j]){
							min = dis[i][j];
							from = i;
							to = j;
						}
					}
				}
			}
		}
		inSet[from] = inSet[to] = true;
		edgeChecked[from][to] = edgeChecked[to][from] = true;

		//! judge flag
		flag = false;
		for (int i = 0; i < STATION_NUM; ++i){
			if (!inSet[i]){
				flag = true;
				break;
			}
		}
	}

	//output
	qDebug() << "(P)Min weight:";
	double result = 0;
	for (int i = 0; i < STATION_NUM; ++i){
		for (int j = i; j < STATION_NUM; ++j){
			if (edgeChecked[i][j]){
				result += dis[i][j];
			}
		}
	}
	qDebug() << result;
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
	//suppose that all points are on a circle whose radius is 400
	//suppose the center of the circle is (800,500)
	QPainter painter(this);
	const int centerX = 800;
	const int centerY = 500;
	const int radius = 400;

	//! draw all path
	painter.setPen(QPen(Qt::black, 4));
	for (int i = 0; i < STATION_NUM; ++i){
		for (int j = 0; j < STATION_NUM; ++j){
			if (dis[i][j] != -1){
				double x1 = cos(6.28 * i / STATION_NUM) * radius + centerX;
				double y1 = sin(6.28 * i / STATION_NUM) * radius + centerY;
				double x2 = cos(6.28 * j / STATION_NUM) * radius + centerX;
				double y2 = sin(6.28 * j / STATION_NUM) * radius + centerY;
				painter.drawLine(x1, y1, x2, y2);
			}
		}
	}

	//! draw chosen path
	painter.setPen(QPen(Qt::red, 4));
	for (int i = 0; i < STATION_NUM; ++i){
		for (int j = 0; j < STATION_NUM; ++j){
			if (edgeChecked[i][j]){
				double x1 = cos(6.28 * i / STATION_NUM) * radius + centerX;
				double y1 = sin(6.28 * i / STATION_NUM) * radius + centerY;
				double x2 = cos(6.28 * j / STATION_NUM) * radius + centerX;
				double y2 = sin(6.28 * j / STATION_NUM) * radius + centerY;
				painter.drawLine(x1, y1, x2, y2);
			}
		}
	}
}
