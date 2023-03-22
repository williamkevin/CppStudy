## 01-1: printf와 scanf를 대신하는 입출력 방식
```c++
#include <iostream>

int main(void) {
	int num = 20;
	std::cout << "Hello World!" << std::endl;
	std::cout << "Hello " << "World!" << std::endl;
	std::cout << num << ' ' << 'A';
	std::cout << ' ' << 3.14 << std::endl;
	return 0;
}
```
![image](https://user-images.githubusercontent.com/110090496/226311741-5b6db22e-81fc-4127-b86b-52927c2345dc.png)

### 코드를 통해 알 수 있는 점

- **std::cout<<'출력대상'** 을 통해 출력을 한다. 
- c언어의 printf와 달리 별도의 출력포멧을 지정하지 않아도 된다. 
- **<<** 를 사용하여 연달아 출력대상을 출력할 수 있고 **std::endl** 를 통해 줄바꿈을 할 수 있다.
```c++
#include <iostream>

int main(void) {
	int val1, val2;
	int result = 0;
	std::cout << "두 개의 숫자입력: ";
	std::cin >> val1 >> val2;
	
	if (val1 < val2)
	{
		for (int i = val1 + 1; i < val2; i++)
			result += i;
	}
	else
	{
		for (int i = val1 + 1; i < val2; i++)
			result += i;
	}
	std::cout << "두 수 사이의 정수 합: " << result << std::endl;
	return 0;
}
```
![image](https://user-images.githubusercontent.com/110090496/226315220-08ecc85a-2e3b-45df-a040-369e8533f0f9.png)
### 코드를 통해 알 수 있는 점
- **std::cin>>변수 ** 을 통해 입력된 값을 변수에 저장한다.
- **>>** 를 통해 연달아 입력을 받을 수 있고 순차적으로 변수들에 저장된다

## 01-2 함수오버로딩
함수호출 시 전달되는 인자를 통해 호출하고자 하는 함수의 구분이 가능하므로 매개변수의 선언형태가 다르다면 동일한 이름의 함수정의를 허용한다. 이를 **함수 오버로딩** 이라 한다.

```c++
#include <iostream>

void Myfunc(void)
{
	std::cout << "Myfunc(void) is called" << std::endl;
}

void Myfunc(char c)
{
	std::cout << "Myfunc(char c) is called" << std::endl;
}
void Myfunc(int a)
{
	std::cout << "Myfunc(int a) is called" << std::endl;
}
int main(void) {
	Myfunc();
	Myfunc('A');
	Myfunc(0);
}
```
![image](https://user-images.githubusercontent.com/110090496/226820652-689f892d-835b-4616-979d-4a387ea729dd.png)

## 01-3 매개변수의 디폴트값
디폴트 값이란 '기본적으로 설정되어 있는 값'이다
```c++
int myfunc(int num=7);
```
c++에서는 위와 같이 함수를 정의할 수 있다. 이와 같이 정의하면 함수호출 시 인자를 전달하지 않을 경우 7이 전달되어 진다.
즉 myfunc()를 통해 함수를 호출한다면 매개변수는 7를 전달하게 된다.

매개변수가 여러개일 때 일부분만 디폴트 값으로 지정할 수 있다. 일부분만 지정할 때 오른쪽 매개변수부터 지정하는 형태로 지정해야 한다.(함수에 전달되는 인자가 왼쪽에서부터 오른쪽으로 채워지기 때문)
```c++
int myfunc(int num1, int num2, int num3=30);
int myfunc(int num1, int num2=20, int num3=30);
int myfunc(int num1=10, int num2=20, int num3=30);
```

```c++
#include <iostream>

int BoxVolume(int length, int width = 1, int height = 1)
{
	return length * width * height;
}

int main(void)
{
	std::cout << "[3, 3, 3] : " << BoxVolume(3, 3, 3) << std::endl;
	std::cout << "[5, 5, D] : " << BoxVolume(5, 5) << std::endl;
	std::cout << "[7, D, D] : " << BoxVolume(7) << std::endl;
	return 0;
}
```
![image](https://user-images.githubusercontent.com/110090496/226826417-dcd47a15-7f72-4918-b2a7-25f33ef01253.png)
## 01-4: 인라인(inline) 함수
인라인 함수는 매크로 함수와 유사하다. 매크로 함수를 호출하면 컴파일 이전에 전처리기에 의해 함수호출문이 함수의 몸체부분으로 대체된다. 매크로 함수의 단점은 복잡한 함수를 정의하기 까다롭다. 이때 인라인함수를 사용하면 매크로 함수의 장점(함수호출문이 함수 몸체부분으로 대체함)을 유지하되 단점(정의가 어려움)을 제거할 수 있다.
```c++
#include <iostream>

inline int SQUARE(int x)
{
	return x * x;
}

int main(void)
{
	std::cout << SQUARE(5) << std::endl;
	std::cout << SQUARE(7) << std::endl;
}
```
위의 예제를 통해 인라인함수 정의방법을 알 수 있다. 예제를 보면 알 수 있듯이 인라인 함수를 정의할 때 매크로함수와 달리 매개변수의 자료형을 정의해야 한다.

## 01-5:이름공간(namespace)에 대한 소개
여러 사람이 함께 프로그램 하나 만든다고 해보자. 커뮤니케이션을 엄청나게 잘하지 않는 이상 각자 짠 코드에서 변수 혹은 함수들의 이름이 중복되어 에러가 날 가능성이 있다. 이러한 가능성을 없애기 위해 이름공간(namespace)가 등장한다.
```c++
#include <iostream>

namespace one
{
	void func(void)
	{
		std::cout << "사람1이 정의한 함수" << std::endl;
	}
}
namespace two
{
	void func(void)
	{
		std::cout << "사람2이 정의한 함수" << std::endl;
	}
}

int main()
{
	one::func();
	two::func();
}
```
![image](https://user-images.githubusercontent.com/110090496/226840164-70356234-55e9-4d21-bfb3-96d76b35a126.png)

아래 예재를 통해 namespace 기반에서의 선언과 정의를 구분 방법을 알 수 있다
```c++
#include <iostream>

namespace one
{
	void func1(void);
	void func2(void);
}
namespace two
{
	void func3(void);
}

int main()
{
	one::func1();
}

void one::func1(void)
{
	std::cout << "사람1이 정의한 func1 함수" << std::endl;
	func2(); // 동일 이름공간에서 정의된 함수를 호출할때 이름공간을 안 적어주어도 된다
	two::func3(); // 다른 이름공간에서 정의된 함수를 호출할때는 이름공간을 적어주어야 한다
}
void one::func2(void)
{
	std::cout << "사람1이 정의한 func2 함수" << std::endl;
}
void two::func3(void)
{
	std::cout << "사람2이 정의한 func3 함수" << std::endl;
}
```
### 이름공간에 중첩
namespace 안에 또다른 namespace를 정의할 수 있다. 다음 예제에서는 namespace의 중첩과 중첩된 namespace에 접근하는 방법을 볼 수 있다.
```c++
#include <iostream>
namespace parent
{
	int num = 2;
	namespace sub1
	{
		int num = 3;
		namespace sub2
		{
			int num = 4;
		}
	}

}

int main(void)
{
	std::cout << parent::num << std::endl;
	std::cout << parent::sub1::num << std::endl;
	std::cout << parent::sub1::sub2::num << std::endl;
}
```
![image](https://user-images.githubusercontent.com/110090496/226847502-d0d74f0d-0fc1-4fc7-93bb-b9ec6adc2edc.png)

위의 예제에서 main 함수를 보면 namespace std가 중복해서 많이 쓰이는 것을 볼 수 있다. 이때 **using** 을 사용해서 이름공간 지정의 생략을 명령할 수 있다.
이때 지역변수의 선언과 마찬가지로 using 선언된 이후부터 효력을 발휘하며, 선언된 지역을 벗어나면 선언의 효력은 잃게 된다.
다음은 이전 예제에서 using 선언을 한 버젼이다
```c++
using namespace std

int main(void)
{
	cout << parent::num << std::endl;
	cout << parent::sub1::num << std::endl;
	cout << parent::sub1::sub2::num << std::endl;
}
```

### 범위지정 연산자(::)
범위지정 연산자를 사용하면 함수 내에서 전역변수에 접근할 수 있다
```c++
int val = 100;

int SimpleFunction(void)
{
	int val = 20; // 지역변수
	val += 3;// 지역변수
	::val += 7; // 전역변수
}
```
