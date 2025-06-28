#include<bits/stdc++.h>
using namespace std;

class HttpRequest{
private:
    string url;                         //req
    string method;                      //req
    map<string, string> headers;
    map<string,string> query_params;
    string body;
    int timeout;                        //req

    HttpRequest(){}
public:
    friend class HttpRequestStepBuilder;

    void execute(){
        cout<<"Executing "<<method <<" request to "<<url<<endl;
        if(!query_params.empty()){
            cout<<"query parameters: "<<endl;
            for(auto& param: query_params){
                cout<<"\t"<<param.first<<" = "<<param.second<<endl;
            }
        }

        cout<<"Headers:"<<endl;
        for(auto& header:  headers){
            cout<<"\t"<<header.first<<": "<<header.second<<endl;
        }

        if(!body.empty()){
            cout<<"Body: "<<body<<endl;
        }

        cout<<"Timeout: "<<timeout<<" seconds"<<endl;
        cout<<"Request executed successfully!"<<endl;
    }
    
};

class MethodStep;
class HeaderStep;
class OptionalStep;

class UrlStep{
public:
    virtual MethodStep& with_url(string url) = 0;
};

class MethodStep{
public:
    virtual HeaderStep& with_method(string method) = 0;
};

class HeaderStep{
public:
    virtual OptionalStep& with_header(string key, string value) = 0;
};

class OptionalStep{
public: 
    virtual OptionalStep& with_query_param(string key, string value) = 0;
    virtual OptionalStep& with_body(string body) = 0;
    virtual OptionalStep& with_timeout(int timeout) = 0;
    virtual HttpRequest& build() = 0;
};


class HttpRequestStepBuilder:
    public MethodStep, 
    public UrlStep, 
    public HeaderStep, 
    public OptionalStep
{
private:
    HttpRequest req;

public:
    MethodStep& with_url(string url) override{
        req.url = url;
        return *this;
    }
    HeaderStep& with_method(string method){
        req.method = method;
        return *this;
    }
    OptionalStep& with_header(string key, string value){
        req.headers[key] = value;
        return *this;
    }
    OptionalStep& with_query_param(string key, string value){
        req.query_params[key] = value;
        return *this;
    }
    OptionalStep& with_body(string body){
        req.body = body;
        return *this;
    }
    OptionalStep& with_timeout(int timeout){
        req.timeout = timeout;
        return *this;
    }

    HttpRequest& build(){
        if(req.url.empty()) throw runtime_error("URL cannot be empty");
        return req;
    }

    static UrlStep& get_builder(){
        return *(new HttpRequestStepBuilder());
    }
};

int main(){
    HttpRequest req = HttpRequestStepBuilder::get_builder()
        .with_url("https://api.example.com")
        .with_method("GET")
        .with_header("Content-Type", "application/json")
        .with_body("{\"name\" = \"Gurekam\"}")
        .with_query_param("key", "12345")
        .with_timeout(60)
        .build();
    
    req.execute();
}