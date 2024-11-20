#include "SatComRelay.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#define width 40
#define height 20

char scanresult;
int toggle = 1;
int toggle2 = 1;
long initialEnergy;
long currEnergy;
long currShieldEnergy;
long totEnergyUsed;
long totShieldEnergyUsed;
long energyToAllocate;
bool randomizeStartPosition;
bool Nmove = false;
int vehiclex = 20;
int vehicley = 10;;
char map [width][height];
char movemap [width][height];
int ShieldEnergy;
int SEUsage;
int scounter = 0;
int mcounter = 0;
int min;
int max;
int valid = 0;
char dinput[100];




VehDataType vehicleData;

void Mmapprint();
void data();
void mapprint();


int validinputd(const char *dinput, int *dchoice, int min, int max) 
{
int g;

	if (dinput[0] == '\n') 
	{
    	printf("Empty input! Please enter a whole number between %d and %d.\n", min, max);
    	return 0;
    }
    for (g = 0; g < strlen(dinput) - 1; g++) 
    { 
    	if (dinput[g] == ' ' || dinput[g] == '.' || !isdigit(dinput[g])) 
    {
    		printf("Invalid input! Please enter a whole number without spaces or decimals.\n");
    		return 0;
    }
    }

    if (sscanf(dinput, "%d", dchoice) == 1) 
    {
        if (*dchoice >= min && *dchoice <= max) 
        {
        	return 1;  
        } 
        else 
        {
       		printf("Invalid choice! Please enter a number between %d and %d.\n", min, max);
        	return 0;
        }
    }

    printf("Invalid input! Please enter a whole number between %d and %d.\n", min, max);
    return 0;
}


void init1()
{
char srcFilename[100];
char encryption[100];
bool fileNeedsDecryption = 0; 
bool randomizeStartPosition = 0;
char startposition[100];
int typemission;
int missionType;
//VehDataType *vehData;
//VehDataType vehicleData;
//vehData = &vehicleData;

strcpy(srcFilename, "Scenario05.dat");
fileNeedsDecryption = true;
randomizeStartPosition = false;
missionType = 8;

vehicleData = SCRelay_Signal_Veh_Init(srcFilename, fileNeedsDecryption, randomizeStartPosition, missionType);
 
return;
}

void init()
{
	char srcFilename[100];
    char encryption[100];
	bool fileNeedsDecryption = 0; 
	bool randomizeStartPosition = 0;
	char startposition[100];
	int typemission;
	int missionType;
	int counter = 0;
	int c;
	VehDataType *vehData;
	VehDataType vehicleData;
	vehData = &vehicleData;
	
	printf("\nPlease enter the scenario file's name: \n");
	fgets(srcFilename, sizeof(srcFilename), stdin);
	srcFilename[strcspn(srcFilename, "\n")] = 0;


while (counter == 0)
{
	printf("\nIs the Scenario file encrypted? (y/n):\n");
	fgets(encryption, sizeof(encryption), stdin);
	encryption[strcspn(encryption, "\n")] = 0; 

	encryption[0] = tolower(encryption[0]);

	if (strcmp(encryption, "y") == 0)
	{
		fileNeedsDecryption = true;
		counter++;
	}
	else if (strcmp(encryption, "n") == 0)
	{
		fileNeedsDecryption = false;
		counter++;
	}	
	else
	{
		printf("\nError. re-enter value.\n");
	} 
 }



 while (counter == 1)
 {
	printf("\nDo you wish to randomize start position (y/n):\n");

    fgets(startposition, sizeof(startposition), stdin);
    startposition[strcspn(startposition, "\n")] = 0;  
	startposition[strcspn(startposition, "\n")] = 0; 

	startposition[0] = tolower(startposition[0]);

	if (strcmp(startposition, "y") == 0)
	{
		randomizeStartPosition = true;
		counter++;

	} 
	else if (strcmp(startposition, "n") == 0)
	{
		randomizeStartPosition = false;
		counter++;
	} 
 	else 
	{
		printf("\nError, re-enter value. \n");
		
	}
 }
	
	printf("\nPlease select mission type below\n");
    printf("1) Casual Explore\n");
    printf("2) Find 1 End Point\n");
    printf("3) Reach 1 End Point\n");
    printf("4) Find ALL End Points\n");
    printf("5) Reach ALL End Points\n");
    printf("6) Find ALL Danger Points\n");
    printf("7) Find Map Boundaries\n");
    printf("8) Explore Everything\n");

min = 1;
max = 8;

while (!valid) 
	{
        printf("Please enter your choice (1-8): ");
        fgets(dinput, sizeof(dinput), stdin);
        valid = validinputd(dinput, &typemission, min, max);
    }
valid = 0;


	
	switch (typemission) 
	{
	case 1:
		printf("\nInitializing mission 1...\n");
		missionType = 1;
	break;
	case 2:
		printf("\nInitializing mission 2...\n");
		missionType = 2;
	break;
	case 3:
		printf("\nInitializing mission 3...\n");
		missionType = 3;
	break;
	case 4:
		printf("\nInitializing mission 4...\n");
		missionType = 4;
	break;
	case 5:
		printf("\nInitializing mission 5...\n");
		missionType = 5;
	break;
	case 6:
		printf("\nInitializing mission 6...\n");
		missionType = 6;
	break;
	case 7:
		printf("\nInitializing mission 7...\n");
		missionType = 7;
	break;
	case 8:
		printf("\nInitializing mission 8...\n");
		missionType = 8;
	break;
	default:
		printf("\nInvalid Mission type! Re-enter the correct mission type.\n");
	}


    printf("\nFilename: %s, isFileEncrypted: %s, RandomisedStartPosition: %s\n",
    srcFilename, fileNeedsDecryption ? "true" : "false", randomizeStartPosition ? "true" : "false");
    vehicleData = SCRelay_Signal_Veh_Init(srcFilename, fileNeedsDecryption, randomizeStartPosition, missionType);
    
    return; 
}


void maximum_South()
{
int rt = 0;
energyToAllocate = 8000;
vehicleData = SCRelay_Signal_Veh_AllocateToShield(energyToAllocate);

toggle2 = (toggle2 == 1) ? 2 : 1;
printf("Scan radius now => now set to %d terrain units!\n", toggle2);

while (1)
{
if(vehicleData.currShieldEnergy == 0)
{
	Nmove;
	break;
}
else
{

ShieldEnergy = vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanSouth(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveDownSouth();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
	break;
}
else
{
	movemap[vehiclex][vehicley + 1] = scanresult;
	vehicley++;
	mcounter++;
	rt++;
}
}
}
 Mmapprint();
 data();
 return;
                                       
}


void maximum_North()
{
int rt = 0;
energyToAllocate = 8000;
vehicleData = SCRelay_Signal_Veh_AllocateToShield(energyToAllocate);

while (1)
{

if(vehicleData.currShieldEnergy == 0)
{
	Nmove;
	break;
}
else
{

ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanNorth(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveUpNorth();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
	break;
}
else
{
movemap[vehiclex][vehicley - 1] = scanresult;
vehicley--;
mcounter++;
rt++;
}	
}
}
 Mmapprint();
 data();
 return;
                                       
}


void maximum_East() 
{
int rt = 0;

energyToAllocate = 8000;
vehicleData = SCRelay_Signal_Veh_AllocateToShield(energyToAllocate);

while (1)
{

if(vehicleData.currShieldEnergy == 0)
{
	Nmove;
	break;
}

else
{

ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanEast(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveRightEast();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;


	if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
	{
	Nmove;
	break;
	}
	else
	{
	movemap[vehiclex + 1][vehicley] = scanresult;
	vehiclex++;
	mcounter++;
	rt++;
	}
}
}
 Mmapprint();
 data();
 return;
                                       
}

void maximum_West() 
{

int rt = 0;

energyToAllocate = 8000;
vehicleData = SCRelay_Signal_Veh_AllocateToShield(energyToAllocate);

while (1)
{

if(vehicleData.currShieldEnergy == 0)
{
	Nmove;
	break;
}

else
{
	ShieldEnergy =  vehicleData.currShieldEnergy;
	scanresult = SCRelay_Signal_Veh_ScanWest(&vehicleData);
	vehicleData = SCRelay_Signal_Veh_MoveLeftWest();
	SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

	if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
	break;
}
	else
{
	movemap[vehiclex - 1][vehicley] = scanresult;
	vehiclex--;
	mcounter++;
	rt++;
}
}
}

 Mmapprint();
 data();

 return;
              

                           
}


    




void mapinit()
{
	int x;
	int y;
	
	for (x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			map[x][y] = '0';
			movemap[x][y] = '0';
		}
}
}

void mapprint()
{
	int x;
	int y;

	for (int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
			if (x == vehiclex && y == vehicley) 
			{
    			if (map[x][y] == '0') 
    			{
        			printf("\033[0;36m\033[4m \033[0m "); // Underline a blank space in cyan
   				} 				
   				else 
   				{
        			printf("\033[0;36m\033[4m%c\033[0m ", map[x][y]); // Underline the symbol at the vehicle's position in cyan
    			}
			}
			
			else
			{
			switch(map[x][y])
			   {
			   	case 'f':
			   	printf("\033[0;32m%c\033[0m ", map[x][y]);
			   	break;
			   	case 'M':
			   	printf("\033[0;35m%c\033[0m ", map[x][y]);
			   	break;
			   	case '~':
			   	printf("\033[0;36m%c\033[0m ", map[x][y]);
			   	break;
			   	case 'E':
			   	printf("\033[0;37m%c\033[0m ", map[x][y]);
			   	break;
			   	case 'j':
			   	printf("\033[0;32m%c\033[0m ", map[x][y]);
			   	break;
			   	case 'X':
			   	printf("\033[0;31m%c\033[0m ", map[x][y]);
			   	break;
			   	case 'h':
			   	printf("\033[0;32m%c\033[0m ", map[x][y]);
			   	break;
			   	case 'w':
			   	printf("\033[0;33m%c\033[0m ", map[x][y]);
			   	break;
			   	case '#':
			   	printf("\033[0;31m%c\033[0m ", map[x][y]);
			   	break;
			   	case '0':
			   	printf("  ");
			   	break;
			   	
			   	//extra symbols not shown in map
			   	case '@': case '&': case '$':
        		printf("\033[0;32m%c\033[0m ", map[x][y]); // Green
        		break;
    			case '!': case '%':
        		printf("\033[0;34m%c\033[0m ", map[x][y]); // Blue
        		break;
    			case '+': case '=': case '-':
        		printf("\033[0;33m%c\033[0m ", map[x][y]); // Yellow
        		break;
    			case '*': case '/': case '\\':
        		printf("\033[0;36m%c\033[0m ", map[x][y]); // Cyan
        		break;
    			case '^': case '<': case '>':
        		printf("\033[0;35m%c\033[0m ", map[x][y]); // Purple
        		break;
    			case '[': case ']': case '{': case '}':
        		printf("\033[0;37m%c\033[0m ", map[x][y]); // White
        		break;
    			case '|': case '_': case '`':
        		printf("\033[0;31m%c\033[0m ", map[x][y]); // Red
        		break;
			   	
			   	default:
			   	printf("%c ", map[x][y]);
			   	break;
			   	
			   }
			}
			}
			printf("\n");
		}
}

void Mmapprint()
{
	int x;
	int y;

	for (int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
			if(movemap[x][y] == '0')
			{
			printf("  ");
			}
			else if(x == vehiclex && y == vehicley)
			{
			   printf("\033[0;36m\033[4m%c\033[0m ", movemap[x][y]);
			}
			else
			{
			switch(movemap[x][y])
			   {
			   	case 'f':
			   	printf("\033[0;32m%c\033[0m ", movemap[x][y]);
			   	break;
			   	case 'M':
			   	printf("\033[0;35m%c\033[0m ", movemap[x][y]);
			   	break;
			   	case '~':
			   	printf("\033[0;36m%c\033[0m ", movemap[x][y]);
			   	break;
			   	case 'E':
			   	printf("\033[0;37m%c\033[0m ", movemap[x][y]);
			   	break;
			   	case 'j':
			   	printf("\033[0;32m%c\033[0m ", movemap[x][y]);
			   	break;
			   	case 'X':
			   	printf("\033[0;31m%c\033[0m ", movemap[x][y]);
			   	break;
			   	case 'h':
			   	printf("\033[0;32m%c\033[0m ", movemap[x][y]);
			   	break;
			   	case 'w':
			   	printf("\033[0;33m%c\033[0m ", movemap[x][y]);
			   	break;
			   	case '#':
			   	printf("\033[0;31m%c\033[0m ", movemap[x][y]);
			   	break;
			   	
			   	//extra symbols not shown in map
			   	case '@': case '&': case '$':
        		printf("\033[0;32m%c\033[0m ", movemap[x][y]); // Green
        		break;
    			case '!': case '%':
        		printf("\033[0;34m%c\033[0m ", movemap[x][y]); // Blue
        		break;
    			case '+': case '=': case '-':
        		printf("\033[0;33m%c\033[0m ", movemap[x][y]); // Yellow
        		break;
    			case '*': case '/': case '\\':
        		printf("\033[0;36m%c\033[0m ", movemap[x][y]); // Cyan
        		break;
    			case '^': case '<': case '>':
        		printf("\033[0;35m%c\033[0m ", movemap[x][y]); // Purple
        		break;
    			case '[': case ']': case '{': case '}':
        		printf("\033[0;37m%c\033[0m ", movemap[x][y]); // White
        		break;
    			case '|': case '_': case '`':
        		printf("\033[0;31m%c\033[0m ", movemap[x][y]); // Red
        		break;
			   	
			   	default:
			   	printf("%c ", movemap[x][y]);
			   	break;
			   	
			   }
			}
			}
			printf("\n");
		}
}

void data ()
{
printf("\nVehicle Status / Statistics : \n");
printf("Initial Energy: %ld ,", vehicleData.initialEnergy);
printf("Current Energy: %ld ,", vehicleData.currEnergy);
printf("Current Shield Energy: %ld ,", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld ,", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld ,", vehicleData.totShieldEnergyUsed);
return;
}

void scanradius ()
{
	toggle = (toggle == 1) ? 2 : 1;
	printf("Scan radius now => now set to %d terrain units!\n", toggle);
	return;
}

void moveradius ()
{
	toggle2 = (toggle2 == 1) ? 2 : 1;
	printf("Move radius now => now set to %d terrain units!\n", toggle2);
	return;
}


void scanSW ()
{
	if (toggle == 2)
	{
	scanresult = SCRelay_Signal_Veh_ScanSouthWest2(&vehicleData);
	printf("Result of SouthWest scan: %c\n", scanresult);
	map[vehiclex - 2][vehicley + 2] = scanresult;
	scounter++;
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanSouthWest(&vehicleData);
	printf("Result of SouthWest scan: %c\n", scanresult);
	map[vehiclex - 1][vehicley + 1] = scanresult;
	scounter++;
	}
	data();
	mapprint();
	return;
}

void scanS ()
{
	if (toggle == 2)
	{
	scanresult = SCRelay_Signal_Veh_ScanSouth2(&vehicleData);
	printf("Result of South scan: %c\n", scanresult);
	map[vehiclex][vehicley + 2] = scanresult;
	scounter++;
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanSouth(&vehicleData);
	printf("Result of South scan: %c\n", scanresult);
	map[vehiclex][vehicley + 1] = scanresult;
	scounter++;
	}
data();
	mapprint();
	return;
}

void scanSE ()
{
	if (toggle == 2)
	{
	scanresult = SCRelay_Signal_Veh_ScanSouthEast2(&vehicleData);
	printf("Result of SouthEast scan: %c\n", scanresult);
	map[vehiclex + 2][vehicley + 2] = scanresult;
	scounter++;
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanSouthEast(&vehicleData);
	printf("Result of SouthEast scan: %c\n", scanresult);
	map[vehiclex + 1][vehicley + 1] = scanresult;
	scounter++;
	}
data();
	mapprint();
	return;
}

void scanW ()
{
	if (toggle == 2)
	{
	scanresult = SCRelay_Signal_Veh_ScanWest2(&vehicleData);
	printf("Result of West scan: %c\n", scanresult);
	map[vehiclex - 2][vehicley] = scanresult;
	scounter++;
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanWest(&vehicleData);
	printf("Result of West scan: %c\n", scanresult);
	map[vehiclex - 1][vehicley] = scanresult;
	scounter++;
	}
data();
	mapprint();
	return;
}

void scanE ()
{
	if (toggle == 2)
	{
	scanresult = SCRelay_Signal_Veh_ScanEast2(&vehicleData);
	printf("Result of East scan: %c\n", scanresult);
	map[vehiclex + 2][vehicley] = scanresult;
	scounter++;
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanEast(&vehicleData);
	printf("Result of East scan: %c\n", scanresult);
	map[vehiclex + 1][vehicley] = scanresult;
	scounter++;
	}
data();
	mapprint();
	return;
}

void scanNW ()
{
	if (toggle == 2)
	{
	scanresult = SCRelay_Signal_Veh_ScanNorthWest2(&vehicleData);
	printf("Result of NorthWest scan:%c\n", scanresult);
	map[vehiclex - 2][vehicley - 2] = scanresult;
	scounter++;
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanNorthWest(&vehicleData);
	printf("Result of NorthWest scan: %c\n", scanresult);
	map[vehiclex - 1][vehicley - 1] = scanresult;
	scounter++;
	}
data();
	mapprint();
	return;
}

void scanN ()
{
	if (toggle == 2)
	{
	scanresult = SCRelay_Signal_Veh_ScanNorth(&vehicleData);
	printf("Result of North scan: %c\n", scanresult);
	map[vehiclex][vehicley - 2] = scanresult;
	scounter++;
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanNorth(&vehicleData);
	printf("Result of North scan: %c\n", scanresult);
	map[vehiclex][vehicley - 1] = scanresult;
	scounter++;
	}
data();
	mapprint();
	return;
}

void scanNE ()
{
	if (toggle == 2)
	{
	scanresult = SCRelay_Signal_Veh_ScanNorthEast2(&vehicleData);
	printf("Result of NorthEast scan: %c\n", scanresult);
	map[vehiclex + 2][vehicley - 2] = scanresult;
	scounter++;
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanNorthEast(&vehicleData);
	printf("Result of NorthEast scan: %c\n", scanresult);
	map[vehiclex + 1][vehicley - 1] = scanresult;
	scounter++;
	}
data();
	mapprint();
	return;
}

void scanAll()
{

	
	scanresult = SCRelay_Signal_Veh_ScanSouthWest(&vehicleData);
	printf("Result of SouthWest scan: %c\n", scanresult);
	map[vehiclex - 1][vehicley + 1] = scanresult;
	scanresult = SCRelay_Signal_Veh_ScanSouth(&vehicleData);
	printf("Result of South scan: %c\n", scanresult);
	map[vehiclex][vehicley + 1] = scanresult;
	scanresult = SCRelay_Signal_Veh_ScanSouthEast(&vehicleData);
	printf("Result of SouthEast scan: %c\n", scanresult);
	map[vehiclex + 1][vehicley + 1] = scanresult;
	scanresult = SCRelay_Signal_Veh_ScanWest(&vehicleData);
	printf("Result of West scan: %c\n", scanresult);
	map[vehiclex - 1][vehicley] = scanresult;
	scanresult = SCRelay_Signal_Veh_ScanEast(&vehicleData);
	printf("Result of East scan: %c\n", scanresult);
	map[vehiclex + 1][vehicley] = scanresult;
	scanresult = SCRelay_Signal_Veh_ScanNorthWest(&vehicleData);
	printf("Result of NorthWest scan: %c\n", scanresult);
	map[vehiclex - 1][vehicley - 1] = scanresult;
	scanresult = SCRelay_Signal_Veh_ScanNorth(&vehicleData);
	printf("Result of North scan: %c\n", scanresult);
	map[vehiclex][vehicley - 1] = scanresult;
	scanresult = SCRelay_Signal_Veh_ScanNorthEast(&vehicleData);
	printf("Result of NorthEast scan: %c\n", scanresult);
	map[vehiclex + 1][vehicley - 1] = scanresult;
	scounter += 8;
data ();
	mapprint();
	return;
}

void moveN ()

{

if(toggle2 == 2)
{

ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanNorth(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveUpNorth();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
movemap[vehiclex][vehicley - 1] = scanresult;
vehicley--;
mcounter++;
}

ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanNorth(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveUpNorth();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;	

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex][vehicley - 1] = scanresult;
	vehicley--;
	mcounter++;
}
}

else
{
ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanEast(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveRightEast();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex][vehicley - 1] = scanresult;
	vehicley--;
	mcounter++;
}
}

 Mmapprint();

 data();

 return;
}

void moveE ()

{

if(toggle2 == 2)
{

ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanEast(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveRightEast();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex + 1][vehicley] = scanresult;
	vehiclex++;
	mcounter++;
}

ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanEast(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveRightEast();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex + 1][vehicley] = scanresult;
	vehiclex++;
	mcounter++;
}
}

else
{
ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanEast(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveRightEast();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex + 1][vehicley] = scanresult;
	vehiclex++;
	mcounter++;
}
}

 Mmapprint();

 data();

 return;
}

void moveW ()

{

if(toggle2 == 2)
{

ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanWest(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveLeftWest();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex - 1][vehicley] = scanresult;
	vehiclex--;
	mcounter++;
}

ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanWest(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveLeftWest();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex - 1][vehicley] = scanresult;
	vehiclex--;
	mcounter++;
}
}

else
{
ShieldEnergy =  vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanWest(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveLeftWest();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex - 1][vehicley] = scanresult;
	vehiclex--;
	mcounter++;
}
}

 Mmapprint();

 data();

 return;
}

void moveS ()
{

if(toggle2 == 2)
{
ShieldEnergy = vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanSouth(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveDownSouth();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex][vehicley+ 1] = scanresult;
	vehicley++;
	mcounter++;
}

ShieldEnergy = vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanSouth(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveDownSouth();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex][vehicley + 1] = scanresult;
	vehicley++;
	mcounter++;
}
}

else
{
ShieldEnergy = vehicleData.currShieldEnergy;
scanresult = SCRelay_Signal_Veh_ScanSouth(&vehicleData);
vehicleData = SCRelay_Signal_Veh_MoveDownSouth();
SEUsage = ShieldEnergy - vehicleData.currShieldEnergy;

if(SEUsage >= 5000 && scanresult != 'X' || scanresult == '#' || scanresult == '?')
{
	Nmove;
}
else
{
	movemap[vehiclex][vehicley + 1] = scanresult;
	vehicley++;
	mcounter++;
}
}

 Mmapprint();

 data();

 return;
}


void giveEnergy ()
{
 	printf("How much energy do you want to allocate to the Shield?\n");

    scanf(" %ld", &energyToAllocate);

    vehicleData = SCRelay_Signal_Veh_AllocateToShield(energyToAllocate);

	data();

    while (getchar() != '\n');

return;
}

void maprpt() 
{
 int x, y;
    int charCount[128] = {0}; // Array to store counts for printable ASCII characters
printf("\n[ Terrain Types Scanned ]\n");
    // Count characters in the final state of the map
    for (y = 0; y < height; y++) 
	{
        for (x = 0; x < width; x++) 
		{
            char currentChar = map[x][y];

            // Exclude '0' from counting
            if (currentChar == '0') 
			{
                continue; // Skip this iteration for '0'
            }

            // Count other printable characters
            if (isprint(currentChar)) 
			{
                charCount[(int)currentChar]++;
            }
        }
    }

    // Print the character frequency
    printf("\nNumber of characters scanned:\n");
    for (int i = 0; i < 128; i++)
	 {
        if (charCount[i] > 0) 
		{
            printf("Number of '%c' scanned: %d\n", i, charCount[i]);
        }
    }
}

void mmaprpt() 
{
 int x, y;
    int charCount[128] = {0}; // Array to store counts for printable ASCII characters
printf("\n[ Terrain Types Explored ]\n");
    // Count characters in the final state of the map
    for (y = 0; y < height; y++) 
	{
        for (x = 0; x < width; x++) 
		{
            char currentChar = movemap[x][y];

            // Exclude '0' from counting
            if (currentChar == '0') 
			{
                continue; // Skip this iteration for '0'
            }

            // Count other printable characters
            if (isprint(currentChar))
			 {
                charCount[(int)currentChar]++;
            }
        }
    }

    // Print the character frequency
    printf("\nNumber of characters explored:\n");
    for (int i = 0; i < 128; i++)
	 {
        if (charCount[i] > 0)
		 {
            printf("Number of '%c' scanned: %d\n", i, charCount[i]);
        }
    }
}

void erpt()
{
	printf("\n[ Energy Report ]\n");
	data();
}

void exprpt()
{
	printf("\n-------------------------\n");
	printf("-- Exploration Report! --\n");
	printf("-------------------------\n");

	printf("Total no. of scans				taken: %d\n", scounter);
	printf("Total no. of movement(steps)		taken: %d\n", mcounter);
}

int main()
{

int map[width][height] = {0};
char Usage;
char UI[100];
char input[10];
int counter = 1;
int g;

mapinit();
init1();

	printf("\n'w','s','a','d' keys to move vehicle north, south, west & east\n");
	printf("Enable numlock', (right key pad), keys 1-9 (except 5) to scan terrain: \n SW (1), S (2),  SE(3),  W(4),  E(6),  NW(7), N(8), NE(9) respectively  \n");
	printf("'t' key - Toggle scan Radius (betw. 1-2)\n");
	printf("'l' key - Toggle movement (betw. 1-2)\n");
	printf("'i' key = increase / divert energy to shield\n");
	printf("'z' key - Info on vehicle status\n");
	printf("'x' key = map of terrain scanned by vehicle\n");
	printf("'c' key = map of terrain travelled by vehicle\n");
	printf("'e', 'g', 'h', 'f' keys to move vehicle north, south west & east until a barricade or out of shield energy. Note: Shield Energy is allocated automatically at 8000.\n");
	printf("Note : In map display, ' ' underline indicates xxx , veh , location!\n\n");

while (counter == 1)
{

printf("\nEnter your command: ");

 if (fgets(input, sizeof(input), stdin) != NULL) 
 {
    input[strcspn(input, "\n")] = '\0'; 
    if (strlen(input) > 1) 
	{
    	printf("\nError! Invalid command: Too many characters entered.\n");
        continue;  
	}
 }

Usage = input[0];

switch (Usage)  
{
case '1' :
		scanSW();
break;
case '2' :
		scanS();
break;
case '3' :
		scanSE();
break;
case '4' :
		scanW();
break;
case '5' :
		scanAll();
break;
case '6' :
		scanE();
break;
case '7' :
		scanNW();
break;
case '8' :
		scanN();
break;
case '9' :
		scanNE();
break;
case 't' :
		scanradius();
break;
case 'w' :
		moveN();
break;
case 'a' :
		moveW();
break;
case 's' :
		moveS();
break;
case 'd' :
		moveE();
break;
case 'i' :
		giveEnergy();
break;
case 'z' :
		data();
break;
case 'v' :
	printf("\n'w','s','a','d' keys to move vehicle north, south, west & east\n");
	printf("Enable numlock', (right key pad), keys 1-9 (except 5) to scan terrain: \n SW (1), S (2),  SE(3),  W(4),  E(6),  NW(7), N(8), NE(9) respectively  \n");
	printf("'t' key - Toggle scan Radius (betw. 1-2)\n");
	printf("'l' key - Toggle movement (betw. 1-2)\n");
	printf("'i' key = increase / divert energy to shield\n");
	printf("'z' key - Info on vehicle status\n");
	printf("'x' key = map of terrain scanned by vehicle\n");
	printf("'c' key = map of terrain travelled by vehicle\n");
	printf("'e', 'g', 'h', 'f' keys to move vehicle north, south west & east until a barricade or out of shield energy. Note: Shield Energy is allocated automatically at 8000.\n");
	printf("Note : In map display, ' ' underline indicates xxx , veh , location!\n\n");
break;
case 'x' :
		mapprint();
break;
case 'q' :
		exprpt();
		erpt();
		maprpt();
		mmaprpt();
		return 0;
break;
case 'f' :
		maximum_West();
break;
case 'g' :
		maximum_South();
break;
case 'h' :
		maximum_East();
break;
case 'e' :
		maximum_North();
break;
case 'c':
		Mmapprint();
break;
case 'l':
		moveradius();
break;
default :
{
	printf("\nInvalid Input!\n\n");
}
}
}
}

	
