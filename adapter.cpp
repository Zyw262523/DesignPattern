#include <iostream>

using namespace std;

// 目标接口（客户端期望的接口）
class Target {
public:
    virtual ~Target() = default;
    virtual void request() const = 0;
};

// 被适配者（需要适配的类）
class Adaptee {
public:
    void specificRequest() const {
        cout << "Adaptee's specific request." << endl;
    }
};

// 适配器类
class Adapter final: public Target {
public:
    explicit Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}

    void request() const override {
        adaptee_->specificRequest(); // 调用被适配者的方法
    }

private:
    Adaptee* adaptee_;
};

// 客户端代码
void clientCode(const Target* target) {
    target->request();
}

int main() {
    auto* adaptee = new Adaptee();// 创建被适配者对象
    const auto* adapter = new Adapter(adaptee);// 创建适配器对象，将被适配者对象传入

    cout << "Client: Using the adapter to call the request method:" << endl; // 客户端调用适配器的接口
    clientCode(adapter);

    delete adaptee;// 释放内存
    delete adapter;
    return 0;
}