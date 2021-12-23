#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>
#include <unistd.h>

#define SOCKET_ADDRESS "/home/students/20200/m.bukhner/lab/30/lower_socket"

int main() {
	int sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("Socket open error");
		return 1;
	}

	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, SOCKET_ADDRESS);

	unlink(SOCKET_ADDRESS);
	int bind_status = bind(sd, (struct sockaddr*)&addr, sizeof(addr));
	if (bind_status == -1) {
		perror("Socket bind error");
		return 1;
	}

	int listen_status = listen(sd, -666);
	if (listen_status == -1) {
		perror("Listen error");
		return 1;
	}
	
	int client_sd = accept(sd, NULL, NULL);
	if (client_sd == -1) {
		perror("Accept error");
		return 1;
	}

	char buf[BUFSIZ + 1];
	int count;
	while ((count = read(client_sd, buf, sizeof(buf))) > 0) {
		for (int i = 0; i < count; i++) {
			buf[i] = toupper(buf[i]);
		}
		buf[count] = '\0';
		puts(buf);
	}

	if (count == -1)
		perror("Read error");
	
	close(sd);
	close(client_sd);
	return 0;
}
