*This project has been created as part of the 42 curriculum by salkhali.*

# get_next_line

## Description

`get_next_line` is a function that returns the next line from a file descriptor each time it is called. Between calls, it keeps track of whatever was read past the newline, until EOF is reached.

The project pushed me to explore the following topics:

- **System I/O**
  - What file descriptors are
  - The contract of the `read` syscall: partial reads and offsets
  - Reading from stdin and from files

- **State management**
  - Persisting data across calls
  - Designing a stateful function that stays clear and readable

- **Memory management**
  - `malloc`/`free` discipline and leak prevention on every exit path
  - `BUFFER_SIZE` as a compile-time macro
  - NULL termination and off-by-one errors

- **String and buffer manipulation**
  - Searching for newlines and extracting lines

## Instructions

### Usage

Include the header, then call the function with an open file descriptor. Each call returns one line (including its `\n`, if present), or `NULL` on EOF or error. The caller must free every returned line.

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

To read from standard input instead, pass `0` as the file descriptor:

```c
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    char    *line;

    line = get_next_line(0);
    if (line != NULL)
    {
        printf("%s", line);
        free(line);
    }
    return (0);
}
```

For the bonus (multiple file descriptors at once), include the bonus header instead:

```c
#include "get_next_line_bonus.h"
```

### Compilation

Compile the function together with its utils file. `BUFFER_SIZE` can be set at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

Bonus:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c
```

## Algorithm & Justification

I followed the single responsibility principle as closely as I could: reading, extracting, and updating are separate functions, orchestrated by the main `get_next_line` function.

**Data structure.** I used a singly linked list to hold what has been read so far. Appending a node doesn't require reallocating and copying the whole accumulated string, whereas with a plain array you would have to allocate a larger buffer, copy everything over, and append the new chunk on every read. Over a long line, that repeated copying adds up to O(n²), while appending a node stays O(1).

**Reading.** Reads `BUFFER_SIZE` bytes at a time. A return of `0` signals EOF and a negative value signals failure. Otherwise, the chunk is stored in a new node appended to the list. If the chunk contains a newline, reading stops; if not, it keeps reading until a newline or EOF.

**Extracting.** Walks the list until it finds a newline or the end, computes the line length, allocates exactly that much on the heap, copies the content over, and returns it.

**Updating.** Isolates the leftover (everything after the newline), frees the nodes that made up the returned line, and re-attaches the leftover as the new head of the list.

**Persistence.** The list persists between calls because it is stored in a `static` variable. It is freed completely once the input has been fully read.

**Error handling.** If anything fails during execution, the list is cleared, all resources are freed, pointers are set to `NULL`, and `NULL` is returned as the subject requires. This keeps the code leak-free.

**Bonus.** The algorithm is identical. The only change is that the single static variable becomes a static array indexed by file descriptor (`MAX_OPEN` entries), so each fd keeps its own list. At the start of each call, a pointer to the relevant slot is taken so the same logic runs unchanged. Descriptors outside `0 <= fd < MAX_OPEN` return `NULL`.

## Resources

- [How the kernel manages file descriptors (USNA IC221)](https://www.usna.edu/Users/cs/wcbrown/courses/IC221/classes/L09/Class.html)
- [`read` syscall man page](https://man7.org/linux/man-pages/man3/read.3p.html)

## AI Usage

AI was used to help find relevant resources for the theory and to explain difficult concepts. All code was written by me.
