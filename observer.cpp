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