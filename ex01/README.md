# 🟢 Exercise 01: cat

## 📝 Objective
Recreate the standard Unix `cat` utility. It must support reading from standard input, parsing multiple files sequentially, and translating system errors using the global `errno` variable.

## 💡 The Logic

1. **Standard Input Fallback:** If no arguments are provided, or if the argument is strictly `-`, the program assigns `0` as the file descriptor to dynamically read from standard input.
2. **Global System Errors (`errno`):** If a file cannot be opened (e.g., missing or permission denied), the system sets an error code in `errno`. We use `strerror(errno)` combined with `basename(argv[0])` to accurately format and print the exact Unix error string to standard error.
3. **The 30KB Limit:** To comply strictly with the module constraints, the read buffer is sized at `28672` bytes (exactly 28 KB), heavily optimizing the system calls while staying below the slightly less than 30 KB limit.
4. **Execution Pipeline:** If one file fails, the program prints the error but safely continues to the next file, returning an exit status of `1` only at the very end.

## 🛠️ Step-by-Step Solution

1. **The Code:**
   *Check out the source files here:* - **[`ft_cat.c`](ft_cat.c)**
   - **[`Makefile`](Makefile)**

2. **Testing Edge Cases:**
   Test the sequential pipeline and the translation of system-level errors:
   ```bash
   make
   
   # Test 1: Standard working case (Single & Multiple Files)
   ./ft_cat Makefile
   ./ft_cat Makefile ft_cat.c
   
   # Test 2: Missing file mixed with valid files (Validates pipeline continuation & errno)
   ./ft_cat Makefile does_not_exist.txt ft_cat.c
   
   # Test 3: Standard Input (Type text and hit Enter. Press Ctrl+D to exit)
   ./ft_cat
   
   # Test 4: Standard Input via the "-" flag mixed with files
   ./ft_cat Makefile - ft_cat.c
   ```
