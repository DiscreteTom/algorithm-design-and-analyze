#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPainter>
#include <QStack>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

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
	result = new double*[size];
	middle = new int*[size];
	for (int i = 0; i < size; ++i){
		result[i] = new double[size];
		middle[i] = new int[size];
	}

	//MinWeightTriangular
//	qDebug("Stations1:");
//	f(stations);
	qDebug("Stations2:\n");
	f(stations);
}

MainWindow::~MainWindow()
{
	//free memory
	for (int i = 0; i < size; ++i){
		delete [] result[i];
		delete [] middle[i];
	}
	delete [] result;
	delete [] middle;

	delete ui;
}

void MainWindow::f(QVector<MainWindow::Point> points)
{
	//init middle
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			middle[i][j] = -1;
		}
	}

	//get min weight
	for (int i = 0; i < size; ++i){//weight of a point
		result[i][i] = 0;
	}
	for (int i = 0; i < size - 1; ++i){//weight of a line
		result[i][i + 1] = points[i + 1] - points[i];
	}
	for (int i = 0; i < size - 2; ++i){//weight of a triangle
		result[i][i + 2] = weight(points[i], points[i + 1], points[i + 2]);
	}
	for (int i = 4; i <= size; ++i){//other
		//! i is the number of points in the part of this graph
		for (int j = 0; j < size - i + 1; ++j){
			//! j is the start point, from points[j] to points[j + i - 1]
			//first situation, middle point = points[j + 1]
			result[j][j + i - 1] = result[j + 1][j + i - 1] + weight(points[j + 1], points[j], points[j + i - 1]);
			middle[j][j + i - 1] = j + 1;
			for (int k = j + 2; k < j + i - 2; ++k){
				//! k is the middle point
				double t = result[j][j + 2] + result[j + i - 3][j + i - 1] + weight(points[j], points[k], points[j + i - 1]);
				if (t < result[j][j + i - 1]){
					result[j][j + i - 1] = t;
					middle[j][j + i - 1] = k;
				}
			}
			//final situation, middle point = points[j + i - 2]
			double t = result[j][j + i - 2] + weight(points[j], points[j + i - 2], points[j + i - 1]);
			if (t < result[j][j + i - 1]){
				result[j][j + i - 1] = t;
				middle[j][j + i - 1] = j + i - 2;
			}
		}
	}
	qDebug() << "MinWeight : " << result[0][size - 1] << endl;
	getMiddlePoint();
}

double MainWindow::weight(const MainWindow::Point &p1, const MainWindow::Point &p2, const MainWindow::Point &p3)
{
	return (p1 - p2) + (p1 - p3) + (p2 - p3);
}

void MainWindow::getMiddlePoint()
{
	//get a new array and init
	int ** mid = new int*[size];
	for (int i = 0; i < size; ++i){
		mid[i] = new int[size];
		for (int j = 0; j < size; ++j){
			mid[i][j] = -1;
		}
	}
	//use stack to simulate recursion
	QStack<int> startStack;
	QStack<int> endStack;
	//stack init
	startStack.push_back(0);
	endStack.push_back(size - 1);
	//get new middle array
	while (startStack.size()){
		int start = startStack.pop();
		int end = endStack.pop();
		mid[start][end] = middle[start][end];
		if (middle[start][end] == -1){
			qDebug() << "!!!wrong calculate";
		}
		if (middle[start][end] - start > 2){
			startStack.push_back(start);
			endStack.push_back(middle[start][end]);
		}
		if (end - middle[start][end] > 2){
			startStack.push_back(middle[start][end]);
			endStack.push_back(end);
		}
	}
	//delete old middle array
	for (int i = 0; i < size; ++i){
		delete [] middle[i];
	}
	delete [] middle;
	//steal memory
	middle = mid;
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
				painter.drawLine((stations[i].longitude() - 102.67) * 5000 + 500, (stations[i].latitude() - 24.95) * 5000 + 100, (stations[middle[i][j]].longitude() - 102.67) * 5000 + 500, (stations[middle[i][j]].latitude() - 24.95) * 5000 + 100);
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
