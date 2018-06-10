#include "PSO.h"

PSO::PSO(int count, int dim) : count(count){
    this->particles.reserve(count);

    for(int i = 0; i < count; i++){
        Particle p(dim);
        this->particles.push_back(p);
    }
}

PSO::~PSO(){
}

void PSO::startOptimization(int times){
    if(this->behavior){
        this->behavior->iteration(times, this->particles);
    }
    else{
        cerr << "You didn't set the behavior !" << endl;
    }
}

void PSO::setBehavior(PSO_Behavior* behavior){
    this->behavior = behavior;
    this->behavior->initial(this->particles);
}

void PSO::getBestParticle(){
    if(this->behavior){
        Particle p = this->behavior->getBestParticle(this->particles);

        cout << "Best location :";
        for(int i = 0; i < p.getBestLocation().size(); i++){
            cout << " " << p.getBestLocation().at(i) ;
        }

        cout << endl;
    }
    else{
        cerr << "You didn't set the behavior !" << endl;
    }
}
