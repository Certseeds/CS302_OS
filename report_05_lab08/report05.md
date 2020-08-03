<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-04-14 17:46:26
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-06-03 15:02:04
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->
1. What is deadlock?什么是死锁.
Answer:
死锁是一种状态,指的是操作系统中,一组进程中任何一个进程都在等待组中另外一个或多个进程(包括自身)所占用的资源(比如发送信息,将某个锁释放等等,打印机等外设等等),因而整组进程都无法执行的状态.线程也可以发生死锁,但是此时所占用的资源的定义与进程不同,主要为各种锁(因为进程内所有线程的文件等资源是公用的).一般来说,我们所说的是进程的死锁.线程死锁会单独称为`Thread deadlock`

2. What are the requirements of deadlock?
    1. 资源不可以被共用,只能被单独进程所使用.在被进程使用时,其他申请的进程必须等待.
    2. 申请到资源使用权限的进程可以无限期等待,同时持有资源.(进程不主动给出资源).
    3. 进程申请到的资源不会被强制收回.(OS不会主动将资源索回,同时也要求).
    4. 有一组进程,其中进程之间互相持有所需要的资源.
    + 注解:这些条件是deadlock发生的必要不充分条件.
3. What’s different between deadlock prevention and deadlock avoidance?
    1. deadlock prevention 从死锁的四个条件入手,目的在与防止四个条件中的至少一个条件出现.好处在于不需要检测流程请求等,避免了检测的成本.但是缺点在于系统的效率会下降.
    2. deadlock avoidence 在进程申请资源时运行,通过进程申请的资源,对会不会出现死锁状态进行检查,会出现死锁状态就拒绝申请.优点时只在进程申请时才会检测,不会限制系统效率,缺点是需要进程预先告知所需的资源请求,而且也要明确系统已有的资源,也不可以出现资源被进程申请后没有被释放就直接退出的情况,换句话说,需要对现在和接下来的资源有明确的了解.在这种情况下,四个条件有可能发生,但是不会发生死锁.
    3. 区别1:deadlock prevention 在运行时发生,防止四个条件出现,而deadlock avoidence是在资源申请的时候进行.
    4. 区别2:prevention不需要对系统资源的情况有了解,而avoidence需要对系统资源,进程申请资源都很明确.
    5. 区别3:prevention会阻止死锁的四个条件发生,但是avoidence之后有可能会将死锁的四个条件凑齐,但是不会发生死锁.

4. How to prevent deadlock? Give at least two examples.
    1. 给进程持有的资源规定一个最长期限,超过最长期限后将资源收回.比如可以将太长时间没有任何变化的进程强制杀死等,这样就将"进程申请到的资源不会被强制收回,可以无限期等待"同时破坏了.
    2. 可以直接在进程开始执行时,将进程需要的所有资源都分配掉,这样进程之间就不会互相持有相互需要的资源.
    3. 可以使用抢占式的资源分配方式,预先给进程之间分配优先级,高优先级的进程可以将低优先级进程的资源抢过去.

5. Which way does recent UNIX OS choose to deal with deadlock problem, why?
    1. unix使用鸵鸟算法,具体来讲就是忽略死锁的存在,因而将死锁转交给进程自己处理.
    2. 因为死锁发生的概率较低,而且避免死锁的代价比较高,因此将检测死锁的职责转交给上层的应用程序(比如数据库等)比较合适.
6. What data structures you use in your implementation（of Banker's algorithm）? Where and why you use them? Are they optimal for your purpose?
   1. 使用了string,vector,unordered_map.
   2. 使用string为了方便接受读入的命令名称,使用vector为了存储资源的现有量,以及进程们的可用量与分配量,使用unordered_map是为了将进程和进程的可用量之间关联起来.
   3. string用在了读取命令处,方便使用.vector既使用在了资源的现有量处,也使用在了unordered_map的value中,存储进程们的资源可用值和已分配值.
   4. 我认为这是最好的选择,首先string比较方便管理,在只需要一次使用的时候比较方便,vector可以动态声明长度,适合资源种类依照输入变化的情况,unordered_map可以将进程的pid和其对应的资源vector联系起来,都是比较适合的数据结构.