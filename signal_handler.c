#include "shell.h"
size_t our_strlen(const char *str);
/**
 * signal_handler - Handle signals, specifically for Ctrl+C
 * @signal: The signal number
 *
 * Description:
 * This function serves as a signal handler for Ctrl+C. It prints a newline
 * and a new shell prompt after the signal is caught, effectively
 * preventing the shell from exiting when Ctrl+C is pressed.
 *
 * Return: Nothing (void)
 */
void signal_handler(int signal)
{
	char *prompt = "\n$ ";

	(void)signal;
	write(1, prompt, our_strlen(prompt));
	fflush(stdout);
}
