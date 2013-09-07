/* 
 * File:   main.cpp
 * 
 * Author: Nathan Buckley
 *
 * Description: Simple C++ project that outputs a string that
 *              is to be used in a Parity check lookup table. 
 * 
 * Last Edited: 7th march 2013
 */

#include <iostream>
#include <math.h>
#include <sstream>
#include <string.h>

//Error codes.  
enum {NO_ARGS, 
      GENERAL_INVALID,
      NO_BITS_AMOUNT,
      HELP};
      
//Prototypes
int stringToInt(const std::string &str);
void printErrorMessage(int errorCode);
void printUsage(void);

/*
 * Main entry point into the program. 
 * 
 * uses the -b flag to determine how many bits should make up a parity check.
 * I created this so I could create a 6bit table of values as the format 
 * I was working with had a 7th bit which was the parity bit. The table I needed
 * was one where the parity bit was odd. So I would need to run the proggy with
 * -b 6 -o 
 * which will produce a 6bit parity bit table, where the parity bit is an odd 
 * parity bit.
 *  
 */
int main(int argc, char* argv[]) {
    
    int     iBits       = 0;
    int     iCombos     = 0;
    int     iBitCount   = 0;
    bool    evenCheck   = true;
    
    if(argc == 0){
        printErrorMessage(NO_ARGS);
        return NO_ARGS;
    }
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-b") == 0){
            if(i+1 < argc){
                iBits = stringToInt(argv[i+1]);
            }
            else{
                printErrorMessage(NO_BITS_AMOUNT);
            }
        }
        else if(strcmp(argv[i], "-o") == 0){
            evenCheck = false;
            std::cout << "switching to odd parity check..." << std::endl;
        }
        else if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0){
            printErrorMessage(HELP);
            return 0;
        }       
    }
    if(iBits == 0)
    {
        printErrorMessage(NO_BITS_AMOUNT);
        return NO_BITS_AMOUNT;
    }
    
    //Find how many possible combinations.
    iCombos = pow(2, (double)iBits);
        
    for(unsigned char i = 0; i < iCombos; i++){
        iBitCount = 0;  //Reset bit count.
        unsigned char k = i;
        for(int j = 0; j < iBits; j++){        
            if(k & 1){
                //bit is set so count bit. 
                iBitCount++;
            }
            //Shift bit right to check next bit along.
            k >>=1;
        }
        int out = -1;
        
        //Time to determine if we should perform an odd/even parity check.
        if(evenCheck){
            out = (iBitCount%2 == 0) ? 0 : 1;
        }
        else{
            out = (iBitCount%2 == 0) ? 1 : 0;
        }
        
        //TODO Improve output by throwing it into a fifo/collection
        //and then having a stage for doing the output afte it has been 
        //collected. This will make offering formatting easier. 
        
        //Perform output.
        //TODO tied in with the above TODO, provide more formatting options.
        std::cout << out << ", ";
    }    
    return 0;
}

//TODO Handle outcome better if not number.
int stringToInt(const std::string &str){
    int iResult = 0;
    std::stringstream ss(str);
    if(!(ss >> iResult)){
        iResult = 0;
    }
    return iResult;
}
/**
 * Uses an error code to print out a more meaningful message
 * to the user as to why there was an error. Will always end by 
 * printing out the flags etc that can be used with the program.
 * 
 * @param errorCode - what error code (see enum at top). 
 */
void printErrorMessage(int errorCode){
    switch(errorCode)
    {
        case NO_ARGS:
        {
            std::cout << "Error: Invalid number of arguments. Requires number of parity bits." << std::endl;
            break;
        }
        case NO_BITS_AMOUNT:
        {
            std::cout << "Error: No bits set. Set with -b x where x is number." << std::endl;
            break;
        }
        default:
        {
            std::cout << "Error: Non specified error." << std::endl;
            break;
        }
    }
    printUsage();    
}

/**
 * prints out the standard usage flags/options for this proggy.
 */
void printUsage(){    
    std::string str = ""
        "Usage\n"
        "-----\n"
        "-b \t\t set parity check bits. This is required.\n"
        "-o \t\t odd parity check. If not sent then performs even\n"
        "-h \t\t displays help information. "
        "--help \t\t same as -h\n";
    std::cout << str;
}

