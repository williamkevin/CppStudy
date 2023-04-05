## 06-1: const와 관련해서 아직 못다한 이야기
### const 객체와 const 객체의 특성들

```c++
const SoSimple sim(20);
```
-> 객체 sim의 데이터 변경을 허용하지 않음

```c++
//코드 1
#include <iostream>
using namespace std;

class SoSimple 
{
private:
	int num;
public:
	SoSimple(int n) : num(n) {}
	SoSimple& AddNum(int n)
	{
		num += n;
		return *this;
	}
	void ShowData() const
	{
		cout << "num: " << num << endl;
	}
	void SimpleFunc()
	{
		cout << "simplefunc: " << num << endl;
	}
	void SimpleFunc() const
	{
		cout << "simplefunc const: " << num << endl;
	}
};

void yourFunc(const SoSimple& obj)
{
	obj.SimpleFunc();
}

int main(void)
{
	SoSimple obj1(2);
	const SoSimple obj2(7);

	obj1.SimpleFunc();
	obj2.SimpleFunc();

	yourFunc(obj1);
	yourFunc(obj2);

	//obj2.AddNum(20);
	return 0;
}
``` 
![image](https://user-images.githubusercontent.com/110090496/230004105-c3a19e55-b621-46d4-bb3e-4d8bccdbd6bd.png)

main에서 정의된 객체 obj는 const에 의해 맴버변수를 바꿀 수 없다. main의 주석의 코드를 실행시키면 오류가 뜬다

### const와 함수 오버로딩
코드 1의 결과에 따라 알 수 있는 점
- 일반 객체를 대상을 SimpleFunc를 호출하면 일반 맴버함수가 호출됨
- const 객체를 대상을 SimpleFunc를 호출하면 const 맴버함수가 호출됨
- yourFunc에서는 인수를 const 참조자로 받았으므로 SimpleFunc를 호출했을때 const 맴버함수가 호출됨 

## 06-2: 클래스와 함수에 대한 friend 선언
```c++
class Boy {
private:
	int height;
	friend class girl;
public:
	Boy(int len) : height(len) {}
	....
};
```
