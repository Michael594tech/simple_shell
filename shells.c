#include "shell.h"

int our_strcmp(const char *string1, const char *string2);
void signal_handler(int signal);
size_t our_strlen(const char *str);
char *our_strdup(const char *str);
char *our_strcat(char *final_str, char *str_to);
char *our_strcpy(char *dest, char *src);
ssize_t our_getline(char **line, size_t *len, FILE *stream);

/**
 * main - Custom shell program
 * @ac: Argument count
 * @av: Argument vector
 *
 * Description:
 * This program serves as a custom shell that allows users to input commands,
 * tokenizes them into smaller strings, and executes them. If the program
 * name is a path, it directly executes the command. If not, it searches
 * through directories in the PATH environment variable to find and execute
 * the desired program.
 *
 * Return:
 * Always returns 0.
 */

int main(int ac, char **av)
{
	/* Initialization and variable declarations */
	char *prompt = "$ ";
	ssize_t characters_read = 0;
	ssize_t prompt_bytes_written = 0;
	char *line = NULL;
	size_t len = 0;
	size_t i = 0;
	size_t free_dir_i = 0;
	const char *delimiters = NULL;
	char *command_token = NULL;
	char **command = NULL;
	size_t max_command = 0;
	int child_pid = 0;
	int status = 0;
	char *path_env_var = NULL;
	int slash_i = 0;
	char *path = NULL;
	size_t max_directories = 0;
	char **directories = NULL;
	char *directories_token = NULL;
	size_t directories_i = 0;
	DIR *directory_stream = NULL;
	size_t searching_i = 0;
	struct dirent *entry = NULL;
	char *concat_path = NULL;
	int found = 0;
	char *err_msg = NULL;
	size_t size = 0;
	(void)ac;

	/* Handle signals */
	signal(SIGINT, signal_handler);

	while (1)
	{
		/* Reset variables and prompt user for input */
		line = NULL;
		delimiters = " \n\t\r\a";
		path = NULL;

		if (isatty(STDIN_FILENO))
		{
			prompt_bytes_written = write(1, prompt, our_strlen(prompt));
			if (prompt_bytes_written == -1)
			{
				perror("write");
				exit(1);
			}
		}

		/* flushing stdout */
		fflush(stdout);

		characters_read = our_getline(&line, &len, stdin);
		if (characters_read == EOF)
		{
			break;
		}

		else if (characters_read == -1)
		{
			break;
		}

		/* Check for built-in commands 'exit' and 'env' */
		if (our_strcmp(line, "exit") == 0)
		{
			free(line);
			exit(0);
		}

		if (our_strcmp(line, "env") == 0)
		{
			int i = 0;

			for (; environ[i]; i++)
			{
				write(1, environ[i], our_strlen(environ[i]));
				write(1, "\n", 1);
			}
			free(line);
			continue;
		}

		/* Tokenize the command */
		command_token = strtok(line, delimiters);
		if (command_token == NULL)
		{
			free(line);
			continue;
		}

		max_command = 10;
		command = malloc(sizeof(char *) * max_command);
		i = 0;
		while (command_token != NULL)
		{
			if (i >= max_command)
			{
				max_command *= 2;
				command = realloc(command, sizeof(char *) * max_command);
				if (command == NULL)
				{
					perror("./hsh");
				}
			}

			command[i] = our_strdup(command_token);
			if (command[i] == NULL)
				continue;
			command_token = strtok(NULL, delimiters);
			i++;
		}
		command[i] = NULL;

		/* Check if the program name is a path */
		slash_i = 0;
		while (line[slash_i] != '\0')
		{
			if (line[slash_i] == '/')
			{
				path = line;
				break;
			}
			slash_i++;
		}

		/* If the program name is not a path */
		if (path == NULL)
		{
			char *PATH = getenv("PATH");

			if (PATH == NULL)
				continue;

			path_env_var = our_strdup(PATH);
			if (path_env_var == NULL)
				continue;

			directories_token = strtok(path_env_var, ":");
			if (directories_token == NULL)
			{
				perror("av[0]");/*PROGRAM NAME ./hsh*/
			}

			/* allcoating space for directories array */
			max_directories = 100;/*max_path = 4096*/
			directories = malloc(sizeof(char *) * max_directories);
			directories_i = 0;

			while (directories_token != NULL)
			{
				if (directories_i >= max_directories)
				{
					max_directories *= 2;
					directories = realloc(directories, sizeof(char *) * max_directories);
					if (directories == NULL)
					{
						perror("realloc");
					}
				}
				/*what if strdup fails?*/
				directories[directories_i] = our_strdup(directories_token);
				if (PATH == NULL)
					continue;
				directories_token = strtok(NULL, ":");
				directories_i++;
			}
			/* null terminate directories array */
			directories[directories_i] = NULL;

			/* opening all directories to look for line(e.g "ls") */
			searching_i = 0;
			while (directories[searching_i] != NULL)
			{
				directory_stream = opendir(directories[searching_i]);

				if (directory_stream == NULL)
				{
					searching_i++;
					continue;
				}

				found = 0;
				entry = readdir(directory_stream);
				while (entry != NULL)
				{
					if (our_strcmp(command[0], entry->d_name) == 0)
					{
						found = 1;
						break;
					}

					entry = readdir(directory_stream);
				}

				closedir(directory_stream);

				if (found == 1)
					break;

				searching_i++;
				if (searching_i == directories_i)
				{
					perror(command[0]);
				}
			}
		}
		/* Fork to create a new process (child) */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
		}
		else if (child_pid == 0)
		{
			if (path == NULL)
			{
				size = our_strlen(directories[searching_i]) + our_strlen(line) + 2;
				concat_path = malloc(size);
				if (concat_path == NULL)
				{
					perror("malloc");
				}
				our_strcpy(concat_path, directories[searching_i]);
				our_strcat(concat_path, "/");
				our_strcat(concat_path, command[0]);

				command[0] = concat_path;
				execve(command[0], command, environ);

				perror("execve");
				free(concat_path);
				free(command);
			}
			else
			{
				(void)av;
				(void)err_msg;
				execve(command[0], command, environ);

				perror("execve");
			}

		}

		wait(&status);

		if (path == NULL)
		{
			for (free_dir_i = 0; directories[free_dir_i] != NULL; free_dir_i++)
			{
				free(directories[free_dir_i]);
			}
		}

		for (i = 0; command[i] != NULL; i++)
		{
			free(command[i]);
		}

		free(directories);
		free(path_env_var);
		free(concat_path);
		free(command);
		free(line);
	}
	free(line);
	if (isatty(STDIN_FILENO) == 1)
		write(1, "\n", 1);
	return (0);
}
