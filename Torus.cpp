#include "Torus.h"

#define M_PI 3.14159265358979323846

void Torus::draw() {
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslated(x, y, z);

	int i, j, k;
	double s, t, x, y, z, twopi;

	twopi = 2 * M_PI;
	for (i = 0; i < numc; i++) {
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= numt; j++) {
			for (k = 1; k >= 0; k--) {
				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = (outerRadius + innerRadius * cos(s * twopi / numc)) * cos(t * twopi / numt);
				y = (outerRadius + innerRadius * cos(s * twopi / numc)) * sin(t * twopi / numt);
				z = innerRadius * sin(s * twopi / numc);
				glNormal3d((innerRadius * cos(s * twopi / numc)) * cos(t * twopi / numt), (innerRadius * cos(s * twopi / numc)) * sin(t * twopi / numt), innerRadius * sin(s * twopi / numc));
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
	glPopMatrix();
}