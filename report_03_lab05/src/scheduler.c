#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include "job.h"

// TODO, only get 0 of 20 points.
// if you know why,plase create issues.
void pid_to_name(int pid, char *ret);

void pid_to_name_2(int pid, char *ret);

//#define DEBUG
int jobid = 0;
int siginfo = 1;
int fifo;
int globalfd;

struct waitqueue *head = NULL;
struct waitqueue *next = NULL;
struct waitqueue *current = NULL;

void schedule() {
    struct jobinfo *newjob = NULL;
    struct jobcmd cmd;
    int count = 0;

    bzero(&cmd, DATALEN);
    if ((count = read(fifo, &cmd, DATALEN)) < 0) {
        error_sys("read fifo failed");
    }

#ifdef DEBUG

    if (count) {
        printf("cmd cmdtype\t%d\n"
            "cmd defpri\t%d\n"
            "cmd data\t%s\n",
            cmd.type, cmd.defpri, cmd.data);
    }// else
     //	printf("no data read\n");

#endif
    switch (cmd.type) {
        case ENQ: {
            do_enq(newjob, cmd);
            break;
        }
        case DEQ: {
            do_deq(cmd);
            break;
        }
        case STAT: {
            do_stat(cmd);
            break;
        }
        default: {
            break;
        }
    }
    /* Update jobs in waitqueue */

    updateall();

    /* select the highest priority job to run */

    next = jobselect();

    /* stop current job, run next job */

    jobswitch();
}

int allocjid() {
    jobid += 1;
    return jobid;
}

void updateall() {
    struct waitqueue *p;

    /* update running job's run_time */
    if (current) {
        current->job->run_time += 100;
        current->job->curpri = current->job->defpri;
    }
    /* update ready job's wait_time */
    for (p = head; p != NULL; p = p->next) {
        p->job->wait_time += 100;
        p->job->curpri += 1;
        //*Find Bug 4.
    }
}

struct waitqueue *jobselect() {
    struct waitqueue *p, *prev, *select, *selectprev;
    int highest = -1;

    select = NULL;
    selectprev = NULL;
    if (head) {
        // 有元素
        if (head->next) {
            //多于一个元素
            for (prev = head, p = head; p != NULL; prev = p, p = p->next) {
                if (p->job->curpri > highest) {
                    select = p;
                    selectprev = prev;
                    highest = p->job->curpri;
                } else if (highest == p->job->curpri
                           && p->job->wait_time > select->job->wait_time) {
                    select = p;
                    selectprev = prev;
                }
            }
            //*Find Bug 3.
            if (selectprev == select) {
                struct waitqueue *temp = head->next;
                select = head;
                select->next = NULL;
                head = temp;
            } else {
                selectprev->next = select->next;
                select->next = NULL;
            }
        } else {
            //只有一个元素
            select = head;
            head = NULL;
        }
    }//没有元素 省去
    return select;
}

void jobswitch() {
    struct waitqueue *p;
    int i;

    if (current && current->job->state == DONE) {           /* current job finished */

        /* job has been done, remove it */
        for (i = 0; (current->job->cmdarg)[i] != NULL; i++) {
            free((current->job->cmdarg)[i]);
            (current->job->cmdarg)[i] = NULL;
        }

        free(current->job->cmdarg);
        free(current->job);
        free(current);

        current = NULL;
    }

    if (next == NULL && current == NULL) {          /* no job to run */
        return;
    } else if (next != NULL && current == NULL) {   /* start new job */

        printf("begin start new job\n");
        current = next;
        next = NULL;
        current->job->state = RUNNING;
        kill(current->job->pid, SIGCONT);
        return;

    } else if (next != NULL && current != NULL) { /* do switch */

        kill(current->job->pid, SIGSTOP);
        current->job->curpri = current->job->defpri;
        current->job->wait_time = 0;
        current->job->state = READY;

        /* move back to the queue */

        if (head) {
            for (p = head; p->next != NULL; p = p->next);
            p->next = current;
        } else {
            head = current;
        }
        // !FIND BUG,jobs was hidden .
        current = next;
        next = NULL;
        current->job->state = RUNNING;
        kill(current->job->pid, SIGCONT);

        //printf("\nbegin switch: current jid=%d, pid=%d\n",
        //		 current->job->jid, current->job->pid);
        return;

    } else {    /* next == NULL && current != NULL, no switch */
        return;
    }
}

void sig_handler(int sig, siginfo_t *info, void *notused) {
    int status;
    int ret;
    switch (sig) {
        case SIGVTALRM: {
            schedule();
            return;
        }
        case SIGCHLD: {
            ret = waitpid(-1, &status, WNOHANG);
            if (0 == ret || -1 == ret) {
                return;
            }
            if (WIFEXITED(status)) {
#ifdef DEBUG
                printf("%d %d %d\n", ret, info->si_pid, current->job->pid);
                //do_stat();
#endif
                current->job->state = DONE;
                printf("normal termation, exit status = %d\tjid = %d, pid = %d\n\n",
                       WEXITSTATUS(status), current->job->jid, current->job->pid);

            } else if (WIFSIGNALED(status)) {
                printf("abnormal termation, signal number = %d\tjid = %d, pid = %d\n\n",
                       WTERMSIG(status), current->job->jid, current->job->pid);

            } else if (WIFSTOPPED(status)) {
                printf("child stopped, signal number = %d\tjid = %d, pid = %d\n\n",
                       WSTOPSIG(status), current->job->jid, current->job->pid);
            }
            return;
        }
        default: {
            return;
        }
    }
}

//null,enqcmd is read from pipe.
void do_enq(struct jobinfo *newjob, struct jobcmd enqcmd) {
    struct waitqueue *newnode, *p;
    int i = 0, pid;
    char *offset, *argvec, *q;
    char **arglist;
    sigset_t zeromask;

    sigemptyset(&zeromask);

    /* fill jobinfo struct */

    newjob = (struct jobinfo *) malloc(sizeof(struct jobinfo));
    newjob->jid = allocjid();
    newjob->defpri = enqcmd.defpri;
    newjob->curpri = enqcmd.defpri;
    newjob->ownerid = enqcmd.owner;
    newjob->state = READY;
    newjob->create_time = time(NULL);
    newjob->wait_time = 0;
    newjob->run_time = 0;
    arglist = (char **) malloc(sizeof(char *) * (enqcmd.argnum + 1));
    newjob->cmdarg = arglist;
    offset = enqcmd.data;
    argvec = enqcmd.data;
    while (i < enqcmd.argnum) {

        if (*offset == ':') {

            *(offset++) = '\0';
            q = (char *) malloc(sizeof(char) * (offset - argvec));
            strcpy(q, argvec);
            arglist[i] = q;
            i++;
            argvec = offset;

        } else {
            offset++;
        }
    }

    arglist[i] = NULL;

#ifdef DEBUG

    printf("enqcmd argnum %d\n",enqcmd.argnum);
    for (i = 0; i < enqcmd.argnum; i++){
        printf("parse enqcmd:%s\n",arglist[i]);
    }
#endif

    /* add new job to the queue */

    newnode = (struct waitqueue *) malloc(sizeof(struct waitqueue));
    newnode->next = NULL;
    newnode->job = newjob;

    if (head) {//非空
        for (p = head; p->next != NULL; p = p->next);

        p->next = newnode;
    } else {
        head = newnode;
    }
    /* create process for the job */

    if ((pid = fork()) < 0) {
        error_sys("enq fork failed");
    }
    /* In child process */

    if (pid == 0) {

        newjob->pid = getpid();

        /* block the child wait for run */

        raise(SIGSTOP);

#ifdef DEBUG

        printf("begin running\n");
        for (i = 0; arglist[i] != NULL; i++){
            printf("arglist %s\n",arglist[i]);
        }
#endif

        /* dup the globalfile descriptor to stdout */
        dup2(globalfd, 1);
        // *UNREAL FIND BUG2
        if (execv(arglist[0], arglist) < 0) {
            printf("exec failed\n");
        }
        exit(1);

    } else {
        newjob->pid = pid;
        printf("\nnew job: jid=%d, pid=%d\n", newjob->jid, newjob->pid);

    }
}

void do_deq(struct jobcmd deqcmd) {
    int deqid, i;
    struct waitqueue *p, *prev, *select, *selectprev;

    deqid = atoi(deqcmd.data);
    if (deqid <= 0 || deqid > jobid) {
        return;
    }
#ifdef DEBUG
    printf("deq jid %d\n",deqid);
#endif

    /* current jodid == deqid, terminate current job */
    if (current && current->job->jid == deqid) {
        printf("terminate job: %d\n", current->job->jid);
        kill(SIGTERM, current->job->pid);

        for (i = 0; (current->job->cmdarg)[i] != NULL; i++) {

            free((current->job->cmdarg)[i]);
            (current->job->cmdarg)[i] = NULL;
        }

        free(current->job->cmdarg);
        free(current->job);
        free(current);

        current = NULL;

    } else {  /* maybe in waitqueue, search it */
        select = NULL;
        selectprev = NULL;

        if (head) {
            if (deqid == head->job->jid) {
                select = head;
                head = head->next;
            } else {
                for (prev = head, p = head; p != NULL; prev = p, p = p->next) {
                    if (p->job->jid == deqid) {
                        select = p;
                        selectprev = prev;
                        break;
                    }
                }
                if (selectprev && select) {
                    selectprev->next = select->next;
                }
            }
        }
        if (select) {
            select->next = NULL;
            for (i = 0; (select->job->cmdarg)[i] != NULL; i++) {
                free((select->job->cmdarg)[i]);
                (select->job->cmdarg)[i] = NULL;
            }

            free(select->job->cmdarg);
            free(select->job);
            free(select);

            select = NULL;
        }
    }
}

void do_stat() {
    /*
    * Print job statistics of all jobs:
    * 1. job id
    * 1_1. job NAME,
    * 1_2. job CUR_PRI
    * 1_3. job DEF_PRI
    * 2. job pid
    * 3. job owner
    * 4. job run time
    * 5. job wait time
    * 6. job create time
    * 7. job state
    */

    struct waitqueue *p;
    char timebuf[BUFLEN];
    char pid_names[1024];
    printf("JID\tPID\tNAME\t\tCUR_PRI\tDEF_PRI\tOWNER\tRUNTIME\tWAITTIME\tCREATTIME\t\tSTATE\n");
    if (current) {//指针非空
        memset(pid_names, '\0', sizeof(char) * 1024);
        pid_to_name_2(current->job->pid, pid_names);
        strcpy(timebuf, ctime(&(current->job->create_time)));
        timebuf[strlen(timebuf) - 1] = '\0';
        printf("%d\t%d\t%s\t%d\t%d\t%d\t%d\t%d\t%s\t%s\n",
               current->job->jid,
               current->job->pid,
               pid_names,
               current->job->curpri,
               current->job->defpri,
               current->job->ownerid,
               current->job->run_time,
               current->job->wait_time,
               timebuf,
               "RUNNING");
    }

    for (p = head; p != NULL; p = p->next) {
        memset(pid_names, '\0', sizeof(char) * 1024);
        pid_to_name_2(p->job->pid, pid_names);
        strcpy(timebuf, ctime(&(p->job->create_time)));
        timebuf[strlen(timebuf) - 1] = '\0';
        printf("%d\t%d\t%s\t%d\t%d\t%d\t%d\t%d\t%s\t%s\n",
               p->job->jid,
               p->job->pid,
               pid_names,
               p->job->curpri,
               p->job->defpri,
               p->job->ownerid,
               p->job->run_time,
               p->job->wait_time,
               timebuf,
               "READY");
    }

    printf("\n");
}

int main() {
    struct timeval interval;
    struct itimerval new, old;
    struct stat statbuf;
    struct sigaction newact;
    struct sigaction oldact1;
    struct sigaction oldact2;

    if (stat(FIFO, &statbuf) == 0) {
        /* if fifo file exists, remove it */
        if (remove(FIFO) < 0) {
            error_sys("remove failed");
        }
    }

    if (mkfifo(FIFO, 0666) < 0) {
        error_sys("mkfifo failed");
    }
    /* open fifo in nonblock mode */

    if ((fifo = open(FIFO, O_RDONLY | O_NONBLOCK)) < 0) {
        error_sys("open fifo failed");
    }

    /* open global file for job output */

    if ((globalfd = open("/dev/null", O_WRONLY)) < 0) {
        error_sys("open global file failed");
    }
    /* setup signal handler */
    newact.sa_sigaction = sig_handler; //
    sigemptyset(&newact.sa_mask); // make newact empty.
    newact.sa_flags = SA_SIGINFO; // set it for make sa_sigaction can be use

    sigaction(SIGCHLD, &newact, &oldact1); // 对原来SIGCHLD信号的处理,去了oldact1
    sigaction(SIGVTALRM, &newact, &oldact2);// 对原来SIGVTALRM信号的处理,去了oldact2

    /* timer interval: 0s, 100ms */

    interval.tv_sec = 0;
    interval.tv_usec = 100000;

    //*FIND BUG2
    // 100 ms = 10^-1s = 10^-1 * 10^6 us = 10^5 us.

    new.it_interval = interval;
    new.it_value = interval;
    setitimer(ITIMER_VIRTUAL, &new, &old); // generate SIGVTALRM every 100ms.

    printf("OK! Scheduler is starting now!!\n");

    while (siginfo == 1);

    close(fifo);
    close(globalfd);
    return 0;
}

void pid_to_name(int pid, char *ret) {
    char command[1024] = "ps -p 3687 comm=";
    char buffer[1024];
    //printf("%s\n",command);
    struct FILE *fp;
    fp = popen(command, "r");
    //fgets(buffer, sizeof(char) * 1024, fp);
    fread(buffer, sizeof(char), sizeof(buffer), fp);
    pclose(fp);
    // ! THEN , the subprocess will send SIGCHLD.
    //! SO IT CAN NOT USE.
    //printf("%s\n",buffer);
    strcpy(ret, buffer);
}

void pid_to_name_2(int pid, char *ret) {
    char path[1024];
    char buffer[1024];
    char useless[1024];
    int count = 0;
    memset(path, '\0', sizeof(path));
    memset(buffer, '\0', sizeof(buffer));
    memset(useless, '\0', sizeof(useless));
    sprintf(path, "/proc/%d/status", pid);
    struct FILE *fp;
    fp = fopen(path, "r");
    fscanf(fp, "%s", useless);
    fgets(useless, 1, (FILE *) fp);
    fgets(buffer, 10, (FILE *) fp);
    if ('\t' == buffer[0]) {
        count++;
    }
    strcpy(ret, buffer + count);
    fclose(fp);
}
