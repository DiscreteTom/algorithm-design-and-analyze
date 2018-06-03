#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPaintEvent>

// #define FILE_NAME "E:\\Cpp\\algorithm-design-and-analyze\\Chapter3\\MinSpanningTree\\matrix22.txt"
// #define STATION_NUM 22
#define FILE_NAME "E:\\Cpp\\algorithm-design-and-analyze\\Chapter3\\MinSpanningTree\\matrix42.txt"
#define STATION_NUM 42

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	int stationCode[STATION_NUM];
	double dis[STATION_NUM][STATION_NUM];//distance matrix
	bool edgeChecked[STATION_NUM][STATION_NUM];

	void k();
	void p();

protected:
	void paintEvent(QPaintEvent * ev);
};

#endif // MAINWINDOW_H
