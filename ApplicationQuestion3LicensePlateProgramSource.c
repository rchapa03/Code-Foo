#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//*************************************************************************//
//
//  FILE NAME: ApplicationQuestion3LicensePlateProgramSource.c
//  AUTHOR: Ruben C. Chapa, III
//  INTIAL CREATION DATE: April 7, 2012
//  DESCRIPTION: Takes a population number as input from the user and generates the simplest pattern that will produce enough unique plates
//  DATE OF LAST REVISION:	April 27, 2012
//
//*************************************************************************//

/*declaration of global variables*/

double numbers;
double letters;


int exitFlag = 0; /*define exitFlag as 0 since exitFlag = 1 means that the user has typed exit */

double calcExcess(double, double);
void printData(double, double, double);
double getData(void);
double generatePatterns(double);

int main()
{
      double pop;
      double ExcessPlates;
      double TotalPlates;
      printf("Welcome to the License Plate Pattern Program. \nPlease note that large numbers will be displayed in scientific notation. \nType exit to quit the program\n\n");
      while(exitFlag != 1)
      {
        pop = getData();
        if(pop != -1)
        {
        TotalPlates = generatePatterns(pop);
        ExcessPlates = calcExcess(pop, TotalPlates);
        printData(pop, TotalPlates, ExcessPlates);
        }
      }

      printf("Thanks for using my program!!\n");
      return 0;
}

//-------------------------calcExcess------------------------
//  Calculates the excess amount of license plates
//  Input:  Population Number
//          Total Number of Plates
//  Output: Excess Plates

double calcExcess(double Population, double TotalPlates)
{
        return TotalPlates - Population; /*Subtract total plates from population number*/
}


//-------------------------printData------------------------
//  Prints information to console
//  Input:  Population Number
//          Total Number of Plates
//          Excess Plates
//  Output: none

void printData(double pop, double TotalPlates, double ExcessPlates)
{
      printf("Population: %G\n", pop);

      if((numbers == 1) && (letters == 0)) /*if only one number, print Number singular*/
      {
          printf("Pattern: %G Number", numbers);
      }else
      {
          if((numbers == 0) && (letters == 1)) /*if only one letter, pring Letter singular*/
          {
              printf("Pattern: %G Letter", letters);
          }else
          {
              printf("Pattern: ");
              if(numbers != 0)
              {
                    if((numbers == 1)) /*if there is 1 number but more letters, print Number singular, else print Numbers Plural*/
                    {
                        printf(" %G Number", numbers);
                    }else
                    {
                        printf(" %G Numbers", numbers);
                    }
              }

              if(letters != 0)
              {
                    if((letters == 1)) /*if there is 1 letter but more numbers, print Letter singular, else print Letters Plural*/
                    {
                        printf(" %G Letter", letters);
                    }else
                    {
                        printf(" %G Letters", letters);
                    }
              }

           }
      }


      printf("\n");
      printf("Total Plates: %G\n", TotalPlates);
      printf("Excess Plates: %G\n\n", ExcessPlates);
}

//-------------------------getData------------------------
//  Gets population number from the user
//  Input:  none
//  Output: returns the number the user type in
//          returns -1 if anything but an integer was typed
//          sets exitFlag = 1 if user types "exit"

double getData(void)
{
    char buf[BUFSIZ];
    char *p;
    double data;

    printf("Please type in a population number and hit enter: ");

    if (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        data = strtod(buf, &p);
        if (buf[0] != '\n' && (*p == '\n' || *p == '\0'))
            {
                printf("\n");
                return data;
            }
        else
            {
                if((buf[0] == 'e') && (buf[1] == 'x') && (buf[2] == 'i') && (buf[3] == 't')) /*if "exit" is typed set exitFlag to 1 and get out*/
                {
                    exitFlag = 1;
                    return -1;
                }
                printf ("Hey! What are you trying to pull here?! Enter INTEGERS only!\n \n"); /*if anything other than exit is typed then it is an invalid input*/
                return -1;
            }

    }


}

//-------------------------generatePatterns------------------------
//  Generates the total number of plates and sets the globals numbers and letters
//  Calculating the number of different pattern that can be generated from numbers or letters or both depend on the amount of spaces the license plate has
//  For example, if there are 3 spaces and you want to use only numbers then for the 1st space there are 10 different numbers we can use, this is also true for the 2nd and 3rd spaces.
//  Therefore the number of unique plates that could be generated is 10*10*10 or 10^3 which is 1000. If you wanted to use only letters it would be 26*26*26 or 26^3 which is 17576.
//  If you wanted to use a combination of 3 numbers and letters, lets say 1 number and 2 letters, then the unique plates that could be generated would be 10*26*26 or 10*26^2 which is 6760.
//  The important thing to notice here is that for a given number of license plate spaces, the combination for letters only is always going to be more than the numbers only and more than any combo of numbers and letters.
//  Input:  Population Number
//
//  Output: sets the globals numbers and letters
//          returns total number of plates

double generatePatterns(double pop)
{
    int i;
    int j = 1;
    int done = 0; /*done is set when an appropriate total number of plates has been found*/
    double temp;
    double pattern;
    double previous;
    double initial = 6; /*Initially starts with 6 license plate spaces since most realistic populations wont need more than 6 letters/numbers*/
    previous = pow(26, initial + 1); /*initialize, pow(26, initial + 1) will make sure previous is big enough for the initial check*/
    while(done != 1)
    {
        if(pop < pow(26, initial)) /*make sure population is bigger than the maximum of plates that can be generated with the given spaces*/
        {
            for(initial; initial > 0; initial--) /*starts with the highest value of combinations and narrows it down until the smallest combination is found and sets globals letters and numbers to that combo*/
            {
                j = 1; /* set this as initial starting point combo for letters, it must be reset each iteration*/
                if((pop <= pow(26, initial)) && (pow(26, initial) < previous)) /*initial check, start with letters only, population must be less than or equal to the max value, and the max value must be less than the previous value*/
                {
                    numbers = 0;
                    letters = initial;
                    pattern = pow(26, initial);
                    previous = pattern;
                    done = 1;
                }
                if((pop <= pow(10, initial)) && (pow(10, initial) < previous)) /*continue with numbers only, population must be less than min value, and the min value must be less than the previous value*/
                {
                    numbers = initial;
                    letters = 0;
                    pattern = pow(10, initial);
                    previous = pattern;
                    done = 1;
                }

                for(i = initial; i > 1; i--) /*if not letters only or numbers only then it must be a combination of both*/
                {
                    /* Variables i and j keep track of the different possible combinations. For example, lets say we are working with 5 license plate spaces
                    the different possible combinations become 4 numbers 1 letter, 3 numbers 2 letters, 2 numbers 3 letters, or 1 number 4 letters.
                    Notice that the pattern is as numbers decreases by 1, letters increases by 1. j is already initially set to 1, and i will be given the number of spaces.
                    Through each loop iteration, i will decrease by 1 and j will increase by 1 and temp becomes the number of unique plates that would be generated with that pattern.*/

                    temp = pow(10, i - 1) * pow(26, j); /* temp becomes the total number of plates that can be generated by the combination*/
                    j++;
                    if((pop <= temp) && (temp < previous)) /* population must be less than or equal to the temp and temp must be less than previous*/
                    {
                        numbers = i - 1;
                        letters = j - 1;
                        pattern = temp;
                        previous = pattern;
                        done = 1;
                    }
                }
            }
        }else
        {
            initial++; /*population is bigger than initial values, so increase initial values until they are bigger than the population*/
            previous = pow(26, initial + 1); /*initialize, pow(26, initial + 1) will make sure previous is big enough for the initial check*/
        }
    }
    return pattern; /* returns number of unique plates generated by the best pattern */
}
