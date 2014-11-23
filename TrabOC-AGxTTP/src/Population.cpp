#include "Population.h"


Population::Population()
{
    //ctor
}

Population::~Population()
{
    //delete bestIndividual;
    delete individuals;
    delete this;
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
            setBestIndividual(individuals[i]);

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
void Population::setBestIndividual(Individual i){

    bestIndividual = i;

}

void Population::SelectParents(float eliteRate){

    int parentsLen = ceil(length*eliteRate);

    for(int i=0;i<length;i++){

        bestParents.push_back(individuals[i]);

    }

    bestParents.sort();                                 // Ordena a lista de individuos da populacao
    bestParents.reverse();                              // Reverte a ordenacao
    bestParents.resize(parentsLen);                     // Corta os primeiros 1/3 dos melhores individuos

}

void Population::ParentsCrossover(float cRate){

    int crossLen = ceil(length*cRate);
    int parent1,parent2;

    std::list<Individual>::iterator it;

    for(int i=0;i<crossLen;i++){
        parent1 = GetRdmInt(0,bestParents.size()-1);

        if(parent1>(bestParents.size()/2)){
            parent2 = GetRdmInt(0,parent1-1);
        }
        else{
            parent2 = GetRdmInt(parent1+1,bestParents.size()-1);
        }

        it =  bestParents.begin();
        std::advance(it,parent1);
        Individual individual1 = *it;
        it =  bestParents.begin();
        std::advance(it,parent2);
        Individual individual2 = *it;

        Individual newIndividual = individual1.Crossover(individual2);
        childCrossover.push_back(newIndividual);
    }

}

void Population::ParentsMutation(float pRate, float mRate){

    int mutateLen = ceil(length*pRate);
    int parent1,parent2;

    std::list<Individual>::iterator it;

    for(int i=0;i<mutateLen;i++){
        parent1 = GetRdmInt(0,bestParents.size()-1);

        it =  bestParents.begin();
        std::advance(it,parent1);
        Individual individual1 = *it;

        Individual newIndividual = individual1.Mutate(mRate);
        childMutation.push_back(newIndividual);
    }
}

void Population::SetDistMatrix(float** matrix){

    matrixDist = matrix;
}

Population Population::GenerateNewPopulation(){



}

