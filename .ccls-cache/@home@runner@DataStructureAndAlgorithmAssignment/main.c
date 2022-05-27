#include <stdbool.h>
#include <stdio.h>

// 배열 출력 함수(매개변수 : 출력할 배열, 배열 길이, 포맷팅 자릿수, 간격, 천단위 구분)
void printArr(int array[], int length, int digits, bool spacing, bool comma) {
  switch (digits) {
  case 0:
    for (int i = 0; i < length; i++) {
      printf("%d", array[(length - 1) - i]); // 배열을 반대로 출력
      if (comma && (length - i - 1) > 0 &&
          ((length - i - 1) % 3) == 0) { // 천단위 콤마 구분
        printf(",");
      }
      if (spacing) {
        printf(" ");
      }
    }
    break;
  case 2:
    for (int i = 0; i < length; i++) {
      printf("%2d", array[(length - 1) - i]);
      if (spacing) {
        printf(" ");
      }
    }
    break;
  case 3:
    for (int i = 0; i < length; i++) {
      printf("%3d", array[(length - 1) - i]);
      if (spacing) {
        printf(" ");
      }
    }
    break;
  }
  printf("\n");
}

// 메인 함수
int main(void) {
  // 변수 선언 및 초기화, 배열 역순 저장
  // ----------------------------------------------------------------------------------
  int reference[21] = {7, 2, 9, 2, 1, 4, 6, 7, 6, 9, 8, 5, 2, 5, 9, 3, 7, 5, 7, 4, 1};
  int divisorA[12] = {7, 8, 2, 7, 5, 2, 8, 3, 8, 1, 6, 7};
  int divisorB[9] = {1, 2, 7, 7, 0, 7, 3, 9, 1};
  int multiply[21] = {0,};
  int power[21] = {0,};
  int diff = 0;

  // 변수 출력
  // ----------------------------------------------------------------------------------
  printf("\n> Values\n");
  printf("  reference : ");
  printArr(reference, 21, 0, false, true);
  printf("  divisorA  : ");
  printArr(divisorA, 12, 0, false, true);
  printf("  divisorB  : ");
  printArr(divisorB, 9, 0, false, true);

  // 2^67 - 1 계산
  // ----------------------------------------------------------------------------------
  printf("\n> Power Operation\n");
  power[0] = 1;
  for (int i = 0; i < 67; i++) {
    for (int j = 0; j < 21; j++) {
      power[j] *= 2;
    }
    printf("  [2^%-2d][ ] ", i + 1);
    printArr(power, 21, 2, true, false);
    for (int j = 0; j < 21; j++) {
      if (power[j] >= 10) {
        power[j + 1] += power[j] / 10;
        power[j] -= (power[j] / 10) * 10;
        printf("  [2^%-2d][C] ", i + 1);
        printArr(power, 21, 2, true, false);
      }
    }
  }
  power[0] -= 1;
  printf("  ------------------------------------------------------------------------\n");
  printf("  [result] 2^67 - 1 = ");
  printArr(power, 21, 0, false, true);
  return 0;
}