# 利用对象数组，计算10个顶点组成折线的长度

## 问题描述

定义一个Cat类，拥有静态数据成员numOfCats，记录Cat的个体数目；静态成员函数getNumOfCats()，读取numOfCats。设计程序测试这个类，体会静态数据成员和静态成员函数的用法。

主函数如下：

```c++
int main()
{
    Cat c;
    cout<<"Num:"<<Cat::getNumOfCats()<<endl;
    Cat carr[4];
    cout<<"Num:"<<Cat::getNumOfCats()<<endl;
    return 0;
}
```

参考的输出结果为：

```
Num:1
Num:5
```

## 输入形式

无。

## 输出形式

参考的输出：

```
Num:1
Num:5
```