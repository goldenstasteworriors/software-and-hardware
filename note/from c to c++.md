# c语言到c++

## 程序框架

#include<iostream>

(#include<>)(如果要调用其他库)

using namespace std;

int main()

{





return 0;

}

## 输入输出

### 输入

#### cin

一般用法：cin>>a>>b;

注：不用加\n也不用加endl；一次要输入多个变量时，无论是用空格还是用回车间隔都可以

####  cout

一般用法：cout<<a<<" "<<b<<endl;

注：

1. 记得加“ ”，中间有多少空格都可以
2. cout是从左到右计算的
3. 可以吧cin和cout看做两扇门，要出去箭头指向门外，要进来箭头指向门内
4. 上下两个cout，则上面那次cout的值在前

##### 关于char

不同于c语言中，c++似乎char和int有本质区别，最明显的一点是想输出符号就只能转换成char型，我们可以多定义一个char类型的变量，并把我们原有的int类型的变量给它赋值以实现这一点。如有int a=52;想输出52对应的字符，需要:char b;b=a;cout<<b<<endl;(或者趁我们现在操作的数字较小可以用强制类型转换)
