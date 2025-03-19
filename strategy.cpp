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