// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    /******************************************************/
    valread = read( new_socket , buffer, 1024);
    // char vectorString = buffer;
    printf("The received vectors are: %s\n",buffer );
    doCirculant(buffer);
    send(new_socket , hello, strlen(hello) , 0 );
    printf("Hello message sent\n");
    
    return 0;
}
/*CIRCULANT FUNCTION*/

void doCirculant(char vectorStr[]){

    /*Obtain individual elements from string*/
    int yourVector[100];
    int counter = 0; 
    for (char *p = strtok(vectorStr, ","); p != NULL; p = strtok(NULL, ",")){
        yourVector[counter] = atoi(p); //String to Array
        counter++;
    }
    
    /*Final value of counter => n 
    /*How many elements are in the array*/ 
    /*Slice vectorElements array to avoid NULL value*/
    int vectorElementsSlice[counter];

    for(int i = 0; i < counter; i++) {
        vectorElementsSlice[i] = yourVector[i];
    }

    /*n by n matrix*/
    /*i by j matrix*/
    int mat[counter][counter];

    
    for(int i = 0; i < counter; i ++){
        for(int j = 0; j < counter; j++){
            mat[i][j] = vectorElementsSlice[j];
        }
        /*Shift elements right after every row*/
        shiftElementsRight(vectorElementsSlice, counter);
    }

    // return mat;/*An (n * n) matrix*/ 

    puts("Cirulant Done");

    for(int i = 0; i < counter; i++){

        for(int j = 0; j < counter; j++){
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }    

}

void shiftElementsRight(int x[],int len){
    int placeholder = x[len - 1]; /*The last element*/
    /*This creates an empty slot at the last element*/
    /*Start shifting from second last element*/
    for(int i = 0;i <= len; i++){
        x[len - i] = x[len- (i+1)];
    }
    /*Move element to the beginning*/
    x[0] = placeholder;
}
