#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include "path.h"

#define PROMPT "\x1b[32;1m>\x1b[0m "

void sig_handler(int) {  }

int main(int argc, char* argv[], char* envp[]) {

	
	signal(SIGINT, sig_handler);  // Do nothing if CRTL + C is pressed (if user wants to exit they can use the exit command)

	// Main loop
	while (true) {
		printf(PROMPT); // Display the prompt
		fflush(stdout); // Make sure prompt is visible before user input

		char* line = NULL;
		size_t size;
		ssize_t nread;
		nread = getline(&line, &size, stdin); // User input
		if (nread > 0 && line[nread - 1] == '\n') line[nread - 1] = '\0'; // Remove trailing newline

		char* cmd = NULL;
		char** args = NULL;

		// Converts "line" into a string array
		{
			int i = 0; // Counter
			char* token = strtok(line, " "); // Seperate "line" into the command and arguments
			while (token != NULL) {
				if (i == 0) cmd = token; // If it is the first word in "line" then set it to be the command
				char** tmp = realloc(args, ((i + 1) * sizeof(char*)) + strlen(token)); // Allocate more memory
				args = tmp; // Copy the temporary array to "args"
				args[i++] = token; // Add argument to "args"

				token = strtok(NULL, " ");
			}
			args[i] = NULL;
		}

		if (cmd != NULL) {
			// Exit command
			if (strcmp(cmd, "exit") == 0) {
				free(line);
				if (args != NULL) free(args);
				return 0;
			}

			if (access(cmd, F_OK) != 0) cmd = find_in_path(cmd);

			pid_t pid = fork(); // Creates a child process for the command
			if (pid == 0) // Child process
				execve(cmd, args, envp); // Execute the command
			else if (pid > 0) // Main process
				wait(NULL); // Wait for child process to finish execution
		}

		if (line != NULL) free(line);
		if (args != NULL) free(args);
	}
}
