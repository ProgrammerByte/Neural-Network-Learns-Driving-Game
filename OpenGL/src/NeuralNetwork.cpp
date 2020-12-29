#include "NeuralNetwork.h"

#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#include <cmath>

using namespace std;

NeuralNetwork::NeuralNetwork(vector<int> nodes) {
	this->nodes = nodes;
    vector<vector<double>> nextMat;
    vector<double> nextRow;
    int weightSize = 0;
    for (int i = 0; i < 3; i++) { //initialises weights with random values between -1 and 1 inclusive
        for (int rows = 0; rows < nodes[i + 1]; rows++) {
            for (int columns = 0; columns < nodes[i]; columns++) {
                nextRow.push_back(((double)rand() / (0.5 * RAND_MAX)) - 1);
                weightSize += 1;
            }
            nextMat.push_back(nextRow);
            nextRow.clear();
        }

        weights.push_back(nextMat);
        //weightGrads.push_back(nextMat); //ONLY USED FOR TRAINING
        nextMat.clear();
    }

    for (int i = 1; i < 4; i++) { //initialises biases with random values
        for (int x = 0; x < nodes[i]; x++) {
            nextRow.push_back((double)rand() / RAND_MAX);
        }
        bias.push_back(nextRow);
        //biasGrads.push_back(nextRow); //ONLY USED FOR TRAINING
        nextRow.clear();
    }

    //READS VALUES FROM FILE, THE FOLLOWING IS STUFF THAT CURRENTLY ISN'T NEEDED BUT COULD BE USEFUL IN THE FUTURE
    /*ifstream file;
    file.open("variables.txt");

    if (!file) {
        cout << "Could not open file!" << endl;
        exit(1);
    }

    double current;
    cout << "Neural Network data found!" << endl;
    int a = 0, b = 0, c = 0; //indexes of values
    while (file >> current) {
        if (c != -1) { //current is a weight
            if (c >= weights[a][b].size()) {
                c = 0;
                b += 1;
            }
            if (b >= weights[a].size()) {
                b = 0;
                a += 1;
            }
            if (a >= weights.size()) {
                c = -1;
                a = 0;
                b = 1;
                bias[0][0] = current;
            }
            else {
                weights[a][b][c] = current;
                c += 1;
            }
        }
        else { //current is a bias
            if (b >= bias[a].size()) {
                b = 0;
                a += 1;
            }
            bias[a][b] = current;
            b += 1;
        }

    }
    file.close();
    //END OF FILE READING
    */
    for (int i = 0; i < 4; i++) { //initialises contents with zero values
        for (int x = 0; x < nodes[i]; x++) {
            nextRow.push_back(0);
        }
        contents.push_back(nextRow);
        nextRow.clear();
    }
}

void NeuralNetwork::randomize() {
    double prob;
    for (int a = 0; a < weights.size(); a++) {
        for (int b = 0; b < weights[a].size(); b++) {
            for (int c = 0; c < weights[a][b].size(); c++) {
                prob = (double)rand() / RAND_MAX;
                if (prob <= 0.005) { //probability of mutation
                    if ((double)rand() / RAND_MAX < 0.5) {
                        weights[a][b][c] += 50 * ((double)rand() / (RAND_MAX));
                    }
                    else {
                        weights[a][b][c] -= 50 * ((double)rand() / (RAND_MAX));
                    }
                }
            }
        }
    }
    for (int a = 0; a < bias.size(); a++) {
        for (int b = 0; b < bias[a].size(); b++) {
            prob = (double)rand() / RAND_MAX;
            if (prob <= 0.005) {
                if ((double)rand() / RAND_MAX < 0.5) {
                    bias[a][b] += 10 * ((double)rand() / RAND_MAX);
                }
                else {
                    bias[a][b] -= 10 * ((double)rand() / RAND_MAX);
                }
            }
        }
    }
}

double expx(double x) {
    double result = 1;
    double currentVal = 1;
    for (int i = 1; i <= 100; i++) {
        currentVal *= (double)x / i;
        result += currentVal;
    }
    return result;
}

double sigmoid(double x) { //returns a value between 0 and 1 given any real x
    return (double)1 / (1 + expx(-x));
}

void NeuralNetwork::setInputs(vector<double> inputs) {
    contents[0] = inputs;
    double currentVal;
    for (int i = 0; i < 3; i++) { //for each node multiply the relevant weight matrix by the given node contents
        //the folloiwing multiplies weights[i] with contents[i]
        for (int a = 0; a < nodes[i + 1]; a++) {
            currentVal = 0;
            for (int b = 0; b < nodes[i]; b++) {
                currentVal += weights[i][a][b] * contents[i][b];
            }
            //zValues[i][a] = currentVal + bias[i][a];
            contents[i + 1][a] = sigmoid(currentVal + bias[i][a]);
        }
    }
}

vector<double> NeuralNetwork::getOutputs() {
    return contents[3];
}

NeuralNetwork::~NeuralNetwork() {}