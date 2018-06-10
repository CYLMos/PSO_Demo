#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>

using std::vector;

class Particle{
    public:
        Particle();
        Particle(int dim);
        virtual ~Particle();

        const vector<double>& getBestLocation() const;
        const vector<double>& getCurrentLocation() const;
        const vector<double>& getVelocity() const;
        double getPoint() const;
        double getBestPoint() const;

        void setBestLocation(vector<double> bestLocation);
        void setCurrentLocation(vector<double> curentLocation);
        void setVelocity(vector<double> velocity);
        void setPoint(double point);
        void setBestPoint(double bestPoint);

        void setDim(int);

    private:
        vector<double> bestLocation;
        vector<double> currentLocation;
        vector<double> velocity;
        double point;
        double bestPoint;
};

#endif // PARTICLE_H
