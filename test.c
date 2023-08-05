#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
volatile sig_atomic_t  g_sig;

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    (void)sig;
}

int main()
{
    sigaction(SIGINT, & (struct sigaction) { .sa_handler = handler }, NULL);
    read(0, (char [2]){}, 2);
    perror("read");
}