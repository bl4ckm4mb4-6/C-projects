# CLI File Shredder

A secure, command-line file shredding tool written in C. This program securely overwrites sensitive files before deleting them to prevent recovery, 
following the **DoD 5220.22-M** standard (3-pass overwrite).

## Features

* **Secure Overwriting (DoD 5220.22-M)**: Overwrites the target file data three times before deletion using:
  1. Pass 1: All zeros (`0x00`)
  2. Pass 2: All ones (`0xFF`)
  3. Pass 3: Random pseudo-binary data (`rand()`)
* **Path Sanitization**: Automatically strips trailing newlines and surrounding quotes from file paths entered by the user.
* **Low-Level File Management**: Directly manipulates binary file streams (`rb+`) and controls memory buffers for maximum efficiency.
* **Safe Deletion**: Unlinks/removes the target file from the filesystem only after complete multi-pass shredding.

## Technical Stack

* **Language**: C (POSIX-compatible)
* **Libraries**: `<stdio.h>`, `<stdlib.h>`, `<time.h>`, `<string.h>`, `<unistd.h>`

## Prerequisites & Compilation

To compile and run this project, you need a C compiler (such as `gcc`).

1. **Clone the repository**:
   ```bash
   git clone https://github.com/bl4ckm4mb4-6/file-shredder.git
   cd file-shredder
   ```

2. **Compile the source code**:
   ```bash
   gcc file_shredder.c -o file_shredder
   ```

## Usage

Run the compiled executable from your terminal:

```bash
./file_shredder
```

When prompted, enter the path to the file you want to securely destroy:
```text
Inserisci path del file da eliminare: /path/to/your/secret.txt
```

Alternatively, you can run it in an IDE.

> ⚠️ **Warning**: File shredding is irreversible. Once a file is processed by this tool, its contents cannot be recovered by any standard file recovery software. Use with caution.

## License

This project is open-source and available under the [MIT License](LICENSE).
