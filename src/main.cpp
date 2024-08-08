#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>

int portCal(char *name)
{
	int portNumber = 0;
	int port;
	
	switch( name[1] )
	{
		case 'a':
		case 'A':
			portNumber += 32*0;
			break;
			
		case 'b':
		case 'B':
			portNumber += 32*1;
			break;
			
		case 'c':
		case 'C':
			portNumber += 32*2;
			break;
			
		case 'd':
		case 'D':
			portNumber += 32*3;
			break;
			
		default:
			printf("Unsupported port: %s\r\n", name);
			return -1;
			break;
	}
	
	for(int i=2; i<strlen(name); i++)
	{
		if( !isdigit(name[i]) )
		{
			printf("incorrect port number (%d)\r\n", name+2);
			return -1;
		}
	}
	
	portNumber += atoi(name+2);
	
	return portNumber;
}

int portNameTrim(char *name, int portNumber)
{
	char portGroup;
	int tmp;
	
	tmp = portNumber % 32;
	portGroup = (char)('A' + portNumber / 32);
	
	sprintf(name, "P%c%d", portGroup, tmp);
	
	return 0;
}

int main(int argc, char **argv)
{
	bool KeepGoing = true;
	int portNumber;
	char portName[32];
	int fd;
	char buf[128];
	
	if( argc != 2 )
	{
		printf("USAGE: gpio_sys PORT_NAME\r\n");
		return -1;
	}
	
	portNumber = portCal(argv[1]);
	portNameTrim(portName, portNumber);
	
	// 1.
	sprintf(buf, "/sys/class/gpio/export");
	if( (fd = open(buf, O_WRONLY)) < 0 )
	{
		printf("ERROR: fail in open %s\r\n", buf);
		return -1;
	}
	
	sprintf(buf, "%d", portNumber);
	if( write(fd, buf, strlen(buf)) < 0 )
	{
		printf("ERROR: fail in write\r\n");
		close(fd);
		return -1;
	}
	
	close(fd);
	//
	
	// 2.
	sprintf(buf, "/sys/class/gpio/%s/direction", portName);
	if( (fd = open(buf, O_WRONLY)) < 0 )
	{
		printf("ERROR: fail in open %s\r\n", buf);
		return -1;
	}
	
	sprintf(buf, "out");
	if( write(fd, buf, strlen(buf)) < 0 )
	{
		printf("ERROR: fail in write\r\n");
		close(fd);
		return -1;
	}
	
	close(fd);
	//
	
	// 3.
	sprintf(buf, "/sys/class/gpio/P%s/value", "B2");
	if( (fd = open(buf, O_WRONLY)) < 0 )
	{
		printf("ERROR: fail in open %s\r\n", buf);
		return -1;
	}
	
	while (KeepGoing)
	{
		sprintf(buf, "1");
		if( write(fd, buf, strlen(buf)) < 0 )
		{
			printf("ERROR: fail in write\r\n");
			close(fd);
			return -1;
		}	
		usleep(500*1000);
		
		sprintf(buf, "0");
		if( write(fd, buf, strlen(buf)) < 0 )
		{
			printf("ERROR: fail in write\r\n");
			close(fd);
			return -1;
		}	
		usleep(500*1000);
	}

	close(fd);
	
	// 4.
	sprintf(buf, "/sys/class/gpio/unexport");
	if( (fd = open(buf, O_WRONLY)) < 0 )
	{
		printf("ERROR: fail in open %s\r\n", buf);
		return -1;
	}
	
	sprintf(buf, "%d", portNumber);
	if( write(fd, buf, strlen(buf)) < 0 )
	{
		printf("ERROR: fail in write\r\n");
		close(fd);
		return -1;
	}
	
	close(fd);
	//
	
	return 0;
}

// end of file

