// miniProject.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "CIndividual.h"
#include "CGenericAlgorithm.h"
#include "CKnapsackProblem.h"

int main()
{
    std::cout << "Hello World!\n\n";
    srand((unsigned int)time(NULL));
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


    //CKnapsackProblem prob(5, values, sizes);
    CKnapsackProblem prob("dane.txt");
    //prob.addItem(3, 2);
    //prob.solveProblem();
    //prob.readFile("dane.txt");
    prob.solveProblem();

   /* CIndividual indi(5);
    indi.createGenotype();
    indi.vPrintGenotype();
    std::cout<<indi.countSizes(sizes)<<"\n";
    std::cout<<indi.count(values);*/

}

// sometimes when genotype is long, max_size is quite low. and your generation size is not too big, the best solution can never be set and we print values from null pointer (so random -84213 value f.e.) - take parameters wisely