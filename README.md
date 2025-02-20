## Overview
This is a simple HTTP client and server program that uses TCP sockets to handle GET requests.

## Project Members
Trevor Mee

## File Structure Breakdown
**Root Directory**
- httpServer.cpp (source code for the HTTP Server)
- httpClient.cpp (source code for the HTTP Client)
- Makefile
- Protocol_Document_P2.pdf
- README.md
- img.jpg
- index.html
- testPresence.html

**Screen_Captures Directory**

Navigate into the Screen_Captures directory to find 6 screenshots of the project working on my end.
- p2_client_server_connection_establishment.png: Displays an image of the client successfully establishing a connection to a server.
- p2_client_server_terminal_indexhtml.png: Displays an image of the client successfully receiving index.html from the server.
- p2_client_server_connection.png: Displays an image of the server and client successfully working via two terminals on the UWF SSH server.
- p2_server_browser_404.png: Displays an image of the HTTP server and client (working as a browser) successfully, but not being able to render a fake html page.
- p2_server_browser_dragon.png: Displays an image of the HTTP server and client (working as a browser) successfully and rendering testPresence.html with the img.jpg image of a dragon.
- p2_server_browser_index.png: Displays an image of the HTTP server and client (working as a browser) successfully and rendering index.html.

## Notes for Grader
This project was developed utilizing WSL, however it has been tested on the UWF SSH Server and works there too. It is up to you whether you want to grade my project using WSL or the UWF SSH Server. Just make sure port 60001 is available to be opened on your machine!

## Compilation and Running
1. **Ensure that port 60001 is available to be opened**

2. **Navigate into the projects root directory**

3. **Compile the program:**
- You can compile both the http server and http client together by running the following command: 
```bash
    make
```
- Alternatively, you can compile the http server and http client seperately by running the following commands:
```bash
    make httpServer
```
```bash
    make httpClient
```

4. **Run the program**
- To run the server:
```bash
    ./httpServer
```
- To run the client:
```bash
    ./httpClient
```

5. **Client Notes**

Once the client begins running, you will be prompted with two questions. The first question will ask you what server IP address you want to connect your client too. The second question will ask you what file you want to "GET" from the server. See the following section, Usage, for more information with testing and running this project!

## Usage
There are a couple options when one wants to view how the HTTP methods are sent and received between the server and the client.

**Option 1**
1) Open two terminals (one terminal will be for the server, the other terminal will be for the client)
2) Compile and run the server in one of the terminals (see instructions above for compilation and running).
3) Compile and run the client in the other terminal (see instructions above for compilation and running).
4) Once the client is running, you will be prompted in the client side terminal asking "What is the address of the HTTP Server that you want to connect to?"
5) Simply type in the IP address that you want the client to connect to (e.g., '127.0.0.1').
6) Once the connection has been established between the client and server, you will be prompted with a question in the client side terminal asking "What file do you want?"
7) Simply type in the name of the file you want to request from the server (note that the file you request must be located in the root directory of this project) and press enter.
8) You will see outputs of information on both the server and client window.

**Option 2**
1) Open a terminal.
2) Compile and run the server (see instructions above for compilation and running).
3) Open a web browser and go to the local host webpage on port 60001 and enter the file you want to view in the web browser (note that the file you request must be located in the root directory of this project).
Example: Open a web browser and go to 'http://localhost:60001/index.html'

