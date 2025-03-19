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
    virtual ~PizzaBuilder() = default;
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