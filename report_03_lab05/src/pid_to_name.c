/* CS302_OS
    Copyright (C) 2020  nanoseeds

    CS302_OS is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    CS302_OS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
    */
/**
 * @Github: https://github.com/Certseeds/CS302_OS
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-03-30 11:12:12
 * @LastEditors  : nanoseeds
 */
#include <stdio.h>
#include <string.h>

void pid_to_name(int pid, char *ret);

int main(int argc, char *argv[]) {
    for (int i = 1; i > 5; i--) {
        printf("%d\n", i);
    }
}

int begin_pid() {
    char out[1024];
    memset(out, '\0', sizeof(char) * 1024);
    pid_to_name(1914, out);
    printf("%s", out);
    printf("%s", out);
    printf("%s", out);
    printf("%s", out);
    return 0;
}

void pid_to_name(int pid, char *ret) {
    int size_of_char = 1024;
    char command[size_of_char];
    char buffer[size_of_char];
    memset(command, '\0', sizeof(char) * size_of_char);
    memset(buffer, '\0', sizeof(char) * size_of_char);
    sprintf(command, "ps -p %d -o comm=", pid);
    printf("%s \n", command);
    struct FILE *fp;
    fp = popen(command, "r");
    fgets(buffer, sizeof(char) * 1024, fp);
    printf("%s 114514 ", buffer);
    strcpy(ret, buffer);
}