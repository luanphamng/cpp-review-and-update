#include <iostream>
#include <string>

class BaseComponent;

class Mediator {
    public:
    virtual void Notify(BaseComponent *sender, std::string event) const = 0;
};

class BaseComponent {
    protected:
        Mediator *mediator_;

    public:
        BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator) {
        }

        void setMediator(Mediator *mediator) {
            this->mediator_ = mediator;
        }
};

class Component1 : public BaseComponent {
    public:
        void do11() {
            std::cout << "Component 1 does say 1" << std::endl;
            this->mediator_->Notify(this, "11");
        }

        void do12() {
            std::cout << "Component 1 does say 2" << std::endl;
            this->mediator_->Notify(this, "12");
        }
};

class Component2 : public BaseComponent {
    public:
        void do21() {
            std::cout << "Component 2 does say 21" << std::endl;
            this->mediator_->Notify(this, "21");
        }

        void do22() {
            std::cout << "Component 2 does say 22" << std::endl;
            this->mediator_->Notify(this, "22");
        }
};

class ConcreteMediator : public Mediator {
    private:
        Component1 *component1_;
        Component2 *component2_;

    public:
        ConcreteMediator(Component1 *c1, Component2 *c2) : component1_(c1), component2_(c2) {
            this->component1_->setMediator(this);
            this->component2_->setMediator(this);
        }

        void Notify(BaseComponent *sender, std::string event) const override {
            if (event == "11") {
                std::cout << "Mediator reacts on 1 and triggers following operations: " << std::endl;
                this->component2_->do21();
            }

            if (event == "22") {
                std::cout << "Mediator reacts on 2 and triggers following operations: " << std::endl;
                this->component1_->do12();
                this->component2_->do21();
            }
        }
};


void ClientCode() {
    Component1 *c1 = new Component1;
    Component2 *c2 = new Component2;

    ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
    std::cout << "Client triggers operation 11." << std::endl;
    c1->do11();
    std::cout << std::endl;
    std::cout << "Client triggers operation 22." << std::endl;
    c2->do22();

    delete c1;
    delete c2;
    delete mediator;
}

int main() {
    ClientCode();
    return 0;
}