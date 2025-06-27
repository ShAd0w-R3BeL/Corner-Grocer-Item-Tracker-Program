/*
 * GroceryTracker.cpp
 *
 * Date: 06/25/2025
 * Author: Matthew Wood
 *
 */

#include <iostream> // Required for input/output operations (e.g., std::cout, std::cin)
#include <fstream>  // Required for file stream operations (e.g., std::ifstream, std::ofstream)
#include <map>      // Required for std::map, used to store item frequencies
#include <string>   // Required for std::string
#include <limits>   // Required for std::numeric_limits, used for input validation
#include <vector>   // Not strictly needed for this simple version, but generally useful

 // Define a class to encapsulate the grocery tracking logic
class GroceryTracker {
private:
    std::map<std::string, int> itemFrequencies; // Private member to store item frequencies
    std::string inputFileName;                  // Name of the input file (e.g., CS210_Project_Three_Input_File.txt)
    std::string outputFileName;                 // Name of the backup output file (e.g., frequency.dat)

    // Private helper method to read data from the input file
    void ReadInputFile() {
        std::ifstream inputFile(inputFileName); // Open the input file
        std::string item;                       // Variable to hold each item read from the file

        // Check if the input file was opened successfully
        if (!inputFile.is_open()) {
            std::cout << "Error: Could not open input file " << inputFileName << std::endl;
            std::cout << "Please ensure 'CS210_Project_Three_Input_File.txt' exists in the same directory." << std::endl;
            return; // Exit if file cannot be opened
        }

        // Read items one by one until the end of the file
        while (inputFile >> item) {
            // Increment the frequency for the current item.
            // If the item is not yet in the map, it will be added with a frequency of 1.
            itemFrequencies[item]++;
        }

        inputFile.close(); // Close the input file
    }

    // Private helper method to generate the backup data file
    void GenerateBackupFile() {
        std::ofstream outputFile(outputFileName); // Open the output file for writing

        // Check if the output file was opened successfully
        if (!outputFile.is_open()) {
            std::cout << "Error: Could not create backup file " << outputFileName << std::endl;
            return; // Exit if file cannot be opened
        }

        // Iterate through the map and write each item and its frequency to the backup file
        for (const auto& pair : itemFrequencies) {
            outputFile << pair.first << " " << pair.second << std::endl;
        }

        outputFile.close(); // Close the output file
        std::cout << "Backup file '" << outputFileName << "' created successfully." << std::endl;
    }

    // Private helper method to display the main menu options
    void DisplayMenu() {
        std::cout << "\n-----------------------------------------" << std::endl;
        std::cout << "           Corner Grocer Menu            " << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "1. Look up individual item frequency" << std::endl;
        std::cout << "2. Print all item frequencies" << std::endl;
        std::cout << "3. Print item frequencies as a histogram" << std::endl;
        std::cout << "4. Exit program" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
    }

    // Private helper method for basic input validation for integers
    int GetMenuChoice() {
        int choice;
        while (!(std::cin >> choice) || choice < 1 || choice > 4) {
            std::cout << "Invalid input. Please enter a number between 1 and 4: ";
            std::cin.clear(); // Clear the error flag
            // Ignore the rest of the invalid input line
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        // Consume the rest of the line after a valid integer is read
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }

public:
    // Constructor for the GroceryTracker class
    // Initializes file names and immediately processes the input file to generate the backup.
    GroceryTracker(const std::string& inputFname, const std::string& outputFname)
        : inputFileName(inputFname), outputFileName(outputFname) {
        ReadInputFile();      // Read data from the specified input file
        GenerateBackupFile(); // Create the backup file
    }

    // Public method for Menu Option One: Get the frequency of a specific item
    void GetItemFrequency() {
        std::string itemToFind;
        std::cout << "Enter the item you wish to look for: ";
        std::getline(std::cin, itemToFind); // Use getline to read item names with spaces if necessary

        // Convert input item to title case to match stored items (assuming items in file are title cased)
        // This is a simple conversion; more robust handling might be needed for varied input.
        if (!itemToFind.empty()) {
            itemToFind[0] = std::toupper(itemToFind[0]); // Capitalize first letter
            for (size_t i = 1; i < itemToFind.length(); ++i) {
                itemToFind[i] = std::tolower(itemToFind[i]); // Lowercase the rest
            }
        }

        // Check if the item exists in the map and print its frequency
        if (itemFrequencies.count(itemToFind)) {
            std::cout << itemToFind << " appeared " << itemFrequencies[itemToFind] << " time(s)." << std::endl;
        }
        else {
            std::cout << "'" << itemToFind << "' not found in the purchase records." << std::endl;
        }
    }

    // Public method for Menu Option Two: Print all item frequencies
    void PrintAllFrequencies() {
        std::cout << "\n-----------------------------------------" << std::endl;
        std::cout << "           All Item Frequencies          " << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        // Iterate through the map and print each item and its frequency
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl;
    }

    // Public method for Menu Option Three: Print item frequencies as a histogram
    void PrintHistogram() {
        std::cout << "\n-----------------------------------------" << std::endl;
        std::cout << "           Item Frequency Histogram      " << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        // Iterate through the map to print the histogram
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << " "; // Print the item name
            // Print asterisks equal to the frequency
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << std::endl; // New line for the next item
        }
        std::cout << "-----------------------------------------" << std::endl;
    }

    // Public method to run the main program loop and handle menu choices
    void RunProgram() {
        int choice;
        do {
            DisplayMenu();        // Display the menu to the user
            choice = GetMenuChoice(); // Get and validate user's menu choice

            // Perform actions based on user's choice
            switch (choice) {
            case 1:
                GetItemFrequency(); // Call method for individual item frequency
                break;
            case 2:
                PrintAllFrequencies(); // Call method to print all frequencies
                break;
            case 3:
                PrintHistogram(); // Call method to print the histogram
                break;
            case 4:
                std::cout << "Exiting program. Goodbye!" << std::endl;
                break;
            default:
                // This case should ideally not be reached due to GetMenuChoice validation
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        } while (choice != 4); // Continue loop until user chooses to exit (option 4)
    }
};

// Main function where the program execution begins
int main() {
    // Create an instance of GroceryTracker.
    // The constructor will automatically read the input file and generate the backup file.
    // Ensure 'CS210_Project_Three_Input_File.txt' is in the same directory as your executable.
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt", "frequency.dat");

    // Run the main program loop, which displays the menu and handles user interactions.
    tracker.RunProgram();

    return 0; // Indicate successful program execution
}