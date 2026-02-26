*This project has been created as part of the 42 curriculum by maaugust.*

<div align="center">
  <img src="https://raw.githubusercontent.com/rfs-hybrid/42-piscine-artwork/main/assets/covers/cover-c10.png" alt="C 10 Cover" width="100%" />
</div>

<div align="center">
  <h1>💻 C 10: File I/O & Unix Utilities</h1>
  <p><i>Mastering file descriptors, system calls, and recreating shell commands.</i></p>
  
  <img src="https://img.shields.io/badge/Language-C-blue" alt="Language badge" />
  <img src="https://img.shields.io/badge/Grade-100%2F100-success" alt="Grade badge" />
  <img src="https://img.shields.io/badge/Norminette-Passing-success" alt="Norminette badge" />
</div>

---

## 💡 Description
**C 10** is an introduction to **Systems Programming**. Up until now, your programs have only interacted with data passed through standard input or arguments. In this module, you will learn how to interact directly with the Operating System's filesystem.

You will use low-level system calls (`open`, `read`, `write`, `close`) to manipulate File Descriptors. You will also learn how to capture and display system-level errors using `errno` and `strerror`. The ultimate goal of this module is to write your own functional versions of standard Unix utilities like `cat`, `tail`, and `hexdump`.

---

## 🧠 Exercise Breakdown & Logic

*The following section explains the core concepts required to solve each exercise. It focuses on the fundamental logic of C programming, emphasizing file I/O operations and buffer management.*

### 🔹 Basic File Operations
| Exercise | Concept & Logic |
| :--- | :--- |
| **[`ex00: display_file`](ex00)** | **Basic I/O:** Replicating a simplified file reader using a fixed-size buffer. <br><br>**Logic:** The program takes a single file path as an argument. We use `open()` to get a file descriptor, and a `while` loop with `read()` to pull chunks of text into a fixed-size character array (without using `malloc`). We use `write()` to print the buffer to standard output, and finally `close()` the file. Custom error messages handle missing arguments or unreadable files. |
| **[`ex01: cat`](ex01)** | **Standard Input & Errno:** Replicating the Unix `cat` command. <br><br>**Logic:** Unlike `ex00`, `cat` can read from standard input (`stdin`) if no arguments are provided, or parse multiple files sequentially. If a file cannot be opened (e.g., permission denied or doesn't exist), we must capture the global `errno` variable and use `strerror()` and `basename()` to print the exact system error message before moving to the next file. Memory is restricted to a fixed-size array of slightly less than 30 KB. |

### 🔢 Advanced Parsing & Offsets
| Exercise | Concept & Logic |
| :--- | :--- |
| **[`ex02: tail`](ex02)** | **Buffer Offsets:** Replicating the `tail` command to read the end of a file. <br><br>**Logic:** This requires dynamic memory allocation (`malloc` and `free`). We must parse the command-line arguments to find the `-c` option, which dictates exactly how many bytes from the end of the file we need to print. The algorithm involves reading the file to calculate its total size, establishing an offset pointer, and only printing from that offset to the EOF (End of File). |
| **[`ex03: hexdump`](ex03)** | **Binary Translation:** Replicating the `hexdump` command with the `-C` formatting option. <br><br>**Logic:** This is an incredibly complex formatting challenge. We must read a file byte-by-byte and print its contents in three distinct columns: the hexadecimal memory offset, the raw hexadecimal value of the bytes, and the ASCII representation of those bytes. This requires rigorous buffer management to align the output perfectly, even if the file size is not perfectly divisible by 16. |

---

## 🛠️ Instructions

### 🧪 Compilation & Testing
Every single exercise in **C 10** must be submitted with its own `Makefile` containing the rules: `all`, `clean`, and `fclean`.

1. **Clone the repository:**
   ```bash
   git clone <your_repository_link>
   cd 42-Piscine/C-10
   ```

2. **Testing ex00 (display_file):**
   ```bash
   cd ex00
   make
   ./ft_display_file Makefile
   ```

3. **Testing ex01 (cat):**
   ```bash
   cd ex01
   make
   ./ft_cat Makefile non_existent_file.txt
   ```

4. **Testing ex02 (tail):**
   ```bash
   cd ex02
   make
   ./ft_tail -c 50 Makefile
   ```

### 🚨 The Norm
Moulinette relies on a program called `norminette` to check if your files comply with the Norm. Every single `.c` and `.h` file must pass. 

**The 42 Header:**
Before writing any code, every file must start with the standard 42 header. `norminette` will automatically fail any file missing this specific signature.

Run the following command before pushing:
```bash
norminette -R CheckForbiddenSourceHeader <file.c>
```

---

## 📚 Resources & References

* `man 2 open` / `man 2 read` / `man 2 write` / `man 2 close` - Manuals for system calls.
* `man 3 errno` - Understanding system error codes.
* `man cat` / `man tail` / `man hexdump` - Manuals for the actual utilities you are replicating.
* [File I/O in C](https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/) - A guide to interacting with file descriptors.
* [42 Norm V4](https://cdn.intra.42.fr/pdf/pdf/96987/en.norm.pdf) - The strict coding standard for 42 C projects.

### 🤖 AI Usage Guidelines
* **Code:** No AI-generated code was used to solve these exercises. All C functions and utilities were built manually to strictly comply with the 42 Norm and deeply understand manual memory manipulation, enforcing the concept that learning is about developing the ability to find an answer, not just getting one directly.
* **Documentation:** AI tools were utilized to structure this `README.md` and format the logic breakdowns to create a clean, accessible educational resource for fellow 42 students.
