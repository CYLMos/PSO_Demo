#include "Particle.h"

Particle::Particle(){
    this->point = 0.0;
    this->bestPoint = 0.0;
}

Particle::Particle(int dim){
    this->bestLocation.reserve(dim);
    this->currentLocation.reserve(dim);
    this->velocity.reserve(dim);
    this->point = 0.0;
    this->bestPoint = 0.0;
}

Particle::~Particle(){
    this->bestLocation.clear();
    this->currentLocation.clear();
    this->velocity.clear();
}

void Particle::setDim(int dim){
    this->bestLocation.reserve(dim);
    this->currentLocation.reserve(dim);
    this->velocity.reserve(dim);
}

const vector<double>& Particle::getBestLocation() const{
    return this->bestLocation;
}

const vector<double>& Particle::getCurrentLocation() const{
    return this->currentLocation;
}

const vector<double>& Particle::getVelocity() const{
    return this->velocity;
}

double Particle::getPoint() const{
    return this->point;
}

double Particle::getBestPoint() const{
    return this->bestPoint;
}

void Particle::setBestLocation(vector<double> bestLocation){
    this->bestLocation.clear();
    this->bestLocation.assign(bestLocation.begin(), bestLocation.end());
}

void Particle::setCurrentLocation(vector<double> currentLocation){
    this->currentLocation.clear();
    this->currentLocation.assign(currentLocation.begin(), currentLocation.end());
}

void Particle::setVelocity(vector<double> velocity){
    this->velocity.clear();
    this->velocity.assign(velocity.begin(), velocity.end());
}

void Particle::setPoint(double point){
    this->point = point;
}

void Particle::setBestPoint(double point){
    this->bestPoint = point;
}
