
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib>		// For exit() and EXIT_FAILURE
#include <iostream>		// For cout
#include <unistd.h>		// For read
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <thread>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <bits/stdc++.h>
extern "C"
{
#include <wiringPi.h>
}
#include <csignal>

using namespace std;

bool isNumber(const string &str) // this function is checking if the particular
{								 // character in a string is a number
	for (char const &c : str)
	{
		if (std::isdigit(c) == 0)
			return false;
	}
	return true;
}

void turn_on_or_off_led(string command, bool todo); // declaring function to turn on or off the led
void blinkLed(string command);						// declaring function to blink the led

int main()
{

	int sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create a socket (IPv4, TCP)
	if (sockfd == -1)
	{
		cout << "Failed to create socket. errno: " << errno << endl;
		exit(EXIT_FAILURE);
	}
	cout << "Socket is created" << endl;
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(8545); // the port address
	if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
	{
		cout << "Failed to bind to port 8545. errno: " << errno << endl;
		exit(EXIT_FAILURE);
	}

	// Start listening. Hold at most 10 connections in the queue
	if (listen(sockfd, 10) < 0)
	{
		cout << "Failed to listen on socket. errno: " << errno << endl;
		exit(EXIT_FAILURE);
	}

	// Grab a connection from the queue
	auto addrlen = sizeof(sockaddr);
	int connection = accept(sockfd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);
	if (connection < 0)
	{
		cout << "Failed to grab connection. errno: " << errno << endl;
		exit(EXIT_FAILURE);
	}
	cout << "Accepting connection from a client!" << endl;

	cout << "waiting for messages from the connected client" << endl;
	char buffer[4048];

	while (1)
	{

		bzero(buffer, 4048); // clear the buffer

		// Read input messages from the connection
		int n = read(connection, buffer, 4048);
		if (n < 0)
		{
			break;
		}
		string message(buffer);
		if (message.compare("#") == 0)
			continue;

		//**** Start Designing your program from this point *****

		// Step1: you received the following character array
		// the received message is in string message;
		cout << "The message was: " << message << endl;

		// Step2: parse/understand the message
		// this step requires using C++ String functions to extract what is required from the message
		string a = "string";
		int pin = 0;
		string word{"string"};

		a = message; // copying the message from client to 'a', so that we dont change the original message.

		bool todo;
		stringstream ss(a); // A stringstream associates a string object with a stream allowing you to read from the string as if it were a stream (like cin).
							//  The stringstream class is extremely useful in parsing input.

		while (ss >> word)
		{
			if (word == "on") // if the message from client contains word 'on' then we go to turn on or off function
			{
				todo = true;
				turn_on_or_off_led(a, todo);
			}
			if (word == "off") //	//if the message from client contains word 'off' then we go to turn on or off function
			{
				todo = false;
				turn_on_or_off_led(a, todo);
			}
			if (word == "Blink") //	//if the message from client contains word 'blink' then we go to blink function
			{
				blinkLed(a);
			}
		}

		// Step4: build a reply message, for example:
		string response;
		response = "next message\n";

		// Step5 (no need to change): Send a message to the connected client
		send(connection, response.c_str(), response.size(), 0);
	}

	// Close the connections and close the socket
	cout << "closing the connection" << endl;
	close(connection);
	close(sockfd);
}

void turn_on_or_off_led(string command, bool todo)
{

	// Step3: perform the required function
	// call the required hardware function (e.g., turn on led)
	wiringPiSetupGpio(); // initialize wiringPi

	int red = 17, yellow = 22, green = 6;
	string word = "string";
	stringstream ss(command);
	int pin;

	pinMode(red, OUTPUT);	 // set up the mode of pin 17
	pinMode(yellow, OUTPUT); // set up the mode of pin 22
	pinMode(green, OUTPUT);	 // set up the mode of pin 6

	while (ss >> word)
	{
		if (isNumber(word)) // function will return true if there is a number in a string
		{
			pin = stoi(word);
		}
		int red = pin;

		if (todo)
		{
			digitalWrite(red, HIGH); // turn on the LED connected on pin 17
		}

		else
		{
			digitalWrite(red, LOW); // turn off the LED connected on pin 17
		}
	}
}

void blinkLed(string command)
{
	wiringPiSetupGpio(); // initialize wiringPi

	int red = 17, yellow = 22, green = 6;
	string word = "string";
	stringstream ss(command);
	int pin = 0, secs = 0;

	pinMode(red, OUTPUT);	 // set up the mode of pin 17
	pinMode(yellow, OUTPUT); // set up the mode of pin 22
	pinMode(green, OUTPUT);	 // set up the mode of pin 6

	while (ss >> word)
	{
		if (isNumber(word)) // function will return true if there is a number in a string
		{
			if (pin != 0)
			{
				secs = stoi(word); // the second number in a string will be assigned to 'secs'(seconds).
				break;
			}
			pin = stoi(word); // the first number in a string will be assigned to 'pin'
		}
	}
	red = pin;

	for (int i = 0; i <= secs; i++) // loop to blink the LED.
	{

		int red = pin;
		digitalWrite(red, HIGH); // turn on the LED connected on pin
		delay(500);				 // wait for 0.5 second
		digitalWrite(red, LOW);	 // turn off the LED connected on pin
		delay(500);				 // wait for 0.5 second
	}
}
