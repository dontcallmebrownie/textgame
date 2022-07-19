#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
#include <unistd.h>
#include <vector>

#include "parse.h"

using namespace std;

// Files for I/O
ifstream gData;
fstream sData;
string dataFile = "./rsc/data";
string saveFile = "./save/save";

// Function protos
int init();
int cleanUp();
void  getInput();
int parser(string);
void printCredits();
void loadCredits();

int getLoadingFrames();
void loadingAnim(string, int);
void loadBanner();
void printBanner();

// Loaded Data storage
char load[5];
string banner[14]; // The lines vary in size (in bytes) 
                   //  extra element in array to account for the memory used
string credits[16];
string verbs[20];

// User input storage
vector<string> parsedInput;

int quit = 0;

int init()
{
    int error = 0;

    gData.open(dataFile);
    
    if (!gData.is_open())
    {
        cout << "ERROR: DATA FILE MISSING\n";
        error = 1;
    }    
   
    // get loading animation frames 
    getLoadingFrames();

    // Load game menu banner 
    loadBanner();

    sData.open(saveFile); // Test for existing file
    if (!sData.is_open())
    {
        // If no file
        cout << "No save data found. ";
        sData.open(saveFile, fstream::in | fstream::out | fstream::trunc);
        sData << "\n";
        loadingAnim("Creating", 2);
    }    
    else 
    {
        // If exists
        sData.close();
        sData.open(saveFile, fstream::in | fstream::out | fstream::trunc);
    }

    loadCredits();


    // Get game data
    // TODO: verb dictionary
    for (int i = 0; i < 19; i++)
    {
        gData >> verbs[i];
        cout << verbs[i] << endl;  
    } 
    // TODO: game scenes
 
return error;
}

int main (int argc, char* argv[])
{

    int error = 0;
    char opt = 0;
    int valid = 0;
    

    if(!gData.is_open())
    {
        cout << "Wecome!\nPlease wait while game loads.\n";

        // Initialize everything
        if (init())
        {
            cout << "ERROR: INIT\n";
        }

        loadingAnim("Loading",3);
    }

    printBanner();
    
    // Handle main menu stuff first    
    while (!valid) 
    {
        cout << "\n\n\tPlease select a menu option.\n:> ";
        cin >> opt;
        
        if (opt < '0' || opt > '9')
        {
            cout << "Please enter a number\n";
            continue;
        }

        switch(opt)
        {
            case '1':
                valid = true;
                break;
            case '2':
                cout << "this function coming soon!\n";
                break;
             case '3':
                printCredits();
                loadingAnim("", 4);
                printBanner();
                break; 
             case '4':
                quit = 1;
                valid = true;
                break;
            default:
                cout << "not a valid choice.\n";
                printBanner();
                break;
        }
    }

    cin.ignore();

    // Actual game loop get input->do stuff -> print -> repeat
    while(!quit)
    {
       
        // Clear the storage vector so we know it's empty
        parsedInput.clear();
        
        getInput();


        for(int i = 0; i < parsedInput.size(); i++)
        {
            cout << parsedInput[i] << "\n";
                                 
        }
        
    }



    // Clear mem and close files
    if (cleanUp())
    {
        cout << "ERROR: CLEANUP\n";
    }    

return error;
}

void getInput()
{
    string raw;


    // Wait for input
    cout << ":> ";
    getline(cin, raw, '\n');
    
    // Parse Input
    parse(mkUpper(raw), &parsedInput);

    if (parsedInput[0] == "QUIT")
    {
        if (parsedInput.size() > 1)
        {
            if (parsedInput[1] == "NOW")
            {
                parsedInput.clear();
                quit = 1;
            }
            else 
            {
                parsedInput.clear();
                main(0, 0);
            }
        }
        else
        {
            parsedInput.clear();
            main(0,0);
        }

    }    

}

int cleanUp()
{
    int error = 0;
    
    parsedInput.clear();    
    
    if (gData.is_open())
    {    
        gData.close();
    }
    
    if (sData.is_open())
    {
        sData.close();
    }
    
    if (gData.is_open() || sData.is_open())
    {
        cout << "ERROR: DATA FILE DID NOT CLOSE\n";
        error = 1;
    }   

return error;
}

int getLoadingFrames()
{
    int error = 0;
    
    char c;

    for (int i = 0; i < 5; i++)
    {
        gData.get(c);
        load[i] = c;
    }

return error;
}

void loadingAnim(string say, int len)
{
    int playing = len * 5;
    int i = 5;
    cout << say << "... ";

    while (playing)
    {
        cout << load[i] << flush;
        usleep(250000);
        i++;

        if (i > 5)
        {
            i = 0;
        }
        else
        cout << "\b";

        playing--;
    }
    cout << "\b" << "Done\n" << endl;
}


/*
// Load and print array functions should be made generic
//  These could have been copy/pasted with no issue so 
//  I need to refactor this


int loadArray(file, &array, delim);

int printArray(&array, size); ?, offset ?);







*/



void loadBanner()
{
     for(int i = 0; i <= 13; i++)
    {
       getline( gData, banner[i], '\n');
    }    
}

void printBanner()
{
    for (int i = 0; i <= 13; i++)
    {
        cout << banner[i] << endl;
    }
}

void loadCredits()
{
    for (int i = 0; i <= 15; i++)
    {
        getline(gData, credits[i], '\n');
    }
}

void printCredits()
{
    for (int i = 0; i <= 15; i++) 
    {
        cout << credits[i] << endl;
    }

}

