#pragma once
#include <vector>
#include "CIndividual.h"
#define POP_SIZE 100
#define GENERATION_NUMBER 150
//#define MAX_SIZE 9


class CGenericAlgorithm
{
private:
	int popSize = POP_SIZE;
	double crossProb = 0.6;
	double mutProb = 0.1;
	std::vector<CIndividual*> individualsVector;
	std::vector<CIndividual*> newPopulationVector;
	int itemsNumber;
	int maxSize = 9;
	std::vector<int> valuesVector;
	std::vector<int> sizesVector;
	int* bestSolutionGen;
	int bestSolutionQuality;
	int generationNumber = GENERATION_NUMBER;
	
public:

	CGenericAlgorithm(int itemsNum, std::vector<int> values, std::vector<int> sizes)
	{
		itemsNumber = itemsNum;
		valuesVector = values;
		sizesVector = sizes;
		bestSolutionGen = new int[itemsNumber];

		if (valuesVector.size() != sizesVector.size())
			throw std::invalid_argument("Tables not equal! \n");
	}
	
	CGenericAlgorithm(int itemsNum, std::vector<int> values, std::vector<int> sizes, int capacity)
	{
		itemsNumber = itemsNum;
		valuesVector = values;
		sizesVector = sizes;
		bestSolutionGen = new int[itemsNumber];
		maxSize = capacity;

		if (valuesVector.size() != sizesVector.size())
			throw std::invalid_argument("Tables not equal! \n");
	}

	~CGenericAlgorithm()
	{
		//std::cout << "CGenericAlgorithm destructor \n";
		for (CIndividual* obj : individualsVector)
			delete obj;
		individualsVector.clear();	
		for (CIndividual* obj : newPopulationVector)
			delete obj;
		newPopulationVector.clear();	
		
		delete bestSolutionGen;
	}

	void solve()
	{
		generatePopulation();
		//printIndividuals(individualsVector);

		int i = 1;
		while (i < generationNumber) 
		{
			while (newPopulationVector.size() < popSize)
			{
				doCrossing();
			}
			//std::cout << "New population: \n";
			//printIndividuals(newPopulationVector);
			//for (CIndividual* parent : individualsVector)
			//	 std::cout<<parent->getQuality()<<" ";
			for (CIndividual* parent : individualsVector)
				delete parent;
			
			individualsVector.clear();
			individualsVector.assign(newPopulationVector.begin(), newPopulationVector.end());

			newPopulationVector.clear();			
			i++;
			//std::cout<< "\n";
		}

	}

	void generatePopulation()
	{
		// generate population with randomly created individuals

		for (int i = 0; i < popSize; i++)
		{

			CIndividual* ind = new CIndividual(itemsNumber);
			ind->createGenotype();
			countFitness(ind);

			individualsVector.push_back(ind);
		}
	}

	void doCrossing()
	{
		int individualsSize = individualsVector.size();

		CIndividual* first = individualsVector[rand() % individualsSize];
		CIndividual* second = individualsVector[rand() % individualsSize];
		
		CIndividual* parent;
		CIndividual* parent2;

		parent = chooseBetterParent(first, second);

		first = individualsVector[rand() % individualsSize];
		second = individualsVector[rand() % individualsSize];

		parent2 = chooseBetterParent(first, second);

		//std::cout << "Parents genotype: \n";
		//parent->vPrintGenotype();
		//parent2->vPrintGenotype();


		std::vector<CIndividual*> childs;

		if ((double)rand() / (RAND_MAX + 1.0) < crossProb)
		{
			childs = parent->cross(parent2);

			childs[0]->mutate(mutProb);
			childs[1]->mutate(mutProb);
			
			countFitness(childs[0]);
			countFitness(childs[1]);
		}
		else
		{
			// added copy method because we then remove parents and when parents arent crossing we delete it twice
			childs.push_back(parent->copy());
			childs.push_back(parent2->copy());
		}

		int* genotypePointer;

		if (bestSolutionGen != NULL)
		{
			checkIfSolutionBetter(childs[0]);
			checkIfSolutionBetter(childs[1]);
		}
		else
		{
			if (childs[0]->getFitness() > 0 && childs[0]->getFitness() > childs[1]->getFitness())
			{
				genotypePointer = childs[0]->getGenotype();
				for (int i = 0; i < itemsNumber; i++)
				{
					bestSolutionGen[i] = genotypePointer[i];
				}
				bestSolutionQuality = childs[0]->getFitness();
			}
			else if (childs[1]->getFitness() > 0)
			{
				genotypePointer = childs[1]->getGenotype();
				for (int i = 0; i < itemsNumber; i++)
				{
					bestSolutionGen[i] = genotypePointer[i];
				}
				bestSolutionQuality = childs[1]->getFitness();
			}
		}

		newPopulationVector.push_back(childs[0]);
		newPopulationVector.push_back(childs[1]);
		childs.clear();

	}


	void printIndividuals(std::vector<CIndividual*> individuals)
	{
		for (int i = 0; i < individuals.size(); i++)
		{
			individuals[i]->vPrintGenotype();
		}
	}	
	

	void printBestSolution()
	{
		if (bestSolutionQuality == 0) // case when all generated genotypes have too big size -> quality = 0
		{
			std::cout << "Haven't faound the best solution. Please increase population/generations number\n";
			return;
		}

		std::cout << "This is the best solution of this instance of Knapsack Problem: \n";

		for (int i = 0; i < itemsNumber; i++)
		{
			std::cout << bestSolutionGen[i];;
		}
		std::cout << "\n";
		std::cout << "Value of solution: "<< bestSolutionQuality << "\n";
		
		int size = 0;
		for (int i = 0; i < sizesVector.size(); i++)
		{
			if (bestSolutionGen[i] == 1)
				size += sizesVector[i];
		}
		std::cout << "Size of solution: " << size << " (maximal size = " << maxSize << ")\n";
	}

	void countFitness(CIndividual* individual)
	{
		int fitness = 0;
		int size = 0;

		int* genotype = individual->getGenotype();
		for (int i = 0; i < sizesVector.size(); i++) 
		{
			if (genotype[i] == 1)
			{
				size += sizesVector[i];
			}
		}

		if (size > maxSize)
		{
			individual->setFitness(0);
		}
		else
		{
			for (int i = 0; i < valuesVector.size(); i++)
			{
				if (genotype[i] == 1)
				{
					fitness += valuesVector[i];
				}
			}
			individual->setFitness(fitness);
		}
	}

	CIndividual* chooseBetterParent(CIndividual* first, CIndividual* second)
	{
		if (first->getFitness() >= second->getFitness())
		{
			return first;
		}
		else
		{
			return second;
		}
	}

	void checkIfSolutionBetter(CIndividual* individual)
	{
		if (individual->getFitness() > bestSolutionQuality)
		{

			int* genotypePointer = individual->getGenotype();
			for (int i = 0; i < itemsNumber; i++)
			{
				bestSolutionGen[i] = genotypePointer[i];
			}
			bestSolutionQuality = individual->getFitness();
		}
	}
};