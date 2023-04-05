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
위의 코드에서 friend을 사용하여 girl클래스의 private맴버에 접근이 가능하다

```c++
#include <iostream>
#include <cstring>
using namespace std;

class girl; //

class Boy
{
private:
	int height;
	friend class girl;

public:
	Boy(int len) : height(len) {}
	void ShowYourFriendInfo(girl& frn);
};

class girl
{
private:
	char phNum[20];
public:
	girl(char* num)
	{
		strcpy(phNum, num);
	}
	void ShowYourFriendInfo(Boy& frn);
	friend class Boy;
};

void Boy::ShowYourFriendInfo(girl& frn)
{
	cout << "her phone number: " << frn.phNum << endl;
}

void girl::ShowYourFriendInfo(Boy& frn)
{
	cout << "his height: " << frn.height << endl;
}

int main(void)
{
	Boy boy(170);
	girl girll("123-123");
	boy.ShowYourFriendInfo(girll);
	girll.ShowYourFriendInfo(boy);
}
```
**friend 선언은 "정보은닉"을 무너뜨리는 문법이기에 아주 위험할 수 있습니다. 그러므로 극히 소극적으로 사용해야 합니다.**

### 함수의 friend 선언
```c++
#include <iostream>
using namespace std;
 
class Point;

class PointOP
{
private: 
	int opcnt;
public: 
	PointOP() :opcnt(0) {}

	Point PoinstAdd(const Point&, const Point&);
	Point PoinstSub(const Point&, const Point&);
	~PointOP()
	{
		cout << "Operation times: " << opcnt << endl;
	}

};

class Point
{
private:
	int x;
	int y;
public:
	Point(const int& xpos, const int& ypos) :x(xpos), y(ypos) {}
	friend Point PointOP::PoinstAdd(const Point&, const Point&);
	friend Point PointOP::PoinstSub(const Point&, const Point&);
	friend void ShowPointPos(const Point&);
};

Point PointOP::PoinstAdd(const Point& p1, const Point& p2)
{
	opcnt++;
	return Point(p1.x + p2.x, p1.y + p2.y);
}

Point PointOP::PoinstSub(const Point& p1, const Point& p2)
{
	opcnt++;
	return Point(p1.x - p2.x, p1.y - p2.y);
}

int main(void)
{
	Point pos1(1, 2);
	Point pos2(2, 4);
	PointOP op;

	ShowPointPos(op.PoinstAdd(pos1, pos2));
	ShowPointPos(op.PoinstSub(pos1, pos2));
	return 0;
}

void ShowPointPos(const Point& pos)
{
	cout << "x: " << pos.x << ", ";
	cout << "y: " << pos.y << ", "<< endl;
}
```

## 06-03: c++에서의 static
### c에서의 static
- 전역변수에서 선언된 static의 의미 -> 선언된 파일내에서만 참조를 허용하겠다는 의미
- 함수 내에서 선언된 static의 의미 -> 한번만 초기화 되고, 지역변수와 달리 함수를 빠져나가도 소멸되지 않는다

### static 맴버변수(클래스 변수)
static맴버변수는 **'클래스 변수'** 라고도 한다. 클래스당 하나만 생성된다. 즉, 객채를 몇개나 생성하건, 생성하지 않건, 하나만 할당되어서 객채들간 공유되는 변수이다. 
```c++
#include <iostream>
using namespace std;

class Simple
{
private: 
	static int simCnt;
public:
	Simple()
	{
		simCnt++;
		cout << simCnt << "번째 Simple 객체" << endl;
	}
};
int Simple::simCnt = 0;

class Complex
{
private:
	static int comCnt;
public:
	Complex()
	{
		comCnt++;
		cout << comCnt << "번째 Simple 객체" << endl;
	}
};
int Complex::comCnt = 0;

int main(void)
{
	Simple s1;
	Simple s2;

	Complex c1;
	Complex c2;
	Complex();

	return 0;

}
```
![image](https://user-images.githubusercontent.com/110090496/230028062-cda2846c-245f-4075-bc00-c7b9c9db45cf.png)

생성자에서 static 변수를 초기화하면 객체가 생성될때마다 static 변수가 초기화되므로 **생성자에서 static 변수를 초기화하면 안된다**

**int Simple::simCnt =0;** 의 형태의 초기화 문법이 별도로 정의되어 있다.

### static 멤버변수의 또 다른 접근 방법
private 멤버변수로 선언되면 해당 클래스들의 객체들만 접근이 가능하지만, public으로 선언되면 어디서든 접근이 가능하다.
위의 코드에서 main을 다음과 같이 수정한 뒤 실행시키면 
```c++
int main(void)
{
	cout << Simple::simCnt << "번째 Simple 객체" << endl;
	Simple s1;
	Simple s2;

	cout << Simple::simCnt << "번째 Simple 객체" << endl;
	cout << s1.simCnt << "번째 Simple 객체" << endl;
	cout << s2.simCnt << "번째 Simple 객체" << endl;

	return 0;

}
```
다음과 같은 결과가 나온다.

![image](https://user-images.githubusercontent.com/110090496/230031219-ca838858-8d4d-4942-95a6-0cb4bce41b54.png)
#### 위의 결과로 알 수  있는 것 (public static 맴버)
- static 변수는 객체끼리 공유된다
- 객체를 통해 static 변수 접근 가능
- 클래스::변수이름 으로 접근가능 (추천방법)

### static 멤버함수
**static 맴버함수 내에서는 static 멤버 변수와 static 멤버함수만 호출 가능하다.**
