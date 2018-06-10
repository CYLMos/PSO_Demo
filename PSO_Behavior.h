#ifndef PSO_BEHAVIOR_H
#define PSO_BEHAVIOR_H

#include "Particle.h"
#include <iostream>
#include <vector>

using std::vector;


class PSO_Behavior{
    public:
        virtual void initial(vector<Particle>& particles) = 0;

        virtual void iteration(int times, vector<Particle>& particles) = 0;

        virtual Particle& getBestParticle(vector<Particle>& particles) const = 0;

        virtual double computePoint(vector<double>& location) = 0;
};

#endif // PSO_BEHAVIOR_H
