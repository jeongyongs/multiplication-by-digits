#include <stdbool.h>
#include <stdio.h>

// 배열 비교 함수(매개변수 : 배열1, 배열2, 배열 길이)
bool diffArr(int ArrA[], int ArrB[], int length) {
  for (int i = 0; i < length; i++) {
    if (ArrA[i] != ArrB[i]) {
      return true;
    }
  }
  return false;
}

// 배열 출력 함수(매개변수 : 출력할 배열, 배열 길이, 포맷팅 자릿수, 간격, 천단위 구분, 줄바꿈)
void printArr(int array[], int length, int digits, bool spacing, bool comma, bool newLine) {
  switch (digits) {
  case 0:
    for (int i = 0; i < length; i++) {
      printf("%d", array[(length - 1) - i]); // 배열을 반대로 출력
      if (comma && (length - i - 1) > 0 && ((length - i - 1) % 3) == 0) { // 천단위 콤마 구분
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
  if (newLine) {
    printf("\n");
  }
}

// 메인 함수
int main(void) {
  // 변수 선언 및 초기화, 배열 역순 저장
  // -----------------------------------------------------------------------------------------------------
  int reference[21] = {7, 2, 9, 2, 1, 4, 6, 7, 6, 9, 8, 5, 2, 5, 9, 3, 7, 5, 7, 4, 1};
  int divisorA[12] = {7, 8, 2, 7, 5, 2, 8, 3, 8, 1, 6, 7};
  int divisorB[9] = {1, 2, 7, 7, 0, 7, 3, 9, 1};
  int multiply[21] = {0,};
  int power[21] = {0,};

  // 변수 출력
  // -----------------------------------------------------------------------------------------------------
  printf("\n> Values\n");
  printf("  reference : ");
  printArr(reference, 21, 0, false, true, true);
  printf("  divisorA  : ");
  printArr(divisorA, 12, 0, false, true, true);
  printf("  divisorB  : ");
  printArr(divisorB, 9, 0, false, true, true);

  // 2^67 - 1 계산 *** (1)
  // -----------------------------------------------------------------------------------------------------
  printf("\n> Power - Power Operation\n");
  power[0] = 1;
  for (int i = 0; i < 67; i++) {
    for (int j = 0; j < 21; j++) { // 제곱 연산
      power[j] *= 2;
    }
    printf("  [2^%-2d][ ] ", i + 1);
    printArr(power, 21, 2, true, false, true);
    for (int j = 0; j < 21; j++) { // 자리 올림
      if (power[j] >= 10) {
        power[j + 1] += power[j] / 10;
        power[j] -= (power[j] / 10) * 10;
        printf("  [2^%-2d][C] ", i + 1); // C : 자리 올림
        printArr(power, 21, 2, true, false, true);
      }
    }
  }
  power[0] -= 1;
  printf("  ------------------------------------------------------------------------\n");
  printf("  [result] power     = ");
  printArr(power, 21, 0, false, true, true);
  printf("           reference = ");
  printArr(reference, 21, 0, false, true, false);
  if (!diffArr(power, reference, 21)) {
    printf(" ..Same\n");
  } else {
    printf(" ..Not Same\n");
  }

  // 약수 곱셈, 각 자릿수 곱셈 연산 *** (2-1)
  // -----------------------------------------------------------------------------------------------------
  printf("\n> Multiply - Multiply Operation\n");
  for (int i = 0; i < 9; i++) {    // divisorB[9]
    for (int j = 0; j < 12; j++) { // divisorA[12]
      multiply[i + j] += divisorA[j] * divisorB[i];
      printf("  [%3d] ", (i * 12) + j + 1);
      printArr(multiply, 21, 3, true, false, true);
    }
  }

  // 약수 곱셈, 각 자릿수 자리 올림 *** (2-2)
  // -----------------------------------------------------------------------------------------------------
  printf("\n> Multiply - Carry Operation\n");
  for (int i = 0; i < 21; i++) {
    if (multiply[i] / 10 != 0) {
      multiply[i + 1] += multiply[i] / 10;
      multiply[i] -= multiply[i] / 10 * 10;
      printf("  [ C ] ");
    } else {
      printf("  [   ] ");
    }
    printArr(multiply, 21, 3, true, false, true);
  }

  // 연산 결과 비교, (multiply == power)?, power:2^67-1, multiply:divisorA * divisorB
  // -----------------------------------------------------------------------------------------------------
  printf("  -----------------------------------------------------------------------------------------\n");
  printf("  [result] multiply = ");
  printArr(multiply, 21, 0, false, true, true);
  printf("           power    = ");
  printArr(power, 21, 0, false, true, false);
  if (!diffArr(multiply, power, 21)) {
    printf(" ..Same\n");
    printf("\n           So, 761,838,257,287 and 193,707,721 are divisor of 147,573,952,589,676,412,927.\n");
    printf("              (761,838,257,287 X 193,707,721 = 147,573,952,589,676,412,927)\n");
  } else {
    printf(" ..Not Same\n");
  }

  return 0;
}