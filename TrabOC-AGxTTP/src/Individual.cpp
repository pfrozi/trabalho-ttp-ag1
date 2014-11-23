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
    return i*nTeams*rounds+j*rounds+k;
}

int Individual::GetPositionValue(int i, int j, int k){
    return chromosome[GetPosition(i,j,k)];
}

void Individual::SetPositionValue(int i, int j, int k, int value){
	chromosome[GetPosition(i,j,k)] = value;
}

void Individual::GetTruePositionsInit() {

    if(initialized) return;
	
    int count = 0;
	for(int i=0; i < nTeams; i++){
		for(int j=0; j < nTeams; j++){
			for(int k=0; k < rounds; k++){
                int value = GetPositionValue(i,j,k);
                if(value == 1)
				{
					cout << "value 1 - i j k:" << i << j << k << endl;
                    truePositions[count] = i;
                    count += 1;
					truePositions[count] = j;
                    count += 1;
					truePositions[count] = k;
                    count += 1;
				}
			}
		}
	}

    truePositionsLenght = count;
    
    //for(int i=0; i < truePositionsLenght; i++){
    //   cout << truePositions[i];
    //}
    //cout << endl;
    //cout << "truePositionsLenght: " << truePositionsLenght << endl;

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
    GetTruePositionsInit();
    int i = 0;
    int j = 0;
    int k = 0;
	       
    int index = 0;
	while(index < truePositionsLenght) {
		i = truePositions[index];
		j = truePositions[index+1];
		k = truePositions[index+2];

        if(i == j) {
            cout << "ValidatePlayYourself: fault" << endl;
			cout << "	i==j:" << i << j << endl;
            return -1;
        }
		
		index += 3;
	}
	cout << "ValidatePlayYourself: ok" << endl;
	return 0;
}

int Individual::ValidateMatchsPerRound(){
    GetTruePositionsInit();
	int i = 0;
    int j = 0;
    int k = 0;
	int countk[rounds];
    
    int x;
    for (x = 0; x < rounds; x++){
      countk[x] = 0;
    }
    	
	int index = 0;
	while(index < truePositionsLenght) {
		i = truePositions[index];
		j = truePositions[index+1];
		k = truePositions[index+2];
        
        //cout << "i j k:" << i << j << k << endl;
    	
        countk[k] = countk[k] + 1;
        
        //cout << "countk[k]" << countk[0] << " " << countk[1] << " " << countk[2] << " " << countk[3] << " " << countk[4] << " " << countk[5] << " " << endl;

        if(countk[k] > nTeams/2) {
            cout << "ValidateMatchsPerRound: fault" << endl;
    		cout << "   Round " << k << " have more then " << (nTeams/2) << " games" << endl;
            return -1;
		}
		
		index += 3;
	}
	cout << "ValidateMatchsPerRound: ok" << endl;
	return 0;
}

int Individual::ValidateGameOneTime(){
	GetTruePositionsInit();

	return 0;
}

int Individual::ValidateOneGame(){
	GetTruePositionsInit();

	return 0;
}

