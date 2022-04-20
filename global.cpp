#include "global.h"
#include "modelerdraw.h"
void drawFace(vector<vector<double>> points) {
	vector<double> pt1 = points[0];

	vector<double> pt2 = points[1];
#define mid(a,b) (a+b)/2.0
	vector<double> mid = { mid(pt1[0],pt2[0]),mid(pt1[1],pt2[1]),mid(pt1[2],pt2[2]) };
	for (int i = 0;i < points.size();i++) {
		vector<double> next;
		if (i + 1 >= points.size()) {
			next = points[0];
		}
		else {
			next = points[i + 1];
		}
		vector<double> pt = points[i];
		drawTriangle(pt[0], pt[1], pt[2], mid[0], mid[1], mid[2], next[0], next[1], next[2]);
	}


}