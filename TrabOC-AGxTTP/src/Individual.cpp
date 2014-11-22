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
            SetPositionValue(i,j,k, true);

        }

    }
}

float Individual::CheckFitness() {

    //TODO:
    return 0.0f;

}
bool initialized = false;

int Individual::GetPosition(int i, int j, int k){
	return i*rounds*rounds+j*rounds+k;
}

int Individual::GetPositionValue(int i, int j, int k){
	return chromosome[GetPosition(i,j,k)];
}

void Individual::SetPositionValue(int i, int j, int k, int value){
	chromosome[GetPosition(i,j,k)] = value;
}

void Individual::GetTruePositions() {

	if(initialized) return;
	
	int count = 0;
	for(int i=0; i < nTeams; i++){
		for(int j=0; j < nTeams; j++){
			for(int k=0; k < rounds; k++){
				if(GetPositionValue(i,j,k) == true)
				{
					truePositions[count++] = i;
					truePositions[count++] = j;
					truePositions[count++] = k;
				}
			}
		}
	}
	
	truePositionsLenght = (sizeof(truePositions)/sizeof(*truePositions))
	
	initialized = true;
}

int Individual::GetTruePositions(int i, int j, int k){
	return i*9+j*3+k;
}

int Individual::GetTruePositionsValue(int i, int j, int k){
	return truePositions[GetTruePositions(i,j,k)];
}

void Individual::SetTruePositionValue(int i, int j, int k, int value){
	truePositions[GetTruePositions(i,j,k)] = value;
}

int Individual::ValidatePlayYourself(){
	GetTruePositions();
	int index = 0
	while(index < truePositionsLenght) {
		i = truePositions[index];
		j = truePositions[index+1];
		k = truePositions[index+2];

		if(i = j) return -1;
		
		index += 3
	}
	return 0;
}

int Individual::ValidateMatchsPerRound(){
	GetTruePositions();
	int countk[rounds] = { 0 };
	
	int index = 0
	while(index < truePositionsLenght) {
		i = truePositions[index];
		j = truePositions[index+1];
		k = truePositions[index+2];

		countk[k] += 1;
		if(countk[k] > nTeams/2) return -1
		
		index += 3
	}
	
	return 0;
}

int Individual::ValidateGameOneTime(){
	GetTruePositions();
	for(int i=0; i < nTeams; i++){
		for(int j=0; j < nTeams; j++){
			if(i!=j)
			{
				int gamesIvsJ = 0;
				for(int k = 0; k < rounds; k++){
					if(GetPositionValue(i,j,k) = true) {
						gamesIvsJ += 1;
					}
				}
				if(gamesIvsJ != 1) {
					return -1;
				}
			}
		}
	}
	return 0;
}

int Individual::ValidateOneGame(){
	GetTruePositions();
	for(int i=0; i < nTeams; i++){
		for(int j=0; j < nTeams; j++){
			if(i!=j)
			{
				for(int k = 0; k < rounds; k++){
					if(GetPositionValue(i,j,k) = true)
					{
						//0, 1, 0 = true
						if(GetPositionValue(i,j,k))
					}				
				}
			}
		}
	}
	return 0;
}

