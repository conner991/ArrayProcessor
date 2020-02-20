/* -----------------------------------------------------------------------------
FILE:              Array_Processor.cpp
DESCRIPTION:       This program allows the user to input a file of numbers and 
				   find out some statistical information about them. 
COMPILER:          MS Visual Studio 2017  C++ compiler
NOTES:

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Conner Fissell     2017-11-28         1.0 - Started general layout. Worked on file input.
Conner Fissell	   2017-11-30		  1.1 - Worked on sorting algorithm.
Conner Fissell	   2017-12-05		  1.2 - Established more functions. Got all of the
											main functions to return a correct-ish answer.
Conner Fissell	   2017-12-06		  1.3 - Created the Show_Results function.
Conner Fissell	   2017-12-07		  1.4 - Worked on output file connections.
----------------------------------------------------------------------------- */

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;


// Function Prototypes
void input(char[], int[], int &);
void sort(int[], int);
int find_min(int[]);
int find_max(int[], int);
double find_average(int[], int);
double find_SD(int[], int);
double find_median(int[], int);
int find_mode(int[], int);
void show_results(ofstream&, char[], char[], int, int, int, double, double, double, int);
void out_file(ofstream&, char[], char[], int, int, int, double, double, double, int);

// Global Constant
const int ARRAY_SIZE = 1000;


const string PROGRAMMER_NAME = "Conner Fissell";		// Global constant

/* -----------------------------------------------------------------------------
FUNCTION:          main()
DESCRIPTION:	   The main function
RETURNS:           0
NOTES:
------------------------------------------------------------------------------- */

int main()
{
	int numbers[ARRAY_SIZE], minimum, maximum, mode;
	int count = 0;
	double median, average, SD;
	char inputfile_name[80], outputfile_name[80];
	
	cout << "What file do you want to open? "; 
	cin >> inputfile_name; 

	cout << endl << "Where would you like to send the results? ";
	cin >> outputfile_name;
	cout << endl;
	
	//Opens file
	input(inputfile_name, numbers, count);
	
	//Array and its size gets sent through sorting function
	sort(numbers, count);
	
	//These are the statistical analysis functions
    minimum = find_min(numbers);
	maximum = find_max(numbers, count);
	average = find_average(numbers, count);
	SD = find_SD(numbers, count);
	median = find_median(numbers, count);
	mode = find_mode(numbers, count);
	
	//Opens the file
	ofstream fileout;
	fileout.open(outputfile_name);
	
	//Stat data goes into this function which connects to the display function
	out_file(fileout, outputfile_name, inputfile_name, count, minimum, maximum, average, SD, median, mode);

	//Closes output file
	fileout.close();
	

	cout << endl << endl;
	cout << "Programmed by: " << PROGRAMMER_NAME << " -- ";
	cout << __DATE__ << "  " __TIME__ << endl;
	cout << endl;

	system("pause");

	return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          input()
DESCRIPTION:	   Opens the input file and assigns it to the numbers array.
				   Also figures out how big the count is.
RETURNS:           nothing
NOTES:
------------------------------------------------------------------------------- */
void input(char inputfile_name[], int numbers[], int& count) {
	
	
	ifstream filein;
	filein.open(inputfile_name);



	while (count < ARRAY_SIZE && filein >> numbers[count]) {
		count++;
	}

	filein.close();
}

/* -----------------------------------------------------------------------------
FUNCTION:          sort()
DESCRIPTION:	   Sorts out the numbers from the file array in ascending order
				   using a selction sort.
RETURNS:           nothing
NOTES:
------------------------------------------------------------------------------- */

void sort(int filenumbers[], int size) {

	int min_index, min_value;

	for (int start = 0; start < (size - 1); start++) {

		min_index = start;
		min_value = filenumbers[start];

		for (int index = start + 1; index < size; index++) {

			if (filenumbers[index] < min_value) {

				min_value = filenumbers[index];
				min_index = index;
			}
		}
		int temp = filenumbers[min_index];
		filenumbers[min_index] = filenumbers[start];
		filenumbers[start] = temp;
	}
	
}

/* -----------------------------------------------------------------------------
FUNCTION:          find_min()
DESCRIPTION:	   Finds the lowest number in the sorted array and returns it.
RETURNS:           lowest
NOTES:
------------------------------------------------------------------------------- */

int find_min(int numbers[]) {

	int lowest;

	lowest = numbers[0];

	return lowest;
	
}

/* -----------------------------------------------------------------------------
FUNCTION:          find_max()
DESCRIPTION:	   Finds the highest number in the sorted array and returns it.
RETURNS:           max
NOTES:
------------------------------------------------------------------------------- */

int find_max(int numbers[], int size) {

	int max = numbers[0];
	
	for (int i = 1; i < size; i++) {
		if (numbers[i] > max) {
			max = numbers[i];
		}
	}

	return max;
}

/* -----------------------------------------------------------------------------
FUNCTION:          find_average()
DESCRIPTION:	   Figures out the mean for the given set of numbers. 
RETURNS:           average
NOTES:
------------------------------------------------------------------------------- */

double find_average(int numbers[], int size) {

	double sum = 0.0;
	double average;

	for (int i = 0; i < size; i++) {
		sum = (sum + numbers[i]);
	}

	average = sum / size;

	return average;
}

/* -----------------------------------------------------------------------------
FUNCTION:          find_SD()
DESCRIPTION:	   Figures out the Standard Deviation for the given set of numbers. 
RETURNS:           SD
NOTES:
------------------------------------------------------------------------------- */

double find_SD(int numbers[], int size) {

	double SD = 0.0;
	double temp_dev;
	double average;
    
	average = find_average(numbers, size);

	for (int i = 0; i < size; i++) {
		temp_dev = numbers[i] - average;
		SD += (temp_dev * temp_dev);
	}

	SD /= size;
	SD = sqrt(SD);


	return SD;
}


/* -----------------------------------------------------------------------------
FUNCTION:          find_median()
DESCRIPTION:	   Figures out the median term for the given set of numbers. 
RETURNS:           median
NOTES:
------------------------------------------------------------------------------- */

double find_median(int numbers[], int size) {

	int middle = 0;
	double median = 0;

	middle = (size / 2);
	
	if (size % 2 == 0) {
		
		median = (numbers[middle - 1] + numbers[middle]) / 2.0;
	}
	else {
		
		median = numbers[middle];
	}

	return median;
}

/* -----------------------------------------------------------------------------
FUNCTION:          find_mode()
DESCRIPTION:	   Figures out the mode(s) for the given set of numbers. 
RETURNS:           mode
NOTES:
------------------------------------------------------------------------------- */

int find_mode(int numbers[], int size) {

	int mode = 0;
	int count = 0;

	for (int i = 0; i < size; i++) {
		int temp_element = numbers[i];
		int temp_count = 0;
			
			for (int x = 0; x < size; x++) {
				if (numbers[x] == temp_element) { 
					temp_count++;
				}
				
				if (temp_count > count) {
					mode = temp_element;
					count = temp_count;
				}
			}
	}

	return mode;
}

/* -----------------------------------------------------------------------------
FUNCTION:          show_results()
DESCRIPTION:	   Displays the output to the screen. 
RETURNS:           nothing
NOTES:
------------------------------------------------------------------------------- */

void show_results(ofstream& fileout, char outputfile_name[], char inputfile_name[], int count, int minimum, int maximum, double average, double SD, double median, int mode) {

	cout << "Input File: " << inputfile_name << endl << endl;
	cout << "No. Points: " << count << endl;
	cout << "The Min is: " << minimum << endl;
	cout << "The Max is: " << maximum << endl;
	cout << "The Avg is: " << average << endl;
	cout << "Std Dev is: " << SD << endl;
	cout << "Median  is: " << median << endl;
	cout << "Modes  are: " << mode << endl << endl;
	cout << "Output filename: " << outputfile_name << endl;


	fileout << "Input File: " << inputfile_name << endl << endl;
	fileout << "No. Points: " << count << endl;
	fileout << "The Min is: " << minimum << endl;
	fileout << "The Max is: " << maximum << endl;
	fileout << "The Avg is: " << average << endl;
	fileout << "Std Dev is: " << SD << endl;
	fileout << "Median  is: " << median << endl;
	fileout << "Modes  are: " << mode << endl;
}

/* -----------------------------------------------------------------------------
FUNCTION:          out_file()
DESCRIPTION:	   Passes all of the data through to the show_results function.
RETURNS:           nothing
NOTES:
------------------------------------------------------------------------------- */

void out_file(ofstream& fileout, char outputfile_name[], char inputfile_name[], int count, int minimum, int maximum, double average, double SD, double median, int mode) {

	show_results(fileout, outputfile_name, inputfile_name, count, minimum, maximum, average, SD, median, mode);
}