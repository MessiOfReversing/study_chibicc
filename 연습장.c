/* main.c */
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { // 열거형 정의 "앞으로 이 타입을 TokenKind 라고 부르겠다" 라는 의미
TK_PUNCT, // 기호 (구분자, 연산자 등)를 의미함.
TK_NUM, // 숫자를 의미함. like 정수 리터럴
TK_EOF, // 파일의 끝을 알림.
} TokenKind;

typedef struct Token Token;
struct Token {
  TokenKind kind; // 토큰의 종류
  Token *next; // 다음 토큰
  int val; // 만약 kind가 TK_NUM 이라면 그 값을 적음
  char *loc; // 토큰의 위치
  int len; // 토큰의 길이
};

static void error(char *fmt, ...) {
  va_list ap; // 벡터 배열 리스트를 의미한다. 즉 이 ap를 받는 함수는 앞에 v가 붙는다. 기본적으로 작동은 순정과 동일하다.
  va_start(ap, fmt); // fmt라고만 적으면 딱 *fmt에 저장된 타깃의 주소를 의미한다.
  vfprintf(stderr, fmt, ap); // 사용자가 보낸 에러 내용인 fmt와 ap를 해석해서 stderr이라는 표준 에러 함수로 출력해라.
  fprintf(stderr, "\n"); // 그리고 줄바꿈.
  exit(1);
}

static bool equal(Token *tok, char *op) {
  return memcmp(tok->loc, op, tok->len) == 0 && op[tok->len] == '\0';
}

static Token *skip(Token *tok, char *s) {
  if (!equal(tok, s))
    error("expected '%s'", s);
  return tok->next; // equal이라면 if 패스하고 next를 반환.
}

static int get_number(Token *tok) { //검사할 토큰의 주소를 인자로 받음
  if (tok->kind != TK_NUM) // 현재 조사중인 토큰이 숫자가 맞는지 확인해줄 함수임.
    error("expected a number"); 
  return tok->val; // if문에서 걸러지지 않았다면 숫자가 맞을테니 val에 입력.
}

static Token *new_token(TokenKind kind, char *start, char *end) { 
  // static Token *에서 생성된 새로운 토큰 객체의 메모리 주소를 반환함.
  // 인자로는 만들고자 하는 인자의 종류와 소스코드 문자열의 시작과 끝 주소 셋을 받는다.
  Token *tok = calloc(1, sizeof(Token)); // 토큰 크기만큼 heap영역에 메모리 공간을 마련한다.
  tok->kind = kind;
  tok->loc = start;
  tok->len = end - start;
  return tok; // 전부 집어넣어서 완성된 토큰의 주소를 반환한다.
}

static Token *tokenize(char *p) { // 컴파일할 소스코드 문자열의 첫번째 글자 주소를 받는다.
  Token head = {}; // 내용이 빈 토큰 머리다. 연결 리스트의 시작점을 쉽게 잡기 위함이다.
  Token *cur = &head; // 현재 마지막 토큰이 어디인지 기억해줄 포인터다.

  while (*p){ 
    if (isspace(*p)) { // 현재 글자가 공백인지 검사한다.
      p++;
      continue; // 맞다면 p++로 한칸 옮기고, 공백이 아니라면 continue로 아래 if문으로 진입.
    }
    if (isdigit(*p)) { // isdigit, 즉 현재 글자가 '0'부터 '9'까지의 숫자 문자인지 검사한다.
      cur = cur -> next = new_token(TK_NUM, p, p);
      char *q = p;
      cur->val = strtoul(p, &p, 10);
      cur->len = p - q;
      continue;
    }
    error("invalid token");
  }
  cur = cur->next = new_token(TK_EOF, p, p);
  return head.next;
}
/* 여기부터 이전 커밋 코드
static bool equal(Token *tok, char *op) {
  return memcmp(tok->loc, op, tok->len) == 0 && op[tok->len] == '\0';
}
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
