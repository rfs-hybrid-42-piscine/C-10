# 🟢 Exercise 02: tail

## 📝 Objective
Recreate the Unix `tail` command, specifically handling the `-c` flag to print a specified number of bytes from the end of one or multiple files.

## 💡 The Logic

Reading the end of a potentially massive file without overflowing RAM requires a strategic memory approach.
1. **The Circular Buffer:** Instead of allocating memory for the entire file, we `malloc` a buffer exactly the size of the requested `-c` length. As we read the file, we place new bytes into the buffer using modulo arithmetic (`buf[total_bytes % len]`). This constantly overwrites the oldest data, meaning our memory footprint never grows, even if we process a 50 GB file!
2. **Flag Parsing:** The program strictly extracts the numeric byte length, supporting both attached (`-c50`) and detached (`-c 50`) flag formatting. 
3. **Header Formatting:** When multiple files are parsed, the program injects headers (`==> filename <==`) to separate the outputs, closely mimicking the standard Unix utility.

## 🛠️ Step-by-Step Solution

1. **The Code:**
   *Check out the source files here:*
   - **[`ft_tail.c`](ft_tail.c)**
   - **[`ft_tail_utils.c`](ft_tail_utils.c)**
   - **[`ft_tail.h`](ft_tail.h)**
   - **[`Makefile`](Makefile)**

3. **Testing Edge Cases:**
   ```bash
   make
   
   # Test 1: Standard execution (Last 50 bytes)
   ./ft_tail -c 50 Makefile
   
   # Test 2: Multiple files (Should display ==> filename <== headers)
   ./ft_tail -c 20 Makefile ft_tail.c
   
   # Test 3: Attached flag formatting
   ./ft_tail -c50 Makefile
   
   # Test 4: Missing byte count error handling (Should NOT Segfault!)
   ./ft_tail -c
   
   # Test 5: File smaller than requested bytes (Should cleanly print whole file)
   ./ft_tail -c 999999 Makefile
   
   # Test 6: Standard Input testing (Type lines, then press Ctrl+D to see the tail)
   ./ft_tail -c 15

   # Test 7: Standard Input via the "-" flag mixed with files
   ./ft_tail -c 10 Makefile - ft_hexdump.c
   ```
