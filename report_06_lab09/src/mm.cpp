#include <iostream>
#include <unistd.h>
#include <string>
#include <algorithm>
#include "./free_block.hpp"
#include "./allocated_block.hpp"
#include "./functions.hpp"
/**
 * 关于这次作业代码题的一些说明。
 * 1) 如果当前没有足够的连续内存空间分配给新创建的进程，就返回创建进程失败。
 * 2）代码里没有给默认的分配算法，可以自己设定默认分配算法，在menu中标明你的默认算法即可。
 * */
/**
 * 实现说明.
 * 没有实现Buddy system.
 * 三种算法均实现,allocate and kill process也实现了,show the memory 是自带的.
 * Menu option1 只能执行一次,且只能在没有allocated_block时执行.
 * 实现了相邻free_block的merge.
 * 每次打印出的free_block均为排序后的顺序.(BF为size小到大,WF为size大到小,FF为地址低位->高位)
 * */
// 完成了基本功能,60分拿到了50.

using std::cout;
using std::cin;
using std::endl;
using std::string;
static constexpr const int32_t PROCESS_NAME_LEN = 32; //进程名最大长度
static constexpr const int32_t MIN_SLICE = 10;//内碎片最大大小
static constexpr const int32_t DEFAULT_MEM_SIZE = 1024; //总内存大小
static constexpr const int32_t DEFAULT_MEM_START = 0; //内存开始分配时的起始地址

int mem_size = DEFAULT_MEM_SIZE;
bool flag = false; //当内存以及被分配了之后，不允许更改总内存大小的flag
static int pid = 0;

algorithm_code algo_number = BF;

auto *free_block_head = new free_block(mem_size, DEFAULT_MEM_START, nullptr); //空闲数据块首指针
auto *allocated_block_head = static_cast<allocated_block *>(nullptr); //分配块首指针

void display_menu(); //显示选项菜单
void set_mem_size(); //设置内存大小
int allocate_mem(allocated_block *ab); //为制定块分配内存,负责switch到
int create_new_process(); //创建新的进程
int free_mem(allocated_block *ab); //释放分配块
int dispose(allocated_block *ab); //释放分配块结构体
void display_mem_usage(); //显示内存情况
void kill_process(); //杀死对应进程并释放其空间与结构体
void rearrange(algorithm_code ac); // FF的rearrange 方法
void merge_memory(); // 将块合在一起
allocated_block *find_process(allocated_block *ab, int32_t id);//寻找pid为id的分配块

//主函数
int main() {
    int op;
    pid = 0;
    while (true) {
        sleep(1);
        display_menu();
        fflush(stdin);
        fflush(stdout);
        cin >> op;
        switch (op) {
            case 1: {
                set_mem_size();
                break;
            }
            case 2: {
                cout << "Choose an algorithm" << endl;
                cout << "1: Best Fit(default)" << endl <<
                     "2: Worst Fit" << endl <<
                     "3: First Fit" << endl <<
                     "4: Buddy System(Dont choose, it the same as Best Fit)" << endl;
                int32_t number = 0;
                cin >> number;
                if (number < BF || number > BS) {
                    cout << "Illegal algorithm order, Please input correct Number" << endl;
                    algo_number = BF;
                } else {
                    algo_number = static_cast<algorithm_code>(number);
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
                cout << "bye...." << endl;
                return 0;
            }
            default: {
                break;
            }
        }
        merge_memory();
        clear_zero(free_block_head);
    }
}

void set_mem_size() { //更改最大内存大小
    if (flag) {
        printf("Flag is %d, Memory can not be set", flag);
        return;
    }
    if (allocated_block_head != nullptr) {
        cout << "Can not set memory, there have memory is using" << std::endl;
        return;
    }
    int recieve_size = 0;
    cin >> recieve_size;
    if (recieve_size > 0) {
        mem_size = recieve_size;
        delete free_block_head;
        free_block_head = new free_block(recieve_size, DEFAULT_MEM_START, nullptr);
        flag = !flag;
        return;
    }
    cout << "Can not use negative memory size" << std::endl;
}

void display_menu() {
    cout << endl << endl << string(18, '*') << "menu" << string(19, '*') << endl;
    printf("1) Set memory size (default = %d)\n", DEFAULT_MEM_SIZE);
    cout << "2) Set memory allocation algorithm" << endl;
    cout << "3) Create a new process" << endl;
    cout << "4) Kill a process" << endl;
    cout << "5) Display memory usage" << endl;
    cout << "233) Exit" << endl;
}

//为块分配内存，真正的操作系统会在这里进行置换等操作
int allocate_mem(allocated_block *ab) {
    // ab is not nullptr;
    // read a allocated_block, which have sizd ,pid.
    // if success return the address_begin, else return -1
    if (free_block_head == nullptr) {
        return -1;
    }
    rearrange(algo_number);
    if (algo_number == WF) {
        return ab->allocate_mem_WF(free_block_head, MIN_SLICE);
    }
    return ab->allocate_mem_FF_BF(free_block_head, MIN_SLICE);
}


int create_new_process() { //创建新进程
    int mem_sz = 0;
    cout << "Please input memory size" << std::endl;
    cin >> mem_sz;
    if (free_block_head == nullptr) {
        cout << "Can not create new process, no memory can use now" << endl;
        return -1;
    }
    // Write your code here
    if (mem_sz > mem_size) {
        cout << "Need too much memory, it is larger than total memory size" << endl;
        return -2;
    } else if (mem_sz <= 0) {
        cout << "Memory can not <= 0" << endl;
        return -3;
    }
    auto *process = new allocated_block(++pid, mem_sz, 0, nullptr);
    int32_t address_begin = allocate_mem(process);
    if (-1 == address_begin) {
        printf("Failed to create process with %d memory", mem_sz);
        delete process;
        pid--;
        return -5;
    }
    process->start_addr = address_begin;
    if (nullptr == allocated_block_head) {
        allocated_block_head = process;
        return 1;
    }
    allocated_block *temp = allocated_block_head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = process;
    return 2;
}


void rearrange(algorithm_code ac) {
    free_block *tmp = free_block_head;
    free_block *tmpx;
    cout << "Rearrange begins..." << endl;
    cout << "Rearrange by address..." << endl;
    while (tmp != nullptr) {
        tmpx = tmp->next;
        while (tmpx != nullptr) {
            if (cmp[ac](tmpx, tmp)) {
                free_block_swap(tmp, tmpx);
            }
            tmpx = tmpx->next;
        }
        tmp = tmp->next;
    }
    usleep(500);
    cout << "Rearrange Done." << endl;
}

int free_mem(allocated_block *ab) { //释放某一块的内存
    // 先判空,然后找有没有能串上的.
    if (free_block_head == nullptr) {
        free_block_head = new free_block(ab->size, ab->start_addr, nullptr);
        return 0;
    }
    free_block *pre = free_block_head;
    while (pre->next != nullptr) {
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
    while (pre->next != nullptr) {
        pre = pre->next;
    }
    pre->next = new free_block(ab->size, ab->start_addr, nullptr);
    return 3;
}

int dispose(allocated_block *fab) { //释放结构体所占的内存
    allocated_block *pre, *ab;
    if (fab == allocated_block_head) {
        allocated_block_head = allocated_block_head->next;
        delete fab;
        return 1;
    }
    pre = allocated_block_head;
    ab = allocated_block_head->next;
    while (ab != fab) {
        pre = ab;
        ab = ab->next;
    }
    pre->next = ab->next;
    delete ab;
    return 2;
}

void display_mem_usage() {
    rearrange(algo_number);
    cout << free_block_head << endl;
    cout << allocated_block_head << endl;
}

void kill_process() { //杀死某个进程
    allocated_block *ab;
    cout << "Please input the pid of Killed process" << endl;
    int pid = -1;
    cin >> pid;
    if (pid <= 0) {
        cout << "Pid begin at 1, can not be number that smaller or equal to zero" << endl;
    }
    ab = find_process(allocated_block_head, pid);
    if (ab != nullptr) {
        free_mem(ab);
        dispose(ab);
    } else {
        cout << pid << " can not be found" << endl;
    }
}

void merge_memory() {
    rearrange(FF);
    cout << "Mergeing connect memory" << endl;
    free_block *tmp = free_block_head;
    free_block *tmpx;
    while (tmp != nullptr) {
        tmpx = tmp->next;
        if (tmpx == nullptr) {
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
    cout << "Rearrange Done." << endl;
}

//循环遍历分配块链表，寻找pid=id的进程所对应的块
allocated_block *find_process(allocated_block *ab, int32_t id) {
    allocated_block *head = ab;
    while (nullptr != head) {
        if (head->pid == id) {
            break;
        }
        head = head->next;
    }
    return head;
}