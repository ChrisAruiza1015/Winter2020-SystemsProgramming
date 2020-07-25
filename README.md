# Systems Programming: CPE 357 - Winter 2020 - C language

## Program 1: Blend two BMP images
### 1/26/2020
A program that blends two 24 bit BMP images together. 
command line parameters :[programname] [imagefile1] [imagefile2] [ratio] [outputfile]
The ratio should determine what decimal percentage of imagefile1 and imagefile2 will be in the result. 
Uses bilinear interpolation if the resolution of the two images is not the same. 

## Program 2: Heap Simulation
### 2/6/2020
An extension of Lab 3 that removes the static heap array uses brk() and sbrk()
when mymalloc is called, the program break is moved as far as needed to allocate the first chunk. 
When a new chunk is added, search through the chunklist similar to lab3, for the smallest size that it will fit in, but if no chunk is free, move the program break further and assign a new chunk!
When the last chunk of the list is removed, the program break moves back up. 

## Program 3: Multiprocess/File Stat
### 2/20/2020
Two programs “monitor1” and “monitor2” that both fork a child process. 
The child process reads a file name from the keyboard and print the files information gathered with “stat”. If no file was found with that name, report this back to the user and wait for the next user input. Entering “list” lists the content of the current directory (wherever the executable is being called in) Entering “q” ends the program (all processes).
The parent process of monitor1: checks every 10 seconds if the child was active. If not, kill (in Linux sense) the child and then end the parent program. 
The parent process of monitor2: The parent should wait(0) for the child process to terminate. Then, wait for 10 seconds(with sleep) and fork the child again. 
Change directories with “..” or "/foldername”

## Program 4: Find files and Text in files/Redirect stdin
### 3/4/2020
A “findstuff” program that redirects stdin and uses pipes and prints the time in hh:mm:ss:ms format how long it took.
This program will let you enter its own shell: findstuff$
• find <filename>: tries to find this specific file by using fork() to make the child search and the parent keeps track of its pid. Once the child finds the file, it redirects stdin and interrupts the scanf from the parent process and prints its result. Print several lines if several files with the same name were found. 
• -s: if this flag is set, search in all sub-directories. If not set, search only in the current directory. 
• find <”text”> the child tries to find a certain text in all files by opening one file at a time, reading the content into a malloc’ed memory, and tries to find the string. When done, it list all files and where to find them with this string.
• -f:XYZ .. means file ending. If this flag is set, search only in files with this ending.
• list: lists all running child processes, their pid, and what they try to do.
• kill <num>: kills a child process, and so ends its finding attempts. 
• quit or q: quits the program and all child processes immediately.
This program limits the number of child processes to 10. 

## Program 5: Message Passing Interface/Syncing programs
Program 1 multiplies 2 10x10 matrices by sharing the work with its copies over shared memory. 
Program1 is called multiple times at the same time, and each instance of the program shares 10x10 matrices and works on a certain part of the matrix multiplication, so that the computational time becomes a fraction in comparison with only one instance. Includes a function that syncs each instance of program1 until each program has reached the same point in code to avoid prematurely moving on and printing the final matrice. 
program2.c calls program1 several times based on the arguments. It gets two arguments: argv[1]: The program which will be called with execv (program1.c) and argv[2]: How many instances of program one should be called. 


## Lab 2: Double-linked list
### 1/17/2020
A double linked list with strings (char arrays) as data saved as a listelement struct. 
Scan from keyboard a number 1-4 to: 1 push string to linked list, 2 print list, 3 delete item, and 4 end program.


## Lab 3: Made my own heap function
### 1/24/2020
A heap simulation in uninitialized space to understand how malloc and free work.
mymalloc function searches in the list for a free chunk that is big enough for the requested memory and returns the address.
myfree function sets the given chunk to “free”, meaning the struct variable info=0. If the previous or next chunk is free as well, it should remove the chunk(s) and link both ends together.
analyse function goes through the list of chunks and prints the contents of the structure for every chunk.

## Lab 4: Multiprocess editing BMP photo brightness
### 1/31/2020
This program reads a bitmap (BMP) file into the memory, allocates with mmap(), and then forks the process. The parent process works on the upper half of all pixels, and the child works on the lower half. It also measures the time with and without fork() and prints the result time.
How to run on command line: ./lab4 [IMAGEFILE] [BRIGHTNESS] [PARALLEL][OUTPUTFILE]
brightness is a number between 0 and 1 and parallel is 0 for working without fork() and 1 with fork()

## Lab 5: fork() practice
### 2/7/2020
Practice fork() by printing numbers in different orders and waiting for the kid. 

## Lab 6: indestructible (nearly) child Program. 
### 2/14/2020
Forks a child process after printing the programs PID.The child process prints the correct time and the current content of the executable’s folder (all files) every 10 seconds and it's PID. Uses a signal handler to avoid termination or killing and the parent process checks if the child process ended with wait(). If so, the child is forked again. 

## Lab 7: Mutual Exclusion
### 2/22/2020
Peterson's algorithm, Lamport's bakery algorithm, and Eisenberg & McGuire algorithm. 
Uses one shared memory array of 1000 characters and will fork into two processes. The child process is alternatively strcpy two long sentences into the shared array. The parent process is strcpy the shared array text into its own array and printing it on the screen.

## Lab 8: Made my own pipe() function
### 2/28/2020
Uses a struct objet with a pipebuffer, buffersize, and start/end. Has three functions:
void init_pipe: initializes the pipe with a size of "size" and sets start and end.
int mywrite: writes "size" bytes from buffer into the pipe, returns size
int myread: reads "size" bytes from pipe into buffer, returns how much it read (max size), 0 if pipe is empty

