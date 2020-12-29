#pragma once

#include "Graphics2D.h"
//#include "Car.h"

class Car;

#include <vector>

class Track {
public:
	Track();
	std::vector<std::vector<std::vector<float>>> coords;
	void render(Graphics2D* engine);
	bool isColliding(Car* car);
	bool lineColliding(std::vector<float> p1, std::vector<float> d1, std::vector<float> p2, std::vector<float> d2, float* dist);
	std::vector<std::vector<std::vector<float>>> getCoords();

	~Track();
};