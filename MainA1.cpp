#include "A1.h"

int main ()
{	
	int mapX [2]; //indexes of Grid X min and max
	int mapY [2]; // indexes of Grid Y mix and max respectively
	CityLocation *cl; // data struct pointer for citylocation.txt
	CloudCover *cc;  // data struct pointer for cloudcover.txt
	Pressure *p; // data struct pointer for pressure.txt
	ForecastSummary *fs; // data struct pointer for forecast summary
	int choice;
	fstream afile;
	string filename;
	string aline;
	bool ok = true;
	bool okX = false;
	bool okY = false;
	int citysize = 0;
	int cloudsize = 0;
	int pressuresize = 0;
	int minX;
	int maxX;
	int noOfCities;
	
	do
	{
		choice = checkValidOption (displayMenuOptions());
		
		switch (choice)
		{
			case 1: do 
				{
					cout << endl;
					cout << "[ 1. Read in and process a configuration file ]" 
					     << endl << endl
				     	     << "Please enter config filename : ";
					cin >> filename;
					ok = readFileOK (afile, filename); // check ifstream ok for reading filename
				} while (ok == false);
				
				cout << endl;
				while (afile.good ())
				{
					// process to read each line of filename
					getline (afile, aline);
					
					// Extracting data that are not comments
					// Will be true if "//" is NOT a substring of aline
					//static const size_t npos = -1;
					if (aline.find ("//") == string::npos)
					{
						if (okX == false)
						{
							if (createIndexToArray (aline, mapX, MAP))
							{
								cout << "Reading in GridX_IdxRange : " << mapX[0] << "-" << mapX[1] << "... done!" << endl;
								okX = true;
							}
						}
			
						if (okY == false)
						{
							if (createIndexToArray (aline, mapY, MAP))
							{
								cout << "Reading in GridY_IdxRange : " << mapY[0] << "-" << mapY[1] << "... done!" << endl;
								okY = true;
							}
						}
					}
					
					// Extracting sub files in main file for reading contents
					if (aline.find (".txt") != string::npos)
					{
						if (aline.compare ("citylocation.txt") == 0)
						{
							fstream afile2;
							if (readFileOK (afile2, aline))
							{
								citysize = getSizeOfRecords (afile2);
								cl = new (nothrow) CityLocation [citysize];
								if (cl == nullptr)
								{
									cout << "Error: No memory allocated" << endl;
								}
								else
								{
									readACityFile (aline, cl, citysize);
								}
							}
						}
						else if (aline.compare ("cloudcover.txt") == 0)
						{
							fstream afile3;
							if (readFileOK (afile3, aline))
							{
								cloudsize = getSizeOfRecords (afile3);
								cc = new (nothrow) CloudCover [cloudsize];
								if (cc == nullptr)
								{
									cout << "Error: No memory allocated" << endl;
								}
								else
								{
									readACloudFile (aline, cc, cloudsize);
								}
							}
						}
						else if (aline.compare ("pressure.txt") == 0)
						{
							fstream afile4;
							if (readFileOK (afile4, aline))
							{
								pressuresize = getSizeOfRecords (afile4);
								p = new (nothrow) Pressure [pressuresize];
								if (p == nullptr)
								{
									cout << "Error: No memory allocated" << endl;
								}
								else
								{
									readAPressureFile (aline, p, pressuresize);
								}
							}
						}
					}		
				}
				afile.close ();
				cout << endl
				     << "All records successfully stored. Going back to main menu …" << endl;
				break;
			case 2: if (citysize == 0)
				{
					cout << "No record to display city map!" << endl
					     << "\t Please enter option 1 to process data in main menu..." << endl;
				}
				else
				{
					cout << "[ 2. Display city map ]" 
					     << endl << endl;
					displayCityMap (mapX, mapY, cl, citysize);
				}
				break;
			case 3: if (cloudsize == 0)
				{
					cout << "No record to display cloud index map!" << endl
					     << "\t Please enter option 1 to process data in main menu..." << endl;
				}
				else
				{
					cout << "[ 3. Display cloud coverage map (cloudiness index) ]" << endl << endl;
					displayCloudMap (mapX, mapY, cc, cloudsize, choice);
				}
				break;
			case 4: if (cloudsize == 0)
				{
					cout << "No record to display cloud symbol map!" << endl
					     << "\t Please enter option 1 to process data in main menu..." << endl;
				}
				else
				{
					cout << "[ 4. Display cloud coverage map (LMH symbols) ]" << endl << endl;
					displayCloudMap (mapX, mapY, cc, cloudsize, choice);
				}
				break;
			case 5: if (pressuresize == 0)
				{
					cout << "No record to display atmospheric pressure index map!" << endl
					     << "\t Please enter option 1 to process data in main menu..." << endl;
				}
				else
				{
					cout << "[ 5. Display atmospheric pressure map (pressure index) ]" << endl << endl;
					displayPressureMap (mapX, mapY, p, pressuresize, choice);
				}
				break;
			case 6: if (pressuresize == 0)
				{
					cout << "No record to display atmospheric pressure symbol map!" << endl
					     << "\t Please enter option 1 to process data in main menu..." << endl;
				}
				else
				{
					cout << "[ 6. Display atmospheric pressure map (LMH symbols) ]" << endl << endl;
					displayPressureMap (mapX, mapY, p, pressuresize, choice);
				}
				break;
			case 7 : if ((citysize == 0) || (cloudsize == 0) || (pressuresize == 0))
				{
					cout << "No record to show weather forecast summary report!" << endl
					     << "\t Please enter option 1 to process data in main menu..." << endl;
				}
				else
				{
					cout << "[ 7. Show weather forecast summary report ]" << endl << endl;
					noOfCities = getNoDistinctCity (cl, citysize);
					fs = new (nothrow) ForecastSummary [noOfCities];
					if (fs == nullptr)
					{
						cout << "Error: No memory allocated" << endl;
					}
					else
					{
						showForecastReport (cl, cc, p, fs, citysize, cloudsize, pressuresize, noOfCities, mapX, mapY);
					}
				}
				break;
			default:delete [] cl;
				delete [] cc;
				delete [] p; 
				delete [] fs;
				
				cout << "Thank you for using Weather Information Processing System" << endl;
		}
		
	} while (choice != 8) ; //loop will break till user keys in 8) Quit
	
	return 0;
}
