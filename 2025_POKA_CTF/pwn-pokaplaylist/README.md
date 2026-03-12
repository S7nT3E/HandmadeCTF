# 출제자
- S7nT3E

# 컨셉
- ROP, Tcache Poisoning, Tcache House of lore

# 풀이
- Tcache Poisoning을 이용해 Premium mode를 활성화시키고,
이를 통해 Tcache House of lore를 진행하여 스택에 fake chunk를 할당한 뒤에 ROP하는 문제

1. Tcache Poisoning
Tcache Poisoning을 위해서 double free를 일으켜야하는데,
이를 위해서song을 3개 이상 추가한 상태에서 마지막 song을 제외한 인접한 song 2개를 연속해서 swap한다.

이때 swap_adjacent_songs_buggy 함수 안에 있는 로직이 작동하며 마지막 곡이 swap에서 입력한 첫 번째 song을 가리키게 포인터가 조작된다.

이후 remove song 함수는song->next->song_id를 찾아서 삭제시키는 로직을 가지고 있기때문에,
동시에 next에 2개가 존재하는 song이 double free된다.

double free와 동시에 tcache에 들어간 chunk의 암호화된 next를 얻을 수 있는 문구가 출력되어서, 이를 통해 암호화에 사용하는 key를 얻는다 (확률적인 부분이 있음)

이후 망가진 tcache count를 복구하기 위해 임의로 1개의 song을 삭제시키고,
double free된 chunk를 재할당해서 하나는 할당된 상태 하나는 해제된 상태로 만든다.

이후 double free된 song을 이전 song의 heap overflow로  edit_album_art 함수에서 조작할 수 있다 이를 통해 song의 next를 전역변수인 premium_mode_active의 위치로 바꾸고 할당한다.

2. Tcache House of lore
premium_mode가 활성화되면 기존 함수의 기능이 추가 혹은 변경되거나, 새로운 함수를 사용할 수 있다.

먼저 premium mode가 활성화되면 메뉴 화면마다 stack에 있는 playlist 변수의 주소가 출력되는데 이를 받아두고, libc leak을 위해서 song count를 10까지 채워 0x420크기의 large song을 할당받고 play song 함수를 통해 libc base를 구한다.

이후 song을 원하는 흐름대로 추가하고 tcache를 가득채운다.
그리고 play_song 함수를 통해 heap address를 구한 뒤, edit_premium_playlist 함수를 통해 stack에 fake chunk와 fake freelist를 생성한다.

마지막으로 tcache에 있던 chunk를 전부 재할당해서 tcache를 비우고 small bin과 fake freelist를 할당받은 뒤 fake freelist를 edit_album_art 함수를 통해 조작하여 ROP를 진행하고 쉘을 딸 수 있다.

# 플래그
- poka{W3lc0m3_t0_th3_POKA_Pr3m1um_Pl4yl1st_M4x_M0d3!}
