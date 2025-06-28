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

public:

    HttpRequest(string url):url(url){}
    HttpRequest(string url, string method): url(url), method(method){}
    HttpRequest(string url, string method, int timeout):url(url), method(method), timeout(timeout){}
    HttpRequest(string url, string method, int timeout, string body):url(url), method(method), timeout(timeout), body(body){}
    // !n ways of constructing

    void set_url(string url){
        this->url = url;
    }

    void set_method(string method){
        this->method = method;
    }

    void add_header(string key, string value){
        headers[key] = value;
    }

    void add_query_params(string key, string value){
        query_params[key] = value;
    }

    void set_body(string body){
        this->body = body;
    }

    void set_timeout(int timeout){
        this->timeout = timeout;
    }

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

int main(){
    HttpRequest* req1 = new HttpRequest("http://api.example.com");
    HttpRequest* req2 = new HttpRequest("http://api.example.com","POST");
    HttpRequest* req3 = new HttpRequest("http://api.example.com","PUT", 60);

    HttpRequest* req4 = new HttpRequest("https://api.example.com");
    req4->set_method("POST");
    req4->add_header("Content-Type", "application/json");
    req4->add_query_params("key", "12345");
    req4->set_body("{\"name\": \"Gurekam\"}");
    req4->set_timeout(60);

    req4->execute();
}