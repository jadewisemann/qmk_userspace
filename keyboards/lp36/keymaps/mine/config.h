#pragma once

/* 1. Tapping Term (기본값: 200ms) */
#undef TAPPING_TERM
#define TAPPING_TERM 135

/* 2. Flow Tap (오타 방지 핵심) */
/* "150ms 이내에 빠르게 연달아 친 키는 무조건 글자로 인식해라" */
/* 이게 있으면 롤링 오타(zf -> F)가 사라집니다. */
#define FLOW_TAP_TERM 30

/** Permissive Hold (빠른 입력 시 Mod Tap이 씹히지 않게 함) 
  * 설명: 탭텀 시간 안이라도 다른 키를 누르고 떼면 즉시 Hold로 판정 */
#define PERMISSIVE_HOLD

/** Ignore Mod Tap Interrupt (최신 QMK 명칭: Hold On Other Key Press) 
 * 설명: Mod-Tap 키를 누른 상태에서 다른 키를 입력하면 즉시 Hold로 판정
 * (Vial의 Ignore Mod Tap Interrupt와 동일한 효과를 냅니다) */
// #define HOLD_ON_OTHER_KEY_PRESS

/* [추천] Quick Tap Term (연타 시 Hold 되는 문제 방지) */
/* 설명: 같은 키를 빠르게 두 번 칠 때(예: zz) 두 번째가 Shift로 인식되는 것을 방지 */
/* 135ms처럼 짧은 탭텀을 쓸 때 매우 유용합니다. */
#define QUICK_TAP_TERM 0

#undef COMBO_TERM
#define COMBO_TERM 25