#include "MyPSOBehavior.h"

MyPSOBehavior::MyPSOBehavior(double target_x, double target_y, int dim) : dim(dim){
    this->upperBound.reserve(this->dim);
    this->lowerBound.reserve(this->dim);

    this->upperBound.push_back(100);
    this->upperBound.push_back(100);

    this->lowerBound.push_back(0);
    this->lowerBound.push_back(0);

    this->target.reserve(this->dim + 1);

    this->target.push_back(target_x);
    this->target.push_back(target_y);

    this->fp = popen("gnuplot -persist", "w");
    fprintf(this->fp, "set term wxt\n");
    fprintf(this->fp, "set title \"PSO Demo\" font \",20\" \n");
    string xRange = "set xrange[" + std::to_string( (int)(this->lowerBound.at(0)) ) + ":" +
            std::to_string( (int)(this->upperBound.at(0)) ) + "]\n";
    string yRange = "set yrange[" + std::to_string( (int)(this->lowerBound.at(1)) ) + ":" +
            std::to_string( (int)(this->upperBound.at(1)) ) + "]\n";

    fprintf(this->fp, xRange.c_str());
    fprintf(this->fp, yRange.c_str());

    string targrtcircle = "set object 1 circle at first " + std::to_string(target_x) + "," + std::to_string(target_y) +
            " radius char 1.0 fillstyle empty border lc rgb '#aa1100' lw 2 \n";
    fprintf(this->fp, targrtcircle.c_str());
    fprintf(this->fp, "plot 0 \n");
}

MyPSOBehavior::MyPSOBehavior(double target_x, double target_y, int dim, vector<Particle>& particles) : dim(dim){
    this->upperBound.reserve(this->dim);
    this->lowerBound.reserve(this->dim);

    this->upperBound.push_back(100);
    this->upperBound.push_back(100);

    this->lowerBound.push_back(0);
    this->lowerBound.push_back(0);

    this->target.reserve(this->dim);

    this->target.push_back(target_x);
    this->target.push_back(target_y);

    this->fp = popen("gnuplot -persist", "w");
    fprintf(this->fp, "set term wxt\n");
    fprintf(this->fp, "set title \"PSO Demo\" font \",20\" \n");
    string xRange = "set xrange[" + std::to_string( (int)(this->lowerBound.at(0)) ) + ":" +
            std::to_string( (int)(this->upperBound.at(0)) ) + "]\n";
    string yRange = "set yrange[" + std::to_string( (int)(this->lowerBound.at(1)) ) + ":" +
            std::to_string( (int)(this->upperBound.at(1)) ) + "]\n";

    fprintf(this->fp, xRange.c_str());
    fprintf(this->fp, yRange.c_str());

    string targrtcircle = "set object 1 circle at first " + std::to_string(target_x) + "," + std::to_string(target_y) +
            " radius char 1.0 fillstyle empty border lc rgb '#aa1100' lw 2 \n";
    fprintf(this->fp, targrtcircle.c_str());
    //fprintf(this->fp, "plot 0 \n");

    this->initial(particles);
}

MyPSOBehavior::~MyPSOBehavior(){
    this->upperBound.clear();
    this->lowerBound.clear();


    pclose(this->fp);
}

void MyPSOBehavior::initial(vector<Particle>& particles){
    srand((unsigned)time(nullptr));

    /// Initial the particles
    for(int i = 0; i < particles.size(); i++){
        double rand1 = (rand() % 100) + 1;
        double rand2 = (rand() % 100) + 1;

        vector<double> position = {rand1, rand2};
        vector<double> velocity = {rand1 / 1000000.0, rand2 / 1000000.0};

        particles.at(i).setCurrentLocation(position);
        particles.at(i).setBestLocation(position);
        particles.at(i).setVelocity(velocity);

        particles.at(i).setPoint(this->computePoint(position));
        particles.at(i).setBestPoint(this->computePoint(position));

        /// Set data in gnuplot
        string paricle = "set object " + std::to_string(i + 2)  + " circle at first " + std::to_string(rand1) + "," + std::to_string(rand2) +
        " radius char 0.5 fillstyle solid 1.0 border lc rgb '#000000' lw 2 \n";
        fprintf(this->fp, paricle.c_str());
    }
    /// Inital the best point and index
    for(int i = 0; i < particles.size(); i++){
        if(i != 0){
            if(this->bestPoint > particles.at(i).getBestPoint()){
                this->bestPoint = particles.at(i).getBestPoint();
                this->bestIndex = i;
            }
        }
        else{
            this->bestPoint = particles.at(i).getBestPoint();
            this->bestIndex = i;
        }
    }

    fprintf(this->fp, "plot 0 \n");

}

void MyPSOBehavior::iteration(int times, vector<Particle>& particles){
    srand((unsigned)time(nullptr));

    for(int i = 0; i < times; i++){
        const vector<double> globalBestLocation = particles.at(this->bestIndex).getBestLocation();

        for(int p_i = 0; p_i < particles.size(); p_i++){
            vector<double> velocity = particles.at(p_i).getVelocity();
            vector<double> currentLocation = particles.at(p_i).getCurrentLocation();
            vector<double> bestLocation = particles.at(p_i).getBestLocation();

            for(int dim_i = 0; dim_i < this->dim; dim_i++){
                double r1 = ((rand() % 10) + 1) / 10.0;
                double r2 = ((rand() % 10) + 1) / 10.0;

                velocity.at(dim_i) =
                        this->w * velocity.at(dim_i) +
                        this->c1 * r1 * (bestLocation.at(dim_i) - currentLocation.at(dim_i)) +
                        this->c2 * r2 * (globalBestLocation.at(dim_i) - currentLocation.at(dim_i));

                currentLocation.at(dim_i) += velocity.at(dim_i);

                /// If not in the range
                if(currentLocation.at(dim_i) > this->upperBound[dim_i]){
                    currentLocation.at(dim_i) = this->upperBound[dim_i];
                }
                else if(currentLocation.at(dim_i) < this->lowerBound[dim_i]){
                    currentLocation.at(dim_i) = this->lowerBound[dim_i];
                }

            }

            string paricle = "set object " + std::to_string(p_i + 2)  + " circle at first " + std::to_string(currentLocation.at(0)) + "," + std::to_string(currentLocation.at(1)) +
            " radius char 0.5 \n";
            fprintf(this->fp, paricle.c_str());

            double point = this->computePoint(currentLocation);
            particles.at(p_i).setPoint(point);

            if(point < particles.at(p_i).getBestPoint()){
                particles.at(p_i).setBestPoint(point);
                particles.at(p_i).setBestLocation(currentLocation);
            }

            /// Update global best point
            if(particles.at(p_i).getPoint() < this->bestPoint){
                this->bestPoint = particles.at(p_i).getPoint();
                this->bestIndex = p_i;
            }

        }

        fprintf(this->fp, "replot\n");
        fflush(this->fp);
    }

    fprintf(this->fp, "exit\n");
    fflush(this->fp);
}

Particle& MyPSOBehavior::getBestParticle(vector<Particle>& particles) const{
    return particles.at(this->bestIndex);
}

double MyPSOBehavior::computePoint(vector<double>& location){
    double distanceSquare = 0.0;

    for(int i = 0; i < location.size(); i++){
        distanceSquare += pow(location.at(i) - this->target.at(i), 2);
    }

    return sqrt(distanceSquare);
}

double MyPSOBehavior::getBestPoint() const{
    return this->bestPoint;
}
