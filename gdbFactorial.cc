// This program requests an integer from the user and returns the 
// factorial of that value
// Taken from: https://www.cprogramming.com/gdb.html

#include<iostream>

using namespace std;

// Function prototype
long factorial(int n);

// Main function
int main()
{
    // Define variable n and set to 0
    int n(0);

    // Request integer from user
    cout<<"Enter an integer to calculate factorial"<<endl;
    cin>>n;

    // Calculate factorial
    long val=factorial(n);

    // Output
    cout<<endl<<n<<"! is "<<val<<endl;
    
    // Keep console open for output
    cin.get();

    return 0;
}

// Factorial calculation, input: n, output: n!
long factorial(int n)
{
    // Define result and initialize to 1
    long result(1);

    // Loop down from integer to 0
    while(n--)
    {
        // Multiply next integer to running product
        result *= n;
    }

    // Return result to main function
    return result;
}

