#include <iostream>
#include <string>
#include "MyPSOBehavior.h"
#include "PSO.h"

using std::cout;
using std::cerr;
using std::endl;
using std::stoi;
using std::stod;
using std::string;

int main(int argc, char *argv[]){
    int times = 100;
    int count = 50;
    int dim = 2;
    int target_x = 50.0, target_y = 50.0;

    for(int i = 1; i < argc;){
        if(argv[i] == string("-t")){
            if(i + 1 < argc){
                times = stoi(argv[i + 1]);
                i += 2;
            }
        }
        else if(argv[i] == string("-c")){
            if(i + 1 < argc){
                count = stoi(argv[i + 1]);
                i += 2;
            }
        }
        else if(argv[i] == string("-p")){
            if(i + 2 < argc){
                target_x = stod(argv[i + 1]);
                target_y = stod(argv[i + 2]);

                i += 3;
            }
        }
        else{
            cerr << "Argumnets error !" << endl;
            return 0;
        }
    }

    PSO pso(count, dim);
    MyPSOBehavior behavior(target_x, target_y, dim);

    pso.setBehavior(&behavior);

    pso.startOptimization(times);

    pso.getBestParticle();

    cout << behavior.getBestPoint() << endl;

    return 0;
}
