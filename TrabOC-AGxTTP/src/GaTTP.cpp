#include "GaTTP.h"


GaTTP::GaTTP()
{
    cRate = 0;
    pRate = 0;

    generation = 0;
    genNoImprov = 0;

    current = new Population;
    time(&startTime);
}

GaTTP::~GaTTP()
{
    delete this;
}

double GaTTP::TimeElapsedInMinutes(){

    return difftime(endTime, startTime)/60.0;

}

void GaTTP::SetNTeams(int n){

    nTeams = n;

}
void GaTTP::SetNPopInitial(int n){

    nPopIn = n;

}


void GaTTP::SetMRate(float rate){

    mRate = rate;

}
void GaTTP::SetPRate(float rate){

    pRate = rate;
    eliteRate  = 1.0f - (pRate+cRate);

}
void GaTTP::SetCRate(float rate){

    cRate = rate;
    eliteRate  = 1.0f - (pRate+cRate);

}
void GaTTP::SetStopN(int n){

    stopQuant = n;

}
void GaTTP::SetStopTime(int minutes){

    stopTime = minutes;

}

void GaTTP::GenerateInitial(){

    GenerateInitial(nPopIn);

}

// Gera a populacao inicial aleatoria
void GaTTP::GenerateInitial(int nPop){

    nPopIn = nPop;
    current->SetNTeams(nTeams);
    current->SetDistMatrix(matrixDist);
    current->GenerateRandom(nPopIn);
}

void GaTTP::SetDistMatrix(std::string strMatrix){

    matrixDist = readMatrix(strMatrix, teams, matrixDist);

}

void GaTTP::nextGeneration(){

    Population* newPop = current->GenerateNewPopulation();

    generation++;

    if(newPop->GetBestFitness()<current->GetBestFitness()) {
        genNoImprov++;
    }
    else{
        genNoImprov = 0;
    }

    delete current;
    current = newPop;

    //bestIndividual = newPop->GetBestIndividual();

    time(&endTime);

}

void GaTTP::Solve() {

    // Gera uma populacao randomica inicial
    GenerateInitial();

    do{

        // Realiza a selecao dos pais
        current->SelectParents(eliteRate);

        // Realiza a reproducao por mutacao, crossover e elitismo
        current->ParentsMutation(pRate, mRate);
        current->ParentsCrossover(cRate);

        nextGeneration();

    }while(!verifyStoppage()); // verifica condicao de parada

}

bool GaTTP::verifyStoppage(){

    // Parada por tempo OU parada por quantidade de geracoes sem melhora
    bool time = (TimeElapsedInMinutes()>stopTime);
    bool gen = (genNoImprov>stopQuant);

    return(time || gen);

}


std::string GaTTP::GetCurrent(){



}
