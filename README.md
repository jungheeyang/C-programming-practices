# C-programming-practices
C programming practice codes 


----------------------------Features----------------------------
This program was built to find the association between words from a text file and present a word histogram, and correlation matrices between each word based on the histogram.


----------------------------Solutions----------------------------
To create the world histogram, in task 1, important words in the text are identified as those which are capitalized. Therefore, the text was read character by character until finding a word starting with a capital letter. It was then saved and filtered by a common word list before being added to the histogram. Subsequently, this histogram is passed to task 2, where the program creates a correlation between a word and all other words in the text. First, two words and the line it appeared were saved, then a count is incremented whenever they appear together to create the correlation matrices.


----------------------------Filestructure----------------------------
This program consists of one main.c file with task1.c and task2.c files and 3 header file for each task1.c and task2.c and for the most common words which is used to remove irrelevant words from the histogram. It allows the user to input their own text file and create a text file with the word histogram and the correlation matrices.


----------------------------Data structures----------------------------
In task1, I used HistogramTemp struct to save a unique word and its number of appearances in the text file. To find unique words, Temp struct was used to save the string in a linked list as single characters.

In task 2, ‘Element’ struct was used to form a linked list of the word from the histogram and which line of the text it appeared. And then ‘Matrix’ struct is used to create a linked list which contains two words with the count of how many times two words were in the same sentence. Also dynamically allocated 2d array ’twoD_array’ was made to save the data from ‘Matrix’ linked list.
