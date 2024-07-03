#include <stdio.h> // Includes the standard I/O library for input/output operations
#include <stdlib.h> // Includes the standard library for general purposes
#include <unistd.h> // Includes the unistd header for accessing POSIX operating system API functions

// Function prototype declaration for tryOpenFile
// This informs the compiler about the existence of this function before it's defined
int tryOpenFile(const char *filename);

int main() {
    char filename[100]; // Declares an array to hold the filename entered by the user
    int result; // Variable to store the result of the file operation

    printf("Enter the name of the file you want to open: "); // Prompt the user to enter a filename
    scanf("%99s", filename); // Reads the filename from the user. Note: Consider using fgets for safer input

    // Debugging: Prints the received filename to the console
    printf("Received filename: %s\n", filename);

    // Get the current working directory
    char cwd[1024]; // Declares an array to hold the current working directory path
    if (getcwd(cwd, sizeof(cwd)) != NULL) { // Calls getcwd() to fill the cwd array with the current working directory
        printf("Current working directory: %s\n", cwd); // Prints the current working directory
    } else {
        perror("getcwd() error"); // If getcwd() fails, print an error message
        return 1; // Exits the program with an error code
    }

    // Constructs the full path to the file, assuming the file is in the current working directory
    char filePath[1024]; // Declares an array to hold the full path to the file
    snprintf(filePath, sizeof(filePath), "%s/%s", cwd, filename); // Use snprintf() to construct the full path

    // Debugging: Prints the constructed file path to the console
    printf("Constructed file path: %s\n", filePath);

    // Attempts to open the file using the constructed file path
    result = tryOpenFile(filePath); // Calls the tryOpenFile() function with the constructed file path
    if (result == 0) { // Check if the file was opened successfully
        printf("File opened successfully.\n"); // Inform the user if the file was opened successfully
    } else {
        printf("Failed to open the file.\n"); // Inform the user if the file failed to open
    }

    return 0; // Return 0 to indicate successful execution of the program
}

// Function definition for tryOpenFile
// Attempts to open a file in read mode ("r")
int tryOpenFile(const char *filename) {
    FILE *file = fopen(filename, "r"); // Try to open the file

    if (file != NULL) { // Check if the file was opened successfully
        fclose(file); // Close the file immediately after opening
        return 0; // Return 0 to indicate success
    } else {
        perror("Error opening file"); // Print a descriptive error message if the file couldn't be opened
        return -1; // Return -1 to indicate failure
    }
}
