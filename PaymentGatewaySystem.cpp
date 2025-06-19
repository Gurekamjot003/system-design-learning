#include<bits/stdc++.h>
using namespace std;
 
class PaymentRequest{
public:
    string sender;
    string reciever;
    double amount;
    string currency;
    bool is_subscription;
    int interval;
    int frequency;

    PaymentRequest(string sender, string reciever, double amount, string currency, bool is_subscription, int interval = 0, int frequency = 0){
        this->sender = sender;
        this->reciever = reciever;
        this->amount = amount;
        this->currency = currency;
        this->is_subscription = is_subscription;
        this->interval = interval;
        this->frequency = frequency;
    }
};



class BankingSystem{
public:
    virtual bool process_payment(double amount) = 0;
    virtual ~BankingSystem(){}
};

class PaytmBankingSystem: public BankingSystem{
public:
    bool process_payment(double amount) override{
        cout<<"[BankingSystem - Paytm] Processing payment of "<<amount<<"..."<<endl;
        int r = rand()%100;
        return r<70;
    }
};

class RazorpayBankingSystem: public BankingSystem{
public:
    bool process_payment(double amount) override{
        cout<<"[BankingSystem - Razorpay] Processing payment of "<<amount<<"..."<<endl;
        int r = rand()%100;
        return r<70;
    }
};

class PaymentGateway{
protected:
    BankingSystem* banking_system;

public:
    PaymentGateway(){
        banking_system = NULL;
    }

    virtual ~PaymentGateway(){
        delete banking_system;
    }

    virtual bool process_payment(PaymentRequest* request){
        if(!validate_payment(request)){
            cout<<"[PaymentGateway] Validation failed for "<<request->sender<<endl;
            return false;
        }
        if(!initiate_payment(request)){
            cout<<"[PaymentGateway] Initiation failed for "<<request->sender<<endl;
            return false;
        }
        if(!confirm_payment(request)){
            cout<<"[PaymentGateway] Confirmation failed for "<<request->sender<<endl;
            return false;
        }
        
        return true;
    }

    virtual bool validate_payment(PaymentRequest* request) = 0;
    virtual bool initiate_payment(PaymentRequest* request) = 0;
    virtual bool confirm_payment(PaymentRequest* request) = 0;
};

class PaytmGateway: public PaymentGateway{
public:
    PaytmGateway(){
        banking_system = new PaytmBankingSystem();
    }

    bool validate_payment(PaymentRequest* request) override{
        cout<<"[Paytm] Validating payment for "<<request->sender<<endl;
        if(request->amount<=0 or request->currency != "INR") return false;
        return true;
    }

    bool initiate_payment(PaymentRequest* request) override{
        cout<<"[Paytm] Initiating payment of "<<request->amount<<" "<<request->currency<<" for "<<request->sender<<endl;
        return banking_system->process_payment(request->amount);
    }

    bool confirm_payment(PaymentRequest* request) override{
        cout<<"[Paytm] Confirming payment for "<<request->sender<<endl;
        return true;
    }
};

class RazorpayGateway: public PaymentGateway{
public:
    RazorpayGateway(){
        banking_system = new RazorpayBankingSystem();
    }

    bool validate_payment(PaymentRequest* request) override{
        cout<<"[Razorpay] Validating payment for "<<request->sender<<endl;
        if(request->amount<=0) return false;
        return true;
    }

    bool initiate_payment(PaymentRequest* request) override{
        cout<<"[Razorpay] Initiating payment of "<<request->amount<<" "<<request->currency<<" for "<<request->sender<<endl;
        return banking_system->process_payment(request->amount);
    }

    bool confirm_payment(PaymentRequest* request) override{
        cout<<"[Razorpay] Confirming payment for "<<request->sender<<endl;
        return true;
    }  
};

//enum
enum class RetryStrategyType{
    LINEAR,
    EXPONENTIAL
};

//abstract
class IRetryStrategy{
public:
    virtual int get_wait_time(int attempt) = 0;
    virtual ~IRetryStrategy(){}
};

class LinearRetryStrategy: public IRetryStrategy{
private:
    int fixed_wait_time;

public:
    LinearRetryStrategy(int wait_ms = 1000){
        this->fixed_wait_time = wait_ms;
    }

    int get_wait_time(int attempt) override{
        return fixed_wait_time;
    }
};

class ExponentialRetryStrategy: public IRetryStrategy{
private:
    int base_wait_time;

public:
    ExponentialRetryStrategy(int wait_ms = 1000){
        this->base_wait_time = wait_ms;
    }

    int get_wait_time(int attempt){
        return base_wait_time<<(attempt-1);
    }
};

//singleton
class RetryStrategyFactory{
private:
    static RetryStrategyFactory* instance;
    RetryStrategyFactory(){}

public:

    static RetryStrategyFactory* get_instance(){
        if(!instance) instance = new RetryStrategyFactory();
        return instance;
    }
    IRetryStrategy* get_retry_strategy(RetryStrategyType type){
        if(type == RetryStrategyType::LINEAR){
            return new LinearRetryStrategy();
        }
        else{
            return new ExponentialRetryStrategy();
        }
    }
};

RetryStrategyFactory* RetryStrategyFactory::instance = NULL;

class PaymentGatewayProxy: public PaymentGateway{
private:   
    PaymentGateway* real_payment_gateway;
    IRetryStrategy* retry_strategy;
    int max_retries;

public: 
    PaymentGatewayProxy(PaymentGateway* gateway, int max_retries, RetryStrategyType type){
        this->real_payment_gateway = gateway;
        this->max_retries = max_retries;
        this->retry_strategy = RetryStrategyFactory::get_instance()->get_retry_strategy(type);
    }

    ~PaymentGatewayProxy(){
        delete real_payment_gateway;
        delete retry_strategy;
    }

    bool process_payment(PaymentRequest* request) override{
        bool result = false;
        for(int attempt = 1; attempt<=max_retries; attempt++){
            if(attempt>1){
                cout<<"[Proxy] Waiting for "<<retry_strategy->get_wait_time(attempt)<<" ms before retrying."<<endl;
                this_thread::sleep_for(chrono::milliseconds(retry_strategy->get_wait_time(attempt)));
                cout<<"[Proxy] Retrying payment(attempt "<<attempt<<") for "<<request->sender<<endl;
            }
            result = real_payment_gateway->process_payment(request);
            if(result) break;
        }

        if(!result){
            cout<<"[Proxy] Payment failed after "<<max_retries<<" attempts for "<<request->sender<<endl;
        }
        return result;
    }

    bool validate_payment(PaymentRequest* request) override{
        return real_payment_gateway->validate_payment(request);
    }

    bool initiate_payment(PaymentRequest* request) override{
        return real_payment_gateway->initiate_payment(request);
    }

    bool confirm_payment(PaymentRequest* request){
        return real_payment_gateway->confirm_payment(request);
    }
};

enum class GatewayType{
    PAYTM,
    RAZORPAY
};

class GatewayFactory{
private:
    static GatewayFactory* instance;
    GatewayFactory(){}

public:
    static GatewayFactory* get_instance(){
        if(!instance){
            instance = new GatewayFactory();
        }
        return instance;
    }

    PaymentGateway* get_gateway(GatewayType gateway_type){
        if(gateway_type == GatewayType::PAYTM){
            return new PaymentGatewayProxy(new PaytmGateway(), 3, RetryStrategyType::LINEAR);
        }
        else{
            return new PaymentGatewayProxy(new RazorpayGateway(), 3, RetryStrategyType::EXPONENTIAL);
        }
    }
};

GatewayFactory* GatewayFactory::instance = NULL;

class PaymentService{
private:
    static PaymentService* instance;
    PaymentGateway* gateway;

    PaymentService(){
        gateway = NULL;
    }

    ~PaymentService(){
        delete gateway;
    }

public:
    static PaymentService* get_instance(){
        if(!instance){
            instance = new PaymentService();
        }
        return instance;
    }

    void set_gateway(PaymentGateway* gateway){
        if(this->gateway) delete this->gateway;
        this->gateway = gateway;
    }

    bool process_payment(PaymentRequest* request){
        if(!gateway){
            cout<<"[PaymentService] No payment gateway selected"<<endl;
            return false;
        }
        if(request->is_subscription){
            int day = 1;
            int i = 1;
            while(i<=request->frequency){
                if(day%request->interval == 0){
                    cout<<"\n\n[PaymentService] Processing subscription payment on day "<<day<<" for "<<request->sender<<" of "<<request->amount<<" "<<i<<"th time"<<endl;
                    gateway->process_payment(request);
                    i++;
                }
                day++;
            }
        }
        else return gateway->process_payment(request);
    }
};

PaymentService* PaymentService::instance = NULL;

class PaymentController{
private:
    static PaymentController* instance;
    PaymentController(){}

public:
    static PaymentController* get_instance(){
        if(!instance){
            instance = new PaymentController();
        }
        return instance;
    }

    bool handle_payment(GatewayType type, PaymentRequest* request){
        PaymentGateway* payment_gateway = GatewayFactory::get_instance()->get_gateway(type);
        PaymentService::get_instance()->set_gateway(payment_gateway);

        return PaymentService::get_instance()->process_payment(request);
    }
};

PaymentController* PaymentController::instance = NULL;

int main(){
    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    PaymentRequest* req1 = new PaymentRequest("Gurekam","VT", 50, "INR", 0);

    cout<<"Paytm payment"<<endl;
    cout<<"------------------"<<endl;
    bool ans1 = PaymentController::get_instance()->handle_payment(GatewayType::PAYTM, req1);
    cout<<"Result: "<<(ans1? "SUCCESS": "FAIL")<<endl;

    PaymentRequest* req2 = new PaymentRequest("VT","Gurekam", 50, "USD", 1, 30, 12);

    cout<<"Razorpay payment"<<endl;
    cout<<"------------------"<<endl;
    bool ans2 = PaymentController::get_instance()->handle_payment(GatewayType::RAZORPAY, req2);
    cout<<"Result: "<<(ans2? "SUCCESS": "FAIL")<<endl;

    delete req1;
    delete req2;
}