# OOP Final Project 8-1Object Serialization

南子谦 信息与计算科学 3210104676

**Warning: the codes can run in Visual Studio for Windows, might be sensitive to Compilers!**

### Header files:

`CustomizedClass.h` ：实现了自定义类，及序列化所必需的四个函数
`RFC_4648.h` ：包含着RFC_4648 Base64的编码方法
`Serialization.h` ：包含两种方法Serialization和Deserialization的函数声明
`Serialization.cpp` ：包含两种方法Serialization和Deserialization的函数实现
`tinyxml2.h` ：开源项目tinyxml2.h的头文件，该项目主要用于生成xml文件中的一行数据
`tinyxml2.cpp` ： 开源项目tinyxml2.h的头文件的实现
`TypeJudging.h` ：用于判断模板参数的类型，对于不同的模板参数我们需要不同的序列化策略

### Main file:

`main.cpp` ： 包含了测试实例，内容覆盖Arithmetic, containers, 自定义类的两种Serialization和Deserialization

`run.sh` use `run` in your terminal to run the test!

## Result

1. bin serialization.

ps. the information about the sizes of containers are used to debug.

```
Container class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >'s size: 18
Container class std::vector<struct std::pair<int,double>,class std::allocator<struct std::pair<int,double> > >'s size: 1
Container class std::set<int,struct std::less<int>,class std::allocator<int> >'s size: 1
Container class std::map<int,double,struct std::less<int>,class std::allocator<struct std::pair<int const ,double> > >'s size: 1
Container class std::map<int,double,struct std::less<int>,class std::allocator<struct std::pair<int const ,double> > >'s size: 1
idx: 0
name: I love Elden ring.
data[].fisrt= 0 data[].second= 100
 data3[]= 100
data4[].fisrt= 0 data4[].second= 100
```

2. xml serialization

```
<?xml version="1.0" encoding="UTF-8"?>
<XMLSerializaiton>
    <class>
        <hasOutputMethod: Arithmetic or char>0</hasOutputMethod: Arithmetic or char>
        <string>I love Elden ring.</string>
        <container>
            <class>
                <hasOutputMethod: Arithmetic or char>0</hasOutputMethod: Arithmetic or char>
                <hasOutputMethod: Arithmetic or char>100</hasOutputMethod: Arithmetic or char>
            </class>
        </container>
        <container>
            <hasOutputMethod: Arithmetic or char>100</hasOutputMethod: Arithmetic or char>
        </container>
        <container>
            <class>
                <hasOutputMethod: Arithmetic or char>0</hasOutputMethod: Arithmetic or char>
                <hasOutputMethod: Arithmetic or char>100</hasOutputMethod: Arithmetic or char>
            </class>
        </container>
        <container>
            <class>
                <hasOutputMethod: Arithmetic or char>0</hasOutputMethod: Arithmetic or char>
                <hasOutputMethod: Arithmetic or char>100</hasOutputMethod: Arithmetic or char>
            </class>
        </container>
    </class>
</XMLSerializaiton>

```

### Bonus

I've completed both bonus.

- Support the serialization of smart pointers, e.g., std::unique_ptr.

  - in file `TypeJudging.h`, the following code ensures the support for smart pointers.
  - ```
    template<typename T>
    class isPointer {
        template<typename C>
        static constexpr true_type check(unique_ptr<C>);

        template<typename C>
        static constexpr true_type check(shared_ptr<C>);

        static constexpr false_type check(...);

        typedef decltype(check(declval<T>())) type;
    public:
        static constexpr bool value = type::value;
    };
    ```
- Use binary-to-text encoding/decoding (base64) to implement a binary mode of XML serialization.

  - in main.cpp , the you can uncomment the following code and test it yourself
  - ```
    //Part 2.2 bin mode xml serialization
        //xmlSerial::Serialization::Serialize(a, "XMLSerializaiton","MyClass_a.xml",1);
        //xmlSerial::Deserialization::Deserialize(b, "MyClass_a.xml",1);
    ```

### 实验心得

本次实验不仅需要基本的模板知识，还涉及到了在编译阶段对模板参数类型的判定。原来不一定要程序运行阶段才能进行运算，在编译阶段已能进行一些逻辑判断，例如在TypeJudging.h中的true_Type和False_Type。当然很多知识我是从互联网上获得的，实验代码中也多多少少受到了他们的启发。

我在上高级数据结构这门课时，我遇到了传入的模板参数是自定义类时，如何判断它是否有某函数对象的问题。而在这次实验学到的东西能够完美解决。

其次，这次实验也让我对生活中我们常常能见到的.xml .json文件更加熟悉了，也学习了tinyxml2这一强大了工具。有这个工具，我们就能高效利用xml文件配置我们自己的一些项目了！