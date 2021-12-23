#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_ADDRESS "/home/students/20200/m.bukhner/lab/31/lower_socket"

int main() {
	int sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("Socket open error");
		return 1;
	}

	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, SOCKET_ADDRESS);
	if (connect(sd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		perror("Socket connect error");
		return 1;
	}

	if (shutdown(sd, SHUT_RD) == -1)
		perror("Unable to disable socket reading.");

	char *str = "i dont't like CAPSLOCK!!!";
	write(sd, str, strlen(str));
	close(sd);
	return 0;
}
