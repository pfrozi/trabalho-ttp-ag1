#include <iostream>
#include <list>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <thread_db.h>
#include <string.h>
#include "GaTTP.h"

/*
    CONSTS
*/
#define ARGS_MAX 8


#define ARGS_HELP   0      // Option para imprimir a lista de opcoes
#define ARGS_OUTPUT 1      // Option com o nome do arquivo de saida
#define ARGS_TEAMS  2      // Option para informar o numero de times
#define ARGS_POP_IN 3      // Option para informar o tamanho da populacao de entrada
#define ARGS_P_RATE 4      // Option para informar a taxa de mutacao
#define ARGS_C_RATE 5      // Option para informar a taxa de crossover
#define ARGS_D      6      // Option para informar a quantidade maxima de geracoes sem melhora para o criterio de parada
#define ARGS_S      7      // Option para o tempo maximo de execucao para o criterio de parada


#define ARGS_MATRIX 8      // Option para informar a matrix de distancias que devera ser considerada

using namespace std;

// Instancia do algoritmo
GaTTP ga;

// Parametros de entrada
int   nTeams;
int   nPopIn;
float pRate;
float cRate;
int   stopQuant;
int   stopTime;


std::string outputFile;

std::list<std::string> teams;                // Lista dos times considerados
float** matrixDist;                          // Matriz de distancias entre as cidades dos times



void setGa();


std::vector<std::string> split(std::string str,std::string sep){

    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

void readMatrix(std::string strMatrix){

    bool first_line = true;


    std::vector<std::string> line = split(strMatrix,"/");

    for (int i=0;i<line.size();i++){

        std::vector<std::string> fields = split(line.at(i),",");


        for (int j=0;j<fields.size();j++){

            if(first_line){

                teams.push_back(fields.at(j));

            }
            else{

                if(j==0){

                    matrixDist[i-1] = new float[teams.size()];
                }
                matrixDist[i-1][j] = atof(fields.at(j).c_str());

            }

        }

        if(first_line){

            matrixDist = new float*[teams.size()];
            first_line = false;
        }
    }

}

std::string argStr(int arg){

    switch(arg){

        case ARGS_HELP:{
            return "-h";
        }
        case ARGS_OUTPUT:{

            return "-o";
        }
        case ARGS_TEAMS:{

            return "-t";
        }
        case ARGS_POP_IN:{

            return "-T";
        }
        case ARGS_P_RATE:{

            return "-p";
        }
        case ARGS_C_RATE:{

            return "-c";
        }
        case ARGS_D:{

            return "-d";
        }
        case ARGS_S:{

            return "-s";
        }
        case ARGS_MATRIX:{

            return "-m";
        }
    }

}

void help(){

    cout << "Invalid Args!\n" << endl;
    cout << "Invalid Args!\n" << endl;


}


int main(int argc, char* argv[])
{

    if (argc < ARGS_MAX || (argc==1 && !argv[1]==ARGS_HELP)) {

        cout << "Argumentos inválidos!\n" << endl;
        help();
        return (0);

    } else { // if we got enough parameters...
        char* myFile, myPath, myOutPath;
        std::cout << argv[0];

        for (int i = 1; i < argc; i+=2) {

            if (i + 1 != argc) // Check that we haven't finished parsing already
            {
                std::string arg = argv[i+1];

                if (argv[i] == argStr(ARGS_HELP)) {

                    help();
                    return (0);


                } else if (argv[i] == argStr(ARGS_OUTPUT)) {

                    outputFile = arg;


                } else if (argv[i] == argStr(ARGS_TEAMS)) {


                    nTeams = atoi(arg.c_str());

                } else if (argv[i] == argStr(ARGS_POP_IN)) {

                    nPopIn = atoi(arg.c_str());

                } else if (argv[i] == argStr(ARGS_P_RATE)) {

                    pRate = atof(arg.c_str());

                } else if (argv[i] == argStr(ARGS_C_RATE)) {

                    cRate = atof(arg.c_str());

                } else if (argv[i] == argStr(ARGS_D)) {

                    stopQuant = atoi(arg.c_str());

                } else if (argv[i] == argStr(ARGS_S)) {

                    stopTime = atoi(arg.c_str());

                } else if (argv[i] == argStr(ARGS_MATRIX)) {

                    readMatrix(argv[i+1]);

                }  else {

                    std::cout << "Argumento inválido: " << argv[i] << "." << endl;
                    sleep(1);
                    return (0);

                }
            }
        }

        setGa();




        return 0;
    }


    cout << "Welcome to Solver of TTP with AG!\n" << endl;



    return 0;
}

void setGa(){

    ga.SetNTeams(nTeams);
    ga.SetNPopInitial(nPopIn);
    ga.SetPRate(pRate);
    ga.SetCRate(cRate);
    ga.SetStopN(stopQuant);
    ga.SetStopTime(stopTime);

}
