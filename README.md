# Corner Grocer Item Tracker Program

Corner Grocer Item Tracker
This repository contains the C++ source code for the Corner Grocer Item Tracker application.

Project Summary and Problem Solved
This project created a C++ program for the Corner Grocer to analyze daily purchase records. It counts how often each item is bought to help the store optimize its produce section layout based on item popularity. The program offers options to look up item frequencies, print all frequencies, or display a text-based histogram. It also automatically saves all item frequencies to a frequency.dat backup file.

Reflection on the Project
What I did particularly well
I focused on structuring the application well using a GroceryTracker class with clear public and private sections. I also implemented robust input validation for the menu choices, ensuring the program handles user errors smoothly.

Where could I enhance my code?
The item name lookup currently uses a simple title-casing conversion. A more comprehensive string normalization function could improve handling of multi-word items (e.g., "ice cream" becoming "Ice Cream"). Additionally, adding error logging to a file would improve maintainability for debugging. For very large datasets, using std::unordered_map might offer slight performance benefits over std::map.

Most challenging pieces of code and how I overcame them
The most challenging part was reliably implementing user input validation to prevent infinite loops from bad input. I overcame this by studying std::cin.clear() and std::cin.ignore() functions, and using a debugger to understand stream states. These C++ stream manipulation techniques are now valuable tools in my network.

Transferable skills from this project
This project reinforced my understanding of Object-Oriented Programming (OOP) principles, file input/output operations, and the effective use of data structures like std::map. I also strengthened my skills in robust input validation and problem decomposition, which are essential for any programming project.

How I made this program maintainable, readable, and adaptable
I designed the program with a modular class structure and clear method responsibilities. Extensive in-line comments, consistent formatting, and meaningful variable names enhance readability. The parameterization of file names makes the program adaptable and reusable for different datasets without modifying the core code.
