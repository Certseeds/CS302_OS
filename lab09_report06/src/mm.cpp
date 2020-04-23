#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
/*
 * 关于这次作业代码题的一些说明。
 * 1) 如果当前没有足够的连续内存空间分配给新创建的进程，就返回创建进程失败。
 * 2）代码里没有给默认的分配算法，可以自己设定默认分配算法，在menu中标明你的默认算法即可。
 * */
/*
 * 实现说明.
 * 没有实现Buddy system.
 * 三种算法均实现,allocate and kill process也实现了,show the memory 是自带的.
 * Menu option1 只能执行一次,且只能在没有allocated_block时执行.
 * 实现了相邻free_block的merge.
 * 每次打印出的free_block均为排序后的顺序.(BF为size小到大,WF为size大到小,FF为地址低位->高位)
 * */
#define PROCESS_NAME_LEN 32 //进程名最大长度
#define MIN_SLICE 10 //内碎片最大大小
#define DEFAULT_MEM_SIZE 1024  //总内存大小
#define DEFAULT_MEM_START 0  //内存开始分配时的起始地址

typedef pair<int, string> My_algo;

int mem_size = DEFAULT_MEM_SIZE;
bool flag = false; //当内存以及被分配了之后，不允许更改总内存大小的flag
static int pid = 0;
My_algo algo[123];
int algo_number = 1;
struct free_block {    //空闲数据块
    int size;
    int start_addr;
    struct free_block *next;
};

struct allocated_block { //已分配的数据块
    int pid;
    int size;
    int start_addr;
    int *data;
    struct allocated_block *next;
};

free_block *free_block_head; //空闲数据块首指针
allocated_block *allocated_block_head = NULL; //分配块首指针

allocated_block *find_process(int id); //寻找pid为id的分配块
free_block *init_free_block(int mem_size); //空闲块初始化
void display_menu(); //显示选项菜单
void set_mem_size(); //设置内存大小
int allocate_mem(allocated_block *ab); //为制定块分配内存,负责switch到
void rearrange(); // 对块进行重新分配
int create_new_process(); //创建新的进程
int free_mem(allocated_block *ab); //释放分配块
void swap(int *p, int *q); //交换地址
int dispose(allocated_block *ab); //释放分配块结构体
void display_mem_usage(); //显示内存情况
void kill_process(); //杀死对应进程并释放其空间与结构体
void Usemy_algo(int id); //使用对应的分配算法
int allocate_mem_WF(allocated_block *ab); // 负责allocate_mem wf
int allocate_mem_FF_BF(allocated_block *ab); // allocate_mem ff bf.
void rearrage_BF(); // BF的rearrage 方法
void rearrage_WF(); // WF的rearrage 方法
void rearrage_FF(); // FF的rearrage 方法
void clear_zero(); // 负责每次循环过后,将free_block中0 == size的去掉.
void merge_memory();
// 负责每次循环后,将相邻的free_block merge到一起.(还有一部分merge在free_mem)时做了

//主函数
int main() {
    int op;
    pid = 0;
    free_block_head = init_free_block(mem_size); //初始化一个可以使用的内存块，类似与操作系统可用的总存储空间
    for (;;) {
        sleep(1);
        display_menu();
        fflush(stdin);
        fflush(stdout);
        scanf("%d", &op);
        switch (op) {
            case 1: {
                set_mem_size();
                break;
            }
            case 2: {
                printf("Choose an algorithm\n");
                printf(" 1: Best Fit(default)\n 2: Worst Fit\n 3: First Fit\n 4: Buddy System(Dont choose, it the same as Best Fit)\n");
                scanf("%d", &algo_number);
                if (algo_number > 4 || algo_number <= 0) {
                    printf("Illegal algorithm order, Please input correct Number");
                    algo_number = 1;
                }
                break;
            }
            case 3: {
                create_new_process();
                break;
            }
            case 4: {
                kill_process();
                break;
            }
            case 5: {
                display_mem_usage();
                break;
            }
            case 233: {
                puts("bye....");
                sleep(1);
                return 0;
            }
            default: {
                break;
            }
        }
        merge_memory();
        clear_zero();
    }
}

allocated_block *find_process(int id) { //循环遍历分配块链表，寻找pid=id的进程所对应的块
    allocated_block *head = allocated_block_head;
    while (NULL != head) {
        if (id == head->pid) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

free_block *init_free_block(int mem_size) {
    //初始化空闲块，这里的mem_size表示允许的最大虚拟内存大小
    free_block *p;
    p = (free_block *) malloc(sizeof(free_block));
    if (NULL == p) {
        puts("No memory left");
        return NULL;
    }
    p->size = mem_size;
    p->start_addr = DEFAULT_MEM_START;
    p->next = NULL;
    return p;
}

// UNTODO
void set_mem_size() { //更改最大内存大小
    if (flag) {
        printf("Flag is %d, Memory can not be set", flag);
        return;
    }
    if (NULL != allocated_block_head) {
        printf("Can not set memory, there have memory is using");
        return;
    }
    int recieve_size;
    scanf("%d", &recieve_size);
    if (recieve_size > 0) {
        mem_size = recieve_size;
        free(free_block_head);
        free_block_head = NULL;
        free_block_head = init_free_block(recieve_size);
        flag = !flag;
        return;
    }
    printf("Can not use negative memory size");
}

void display_menu() {
    puts("\n\n******************menu*******************");
    printf("1) Set memory size (default = %d)\n", DEFAULT_MEM_SIZE);
    printf("2) Set memory allocation algorithm\n");
    printf("3) Create a new process\n");
    printf("4) Kill a process\n");
    printf("5) Display memory usage\n");
    printf("233) Exit\n");
}

int allocate_mem(allocated_block *ab) { //为块分配内存，真正的操作系统会在这里进行置换等操作
    // read a allocated_block, which have sizd ,pid.
    // if success return the address_begin, else return -1
    if (NULL == free_block_head) {
        return -1;
    }
    switch (algo_number) {
        case 1: {
            rearrage_BF();
            return allocate_mem_FF_BF(ab);
        }
        case 2: {
            rearrage_WF();
            return allocate_mem_WF(ab);
        }
        case 3: {
            rearrage_FF();
            return allocate_mem_FF_BF(ab);
        }
        case 4: {
            // UNTODO
            rearrage_BF();
            return allocate_mem_FF_BF(ab);
        }
        default: {
            return -1;
        }
    }
}

int allocate_mem_WF(allocated_block *ab) {
    rearrage_WF();
    int will_return = -1;
    if (free_block_head->size >= ab->size) {
        will_return = free_block_head->start_addr;
        if (free_block_head->size <= ab->size + MIN_SLICE) {
            ab->size = free_block_head->size;
            free_block_head->size = 0;
            free_block_head->start_addr = 0;
        } else {
            free_block_head->size -= ab->size;
            free_block_head->start_addr += ab->size;
        }
    }
    return will_return;
}

int allocate_mem_FF_BF(allocated_block *ab) {
    free_block *fb = (free_block *) malloc(sizeof(free_block));
    fb->next = free_block_head;
    free_block *fb_head = fb;
    int will_return = -1;
    while (NULL != fb->next) {
        if (fb->next->size >= ab->size) {
            will_return = fb->next->start_addr;
            if (fb->next->size <= ab->size + MIN_SLICE) {
                ab->size = fb->next->size;
                fb->next->size = 0;
                fb->next->start_addr = 0;
            } else {
                fb->next->size -= ab->size;
                fb->next->start_addr += ab->size;
            }
            break;
        }
        fb = fb->next;
    }
    free(fb_head);
    fb = NULL;
    return will_return;
}

int create_new_process() { //创建新进程
    int mem_sz = 0;
    printf("Please input memory size\n");
    scanf("%d", &mem_sz);
    if (NULL == free_block_head) {
        printf("Can not create new process, no memory can use now");
        return -1;
    }
    // Write your code here
    if (mem_sz > mem_size) {
        printf("Need too much memory, it is larger than total memory size");
        return -2;
    } else if (mem_sz <= 0) {
        printf("Memory can not <= 0");
        return -3;
    }
    allocated_block *process = (allocated_block *) malloc(sizeof(allocated_block));
    if (NULL == process) {
        printf("malloc for process failed");
        return -4;
    }
    process->size = mem_sz;
    process->next = NULL;
    pid++;
    process->pid = pid;
    int32_t address_begin = allocate_mem(process);
    if (-1 == address_begin) {
        printf("Failed to create process with %d memory", mem_sz);
        free(process);
        process = NULL;
        pid--;
        return -5;
    }
    process->start_addr = address_begin;
    if (NULL == allocated_block_head) {
        allocated_block_head = process;
        return 1;
    }
    allocated_block *temp = allocated_block_head;
    while (NULL != temp->next) {
        temp = temp->next;
    }
    temp->next = process;
    return 2;
}

void swap(int *p, int *q) {
    int tmp = *p;
    *p = *q;
    *q = tmp;
    return;
}

void rearrange() { //将块按照地址大小进行排序
}

// 遍历未分配list,去掉那些size == 0的
void clear_zero() {
    if (NULL == free_block_head) {
        return;
    } else if (0 == free_block_head->size) {
        free_block *fb_head = free_block_head->next;
        free(free_block_head);
        free_block_head = fb_head;
        clear_zero();
        return;
    }
    free_block *fb_head = free_block_head;
    free_block *will_free;
    while (NULL != fb_head->next) {
        if (0 == fb_head->next->size) {
            will_free = fb_head->next;
            fb_head->next = will_free->next;
            free(will_free);
        }
        fb_head = fb_head->next;
    }
}

void rearrage_BF() {
    free_block *tmp = free_block_head;
    free_block *tmpx;
    puts("Rearrange begins...");
    puts("Rearrange by address...");
    while (NULL != tmp) {
        tmpx = tmp->next;
        while (NULL != tmpx) {
            if (tmpx->size < tmp->size) {
                swap(&tmp->start_addr, &tmpx->start_addr);
                swap(&tmp->size, &tmpx->size);
            }
            tmpx = tmpx->next;
        }
        tmp = tmp->next;
    }
    usleep(500);
    puts("Rearrange Done.");
}

void rearrage_WF() {
    free_block *tmp = free_block_head;
    free_block *tmpx;
    puts("Rearrange begins...");
    puts("Rearrange by address...");
    while (NULL != tmp) {
        tmpx = tmp->next;
        while (NULL != tmpx) {
            if (tmpx->size > tmp->size) {
                swap(&tmp->start_addr, &tmpx->start_addr);
                swap(&tmp->size, &tmpx->size);
            }
            tmpx = tmpx->next;
        }
        tmp = tmp->next;
    }
    usleep(500);
    puts("Rearrange Done.");
}

void rearrage_FF() {
    free_block *tmp, *tmpx;
    puts("Rearrange begins...");
    puts("Rearrange by address...");
    tmp = free_block_head;
    while (NULL != tmp) {
        tmpx = tmp->next;
        while (NULL != tmpx) {
            if (tmpx->start_addr < tmp->start_addr) {
                swap(&tmp->start_addr, &tmpx->start_addr);
                swap(&tmp->size, &tmpx->size);
            }
            tmpx = tmpx->next;
        }
        tmp = tmp->next;
    }
    usleep(500);
    puts("Rearrange Done.");
}

int free_mem(allocated_block *ab) { //释放某一块的内存
    // 先判空,然后找有没有能串上的.
    if (NULL == free_block_head) {
        free_block *fb = (free_block *) malloc(sizeof(free_block));
        fb->start_addr = ab->start_addr;
        fb->size = ab->size;
        fb->next = NULL;
        free_block_head = fb;
        return 0;
    }
    free_block *pre = free_block_head;
    while (NULL != pre->next) {
        if (pre->start_addr + pre->size == ab->start_addr) {
            pre->size += ab->size;
            return 1;
        } else if (ab->start_addr + ab->size == pre->start_addr) {
            pre->start_addr = ab->start_addr;
            pre->size += ab->size;
            return 2;
        }
        pre = pre->next;
    }
    pre = free_block_head;
    while (NULL != pre->next) {
        pre = pre->next;
    }
    pre->next = (free_block *) malloc(sizeof(free_block));
    pre->next->size = ab->size;
    pre->next->start_addr = ab->start_addr;
    pre->next->next = NULL;
    return 3;
}

int dispose(allocated_block *fab) { //释放结构体所占的内存
    allocated_block *pre, *ab;
    if (fab == allocated_block_head) {
        allocated_block_head = allocated_block_head->next;
        free(fab);
        return 1;
    }
    pre = allocated_block_head;
    ab = allocated_block_head->next;
    while (ab != fab) {
        pre = ab;
        ab = ab->next;
    }
    pre->next = ab->next;
    free(ab);
    return 2;
}

void display_mem_usage() {
    switch (algo_number) {
        case 1: {
            rearrage_BF();
            break;
        }
        case 2: {
            rearrage_WF();
            break;
        }
        case 3: {
            rearrage_FF();
            break;
        }
        case 4: {
            rearrage_BF();
            break;
        }
        default: {
            break;
        }
    }
    free_block *fb = free_block_head;
    allocated_block *ab = allocated_block_head;
    puts("*********************Free Memory*********************");
    printf("%20s %20s\n", "start_addr", "size");
    int cnt = 0;
    while (NULL != fb) {
        cnt++;
        printf("%20d %20d\n", fb->start_addr, fb->size);
        fb = fb->next;
    }
    if (!cnt) {
        puts("No Free Memory");
    } else {
        printf("Totaly %d free blocks\n", cnt);
    }
    puts("");
    puts("*******************Used Memory*********************");
    printf("%10s %10s %20s\n", "PID", "start_addr", "size");
    cnt = 0;
    while (NULL != ab) {
        cnt++;
        printf("%10d %10d %20d\n", ab->pid, ab->start_addr, ab->size);
        ab = ab->next;
    }
    if (!cnt) {
        puts("No allocated block");
    } else {
        printf("Totaly %d allocated blocks\n", cnt);
    }
    return;
}

void kill_process() { //杀死某个进程
    allocated_block *ab;
    int pid;
    puts("Please input the pid of Killed process");
    scanf("%d", &pid);
    if (pid <= 0) {
        printf("Pid begin at 1, can not be number that smaller or equal to zero");
    }
    ab = find_process(pid);
    if (ab != NULL) {
        free_mem(ab);
        dispose(ab);
    } else {
        printf("%d can not be found", pid);
    }
}

void merge_memory() {
    rearrage_FF();
    printf("Mergeing connect memory");
    free_block *tmp = free_block_head;
    free_block *tmpx;
    while (NULL != tmp) {
        tmpx = tmp->next;
        if (NULL == tmpx) {
            break;
        }
        if (tmp->start_addr + tmp->size == tmpx->start_addr) {
            tmpx->start_addr = tmp->start_addr;
            tmpx->size += tmp->size;
            tmp->size = 0;
            tmp->start_addr = 0;
        }
        tmp = tmpx;
    }
    usleep(500);
    puts("Rearrange Done.");
}
