// SpellCheck <Project1.cpp>
// EE 312 Project 1 submission by
// <Kevin Li>
// <kal3552>
// Slip days used: <0>
// Spring 2020
// Copy-paste contents of this file at the top of every .c or .h file that you write or modify.
/*
 * Project1.cpp
 * 
 * Name: Kevin Li
 * EE312 Spring 2020
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */
void printArray(char c[]) //prints a null-terminated array
{
    int index=0;
    while(c[index]!=0)
    {
        printf("%c", c[index]);
        index++;
    }
    printf("\n");
}
int isAlphabet(char c) //returns 1 if the character is in the Alphabet, 0 otherwise
{
    if((65<=c && c<=90) || (97<=c && c<=122))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkIfCharMatch(char c, char d) //return 1 if characters match, 0 otherwise. No case sensitivity
{
    if(c==d)
    {
        return 1;
    }
    if((c>=65 && c<=90) && (c+32==d)) //checks if d is lowercase c
    {
        return 1;
    }
    if((c>=91 && c<=122) && (c-32==d)) //checks if d is uppercase c
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int isWord(char theWordInQuestion[], char dictionary[]) //returns 1 if the word exists in the dictionary, 0 otherwise
{
    uint32_t index=0; //goes through the word array
    uint32_t dictionaryIndex=0; //goes through the dictionary array
    uint32_t resetIndex=0; //determines whether the word needs to be re-checked with the next dictionary word
    while(1)
    {
        resetIndex=0; //reset is cleared, proceed to continue checking for a matching word
        if(theWordInQuestion[index]==0 && (dictionary[dictionaryIndex]=='\n' || dictionary[dictionaryIndex]==0))
        {
            return 1; //word is in the dictionary
        }
        if(dictionary[dictionaryIndex]==0)
        {
            return 0; //the dictionary has ended with no match for the word
        }
        if(checkIfCharMatch(dictionary[dictionaryIndex], theWordInQuestion[index])!=1)
        {
            resetIndex=1; //no match, check the next word
            while(dictionary[dictionaryIndex]!='\n')
            {
                if(dictionary[dictionaryIndex]==0)
                {
                    return 0; //the dictionary has ended with no match for the word
                }
                dictionaryIndex++; //skip ahead to the next word
            }
        }
        index++;
        dictionaryIndex++;
        if(resetIndex==1)
        {
            index=0; //reset index if the current word does not match
        }
    }
}

void spellCheck(char article[], char dictionary[]) { //main spellcheck function
    uint32_t index=0; //goes through the article
    char bufferArray[1<<20]={0}; //this array contains a word to be checked. Fool-proof
    uint32_t charCounter=0; //counts the number of characters in a row
    while(1)
    {
        if(isAlphabet(article[index])==1)
        {
            bufferArray[charCounter]=article[index]; //add another letter to the word array
            charCounter++;
        }
        if(isAlphabet(article[index])==0 && charCounter>=2) //a valid word has ended. Let's check it
        {
            bufferArray[charCounter]=0; //null terminate the word array in case a print operation is necessary
            if(isWord(bufferArray, dictionary)!=1)
            {
                printArray(bufferArray); //print the word if it isn't in the dictionary
            }
            bufferArray[charCounter=0];
            charCounter=0; //reset the counter to begin accumulating the next word
        }
        if(article[index]==0)
        {
            break; //reached the end of article
        }
        if(isAlphabet(article[index])==0)
        {
            charCounter=0; //word is in the dictionary. Do nothing and begin accumulating the next word
        }
        index++;
    }
}


