// Lab 5 - exercise 3 & 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFF_SIZE 1024
#define MAX_PIPE 8
#define MAX_ARGS 128
#define ARG_DELIMS " \t\r\n"





void checkStreamRedirect (char *input, char **redirect) {
    static char* inputCopy;

    redirect[0] = NULL;
    redirect[1] = NULL;

    inputCopy = input;
    char* cmd = strtok(inputCopy, "<");
    char* redirectFile = strtok(NULL, "<");
    if (redirectFile != NULL) {
        redirect[0] = "<";
        redirect[1] = redirectFile + 1;

        input = strtok(input, "<");
        return;
    }

    inputCopy = input;
    cmd = strtok(inputCopy, ">");
    redirectFile = strtok(NULL, ">");
    if (redirectFile != NULL) {
        redirect[0] = ">";
        redirect[1] = redirectFile + 1;

        input = strtok(input, ">");

        if (strcmp(&cmd[strlen(cmd) - 1], "2") == 0) {
            redirect[0] = "2>";
                
            input = strtok(input, "2>");
            return;
        }
        return;
    }

    return;
}



int getArgs (char *input, char **args, char delims[]) {
    int flag = 0;

    // Split the input to args
    char* arg = strtok(input, delims);
    int n_args = 0;
    while (arg != NULL) {
        args[n_args++] = arg;
        arg = strtok(NULL, delims);
    }
    args[n_args] = NULL;

    if (n_args > 0 && strcmp(args[n_args - 1], "&") == 0) {
        flag = 2; // background flag
        args[n_args - 1] = NULL;
    }

    return flag;
}



int processInput (char *input, char **args, char **pipeArgs[]) {
    char **pipeInput = (char**)malloc(MAX_PIPE * sizeof(char*));

    getArgs(input, pipeInput, "|");
    if (pipeInput[1] == NULL) {
        free(pipeInput);
        return getArgs(input, args, ARG_DELIMS);
    }
    
    int flag = 1; // pipe flag
    int n_pipe = 0;
    while (n_pipe < MAX_PIPE - 1 && pipeInput[n_pipe] != NULL) {
        getArgs(pipeInput[n_pipe], pipeArgs[n_pipe], ARG_DELIMS);
        n_pipe++;
    }
    flag += getArgs(pipeInput[n_pipe - 1], pipeArgs[n_pipe - 1], ARG_DELIMS);

    free(pipeInput);
    return flag;
}



void cd (char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to 'cd'\n");
    }
    else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }
}



void execCmd(char** args, int background, char *redirect[]) {
    if (args[0] == NULL) {
        // Empty input
        return;
    } 
    else if (strcmp(args[0], "cd") == 0) {
        cd(args);
        return;
    } 
    else if (strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    }
    else {
        pid_t pid;
        int status;

        pid = fork(); // Creating a child process

        if (pid == 0) {
            // Redirecting std int, out, err streams
            if (redirect[0] != NULL && redirect[1] != NULL) {
                int file;
                if (strcmp(redirect[0], "<") == 0) {
                    printf("Redirectding stdin\n");
                    file = open(redirect[1], O_RDONLY);
                    dup2(file, STDIN_FILENO);
                    close(file);
                }
                else if (strcmp(redirect[0], ">") == 0) {
                    // 0777 - file permissions when creating the file (in octal)
                    file = open(redirect[1], O_WRONLY | O_APPEND | O_CREAT, 0777);
                    dup2(file, STDOUT_FILENO);
                    close(file);
                }
                else if (strcmp(redirect[0], "2>") == 0) {
                    // 0777 - file permissions when creating the file (in octal)
                    file = open(redirect[1], O_WRONLY | O_APPEND | O_CREAT, 0777);
                    dup2(file, STDERR_FILENO);
                    close(file);
                }
            }

            // executing the child process
            if (execvp(args[0], args) == -1) {
                perror("lsh");
            }
            exit(EXIT_FAILURE);
        } 
        else if (pid < 0) {
            // Fork error
            perror("lsh");
        } 
        else {
            // Parent process waiting for the child process to terminate (if the child process is not running in the background)
            if (!background) {
                int status;
                waitpid(pid, &status, 0);

                if (WIFEXITED(status)) {
                    if (WEXITSTATUS(status) != 0) {
                        fprintf(stderr, "lsh: child process exited with non-zero status\n");
                    }
                }
            }
        }
    }
}



void execPipe (char **pipeArgs1, char **pipeArgs2, char *redirect[]) {
    // 0 - read end, 1 - write end
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) < 0) {
        perror("pipe");
        return;
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        return;
    }

    if (pid1 == 0) {
        // Redirecting the output stream of the read end to the input stream of the write end
        dup2(pipefd[1], STDOUT_FILENO);

        // Redirecting std in stream
        int file;
        if (redirect[0] != NULL && redirect[1] != NULL) {
            if (strcmp(redirect[0], "<") == 0) {
                file = open(redirect[1], O_RDONLY);
                dup2(file, STDIN_FILENO);
                close(file);
            }
        }
        else if (strcmp(redirect[0], "2>") == 0) {
            // 0777 - file permissions when creating the file (in octal)
            file = open(redirect[1], O_WRONLY | O_APPEND | O_CREAT, 0777);
            dup2(file, STDERR_FILENO);
            close(file);
        }

        close(pipefd[0]);
        close(pipefd[1]);

        if (execvp(pipeArgs1[0], pipeArgs1) < 0) {
            perror("execvp");
            return;
        }
    } 
    

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        return;
    }

    if (pid2 == 0) {
        // Redirecting the output stream of the read end to the input stream of the write end
        dup2(pipefd[0], STDIN_FILENO);

        // Redirecting std out, err streams
        if (redirect[0] != NULL && redirect[1] != NULL) {
            int file;
            if (strcmp(redirect[0], ">") == 0) {
                // 0777 - file permissions when creating the file (in octal)
                file = open(redirect[1], O_WRONLY | O_APPEND | O_CREAT, 0777);
                dup2(file, STDOUT_FILENO);
                close(file);
            }
            else if (strcmp(redirect[0], "2>") == 0) {
                // 0777 - file permissions when creating the file (in octal)
                file = open(redirect[1], O_WRONLY | O_APPEND | O_CREAT, 0777);
                dup2(file, STDERR_FILENO);
                close(file);
            }
        }

        close(pipefd[0]);
        close(pipefd[1]);

        if (execvp(pipeArgs2[0], pipeArgs2) < 0) {
            perror("execvp");
            return;
        }
    } 

    close(pipefd[0]);
    close(pipefd[1]);

    // WIFEXITED - This macro queries the child termination status provided by the wait and waitpid functions, and determines whether the child process ended normally
    // WEXITSTATUS - This macro queries the child termination status provided by the wait and waitpid functions. If the WIFEXITED macro indicates that the child process exited normally, the WEXITSTATUS macro returns the exit code specified by the child process

    int status1;
    waitpid(pid1, &status1, 0);
    if (WIFEXITED(status1)) {
        if (WEXITSTATUS(status1) != 0) {
            fprintf(stderr, "lsh: child process exited with non-zero status\n");
        }
    }

    int status2;
    waitpid(pid2, &status2, 0);
    if (WIFEXITED(status2)) {
        if (WEXITSTATUS(status2) != 0) {
            fprintf(stderr, "lsh: child process exited with non-zero status\n");
        }
    }
}





int main(int argc, char** argv) {
    char cwd[BUFF_SIZE];
    char *input = (char*)malloc(BUFF_SIZE * sizeof(char));
    char **args = (char**)malloc(MAX_ARGS * sizeof(char*));
    char **pipeArgs[2];
    char **redirect = (char**)malloc(2 * sizeof(char*));

    // flags:
    // 0 - no flags
    // 1 - pipe
    // 2 - background
    // 3 - pipe + background
    int flag = 0;

    while (1) {
        // Print prompt and get input
        getcwd(cwd, sizeof(cwd));
        printf("lsh %s> ", cwd);
        if (fgets(input, BUFF_SIZE, stdin) == NULL) {
            exit(EXIT_SUCCESS);
        }

        checkStreamRedirect(input, redirect);
        flag = processInput(input, args, pipeArgs);

        // Execute commands
        switch (flag) {
            case 0: {
                execCmd(args, 0, redirect);
                break;
            }
            
            case 1: {
                execPipe(pipeArgs[0], pipeArgs[1], redirect);
                break;
            }

            case 2: {
                execCmd(args, 1, redirect);
                break;
            }

            case 3: {
                execPipe(pipeArgs[0], pipeArgs[1], redirect);
                break;
            }

            default: {
                printf("Input: sth went wrong!");
                break;
            }
        }
    }

    free(input);
    free(args);
    free(pipeArgs[0]);
    free(pipeArgs[1]);

    return 0;
}