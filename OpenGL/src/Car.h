#pragma once

#include "Graphics2D.h"
#include "NeuralNetwork.h"
//#include "Track.h"

#include <vector>

class Track;

class NeuralNetwork;

class Car {
private:
	float vel;
	float acc;
	bool alive;
	int timeAlive;
	std::vector<std::vector<float>> coords;
	std::vector<float> center;
	std::vector<std::vector<float>> boundingBox;
	std::vector<std::vector<float>> dir;
	std::vector<double> dists;
	NeuralNetwork network;

	void findBoundingBox();

public:
	Car();
	void resetAll();
	void render(Graphics2D* engine);
	void turn(float dir);
	void translate(float x, float y);
	void rotate(double angle);
	void update();
	void findDists(Track* track);
	void applyNetwork();
	void applyMutations();
	std::vector<std::vector<float>> getCoords();
	std::vector<std::vector<float>> getBoundingBox();
	bool getAlive();
	int getTimeAlive();
	void setAcc(float val);
	void setAlive(bool val);
	~Car();
};