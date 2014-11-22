#include "Population.h"


Population::Population()
{
    //ctor
}

Population::~Population()
{
    //dtor
}

void Population::SetNTeams(int n){

    nTeams = n;
    rounds = 2*(nTeams-1);
}


void Population::GenerateRandom(int length){

    individuals = new Individual[length];

    for(int l=0;l<length;l++){

        individuals[l].SetLengthChromo(nTeams*nTeams*rounds);
        individuals[l].SetNTeams(nTeams);

    }

}
