#ifndef PSO_H
#define PSO_H

#include "PSO_Behavior.h"
#include <iostream>
#include <vector>

using std::cout;
using std::cerr;
using std::endl;

class PSO
{
    public:
        PSO(int count, int dim);
        virtual ~PSO();
        void startOptimization(int times);
        void setBehavior(PSO_Behavior* behavior);
        void getBestParticle();

    private:
        vector<Particle> particles;
        PSO_Behavior* behavior;
        int count;
};

#endif // PSO_H
