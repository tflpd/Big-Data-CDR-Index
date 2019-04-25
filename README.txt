The goal of this specific implementation, which was achieved, is to have a retrieve and insert computational cost of O(1) no matter the
size of the data as well as being able to perform actions like delete, find, and combining queries with multiple CDRs almost instantly.

READ ME

SysPro Assignment 1
Athanasios Filippidis
AM : 1115201400215 - sdi1400215@di.uoa.gr

Files:
werhauz.c
hashStructs.h
utilities.c, utilities.h
setters.c, setters.h
list.c, list.h
findFuncs.c, findFuncs.h
stringManipulate.c, stringManipulate.h

makefile included

compile with make
run with: ./werhauz -o <file> -h1 <bucketentries> -h2 <bucketentries> -s <numofbytes>
example:  ./werhauz -o input1.txt -h1 10 -h2 10 -s 160

remove .o with make clean

Implementation notes:
> supports both file streams and commands given by the user
> every srtucture is implemented according to the instructions given
> the implementation does not use duplicates
> dump (bonus) implemented 
> dump gets as argument hashtable1 or hashtable2 and creates files
  dumpedHashT1.txt or dumpedHashT2.txt
> -c flag (optional) not supported
> command  exit: frees all the allocated memory and terminates the program 
  (not requested but implemented)
> command   bye: frees all the overflow buckets and reallocs the main bucket 
  of each hashtable
> hash function: http://www.cse.yorku.ca/~oz/hash.html
> admission: every month is considered to have 30 days (for the dates)
> no memory leaks, checked with valgrind
> read also the comments above every function prototype
