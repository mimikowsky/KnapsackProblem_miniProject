#pragma once
#include <vector>
#include "CIndividual.h"
#define POP_SIZE 5
#define MAX_SIZE 9
#define GENERATION_NUMBER 20


class CGenericAlgorithm
{
private:
	int popSize = POP_SIZE;
	double crossProb = 0.6;
	double mutProb = 0.1;
	std::vector<CIndividual*> individualsVector;
	std::vector<CIndividual*> newPopulationVector;
	int itemsNumber;
	int maxSize = MAX_SIZE;
	std::vector<int> valuesVector;
	std::vector<int> sizesVector;
	//CIndividual* bestSolution; //to do
	int* bestSolutionGen; //to do
	int generationNumber = GENERATION_NUMBER;

	
public:

	CGenericAlgorithm(int itemsNum, std::vector<int> values, std::vector<int> sizes)
	{
		itemsNumber = itemsNum;
		//std::cout << itemsNumber << "itemsnumberGenericalg \n";
		valuesVector = values;
		sizesVector = sizes;
		bestSolutionGen = new int[itemsNumber];
	}

	~CGenericAlgorithm()
	{
		std::cout << "CGenericAlgorithm destructor \n";
		for (CIndividual* obj : individualsVector)
			delete obj;
		individualsVector.clear();
	}

	void solve()
	{
		generatePopulation();
		printIndividuals();

		int i = 1;

		while (i < generationNumber) {

		while (newPopulationVector.size() < popSize)
		{
			doCrossing();
		}
		std::cout << "New population: \n";
		printNewPopulation();

		for (CIndividual* parent : individualsVector)
			delete parent;
		individualsVector.clear();

		//individualsVector = newPopulationVector;
		//std::copy(newPopulationVector.begin(), newPopulationVector.end(), inserter(individualsVector, individualsVector.begin()));
			
		individualsVector.assign(newPopulationVector.begin(), newPopulationVector.end());


		newPopulationVector.clear();
			
		i++;
		}

	}

	void generatePopulation()
	{
		// generate population with randomly created individuals

		for (int i = 0; i < popSize; i++)
		{

			CIndividual* ind = new CIndividual(itemsNumber);
			ind->createGenotype();

			individualsVector.push_back(ind);
		}
	}

	int countFitness(int* genotypeI)
	{
		// value or 0 if solution is unacceptable (too big size of items)
		int fitness = 0;
		for (int i = 0; i < itemsNumber; i++)
		{
			if (genotypeI[i] == 1)
			{
				fitness += valuesVector[i];
			}
		}
		return fitness;
		
	}

	void doCrossing()
	{
		// uwzglednij jescze prawdopodobienstwo crossowania
		int individualsSize = individualsVector.size();
		//int randomNum = rand() % individualsSize;
		CIndividual* first = individualsVector[rand() % individualsSize];
		CIndividual* second = individualsVector[rand() % individualsSize];

		//CIndividual* parent = first;
		//CIndividual* parent2 = second;
		
		CIndividual* parent;
		CIndividual* parent2;
		// have to set here values and sizes table

		if (first->countSizes(sizesVector) > maxSize)
		{
			parent = second;
			//std::cout << "1 if \n";
		}
		else if (second->countSizes(sizesVector) > maxSize)
		{
			parent = first;
			//std::cout << "2 if \n";
		}
		else if (first->count(valuesVector) > second->count(valuesVector))
		{
			parent = first;
			//std::cout << "3 if \n";
		}
		else
		{
			parent = second;
			//std::cout << "4 if \n";
		}	


		first = individualsVector[rand() % individualsSize];
		second = individualsVector[rand() % individualsSize];


		if (first->countSizes(sizesVector) > maxSize)
		{
			parent2 = second;
		}
		else if (second->countSizes(sizesVector) > maxSize)
		{
			parent2 = first;
		}
		else if (first->count(valuesVector) > second->count(valuesVector))
		{
			parent2 = first;
		}
		else
		{
			parent2 = second;
		}

		std::cout << "Parents genotype: \n";
		parent->vPrintGenotype();
		parent2->vPrintGenotype();


		std::vector<CIndividual*> childs;

		if ((double)rand() / (RAND_MAX + 1.0) < crossProb)
		{
			childs = parent->cross(parent2);
			childs[0]->mutate(mutProb);
			childs[1]->mutate(mutProb);
		}
		else
		{
			// added copy method because we then remove parents and when parents arent crossing we delete it twice
			childs.push_back(parent->copy());
			childs.push_back(parent2->copy());
		}
		// maybe mutation will be neccesary only in case with created new children (not when we do not do crossing and put parents genotype into new population)
		// decided not to mutate parents, better results and logic says not to mute individual who does already exist
		//childs[0]->mutate(mutProb);
		//childs[1]->mutate(mutProb);

		//if (bestSolution != NULL)
		//{
		//	if (childs[0]->count(valuesTable) > bestSolution->count(valuesTable) && childs[0]->countSizes(sizesTable) < maxSize)
		//		bestSolution = childs[0];

		//	if (childs[1]->count(valuesTable) > bestSolution->count(valuesTable) && childs[1]->countSizes(sizesTable) < maxSize)
		//		bestSolution = childs[1];
		//}
		//else
		//{
		//	if (childs[0]->countSizes(sizesTable) < maxSize)
		//		bestSolution = childs[0];
		//	else if (childs[1]->countSizes(sizesTable) < maxSize)
		//		bestSolution = childs[1];
		//}
		
		int* justPointer;

		if (bestSolutionGen != NULL)
		{
			if (childs[0]->count(valuesVector) > countFitness(bestSolutionGen) && childs[0]->countSizes(sizesVector) < maxSize) {
				
				justPointer = childs[0]->getGenotype();
				for (int i = 0; i < itemsNumber; i++)
				{
					bestSolutionGen[i] = justPointer[i];
				}
			}

			if (childs[1]->count(valuesVector) > countFitness(bestSolutionGen) && childs[1]->countSizes(sizesVector) < maxSize) {
				justPointer = childs[1]->getGenotype();
				for (int i = 0; i < itemsNumber; i++)
				{
					bestSolutionGen[i] = justPointer[i];
				}
			}
		}
		else
		{
			//bestSolutionGen = new int[itemsNumber];

			if (childs[0]->countSizes(sizesVector) < maxSize)
			{
				justPointer = childs[0]->getGenotype();
				for (int i = 0; i < itemsNumber; i++)
				{
					bestSolutionGen[i] = justPointer[i];
				}
			}
			else //(childs[1]->countSizes(sizesTable) < maxSize){
			{
				justPointer = childs[1]->getGenotype();
				for (int i = 0; i < itemsNumber; i++)
				{
					bestSolutionGen[i] = justPointer[i];
				}
			}
		}

		


		newPopulationVector.push_back(childs[0]);
		newPopulationVector.push_back(childs[1]);
		childs.clear();
		//printNewPopulation();
		// draw one parent (better from two randomly drawed) and second one (also randomly drawed, we choose from all (even previous drawed) )
		// CrossProb random percent and yes or not 
		// so 2 parents, random draw place where genotype should be cut (n-1) n-itemsNumber.
		// 2 children created from different cutted parts of parents
		// put 2 children to newPopulation. we have 2. popSize shoulde f.e. 4

		// next crossing. if CrossProb show that we do not do a crossing we just put into new population copy of parents
	}

	//void mutation()
	//{

	//	// done for every individual, mutProb f.e. 0,1
	//	// for every gen of genotype if we draw that mutation should be done, we change a gen for the opposite 0011 -> 0111 (second gen mutated)

	//	for (int i = 0; i < newPopulationVector.size(); i++)
	//	{
	//		newPopulationVector[i]-> mutate(mutProb);
	//	}
	//}

	void printIndividuals()
	{
		for (int i = 0; i < individualsVector.size(); i++)
		{
			individualsVector[i]->vPrintGenotype();
		}
	}	
	
	void printNewPopulation()
	{
		for (int i = 0; i < newPopulationVector.size(); i++)
		{
			newPopulationVector[i]->vPrintGenotype();
		}
	}

	void printBestSolution()
	{
		std::cout << "This is the best solution of this instance of Knapsack Problem: \n";
		//bestSolution->vPrintGenotype();
		for (int i = 0; i < itemsNumber; i++)
		{
			std::cout << bestSolutionGen[i];;
		}
		std::cout << "\n";
		std::cout << "Value of sulution: "<< countFitness(bestSolutionGen) << "\n";
		//std::cout << "Size of solution: "<< bestSolution->countSizes(sizesTable) << "\n";

		//std::cout << "Value of sulution: "<< bestSolution->count(valuesTable) << "\n";
		//std::cout << "Size of solution: "<< bestSolution->countSizes(sizesTable) << "\n";
	}

	void setFitness(CIndividual* individual)
	{
		int fitness;
		int size;

		for (int i = 0; i < sizesVector.size(); i++) {

		}
	}
};