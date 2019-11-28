#include "A1.h"

void CityLocation::toString (int no, char name [], int id, GridIndices gi)
{
	cout << no << ") City name: " << name << endl
	     << " ID: " << id << endl
	     << "\t grid X: " << gi.gridXY[0] 
	     << " Y: " << gi.gridXY[1] << endl << endl;
}

void CloudCover::toString (int no, GridIndices gi, int forecast)
{
	cout << no << ") Grid X: " << gi.gridXY[0] 
	     << " Y: " << gi.gridXY[1] << endl 
	     << "\t Forecast: " << forecast << endl;
}

void Pressure::toString (int no, GridIndices gi, int forecast)
{
	cout << no << ") Grid X: " << gi.gridXY[0] 
	     << " Y: " << gi.gridXY[1] << endl 
	     << "\t Forecast: " << forecast << endl;
}

int displayMenuOptions ()
{
	int choice;
	
	cout << endl << "Student ID   : 5841549" << endl
	     << "Student Name : Nur Suhaira Bte Badrul Hisham" << endl
	     << "--------------------------------------------" << endl
	     << "Welcome to Weather Information Processing System" 
	     << endl << endl
	     << "1) \t Read in and process a configuration file" << endl
	     << "2) \t Display city map" << endl
	     << "3) \t Display cloud coverage map (cloudiness index)" << endl
	     << "4) \t Display cloud coverage map (LMH symbols)" << endl
	     << "5) \t Display atmospheric pressure map (pressure index)" << endl
	     << "6) \t Display atmospheric pressure map (LMH symbols)" << endl
	     << "7) \t Show weather forecast summary report" << endl
	     << "8) \t Quit" << endl
	     << endl << "Please enter your choice: ";
	cin >> choice;
	
	return choice;
}

int checkValidOption (int option)
{
	switch (option)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8: return option; 
		default: do
			 {
			 	cout << endl << "You have entered an invalid menu option. Please re-enter..."
			          	     << endl;
				option = displayMenuOptions ();
				
			 } while ((option != 1) || (option != 2) || (option != 3) ||
			          (option != 4) || (option != 5) || (option != 6) || 
			          (option != 7) || (option != 8));
	}
	
	return option;
}

bool readFileOK (fstream& afile, string filename)
{
	afile.open (filename, ios::in);
	
	if (!afile)
	{
		cout << filename << " open for reading failed" << endl;
		return false;
	}

	return true;
}

int getSizeOfRecords (fstream& afile)
{
	string aline;
	int i = 0;
	while (getline (afile, aline))
	{	if (aline.length() != 0)
		{
			++i;	
		}
	}
	
	return i;
}

bool createIndexToArray (string str, int xy [], int MAP)
{	
	int j = 0;
	for (int i = 0; i < str.length(); i++)
	{
		// Checking the given char in a string contains integer
		if (isdigit (str[i]))
		{	
			xy[j] = str[i] - '0';
			++j;		
		}
	}

	if (j == MAP)
	{
		return true;	
	}
	
	return false;
}

void readACityFile (string filename, CityLocation cl [], int size)
{
	char temp;
	string aline;
	
	cout << endl
	     << "Storing data from " << filename << " :" << endl;
	
	int i = 0;
	fstream afile (filename.c_str(), fstream::in);
	// extracting data till SIZE but stops at delimiter
	while ((i < size) && (afile.getline (cl[i].gi.gridIndices, SIZE, DELIMITER)))
	{				
		//        *     *
		// e.g. 0 1 2 3 4 5
		//      [ 1 ,   1 ]
		// indexes will always be one digit ** (< 10)
		if (createIndexToArray (cl[i].gi.gridIndices, cl[i].gi.gridXY, MAP))
		{
			afile >> cl[i].cityID; // extracting int data
			temp = afile.get (); // store "-" in a char temp
			if (temp == DELIMITER)
			{
				afile.getline (cl[i].cityName, SIZE); // store city name after extraction of temp

			}
			
			afile.clear ();
		}
		// cl[i].toString (i+1, cl[i].cityName, cl[i].cityID, cl[i].gi);
		++i;
	}
		
	afile.close ();
	
	cout << endl << filename << "... done!" << endl;
}

void readACloudFile (string filename, CloudCover cc [], int size)
{
	string aline;
	int temp;
	
	cout << endl
	     << "Storing data from " << filename << " :" << endl;
	
	int i = 0;
	fstream afile (filename.c_str(), fstream::in);
	// extracting data till SIZE but stops at delimiter
	while ((i < size) && (afile.getline (cc[i].gi.gridIndices, SIZE, DELIMITER)))
	{				
		//        *     *
		// e.g. 0 1 2 3 4 5
		//      [ 1 ,   1 ]
		// indexes will always be one digit ** (< 10)
		if (createIndexToArray (cc[i].gi.gridIndices, cc[i].gi.gridXY, MAP))
		{
			afile >> temp; // extracting int data
			if ((temp > -1) && (temp < 100))
			{
				cc[i].forecast = temp;
			}
			afile.clear ();
		}
		// cc[i].toString (i+1, cc[i].gi, cc[i].forecast);
		++i;
	}
		
	afile.close ();
	
	cout << endl << filename << "... done!" << endl;
}

void readAPressureFile (string filename, Pressure p [], int size)
{
	string aline;
	int temp;
	
	cout << endl
	     << "Storing data from " << filename << " :" << endl;
	
	int i = 0;
	fstream afile (filename.c_str(), fstream::in);
	// extracting data till SIZE but stops at delimiter
	while ((i < size) && (afile.getline (p[i].gi.gridIndices, SIZE, DELIMITER)))
	{				
		//        *     *
		// e.g. 0 1 2 3 4 5
		//      [ 1 ,   1 ]
		// indexes will always be one digit ** (< 10)
		if (createIndexToArray (p[i].gi.gridIndices, p[i].gi.gridXY, MAP))
		{
			afile >> temp; // extracting int data
			if ((temp > -1) && (temp < 100))
			{
				p[i].forecast = temp;
			}
			afile.clear ();
		}
		// p[i].toString (i+1, p[i].gi, p[i].forecast);
		++i;
	}
		
	afile.close ();
	
	cout << endl << filename << "... done!" << endl;
}

void displayCityMap (int x [], int y [], CityLocation cl [], int size)
{
	string hex = "# ";
	int valueY = y[1];
	int valueX = x[0];
	int minX = abs (x[0]); // remove any negative sign in min value x of map
	int maxX = minX+x[1]+1+2; // add 1 for value 0 in map, add 2 for spacing
	int minY = abs (y[0]); // remove any negative sign in min value y of map
	int maxY = minY+y[1]+1+2; // add 1 for value 0 in map, add 2 for spacing
	static bool cityfound = false; // if there is a city occupied within the row then true
	
	for (int y = minY; y < maxY; y++) // rows
	{
		if ((y == minY) || (y == maxY-1)) // if y in first and last row print a line of #
		{
			cout << "  ";
			for (int i = 0; i < maxY; i++)
			{
				cout << hex; // print maxY times in a line
			}
			
			cout << endl; // move on to next line
		}
		else // if y is not in first and last row do this
		{
			cout << valueY << " "; // displaying indices not on first and last rows
			for (int x = minX; x < maxX; x++) // columns
			{
				if ((y != minY) || (y != maxY-1)) // if x is not in y first and last row print #
				{
					if ((x == minX) || (x == maxX-1)) // if x in the edge of the map then print # and a spacing
					{
						cout << hex;
					}
					else // within the empty spaces of the map
					{
						for (int a = 0; a < size; a++)
						{
							// x-1 as x in map starts with 0
							if ((cl[a].gi.gridXY[0] == x-1) && (cl[a].gi.gridXY[1] == valueY)) // compare with valueY as it matches the value in map
							{
								cout << cl[a].cityID << " "; // printing city id with a space
								cityfound = true;
							}
						}
						if (cityfound == false)
						{
							cout << "  "; // no city id print 2 spaces
						}
						
						cityfound = false; // set back to false again to move on to next row
					}
				}
			}
			cout << endl; // once x is done with the printing on 1 line move on to next line
			--valueY; // decrement of y indices after every row
		}
	}
	
	cout << "    "; // to start indexing x indices from 4 spaces onwards
	// due to y indices and 2 spacing
	for (int z = 0; z < maxY-2; z++)
	{
		cout << valueX << " ";
		++valueX; // increment of y indices after every row
	}
	
	cout << endl << endl;
}

int getCloudIndex (int value, string &message)
{
	if ((value < 0) || (value > 99))
	{
		message = "Invalid cloud cover value";
		return -1;
	}
	
	if (value < 10)
	{
		if (value == 0)
		{
			message = "Not a single wisp of cloud - \"clear blue skies\" for the grid area!";
		}
		return 0;
	}
	else if (value < 20)
	{
		return 1;
	}
	else if (value < 30)
	{
		return 2;
	}
	else if (value < 40)
	{
		return 3;
	}
	else if (value < 50)
	{
		return 4;
	}
	else if (value < 60)
	{
		return 5;
	}
	else if (value < 70)
	{
		return 6;
	}
	else if (value < 80)
	{
		return 7;
	}
	else if (value < 90)
	{
		return 8;
	}
	
	if (value == 99)
	{
		message = "Grid area is forecasted to be entirely covered with thick clouds!";
	}
	
	return 9;
}

char getSymbol (int value)
{
	if ((value < 0) || (value > 99))
	{
		return '-';
	}
	
	if (value < 35)
	{
		return 'L';
	}
	else if (value < 65)
	{
		return 'M';
	}
	
	return 'H';
}

void displayCloudMap (int x [], int y [], CloudCover cc [], int size, int menu)
{
	char tempChar;
	int tempInt;
	string message;
	string hex = "# ";
	int valueY = y[1];
	int valueX = x[0];
	int minX = abs (x[0]); // remove any negative sign in min value x of map
	int maxX = minX+x[1]+1+2; // add 1 for value 0 in map, add 2 for spacing
	int minY = abs (y[0]); // remove any negative sign in min value y of map
	int maxY = minY+y[1]+1+2; // add 1 for value 0 in map, add 2 for spacing
	static bool cloudfound = false; // if there is a cloud occupied within the row then true
	
	for (int y = minY; y < maxY; y++) // rows
	{
		if ((y == minY) || (y == maxY-1)) // if y in first and last row print a line of #
		{
			cout << "  ";
			for (int i = 0; i < maxY; i++)
			{
				cout << hex; // print maxY times in a line
			}
			
			cout << endl; // move on to next line
		}
		else // if y is not in first and last row do this
		{
			cout << valueY << " "; // displaying indices not on first and last rows
			for (int x = minX; x < maxX; x++) // columns
			{
				if ((y != minY) || (y != maxY-1)) // if x is not in y first and last row print #
				{
					if ((x == minX) || (x == maxX-1)) // if x in the edge of the map then print # and a spacing
					{
						cout << hex;
					}
					else // within the empty spaces of the map
					{
						for (int a = 0; a < size; a++)
						{
							// x-1 as x in map starts with 0
							if ((cc[a].gi.gridXY[0] == x-1) && (cc[a].gi.gridXY[1] == valueY)) // compare with valueY as it matches the value in map
							{
								// dereference int pointer to extract the int value
								switch (menu)
								{
									case 3: tempInt = getCloudIndex (int (cc[a].forecast), message);
										if (tempInt != -1)
										{
											cout << tempInt << " "; // printing cloud index with a space
										}
										else
										{
											cout << DELIMITER << " ";
										}
										break;
									case 4: tempChar = getSymbol (int (cc[a].forecast));
										cout << tempChar << " "; // printing cloud symbol with a space
								}
								
								cloudfound = true;
							}
						}
						if (cloudfound == false)
						{
							cout << "  "; // no cloud index/symbol print 2 spaces
						}
						
						cloudfound = false; // set back to false again to move on to next row
					}
				}
			}
			cout << endl; // once x is done with the printing on 1 line move on to next line
			--valueY; // decrement of y indices after every row
		}
	}
	
	cout << "    "; // to start indexing x indices from 4 spaces onwards
	// due to y indices and 2 spacing
	for (int z = 0; z < maxY-2; z++)
	{
		cout << valueX << " ";
		++valueX; // increment of y indices after every row
	}
	
	cout << endl << endl;
}

int getPressureIndex (int value, string &message)
{
	if ((value < 0) || (value > 99))
	{
		message = "Invalid pressure value";
		return -1;
	}
	
	if (value < 10)
	{
		if (value == 0)
		{
			message = "The grid area will experience no pressure!";
		}
		return 0;
	}
	else if (value < 20)
	{
		return 1;
	}
	else if (value < 30)
	{
		return 2;
	}
	else if (value < 40)
	{
		return 3;
	}
	else if (value < 50)
	{
		return 4;
	}
	else if (value < 60)
	{
		return 5;
	}
	else if (value < 70)
	{
		return 6;
	}
	else if (value < 80)
	{
		return 7;
	}
	else if (value < 90)
	{
		return 8;
	}
	
	if (value == 99)
	{
		message = "The grid area will experience extremely high pressure!";
	}
	
	return 9;
}

void displayPressureMap (int x [], int y [], Pressure p [], int size, int menu)
{
	int tempInt;
	char tempChar;
	string message;
	string hex = "# ";
	int valueY = y[1];
	int valueX = x[0];
	int minX = abs (x[0]); // remove any negative sign in min value x of map
	int maxX = minX+x[1]+1+2; // add 1 for value 0 in map, add 2 for spacing
	int minY = abs (y[0]); // remove any negative sign in min value y of map
	int maxY = minY+y[1]+1+2; // add 1 for value 0 in map, add 2 for spacing
	static bool pressurefound = false; // if there is pressure occupied within the row then true
	
	for (int y = minY; y < maxY; y++) // rows
	{
		if ((y == minY) || (y == maxY-1)) // if y in first and last row print a line of #
		{
			cout << "  ";
			for (int i = 0; i < maxY; i++)
			{
				cout << hex; // print maxY times in a line
			}
			
			cout << endl; // move on to next line
		}
		else // if y is not in first and last row do this
		{
			cout << valueY << " "; // displaying indices not on first and last rows
			for (int x = minX; x < maxX; x++) // columns
			{
				if ((y != minY) || (y != maxY-1)) // if x is not in y first and last row print #
				{
					if ((x == minX) || (x == maxX-1)) // if x in the edge of the map then print # and a spacing
					{
						cout << hex;
					}
					else // within the empty spaces of the map
					{
						for (int a = 0; a < size; a++)
						{
							// x-1 as x in map starts with 0
							if ((p[a].gi.gridXY[0] == x-1) && (p[a].gi.gridXY[1] == valueY)) // compare with valueY as it matches the value in map
							{
								// dereference int pointer to extract the int value
								switch (menu)
								{
									case 5: tempInt = getPressureIndex (int (p[a].forecast), message);
										if (tempInt != -1)
										{
											cout << tempInt << " "; // printing cloud index with a space
										}
										else
										{
											cout << DELIMITER << " "; // printing delimiter with a space
										}
										break;
									case 6: tempChar = getSymbol (int (p[a].forecast));
										cout << tempChar << " "; // printing cloud symbol with a space
								}
								
								pressurefound = true;
							}
						}
						if (pressurefound == false)
						{
							cout << "  "; // no pressure print 2 spaces
						}
						
						pressurefound = false; // set back to false again to move on to next row
					}
				}
			}
			cout << endl; // once x is done with the printing on 1 line move on to next line
			--valueY; // decrement of y indices after every row
		}
	}
	
	cout << "    "; // to start indexing x indices from 4 spaces onwards
	// due to y indices and 2 spacing
	for (int z = 0; z < maxY-2; z++)
	{
		cout << valueX << " ";
		++valueX; // increment of y indices after every row
	}
	
	cout << endl << endl;
}

int getNoDistinctCity (CityLocation cl [], int size)
{
	int no = 0;
	for (int i = 0; i < size; i++)
	{
		int j; // to store index in block so can be used later
		for (j = 0; j < i; j++) // to iterate to current i index
		{
			if (cl[i].cityID == cl[j].cityID) // if equal means same value (not distinct)
			{
				break;
			}
		}
		if (i == j) // if both i and j indexes are same means same value in same index
		{
			++no; // to count since values are distinct (same indexes; not repeated)
		}
		
	}
	return no;
}

void createForecastSummary (CityLocation cl [], ForecastSummary fs [], int size)
{
	int no = 0;
	for (int i = 0; i < size; i++)
	{
		int j; // to store index in block so can be used later
		for (j = 0; j < i; j++) // to iterate to current i index
		{
			if (cl[i].cityID == cl[j].cityID) // if equal means same value (not distinct)
			{
				break;
			}
		}
		if (i == j) // if both i and j indexes are same means same value in same index
		{
			fs[no].cityID = cl[i].cityID;
			strcpy (fs[no].cityName, cl[i].cityName);
			++no;
		}
	}
}

void markCityOccupiedCC (CityLocation cl [], int fs, CloudCover cc [], int clsize, int csize)
{
	for (int j = 0; j < clsize; j++)
	{
		if (fs == cl[j].cityID) // getting the distinct id to match with individual city id
		{
			for (int k = 0; k < csize; k++) // if match, we extract the cloud cover value
			{
				// by matching both x and y grids match
				if ((cl[j].gi.gridXY [0] == cc[k].gi.gridXY [0])
				&& (cl[j].gi.gridXY [1] == cc[k].gi.gridXY [1]))
				{
					cc[k].cityFound = true;
				}
			}
		} 
	}
}

double calcAvgCC (CityLocation cl [], int fs, CloudCover cc [], int clsize, int csize, int x [], int y [])
{
	double totalCityCC = 0.0;
	int noOfGridArea = 0;
	
	for (int j = 0; j < clsize; j++)
	{
		if (fs == cl[j].cityID) // getting the distinct id to match with individual city id
		{
			for (int k = 0; k < csize; k++) // if match, we extract the cloud cover value
			{
				// by matching both x and y grids match
				if ((cl[j].gi.gridXY [0] == cc[k].gi.gridXY [0])
				&& (cl[j].gi.gridXY [1] == cc[k].gi.gridXY [1]))
				{
					++noOfGridArea;
					// sum up the cloud cover value of cities
					totalCityCC += cc[k].forecast;
					// sum up the cloud cover values of surrounding grids of the city
					for (int l = 0; l < csize; l++)
					{
						// top grid of city (x, y+1)
						// matching the city surrounding grid with CC grids
						if ((cc[k].gi.gridXY[0] == cc[l].gi.gridXY[0]) && (cc[k].gi.gridXY[1]+1 == cc[l].gi.gridXY[1]))
						{
							// ensure the grids are within the map grids
							// increment of y axis so check upper limit of y axis
							// check that there is no city on grid
							// check that grid has not been used
							 if ((cc[l].gi.gridXY [1] <= y[1]) && (cc[l].cityFound == false) && (cc[l].surroundFound == false))
							 {
							  								 	cc[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityCC += cc[l].forecast;
							 }	
						}
						// top right of city (x+1, y+1)
						else if ((cc[k].gi.gridXY[0]+1 == cc[l].gi.gridXY[0]) && (cc[k].gi.gridXY[1]+1 == cc[l].gi.gridXY[1]))
						{
							// increment of x and y axis so check upper limit of x and y axis
							if ((cc[l].gi.gridXY [0] <= x[1]) && (cc[l].gi.gridXY [1] <= y[1]) && (cc[l].cityFound == false) && (cc[l].surroundFound == false))
							 {
							 	cc[l].surroundFound = true; 								 	++noOfGridArea;
							 	totalCityCC += cc[l].forecast;
							 }
						}
						// right of city (x+1, y)
						else if ((cc[k].gi.gridXY[0]+1 == cc[l].gi.gridXY[0]) && (cc[k].gi.gridXY[1] == cc[l].gi.gridXY[1]))
						{
							// increment of x axis so check upper limit of x axis
							if ((cc[l].gi.gridXY [0] <= x[1]) && (cc[l].cityFound == false) && (cc[l].surroundFound == false))
							 {
								cc[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityCC += cc[l].forecast;
							 }
						}
						// bottom right of city (x+1, y-1)
						else if ((cc[k].gi.gridXY[0]+1 == cc[l].gi.gridXY[0]) && (cc[k].gi.gridXY[1]-1 == cc[l].gi.gridXY[1]))
						{
							// increment of x axis so check upper limit of x axis but decrement of y axis so check lower limit of y axis
							if ((cc[l].gi.gridXY [0] <= x[1]) && (cc[l].gi.gridXY [1] >= y[0]) && (cc[l].cityFound == false) && (cc[l].surroundFound == false))
							 {
							 	cc[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityCC += cc[l].forecast;
							 }
						}
						// bottom of city (x, y-1)
						else if ((cc[k].gi.gridXY[0] == cc[l].gi.gridXY[0]) && (cc[k].gi.gridXY[1]-1 == cc[l].gi.gridXY[1]))
						{
							// decrement of y axis so check lower limit of y axis
							if ((cc[l].gi.gridXY [1] >= y[0]) && (cc[l].cityFound == false) && (cc[l].surroundFound == false))
							{
								cc[l].surroundFound = true; 								 	++noOfGridArea;
							 	totalCityCC += cc[l].forecast;
							 }
						}
						// bottom left of city (x-1, y-1)
						else if ((cc[k].gi.gridXY[0]-1 == cc[l].gi.gridXY[0]) && (cc[k].gi.gridXY[1]-1 == cc[l].gi.gridXY[1]))
						{
							// decrement of x and y axis so check lower limit of x and y axis
							if ((cc[l].gi.gridXY [0] >= x[0]) && (cc[l].gi.gridXY [1] >= y[0]) && (cc[l].cityFound == false) && (cc[l].surroundFound == false))
							{
								cc[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityCC += cc[l].forecast;
							 }
						}
						// left of city (x-1, y)
						else if ((cc[k].gi.gridXY[0]-1 == cc[l].gi.gridXY[0]) && (cc[k].gi.gridXY[1] == cc[l].gi.gridXY[1]))
						{
							// decrement of x axis so check lower limit of x axis
							if ((cc[l].gi.gridXY [0] >= x[0]) && (cc[l].cityFound == false) && (cc[l].surroundFound == false))
							{
								cc[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityCC += cc[l].forecast;
							 }
						}
						// top left of city (x-1, y+1)
						else if ((cc[k].gi.gridXY[0]-1 == cc[l].gi.gridXY[0]) && (cc[k].gi.gridXY[1]+1 == cc[l].gi.gridXY[1]))
						{
							// decrement of x axis so check lower limit of x axis but increment of y axis so check upper limit of y axis
							if ((cc[l].gi.gridXY [0] >= x[0]) && (cc[l].gi.gridXY [1] <= y[1]) && (cc[l].cityFound == false) && (cc[l].surroundFound == false))
							{
								cc[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityCC += cc[l].forecast;
							 }
						}
					}
					
				}
			}
		} 
	}

	return (static_cast<double> (totalCityCC) / noOfGridArea);
}

void resetCCSurround (CloudCover cc [], int size)
{
	for (int i = 0; i < size; i++)
	{
		cc[i].cityFound = false;
		cc[i].surroundFound = false;
	}
}

void markCityOccupiedP (CityLocation cl [], int fs, Pressure p [], int clsize, int psize)
{
	for (int j = 0; j < clsize; j++)
	{
		if (fs == cl[j].cityID) // getting the distinct id to match with individual city id
		{
			for (int k = 0; k < psize; k++) // if match, we extract the cloud cover value
			{
				// by matching both x and y grids match
				if ((cl[j].gi.gridXY [0] == p[k].gi.gridXY [0])
				&& (cl[j].gi.gridXY [1] == p[k].gi.gridXY [1]))
				{
					p[k].cityFound = true;
				}
			}
		} 
	}
}

double calcAvgP (CityLocation cl [], int fs, Pressure p [], int clsize, int psize, int x [], int y [])
{
	double totalCityP = 0.0;
	int noOfGridArea = 0;
	
	for (int j = 0; j < clsize; j++)
	{
		if (fs == cl[j].cityID) // getting the distinct id to match with individual city id
		{
			for (int k = 0; k < psize; k++) // if match, we extract the pressure value
			{
				// by matching both x and y grids match
				if ((cl[j].gi.gridXY [0] == p[k].gi.gridXY [0])
				&& (cl[j].gi.gridXY [1] == p[k].gi.gridXY [1]))
				{
					++noOfGridArea;
					// sum up the pressure value of cities
					totalCityP += p[k].forecast;
					// sum up the pressure values of surrounding grids of the city
					for (int l = 0; l < psize; l++)
					{
						// top grid of city (x, y+1)
						// matching the city surrounding grid with P grids
						if ((p[k].gi.gridXY[0] == p[l].gi.gridXY[0]) && (p[k].gi.gridXY[1]+1 == p[l].gi.gridXY[1]))
						{
							// ensure the grids are within the map grids
							// increment of y axis so check upper limit of y axis
							// check that there is no city on grid
							// check that grid has not been used
							 if ((p[l].gi.gridXY [1] <= y[1]) && (p[l].cityFound == false) && (p[l].surroundFound == false))
							 {
							  								 	p[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityP += p[l].forecast;
							 }	
						}
						// top right of city (x+1, y+1)
						else if ((p[k].gi.gridXY[0]+1 == p[l].gi.gridXY[0]) && (p[k].gi.gridXY[1]+1 == p[l].gi.gridXY[1]))
						{
							// increment of x and y axis so check upper limit of x and y axis
							if ((p[l].gi.gridXY [0] <= x[1]) && (p[l].gi.gridXY [1] <= y[1]) && (p[l].cityFound == false) && (p[l].surroundFound == false))
							 {
							 	p[l].surroundFound = true; 								 	++noOfGridArea;
							 	totalCityP += p[l].forecast;
							 }
						}
						// right of city (x+1, y)
						else if ((p[k].gi.gridXY[0]+1 == p[l].gi.gridXY[0]) && (p[k].gi.gridXY[1] == p[l].gi.gridXY[1]))
						{
							// increment of x axis so check upper limit of x axis
							if ((p[l].gi.gridXY [0] <= x[1]) && (p[l].cityFound == false) && (p[l].surroundFound == false))
							 {
								p[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityP += p[l].forecast;
							 }
						}
						// bottom right of city (x+1, y-1)
						else if ((p[k].gi.gridXY[0]+1 == p[l].gi.gridXY[0]) && (p[k].gi.gridXY[1]-1 == p[l].gi.gridXY[1]))
						{
							// increment of x axis so check upper limit of x axis but decrement of y axis so check lower limit of y axis
							if ((p[l].gi.gridXY [0] <= x[1]) && (p[l].gi.gridXY [1] >= y[0]) && (p[l].cityFound == false) && (p[l].surroundFound == false))
							 {
							 	p[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityP += p[l].forecast;
							 }
						}
						// bottom of city (x, y-1)
						else if ((p[k].gi.gridXY[0] == p[l].gi.gridXY[0]) && (p[k].gi.gridXY[1]-1 == p[l].gi.gridXY[1]))
						{
							// decrement of y axis so check lower limit of y axis
							if ((p[l].gi.gridXY [1] >= y[0]) && (p[l].cityFound == false) && (p[l].surroundFound == false))
							{
								p[l].surroundFound = true; 								 	++noOfGridArea;
							 	totalCityP += p[l].forecast;
							 }
						}
						// bottom left of city (x-1, y-1)
						else if ((p[k].gi.gridXY[0]-1 == p[l].gi.gridXY[0]) && (p[k].gi.gridXY[1]-1 == p[l].gi.gridXY[1]))
						{
							// decrement of x and y axis so check lower limit of x and y axis
							if ((p[l].gi.gridXY [0] >= x[0]) && (p[l].gi.gridXY [1] >= y[0]) && (p[l].cityFound == false) && (p[l].surroundFound == false))
							{
								p[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityP += p[l].forecast;
							 }
						}
						// left of city (x-1, y)
						else if ((p[k].gi.gridXY[0]-1 == p[l].gi.gridXY[0]) && (p[k].gi.gridXY[1] == p[l].gi.gridXY[1]))
						{
							// decrement of x axis so check lower limit of x axis
							if ((p[l].gi.gridXY [0] >= x[0]) && (p[l].cityFound == false) && (p[l].surroundFound == false))
							{
								p[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityP += p[l].forecast;
							 }
						}
						// top left of city (x-1, y+1)
						else if ((p[k].gi.gridXY[0]-1 == p[l].gi.gridXY[0]) && (p[k].gi.gridXY[1]+1 == p[l].gi.gridXY[1]))
						{
							// decrement of x axis so check lower limit of x axis but increment of y axis so check upper limit of y axis
							if ((p[l].gi.gridXY [0] >= x[0]) && (p[l].gi.gridXY [1] <= y[1]) && (p[l].cityFound == false) && (p[l].surroundFound == false))
							{
								p[l].surroundFound = true;
							 	++noOfGridArea;
							 	totalCityP += p[l].forecast;
							 }
						}
					}
					
				}
			}
		} 
	}
	
	return (static_cast<double> (totalCityP) / noOfGridArea);
}

void resetPSurround (Pressure p [], int size)
{
	for (int i = 0; i < size; i++)
	{
		p[i].cityFound = false;
		p[i].surroundFound = false;
	}
}

int getProbabilityRain (char p, char c, string& str)
{
	if ((p == 'L') && (c == 'H'))
	{
		str = "~~~~\n~~~~~\n\\\\\\\\\\";
		return 90;
	}
	else if ((p == 'L') && (c == 'M'))
	{
		str = "~~~~\n~~~~~\n\\\\\\\\";
		return 80;
	}
	else if ((p == 'L') && (c == 'L'))
	{
		str = "~~~~\n~~~~~\n  \\\\\\";
		return 70;
	}
	else if ((p == 'M') && (c == 'H'))
	{
		str = "~~~~\n~~~~~\n   \\\\";
		return 60;
	}
	else if ((p == 'M') && (c == 'M'))
	{
		str = "~~~~\n~~~~~\n    \\";
		return 50;
	}
	else if ((p == 'M') && (c == 'L'))
	{
		str = "~~~~\n~~~~~\n";
		return 40;
	}
	else if ((p == 'H') && (c == 'H'))
	{
		str = "~~~\n~~~~\n";
		return 30;
	}
	else if ((p == 'H') && (c == 'M'))
	{
		str = "~~~\n~~~\n";
		return 20;
	}
	
	str = "~\n~~\n";
	return 10;
}

void getHighest (ForecastSummary fs [], int size)
{
	double maxCC;
	double maxP;
	char cityCC [SIZE];
	char cityP [SIZE];
	bool flagCC = false;
	bool flagP = false;
	
	maxCC = fs[0].avgCloudCover;
	maxP = fs[0].avgPressure;
	strcpy (cityCC, fs[0].cityName);
	strcpy (cityP, fs[0].cityName);
	
	for (int i = 1; i < size; i++)
	{
		if (fs[i].avgCloudCover > maxCC)
		{
			maxCC = fs[i].avgCloudCover;
			strcpy (cityCC, fs[i].cityName);
		}
		else if (fs[i].avgCloudCover == maxCC)
		{
			flagCC = true;
		}
		
		if (fs[i].avgPressure > maxP)
		{
			maxP = fs[i].avgPressure;
			strcpy (cityP, fs[i].cityName);
		}
		else if (fs[i].avgPressure == maxP)
		{
			flagP = true;
		}
	
	}
	
	cout << "Highest Cloud Cover (CC)" << endl
	     << "------------------------" << endl;	
	if (flagCC == false)
	{
		cout << "City Name       : " << cityCC << endl
		     << "Cloud Cover (CC): " << maxCC << endl;
	}
	else
	{
		cout << "More than 1 cities have a value of : " << maxCC << endl;
	}
	
	cout << endl
	     << "Highest Pressure (P)" << endl
	     << "------------------------" << endl;	
	if (flagP == false)
	{
		cout << "City Name       : " << cityP << endl
		     << "Pressure (P)    : " << maxP << endl;
	}
	else
	{
		cout << "More than 1 cities have a value of : " << maxP << endl;
	}
	cout << endl;
}

void getLowest (ForecastSummary fs [], int size)
{
	double minCC;
	double minP;
	char cityCC [SIZE];
	char cityP [SIZE];
	bool flagCC = false;
	bool flagP = false;
	
	minCC = fs[0].avgCloudCover;
	minP = fs[0].avgPressure;
	strcpy (cityCC, fs[0].cityName);
	strcpy (cityP, fs[0].cityName);
	
	for (int i = 1; i < size; i++)
	{
		if (fs[i].avgCloudCover < minCC)
		{
			minCC = fs[i].avgCloudCover;
			strcpy (cityCC, fs[i].cityName);
		}
		else if (fs[i].avgCloudCover == minCC)
		{
			flagCC = true;
		}
		
		if (fs[i].avgPressure < minP)
		{
			minP = fs[i].avgPressure;
			strcpy (cityP, fs[i].cityName);
		}
		else if (fs[i].avgPressure == minP)
		{
			flagP = true;
		}
	
	}
	
	cout << "Lowest Cloud Cover (CC)" << endl
	     << "------------------------" << endl;	
	if (flagCC == false)
	{
		cout << "City Name       : " << cityCC << endl
		     << "Cloud Cover (CC): " << minCC << endl;
	}
	else
	{
		cout << "More than 1 cities have a value of : " << minCC << endl;
	}
	
	cout << endl
	     << "Lowest Pressure (P)" << endl
	     << "------------------------" << endl;	
	if (flagP == false)
	{
		cout << "City Name       : " << cityP << endl
		     << "Pressure (P)    : " << minP << endl;
	}
	else
	{
		cout << "More than 1 cities have a value of : " << minP << endl;
	}
	cout << endl;
}

void showForecastReport (CityLocation cl [], CloudCover cc [], Pressure p [], ForecastSummary fs [], int clsize, int csize, int psize, int fsize, int x [], int y [])
{
	double avgCC;
	char avgCCsym;
	double avgP;
	char avgPsym;
	string graphics;
	double probRain;
	
	double minCC;
	double minP;
	char mincityCC [SIZE];
	char mincityP [SIZE];
	bool minflagCC = false;
	bool minflagP = false;
	
	createForecastSummary (cl, fs, clsize);
	
	if (fs == nullptr)
	{
		cout << "Error: No memory allocated" << endl;
	}
	else
	{
		cout << endl
		     << "Weather Forecast Summary Report" << endl
		     << "-------------------------------" << endl;
		for (int no = 0; no < fsize; no++)
		{  
			markCityOccupiedCC (cl, int (fs[no].cityID), cc, clsize, csize);
			avgCC = calcAvgCC (cl, int (fs[no].cityID), cc, clsize, csize, x, y);
			fs[no].avgCloudCover = avgCC;
			avgCCsym = getSymbol (avgCC);
			resetCCSurround (cc, csize);
			
			markCityOccupiedP (cl, int (fs[no].cityID), p, clsize, psize);
			avgP = calcAvgP (cl, int (fs[no].cityID), p, clsize, psize, x, y);
			fs[no].avgPressure = avgP;
			avgPsym = getSymbol (avgP);
			resetPSurround (p, psize);
			probRain = getProbabilityRain (avgPsym, avgCCsym, graphics);
			cout << "City Name : " << fs[no].cityName << endl
			     << "City ID   : " << fs[no].cityID << endl
			     << "Ave. Cloud Cover (ACC) \t: " << fixed << setprecision (2) << avgCC 
			     << " (" << avgCCsym << ")" << endl
			     << "Ave. Pressure    (AP)  \t: " << fixed << setprecision (2) << avgP 				     <<  " (" << avgPsym << ")" << endl
			     << "Probability of Rain (%)\t: " << fixed << setprecision (2) << probRain 				     << endl
			     << graphics
			     << endl << endl;
		}
		
		getHighest (fs, fsize);
		getLowest (fs, fsize);
	}
	
	
}
