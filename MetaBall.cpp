#include "MetaBall.h"
#include "modelerview.h"
#include <iostream>
#include "math.h"
#include "global.h"
#define ABS(x) ((x)<0 ? (-x) : (x))
#define   verticeValueCal(x1,y1,z1,x2,y2,z2) \
 ((x1==x2&& y1==y2 &&z1==z2) ?  INFINITY: 1 / ((x1-x2)*(x1-x2) +(y1-y2)*(y1-y2)+ (z1-z2)*(z1-z2)))
XYZ InterpretVec(double iso, XYZ p1, XYZ p2, double valp1, double valp2)
{
    XYZ p;
    p.x = p1.x + (iso - valp1) / (valp2 - valp1) * (p2.x - p1.x);
    p.y = p1.y + (iso - valp1) / (valp2 - valp1) * (p2.y - p1.y);
    p.z = p1.z + (iso - valp1) / (valp2 - valp1) * (p2.z - p1.z);
    return(p);
}
MetaBall::MetaBall(int x, int y, int z, float r,char* label) :Component(METABALL) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->radius = r;
	this->thetax = 0;
	xoffset = 0;
	yoffset = 0;
	zoffset = 0;
	thetax = 0;
	thetay = 0;
	thetaz = 0;
	thetaxOff = 0;
	thetayOff = 0;
	thetazOff = 0;
}

void MetaBall::polygonizeFunc(double iso, Cell grid)
{
    
    int cindex;
    XYZ vList[12];
    cindex = 0;
    for (int i = 0;i < 8;i++) {
        if (grid.val[i] < iso) cindex |=(int) pow(2,i);
    }
    if (edgeTable[cindex] == 0)
        return;
    if (edgeTable[cindex] & 1)vList[0] = InterpretVec(iso, grid.p[0], grid.p[1], grid.val[0], grid.val[1]);
    if (edgeTable[cindex] & 2)vList[1] =  InterpretVec(iso, grid.p[1], grid.p[2], grid.val[1], grid.val[2]);
    if (edgeTable[cindex] & 4)  vList[2] = InterpretVec(iso, grid.p[2], grid.p[3], grid.val[2], grid.val[3]);
    if (edgeTable[cindex] & 8) vList[3] =  InterpretVec(iso, grid.p[3], grid.p[0], grid.val[3], grid.val[0]);
    if (edgeTable[cindex] & 16)  vList[4] =InterpretVec(iso, grid.p[4], grid.p[5], grid.val[4], grid.val[5]);
    if (edgeTable[cindex] & 32) vList[5] =InterpretVec(iso, grid.p[5], grid.p[6], grid.val[5], grid.val[6]);
    if (edgeTable[cindex] & 64)vList[6] =InterpretVec(iso, grid.p[6], grid.p[7], grid.val[6], grid.val[7]);
    if (edgeTable[cindex] & 128) vList[7] = InterpretVec(iso, grid.p[7], grid.p[4], grid.val[7], grid.val[4]);
    if (edgeTable[cindex] & 256)vList[8] = InterpretVec(iso, grid.p[0], grid.p[4], grid.val[0], grid.val[4]);
    if (edgeTable[cindex] & 512)vList[9] =InterpretVec(iso, grid.p[1], grid.p[5], grid.val[1], grid.val[5]);
    if (edgeTable[cindex] & 1024)vList[10] =   InterpretVec(iso, grid.p[2], grid.p[6], grid.val[2], grid.val[6]);
    if (edgeTable[cindex] & 2048)vList[11] =  InterpretVec(iso, grid.p[3], grid.p[7], grid.val[3], grid.val[7]);
    for (int i = 0;triTable[cindex][i] != -1;i += 3) {
        drawTriangle(
            vList[triTable[cindex][i]].x, vList[triTable[cindex][i]].y, vList[triTable[cindex][i]].z,
            vList[triTable[cindex][i + 1]].x, vList[triTable[cindex][i + 1]].y, vList[triTable[cindex][i + 1]].z,
            vList[triTable[cindex][i + 2]].x, vList[triTable[cindex][i + 2]].y, vList[triTable[cindex][i + 2]].z
        );
    }
 
}
void MetaBall::drawBall(const double r) {

    double threshold = verticeValueCal(-0.6, 0, 0, 1.12, 0, 0) + verticeValueCal(0.6, 0, 0, 1.12, 0, 0);
    double size = VAL(RESOLUTIONMETABALL);
    double border = 0.21;
    for (double x = 0; x <= 2*r+2*border; x += size) {
            for (double y =0; y <= 2*r + 2*border; y += size) {
                for (double z = 0; z <= 2 * r + 2 * border; z += size) {
                    XYZ points[8] = {
                        { x - r - border, y - r - border, z - r - border},
                        { x - r - border + size, y - r - border, z - r - border},
                        { x - r - border + size, y - r - border, z + size - r - border},
                        { x - r - border, y - r - border, z + size - r - border},
                        { x - r - border, y - r - border + size, z - r - border},
                        { x - r - border + size, y - r - border + size, z - r - border},
                        { x - r - border + size, y - r - border + size, z + size - r - border},
                        { x - r - border, y + size - r - border, z - r - border + size }
                    };
                    double values[8];
                    for (int i = 0; i < 8; i++) {
                        values[i] = verticeValueCal(-0.6,0,0,points[i].x, points[i].y, points[i].z) + verticeValueCal(0.6, 0, 0, points[i].x, points[i].y, points[i].z);
                    }
                    Cell grid; 
                    grid =  std::pair<XYZ*,double*>(points, values);
                    polygonizeFunc(threshold, grid);
                }
            }
        }
    

}
void MetaBall::draw() {
    //setAmbientColor(.1f, .1f, .1f);
    //setDiffuseColor(COLOR_RED);
    //glPushMatrix();
    //glTranslated(x,y, z);
    //glScaled(radius, radius, radius);
    //drawBall(1);
    //glPopMatrix();
    thetay = 90;
    GeneralDraw(COLOR_RED, glScaled(radius, radius, radius); drawBall(1););
}