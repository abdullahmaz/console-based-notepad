# Console-Based Notepad

Console-Based Notepad is a simple text editor implemented in C++ that allows users to create, edit, and save text files. It comes with basic functionality such as cursor movement, text insertion and deletion, spell checking, and file loading/saving.

## Features

- **Text Editing**: Users can type, delete, and navigate through text using arrow keys and other standard keyboard shortcuts.
- **Cursor Movement**: Navigate the cursor up, down, left, or right within the text.
- **Spell Checking**: Integrated spell checker suggests corrections for misspelled words based on a provided dictionary file.
- **File Operations**: Load and save text files to/from the local filesystem.
- **Simple Interface**: Clean and intuitive user interface for ease of use.

## How to Use

1. **Compile the Program**: Compile the source code using a C++ compiler such as `g++`.
   
    ```bash
    g++ -o notepad.exe main.cpp
    ```

2. **Run the Program**: Execute the compiled binary to launch the Notepad application.

    ```bash
    ./notepad.exe
    ```

3. **Basic Navigation**:
   - Use arrow keys to navigate the cursor within the text.
   - Press Enter to create a new line.
   - Press Backspace to delete characters.
   - Press Ctrl + S to save the current file.
   - Press Ctrl + L to load a file.

## Requirements

- C++ compiler (e.g., `g++`)
- Windows operating system (the provided code includes Windows-specific headers and system calls)

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
