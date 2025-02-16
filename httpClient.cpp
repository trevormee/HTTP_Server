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

const char *SERVER_IP = "127.0.0.1"; // Localhost
const int SERVER_PORT = 60001;

/*
    @brief sends http requests to server and processes server responses

    @param client_fd: file descriptor of the client

    @return N/A
*/
void handleRequests(int client_fd)
{
    char buffer[4096] = {0};

    // send http request
    std::string request = "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    ssize_t bytesSent = send(client_fd, request.c_str(), request.length(), 0);
    if(bytesSent < 0)
    {
        perror("FAILED: Could not send your request to the server");
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
void handleRequests(int client_fd, std::string fileRequested)
{
    char buffer[4096] = {0};

    // send http request
    // std::string request = "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    std::string request = "GET /" + fileRequested + " HTTP/1.1\r\nHost: localhost\r\n\r\n";
    ssize_t bytesSent = send(client_fd, request.c_str(), request.length(), 0);
    if(bytesSent < 0)
    {
        perror("FAILED: Could not send your request to the server");
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

    // define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

    // connect to the server
    if(connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0 )
    {
        perror("FAILED to connect client. Exiting...");
        exit(EXIT_FAILURE);
    }

    std::cout << "Client connected to server at " << SERVER_IP << std::endl;
    
    std::string fileName;
    std::cout << "What file do you want?" << std::endl;
    std::cin >> fileName;

    // send http requests and receive responses
    //handleRequests(client_fd);
    handleRequests(client_fd, fileName);
    
    // BONUS
    /*
    int userChoice;
    std::cout << "\nSelect an option (1 or 2)" << std::endl;
    std::cout << "1. Get a file from server "<< std::endl;
    std::cout << "2. Send a text message to server" << std::endl;
    std::cin >> userChoice;

    if(userChoice == 1){
    std::string fileName;
    std::cout << "What file do you want?" << std::endl;
    std::cin >> fileName;

    // send http requests and receive responses
    //handleRequests(client_fd);
        handleRequests(client_fd, fileName);
    }else if (userChoice == 2)
    {
        std::string textMsg;    
        std::cout << "\n Enter your text message to send" << std::endl;
        std::cin >> textMsg; 
        sendText(client_fd, textMsg);
    }else{
        std::cerr << "Invalid choice. Must choose 1 or 2!"
    }
    */

    // close the client connection
    close(client_fd);    

    return 0;
}