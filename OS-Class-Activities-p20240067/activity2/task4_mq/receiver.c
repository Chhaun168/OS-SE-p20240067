#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include "common.h"

int main() {
    mqd_t mq;
    char buffer[MAX_SIZE];

    mq = mq_open(QUEUE_NAME, O_RDONLY);

    mq_receive(mq, buffer, MAX_SIZE, NULL);

    printf("Received: %s\n", buffer);

    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}
