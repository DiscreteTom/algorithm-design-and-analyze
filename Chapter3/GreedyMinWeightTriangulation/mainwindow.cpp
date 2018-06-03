#include "mainwindow.h"
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPainter>
#include <QStack>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	showMaximized();

	//input
//	QFile file1(FILE_NAME_1);
//	file1.open(QFile::ReadOnly | QFile::Text);
//	QTextStream fin1(&file1);
//	for (int i = 0; i < STATION_NUM_1; ++i){
//		int id;
//		double lng, lat;
//		fin1 >> id >> lng >> lat;
//		stations.push_back(Point(lng, lat, id));
//	}
//	file1.close();
	QFile file2(FILE_NAME_2);
	file2.open(QFile::ReadOnly | QFile::Text);
	QTextStream fin2(&file2);
	for (int i = 0; i < STATION_NUM_2; ++i){
		int id;
		double lng, lat;
		fin2 >> id >> lng >> lat;
		stations.push_back(Point(lng, lat, id));
	}
	file2.close();

	//---------------------------------- get memory
	size = stations.size();
	middle = new int*[size];
	for (int i = 0; i < size; ++i){
		middle[i] = new int[size];
	}

	//MinWeightTriangular
	qDebug("result2:");
	f(stations);
}

MainWindow::~MainWindow()
{
	//free memory
	for (int i = 0; i < size; ++i){
		delete [] middle[i];
	}
	delete [] middle;
}

void MainWindow::f(QVector<MainWindow::Point> points)
{
	//init middle
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			middle[i][j] = -1;
		}
	}
	result = 0;

	//! use stack instead of recursion
	QStack<int> startStack;
	QStack<int> endStack;
	startStack.push_back(0);
	endStack.push_back(size - 1);
	while (startStack.size()){
		int start = startStack.pop();
		int end = endStack.pop();
		if (end - start > 2){
			//! first situation, middle = start + 1
			int min = points[start + 1] - points[end];
			middle[start][end] = start + 1;
			//! last situation, middle = end - 1
			int t = points[start] - points[end - 1];
			if (min > t){
				min = t;
				middle[start][end] = end - 1;
			}
			//! other situation
			for (int i = start + 2; i < end - 1; ++i){
				int tt = (points[start] - points[i]) + (points[i] - points[end]);
				if (min > tt){
					min = tt;
					middle[start][end] = i;
				}
			}
			//! push stack
			startStack.push_back(start);
			endStack.push_back(middle[start][end]);
			startStack.push_back(middle[start][end]);
			endStack.push_back(end);
			result += weight(points[start], points[end], points[middle[start][end]]);
		} else if (end - start == 2){
			result += weight(points[start], points[start + 1], points[end]);
		}
	}
	qDebug() << result;
}

double MainWindow::weight(const MainWindow::Point &p1, const MainWindow::Point &p2, const MainWindow::Point &p3)
{
	return (p1 - p2) + (p1 - p3) + (p2 - p3);
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
	//! DO NOT CHANGE ANY CONST NUMBER HERE
	//------------------------------ draw path
	QPainter painter(this);
	painter.setPen(QPen(Qt::black, 4));
	for (int i = 0; i < size - 1; ++i){
		painter.drawLine((stations[i].longitude() - 102.67) * 5000 + 500, (stations[i].latitude() - 24.95) * 5000 + 100, (stations[i + 1].longitude() - 102.67) * 5000 + 500, (stations[i + 1].latitude() - 24.95) * 5000 + 100);
	}
	painter.setPen(QPen(Qt::red,4));
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if (middle[i][j] != -1){
				if (i != middle[i][j] - 1)
					painter.drawLine((stations[i].longitude() - 102.67) * 5000 + 500, (stations[i].latitude() - 24.95) * 5000 + 100, (stations[middle[i][j]].longitude() - 102.67) * 5000 + 500, (stations[middle[i][j]].latitude() - 24.95) * 5000 + 100);
				if (j != middle[i][j] + 1)
					painter.drawLine((stations[j].longitude() - 102.67) * 5000 + 500, (stations[j].latitude() - 24.95) * 5000 + 100, (stations[middle[i][j]].longitude() - 102.67) * 5000 + 500, (stations[middle[i][j]].latitude() - 24.95) * 5000 + 100);
			}
		}
	}
}

double MainWindow::Point::operator-(const MainWindow::Point &another) const
{
	double radLat1 = rad(lat);
	double radLat2 = rad(another.lat);
	double radLng1 = rad(lng);
	double radLng2 = rad(another.lng);
	double s = acos(cos(radLat1) * cos(radLat2) * cos(radLng1 - radLng2) + sin(radLat1) * sin(radLat2));
	s *= EARTH_RADIUS;
	s = round(s * 5000 + 500);
	return s;
}

bool MainWindow::Point::operator==(const MainWindow::Point &another) const
{
	return (lat == another.lat && lng == another.lng);
}
