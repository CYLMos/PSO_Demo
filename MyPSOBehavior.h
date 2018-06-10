#ifndef MYPSOBEHAVIOR_H
#define MYPSOBEHAVIOR_H

#include "PSO_Behavior.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>
#include <vector>

using std::string;

using std::vector;

class MyPSOBehavior : public PSO_Behavior{
    public:
        MyPSOBehavior(double target_x, double target_y, int dim, vector<Particle>& particles);
        MyPSOBehavior(double target_x, double target_y, int dim);
        virtual ~MyPSOBehavior();

        void initial(vector<Particle>& particles) override;
        void iteration(int times, vector<Particle>& particles) override;
        Particle& getBestParticle(vector<Particle>& particles) const override;
        double computePoint(vector<double>& location) override;

        double getBestPoint() const;

    private:
        double w = 1.0;
        double c1 = 0.5;
        double c2 = 0.5;
        double bestPoint = 0.0;
        int bestIndex = 0;
        int dim;
        vector<double> upperBound;
        vector<double> lowerBound;
        vector<double> target;

        FILE *fp;
};

#endif // MYPSOBEHAVIOR_H
