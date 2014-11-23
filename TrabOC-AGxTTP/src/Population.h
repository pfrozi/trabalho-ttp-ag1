#include <iostream>
#include <list>
#include "Individual.h"
#include <math.h>


#ifndef POPULATION_H
#define POPULATION_H

class Population
{
    public:

        Population();
        virtual ~Population();

        void GenerateRandom(int length);

        void SetLength(int len);
        void SetNTeams(int n);
        void CalcFitness();
        void SelectParents(float eliteRate);
        void ParentsCrossover(float cRate);
        void ParentsMutation(float pRate, float mRate);

    protected:

    private:

        int         length;
        int         nTeams;
        int         rounds;

        float       bestFitness;
        float       worstFitness;
        float       avgFitness;

        Individual* bestIndividual;
        Individual* individuals;

        std::list<Individual*> bestParents;
        std::list<Individual*> childCrossover;
        std::list<Individual*> childMutation;

        void setBestIndividual(Individual* i);

};

#endif // POPULATION_H
