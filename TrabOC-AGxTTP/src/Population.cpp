#include "Population.h"


Population::Population()
{
    //ctor
}

Population::~Population()
{
    delete bestIndividual;
    delete individuals;
}

void Population::SetNTeams(int n){

    nTeams = n;
    rounds = 2*(nTeams-1);
}


void Population::GenerateRandom(int length){

    SetLength(length);

    individuals = new Individual[length];

    for(int l=0;l<length;l++){

        individuals[l].SetLengthChromo(nTeams*nTeams*rounds);
        individuals[l].SetNTeams(nTeams);

    }

}
void Population::CalcFitness(){

    float curr, sum = 0;

    bestFitness = 0;
    worstFitness = 0;

    for(int i=0;i<length;i++){

        curr = individuals[i].CheckFitness();
        if(curr<bestFitness){

            bestFitness = curr;
            setBestIndividual(&individuals[i]);

        }
        else if(curr>worstFitness){

            worstFitness = curr;

        }
        sum+=curr;

    }
    avgFitness = sum / (float)length;

}
void Population::SetLength(int len){

    length = len;

}
void Population::setBestIndividual(Individual* i){

    bestIndividual = i;

}

void Population::SelectParents(){

    for(int i=0;i<length;i++){

        bestParents.push_back(&individuals[i]);

    }

    bestParents.sort();                           // Ordena a lista de individuos da populacao
    bestParents.reverse();                        // Reverte a ordenacao
    bestParents.resize(length/3);                 // Corta os primeiros 1/3 dos melhores individuos

}
