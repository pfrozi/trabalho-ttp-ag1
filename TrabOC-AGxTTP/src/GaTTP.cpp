#include "GaTTP.h"


GaTTP::GaTTP()
{
    //ctor
}

GaTTP::~GaTTP()
{
    //dtor
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
