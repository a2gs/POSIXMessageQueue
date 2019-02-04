/* Andre Augusto Giannotti Scota (a2gs)                              
 * andre.scota@gmail.com
 *
 * A POSIX Message Queue server sample
 *
 * Public Domain
 *
 */

/* <file name>
 * <File description>
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 01/01/2005 | Creation
 *          |            |
 */

#include "comum.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <mqueue.h>

int main(int argc, char *argv[])
{
	mqd_t queue;
	char msg[MSG_SIZE + 1] = {0}, text[TEXT_SIZE + 1] = {0}, szStr[TEXTSIZE_SIZE + 1] = {0};
	unsigned int prio = 0;
	struct mq_attr attr;
	unsigned int sz = 0;

	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MSG_SIZE;

	if((queue =  mq_open(QUEUE_FILE, O_RDONLY|O_CREAT/*|O_NONBLOCK*/, 0777, &attr)) == -1){
	   printf("Erro mq_open(): %s\n", strerror(errno));
	   return(1);
	}

	do{
		memset(text, 0, TEXT_SIZE + 1);
		memset(msg, 0, MSG_SIZE + 1);

		if(mq_getattr(queue, &attr) == -1){
			printf("Erro mq_getattr(): %s\n", strerror(errno));
			break;
		}

		if(mq_receive(queue, msg, MSG_SIZE, &prio) == -1){
		   printf("Erro mq_receive(): %s\n", strerror(errno));
			break;
		}

		/* Protocolo */
		strncpy(szStr, msg, TEXTSIZE_SIZE);
		szStr[TEXTSIZE_SIZE] = '\0';
		sz = atoi(szStr);

		memcpy(text, msg + TEXTSIZE_SIZE + 1, sz);
		text[sz] = '\0';

		printf("SERVER >>> Recebeu[%s] | Mensagem[%s] | Tamanho[%d]\n", msg, text, sz);
		printf("SERVER >>> Dados da queue: Flags[%ld] | MaxMsg[%ld] | MsgSize[%ld] | CurMsgs[%ld]\n\n",
		       attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

		if(strcmp(text, "exit") == 0) break;
		else                          system(text);
	}while(1);

	mq_unlink(QUEUE_FILE);

	return(0);
}
