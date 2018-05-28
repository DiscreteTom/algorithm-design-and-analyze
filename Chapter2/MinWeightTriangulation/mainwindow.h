#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <math.h>
#include <QPaintEvent>

#define FILE_NAME_1 "E:\\Cpp\\algorithm-design-and-analyze\\Chapter2\\MinWeightTriangulation\\station1.txt"
#define FILE_NAME_2 "E:\\Cpp\\algorithm-design-and-analyze\\Chapter2\\MinWeightTriangulation\\station2.txt"
#define STATION_NUM_1 21
#define STATION_NUM_2 29
#define EARTH_RADIUS 6378.137

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	class Point{
	private:
		double lng;//longitude
		double lat;//latitude
		long m_id;

		double rad(double d) const {return d * M_PI / 180.0;}
	public:
		Point(double longitude = 0, double latitude = 0, long id = 0)//id = 0 is invalid
			: lng(longitude), lat(latitude), m_id(id){}

		//------ getter -----
		double longitude() const {return lng;}
		double latitude() const {return lat;}
		long id() const {return m_id;}

		double operator-(const Point & another) const ;//return distance
		bool operator==(const Point & another) const ;
	};

	int size;
	int ** middle;
	double ** result;
	QVector<Point> stations;

	void f(QVector<Point> points);
	double weight(const Point & p1, const Point & p2, const Point & p3);
	void getMiddlePoint();
protected:
	void paintEvent(QPaintEvent * ev);
};

#endif // MAINWINDOW_H
