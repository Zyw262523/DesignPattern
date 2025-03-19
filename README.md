# 设计模式



## 设计模式原则

1. **依赖倒置原则**
   - 高层模块(稳定)不应该依赖于底层模块(变化),二者都应该依赖于抽象(稳定)
   - 抽象(稳定)不应该依赖于实现细节(变化),实现细节应该依赖于抽象(稳定)
2. **开闭原则**
   - 对扩展开放，对更改关闭
   - 类模块应该是可扩展的，但是不可修改
3. **接口隔离原则**
   - 使用多个专门的接口，而不使用单一的总接口，不应该强迫客户程序依赖它们不用的方法
   - 接口尽量细化，同时接口中的方法尽量少并且完备。
4. **里氏替换原则**
   - 子类可以扩展父类的功能，但不能改变父类原有的功能
5. **单一职责原则**
   - 不要存在多余一个导致类变更的原因。一个类应该应该只负责一项职责。
   - 每个应该实现单一职责，否则就应该把类拆分，便于后期的维护
6. **迪米特法则**
   - 是指一个对象应该对其他对象保持最少的了解，又叫最少知道原则，尽量降低类与类之间的耦合。迪米特原则主要强调只和朋友交流，不和陌生人说话
7. **合成复用原则**
   - 组合优于继承



## 创建型模式

*它们主要关注对象的创建过程，旨在以灵活、可维护和可复用的方式来创建对象*



### 原型模式

**概念**

这种模式是实现了一个原型接口，该接口用于创建当前对象的克隆。当直接创建对象的代价比较大时，则采用这种模式。

**意图**：使用原型实例指定要创建对象的种类，并通过拷贝这些原型创建新的对象。

**组成部分**

1. **Prototype（原型接口）**：
   定义了克隆自身的方法，通常是一个抽象类或接口。
2. **ConcretePrototype（具体原型类）**：
   实现了`Prototype`接口，提供克隆自身的具体实现。
3. **Client（客户端）**：
   使用原型对象的克隆方法来创建新对象，而无需了解对象的具体类型。

**优点**：

- 性能提高
- 避免构造函数的约束

**缺点**:

- 配备克隆方法需要全面考虑类的功能，对已有类可能较难实现，特别是处理不支持串行化的间接对象或含有循环结构的引用时
- 必须实现 `Cloneable` 接口

**例子**

```c++
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
```



### 单例模式

**概念**

这种模式涉及到一个单一的类，该类负责创建自己的对象，同时确保只有单个对象被创建

**意图**：确保一个类只有一个实例，并提供一个全局访问点来访问该实例。

**组成部分**

1. 构造，移动构造等函数是私有
2. 一个Instance接口

**优点**

- 内存中只有一个实例，减少内存开销，尤其是频繁创建和销毁实例时（如管理学院首页页面缓存）。
- 避免资源的多重占用（如写文件操作）。

**缺点**

- 没有接口，不能继承。
- 与单一职责原则冲突，一个类应该只关心内部逻辑，而不关心实例化方式。

**例子**

```c++
#include <iostream>

using namespace std;

// 单例类
class Singleton {
private:
    // 私有构造函数，防止外部实例化
    Singleton() {
        cout << "Singleton instance created!" << endl;
    }

    // 删除拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // 获取单例实例的静态方法
    static Singleton& getInstance() {
        // 局部静态变量，线程安全
        static Singleton instance;
        return instance;
    }

    // 示例方法
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
    // 获取单例实例
    Singleton& singleton = Singleton::getInstance();

    // 调用单例方法
    singleton.doSomething();

    // 再次获取单例实例
    Singleton& anoherSingleton = Singleton::getInstance();

    // 检查是否为同一个实例
    if (&singleton == &anoherSingleton) {
        cout << "Both references point to the same instance!" << endl;
    }

    return 0;
}
```

**特殊**

在C++11及更高版本中，局部静态变量的初始化是**线程安全**的。

局部静态变量在函数第一次被调用时初始化，并且在程序结束时销毁。C++11标准规定，局部静态变量的初始化是线程安全的，

- **线程安全初始化**：当多个线程同时调用包含局部静态变量的函数时，编译器会确保只有一个线程执行初始化，其他线程会等待初始化完成。
- **初始化只发生一次**：局部静态变量的初始化只会发生一次，即使在多线程环境下也是如此。



### 工厂模式

**概念**

工厂模式提供了一种创建对象的方式，而无需指定要创建的具体类

**类型**

**1、简单工厂模式（Simple Factory Pattern）**：

- 简单工厂模式不是一个正式的设计模式，但它是工厂模式的基础。它使用一个单独的工厂类来创建不同的对象，根据传入的参数决定创建哪种类型的对象。

**2、工厂方法模式（Factory Method Pattern）**：

- 工厂方法模式定义了一个创建对象的接口，但由子类决定实例化哪个类。工厂方法将对象的创建延迟到子类。

**3、抽象工厂模式（Abstract Factory Pattern）**：

- 抽象工厂模式提供一个创建一系列相关或互相依赖对象的接口，而无需指定它们具体的类。

**意图**：定义一个创建对象的接口，让其子类决定实例化哪一个具体的类。工厂模式使对象的创建过程延迟到子类。

**组成部分**

对象的创建过程在子类中实现

**优点**

1. 调用者只需要知道对象的名称即可创建对象。
2. 扩展性高，如果需要增加新产品，只需扩展一个工厂类即可。
3. 屏蔽了产品的具体实现，调用者只关心产品的接口。

**缺点**

每次增加一个产品时，都需要增加一个具体类和对应的工厂，使系统中类的数量成倍增加，增加了系统的复杂度和具体类的依赖。

**例子**

1.工厂

```c++
#include <iostream>
#include <memory>

using namespace std;

// 产品基类
class Product {
public:
    virtual ~Product() {}
    virtual void use() = 0;
};

// 具体产品类A
class ProductA final: public Product {
public:
    void use() override {
        cout << "Using ProductA!" << endl;
    }
};

// 具体产品类B
class ProductB final: public Product {
public:
    void use() override {
        cout << "Using ProductB!" << endl;
    }
};

// 工厂类
class Factory {
public:
    static unique_ptr<Product> createProduct(const string& type) { // 创建产品
        if (type == "A") {
            return make_unique<ProductA>();
        } else if (type == "B") {
            return make_unique<ProductB>();
        } else {
            throw invalid_argument("Unknown product type");
        }
    }
};

int main() {
    try {
        const auto productA = Factory::createProduct("A");// 使用工厂创建产品A
        productA->use();

        const auto productB = Factory::createProduct("B");// 使用工厂创建产品B
        productB->use();

        const auto productC = Factory::createProduct("C");// 尝试创建未知类型的产品
        productC->use();
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
```

### 建造者模式

**概念**

它的主要目的是将一个复杂对象的构建过程与其表示相分离，从而可以创建具有不同表示形式的对象

**意图**

将一个复杂的构建过程与其表示相分离，使得同样的构建过程可以创建不同的表示。

**组成部分**

- **建造者**：创建并提供实例。
- **导演**：管理建造出来的实例的依赖关系和控制构建过程。

**优点**

- 分离构建过程和表示，使得构建过程更加灵活，可以构建不同的表示。
- 可以更好地控制构建过程，隐藏具体构建细节。
- 代码复用性高，可以在不同的构建过程中重复使用相同的建造者。

**缺点**

- 如果产品的属性较少，建造者模式可能会导致代码冗余。
- 增加了系统的类和对象数量。

**例子**

```c++
#include <iostream>
#include <string>
#include <memory>

using namespace std;

// 产品类
class Pizza {
public:
    void setDough(const string& dough) {
        dough_ = dough;
    }

    void setSauce(const string& sauce) {
        sauce_ = sauce;
    }

    void setTopping(const string& topping) {
        topping_ = topping;
    }

    void showPizza() const {
        cout << "Pizza with " << dough_ << " dough, "<< sauce_ << " sauce, and "<< topping_ << " topping." << endl;
    }

private:
    string dough_;
    string sauce_;
    string topping_;
};

// 抽象建造者
class PizzaBuilder {
public:
    virtual ~PizzaBuilder() {}
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
    virtual unique_ptr<Pizza> getPizza() = 0;
};

// 具体建造者1：经典披萨
class ClassicPizzaBuilder final: public PizzaBuilder {
public:
    ClassicPizzaBuilder() {
        pizza_ = make_unique<Pizza>();
    }

    void buildDough() override {
        pizza_->setDough("thin crust");
    }

    void buildSauce() override {
        pizza_->setSauce("tomato");
    }

    void buildTopping() override {
        pizza_->setTopping("cheese");
    }

    unique_ptr<Pizza> getPizza() override {
        return move(pizza_);
    }

private:
    unique_ptr<Pizza> pizza_;
};

// 具体建造者2：海鲜披萨
class SeafoodPizzaBuilder final: public PizzaBuilder {
public:
    SeafoodPizzaBuilder() {
        pizza_ = make_unique<Pizza>();
    }

    void buildDough() override {
        pizza_->setDough("thick crust");
    }

    void buildSauce() override {
        pizza_->setSauce("garlic");
    }

    void buildTopping() override {
        pizza_->setTopping("shrimp");
    }

    unique_ptr<Pizza> getPizza() override {
        return move(pizza_);
    }

private:
    unique_ptr<Pizza> pizza_;
};

// 导演类
class PizzaDirector {
public:
    PizzaDirector() = default;
    void setBuilder(PizzaBuilder* builder) {
        builder_ = builder;
    }
    void constructPizza() const{
        builder_->buildDough();
        builder_->buildSauce();
        builder_->buildTopping();
    }

private:
    PizzaBuilder* builder_;
};

// 客户端代码
int main() {
    // 创建具体建造者
    ClassicPizzaBuilder classicBuilder;
    SeafoodPizzaBuilder seafoodBuilder;

    // 创建导演
    PizzaDirector director;

    // 制作经典披萨
    director.setBuilder(&classicBuilder);
    director.constructPizza();
    unique_ptr<Pizza> classicPizza = classicBuilder.getPizza();
    classicPizza->showPizza();

    // 制作海鲜披萨
    director.setBuilder(&seafoodBuilder);
    director.constructPizza();
    unique_ptr<Pizza> seafoodPizza = seafoodBuilder.getPizza();
    seafoodPizza->showPizza();

    return 0;
}
```



## 结构型模式

*结构型模式（Structural Patterns）是设计模式中的一种类型，主要用于**处理对象之间的组合关系**，以确保系统在结构上更加灵活、可扩展和可维护。结构型模式关注如何将类或对象组合成更大的结构，同时保持这些结构的灵活性和高效性。*

### 适配器模式

**概念**

它通过一个中间件（适配器）将一个类的接口转换成客户期望的另一个接口，使原本不能一起工作的类能够协同工作

**意图**

将一个类的接口转换为另一个接口，使得原本不兼容的类可以协同工作。

**组成部分**

适配器通过继承或依赖现有对象，并实现所需的目标接口。

**优点**

- 促进了类之间的协同工作，即使它们没有直接的关联。
- 提高了类的复用性。
- 增加了类的透明度。
- 提供了良好的灵活性。

**缺点**

- 过度使用适配器可能导致系统结构混乱，难以理解和维护。
- 在Java中，由于只能继承一个类，因此只能适配一个类，且目标类必须是抽象的。

**例子**

```c++
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
```



## 行为模式

*行为模式（Behavioral Patterns）是设计模式中的一种类型，主要用于**处理对象之间的职责分配和通信**，以确保系统在行为上更加灵活、可扩展和可维护。行为模式关注对象之间的交互方式，定义对象如何协作以及如何分配职责。*

### 策略模式

**概念**

在策略模式（Strategy Pattern）中一个类的行为或其算法可以在运行时更改。这种类型的设计模式属于行为型模式

**意图**

将每个算法封装起来，使它们可以互换使用。

**组成部分**

- **策略接口**：规定了所有策略类必须实现的方法。
- **具体策略类**：实现了策略接口，包含具体的算法实现。

**优点**

1. **算法切换自由**：可以在运行时根据需要切换算法。
2. **避免多重条件判断**：消除了复杂的条件语句。
3. **扩展性好**：新增算法只需新增一个策略类，无需修改现有代码。

**缺点**

1. **策略类数量增多**：每增加一个算法，就需要增加一个策略类。
2. **所有策略类都需要暴露**：策略类需要对外公开，以便可以被选择和使用。

**例子**

```c++
#include <iostream>
#include <cstdint>

// 策略接口
class Pay {
public:
    virtual void pay(double money) const = 0;
    virtual ~Pay() = default;
};

// 具体策略：信用卡支付
class CreditCardPay final: public Pay {
public:
    void pay(const double money) const override {
        std::cout <<"Card Pay : "<< money << "\n";
    }
};

// 具体策略：支付宝支付
class AlipayPay final: public Pay {
public:
    void pay(const double money) const override {
        std::cout <<"Alipay Pay : "<< money << "\n";
    }
};

// 具体策略：微信支付
class WechatPay final: public Pay {
public:
    void pay(const double money) const override {
        std::cout <<"Wechat Pay : "<< money << "\n";
    }
};

// 上下文类
class PayContext {
public:
    explicit PayContext(Pay* strategy):myPay(strategy){}
    ~PayContext() {
        delete myPay;
    };

    void setPay(Pay* strategy) {
        myPay = strategy;
    }
    void pay(const double money) const {
        if (myPay) {
            myPay->pay(money);
        }else {
            std::cerr << "Payment strategy not set!" << std::endl;
        }
    }
private:
    Pay * myPay;
};

int main() {
    Pay* creditCard = new CreditCardPay();
    Pay* alipay = new AlipayPay();
    Pay* wechat = new WechatPay();

    const PayContext pay1(creditCard);
    const PayContext pay2(alipay);
    const PayContext pay3(wechat);

    pay1.pay(123);
    pay2.pay(123);
    pay3.pay(123);

    return 0;
}
```



### 观察者模式

**概念**

它定义了一种一对多的依赖关系，当一个对象的状态发生改变时，其所有依赖者都会收到通知并自动更新

**意图**

创建了对象间的一种一对多的依赖关系，当一个对象状态改变时，所有依赖于它的对象都会得到通知并自动更新。。

**实现方式**

- **定义观察者接口**：包含一个更新方法。
- **创建具体观察者**：实现观察者接口，定义接收到通知时的行为。
- **定义主题接口**：包含添加、删除和通知观察者的方法。
- **创建具体主题**：实现主题接口，管理观察者列表，并在状态改变时通知它们。

**优点**

- **抽象耦合**：观察者和主题之间是抽象耦合的。
- **触发机制**：建立了一套状态改变时的触发和通知机制。

**缺点**

- **性能问题**：如果观察者众多，通知过程可能耗时。
- **循环依赖**：可能导致循环调用和系统崩溃。
- **缺乏变化详情**：观察者不知道主题如何变化，只知道变化发生。

**例子**

```c++
#include <string>
#include <vector>
#include <iostream>

// 观察者接口
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

// 被观察者
class Subject {
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        std::erase(observers, observer);
    }

    void notify(const std::string& message) const{
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }

private:
    std::vector<Observer*> observers;
};


// 具体观察者：邮件通知
class EmailObserver final: public Observer {
public:
    explicit  EmailObserver(std::string email) : email(std::move(email)) {}

    void update(const std::string& message) override {
        std::cout << "Email to " << email << ": " << message << std::endl;
    }

private:
    std::string email;
};

// 具体观察者：短信通知
class SmsObserver final: public Observer {
public:
    explicit SmsObserver(std::string phone) : phone(std::move(phone)) {}

    void update(const std::string& message) override {
        std::cout << "SMS to " << phone << ": " << message << std::endl;
    }

private:
    std::string phone;
};

int main() {
    Subject subject;
    EmailObserver emailObserver("alice@example.com");
    SmsObserver smsObserver("1234567890");

    // 注册观察者
    subject.attach(&emailObserver);
    subject.attach(&smsObserver);

    subject.notify("Hello, World!");            // 模拟状态变化并通知观察者
    subject.detach(&smsObserver);                           // 移除一个观察者
    subject.notify("Goodbye!");                 // 再次通知观察者
    return 0;
}
```


