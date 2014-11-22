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

        void SetNTeams(int n);

    protected:

    private:

        int         nTeams;
        int         rounds;

        Individual* individuals;

};

#endif // POPULATION_H
