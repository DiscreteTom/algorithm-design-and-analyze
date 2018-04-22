# 作业四 最近点对

- 班级 2016211306
- 学号 2016211281
- 姓名 王景辉

## 目录

- [作业四 最近点对](#)
	- [目录](#)
	- [实验条件](#)
	- [实验结果](#)
	- [附1 源码(附件ShortestPoints.cpp)](#1-shortestpointscpp)
	- [附2 输出结果(附件closest.txt)](#2-closesttxt)

## 实验条件

- 已知1033个站点数据 包括
	- id          站点编号
	- longitude   经度
	- latitude    纬度
- 两种查询模式
	- 允许存在重合点
	- 不允许存在重合点

## 实验结果

- 允许存在重合点时
	- 最近距离为 0
		- 第一个点
			- id  568471
			- longitude 102.721
			- latitude  25.045600
		- 第二个点
			- id  568849
			- longitude 102.721
			- latitude  25.045600
- 不允许存在重合点时
	- 最近距离为 6
		- 第一个点
			- id  567389
			- longitude 102.741
			- latitude  25.053888
		- 第二个点
			- id  566803
			- longitude 102.741
			- latitude  25.053940
	- 次近距离为 57
		- 第一个点
			- id  567760
			- longitude 102.740
			- latitude  25.051339
		- 第二个点
			- id  567760
			- longitude 102.740
			- latitude  25.051853

## 附1 源码(附件[ShortestPoints.cpp](ShortestPoints.cpp))

	#include <iostream>
	#include <cmath>
	#include <vector>
	#include <fstream>
	#include <float.h>
	#include <iomanip>

	#define EARTH_RADIUS 6378.137
	#define FILE_NAME "points.txt"
	#define NUMBER 1033

	using namespace std;

	//==================== class Point ==================
	class Point{
	private:
		double lng;//longitude
		double lat;//latitude
		long m_id;

		double rad(double d) const {return d * M_PI / 180.0;}
	public:
		Point(double longitude = 0, double latitude = 0, long id = 0)//id = 0 is invalid
			: lng(longitude), lat(latitude), m_id(id){};

		//------ getter -----
		double longitude() const {return lng;}
		double latitude() const {return lat;}
		long id() const {return m_id;}

		double operator-(const Point & another) const ;//return distance
		bool operator==(const Point & another) const ;
	};

	double Point::operator-(const Point & another) const {
		// from doc 
		// double radLat1 = rad(lat);
		// double radLat2 = rad(another.lat);
		// double a = radLat1 - radLat2;
		// double b = rad(lng) - rad(another.lng);
		// double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));
		// s *= EARTH_RADIUS;
		// s = round(s * 10000) / 10000;
		// return s;

		// from ppt
		double radLat1 = rad(lat);
		double radLat2 = rad(another.lat);
		double radLng1 = rad(lng);
		double radLng2 = rad(another.lng);
		double s = acos(cos(radLat1) * cos(radLat2) * cos(radLng1 - radLng2) + sin(radLat1) * sin(radLat2));
		s *= EARTH_RADIUS;
		s = round(s * 1000);
		return s;
	}
	bool Point::operator==(const Point & another) const {
		return (lat == another.lat && lng == another.lng);
	}


	//================= functions =================
	double closest(const vector<Point *> & pointsX, const vector<Point *> & pointsY, int left, int right, Point & p1, Point & p2, bool allowSamePoint = true);
	int QuickSortPartition(vector<Point *> & a, int left, int right, bool modeLng);
	void quickSort(vector<Point *> & a, int left, int right, bool modeLng);
	void show(const vector<Point *> & a, int n);
	void del(vector<Point *> & points, long id);

	//=================== main =====================
	int main(){
		//input
		ifstream fin;
		fin.open(FILE_NAME);
		vector<Point> points;
		for (int i = 0; i < NUMBER; ++i){
			long id;
			double lng, lat;
			fin >> id >> lng >> lat;
			points.push_back(Point(lng, lat, id));
		}
		fin.close();

		//get pointsX and pointsY
		vector<Point *> pointsX;
		vector<Point *> pointsY;
		for (int i = 0; i < NUMBER; ++i){
			pointsX.push_back(&points[i]);
			pointsY.push_back(&points[i]);
		}
		quickSort(pointsX, 0, NUMBER - 1, true);
		quickSort(pointsY, 0, NUMBER - 1, false);

		// debug
		// show(pointsX, NUMBER);
		// cout << endl;
		// show(pointsY, NUMBER);
		// cout << endl;

		//get result
		Point p1;
		Point p2;
		double dis;
		ofstream fout;
		fout.open("closest.txt"); 

		//============== 1
		dis = closest(pointsX, pointsY, 0, NUMBER - 1, p1, p2);
		cout << "points at the same location is allowed" << endl;
		cout << "closest distance : " << dis << endl;
		cout << fixed;
		cout << "Point1 id : " << p1.id() << " longitude : " << setprecision(3) << p1.longitude() << " latitude : " << setprecision(6) << p1.latitude() << endl;
		cout << "Point2 id : " << p2.id() << " longitude : " << setprecision(3) << p2.longitude() << " latitude : " << setprecision(6) << p2.latitude() << endl << endl;
		cout.unsetf(ios::fixed);
		fout << "points at the same location is allowed" << endl;
		fout << "closest distance : " << dis << endl;
		fout << fixed;
		fout << "Point1 id : " << p1.id() << " longitude : " << setprecision(3) << p1.longitude() << " latitude : " << setprecision(6) << p1.latitude() << endl;
		fout << "Point2 id : " << p2.id() << " longitude : " << setprecision(3) << p2.longitude() << " latitude : " << setprecision(6) << p2.latitude() << endl << endl;
		fout.unsetf(ios::fixed);

		//============== 2
		dis = closest(pointsX, pointsY, 0, NUMBER - 1, p1, p2, false);
		cout << "points at the same location is allowed" << endl;
		cout << "closest distance : " << dis << endl;
		cout << fixed;
		cout << "Point1 id : " << p1.id() << " longitude : " << setprecision(3) << p1.longitude() << " latitude : " << setprecision(6) << p1.latitude() << endl;
		cout << "Point2 id : " << p2.id() << " longitude : " << setprecision(3) << p2.longitude() << " latitude : " << setprecision(6) << p2.latitude() << endl << endl;
		cout.unsetf(ios::fixed);
		fout << "points at the same location is allowed" << endl;
		fout << "closest distance : " << dis << endl;
		fout << fixed;
		fout << "Point1 id : " << p1.id() << " longitude : " << setprecision(3) << p1.longitude() << " latitude : " << setprecision(6) << p1.latitude() << endl;
		fout << "Point2 id : " << p2.id() << " longitude : " << setprecision(3) << p2.longitude() << " latitude : " << setprecision(6) << p2.latitude() << endl << endl;
		fout.unsetf(ios::fixed);

		//============== 3
		auto anotherPointsX = pointsX;
		auto anotherPointsY = pointsY;
		del(anotherPointsX, p1.id());
		del(anotherPointsY, p1.id());
		Point p1a, p2a;
		auto dis1 = closest(anotherPointsX, anotherPointsY, 0, NUMBER - 2, p1a, p2a, false);
		anotherPointsX = pointsX;
		anotherPointsY = pointsY;
		del(anotherPointsX, p2.id());
		del(anotherPointsY, p2.id());
		Point p1b, p2b;
		auto dis2 = closest(anotherPointsX, anotherPointsY, 0, NUMBER - 2, p1b, p2b, false);
		cout << "points at the same location is NOT allowed" << endl;
		fout << "points at the same location is NOT allowed" << endl;
		if (dis1 <= dis2){
			cout << "2nd closest distance : " << dis1 << endl;
			cout << fixed;
			cout << "Point1 id : " << p1a.id() << " longitude : " << setprecision(3) << p1a.longitude() << " latitude : " << setprecision(6) << p1a.latitude() << endl;
			cout << "Point2 id : " << p2a.id() << " longitude : " << setprecision(3) << p2a.longitude() << " latitude : " << setprecision(6) << p2a.latitude() << endl;
			cout.unsetf(ios::fixed);
			fout << "2nd closest distance : " << dis1 << endl;
			fout << fixed;
			fout << "Point1 id : " << p1a.id() << " longitude : " << setprecision(3) << p1a.longitude() << " latitude : " << setprecision(6) << p1a.latitude() << endl;
			fout << "Point2 id : " << p2a.id() << " longitude : " << setprecision(3) << p2a.longitude() << " latitude : " << setprecision(6) << p2a.latitude() << endl;
			fout.unsetf(ios::fixed);
		} else {
			cout << "2nd closest distance : " << dis2 << endl;
			cout << fixed;
			cout << "Point1 id : " << p1b.id() << " longitude : " << setprecision(3) << p1b.longitude() << " latitude : " << setprecision(6) << p1b.latitude() << endl;
			cout << "Point2 id : " << p2b.id() << " longitude : " << setprecision(3) << p2b.longitude() << " latitude : " << setprecision(6) << p2b.latitude() << endl;
			cout.unsetf(ios::fixed);
			fout << "2nd closest distance : " << dis2 << endl;
			fout << fixed;
			fout << "Point1 id : " << p1b.id() << " longitude : " << setprecision(3) << p1b.longitude() << " latitude : " << setprecision(6) << p1b.latitude() << endl;
			fout << "Point2 id : " << p2b.id() << " longitude : " << setprecision(3) << p2b.longitude() << " latitude : " << setprecision(6) << p2b.latitude() << endl;
			fout.unsetf(ios::fixed);
		}

		fout.close();
		system("pause");
	}

	//================ functions =================
	/* 
		p1 and p2 are receiver
		return distance -1 is invalid
		pointsX    all points sort by lng
		pointsY    points from left to right sort by lat
		pointsZ    points from left to right sort by lat
		left       index in pointsX
		right      index in pointsX
	*/
	double closest(const vector<Point *> & pointsX, const vector<Point *> & pointsY, int left, int right, Point & p1, Point & p2, bool allowSamePoint){
		//debug
		// show(pointsY, pointsY.size());
		// cout << endl;

		if (pointsY.size() <= 1){
			return DBL_MAX;
		} else if (pointsY.size() == 2){
			p1 = *pointsY[0];
			p2 = *pointsY[1];
			if (allowSamePoint){
				return p1 - p2;
			} else {
				if (p1 == p2){
					return DBL_MAX;
				} else {
					return p1 - p2;
				}
			}
		} else if (pointsY.size() == 3){
			bool flag1 = *pointsY[0] == *pointsY[1];
			bool flag2 = *pointsY[0] == *pointsY[2];
			bool flag3 = *pointsY[2] == *pointsY[1];
			if (!flag1 && !flag2 && !flag3){
				double dis1 = *pointsY[0] - *pointsY[1];
				double dis2 = *pointsY[0] - *pointsY[2];
				double dis3 = *pointsY[1] - *pointsY[2];

				if (dis1 <= dis2 && dis1 <= dis3){
					p1 = *pointsY[0];
					p2 = *pointsY[1];
					return dis1;
				} else if (dis2 <= dis1 && dis2 <= dis3){
					p1 = *pointsY[0];
					p2 = *pointsY[2];
					return dis2;
				} else {
					p1 = *pointsY[1];
					p2 = *pointsY[2];
					return dis3;
				}
			} else {
				if (allowSamePoint){
					if (flag1){
						p1 = *pointsY[0];
						p2 = *pointsY[1];
					} else if (flag2){
						p1 = *pointsY[0];
						p2 = *pointsY[2];
					} else {
						p1 = *pointsY[2];
						p2 = *pointsY[1];
					}
					return 0;
				} else {
					//not allowed same points
					if (flag1){
						if (*pointsY[0] == *pointsY[2]){
							return DBL_MAX;
						} else {
							p1 = *pointsY[0];
							p2 = *pointsY[2];
							return p1 - p2;
						}
					} else {
						if (*pointsY[0] == *pointsY[1]){
							return DBL_MAX;
						} else {
							p1 = *pointsY[0];
							p2 = *pointsY[1];
							return p1 - p2;
						}
					}
				}
			}
		} else {
			int middle = (left + right) / 2;//middle point according to lng

			//deal with pointsX[left : middle]
			vector<Point *> pointsY2;
			for (int i = 0; i < pointsY.size(); ++i){
				if (pointsY[i]->longitude() <= pointsX[middle]->longitude()){
					pointsY2.push_back(pointsY[i]);
					if (pointsY2.size() == middle - left + 1){
						break;
					}
				}
			}

			//debug
			// show(pointsY2, pointsY2.size());
			// cout << endl;

			Point p1Left, p2Left;
			double dis1 = closest(pointsX, pointsY2, left, middle, p1Left, p2Left, allowSamePoint);

			//deal with pointsX[middle + 1 : right]
			pointsY2.clear();
			for (int i = 0; i < pointsY.size(); ++i){
				if (pointsY[i]->longitude() >= pointsX[middle]->longitude()){
					pointsY2.push_back(pointsY[i]);
				}
			}
			while (pointsY2.size() > right - middle){
				pointsY2.erase(pointsY2.begin());
			}
			Point p1Right, p2Right;
			double dis2 = closest(pointsX, pointsY2, middle + 1, right, p1Right, p2Right, allowSamePoint);

			double result;
			if (dis1 > dis2){
				p1 = p1Right;
				p2 = p2Right;
			} else {
				p1 = p1Left;
				p2 = p2Left;
			}
			result = p1 - p2;
			//find (pointsX[middle]->lng - result <= lng <= pointsX[middle]->lng) as leftPoints
			//find (pointsX[middle]->lng < lng <= pointsX[middle]->lng + result) as rightPoints
			vector<Point *> leftPoints;
			vector<Point *> rightPoints;
			for (int i = 0; i < pointsY.size(); ++i){
				if (pointsY[i]->longitude() >= pointsX[middle]->longitude() && pointsY[i]->longitude() <= pointsX[middle]->longitude()){
					leftPoints.push_back(pointsY[i]);
				} else if (pointsY[i]->longitude() > pointsX[middle]->longitude() && pointsY[i]->longitude() <= pointsX[middle]->longitude() + result){
					rightPoints.push_back(pointsY[i]);
				}
			}

			//debug
			// cout << leftPoints.size() << endl;
			// cout << leftPoints.size() - 1 << endl;
			// cout << ((0 < leftPoints.size() - 1) ? 1 : 0) << endl;

			//maybe some points are at the same locate in leftPoints
			for (int i = 0; i + 1 < leftPoints.size(); ++i){
				for (int j = i + 1; j < leftPoints.size(); ++j){
					if (*leftPoints[i] == *leftPoints[j]){
						if (allowSamePoint){
							p1 = *leftPoints[i];
							p2 = *leftPoints[j];
							return 0;
						} else {
							leftPoints.erase(leftPoints.begin() + j);
							--j;
						}
					}
				}
			}

			//judge result
			if (!leftPoints.size() || !rightPoints.size()){
				return result;
			}
			//now leftPoints and rightPoints have item
			//find min in leftPoints and rightPoints
			int i = 0;//index in leftPoints
			int j = 0;//index in rightPoints
			bool flag = leftPoints[0]->latitude() < rightPoints[0]->latitude();//left point is judgement element?
			while (i < leftPoints.size() && j < rightPoints.size()){
				if (flag){
					while (j < rightPoints.size() && rightPoints[j]->latitude() - leftPoints[i]->latitude() <= result && ((i + 1 < leftPoints.size()) ? (rightPoints[j]->latitude() < leftPoints[i + 1]->latitude()) : true)){
						if (*(rightPoints[j]) - *(leftPoints[i]) < result){//new result
							p1 = *rightPoints[j];
							p2 = *leftPoints[i];
							result = p1 - p2;
						}
						++j;
					}
				} else {
					while (i < leftPoints.size() && leftPoints[i]->latitude() - rightPoints[j]->latitude() <= result && ((j + 1 < rightPoints.size()) ? (leftPoints[i]->latitude() < rightPoints[j + 1]->latitude()) : true)){
						if (*(rightPoints[j]) - *(leftPoints[i]) < result){//new result
							p1 = *rightPoints[j];
							p2 = *leftPoints[i];
							result = p1 - p2;
						}
						++i;
					}
				}
				flag = !flag;
			}

			return result;
		}
	}
	//if modeLng is true then sort according to longitude
	void quickSort(vector<Point *> & a, int left, int right, bool modeLng){
		if (left < right){
			int m = QuickSortPartition(a, left, right, modeLng);

			quickSort(a, left, m - 1, modeLng);
			quickSort(a, m + 1, right, modeLng);
		}
	}
	int QuickSortPartition(vector<Point *> & a, int left, int right, bool modeLng){
		int i = left, j = right + 1;
		while (true){
			if (modeLng){
				do {++i;}
				while (i < j && a[i]->longitude() < a[left]->longitude());
				while (a[--j]->longitude() > a[left]->longitude());
			} else {
				do {++i;}
				while (i < j && a[i]->latitude() < a[left]->latitude());
				while (a[--j]->latitude() > a[left]->latitude());
			}

			if (i >= j){
				break;
			}

			//swap a[i] a[j]
			auto t = a[i];
			a[i] = a[j];
			a[j] = t;
		}

		//swap a[left] a[j]
		auto t = a[left];
		a[left] = a[j];
		a[j] = t;
		return j;
	}
	void show(const vector<Point *> & a, int n){
		for (int i = 0; i < n; ++i){
			cout << "id : " << a[i]->id() << " longitude : " <<  a[i]->longitude() << " latitude : " << a[i]->latitude() << endl;
		}
	}
	void del(vector<Point *> & points, long id){
		for (int i = 0; i < points.size(); ++i){
			if (points[i]->id() == id){
				points.erase(points.begin() + i);
				return;
			}
		}
	}

## 附2 输出结果(附件[closest.txt](closest.txt))

	points at the same location is allowed
	closest distance : 0
	Point1 id : 568471 longitude : 102.721 latitude : 25.045600
	Point2 id : 568849 longitude : 102.721 latitude : 25.045600

	points at the same location is allowed
	closest distance : 6
	Point1 id : 567389 longitude : 102.741 latitude : 25.053888
	Point2 id : 566803 longitude : 102.741 latitude : 25.053940

	points at the same location is NOT allowed
	2nd closest distance : 57
	Point1 id : 567760 longitude : 102.740 latitude : 25.051339
	Point2 id : 567760 longitude : 102.740 latitude : 25.051853
