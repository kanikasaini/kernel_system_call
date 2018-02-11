#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

int main()
{
	int my_pid;
	char filename[100];
	printf("Enter PID: ");
	scanf("%d", &my_pid);
	printf("\nEnter file name: ");
	scanf("%s", filename);
	syscall(314, my_pid, filename);	
	perror("testing");
	return 0;
}
