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

// Function protos
int init();
int cleanUp();
void  getInput();
int parser(string);


int getLoadingFrames();
void loadingAnim();
void loadBanner();
void printBanner();

// Loaded Data storage
char load[5];
string banner[11];


// User input storage
vector<string> parsedInput;
int quit = 0;

int init()
{
    int error = 0;

    gData.open("./rsc/data");
    
    if (!gData.is_open())
    {
        cout << "ERROR: DATA FILE MISSING\n";
        error = 1;
    }
   
    // get loading animation frames 
    getLoadingFrames();

    // Load game menu banner 
    loadBanner();
    
    // Get game data
    // TODO: verb dictionary
 
return error;
}

int main (int argc, char* argv[])
{
    int error = 0;
    char opt;
    int valid = 0;
    
    cout << "Wecome!\nPlease wait while game loads.\n";

    // Initialize everything
    if (init())
    {
        cout << "ERROR: INIT\n";
    }

    loadingAnim();
    printBanner();
//    
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
                quit = 1;
                valid = true;
                break;
            default:
                cout << "not a valid choice.\n";
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
        quit = 1;

    }    

}



int cleanUp()
{
    int error = 0;
    
    if (gData.is_open())
    {    
        gData.close();
    }
    
    if (gData.is_open())
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

void loadingAnim()
{
    int playing = 50;
    int i = 5;
    cout << "Loading...   ";

    while (playing)
    {
        cout << load[i] << flush;
//        usleep(250000);
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

void loadBanner()
{
     for(int i = 0; i <= 10; i++)
    {
       getline( gData, banner[i]);
    }    
}
void printBanner()
{
    for (int i = 0; i <= 10; i++)
    {
        cout << banner[i] << endl;
    }
}