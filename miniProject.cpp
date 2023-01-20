// miniProject.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "CIndividual.h"
#include "CGenericAlgorithm.h"
#include "CKnapsackProblem.h"

int main()
{
    //srand((unsigned int)time(NULL));
    
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


    CKnapsackProblem prob(5, values, sizes, 9);
    //prob.addItem(3, 2);
    prob.solveProblem();

    std::cout << "\n----------- \n\n";
    CKnapsackProblem prob2("dane.txt", 14);
    prob2.solveProblem();

    std::cout << "\n----------- \n\n";
    CKnapsackProblem prob3("dane2.txt", 14);
    prob3.solveProblem();

}
// sometimes when genotype is long, max_size is quite low. and your generation size is not too big, the best solution can never be set and we print values from null pointer (so random -84213 value f.e.) - take parameters wisely