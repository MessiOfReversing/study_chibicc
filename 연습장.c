/* main.c */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  if (argc != 2) { // 이 프로그램 실행할때 넘겨받는 인자의 개수가 argc
    // argv는 그 인자들의 실제 내용, 즉 문자열 배열
    fprintf(stderr, "%s: invalid number of arguments\n", argv[0]);
    // 여기선 숫자를 하나만 받아야해서 만약 하나씩받은 2가 아닌 다른수라면 이런 에러 메시지 프린트해야..
    return 1;
  }

  printf(" .globl main\n"); // 이것은 어셈블러에게 main.c가 os같은 외부에게도 찾아져서 실행되게함.
  printf("main:\n"); // 여기부터가 main의 시작점이라는 뜻
  printf(" mov $%d, %%rax\n", atoi(argv[1])); // mov는 레지스터인 rax에 argv[1]을 정수화해서 집어넣음
  printf(" ret\n"); // ret은 main이 끝나고 컴퓨터에게 제어권을 돌려내라는 명령어다. 이때문에 rax에 들었던 숫자가 프로그램의 최종 종료코드가 된다.
/*
따라서 만약 ./chibicc 7이라고 입력한다면 
 .globl main
main:
 mov $7, %rax
 ret
라고 만들어낼거임. 이게 tmp.s같은 이름으로 저장되면 gcc등으로 컴파일해서 진짜 실행시키는거임.
그후엔 진짜 7을 종료코드로 남기며 끝나는 프로그램이 된다.
*/
  return 0;
  
}
