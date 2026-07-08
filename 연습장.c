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

  char *p = argv[1];

  printf(" .globl main\n"); // 이것은 어셈블러에게 main.c가 os같은 외부에게도 찾아져서 실행되게함.
  printf("main:\n"); // 여기부터가 main의 시작점이라는 뜻
  printf(" mov $%ld, %%rax\n", strtol(p, &p, 10)); 
  // strtol은 문자열을 long int로 바꿔주는 함수이고, 세번째 인자의 10은 10진수로~ 라는 뜻이다.

  while (*p) { // while (null) 에서 종료
    if (*p == '+') {
      p++;
      printf(" add $%ld, %%rax\n", strtol(p, &p, 10));
      continue;
    }

    if (*p == '-') {
      p++;
      printf(" sub $%ld, %%rax\n", strtol(p, &p, 10));
      continue;
    }

    fprintf(stderr, "unexpected character: '%c'\n", *p);
    return 1;
  }
  printf(" ret\n"); // ret은 main이 끝나고 컴퓨터에게 제어권을 돌려내라는 명령어다. 이때문에 rax에 들었던 숫자가 프로그램의 최종 종료코드가 된다.
/*
따라서 만약 4 + 3 - 1 로 입력한다면
 .globl main
main:
 mov $4, %rax
 add $3, %rax
 sub $1, %rax
 ret
다.
*/
  return 0;
  
}
