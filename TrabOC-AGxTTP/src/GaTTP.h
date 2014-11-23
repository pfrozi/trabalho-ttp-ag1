#include <iostream>
#include <list>
#include <time.h>

#include "Population.h"#include "Individual.h"

#include "Util.h"

#ifndef GATTP_H
#define GATTP_H

class GaTTP
{
    public:


        GaTTP();
        virtual ~GaTTP();
        void GenerateInitial();                         // Gera a população inicial que será utilizada pelo algoritimo
        void GenerateInitial(int length);               // Gera a população inicial que será utilizada pelo algoritimo
        void Solve();                                   // Processa o algoritmo até que os critérios de parada sejam aceitos

        std::string GetCurrent();

        time_t GetStartTime();
        time_t GetEndTime();

        void SetNTeams(int n);
        void SetNPopInitial(int n);
        void SetPRate(float rate);
        void SetCRate(float rate);
        void SetMRate(float rate);
        void SetStopN(int n);
        void SetStopTime(int minutes);
        void SetDistMatrix(std::string strMatrix);


    protected:



    private:

        // Parametros de entrada

        std::list<std::string> teams;                // Lista dos times considerados
        float** matrixDist;                          // Matriz de distancias entre as cidades dos times

        int   nTeams;
        int   nPopIn;
        float pRate;
        float cRate;
        float mRate;
        float eliteRate;
        int   stopQuant;
        int   stopTime;

        time_t startTime;
        time_t endTime;

        Population* current;

        void selection(int length);                                     // Realiza a seleção dos individuos mais aptos da populacao

        void mutate(float rate, Individual i, Individual i_mutated);    // Realiza o processo de mutação do individuo
        void crossover(Individual i_a, Individual i_b);                 // Realiza o processo de crossover do individuo

};

#endif // GATTP_H
