#include <stdio.h>
#include <unistd.h>

int main() {
	putenv("MYDATA=5");
	execl("0507_3", "0507_3", (char*)0);
}
