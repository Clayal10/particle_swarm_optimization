
#include<iostream>
#include<cstdlib>
#include<vector>
#include<limits>
#include<cmath>

#include "swarm.h"


double rand_double(double min, double max){
	return min+(max - min)*(rand()%RAND_MAX) / RAND_MAX;
}

double sphere(partical p){//assigning fitness for minimizing the sqhere func
	double sum=0;
	for(int i=0; i<10; i++){
		sum += p.position[i]*p.position[i];
	}
	return sum;
}

double rosenbrock(partical p){
	double sum=0;
	for(int i=0; i<2; i++){//iterates through total-1
		sum += 100 * pow((p.position[i+1] - pow(p.position[i], 2)), 2) + pow(1 - p.position[i], 2);
	}
	
	return sum;
}
int dimension_buffer;
partical init_partical(char func){
	partical p;
if(func == 's'){
	dimension_buffer = 10;
	for(int i=0; i<dimension_buffer; i++){
		//rand between 0 and 1000
		p.position.push_back(rand_double(-1000, 1000));
		//rand between -10 and 10
		p.velocity.push_back(rand_double(-10, 10));
		//this function only needs position vector
		p.fitness = sphere(p);
		p.best_pposition.push_back(p.position[i]);
	}
}
else if(func == 'r'){
	dimension_buffer = 3;
	for(int i=0; i<dimension_buffer; i++){
		//rand between 0 and 1000
		p.position.push_back(rand_double(-1000, 1000));
		//rand between -10 and 10
		p.velocity.push_back(rand_double(-10, 10));
		//this function only needs position vector
		p.fitness = rosenbrock(p);
		p.best_pposition.push_back(p.position[i]);
	}
}
	return p;
}

/*All the functions for swarm.h*/

Swarm::Swarm(int i, int p, double w, double c1, double c2, char f){// the constructor
	Swarm::iterations = i;
	Swarm::partical_amt = p;
	Swarm::w = w;
	Swarm::c1 = c1;
	Swarm::c2 = c2;
	Swarm::function = f;
	if(f == 's'){Swarm::dimensions = 10;}
	else if(f == 'r'){Swarm::dimensions = 3;}
	for(int i=0; i<partical_amt; i++){
		Swarm::swarm_vec.push_back(init_partical(f));
	}
	//finding the best global position (lowest fitness value)
	double best = Swarm::swarm_vec[0].fitness;
	int best_pos = 0;
	for(int i=1; i<Swarm::swarm_vec.size(); i++){
		if(Swarm::swarm_vec[i].fitness < best){
			best_pos = i;
			best = Swarm::swarm_vec[i].fitness;
		}
	}
	//copying the best partical based on position for the constructor
	Swarm::best_gpartical = Swarm::swarm_vec[best_pos];

	

}	
void Swarm::update_velocity(partical* p){//make sure to use address as parameter
		
	double new_velocity;
	double r1 = rand_double(0, 1);
	double r2 = rand_double(0, 1);
	for(int i=0; i<p->velocity.size(); i++){
		new_velocity = Swarm::w * p->velocity[i] + Swarm::c1 * r1 * (p->best_pposition[i] - p->position[i]) + Swarm::c2 * r2 * (Swarm::best_gpartical.position[i] - p->position[i]);
		if(new_velocity < -10)
			new_velocity = -10;
		else if(new_velocity > 10)
			new_velocity = 10;
		
		//std::cout << new_velocity << std::endl;	
		p->velocity[i] = new_velocity;
	}
}

void Swarm::update_position(partical* p){
	double new_pos;
	for(int i=0; i<p->position.size(); i++){
		new_pos = p->position[i] + p->velocity[i];
		//may want to check bounds
		if(new_pos > 1000)
			new_pos = 1000;
		else if(new_pos < -1000)
			new_pos = -1000;

		p->position[i] = new_pos;
	}
	//update fitenss when we update the position
	double new_fitness;
	if(Swarm::function == 's'){
		new_fitness = sphere(*p);//just want the value of the partical
	}
	else if(Swarm::function == 'r'){
		new_fitness = rosenbrock(*p);
	}

	if(new_fitness < p->fitness){
		p->best_pposition = p->position;
	}
	p->fitness = new_fitness;
}

void Swarm::iterate_swarm(){
	int iteration_count = 0;

	double best_fitness;
	int best_idx = 0;
	while(iteration_count < Swarm::iterations){
		best_fitness = std::numeric_limits<double>::max();
		//find_best_gposition();
		for(int i=0; i<Swarm::partical_amt; i++){
			update_velocity(&Swarm::swarm_vec[i]);
			update_position(&Swarm::swarm_vec[i]);
			if(Swarm::swarm_vec[i].fitness <= best_fitness){
				best_idx = i;
				best_fitness = Swarm::swarm_vec[i].fitness;
			}
		}
		//update the global best
		Swarm::best_gpartical = Swarm::swarm_vec[best_idx];
		//std::cout << "Best fitness at iteration " << iteration_count << ": " << best_gpartical.fitness << std::endl;
		iteration_count++;
	}

}
