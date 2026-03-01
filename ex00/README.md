# 🟢 Exercise 00: display_file

## 📝 Objective
Create a simplified version of the `cat` command that displays the content of a single file on the standard output.

## 💡 The Logic

This exercise introduces low-level file manipulation using system calls. 
1. **Argument Parsing:** The program requires exactly one file. If none are provided, it outputs `File name missing.`; if too many are provided, it outputs `Too many arguments.` to standard error (fd 2).
2. **File Descriptors:** We use the `open()` system call with the `O_RDONLY` flag to get a file descriptor. If it fails (returns `-1`), we print `Cannot read file.`.
3. **The Buffer Loop:** Because `malloc` is forbidden, we declare a fixed-size `char buf[4096]`. We use a `while` loop to continuously `read()` chunks of the file into the buffer and `write()` them to standard output until `read()` returns `0` (End of File).
4. **Cleanup:** We safely `close()` the file descriptor before exiting.

## 🛠️ Step-by-Step Solution

1. **The Code:**
   *Check out the source files here:*
   - **[`ft_display_file.c`](ft_display_file.c)**
   - **[`Makefile`](Makefile)**

3. **Testing Edge Cases:**
   Compile the program using the required `Makefile`, then test it against the strict argument limits and error handlers:
   ```bash
   make
   
   # Test 1: Standard working case
   ./ft_display_file Makefile
   
   # Test 2: Missing arguments (Expected: "File name missing.")
   ./ft_display_file
   
   # Test 3: Too many arguments (Expected: "Too many arguments.")
   ./ft_display_file file1 file2
   
   # Test 4: Unreadable/Non-existent file (Expected: "Cannot read file.")
   ./ft_display_file missing_file.txt
   ```
