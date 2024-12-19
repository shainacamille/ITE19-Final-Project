#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function Prototypes
int convertRomanToDecimal(const char *roman); // Convert Roman numeral to decimal
void processInputFile(const     char *inputFile, const char *outputFile); // Process the input file and perform operations
void convertDecimalToWords(int num, char *output); // Convert decimal number to words
void numberToWordsHelper(int n, char *result); // Recursive helper function to generate words

// Main function
int main()
{
    // Define input and output file names
    const char inputFile[] = "input.txt";
    const char outputFile[] = "output.txt";

    // Process the input file and generate output
    processInputFile(inputFile, outputFile);

    // Notify user of successful execution
    printf("Program executed successfully. Check '%s' for results.\n", outputFile);
    return 0;
}

// Function to convert Roman numeral to decimal
int convertRomanToDecimal(const char *roman)
{
    int value = 0;   // Total value
    int prev = 0;    // Previous numeral value
    int current = 0; // Current numeral value

    // Iterate over the Roman numeral from end to start
    for (int i = strlen(roman) - 1; i >= 0; i--)
    {
        // Map Roman numeral characters to their decimal equivalents
        switch (toupper(roman[i]))
        {
        case 'I':
            current = 1;
            break;
        case 'V':
            current = 5;
            break;
        case 'X':
            current = 10;
            break;
        case 'L':
            current = 50;
            break;
        case 'C':
            current = 100;
            break;
        case 'D':
            current = 500;
            break;
        case 'M':
            current = 1000;
            break;
        default:
            current = 0; // Handle invalid characters
        }

        // Apply subtraction rule if current is less than previous
        if (current < prev)
            value -= current;
        else
            value += current;

        // Update previous numeral value
        prev = current;
    }
    return value;
}

// Function to process input file and perform arithmetic operations
void processInputFile(const char *inputFile, const char *outputFile)
{
    FILE *in = fopen(inputFile, "r");  // Open input file for reading
    FILE *out = fopen(outputFile, "w"); // Open output file for writing

    // Check if files are successfully opened
    if (!in || !out)
    {
        printf("Error: Unable to open file(s).\n");
        return;
    }

    char roman1[20], roman2[20], operator; // Variables to hold input data

    // Read input file line by line
    while (fscanf(in, "%s %c %s", roman1, &operator, roman2) != EOF)
    {
        int num1 = convertRomanToDecimal(roman1); // Convert first Roman numeral to decimal
        int num2 = convertRomanToDecimal(roman2); // Convert second Roman numeral to decimal
        int result = 0; // Variable to store the result of the operation
        char wordResult[500] = ""; // Buffer to hold the result in words

        // Perform the arithmetic operation based on the operator
        switch (operator)
        {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        default:
            fprintf(out, "Invalid operator\n"); // Handle invalid operators
            continue;
        }

        // Convert the result to words
        convertDecimalToWords(result, wordResult);

        // Write the result in words to the output file
        fprintf(out, "%s\n", wordResult);
    }

    // Close the input and output files
    fclose(in);
    fclose(out);
}

// Function to convert a decimal number to words
void convertDecimalToWords(int num, char *output)
{
    if (num < 0)
    {
        strcat(output, "Negative "); // Add "Negative" for negative numbers
        num = -num; // Convert to positive for processing
    }

    if (num == 0)
    {
        strcat(output, "Zero"); // Handle the case for zero
        return;
    }

    // Convert the number to words using a helper function
    numberToWordsHelper(num, output);
}

// Recursive helper function to convert numbers to words
void numberToWordsHelper(int n, char *result)
{
    // Arrays for units, tens, and teens
    const char *units[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                           "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                           "Seventeen", "Eighteen", "Nineteen"};
    const char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    // Process billions place
    if (n >= 1000000000)
    {
        numberToWordsHelper(n / 1000000000, result);
        strcat(result, " Billion ");
        n %= 1000000000;
    }

    // Process millions place
    if (n >= 1000000)
    {
        numberToWordsHelper(n / 1000000, result);
        strcat(result, " Million ");
        n %= 1000000;
    }

    // Process thousands place
    if (n >= 1000)
    {
        numberToWordsHelper(n / 1000, result);
        strcat(result, " Thousand ");
        n %= 1000;
    }

    // Process hundreds place
    if (n >= 100)
    {
        strcat(result, units[n / 100]);
        strcat(result, " Hundred ");
        n %= 100;
    }

    // Process tens and units
    if (n >= 20)
    {
        strcat(result, tens[n / 10]);
        strcat(result, " ");
        strcat(result, units[n % 10]);
    }
    else if (n > 0)
    {
        strcat(result, units[n]);
    }
}
