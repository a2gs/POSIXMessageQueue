/* cc -o client client.c -lrt */

#include "comum.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <mqueue.h>

int main(){
	mqd_t queue;
	char msg[MSG_SIZE], text[TEXT_SIZE], *chr;
	struct mq_attr attr;
	unsigned int sz;

	if((queue =  mq_open(QUEUE_FILE, O_WRONLY|O_NONBLOCK, 0777, NULL)) == -1){
		printf("Erro mq_open(): %s\n", strerror(errno));
		return(1);
	}

	if(mq_getattr(queue, &attr) == -1){
	   printf("Erro mq_setattr(): %s\n", strerror(errno));
		return(1);
	}
	printf("CLIENT >>> Dados da queue: Flags[%ld] | MaxMsg[%ld] | MsgSize[%ld] | CurMsgs[%ld]\n",
	       attr.mq_flags,  attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

	do{
		memset(text, 0, TEXT_SIZE + 1);
		memset(msg, 0, MSG_SIZE + 1);

		fgets(text, TEXT_SIZE, stdin);
		chr = strrchr(text, '\n');
		if(chr != NULL) *chr = '\0';

		/* Protocolo */
		sz = strlen(text);
		sprintf(msg, "%0*d|%s", TEXTSIZE_SIZE, sz, text);

		printf("CLIENT >>> Enviando[%s] | Mensagem[%s] | Tamanho[%d]\n", msg, text, sz);

		if(mq_send(queue, msg, strlen(msg), 0) == -1){
			printf("Erro mq_send(): %s\n", strerror(errno));
			break;
		}

		if(strcmp(text, "exit") == 0) break;	
	}while(1);

	return(0);
}
