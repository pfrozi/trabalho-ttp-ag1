#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

class Individual
{
    public:


        Individual();
        virtual ~Individual();
        bool operator ==(const Individual& i);
        bool operator !=(const Individual& i);
        bool operator >=(const Individual& i);
        bool operator <=(const Individual& i);
        bool operator  >(const Individual& i);
        bool operator  <(const Individual& i);

        void        SetLengthChromo(int len);
        void        SetNTeams(int n);

        std::string GetChromosome();
        float       GetFitness();
        float       CheckFitness();     // Verifica / Calcula o valor da funcao fitness;

        void        GenerateRdm();

    protected:
    private:

        int         length;                  // Quantidade de alelos do individuo
		int         nTeams;
        int         rounds;
		bool 		initialized;
		int*		truePositions;
		int 		truePositionsLenght;

        std::string       strChromosome;      // Representacao da solucao
        bool*             chromosome;         // Representacao da solucao
        float             fitness;            // Valor do fitness, Representa o resultado da funcao de fitness aplicada a instancia (cromossomo)


        void        SetTruePositionValue(int i, int j, int k, int value);
        int         GetTruePositionsValue(int i, int j, int k);
        int         GetTruePositions(int i, int j, int k);
        void        GetTruePositionsInit();
        void        SetPositionValue(int i, int j, int k, int value);
        int         GetPosition(int i, int j, int k);
        int         GetPositionValue(int i, int j, int k);
        int         ValidatePlayYourself();
        int         ValidateMatchsPerRound();
        int         ValidateGameOneTime();
        int         ValidateOneGame();
};

#endif // INDIVIDUAL_H
