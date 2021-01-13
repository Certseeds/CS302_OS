/*
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-31 22:53:58
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-03-31 23:00:34
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/types.h>

struct waitqueue {            /* 双向的链表 double link list */
    struct waitqueue *next;    //下一个等待作业
    int count;       //当前等待作业的信息
};

int main() {
    struct waitqueue *head, *next, *s, *spre;
    head = (struct waitqueue *) malloc(sizeof(struct waitqueue));
    next = (struct waitqueue *) malloc(sizeof(struct waitqueue));
    s = NULL;
    spre = NULL;
    head->next = next;
    head->count = 1;
    next->next = NULL;
    next->count = 2;
    s = head;
    spre = head;
    head = NULL;
    if (s) {
        printf("1230");
    } else {
        printf("4560");
    }
}