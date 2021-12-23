#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>
#include <unistd.h>

#define SOCKET_ADDRESS "/home/students/20200/m.bukhner/lab/31/lower_socket"
#define MAX_ACTIVE_CLIENTS 100

struct pollfd fds[MAX_ACTIVE_CLIENTS];

int main() {
	int sd = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0);
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

	int listen_status = listen(sd, MAX_ACTIVE_CLIENTS);
	if (listen_status == -1) {
		perror("Listen error");
		return 1;
	}

	for (int i = 0; i < MAX_ACTIVE_CLIENTS; i++) {
		fds[i].fd = -1;
		fds[i].events = POLLIN;
	}

	int active_clients = 0;
	char buf[BUFSIZ + 1];
	while (1) {
		int client_sd = accept(sd, NULL, NULL);
		// printf("SD: %d, active_clients: %d\n", client_sd, active_clients);
		if (client_sd > -1) {
			if (active_clients >= MAX_ACTIVE_CLIENTS) {
				fprintf(stderr, "Server overloaded");
			}
			for (int i = 0; i < MAX_ACTIVE_CLIENTS; i++) {
				if (fds[i].fd == -1) {
					fds[i].fd = client_sd;
					active_clients++;
					break;
				}
			}
		}

		poll(fds, MAX_ACTIVE_CLIENTS, 1);

		int count;
		for (int i = 0; i < MAX_ACTIVE_CLIENTS; i++) {
			if (fds[i].fd > 0 && fds[i].revents & POLLIN) {
				count = read(fds[i].fd, buf, sizeof(buf));
				if (count <= 0 && fds[i].revents & POLLHUP) {
					close(fds[i].fd);
					fds[i].fd = -1;
					active_clients--;
				} else {
					for (int i = 0; i < count; i++) {
						buf[i] = toupper(buf[i]);
					}
					buf[count] = '\0';
					puts(buf);
					// write(0, buf, count);
				}
			}
		}

	}

	close(sd);
	return 0;
}

