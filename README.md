# Source to HTML Converter

Source to HTML Converter is a C project that converts C source code into an HTML file with syntax highlighting. It uses HTML and CSS with VS Code Dark Theme-inspired colors to display code in a browser.

## Features
- Reads C source code from a file.
- Identifies keywords, variables, operators, strings, comments, numbers, and header files.
- Converts identified tokens into HTML span tags.
- Applies syntax highlighting using CSS.
- Generates an `output.html` file that can be viewed in a web browser.

## Workflow
1. Accepts the input source file through command-line arguments.
2. Opens and reads the source file character by character.
3. Identifies different C language tokens.
4. Converts tokens into HTML elements with CSS classes.
5. Generates the final `output.html` file with syntax highlighting.

## Technologies Used
- C Programming
- File Handling
- HTML
- CSS
- String Handling
- Character Handling

## Execution
```bash
gcc *.c -o source_to_html
./source_to_html sample.c
```

Open `output.html` in a web browser to view the highlighted source code.
