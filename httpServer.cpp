#include <stdio.h>          
#include <stdlib.h>         
#include <sys/socket.h>     
#include <sys/types.h>      
#include <netinet/in.h>    
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>

const int PORT = 60001;

void handleClient(int client_fd)
{
    char buffer[4096] = {0};

    // read request from client
    ssize_t bytesRead = read(client_fd, buffer, sizeof(buffer));
    if(bytesRead < 0)
    {
        perror("Error reading from socket");
        return;
    }
    std::cout << "Received request: " << buffer << std::endl;

    // parse the http request
    std::istringstream request(buffer);
    std::string method, path, version;
    request >> method >> path >> version;
    std::string response;
    
    if(method == "GET")
    {
        std::ifstream file("." + path);
        std::cout << "path: " << path << std::endl;

        if (file) {

            std::ostringstream content;
            
            content << file.rdbuf();

            std::string contentType = "text/html"; // Default content type

            response = "HTTP/1.1 200 OK\r\nContent-Type: "+ contentType + "\r\n\r\n" + content.str();
            
        } else {
            std::string error_message = "<html><body><h1>404 Not Found</h1></body></html>";
            response = "HTTP/1.1 404 Not Found\r\n";
            response += "Content-Type: text/html\r\n";
            response += "Content-Length: " + std::to_string(error_message.size()) + "\r\n";
            response += "\r\n";
            response += error_message;
        }

    }
    else
    {
        // handle other methods
        response = "HTTP/1.1 404 Not found\r\n\r\n";
    }

    write(client_fd, response.c_str(), response.size());
    
}


int main()
{
    int server_fd;
    
    // create the server socket
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }   

    // define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket
    if(bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port: " << PORT << std::endl;

    // listen for connections
    if(listen(server_fd, 5) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server waiting for connection..." << std::endl;

    while(true)
    {
        int client_fd;

        // accept a connection
        if((client_fd = accept(server_fd, NULL, NULL)) < 0)
        {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        std::cout << "Connection established with client" << std::endl;

        // handle client request
        handleClient(client_fd);

        // close the client socket
        close(client_fd);
    }

    // close the server socket
    close(server_fd);

    return 0;
}