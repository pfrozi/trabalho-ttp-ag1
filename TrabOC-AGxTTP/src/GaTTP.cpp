#include "GaTTP.h"


GaTTP::GaTTP()
{
    cRate = 0;
    pRate = 0;
}

GaTTP::~GaTTP()
{
    delete this;
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

    current->GenerateRandom(nPopIn);
}

void GaTTP::SetDistMatrix(std::string strMatrix){

    readMatrix(strMatrix, teams, matrixDist);

}

std::string GaTTP::GetCurrent(){



}
