//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "Graphics2D.h"
#include "Car.h"
#include "Track.h"

#include <vector>
#include <iostream>
#include <time.h>

using namespace std;

Graphics2D engine = Graphics2D(1280, 720, "Driving", false);
Track track = Track();
//Car car = Car();

/*void input() {
	if (engine.keyPress(GLFW_KEY_W)) {
		car.setAcc(0.0001f);
	}
	if (engine.keyPress(GLFW_KEY_S)) {
		car.setAcc(-0.0001f);
	}
	if (engine.keyPress(GLFW_KEY_A)) {
		car.turn(1);
	}
	if (engine.keyPress(GLFW_KEY_D)) {
		car.turn(-1);
	}
}*/

//for now the coordinates system goes from (-aspectRatio, -1) to (aspectRatio, 1)
int main() {
	srand(time(0));
	const int cars = 100;
	Car car[cars];
	for (int i = 0; i < cars; i++) {
		car[i] = Car();
	}
	bool finished;
	int maxInd;
	int maxFitness;
	while (engine.shouldClose() == false) {
		//input();
		finished = true;
		for (int i = 0; i < cars; i++) {
			if (car[i].getAlive() == true) {
				finished = false;
				car[i].setAcc(0.001f);
				car[i].findDists(&track);
				car[i].applyNetwork();
				car[i].update();
				car[i].render(&engine);
				if (track.isColliding(&car[i]) == true) {
					car[i].setAlive(false);
				}
			}
		}
		track.render(&engine);
		engine.clear();

		if (finished == true) {
			maxFitness = -1;
			maxInd = -1;
			for (int i = 0; i < cars; i++) {
				if (car[i].getTimeAlive() > maxFitness) {
					maxInd = i;
					maxFitness = car[i].getTimeAlive();
				}
			}
			car[maxInd].resetAll();
			for (int i = 0; i < cars; i++) {
				if (i != maxInd) {
					car[i] = car[maxInd];
					car[i].applyMutations();
				}
			}
			//cout << "GINSIEHD" << endl;
		}

		//if (track.isColliding(&car)) {
		//	engine.setFillColour(1, 0, 0, 1);
		//}
		//else {
		//	engine.setFillColour(1, 1, 1, 1);
		//}

		if (engine.keyPress(GLFW_KEY_ESCAPE)) {
			engine.closeWindow();
		}
	}
}