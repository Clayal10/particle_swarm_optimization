/*
 10 Dimensions will be 10 seperate values for location, velocity, c1, and c2. We won't graph so it doesn't really matter to conceptualize.
 I have spelt "particle" wrong in the whole program so it is now spelt "partical" :)

notes:
	- use a struct for each partical.
	- use a vector to store the dimensions
	- position values are between 0 and 1000
	- velocity values are betwen -10 and 10	
	- Do 3 dimensions for Rosenbrock
 * */
#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>
#include<fstream>
#include<cmath>
#include"swarm.h"

using namespace std;


//double rosenbrock(vector<double> p);

int main(){
	srand((unsigned int)time(0));
	int iterations = 10000;
	int swarm_size = 30;
	double inertia = 0.9;
	double c1 = 2;
	double c2 = 2;
	char function = 's';

	//PSO parameters
	Swarm swarm(iterations, swarm_size, inertia, c1, c2, function);
	function = 'r';
	Swarm rose_swarm(iterations, swarm_size, inertia, c1, c2, function);
	swarm.iterate_swarm();
	rose_swarm.iterate_swarm();
	
	ofstream fp;
	fp.open("output.txt");
	if(!fp){
		cout << "Failed to open file" << endl;
		exit(-1);
	}

	fp << "Benchmark Function: Sphere" << endl;
	fp << "Best Position: [";
	for(int i=0; i<swarm.dimensions; i++){
		fp << swarm.best_gpartical.position[i] << ", ";
	}
	fp << "]\n";
	fp << "Best Fitness: " << swarm.best_gpartical.fitness << endl;
	fp << "Swarm Size: " << swarm_size << endl;
	fp << "Intertia Weight: " << inertia << endl;
	fp << "Cognitive Coefficient: " << c1 << endl;
	fp << "Social Coefficient: " << c2 << endl;
	fp << "Number of Iterations: " << iterations << endl;
	
	fp << "\n======================================\n\n";

	fp << "Benchmark Function: Rosenbrock" << endl;
	fp << "Best Position: [";
	for(int i=0; i<rose_swarm.dimensions; i++){
		fp << rose_swarm.best_gpartical.position[i] << ", ";
	}
	fp << "]\n";
	fp << "Best Fitness: " << rose_swarm.best_gpartical.fitness << endl;
	fp << "Swarm Size: " << swarm_size << endl;
	fp << "Intertia Weight: " << inertia << endl;
	fp << "Cognitive Coefficient: " << c1 << endl;
	fp << "Social Coefficient: " << c2 << endl;
	fp << "Number of Iterations: " << iterations << endl;
/*
	vector<double> rose = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	cout << rosenbrock(rose) << endl;
*/	

	return 0;	
}
/*
double rosenbrock(vector<double> p){
	double sum=0;
	for(int i=0; i<9; i++){//iterates through total-1
		sum += 100 * pow((p[i+1] - pow(p[i], 2)), 2) + pow(1 - p[i], 2);
	}
	
	return sum;
}
*/
