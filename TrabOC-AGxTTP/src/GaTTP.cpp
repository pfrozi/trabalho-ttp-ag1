#include "GaTTP.h"


GaTTP::GaTTP()
{
    //ctor
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
void GaTTP::SetPRate(float rate){

    pRate = rate;

}
void GaTTP::SetCRate(float rate){

    cRate = rate;

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
