# Sequence_ROP

### 문제 설명

ROP를 통해서 Sequence를 순서에 맞게 통과하면 쉘을 딸 수 있는 ROP 문제

---

### 문제 풀이

문제의 C코드를 제공하지는 않지만,
파일을 실행해보면 Canary 값과 check_sequence1 함수의 주소를 출력해줍니다.
(무슨 값인지 정확하게 알기 위해서는 바이너리를 분석해봐야합니다 (strip이 걸려있음))

이를 통해 Canary Leak, PIE base leak을 하고 sequence 함수들의 offset을 찾아서
각각 시퀀스의 조건을 넣고 ROP를 진행하면 sequence3까지 통과했을 때 쉘을 딸 수 있습니다.

---

### 후기

항상 내보고 싶었던 문제인 ROP기법을 활용한 문제를
이번 기회에 처음 출제하게 되었는데, 사실 Stack Pivoting과 같은 기법을 섞거나
더 꼬아서 어렵게 내고 싶었는데, 신입생 분들의 시도를 유도하기 위해 여러 요소들을 넣어봤습니다.

하지만 정작 신입생 분들은 풀지 못하시고, 이미 잘하시는 분들이
그냥 Libc base leak을 하거나 예상치 못한 offset을 통해 exploit을 하신 경우들이 있어서
writeup을 보며 재미를 느낄 수 있었던 문제였습니다.