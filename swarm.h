#pragma once

#include<iostream>
#include<cstdlib>
#include<vector>

struct partical{
	std::vector<double> position;
	std::vector<double> velocity;
	double fitness; // more fit if it is small
	std::vector<double> best_pposition;
};


class Swarm{
public:
	std::vector<partical> swarm_vec;
	partical best_gpartical;

	int iterations;
	int partical_amt;
	double w; // inertia weight
	double c1; // influence of personal best position
	double c2; // influence of global best position
	
	void update_velocity(partical* p);
	void update_position(partical* p);
	void iterate_swarm();

	
	Swarm(int i, int p, double w, double c1, double c2);	
};
