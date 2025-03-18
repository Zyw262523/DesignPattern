#include <iostream>

using namespace std;

// 单例类
class Singleton {
public:
    // 删除拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
private:
    // 私有构造函数，防止外部实例化
    Singleton() {
        cout << "Singleton instance created!" << endl;
    }
public:
    // 获取单例实例的静态方法
    static Singleton& getInstance() {
        static Singleton instance;// 局部静态变量，线程安全
        return instance;
    }

    void doSomething() {
        cout << "Doing something!" << endl;
    }

    // 析构函数
    ~Singleton() {
        cout << "Singleton instance destroyed!" << endl;
    }
};

// 客户端代码
int main() {
    Singleton& singleton = Singleton::getInstance();// 获取单例实例
    singleton.doSomething();// 调用单例方法
    const Singleton& anotherSingleton = Singleton::getInstance();// 再次获取单例实例
    if (&singleton == &anotherSingleton) { // 检查是否为同一个实例
        cout << "Both references point to the same instance!" << endl;
    }
    return 0;
}