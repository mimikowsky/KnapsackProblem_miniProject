#pragma once
#include "CGenericAlgorithm.h"
#include <fstream>
#include <string>
#include <vector>

class CKnapsackProblem
{
private:
	int iItemsNumber;
	std::vector<int> iValuesVector;
	std::vector<int> iSizeVector;


public:
	CKnapsackProblem()
	{
		iItemsNumber = 4;
		//iValuesVector = new int[iItemsNumber];
		//iSizeTable = new int[iItemsNumber];
	}
	CKnapsackProblem(int iItemsNum)
	{
		iItemsNumber = iItemsNum;
		//iValuesVector = new int[iItemsNumber];
		//iSizeTable = new int[iItemsNumber];
	}
	
	/*CKnapsackProblem(int itemsNum, int* values, int* sizes)
	{
		iItemsNumber = itemsNum;
		iValuesVector = values;
		iSizeVector = sizes;
	}	*/
	
	CKnapsackProblem(int itemsNum, std::vector<int> values, std::vector<int> sizes)
	{
		iItemsNumber = itemsNum;
		iValuesVector = values;
		iSizeVector = sizes;
	}

	void addItem(int iValue, int iSize)
	{
		/*int* newValues = new int[iItemsNumber + 1];
		int* newSizes = new int[iItemsNumber + 1];
		
		for (int i = 0; i < iItemsNumber; i++)
		{
			newValues[i] = iValuesVector[i];
		}
		newValues[iItemsNumber] = iValue;

		for (int i = 0; i < iItemsNumber; i++)
		{
			newSizes[i] = iSizeVector[i];
		}
		newSizes[iItemsNumber] = iSize;
		iItemsNumber++;

		delete iValuesVector;
		delete iSizeVector;
		iValuesVector = newValues;
		iSizeVector = newSizes;*/

		iItemsNumber++;
		iValuesVector.push_back(iValue);
		iSizeVector.push_back(iSize);

		}
	
	bool changeItem(int offset, int value, int size)
	{
		if (offset >= iItemsNumber)
			return false;
		iValuesVector[offset] = value;
		iSizeVector[offset] = size;
		return true;
	}

	void readFile(std::string filename)
	{
		std::vector<int> values;
		std::vector<int> sizes;
		readFileToVectors(filename, values, sizes);

	}

	void readFileToVectors(std::string textFileName, std::vector<int> values, std::vector<int> sizes)
	{

		std::ifstream myfile;
		myfile.open(textFileName);
		std::string mystring;

		/*if (myfile.is_open()) {
			while (myfile.good()) {
				myfile >> mystring;
				std::cout << mystring + " ";
			}
		}*/
		std::cout << "---------\n";
		
		//std::vector<int> values;
		//std::vector<int> sizes;

		bool valuesDone = false;
		bool sizesDone = false;

		if (myfile.is_open()) {

			char mychar;
			//itemsNumber = myfile.get();
			//myfile.get();
			int number1, number2;

			while (myfile >> number1 >> number2)
			{
				values.push_back(number1);
				sizes.push_back(number2);
			}

			/*while (myfile.good()) {
				
				mychar = myfile.get();
				if (mychar == ' ')
				{
					std::cout << "spacja \n";
				}
				else if (!valuesDone)
				{
					values.push_back(mychar);
					valuesDone = true;
				}
				else
				{
					sizes.push_back(mychar);
					valuesDone = false;

				}*/


				//std::cout << mychar;

			//std::cout << ": " << myfile.tellg() << ", ";
			//}

			std::cout << "\n";

			for(int i=0; i<values.size(); i++)
			{
				std::cout << values[i];
			}

			std::cout << "\n";
			for(int i=0; i<sizes.size(); i++)
			{
				std::cout << sizes[i];
			}
		}
	}

	void solveProblem()
	{
		CGenericAlgorithm algorithm(iItemsNumber, iValuesVector, iSizeVector);
		algorithm.solve();
		algorithm.printBestSolution();
	}
};

