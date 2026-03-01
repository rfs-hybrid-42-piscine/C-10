# 🟢 Exercise 03: hexdump

## 📝 Objective
Create a program that displays a given file's binary content on screen, replicating the system's `hexdump` tool. It must format the data into columns and specifically handle the `-C` formatting option.

## 💡 The Logic

This is the final boss of the C 10 module, conceptually similar to `ft_print_memory` from C 02, but operating on live file streams.
1. **The State Machine:** We use a custom `t_hex` structure to track the 16-byte buffer, the global byte offset across multiple files, and the canonical `-C` formatting flag.
2. **The Asterisk (*) Collapse:** The program compares the current 16-byte buffer with the previous one using `ft_memcmp`. If multiple lines of data are exactly identical, it skips printing the duplicates and simply outputs a single `*` character.
3. **Endianness & Formatting:** For the default hexdump behavior, the bytes are swapped (`byte[1]` before `byte[0]`) to natively support Little-Endian word representation. When the `-C` flag is active, the bytes are printed in strict sequential order, alongside their ASCII equivalents (replacing non-printables with `.`).

## 🛠️ Step-by-Step Solution

1. **The Code:**
   *Check out the source files here:*
   - **[`ft_hexdump.c`](ft_hexdump.c)**
   - **[`ft_hexdump_print.c`](ft_hexdump_print.c)**
   - **[`ft_hexdump_utils.c`](ft_hexdump_utils.c)**
   - **[`ft_hexdump.h`](ft_hexdump.h)**
   - **[`Makefile`](Makefile)**

3. **Testing Edge Cases:**
   Compare your output directly against the native system utility to verify formatting:
   ```bash
   make
   
   # Test 1: Standard Little-Endian formatting (No flags)
   ./ft_hexdump ft_hexdump.c
   hexdump ft_hexdump.c         # Compare the two!
   
   # Test 2: Canonical formatting with ASCII characters
   ./ft_hexdump -C ft_hexdump.c
   hexdump -C ft_hexdump.c      # Compare the two!
   
   # Test 3: Multiple file offset tracking
   ./ft_hexdump -C Makefile ft_hexdump.c
   
   # Test 4: The Asterisk (*) Collapse
   # Create a file with repeating identical characters
   echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" > test.txt
   ./ft_hexdump -C test.txt     # Should print the first line, an asterisk, and the EOF offset
   
   # Test 5: Missing files (Testing errno)
   ./ft_hexdump -C missing.txt
   ```
