/* Justin Farnsworth
 * October 1, 2017
 * Word Search Solver
 * 
 * This program solves a word search puzzle. The user can specify the words they 
 * want to find in the matrix, which will be highlighted if found.
 * 
 * This project works best with a Unix shell. Not recommended for the Windows command prompt
 * 
 * Compile Command:
 * g++ WordSearchSolver.cpp -o WordSearchSolver
 * 
 * Run Command:
 * Unix: 
 * 	  ./WordSearchSolver [word arguments] < [textfile]
 * 	    -ex: ./WordSearchSolver this is my project < 2020matrix
 * 
 * Windows:
 *   WordSearchSolver.exe [word arguments] < [textfile]
 * 	   -ex: WordSearchSolver.exe this is my project < 2020matrix
 */

#include "colormod.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;


// Main function
int main(int argc, char* argv[]) {
	// Sets the color mods
	Color::Setting red(Color::FG_RED);
    Color::Setting def(Color::FG_DEFAULT);
	
	// Number of consecutive letters that match
	int nMatches = 0;

	// This boolean terminates the while loop when flipped to true
	bool terminateLoop = false;
	
	// Dimensions of the matrix
    int x = 0;
    int y = 0;
    
	// Gets dimensions from the input file
    cin >> x;
    cin >> y;
    
	// Matrix 1 contains the inputted letters
	char matrix[x][y];
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cin >> matrix[i][j];
		}
	}
	
	// Matrix 2 acts as a switch for when the word is found in matrix
	bool matrix2[x][y];
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			matrix2[i][j] = false;
		}
	}

	// Search for the words in the matrix
	for (int word = 1; word < argc; word++) {
		int argvLength = strlen(argv[word]);
		
		// Left to right 
		for (int i = 0; i < x; i++) {
			for (int j = 0; j <= (y - argvLength); j++) {
				nMatches = 0;
				terminateLoop = false;

				// Count the number of times the letters consecutively match. Terminate if any don't
				while (!terminateLoop) {
					if (argv[word][nMatches] == matrix[i][j+nMatches]) { // Letters match
						nMatches++;
						if (nMatches == argvLength) { // The word has been found in the matrix
							for (int k = 0; k < argvLength; k++) {
								// Flip the corresponding values of matrix2 to true
								matrix2[i][j+k] = true;

								// Terminate the current loop
								terminateLoop = true;
							}
						}
					} else {
						terminateLoop = true;
					}	
				}
			}
		}
		
		// Right to left
		for (int i = 0; i < x; i++) {
			for (int j = (y - 1); j >= argvLength - 1; j--) {
				nMatches = 0;
				terminateLoop = false;

				// Count the number of times the letters consecutively match. Terminate if any don't
				while (!terminateLoop) {
					if (argv[word][nMatches] == matrix[i][j-nMatches]) { // Letters match
						nMatches++;
						if (nMatches == argvLength) { // The word has been found in the matrix
							for (int k = 0; k < argvLength; k++) {
								// Flip the corresponding values of matrix2 to true
								matrix2[i][j-k] = true;

								// Terminate the current loop
								terminateLoop = true;
							}
						}
					} else {
						terminateLoop = true;
					}
				}
			}
		}
		
		// Top to bottom
		for (int j = 0; j < y; j++) {
			for (int i = 0; i <= (x - argvLength); i++) {
				nMatches = 0;
				terminateLoop = false;

				// Count the number of times the letters consecutively match. Terminate if any don't
				while (!terminateLoop){
					if (argv[word][nMatches] == matrix[i+nMatches][j]) { // Letters match
						nMatches++;
						if (nMatches == argvLength) { // The word has been found in the matrix
							for (int k = 0; k < argvLength; k++) {
								// Flip the corresponding values of matrix2 to true
								matrix2[i+k][j] = true;

								// Terminate the current loop
								terminateLoop = true;
							}
						}
					} else { // A mismatch is found. Terminate the loop
						terminateLoop = true;
					}
				}
			}
		}
		
		// Bottom to top
		for (int j = 0; j < y; j++) {
			for (int i = (x - 1); i >= (argvLength - 1); i--) {
				nMatches = 0;
				terminateLoop = false;

				// Count the number of times the letters consecutively match. Terminate if any don't
				while (!terminateLoop) {
					if (argv[word][nMatches] == matrix[i-nMatches][j]) { // Letters match
					nMatches++;
						if (nMatches == argvLength) { // The word has been found in the matrix
							for (int k = 0; k < argvLength; k++) {
								// Flip the corresponding values of matrix2 to true
								matrix2[i-k][j] = true;

								// Terminate the current loop
								terminateLoop = true;
							}
						}
					} else { // A mismatch is found. Terminate the loop
						terminateLoop = true;
					}
				}
			}
		}
		
		// Top-left to bottom right
		for (int i = 0; i <= (x - argvLength); i++) {
			for (int j = 0; j <= (y - argvLength); j++) {
				nMatches = 0;
				terminateLoop = false;

				// Count the number of times the letters consecutively match. Terminate if any don't
				while (!terminateLoop) {
					if (argv[word][nMatches] == matrix[i+nMatches][j+nMatches]) { // Letters match
						nMatches++;
						if (nMatches == argvLength) { // The word has been found in the matrix
							for (int k = 0; k < argvLength; k++) {
								// Flip the corresponding values of matrix2 to true
								matrix2[i+k][j+k] = true;

								// Terminate the current loop
								terminateLoop = true;
							}
						}
					} else { // A mismatch is found. Terminate the loop
						terminateLoop = true;
					}
				}
			}
		}

		// Bottom-right to top-left
		for (int i = (x - 1); i >= (argvLength - 1); i--) {
			for (int j = (y - 1); j >= (argvLength - 1); j--) {
				nMatches = 0;
				terminateLoop = false;

				// Count the number of times the letters consecutively match. Terminate if any don't
				while (!terminateLoop) {
					if (argv[word][nMatches] == matrix[i-nMatches][j-nMatches]) { // Letters match
						nMatches++;
						if (nMatches == argvLength) { // The word has been found in the matrix
							for (int k = 0; k < argvLength; k++) {
								// Flip the corresponding values of matrix2 to true
								matrix2[i-k][j-k] = true;

								// Terminate the current loop
								terminateLoop = true;
							}
						}
					} else { // A mismatch is found. Terminate the loop
						terminateLoop = true;
					}
				}
			}
		}
		
		// Bottom-left to top-right
		for (int i = (x - 1); i >= (argvLength - 1); i--) {
			for (int j = 0; j <= (y - argvLength); j++) {
				nMatches = 0;
				terminateLoop = false;

				// Count the number of times the letters consecutively match. Terminate if any don't
				while (!terminateLoop) {
					if (argv[word][nMatches] == matrix[i-nMatches][j+nMatches]) { // Letters match
						nMatches++;
						if (nMatches == argvLength) { // The word has been found in the matrix
							for (int k = 0; k < argvLength; k++) {
								// Flip the corresponding values of matrix2 to true
								matrix2[i-k][j+k] = true;

								// Terminate the current loop
								terminateLoop = true;
							}
						}
					} else { // A mismatch is found. Terminate the loop
						terminateLoop = true;
					}
				}
			}
		}
		
		// Top-right to bottom-left
		for (int i = 0; i <= (x - argvLength); i++) {
			for (int j = (y - 1); j >= (argvLength - 1); j--) {
				nMatches = 0;
				terminateLoop = false;

				// Count the number of times the letters consecutively match. Terminate if any don't
				while (!terminateLoop) {
					if (argv[word][nMatches] == matrix[i+nMatches][j-nMatches]) { // Letters match
						nMatches++;
						if (nMatches == argvLength) { // The word has been found in the matrix
							for (int k = 0; k < argvLength; k++) {
								// Flip the corresponding values of matrix2 to true
								matrix2[i+k][j-k] = true;

								// Terminate the current loop
								terminateLoop = true;
							}
						}
					} else { // A mismatch is found. Terminate the loop
						terminateLoop = true;
					}
				}
			}
		}
	}
	
	// Prints the word matrix and changes the color of corresponding letters if the word is found
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (matrix2[i][j]) { // Color
				cout << red << matrix[i][j] << def;
			} else { // No color
				cout << matrix[i][j];
			}
        }
        cout << endl;
    }
	
    return 0;
}