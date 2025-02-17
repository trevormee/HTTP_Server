/***************************************************************
  Student Name: Trevor Mee
  File Name: httpClient.cpp
  Date: 02/15/2025
  Project 2
  COP4635 - Systems & Networks 2

  @brief Simple HTTP client that uses TCP sockets to generate 
         GET requests
***************************************************************/

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

const int SERVER_PORT = 60001;

/*
    @brief sends http requests to server and processes server responses

    @param client_fd: file descriptor of the client
    @param fileRequest: file being requested by the client

    @return N/A
*/
void handleRequests(int client_fd, std::string fileRequested)
{
    char buffer[4096] = {0};

    // send http request
    std::string request = "GET /" + fileRequested + " HTTP/1.1\r\nHost: localhost\r\n\r\n";
    ssize_t bytesSent = send(client_fd, request.c_str(), request.length(), 0);
    if(bytesSent < 0)
    {
        perror("FAILED: Could not send your request to the server");
        close(client_fd);
        return;
    }

    std::cout << "Request sent successfully!\n" << request << std::endl;

    // receive server response
    ssize_t bytesRead = read(client_fd, buffer, sizeof(buffer) - 1);
    if(bytesRead < 0)
    {
        perror("FAILED: Error receving response from server");
        return;
    }else
    {
        buffer[bytesRead] = '\0';
        std::cout << "Response from server received successfully!\n" << buffer << std::endl;
    }
}

/*
    @brief sends http requests to server and processes server responses

    @param client_fd: file descriptor of the client
    @param fileRequest: file being requested by the client

    @return N/A
*/
void handleRequests(int client_fd, std::string fileRequested, const char* serverAddr)
{
    char buffer[4096] = {0};

    // send http request
    //std::string request = "GET /" + fileRequested + " HTTP/1.1\r\nHost: localhost\r\n\r\n";
    std::string request = "GET /" + fileRequested + " HTTP/1.1\r\nHost: " + serverAddr + "\r\n\r\n";
    ssize_t bytesSent = send(client_fd, request.c_str(), request.length(), 0);
    if(bytesSent < 0)
    {
        perror("FAILED: Could not send your request to the server");
        close(client_fd);
        return;
    }

    std::cout << "Request sent successfully!\n" << request << std::endl;

    // receive server response
    ssize_t bytesRead = read(client_fd, buffer, sizeof(buffer) - 1);
    if(bytesRead < 0)
    {
        perror("FAILED: Error receving response from server");
        return;
    }else
    {
        buffer[bytesRead] = '\0';
        std::cout << "Response from server received successfully!\n" << buffer << std::endl;
    }
}


/*
    @brief main function

    @param N/A

    @return 0 on success
*/
int main()
{
    int client_fd;

    // create the client socket
    if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("FAILED to create client socket. Exiting...");
        exit(EXIT_FAILURE);
    }

    std::cout << "Client socket created successfully!" << std::endl;

    // prompt the user for the server address
    std::string serverAddr;
    std::cout << "\nWhat is the IP address of the HTTP Server that you want to connect to?" << std::endl;
    std::cin >> serverAddr;

    // define server address
    const char* cstrServerAddr = serverAddr.c_str();
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    
    if((inet_pton(AF_INET, cstrServerAddr, &server_address.sin_addr)) < 0)
    {
        perror("ERROR: Invalid IP Address. Closing client and exiting...");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // connect to the server
    if(connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0 )
    {
        perror("FAILED to connect client. Exiting...");
        exit(EXIT_FAILURE);
    }

    std::cout << "Client connected to server at " << cstrServerAddr << std::endl;

    // prompt the user for a requested file
    std::string fileName;
    std::cout << "\nWhat file do you want?" << std::endl;
    std::cin >> fileName;

    // send http requests and receive responses
    //handleRequests(client_fd, fileName);
    handleRequests(client_fd, fileName, cstrServerAddr);
    
    // close the client connection
    std::cout << "Closing the client" << std::endl;
    close(client_fd);    

    return 0;
}