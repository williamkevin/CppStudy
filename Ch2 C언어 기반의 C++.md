chapter2
==============

02-1 c언어 복습
---------------
* 키워드 const
```c++
const int num = 10; //변수num 값을 상수로. 수정불가.
const int* ptr = &val; //포인터ptr을 이용해서 변수val의 값을 수정할 수 없음.
int* const ptr = &val; //포인터ptr값 자체를 수정할 수 없음.
const int* const ptr = &val; //포인터 ptr값 자체를 수정할 수 없고 그 값을 이용해서 val의 값을 수정할 수 없음.
```
* 프로그램 메모리 구조
1. 데이터 : 전역변수
2. 스택 : 지역변수, 함수 호출 시 매개변수
3. 힙 : 동적할당(malloc)

* call-by-value vs call-by-reference
call-by-value : 함수 호출 시 값만 매개변수로 복사한다.
call-by-reference : 함수 호출 시 주솟값을 매개변수로 사용한다. 주솟값에 의해 함수 외부공간에 선언된 변수에 접근할 수 있다.

02-2 자료형 bool
-----------------
false : 0   
true : 0을 제외한 모든 값

```c++
sizeof(true); 1Byte
sizeof(false); 1Byte
```

02-3 참조자(reference)
------------------
C++에서는 C에서 없는 참조자라는 문법이 존재한다.   
```c++
int *ptr = &num; //1
int &ref = num; //2
```
>  ptr은 num이라는 변수의 주소를 담은 포인터이다.   
>  참조자는 2번처럼 선언되며 선언과 동시에 변수를 할당해야 된다.   
>  변수 num에 접근하는 것과 참조자 ref에 접근하는 것은 사실강 같은 메모리 공간의 값을 사용한다는 의미이다.   
>  참조자는 기존에 있던 변수의 별칭 정도로 이해할 수 있다.
   
다음 예시는 포인터에 대한 참조자 선언의 예시이다.
```c++
int num = 12;
int *ptr = &num;
int **dptr = &ptr;

int &ref = num;
int *(&pref) = ptr;
int **(&dpref) = dptr;
```
기존의 포인터 선언에서 &기호만 추가되었다.   사용할 때에는 기존의 포인터와 이중포인터처럼 사용하면 된다.
   
02-4 참조자와 함수
-------------
참조자는 함수와 함께 사용할 때 사용자에게 편리함을 가져다준다.
다음 두가지 swap함수를 살펴보자
```c++
void swap1(int *num1, int *num2)
{
   int temp = *num1;
   *num1 = *num2;
   *num2 = temp;
}
int main(void)
{
   int val1 = 10;
   int val2 = 20;
   swap1(&val1,&val2);

   return 0;
}
```

```c++
void swap2(int &num1, int &num2)
{
   int temp = num1;
   num1 = num2;
   num2 = temp;
}
int main(void)
{
   int val1 = 10;
   int val2 = 20;
   swap2(val1,val2);

   return 0;
}
```
swap1은 주솟값을 이용한 call-by reference형태의 함수 호출이고   
swap2는 참조값을 이용한 call-by reference형태의 함수 호출이다.   
swap2함수가 호출될 때 참조값이 선언과 동시에 할당되기 때문에 문법적인 문제가 발생하지 않는다.   
   swap2함수를 사용하는 것이 주소연산에 대한 문법적인 부분을 덜어내기 때문에 가독성이 좋다고 생각될 수 있지만 다음과 같은 문제점이 발생한다.
```c++
int num = 24;
myFunc(num);
cout<<num<<enl;
```
myFunc의 인자로 변수가 선언되는지(call-by reference), 참조자가 선언되는지(call-by reference)에 따라서 num값이 그대로일 수도 있고 바뀔 수도 있는 문제점이 있다.   
결국 myFunc의 함수 원형을 살펴본 후 num값의 변화에 대해 직접 확인해보는 불편함이 존재한다.   
따라서 다음의 const키워드를 통해 명시적으로 값이 변경되지 않음을 표현해줄 수 있다.
```c++
void myFunc(const int &ref) { ... }
```
함수 호출 시에 참조값을 인자로 전달하지만 값 자체를 변경하지는 않겠다는 의미이다.   
그렇다면 그냥 call-by value로 값만 전달하면 될 것을 굳이 참조자를 쓰는 이유가 뭘까?
  책에서는 실제로 참조자를 사용하지 않는 c++프로그래머들도 존재한다고 한다.
  개인적인 생각으로 참조자가 좋은 건지 잘 모르겠지만 다른 사람의 코드를 볼 줄 알아야 하니 이런게 있는구나 하고 넘어가야겠다.
   
지금까지는 함수의 인자로 참조자가 사용되는 경우에 대해서 살펴보았다. 이제 반환형이 참조자인 경우에 대해서 다음 예시를 통해 살펴보자.
```c++
int& RefRetrunFunc1(int &ref)
{
   ref++;
   return ref;
}
int main(void)
{
   int num1 = 1;
   int &num2 = RefRetrunFunc1(num1); //1
   //int num2 = RefRetrunFunc1(num1); //2

   num1++;
   num2++;
   num2++;

   cout<<num1<<endl;
   cout<<num2<<endl;

   return 0;
}
```
> 출력결과   
> 5   
> 5   

num1을 증가시키는 것과 num2를 증가시키는 것은 같은 메모리 공간의 값을 증가시키는 것이다.   
1번 대신 2번을 실행하는 경우 num1과 num2의 메모리 공간은 다르므로 다음과 같이 다른 값이 출력된다.   
> 출력결과   
> 3   
> 4   

반환형이 참조형인 경우, 반환값을 무엇으로 지정하는지에 따라 위와 같은 차이가 발생한다.

02-5 new & delete
-----------------
malloc과 free 대신 new와 delete를 이용하여 동적할당
```c++
int* ptr1 = (int*)malloc(sizeof(int) * n); //C
free(ptr1);

int* ptr2 = new int[n] //C++
delete []ptr2;
```
malloc과 new를 통해 동적할당하는 방식은 내부적으로 차이가 있으므로 주의해야됨(추후에 배움)   
다음과 같이 힙 영역에 대한 접근을 참조자로도 할 수 있음을 주목해자.
```c++
int *ptr = new int;
int &ref = *ptr;
ref = 20;
cout<<ref; //20출력
```

02-6 C++에서 C언어 표준함수 호출
-------------------
C++은 C언어에서 주로 사용한 라이브러리를 C++만의 버전으로 손쉽게 사용할 수 있다. 다음과 같이 선언하면 된다
```c++
#include <cstdio.h>
#include <cstdlib>
#include <cmath>
#include <cstring>
```
#include <stdio.h>처럼 C언어에서 사용하듯이 C++에서 사용해도 되지만, 가급적 C++만의 문법적 특징으로 구성된 C++의 표준 헤더파일을 사용하길 권장한다
