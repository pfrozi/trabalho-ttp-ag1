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

        Individual[l].SetLengthChromo(nTeams*nTeams*rounds);
        Individual[l].SetNTeams(nTeams);

    }

}
