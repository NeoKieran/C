#include "SatComRelay.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define width 40
#define height 20

char scanresult;
int toggle = 1;
long initialEnergy;
long currEnergy;
long currShieldEnergy;
long totEnergyUsed;
long totShieldEnergyUsed;
long energyToAllocate;
bool randomizeStartPosition;
int vehiclex = 20;
int vehicley = 10;
char map [width][height];
char movemap [width][height];
//VehDataType *vehData;
VehDataType vehicleData;
//vehData = &vehicleData;


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
	VehDataType *vehData;
	VehDataType vehicleData;
	vehData = &vehicleData;
	
	printf("\nPlease enter the scenario file's name: \n");
	fgets(srcFilename, sizeof(srcFilename), stdin);
	srcFilename[strcspn(srcFilename, "\n")] = 0;
	
	printf("\nIs the Scenario file encrypted? (y/n):\n");
	fgets(encryption, sizeof(encryption), stdin);
	encryption[strcspn(encryption, "\n")] = 0; // Remove newline character
	if (strcmp(encryption, "y") == 0)
	{
		fileNeedsDecryption = true;
	}
	else if (strcmp(encryption, "n") == 0)
	{
		fileNeedsDecryption = false;
	}	
	else
	{
		printf("Error Re-enter value.\n");
	} 
	printf("\nDo you wish to randomize start position (y/n):\n");

    fgets(startposition, sizeof(startposition), stdin);
    startposition[strcspn(startposition, "\n")] = 0;  // Remove Newline

// Convert the input to lowercase for case-insensitive comparison
	for (int i = 0; startposition[i]; i++) 
	{
  		startposition[i] = tolower(startposition[i]); 
	}
	if (strcmp(startposition, "y") == 0) 
	{
		randomizeStartPosition = true;

	} 
	else if (strcmp(startposition, "n") == 0) 
	{
		randomizeStartPosition = false;
	} 
 	else 
	{
		printf("Error, re-input your option: \n");
		int c;
		while ((c = getchar()) != '\n' && c != EOF);  // Clear input buffer only after invalid input
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
    printf("Enter your choice (1-8): ");
    scanf(" %d", &typemission);
	
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
	while ((typemission = getchar()) != '\n' && typemission != EOF);
    // Call the function with the correctly set missionType
    printf("\nFilename: %s, isFileEncrypted: %s, RandomisedStartPosition: %s\n",
    srcFilename, fileNeedsDecryption ? "true" : "false", randomizeStartPosition ? "true" : "false");
    vehicleData = SCRelay_Signal_Veh_Init(srcFilename, fileNeedsDecryption, randomizeStartPosition, missionType);
    
    return; 
}


void mapinit()
{
	int x;
	int y;
	
	for (int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			map[x][y] = '0';
			movemap[x][y] = ' ';
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
			if(map[x][y] == '0')
			{
			printf("  ");
			}
			else if(x == vehiclex && y == vehicley)
			{
			   printf("\033[4m\%c\033[0m ", map[x][y]);
			}
			else
			{
			printf("%c ", map[x][y]);
			}
			}
			printf("\n");
		}
}



void scanradius ()
{
	toggle = (toggle == 1) ? 2 : 1;
	printf("Scan radius now => now set to %d terrain units!\n", toggle);
	return;
}


void scanSW ()
{
	if (toggle == 2)
	{
	scanresult = SCRelay_Signal_Veh_ScanSouthWest2(&vehicleData);
	printf("Result of SouthWest scan: %c\n", scanresult);
	map[vehiclex - 2][vehicley + 2] = scanresult;
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanSouthWest(&vehicleData);
	printf("Result of SouthWest scan: %c\n", scanresult);
	map[vehiclex - 1][vehicley + 1] = scanresult;
	}
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
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
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanSouth(&vehicleData);
	printf("Result of South scan: %c\n", scanresult);
	map[vehiclex][vehicley + 1] = scanresult;
	}
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
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
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanSouthEast(&vehicleData);
	printf("Result of SouthEast scan: %c\n", scanresult);
	map[vehiclex + 1][vehicley + 1] = scanresult;
	}
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
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
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanWest(&vehicleData);
	printf("Result of West scan: %c\n", scanresult);
	map[vehiclex - 1][vehicley] = scanresult;
	}
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
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
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanEast(&vehicleData);
	printf("Result of East scan: %c\n", scanresult);
	map[vehiclex + 1][vehicley] = scanresult;
	}
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
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
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanNorthWest(&vehicleData);
	printf("Result of NorthWest scan: %c\n", scanresult);
	map[vehiclex - 1][vehicley - 1] = scanresult;
	}
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
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
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanNorth(&vehicleData);
	printf("Result of North scan: %c\n", scanresult);
	map[vehiclex][vehicley - 1] = scanresult;
	}
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
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
	}
	else
	{
	scanresult = SCRelay_Signal_Veh_ScanNorthEast(&vehicleData);
	printf("Result of NorthEast scan: %c\n", scanresult);
	map[vehiclex + 1][vehicley - 1] = scanresult;
	}
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
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
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
	mapprint();
	return;
}

void moveN ()

{
 vehicleData = SCRelay_Signal_Veh_MoveUpNorth();
 vehicley--;
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
 return;
}

void moveE ()

{

 vehicleData = SCRelay_Signal_Veh_MoveRightEast();
 vehiclex++;
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
 return;
}

void moveW ()

{
 vehicleData = SCRelay_Signal_Veh_MoveLeftWest();
 vehiclex--;
 printf("\n");
 printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
 return;
}

void moveS ()

{
 vehicleData = SCRelay_Signal_Veh_MoveDownSouth();
 vehicley++;
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
 return;
}

void giveEnergy ()

{


 long energyToAllocate;

 printf("How much energy do you want to allocate to the Shield?\n");

    scanf(" %ld", &energyToAllocate);

    vehicleData = SCRelay_Signal_Veh_AllocateToShield(energyToAllocate);
	printf("\n");
	printf("-----------------------------------\n");
    printf("----Vehicle Status / Statistics----\n");
	printf("-----------------------------------\n");
	printf("\n");
	printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
	printf("Current Energy: %ld \n", vehicleData.currEnergy);
	printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
	printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
	printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);

    while (getchar() != '\n');

return;
}


void data ()
{
printf("\n");
printf("-----------------------------------\n");
printf("----Vehicle Status / Statistics----\n");
printf("-----------------------------------\n");
printf("\n");
printf("Initial Energy: %ld \n", vehicleData.initialEnergy);
printf("Current Energy: %ld \n", vehicleData.currEnergy);
printf("Current Shield Energy: %ld \n", vehicleData.currShieldEnergy);
printf("Total Energy Used: %ld \n", vehicleData.totEnergyUsed);
printf("Total Shield Energy Used: %ld\n\n", vehicleData.totShieldEnergyUsed);
return;
}

int main()
{

int map[width][height] = {0};
unsigned char Usage;
char UI[100];
int counter = 1;
mapinit();
init1();

printf("\n'w','s','a','d' keys to move vehicle north, south, west & east\n");
printf("Enable numlock', (right key pad), keys 1-9 (except 5) to scan terrain: \n SW (1), S (2),  SE(3),  W(4),  E(6),  NW(7), N(8), NE(9) respectively  \n");
printf("'t' key - Toggle scan Radius (betw. 1-2)\n");
printf("'i' key = increase / divert energy to shield\n");
printf("'z' key - Info on vehicle status\n");
printf("'x' key = map of terrain scanned by vehicle\n");
printf("'c' key = map of terrain travelled by vehicle\n");
printf("Note : In map display, ' ' underline indicates xxx , veh , location!\n\n");

while (counter == 1)
{
printf("Enter your command: " );
fgets(UI, sizeof(UI), stdin);
UI[strcspn(UI, "\n")] = 0;
Usage = UI[0];

switch ((unsigned char) Usage)  
{
case 'q' :
		return 0;
break;
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
	printf("'i' key = increase / divert energy to shield\n");
	printf("'z' key - Info on vehicle status\n");
	printf("'x' key = map of terrain scanned by vehicle\n");
	printf("'c' key = map of terrain travelled by vehicle\n");
	printf("Note : In map display, ' ' underline indicates xxx , veh , location!\n\n");
break;
case 'x' :
		mapprint();
break;
}
}
}	
	
