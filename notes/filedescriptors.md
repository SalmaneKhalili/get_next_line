*everything behaves as a file within a unix system*
a file descriptor is a process local handle to a kernel object.

there are automatic fds, 

## THE PROCESS TABLE 
Kernel decides which process gets to run on the CPU, to do so it uses a datastructure called the process table.

Each process has an entry in this table (these entries are called process control blocks, they include all sort of information, such as the PID) 

the process table is like the business record a business keeps of their customers.

## WHEN A PROCESS OPENS A FILE 
when a process opens a file to read from or write into, sever entities are involved.
 - the actual file in the hardrive
 - a record that stores in memory basic file info.
 - a record specifying the processes connections to files
 - the number that the prcoess uses to tell the kernel which file its referring to.

## UNIX I / O file descriptors



