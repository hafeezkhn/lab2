Exercise :

**001. #LinkedLists**
Write a program that defines a struct called node that contains an integer data and a pointer to the next node. Then, write functions to create a linked list of nodes, insert a node at the beginning, end, or any position of the list, delete a node from the list, reverse the list, and print the list. Use these functions to demonstrate the operations on a sample linked list.

**002. #StacksAndQueues**
Write a program that defines two structs called stack and queue, each containing an array of integers and an integer top or front. Then, write functions to initialize, push, pop, enqueue, dequeue, and display the elements of a stack or a queue. Use these functions to implement a simple calculator that takes an arithmetic expression in postfix notation as input and evaluates it using a stack. Also use these functions to implement a simple simulation of a bank queue that takes the arrival and service times of customers as input and calculates the average waiting time using a queue.

**003. #Trees**
Write a program that defines a struct called tree_node that contains an integer data and two pointers to the left and right child nodes. Then, write functions to create a binary tree from an array of integers, traverse the tree in preorder, inorder, and postorder ways, and print the tree in a horizontal format. Use these functions to create and display a sample binary tree. Next, write functions to create a binary search tree from an array of integers, search for an element in the tree, insert an element into the tree, delete an element from the tree, and find the minimum and maximum elements in the tree. Use these functions to create and display a sample binary search tree.

**004. #HashTables**
Write a program that defines a struct called hash_node that contains a string key and an integer value. Then, write functions to create a hash table of size 10 using an array of pointers to hash_nodes, hash a key using a simple modulo function, insert a key-value pair into the table using linear probing for collision resolution, search for a key in the table and return its value or -1 if not found, delete a key-value pair from the table, and print the table. Use these functions to create and display a sample hash table.

**005. #FunctionPointers_ArgumentsAndReturnValues**
Write a program that defines four functions: add, subtract, multiply, and divide, each taking two integers as parameters and returning an integer result. Then, write another function called apply_operation that takes a function pointer and two integers as parameters and returns the result of calling the function pointer with the two integers. Use this function to apply different operations to different pairs of integers and print the results.

**006. #CallbackFunctions**
Write a program that defines a function called sort_array that takes an array of integers, its size, and a function pointer as parameters and sorts the array using the function pointer as a comparison criterion. Then, write two functions called ascending and descending, each taking two integers as parameters and returning a boolean value indicating whether the first integer is smaller or larger than the second one. Use these functions as callback functions to sort an array of integers in ascending or descending order and print the sorted array.

**007. #FunctionPointerArrays**
Write a program that defines an enum called operation with four values: ADD, SUBTRACT, MULTIPLY, and DIVIDE. Then, declare an array of four function pointers, each pointing to one of the functions defined in the previous exercise. Use the enum values as indices to access the function pointers in the array. Then, write a function called calculate that takes an operation and two integers as parameters and returns the result of calling the corresponding function pointer in the array with the two integers. Use this function to perform different calculations and print the results.

**008. #FunctionPointersInStructures**
Write a program that defines a struct called student that contains three fields: name (a char array of size 20), score (an integer), and compare (a function pointer that takes two student structs as parameters and returns a boolean value indicating whether the first student has a higher score than the second one). Then, declare an array of three student structs and initialize them with some values. Write a function called sort_students that takes an array of student structs, its size, and a function pointer as parameters and sorts the array using the function pointer as a comparison criterion. Use this function to sort the array of students by their scores in ascending or descending order and print their names and scores.

**009. #RecursiveFunctions**
Write a program that defines a recursive function called power that takes two integers as parameters: base and exponent, and returns the result of raising the base to the exponent. Do not use any loops or library functions. Use this function to calculate and print the power of different numbers.

**010. #RecursiveDataStructures**
Write a program that defines a struct called tree_node that contains an integer data and two pointers to the left and right child nodes. Then, write a recursive function called count_nodes that takes a pointer to the root node of a binary tree as a parameter and returns the number of nodes in the tree. Do not use any loops or global variables. Use this function to count and print the number of nodes in a sample binary tree.

**011. #TailRecursionOptimization**
Write a program that defines two recursive functions called factorial and factorial_tail, each taking an integer n as a parameter and returning the factorial of n. The factorial function should use the standard recursive definition: n! = n * (n-1)!, while the factorial_tail function should use an accumulator variable to store the intermediate result and pass it as an additional parameter. The factorial_tail function should be tail recursive, meaning that the recursive call is the last thing it does before returning. Use these functions to calculate and print the factorial of different numbers and compare their performance using a timer or a debugger. Explain how tail recursion optimization works and why it is beneficial for recursive functions.

**012. #StackAndHeapMemory #MemoryAllocationFunctions**
Write a program that defines a function called allocate_memory that takes an integer n as a parameter and allocates n bytes of memory on the heap using malloc. The function should return a pointer to the allocated memory. Then, write another function called print_address that takes a pointer as a parameter and prints its address. Use these functions to demonstrate the difference between stack and heap memory allocation by creating some local and global variables, as well as some pointers to dynamically allocated memory, and printing their addresses. Explain how stack and heap memory allocation work and why they are different.

**013. #StackAndHeapMemory #MemoryAllocationFunctions**
Write a program that defines a struct called student that contains three fields: name (a char pointer), age (an integer), and courses (a char pointer array). Then, write a function called create_student that takes a name, an age, and a list of courses as parameters and creates a new student struct on the heap using malloc. The function should allocate memory for the name and the courses fields as well, and copy the values from the parameters. The function should return a pointer to the new student struct. Then, write another function called delete_student that takes a pointer to a student struct as a parameter and frees the memory allocated for it using free. The function should also free the memory allocated for the name and the courses fields. Use these functions to create and delete some student structs and print their details.

**014. #MemoryLeaksAndMemoryErrors**
Write a program that defines a function called create_array that takes an integer n as a parameter and creates an array of n integers on the heap using malloc. The function should return a pointer to the array. Then, write another function called fill_array that takes a pointer to an array and its size as parameters and fills the array with random numbers. Then, write another function called print_array that takes a pointer to an array and its size as parameters and prints the array elements. Use these functions to create and fill some arrays of different sizes and print them. Then, introduce a memory leak or a memory error in your program by either forgetting to free the allocated memory, freeing the same memory twice, accessing memory out of bounds, or using an invalid pointer. Run your program and observe the effects of the memory leak or error using a debugger or a memory profiler. Explain what causes the memory leak or error and how to avoid it.

**015. #GDB #Breakpoints #Watchpoints #CoreDumps #RemoteDebugging**
Write a program that defines a function called factorial that takes an integer n as a parameter and returns the factorial of n using recursion. Then, write a main function that takes an integer as input from the user and calls the factorial function with that input. Compile your program with the -g flag to enable debugging symbols. Then, use GDB to debug your program and set and remove breakpoints at different lines of code. Use the break, delete, run, continue, next, step, and print commands to control the execution flow and inspect the values of variables.

**016. #GDB #Breakpoints #Watchpoints #CoreDumps #RemoteDebugging**
Download a large C program from an online source, such as GitHub or SourceForge, and compile it with the -g flag.

**017. #GDB #Breakpoints #Watchpoints #CoreDumps #RemoteDebugging**
Use GDB to debug the large C program that you wrote or downloaded in the previous exercise. Set and remove watchpoints on some variables that are important for the functionality or logic of your program. Use the watch, delete, run, continue, next, step, and print commands to control the execution flow and inspect the values of variables.

**018. #GDB #Breakpoints #Watchpoints #CoreDumps #RemoteDebugging**
Introduce a segmentation fault in your large C program by either accessing an invalid memory address, dereferencing a null pointer, or writing beyond the bounds of an array. Run your program and observe that it crashes and generates a core dump file. Then, use GDB to analyse the core dump file and find the cause and location of the segmentation fault. Use the core, backtrace, frame, list, and print commands to examine the core dump file and inspect the values of variables and registers.

**019. #GDB #Breakpoints #Watchpoints #CoreDumps #RemoteDebugging**
Set up a remote debugging environment. Use gdbserver tool to run a program on one terminal and debug it from another terminal on the same machine.

**020. #GDB #Breakpoints #Watchpoints #CoreDumps #RemoteDebugging**
Write a C program that calculates the factorial of a given number using recursion. Compile the program with the -g flag to enable debugging symbols. Then, use gdb to run the program and inject errors into it using different commands. For each error, observe the output of the program and use gdb to identify and fix the error. Use the following commands for error injection:

* `set n = -1`: This command changes the value of the parameter n to -1, which causes an infinite recursion and maybe a stack overflow.
* `call printf("%d\n", factorial(5))`: This command calls the printf function with the factorial function as an argument, which causes the program to print 120 before returning to the original execution point.

**021. #ErrorCodesAndErrorMessages #ErrorPropagation #SignalHandling**
Write a program that defines a function called open_file that takes a file name as a parameter and tries to open the file in read mode. The function should return an integer error code indicating whether the file was opened successfully or not. The function should also print an appropriate error message if the file could not be opened. Use the fopen and perror functions to perform the file operation and display the error message. Then, write a main function that takes a file name as input from the user and calls the open_file function with that input. Check the return value of the open_file function and print a success message if the file was opened successfully or an error message if not.

**022. #ErrorCodesAndErrorMessages #ErrorPropagation #SignalHandling**
Write a program that consists of two modules: main.c and math.c. The math.c module should define two functions: divide and power, each taking two integers as parameters and returning an integer result. The divide function should perform integer division and check for division by zero error. The power function should perform exponentiation and check for overflow error. Both functions should return an integer error code indicating whether the operation was successful or not. The main.c module should include the math.c module and define a main function that takes two integers as input from the user and calls the divide and power functions with those inputs. The main function should check the return values of the divide and power functions and print the results if they were successful or print appropriate error messages if not.

**023. #ErrorCodesAndErrorMessages #ErrorPropagation #SignalHandling**
Write a program that defines a function called signal_handler that takes an integer signal number as a parameter and prints an appropriate message depending on the signal received. The function should also exit the program gracefully using the exit function. Then, write a main function that registers the signal_handler function as a handler for some common signals, such as SIGINT, SIGSEGV, SIGFPE, and SIGTERM, using the signal function. Then, write some code that generates some of these signals, such as pressing Ctrl+C, dereferencing a null pointer, dividing by zero, or sending a kill command from another terminal. Run your program and observe how it handles different signals using your signal_handler function.

**024. #LittleEndianAndBigEndian #ByteOrdering #NetworkByteOrder #EndiannessConversion**
Write a program that defines a union called endian_test that contains two fields: a char array of size 4 and an unsigned int. Then, declare an object of the union and initialize the unsigned int field with the hexadecimal value 0x01020304. Then, print the value of the first element of the char array using the %x format specifier. If the output is 04, then the system is little-endian. If the output is 01, then the system is big-endian.

**025. #LittleEndianAndBigEndian #ByteOrdering #NetworkByteOrder #EndiannessConversion**
Write a program that defines a function called swap_bytes that takes an unsigned int as a parameter and returns an unsigned int with its bytes reversed. The function should use bitwise operators to swap the bytes of the input. For example, if the input is 0x01020304, the output should be 0x04030201. Use this function to convert between little-endian and big-endian representations of integers. Print the input and output values in hexadecimal format.

**026. #LittleEndianAndBigEndian #ByteOrdering #NetworkByteOrder #EndiannessConversion**
Write a program that uses the socket library to create a simple client-server application that can exchange messages over a network. The server should listen on a port number specified as a command-line argument and accept connections from clients. The client should take the server's IP address and port number as command-line arguments and connect to the server. The server and client should use the send and recv functions to send and receive messages as unsigned ints. The server and client should also use the htonl and ntohl functions to convert between host byte order and network byte order before sending and after receiving messages. The network byte order is big-endian, so these functions may or may not swap bytes depending on the endianness of the host system. Print the messages in hexadecimal format before and after conversion. Explain why network byte order is used for network communication and how it ensures interoperability between different systems.


**027. #NullPointersAndDanglingPointers #MemoryLeaksAndMemoryCorruption #BufferOverflows #AddressSpaceLayoutRandomisation**
Write a program that defines a function called print_string that takes a char pointer as a parameter and prints the string pointed by it. Then, write a main function that declares two char pointers and assigns them to NULL and "Hello" respectively. Then, call the print_string function with both pointers and observe the output. Next, declare another char pointer and assign it to a string literal "World". Then, use the free function to deallocate the memory pointed by it. Then, call the print_string function with this pointer and observe the output.

**028. #NullPointersAndDanglingPointers #MemoryLeaksAndMemoryCorruption #BufferOverflows #AddressSpaceLayoutRandomisation**
Write a program that defines a function called create_array that takes an integer n as a parameter and creates an array of n integers on the heap using malloc. The function should return a pointer to the array. Then, write another function called fill_array that takes a pointer to an array and its size as parameters and fills the array with random numbers. Then, write another function called print_array that takes a pointer to an array and its size as parameters and prints the array elements. Use these functions to create and fill some arrays of different sizes and print them. Then, introduce a memory leak in your program by either forgetting to free the allocated memory or losing the reference to the allocated memory. Run your program and observe the effects of the memory leak using a debugger or a memory profiler.

**029. #NullPointersAndDanglingPointers #MemoryLeaksAndMemoryCorruption #BufferOverflows #AddressSpaceLayoutRandomisation**
Write a program that defines a function called copy_string that takes two char pointers as parameters: source and destination, and copies the string from source to destination using a loop. Do not use any library functions or check for the size of the destination buffer. Then, write a main function that declares two char arrays of size 10 and 5 respectively and initializes them with some values. Then, call the copy_string function with these arrays as arguments and observe the output.

**030. #NullPointersAndDanglingPointers #MemoryLeaksAndMemoryCorruption #BufferOverflows #AddressSpaceLayoutRandomisation**
Write a program that defines a function called vulnerable that takes a char pointer as a parameter and copies it to a local char array of size 10 using strcpy function. Do not check for the size of the input or the destination buffer. Then, write another function called secret that prints a secret message. Then, write a main function that takes a command-line argument and passes it to the vulnerable function. Compile your program with the -fno-stack-protector flag to disable stack protection mechanisms. Then, run your program with different inputs and try to overwrite the return address of the vulnerable function with the address of the secret function. Use GDB or objdump to find the addresses of these functions. Observe that you can execute the secret function by exploiting the buffer overflow vulnerability. Next, enable address space layout randomisation (ASLR) on your system using the sysctl command or by editing the /proc/sys/kernel/randomize_va_space file. Run your program again with different inputs and try to execute the secret function using the same attack. Observe that you cannot predict the address of the secret function anymore and your attack fails.

**031. #SignalTypesAndSignalHandlers #SignalMasksAndSignalDelivery #SignalSafety**
Write a program that defines a function called signal_handler that takes an integer signal number as a parameter and prints an appropriate message depending on the signal received. The function should also exit the program gracefully using the exit function. Then, write a main function that registers the signal_handler function as a handler for some common signals, such as SIGINT, SIGSEGV, SIGFPE, and SIGTERM, using the signal function. Then, write some code that generates some of these signals, such as pressing Ctrl+C, dereferencing a null pointer, dividing by zero, or sending a kill command from another terminal. Run your program and observe how it handles different signals using your signal_handler function. *(Note: This exercise appears again

**032. #SignalTypesAndSignalHandlers #SignalMasksAndSignalDelivery #SignalSafety**
Write a program that defines a function called busy_work that takes no parameters and performs some computation-intensive task in an infinite loop. Then, write a main function that creates a sigset_t object and initializes it with the SIGINT signal using the sigemptyset and sigaddset functions. Then, use the sigprocmask function to block the SIGINT signal using the sigset_t object. Then, call the busy_work function and observe that pressing Ctrl+C does not interrupt the program. Next, use the sigprocmask function again to unblock the SIGINT signal using the sigset_t object. Then, call the busy_work function again and observe that pressing Ctrl+C interrupts the program.


**033. #TextSegment #DataSegment #BSSSegment #HeapAndStack #SharedLibraries**
Write a program that defines a function called allocate_memory that takes an integer n as a parameter and allocates n bytes of memory on the heap using malloc. The function should return a pointer to the allocated memory. Then, write another function called print_address that takes a pointer as a parameter and prints its address. Use these functions to demonstrate the use of heap memory segment by creating some pointers to dynamically allocated memory and printing their addresses. Then, write another function called print_local that takes no parameters and declares a local variable and prints its address. Use this function to demonstrate the use of stack memory segment by creating some local variables and printing their addresses. Learn how heap and stack memory segments are used to store different types of data and how they grow and shrink during the execution of your program.

**034. #TextSegment #DataSegment #BSSSegment #HeapAndStack #SharedLibraries**
Write a program that uses some functions from the math library, such as sqrt, pow, sin, and cos. Include the math.h header file in your program and use the -lm flag to link with the math library while compiling your program. Then, use the ldd command to display the shared libraries that your program depends on and their locations. Explain what shared libraries are and how they are loaded into memory when your program is executed. Find out the advantages and disadvantages of using shared libraries over static libraries.

**035. #CreatingStaticAndDynamicLibraries #LinkingWithStaticAndDynamicLibraries**
Write a program that consists of two modules: main.c and math.c. The math.c module should define two functions: add and subtract, each taking two integers as parameters and returning an integer result. The main.c module should include the math.c module and define a main function that takes two integers as input from the user and calls the add and subtract functions with those inputs. Compile the math.c module with the -c flag to create an object file called math.o. Then, use the ar command to create a static library called libmath.a from the math.o file. Then, compile the main.c module and link it with the libmath.a library using the -L and -l flags. Run your program and observe the output.

**036. #CreatingStaticAndDynamicLibraries #LinkingWithStaticAndDynamicLibraries**
Write a program that consists of two modules: main.c and math.c. The math.c module should define two functions: multiply and divide, each taking two integers as parameters and returning an integer result. The main.c module should include the math.c module and define a main function that takes two integers as input from the user and calls the multiply and divide functions with those inputs. Compile the math.c module with the -c and -fPIC flags to create a position-independent object file called math.o. Then, use the gcc command with the -shared flag to create a dynamic library called libmath.so from the math.o file. Then, compile the main.c module and link it with the libmath.so library using the -L and -l flags. Run your program and observe the output.

**037. #CreatingStaticAndDynamicLibraries #LinkingWithStaticAndDynamicLibraries**
Write a program that defines some global and static variables, some local variables, some constants, some functions, and a main function. Compile your program with the -g flag to enable debugging symbols. Then, use the nm command to display the symbols defined in your executable file, such as variables and functions. Observe the name, address, and type of each symbol. Explain what nm command does and how it can help you to inspect the symbols in your program. Next, use the ldd command to display the shared libraries that your program depends on and their locations.

**038. #Pipes #InterProcessCommunication** 
Write a program that creates a pipe using the pipe function and forks a child process using the fork function. The parent process should write a message to the pipe using the write function, and the child process should read the message from the pipe using the read function. Both processes should close the unused ends of the pipe using the close function. The child process should print the message received from the parent process to the standard output.

**039. #IPC #Pipes #NamedPipes #MessageQueues #SharedMemory #Semaphores**
Write a program that creates a named pipe using the mkfifo function and opens it for writing using the open function. The program should take a command-line argument as the name of the named pipe. The program should write some messages to the named pipe using the write function and close it using the close function. Then, write another program that opens the same named pipe for reading using the open function and reads the messages from it using the read function. The program should print the messages received from the other program to the standard output and close the named pipe using the close function.

**040. #IPC #Pipes #NamedPipes #MessageQueues #SharedMemory #Semaphores**
Write a program that creates a message queue using the msgget function and sends some messages to it using the msgsnd function. The program should use a struct called message that contains a long type field and a char array field. The long type field should store the message type and the char array field should store the message text. The program should take a command-line argument as the key for creating the message queue. The program should also display the message queue identifier returned by the msgget function. Then, write another program that opens the same message queue using the msgget function and receives the messages from it using the msgrcv function. The program should print the messages received from the other program to the standard output and delete the message queue using the msgctl function.

**041. #IPC #Pipes #NamedPipes #MessageQueues #SharedMemory #Semaphores**
Write a program that creates a shared memory segment using the shmget function and attaches it to its address space using the shmat function. The program should use a struct called data that contains two integer fields: value and flag. The value field should store some data and the flag field should indicate whether the data is ready or not. The program should write some data to the shared memory segment using the value field and set the flag field to 1 when done. The program should also display the shared memory identifier returned by the shmget function and detach from the shared memory segment using the shmdt function. Then, write another program that opens the same shared memory segment using the shmget function and attaches it to its address space using the shmat function. The program should read the data from the shared memory segment using the value field when the flag field is 1 and print it to the standard output. The program should also detach from and delete the shared memory segment using the shmdt and shmctl functions.

**042. #IPC #Pipes #NamedPipes #MessageQueues #SharedMemory #Semaphores**
Write a program that creates two semaphores using semget: one for mutual exclusion and one for synchronization. The program should also create two child processes using fork: one for producer and one for consumer. The producer process should generate some random numbers and store them in an array of size 10, which acts as a buffer. The producer process should use semop to lock and unlock both semaphores: it should lock mutual exclusion semaphore before accessing buffer, lock synchronization semaphore when buffer is full, unlock mutual exclusion semaphore after accessing buffer, unlock synchronization semaphore when buffer is not empty. The consumer process should read numbers from buffer array and print them to standard output. The consumer process should also use semop to lock and unlock both semaphores: it should lock mutual exclusion semaphore before accessing buffer, lock synchronization semaphore when buffer is empty, unlock mutual exclusion semaphore after accessing buffer, unlock synchronization semaphore when buffer is not full.

**043. #ThreadCreationAndTermination #ThreadSynchronisation #ThreadCommunication #ThreadSafety**
Write a program that uses the pthread library to create and terminate threads. The program should define a function called thread_func that takes a void pointer as a parameter and prints a message with the thread id using the pthread_self function. The function should also return a void pointer with some value. The program should create four threads using the pthread_create function and pass them different arguments using the void pointer. The program should also join the threads using the pthread_join function and print the return values of the threads.

**044. #ThreadCreationAndTermination #ThreadSynchronisation #ThreadCommunication #ThreadSafety**
Write a program that uses the pthread library to create and synchronise threads using mutexes and condition variables. The program should define a global variable called count and initialise it to zero. The program should also define a mutex called lock and two condition variables called cond1 and cond2. The program should create two threads: one for incrementing count and one for decrementing count. The incrementing thread should lock the mutex, check if count is less than 10, increment count by one, signal cond1, wait for cond2, unlock the mutex, and repeat until count reaches 10. The decrementing thread should lock the mutex, check if count is greater than 0, decrement count by one, signal cond2, wait for cond1, unlock the mutex, and repeat until count reaches 0. Both threads should print the value of count after each operation.


**045. #ThreadCreationAndTermination #ThreadSynchronisation #ThreadCommunication #ThreadSafety**
Write a program that uses the pthread library to create and communicate between threads using message queues or shared memory. The program should create two threads: one for producer and one for consumer. The producer thread should generate some random numbers and send them to the consumer thread using either a message queue or a shared memory segment. The consumer thread should receive the numbers from the producer thread and print them to the standard output. The program should use appropriate functions to create, open, close, send, receive, attach, detach, and delete the message queue or shared memory segment.

**046. #ThreadCreationAndTermination #ThreadSynchronisation #ThreadCommunication #ThreadSafety**
Write a program that uses the pthread library to create and demonstrate thread safety. The program should define a global variable called balance and initialise it to 1000. The program should also define a function called deposit that takes an integer amount as a parameter and adds it to balance. The function should also print the new balance after each deposit. The program should create two threads: one for depositing 100 five times and one for depositing 200 five times. Both threads should call the deposit function with their respective amounts. Observe that without any synchronisation mechanism, the output may be inconsistent or incorrect due to race conditions. Then, modify your program to use a mutex or a semaphore to protect the critical section of code where balance is updated. Observe that with synchronisation mechanism, the output is consistent and correct.

**047. #UART**
Write a C program to:

* send a string to a virtual UART device in Linux. The string should be encrypted using a simple XOR cipher with a given key.
* receive an encrypted string from the virtual UART device and decrypt it using the same key. Print the decrypted string to the console and check if it matches the original string.

* Implement flow control using the RTS/CTS signals on the virtual UART device and show tx and rx. Use a timer to simulate different transmission speeds and delays. Display the number of bytes sent and received on the console.

* Implement an interrupt-driven UART receive routine that saves the received data to a circular buffer. The buffer should have a fixed size and handle overflow and underflow conditions. Write a function to read data from the buffer and print it to the console.

* Write a Python script to simulate a device sending a continuous stream of data over the virtual UART device, and write a C program to receive and parse the data. The data should consist of packets with a header, payload and checksum. The header should contain the packet type, length and sequence number. The payload should contain random alphanumeric characters. The checksum should be calculated using a CRC algorithm. The C program should verify the checksum and display the packet information on the console.

**048. #SPI**
Write a C program to:

* read data from a virtual SPI device using the spidev interface.
* write data to the virtual SPI device

* Implement an interrupt-driven SPI receive routine that saves the received data in a circular buffer.

* Implement a DMA-based SPI transfer routine that reads and writes data to the virtual SPI device using the spidev interface.

* Write a Python script to simulate a device sending a continuous stream of data over the virtual SPI device, and write a C program to receive and parse the data.

**049. #I2C**
Write a C program to:

* read data from a virtual I2C device using the i2c-dev interface.
* write data to the virtual I2C device

* Implement an interrupt-driven I2C receive routine that saves the received data to a circular buffer.

* Implement a DMA-based I2C transfer routine that reads and writes data to the virtual I2C device using the i2c-dev interface.

* Write a Python script to simulate a device sending a continuous stream of data over the virtual I2C device, and write a C program to receive and parse the data.

**050. #Makefile #linkerScript
 * Understanding Dependencies and variables
 * Paths ,targets ,shell functions, macros

 * Memory sections,linking multiple objects
 * including discarding sections
 * VMA and LMA ,two memory system
 * location counter,addr of data section in Rom
 * Creating custom section, copying section from rom to RAM
 * linker command language

