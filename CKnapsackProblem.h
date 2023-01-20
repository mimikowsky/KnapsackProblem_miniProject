#pragma once
#include "CGenericAlgorithm.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class CKnapsackProblem
{
private:
	int iItemsNumber;
	std::vector<int> iValuesVector;
	std::vector<int> iSizeVector;
	bool correctData = true;
	int iCapacity = 9;

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
	}
	
	CKnapsackProblem(int itemsNum, std::vector<int> values, std::vector<int> sizes)
	{
		iItemsNumber = itemsNum;
		iValuesVector = values;
		iSizeVector = sizes;
	}

	CKnapsackProblem(int itemsNum, std::vector<int> values, std::vector<int> sizes, int capacity)
	{
		iItemsNumber = itemsNum;
		iValuesVector = values;
		iSizeVector = sizes;
		iCapacity = capacity;
	}

	CKnapsackProblem(std::string filename, int capacity)
	{
		iCapacity = capacity;
		readFile(filename);
	}
	CKnapsackProblem(std::string filename)
	{
		readFile(filename);
		/*try
		{
			readFile(filename);

			for (int i = 0; i < iValuesVector.size(); i++)
			{
				std::cout << iValuesVector[i] << " ";
				std::cout << iSizeVector[i] << "\n";
			}
		}
		catch (const std::exception& er)
		{
			std::cout << "xd";
			std::cout << er.what();
		}*/
		
	}

	void addItem(int iValue, int iSize)
	{
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
		iValuesVector.clear();
		iSizeVector.clear();
		readFileToVectors(filename);		
	}

	void readFileToVectors(std::string textFileName)
	{

		std::ifstream myfile;
		myfile.open(textFileName);
	

		if (myfile.is_open()) {

			std::string line;
			std::stringstream ss;
			int number1, number2;
			while (std::getline(myfile, line))
			{
				ss.clear();
				ss.str(line);
				ss >> number1 >> number2;
				if (number1 <= 0 || number2 <= 0) 
				{
					std::cout << "Error, invalid input: " << line << std::endl;
					correctData = false;
				}
				if (ss.fail()) {
					std::cout << "Error, invalid input: " << line << std::endl;
					correctData = false;
				}
				else {
					iValuesVector.push_back(number1);
					iSizeVector.push_back(number2);
				}
			}

		}
		else {
			std::cout << "Error, unable to open the file" << std::endl;
		}

		//std::ifstream myfile;
		//myfile.open(textFileName);
		//std::string mystring;

		//if (myfile.is_open()) {

		//	int number1, number2;

		//	while (myfile >> number1 >> number2)
		//	{
		//		//values.push_back(number1);
		//		//sizes.push_back(number2);
		//		iValuesVector.push_back(number1);
		//		iSizeVector.push_back(number2);
		//	}

		iItemsNumber = iValuesVector.size();
	}

	void solveProblem()
	{
		if (correctData == true)
		{
			printProblemDetails();
			srand((unsigned int)time(NULL));
			CGenericAlgorithm algorithm(iItemsNumber, iValuesVector, iSizeVector, iCapacity);
			algorithm.solve();
			algorithm.printBestSolution();
		}

		/*try
		{
			CGenericAlgorithm algorithm(iItemsNumber, iValuesVector, iSizeVector);
			algorithm.solve();
			algorithm.printBestSolution();
		}
		catch (const std::invalid_argument&)
		{
			std::cout << "Nieprawidlowe dane wejsciowe";
		}
		catch (const std::exception&)
		{
			std::cout << "Other Exception";
		}*/
		
	}

	void printProblemDetails()
	{
		std::cout << "Knapsack problem: \n";
		std::cout << "Number of items: " << iItemsNumber << "\n";
		std::cout << "Each item and its size: \n";
		for (int i = 0; i < iValuesVector.size(); i++)
		{
			std::cout << iValuesVector[i] << " -> " << iSizeVector[i] << "\n";
		}
	}
};