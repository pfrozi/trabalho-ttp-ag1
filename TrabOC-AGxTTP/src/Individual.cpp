#include "Individual.h"

Individual::Individual()
{
    //ctor
}

Individual::~Individual()
{
    //delete chromosome;
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

    for(int i=0;i<length;i++) chromosome[i]=false;

}

void Individual::SetNTeams(int n){

    nTeams = n;
    rounds = 2*(nTeams-1);
}

void Individual::GenerateRdm(){

    srand(time(NULL));

    for(int i=0; i<nTeams; i++){

        for(int j=0; j<nTeams; j++){

            if(i!=j){

                int k = rand() % rounds;
                SetPositionValue(i,j,k, true);
            }
        }

    }
}

void Individual::SetDistMatrix(float** matrix){

    matrixDist = matrix;
}

float Individual::CheckFitness() {

    //fitness = (float)GetRdmInt(0,10000)*1.0f/(float)GetRdmInt(0,1000);

    //return fitness;

    float total = 0.0f;
	float fo = ObjectiveFunction();
	int playYourself = ValidatePlayYourself();
	int matchsPerRound = ValidateMatchsPerRound();
	int oneGamePerTeamPerRound = ValidateOneGamePerTeamPerRound();
	int maxThreeGamesHome = ValidateMaxThreeGamesHome();
	int maxThreeGamesOut = ValidateMaxThreeGamesOut();
	int playEachOtherAgain = ValidatePlayEachOtherAgain();

	total += playYourself * 		100000000000000000;
	total += matchsPerRound * 		 10000000000000000;
	total += oneGamePerTeamPerRound * 1000000000000000;
	total += maxThreeGamesHome * 	   100000000000000;
	total += maxThreeGamesOut * 		10000000000000;
	total += playEachOtherAgain * 		 1000000000000;
	total += fo;

    fitness = total;

	return total;
}

float Individual::ObjectiveFunctionFirstRound() {
    float total = 0.0f;

    int i0 = 0;
    int j0 = 0;
    int k0 = 0;

    int firstRoundIndex = 0;
    int firstRound[120];
    int firstRoundLength = 0;
    int x = 0;
    for (x = 0; x < (nTeams/2) * 3; x++){
        firstRound[x] = 0;
    }
    firstRoundLength = x;
    //std::cout << "firstRoundLength: " << firstRoundLength <<endl;

    for(int index=0; index < truePositionsLenght; index+=3){
        i0 = truePositions[index];
        j0 = truePositions[index+1];
    	k0 = truePositions[index+2];

        // store i,j,k of first round
        if(k0 == 0) {
            firstRound[firstRoundIndex] = i0;
            firstRound[firstRoundIndex+1] = j0;
            firstRound[firstRoundIndex+2] = k0;
            firstRoundIndex += 3;
        }
    }

    // print firstRound array
    //std::cout << "firstRound[]: ";
    //for(int i=0; i < firstRoundLength; i++){
    //   std::cout << firstRound[i];
    //}
    //std::cout << std::endl;

    for(int x=0; x < firstRoundLength; x+=3){
        i0 = firstRound[x];
        j0 = firstRound[x+1];
        k0 = firstRound[x+2];
        total += matrixDist[i0][j0];
    }

    return total;
}

float Individual::ObjectiveFunctionMidleRounds() {
	float total = 0.0f;

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

			if(k0 + 1 == k1){

				// time i0 viaja ate a casa de j1
				if(i0 == j1){
                    //std::cout << "i0==jl -> i0j0k0: " << i0 << j0 << k0 << "  i1j1k1: " << i1 << j1 << k1 << endl;
                    //std::cout << "distancia: " << (matrixDist[i0][i1]) <<endl;
					total += float(matrixDist[i0][i1]);
				}

				// time j0 viaga para casa
				if(j0 == i1){
                    //std::cout << "j0==il -> i0j0k0: " << i0 << j0 << k0 << "  i1j1k1: " << i1 << j1 << k1 << endl;
                    //std::cout << "distancia: " << (matrixDist[i0][i1]) <<endl;
					total += float(matrixDist[i0][i1]);
				}

				// time j0 viaga para casa de i1
				if(j0 == j1){
                    //std::cout << "j0==jl -> i0j0k0: " << i0 << j0 << k0 << "  i1j1k1: " << i1 << j1 << k1 << endl;
                    //std::cout << "distancia: " << (matrixDist[i0][i1]) <<endl;
					total += float(matrixDist[i0][i1]);
				}

				// i0 permanece em casa
				if(i0 == i1) {
					//std::cout << "i0==il -> i0j0k0: " << i0 << j0 << k0 << "  i1j1k1: " << i1 << j1 << k1 << endl;
                    //std::cout << "distancia: " << (matrixDist[i0][i1]) <<endl;
                    total += 0;
				}
			}
		}
	}

    return total;
}

float Individual::ObjectiveFunctionLastRound() {
    float total = 0.0f;

    int i0 = 0;
    int j0 = 0;
    int k0 = 0;

    int lastRoundIndex = 0;
    int lastRound[120];
    int lastRoundLength = 0;
    int x = 0;
    for (x = 0; x < (nTeams/2) * 3; x++){
        lastRound[x] = 0;
    }
    lastRoundLength = x;
    //std::cout << "lastRoundLength: " << lastRoundLength <<endl;

    for(int index=0; index < truePositionsLenght; index+=3){
        i0 = truePositions[index];
        j0 = truePositions[index+1];
		k0 = truePositions[index+2];

        // store i,j,k of last round
        if(k0 == rounds-1) {
            lastRound[lastRoundIndex] = i0;
            lastRound[lastRoundIndex+1] = j0;
            lastRound[lastRoundIndex+2] = k0;
            lastRoundIndex += 3;
        }
    }

    // print lastRound array
    //std::cout << "lastRound[]: ";
    //for(int i=0; i < lastRoundLength; i++){
    //   std::cout << lastRound[i];
    //}
    //std::cout << std::endl;

    for(int x=0; x < lastRoundLength; x+=3){
        i0 = lastRound[x];
        j0 = lastRound[x+1];
        k0 = lastRound[x+2];
        //std::cout << "lastRound total part: " << matrixDist[i0][j0] <<std::endl;
        total += matrixDist[i0][j0];
    }

    return total;
}

float Individual::ObjectiveFunction() {
    GetTruePositionsInit();

    float total = 0.0f;
    float firstRound = ObjectiveFunctionFirstRound();
    float midleRounds = ObjectiveFunctionMidleRounds();
    float lastRound = ObjectiveFunctionLastRound();

    total += firstRound + midleRounds + lastRound;

    std::cout << "firstRound: " << firstRound << std::endl;
    std::cout << "midleRounds: " << midleRounds << std::endl;
    std::cout << "lastRound: " << lastRound << std::endl;
    std::cout << "total: " << total << std::endl;

    return total;
}

int Individual::GetPosition(int i, int j, int k){
	return i*nTeams*rounds+j*rounds+k;
}

int Individual::GetPositionValue(int i, int j, int k){
    return chromosome[GetPosition(i,j,k)];
}

void Individual::SetPositionValue(int i, int j, int k, int value){
	chromosome[GetPosition(i,j,k)] = value;
}

Individual Individual::Crossover(Individual individual){

    Individual newIndividual;

    newIndividual.SetLengthChromo(nTeams*nTeams*rounds);
    newIndividual.SetNTeams(nTeams);
    newIndividual.SetDistMatrix(matrixDist);

    for(int i=0;i<length;i++){

        if(i<length/2){
            newIndividual.SetAllele(i,chromosome[i]);
        }
        else{
            newIndividual.SetAllele(i,individual.GetAllele(i));
        }
    }

    return newIndividual;
}

Individual Individual::Mutate(float mRate){

    Individual newIndividual;

    newIndividual.SetLengthChromo(nTeams*nTeams*rounds);
    newIndividual.SetNTeams(nTeams);
    newIndividual.SetDistMatrix(matrixDist);

    for(int i=0;i<length;i++){

        if(GetRdmBool(mRate)){
            newIndividual.SetAllele(i,!chromosome[i]);
        }
        else{
            newIndividual.SetAllele(i,chromosome[i]);
        }
    }

    return newIndividual;

}

void Individual::SetAllele(int index, bool value){

    chromosome[index] = value;

}
bool Individual::GetAllele(int index){

    return chromosome[index];

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
    //   std::cout << truePositions[i];
    //}
    //std::cout << std::endl;
    //std::cout << "truePositionsLenght: " << truePositionsLenght << std::endl;

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
            return 1;
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

    for (int x = 0; x < rounds; x++){
      countk[x] = 0;
    }

	int index = 0;
	while(index < truePositionsLenght) {
		i = truePositions[index];
		j = truePositions[index+1];
		k = truePositions[index+2];

        //std::cout << "i j k:" << i << j << k << std::endl;

        countk[k] = countk[k] + 1;

        //std::cout << "countk[k]" << countk[0] << " " << countk[1] << " " << countk[2] << " " << countk[3] << " " << countk[4] << " " << countk[5] << " " << std::endl;

        if(countk[k] > nTeams/2) {
            std::cout << "ValidateMatchsPerRound: fault" << std::endl;
    		std::cout << "   Round " << k << " have more then " << (nTeams/2) << " games" << std::endl;
            return 1;
		}

		index += 3;
	}
	std::cout << "ValidateMatchsPerRound: ok" << std::endl;
	return 0;
}

int Individual::ValidateOneGamePerTeamPerRound(){
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
            if(jndex != index) {
                i1 = truePositions[jndex];
                j1 = truePositions[jndex+1];
		        k1 = truePositions[jndex+2];

                if(k0 == k1) {
                    if((i0 == i1) || (j0 == j1) || (i0 == j1) || (j0 == i1)) {
                        std::cout << "ValidateOneGamePerTeamPerRound: fault" << std::endl;
            	        std::cout << "   Game " << i0 << "vs" << j0 << " and game " << i1 << "vs" << j1 << " can't happen in same round" << std::endl;
                        return 1;
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

                                std::cout << "ValidateMaxThreeGamesHome: fault" << std::endl;
                	            std::cout << "   Games " << i0 << "vs" << j0 << ", ";
                                std::cout << i1 << "vs" << j1 << ", ";
                                std::cout << i2 << "vs" << j2 << ", ";
                                std::cout << i3 << "vs" << j3 << ", ";
                                std::cout << " can't happen in sequence" << std::endl;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }

	std::cout << "ValidateMaxThreeGamesHome: ok" << std::endl;
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

                                std::cout << "ValidateMaxThreeGamesOut: fault" << std::endl;
                	            std::cout << "   Games " << i0 << "vs" << j0 << ", ";
                                std::cout << i1 << "vs" << j1 << ", ";
                                std::cout << i2 << "vs" << j2 << ", ";
                                std::cout << i3 << "vs" << j3 << ", ";
                                std::cout << " can't happen in sequence" << std::endl;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }

	std::cout << "ValidateMaxThreeGamesOut: ok" << std::endl;
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
                    std::cout << "ValidatePlayEachOtherAgain: fault" << std::endl;
                    std::cout << "   Games " << i0 << "vs" << j0 << " and ";
                    std::cout << i1 << "vs" << j1 << ", ";
                    std::cout << " can't happen in sequence" << std::endl;
                    return 1;
                }
            }
        }
    }

	std::cout << "ValidatePlayEachOtherAgain: ok" << std::endl;
	return 0;
}

std::string Individual::ToString(){

    std::stringstream out;
    out << "--------------------------------/nCromossomo: ";

    for(int i=0;i<length;i++){

        if(chromosome[i]){
            out << "1";
        }
        else {
            out << "0";
        }

    }

    out << "\n";
    out << "Fitness: ";
    out << fitness;
    out << "\n";
    out << "--- Representacao da Solucao ---\n";

    for(int k=0;k<rounds;k++){

        out << "Rodada " << (k+1) << ":\n";

        for(int i=0;i<nTeams;i++){
            for(int j=0;j<nTeams;j++){

                if((bool)GetPositionValue(i,j,k)){

                    out << "Time " << (i+1) << " X Time " << (j+1) << "\n";

                }

            }
        }
    }

    out << "--------------------------------/n";
    return out.str();

}
