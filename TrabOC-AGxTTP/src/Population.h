#include <iostream>
#include <list>
#include "Individual.h"


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
        void SelectParents();

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

        void setBestIndividual(Individual* i);

};

#endif // POPULATION_H
