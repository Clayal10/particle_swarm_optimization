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
#include"swarm.h"

using namespace std;

int main(){
	srand((unsigned int)time(0));
	int iterations = 10000;
	int swarm_size = 30;
	double inertia = 0.99;
	double c1 = 2.0;
	double c2 = 2.0;

	//PSO parameters
	Swarm swarm(iterations, swarm_size, inertia, c1, c2);
	swarm.iterate_swarm();
	/*for testing*/
/*
	cout << "=======\n" << swarm.best_gpartical.fitness << "\n======\n";
	double fitness;
	//iterations
for(int j=0; j<3; j++){
	fitness = 0;
	for(int i=0; i<10; i++){
		cout << swarm.swarm_vec[j].position[i] << endl;
		fitness += swarm.swarm_vec[j].position[i];
	}
	cout << "Fitness: ";
	cout << fitness << "\n\n";

}
	swarm.iterate_swarm();

	cout << "\n\n\n";
for(int j=0; j<3; j++){
	fitness = 0;
	for(int i=0; i<10; i++){
		cout << swarm.swarm_vec[j].position[i] << endl;
		fitness += swarm.swarm_vec[j].position[i];
	}
	cout << "Fitness: ";
	cout << fitness << endl;
}
	cout << "=======\n" << swarm.best_gpartical.fitness << "\n======\n";

*/
	
	ofstream fp;
	fp.open("output.txt");
	if(!fp){
		cout << "Failed to open file" << endl;
		exit(-1);
	}

	fp << "Benchmark Function: Sphere" << endl;
	fp << "Best Position: [";
	for(int i=0; i<10; i++){
		fp << swarm.best_gpartical.position[i] << ", ";
	}
	fp << "]\n";
	fp << "Best Fitness: " << swarm.best_gpartical.fitness << endl;
	fp << "Swarm Size: " << swarm_size << endl;
	fp << "Intertia Weight: " << inertia << endl;
	fp << "Cognitive Coefficient: " << c1 << endl;
	fp << "Social Coefficient: " << c2 << endl;
	fp << "Number of Iterations: " << iterations << endl;
	

	

	return 0;	
}
