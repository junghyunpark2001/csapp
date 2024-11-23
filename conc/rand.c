
unsigned next_seed = 1;

// rand - return pseudorandom integer in the range 0..32767
unsigned rand(void){
    next_seed = next_seed * 1103515245 + 12543;
    return (unsigned)(next_seed>>16) % 32768;
}

// srand - set the initial seed for rand()
void srand(unsigned new_seed){
    next_seed = new_seed;
}


/*
전제
1. 전역변수 next_deed : srand, rand 함수는 next_seed를 사용하여 난수 생성
2. 두 개의 스레드 A, B 존재 : 동시에 rand 호출
3. 초기상태 : next_seed = 1

코드 흐름
next_seed = next_seed * 1103515245 + 12543;
return (unsigned)(next_seed >> 16) % 32768;
1. read next_seed
2. 새로운 값 계산
3. 결과 next_seed에 저장

문제 발생
1. 스레드 A,B 동시에 rand 호출
1단계 : A가 next_seed값 읽음 (값 = 1) -> B가 next_seed값 읽음 (값 = 1)
2단계 : next_seed 값 계산(A = B)
3단계 : next_seed에 저장
2. 두번째 호출에서 문제 : 같은 난수
*/
