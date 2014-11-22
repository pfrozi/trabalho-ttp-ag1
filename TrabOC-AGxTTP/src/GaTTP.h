#include <iostream>
#include <list>
#include <time.h>

#include "Individual.h"

#ifndef GATTP_H
#define GATTP_H

class GaTTP
{
    public:
        
        
        GaTTP();
        virtual ~GaTTP();
        
        void GenerateInitial(int length);               // Gera a população inicial que será utilizada pelo algoritimo
        void Solve();                                   // Processa o algoritmo até que os critérios de parada sejam aceitos
        
        std::String GetCurrent(); 
        
        time_t GetStartTime(); 
        time_t GetEndTime(); 
        
    protected:
        
        
        
    private:
        
        time_t startTime;
        time_t endTime;
        
        Population current;
        
        void selection(int length);                         // Realiza a seleção dos individuos mais aptos da populacao
        
        void mutate(float rate, Individual i, Individual i_mutated);   // Realiza o processo de mutação do individuo
        void crossover(Individual i_a, Individual i_b); // Realiza o processo de crossover do individuo
};

#endif // GATTP_H
