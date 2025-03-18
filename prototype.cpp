//
// Created by zyw on 25-3-18.
//

#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Prototype接口
class Prototype {
public:
    virtual ~Prototype() {}
    virtual unique_ptr<Prototype> clone() const = 0;
    virtual void print() const = 0;
};

// 具体原型类
class ConcretePrototype : public Prototype {
public:
    ConcretePrototype(const string& name) : name(name) {}

    // 实现克隆方法
    unique_ptr<Prototype> clone() const override {
        return make_unique<ConcretePrototype>(*this);
    }

    // 实现打印方法
    void print() const override {
        cout << "ConcretePrototype [Name: " << name << "]" << endl;
    }

    // 设置名称
    void setName(const string& newName) {
        name = newName;
    }

private:
    string name;
};

// 客户端代码
int main() {
    // 创建原型对象
    unique_ptr<Prototype> prototype = make_unique<ConcretePrototype>("Prototype1");
    cout << "Original ";
    prototype->print();

    // 克隆对象
    unique_ptr<Prototype> clone = prototype->clone();
    cout << "Cloned ";
    clone->print();

    // 修改克隆对象的名称
    dynamic_cast<ConcretePrototype*>(clone.get())->setName("Clone1");
    cout << "Modified Cloned ";
    clone->print();

    // 打印原始对象，验证是否被修改
    cout << "Original ";
    prototype->print();

    return 0;
}