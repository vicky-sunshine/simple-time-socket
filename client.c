/*
 * Simple Time Client For 2016 Introduction to Computer Network
 * Author: vicky-sunshine @ HSNL-TAs
 * 2016/09
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  /* contains a number of basic derived types */
#include <sys/socket.h> /* provide functions and data structures of socket */
#include <arpa/inet.h>  /* convert internet address and dotted-decimal notation */
#include <netinet/in.h> /* provide constants and structures needed for internet domain addresses*/
#include <unistd.h>     /* `read()` and `write()` functions */
#include <time.h>       /* provide functions about time */

#define MAX_SIZE 2048


int main (int argc , char **argv) {
  int cli_fd;
  struct sockaddr_in svr_addr;
  int byte_num;
  char buf[MAX_SIZE];

  /* 1) Create the socket, use `socket()`
        AF_INET: IPv4
        SOCK_STREAM: Stream Socket (TCP)
  */
  cli_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (cli_fd < 0) {
    perror("Create socket failed.");
    exit(1);
  }

  /* 2) Bind the socket to port, with prepared sockaddr_in structure */
  bzero(&svr_addr, sizeof(svr_addr));
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  svr_addr.sin_port = htons(8888);

  /* 3) Connect to a given port on the server address*/
  if (connect(cli_fd, (struct sockaddr *)&svr_addr, sizeof(svr_addr)) < 0) {
    perror("Connect failed");
    exit(1);
  }

  printf("Connected\n");

  /* Handle message, read current from the server */
  byte_num = read(cli_fd, buf, sizeof(buf));
  if (byte_num < 0) {
    perror("Read failed");
    exit(1);
  }
  buf[byte_num] = '\0';

  printf("Get bytes length: %d\n", byte_num);
  printf("Server datetimes: %s\r\n", buf);
  close(cli_fd);

  return 0;
}
