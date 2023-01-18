#pragma once
#include <iostream>
#include <vector>

class CIndividual
{
private:
	int* genotype;
	int iSize;
	int iFitness;

public:
	CIndividual()
	{
		iSize = 4;
		genotype = new int[iSize];
	}
	CIndividual(int size)
	{
		iSize = size;
		genotype = new int[size];
	}
	~CIndividual()
	{
		delete genotype;
	}
	void vPrintGenotype()
	{
		for (int i = 0; i < iSize; i++)
		{
			std::cout << genotype[i];
		}
			
		std::cout << "\n";
	}
	int* getGenotype()
	{
		return genotype;
	}
	void createGenotype()
	{
		//srand(time(NULL));
		for (int i = 0; i < iSize; i++)
			genotype[i] = rand() % 2;
	}
	void mutate(double mutProb)
	{
		//if(genotype != NULL)
		for (int i = 0; i < iSize; i++)
		{
			double randNum = (double)rand() / (RAND_MAX + 1.0);
			if (randNum < mutProb)
			{
				//std::cout << "mutation " << randNum <<  " ";
				int gen = genotype[i];
				if (gen == 0)
					genotype[i] = 1;
				else
					genotype[i] = 0;
			}
		}
	}

	std::vector<CIndividual*> cross(CIndividual* partner)
	{
		int divideIndex = rand() % (iSize - 1); // iSize = 4 -> 0/1/2/3

		int* partnerGenotype = partner->getGenotype();

		CIndividual* firstChild = new CIndividual(iSize);
		int* firstChildGenotype = firstChild->getGenotype();

		for (int i = 0; i < divideIndex; i++)
		{
			firstChildGenotype[i] = genotype[i];
		}
		
		for (int i = divideIndex; i < iSize; i++)
		{
			firstChildGenotype[i] = partnerGenotype[i];
		}

		// second child 

		CIndividual* secondChild = new CIndividual(iSize);
		int* secondChildGenotype = secondChild->getGenotype();


		for (int i = 0; i < divideIndex; i++)
		{
			secondChildGenotype[i] = partnerGenotype[i];
		}

		for (int i = divideIndex; i < iSize; i++)
		{
			secondChildGenotype[i] = genotype[i];
		}

		std::vector<CIndividual*> twoChildren;

		twoChildren.push_back(firstChild);
		twoChildren.push_back(secondChild);

		return twoChildren;
	}

	int count(std::vector<int> values)
	{
		int fitness = 0;
		for (int i = 0; i < iSize; i++)
		{
			if (genotype[i] == 1)
			{
				fitness += values[i];
			}
		}
		return fitness;
	}
	
	int countSizes(std::vector<int> sizes)
	{
		int size = 0;
		for (int i = 0; i < iSize; i++)
		{
			if (genotype[i] == 1)
			{
				size += sizes[i];
			}
		}
		//std::cout << "size " << size << "\n";
		return size;
	}

	void zeroGenotype()
	{
		for (int i = 0; i < iSize; i++)
		{
			genotype[i] = 0;
		}
	}

	/*CIndividual getCopy()
	{
		return *this;
	}*/

	CIndividual* copy()
	{
		CIndividual* copy = new CIndividual(iSize);
		int* copyGen = copy->genotype;
		for (int i = 0; i < iSize; i++)
		{
			copyGen[i] = genotype[i];
		}
		return copy;
	}

	void setQuality(int fitness)
	{
		iFitness = fitness;
	}

};