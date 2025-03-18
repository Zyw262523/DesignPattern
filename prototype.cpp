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
    virtual ~Prototype() = default;
     [[nodiscard]] virtual unique_ptr<Prototype> clone() const = 0;
    virtual void print() const = 0;
};

// 具体原型类
class ConcretePrototype : public Prototype {
public:
    explicit  ConcretePrototype(string name) : name(std::move(name)) {}

     [[nodiscard]] unique_ptr<Prototype> clone() const override {// 实现克隆方法
        return make_unique<ConcretePrototype>(*this);
    }

    void print() const override {   // 实现打印方法
        cout << "ConcretePrototype [Name: " << name << "]" << endl;
    }

    void setName(const string& newName) {   // 设置名称
        name = newName;
    }

private:
    string name;
};

// 客户端代码
int main() {
    const auto prototype = make_unique<ConcretePrototype>("Prototype1");// 创建原型对象
    cout << "原型 :";
    prototype->print();

    const auto clone = prototype->clone();// 克隆对象
    cout << "克隆 :";
    clone->print();


    dynamic_cast<ConcretePrototype*>(clone.get())->setName("Clone1");// 修改克隆对象的名称
    cout << "修改的克隆 ";
    clone->print();

    cout << "原型 ";// 打印原始对象，验证是否被修改
    prototype->print();

    return 0;
}