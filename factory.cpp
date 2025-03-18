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