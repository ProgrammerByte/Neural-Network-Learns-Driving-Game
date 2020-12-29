#include "Track.h"
#include "Car.h"
#include "maths.h"
#include "Graphics2D.h"

#include <vector>

//#include <iostream>

using namespace std;

Track::Track() {
	this->coords = { {{488,463},{486,123},{455,74},{409,59},{360,72},{327,116},{297,234},{280,254},{188,254},{174,237},{174,205},{236,135},{244,104},{227,67},{196,54},{88,55},{52,69},{36,90},{26,119},{24,298},{37,326},{64,342},{326,343},{340,355},{343,370},{328,381},{300,382},{238,367},{144,367},{116,374},{41,444},{28,479},{41,522},{83,534},{114,532},{223,481},{253,454},{271,452},{315,488},{386,517},{457,509},{488,463}},
					 {{448,433},{448,160},{432,127},{402,120},{363,136},{329,267},{299,292},{177,293},{148,280},{135,252},{134,188},{200,106},{190,95},{99,95},{73,105},{61,139},{59,272},{69,295},{361,303},{409,334},{413,383},{385,414},{342,417},{225,388},{154,387},{130,395},{83,445},{83,467},{102,476},{185,459},{253,428},{306,433},{389,472},{433,468},{448,433}}};
	for (int i = 0; i < coords.size(); i++) {
		for (int x = 0; x < coords[i].size(); x++) {
			coords[i][x][0] = ((float)coords[i][x][0] / 250) - 1;
			coords[i][x][1] = ((float)coords[i][x][1] / 250) - 1.15;
		}
	}
}

void Track::render(Graphics2D* engine) {
	for (int i = 0; i < coords.size(); i++) {
		for (int x = 0; x < coords[i].size() - 1; x++) {
			engine->line(coords[i][x][0], coords[i][x][1], coords[i][x + 1][0], coords[i][x + 1][1]);
		}
	}
}

bool Track::lineColliding(vector<float> p1, vector<float> d1, vector<float> p2, vector<float> d2, float* dist) {
	float det = (d2[0] * d1[1]) - (d1[0] * d2[1]);
	if (det == 0) {
		return false;
	}
	det = (float)1 / det;
	float lambda = ((d2[1] * (p1[0] - p2[0])) + (d2[0] * (p2[1] - p1[1]))) * det;
	if (dist != nullptr) {
		*dist = lambda;
	}
	if (lambda > 1 || lambda < 0) {
		return false;
	}
	lambda = ((d1[1] * (p1[0] - p2[0])) + (d1[0] * (p2[1] - p1[1]))) * det;
	if (lambda > 1 || lambda < 0) {
		return false;
	}
	return true;
}

bool Track::isColliding(Car* car) {
	int vertex1, vertex2;
	float minX, minY, maxX, maxY;
	vector<vector<float>> boundingBox = car->getBoundingBox();
	vector<vector<float>> carCoords = car->getCoords();
	vector<float> d1;
	vector<float> d2;
	for (int i = 0; i < coords.size(); i++) {
		for (int x = 0; x < coords[i].size() - 1; x++) {
			if (coords[i][x][0] < coords[i][x + 1][0]) { //bounding box for each line segment
				minX = coords[i][x][0];
				maxX = coords[i][x + 1][0];
			}
			else {
				minX = coords[i][x + 1][0];
				maxX = coords[i][x][0];
			}
			if (coords[i][x][1] < coords[i][x + 1][1]) {
				minY = coords[i][x][1];
				maxY = coords[i][x + 1][1];
			}
			else {
				minY = coords[i][x + 1][1];
				maxY = coords[i][x][1];
			}

			if (minX <= boundingBox[1][0] && maxX >= boundingBox[0][0] && minY <= boundingBox[1][1] && maxY >= boundingBox[0][1]) { //bounding box check
				d2 = {coords[i][x + 1][0] - coords[i][x][0], coords[i][x + 1][1] - coords[i][x][1]};
				for (int a = 0; a < 4; a++) { //collision logic
					vertex1 = a;
					vertex2 = (a + 1) % 4;
					d1 = {carCoords[vertex2][0] - carCoords[vertex1][0], carCoords[vertex2][1] - carCoords[vertex1][1]};
					if (lineColliding(carCoords[vertex1], d1, coords[i][x], d2, nullptr) == true) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

vector<vector<vector<float>>> Track::getCoords() {
	return this->coords;
}

Track::~Track() {}