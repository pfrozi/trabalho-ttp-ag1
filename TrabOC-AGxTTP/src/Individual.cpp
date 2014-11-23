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

void Individual::SetDistMatrix(float** matrix){

    matrixDist = matrix;
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
					std::cout << "value 1 - i j k:" << i << j << k << std::endl;
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
            std::cout << "ValidatePlayYourself: fault" << std::endl;
			std::cout << "	i==j:" << i << j << std::endl;
            return -1;
        }

		index += 3;
	}
	std::cout << "ValidatePlayYourself: ok" << std::endl;
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
            std::cout << "ValidateMatchsPerRound: fault" << std::endl;
    		std::cout << "   Round " << k << " have more then " << (nTeams/2) << " games" << std::endl;
            return -1;
		}

		index += 3;
	}
	std::cout << "ValidateMatchsPerRound: ok" << std::endl;
	return 0;
}

int Individual::ValidateGameOneTime(){
    GetTruePositionsInit();
	int i = 0;
    int j = 0;
    int k = 0;

    int i1 = 0;
    int j1 = 0;
    int k1 = 0;

    for(int index=0; index < truePositionsLenght; index+=3){
        i = truePositions[index];
    	j = truePositions[index+1];
		k = truePositions[index+2];

        for(int jndex=0; jndex < truePositionsLenght; jndex+=3){
            if(jndex != index) {
                i1 = truePositions[jndex];
                j1 = truePositions[jndex+1];
		        k1 = truePositions[jndex+2];

                if(k == k1) {
                    if((i == i1) || (j == j1) || (i == j1) || (j == i1)) {
                        std::cout << "ValidateGameOneTime: fault" << std::endl;
            	        std::cout << "   Game " << i << "vs" << j << " and game " << i1 << "vs" << j1 << " can't happen in same round" << std::endl;
                        return -1;
                    }
                }
            }
        }
    }

	std::cout << "ValidateGameOneTime: ok" << std::endl;
	return 0;
}

int Individual::ValidateMaxThreeGamesHome(){
    GetTruePositionsInit();
	int i0 = 0;
    int j0 = 0;
    int k0 = 0;

    int i1 = 0;
    int j1 = 0;
    int k1 = 0;

    int i2 = 0;
    int j2 = 0;
    int k2 = 0;

    int i3 = 0;
    int j3 = 0;
    int k3 = 0;

    for(int index=0; index < truePositionsLenght; index+=3){
        i0 = truePositions[index];
    	j0 = truePositions[index+1];
		k0 = truePositions[index+2];

        for(int jndex=0; jndex < truePositionsLenght; jndex+=3){
            i1 = truePositions[jndex];
            j1 = truePositions[jndex+1];
		    k1 = truePositions[jndex+2];

            if((k0+1 == k1) && (i0 == i1)) {
                for(int xndex=0; xndex < truePositionsLenght; xndex+=3){
                    i2 = truePositions[xndex];
                    j2 = truePositions[xndex+1];
            	    k2 = truePositions[xndex+2];

                    if((k1+1 == k2) && (i0 == i2)) {
                        for(int zndex=0; zndex < truePositionsLenght; zndex+=3){
                            i3 = truePositions[zndex];
                            j3 = truePositions[zndex+1];
                            k3 = truePositions[zndex+2];

                            if((k2+1 == k3) && (i0 == i3)) {

                                cout << "ValidateMaxThreeGamesHome: fault" << endl;
                	            cout << "   Games " << i0 << "vs" << j0 << ", ";
                                cout << i1 << "vs" << j1 << ", ";
                                cout << i2 << "vs" << j2 << ", ";
                                cout << i3 << "vs" << j3 << ", ";
                                cout << " can't happen in sequence" << endl;
                                return -1;
                            }
                        }
                    }
                }
            }
        }
    }

	cout << "ValidateMaxThreeGamesHome: ok" << endl;
	return 0;
}

int Individual::ValidateMaxThreeGamesOut(){
    GetTruePositionsInit();
	int i0 = 0;
    int j0 = 0;
    int k0 = 0;

    int i1 = 0;
    int j1 = 0;
    int k1 = 0;

    int i2 = 0;
    int j2 = 0;
    int k2 = 0;

    int i3 = 0;
    int j3 = 0;
    int k3 = 0;

    for(int index=0; index < truePositionsLenght; index+=3){
        i0 = truePositions[index];
    	j0 = truePositions[index+1];
		k0 = truePositions[index+2];

        for(int jndex=0; jndex < truePositionsLenght; jndex+=3){
            i1 = truePositions[jndex];
            j1 = truePositions[jndex+1];
		    k1 = truePositions[jndex+2];

            if((k0+1 == k1) && (j0 == j1)) {
                for(int xndex=0; xndex < truePositionsLenght; xndex+=3){
                    i2 = truePositions[xndex];
                    j2 = truePositions[xndex+1];
            	    k2 = truePositions[xndex+2];

                    if((k1+1 == k2) && (j0 == j2)) {
                        for(int zndex=0; zndex < truePositionsLenght; zndex+=3){
                            i3 = truePositions[zndex];
                            j3 = truePositions[zndex+1];
                            k3 = truePositions[zndex+2];

                            if((k2+1 == k3) && (j0 == j3)) {

                                cout << "ValidateMaxThreeGamesOut: fault" << endl;
                	            cout << "   Games " << i0 << "vs" << j0 << ", ";
                                cout << i1 << "vs" << j1 << ", ";
                                cout << i2 << "vs" << j2 << ", ";
                                cout << i3 << "vs" << j3 << ", ";
                                cout << " can't happen in sequence" << endl;
                                return -1;
                            }
                        }
                    }
                }
            }
        }
    }

	cout << "ValidateMaxThreeGamesOut: ok" << endl;
	return 0;
}

int Individual::ValidatePlayEachOtherAgain(){
    GetTruePositionsInit();
	int i0 = 0;
    int j0 = 0;
    int k0 = 0;

    int i1 = 0;
    int j1 = 0;
    int k1 = 0;

    for(int index=0; index < truePositionsLenght; index+=3){
        i0 = truePositions[index];
    	j0 = truePositions[index+1];
		k0 = truePositions[index+2];

        for(int jndex=0; jndex < truePositionsLenght; jndex+=3){
            i1 = truePositions[jndex];
            j1 = truePositions[jndex+1];
		    k1 = truePositions[jndex+2];

            if(k0+1 == k1){
                if(i0 == j1 && i1 == j0)
                {
                    cout << "ValidatePlayEachOtherAgain: fault" << endl;
                    cout << "   Games " << i0 << "vs" << j0 << " and ";
                    cout << i1 << "vs" << j1 << ", ";
                    cout << " can't happen in sequence" << endl;
                    return -1;
                }
            }
        }
    }

	cout << "ValidatePlayEachOtherAgain: ok" << endl;
	return 0;
}

