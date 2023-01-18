// miniProject.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "CIndividual.h"
#include "CGenericAlgorithm.h"
#include "CKnapsackProblem.h"

int main()
{
    std::cout << "Hello World!\n\n";
    srand(time(NULL));
    //int iRandom = rand() % 2;
    //std::cout << iRandom;
   /* CIndividual cInd;
    cInd.createGenotype();
    cInd.vPrintGenotype();
    int* code = cInd.getGenotype();
    code[0] = 3;
    cInd.vPrintGenotype();*/

    //std::cout << rand() % (4 - 1); // od 0 do 2
    //std::cout << "------------ \n";

   /* CGenericAlgorithm gen;
    gen.generatePopulation();
    gen.printIndividuals();
    gen.doCrossing();*/


   /* int* values = new int[5];
    values[0] = 3;
    values[1] = 1;
    values[2] = 2;
    values[3] = 4;
    values[4] = 2;

    int* sizes = new int[5];
    sizes[0] = 1;
    sizes[1] = 2;
    sizes[2] = 3;
    sizes[3] = 5;
    sizes[4] = 1;*/
    
    std::vector<int> values;
    values.push_back(3);
    values.push_back(1);
    values.push_back(2);
    values.push_back(4);
    values.push_back(2);

    std::vector<int> sizes;
    sizes.push_back(1);
    sizes.push_back(2);
    sizes.push_back(3);
    sizes.push_back(5);
    sizes.push_back(1);


    CKnapsackProblem prob(5, values, sizes);
    prob.solveProblem();
    //prob.readFile("dane.txt");

   /* CIndividual indi(5);
    indi.createGenotype();
    indi.vPrintGenotype();
    std::cout<<indi.countSizes(sizes)<<"\n";
    std::cout<<indi.count(values);*/

}

// consider situation when solution has the same value as best solution, but lower size, should we change best solution? my if doesnt do it.   probably doesn't need to do it
// add quality componet do CIndividual class, not to calculate every time quality when you choose parent.
// consider fitness/quality component as normaln number or 0 if size is too big.