#include "Individual.h"


Individual::Individual()
{
    //ctor
}

Individual::~Individual()
{
    delete chromosome;
}


bool Individual::operator ==(const Individual& i)
{
    return (fitness == i.fitness);
}
bool Individual::operator !=(const Individual& i)
{
    return (fitness != i.fitness);
}
bool Individual::operator >=(const Individual& i)
{
    return (fitness >= i.fitness);
}
bool Individual::operator <=(const Individual& i)
{
    return (fitness <= i.fitness);
}
bool Individual::operator >(const Individual& i)
{
    return (fitness > i.fitness);
}
bool Individual::operator <(const Individual& i)
{
    return (fitness < i.fitness);
}


void Individual::SetLengthChromo(int len){

    length = len;
    chromosome = new bool[length];
}

void Individual::SetNTeams(int n){

    nTeams = n;
    rounds = 2*(nTeams-1);
}
void Individual::GenerateRdm(){

    srand(time(NULL));

    for(int i=0; i<nTeams; i++){

        for(int j=0; j<nTeams; j++){

            int k = rand() % rounds;
            chromosome[i*rounds*rounds+j*rounds+k] = true;

        }

    }
}

float Individual::CheckFitness() {

    //TODO:
    return 0.0f;

}
