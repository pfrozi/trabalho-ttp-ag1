#include "Population.h"


Population::Population()
{
    //ctor
}

Population::~Population()
{
    //delete bestIndividual;
    //delete individuals;
    //delete this;
}

void Population::SetNTeams(int n){

    nTeams = n;
    rounds = 2*(nTeams-1);
}


void Population::GenerateRandom(int length){

    SetLength(length);

    for(int l=0;l<length;l++){


        individuals[l].SetLengthChromo(nTeams*nTeams*rounds);
        individuals[l].SetNTeams(nTeams);
        individuals[l].SetDistMatrix(matrixDist);

        individuals[l].GenerateRdm();

//        std::cout << individuals[l].ToString();

//        Individual individual;
//
//        individual.SetLengthChromo(nTeams*nTeams*rounds);
//        individual.SetNTeams(nTeams);
//        individual.SetDistMatrix(matrixDist);
//
//        individual.GenerateRdm();
//
//        individuals.push_back(individual);

    }

}
void Population::CalcFitness(){

    float curr, sum = 0;

    bestFitness = std::numeric_limits<float>::max();
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
    individuals = new Individual[length];

}
void Population::setBestIndividual(Individual i){

    bestIndividual = i;

}

void Population::SelectParents(float eliteRate){

    int parentsLen = ceil(length*eliteRate);

    for(int i=0;i<length;i++){

        lsBestParents.push_back(individuals[i]);

    }

    lsBestParents.sort();                                 // Ordena a lista de individuos da populacao
    //lsBestParents.reverse();                            // Reverte a ordenacao
    //lsBestParents.resize(parentsLen);                   // Corta os primeiros 1/3 dos melhores individuos

    std::list<Individual>::iterator it;
    int k = 0;
    for(it = lsBestParents.begin();k<parentsLen;++it){
        Individual i = *it;
        bestParents.push_back(i);
        k++;
    }

//    printParents();
}

void Population::printParents() {

    std::cout << "######### Best Parents #########" << std::endl;

    for(int i=0;i<bestParents.size();i++){
        std::cout << bestParents[i].ToString();
    }

}
void Population::printCrossOver() {

    std::cout << "######### CrossOver #########" << std::endl;

    for(int i=0;i<childCrossover.size();i++){
        std::cout << childCrossover[i].ToString();
    }

}
void Population::printMutation() {

    std::cout << "######### Mutation #########" << std::endl;

    for(int i=0;i<childMutation.size();i++){
        std::cout << childMutation[i].ToString();
    }

}

void Population::ParentsCrossover(float cRate){

    int crossLen = ceil(length*cRate);
    int parent1,parent2;

    for(int i=0;i<crossLen;i++){
        parent1 = GetRdmInt(0,bestParents.size()-1);

        if(parent1>(bestParents.size()/2)){
            parent2 = GetRdmInt(0,parent1-1);
        }
        else{
            parent2 = GetRdmInt(parent1+1,bestParents.size()-1);
        }


        Individual individual1 = bestParents[parent1];
        Individual individual2 = bestParents[parent2];

        Individual newIndividual = individual1.Crossover(individual2);
        childCrossover.push_back(newIndividual);
    }

//    printCrossOver();

}

void Population::ParentsMutation(float pRate, float mRate){

    int mutateLen = ceil(length*pRate);
    int parent1,parent2;

    for(int i=0;i<mutateLen;i++){
        parent1 = GetRdmInt(0,bestParents.size()-1);

        Individual individual1 = bestParents[parent1];
        Individual newIndividual = individual1.Mutate(mRate);
        childMutation.push_back(newIndividual);
    }

//    printMutation();
}

void Population::SetDistMatrix(float** matrix){

    matrixDist = matrix;
}

float Population::GetBestFitness()
{
    return bestFitness;
}

void Population::GenerateNewPopulation(Population* newPopulation){

    int newLength = bestParents.size()+childCrossover.size()+childMutation.size();

    newPopulation->SetLength(newLength);
    newPopulation->SetNTeams(nTeams);
    newPopulation->SetDistMatrix(matrixDist);

    int k = 0;
    for(int l=0;l<bestParents.size();l++){
        newPopulation->CopyIndividual(k,bestParents[l]);
        k++;
    }
    for(int i=0;i<childCrossover.size();i++){
        newPopulation->CopyIndividual(k,childCrossover[i]);
        k++;
    }
    for(int j=0;j<childMutation.size();j++){
        newPopulation->CopyIndividual(k,childMutation[j]);
        k++;
    }



}

void Population::CopyIndividual(int index, Individual individual){


    individuals[index].SetLengthChromo(nTeams*nTeams*rounds);
    individuals[index].SetNTeams(nTeams);
    individuals[index].SetDistMatrix(matrixDist);

    for(int i=0;i<nTeams*nTeams*rounds;i++){
        individuals[index].SetAllele(i,individual.GetAllele(i));
    }
}

Individual Population::GetBestIndividual(){

    return bestIndividual;

}
