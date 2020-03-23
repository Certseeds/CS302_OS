<!--
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-23 18:18:03
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-03-23 19:17:52
 -->
# Report 1
studentID=1145141
username=1919810
## 1 run `mkdir ~/${studentID}`
1. first of all, use mkdir to build a new folder,
2. ~ is the Abbreviation of `/home/${username}`
3. so `mkdir ~/${studentID}` is build a  new folder named `${studentID}`in `/home/${username}/`

## 2 run `ls –la ~ `
1. The ls command is used to display sub-files and directories under a folder.
-la as a parameter, a combination of "-l"&"-a"
2. -a show all files and directories(include hidden files)
3. -l In addition to the file name, it also details the file type, permissions, owner, file size, etc.
4. ~ Is short for `/home/${username}`
Therefore, this instruction lists all the file types, permissions, owners, file sizes, etc. of all files in the `/home/${username}` folder

## 3 run ` cd ~/${studentID}`
1. The cd command is used to switch the current working directory to dirName (directory parameter).
2. Where dirName notation can be absolute or relative. 
3. If the directory name is omitted, it changes to the user's home directory (that is, the directory where the user was just logged in).
4. ~ Is short for `/home/${username}`
therefore, this instruction change to `/home/${username}/${studentID}`

## 4 run `man grep`
1. The man command is a help command under Linux. Through the man command, you can view information such as command help, configuration file help, and programming help in Linux.
2. `man (options) (parameters)`
    1. Parameters: Specify a keyword or manual to search for help.
3. man grep is to view the grep instruction help page

## 5 run `mv ~/${studentID} /home`and" ls/home"
1. The Linux mv command is used to rename a file or directory, or move a file or directory to another location.
2. `mv [options] source dest`
mv directory name directory name destination directory already exists, move the source directory to the destination directory; rename the destination directory if it does not exist
3. ~ Is short for `/home/${username}`
mv `~/${studentID} /home` will move `/home/${username}/${studentID}` folder to `/home/`
3. ls /home  instruction list files in the `/home` folder

## 6 run `rm -r /home/${studentID}`
1. rm command is used to delete a file or directory.
    1. -r Delete directories and the following files one by one.
    2. `rm -r /home/${studentID}` deletes all `/home/${studentID}` directories

## 7 run `cp /etc/apt/sources.list /etc/apt/sources.list.bak`
1. The cp command is mainly used to copy files or directories.
2. `cp /etc/apt/sources.list /etc/apt/sources.list.bak`
Will copy a copy of `/etc/apt/sources.list` to `/etc/apt/sources.list.bak`

## 8 run `cat /etc/shells`
1. The cat command is used to connect a file and print it to the standard output device.
2. The `/etc/shells` file is a list of all available shells on the current system
3. cat `etc/shells` will print available shells on the system

## 9 run `cat /etc/shells | grep bash`
1. 
    + The cat command is used to connect a file and print it to the standard output device.
    + The `/etc/shells` file is a list of all available shells on the current system
    + cat `/etc/shells` will print available shells on the system 
2. 
    + `|` Is a pipe command operator, it can only process the correct output information sent by the previous instruction, that is, the information of standard output, and then pass it to the next command as the standard input.
3. 
    + The grep command is used to find qualified strings in a file
    + grep bash will output all lines that include the word `bash`
4. final
This statement reads from `/etc/shells` and filters all lines with `bash`

## 10 Open two terminals, find their PIDs by ps and kill one of them
1. open two terminals use gui, no instruction.
2. The ps command is used to display the status of the current process.
    + -ef Display all process information, along with the command line
    + -e show all processes
    + -f show the relationship between processes
    + `ps -ef` shows all processes and shows the relationship between processes.
3. The kill command is used to delete a running program or job
    + -KILL can be forced off
4. The closed instruction is queried with pid.
