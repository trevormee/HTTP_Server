## Overview
This is a simple HTTP server that utilizes TCP sockets for handling HTTP requests

## Project Members
Trevor Mee

## Screen Captures
Navigate into the Screen_Captures directory to find 4 screenshots of the project working on my end.
- working_clientServer_index.png: Displays a screen shot of the client and server communicating to display 'index.html' on a web broswer.
- working_clientServer_dragon.png: Displays a screen shot of the client and server communicating to display 'img.jpg' on a web browser.
- invalid_clientServer_htmlFile.png: Displays a screen shot of the client and server communicating to display an error message for an invalid html file.
- shut_down_server.png: Displays a screen shot of the connection being broken between the client and server after the server has been shut down.

## Compilation and Running

- Use WSL for compiling and running this program

1. **Ensure that port 60001 is available to be opened**

2. **Navigate into the projects root directory**

3. **Compile the program:**
```bash
    make
```

4. **Run the program**
```bash
    ./proj1
```

## Usage
Once the server is running, you can access it through a web browser or through command line commands like 'curl'.

**Example**
- Open a web browser and go to 'http://localhost:60001/index.html'

