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
    friend class HttpRequestBuilder;

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

class HttpRequestBuilder{
private:
    HttpRequest req;

public:
    HttpRequestBuilder(){}
    HttpRequestBuilder with_url(string url){
        req.url = url;
        return *this;
    }
    HttpRequestBuilder with_method(string method){
        req.method = method;
        return *this;
    }
    HttpRequestBuilder with_header(string key, string value){
        req.headers[key] = value;
        return *this;
    }
    HttpRequestBuilder with_query_param(string key, string value){
        req.query_params[key] = value;
        return *this;
    }
    HttpRequestBuilder with_body(string body){
        req.body = body;
        return *this;
    }
    HttpRequestBuilder with_timeout(int timeout){
        req.timeout = timeout;
        return *this;
    }

    HttpRequest build(){
        if(req.url.empty()) throw runtime_error("URL cannot be empty");
        return req;
    }
};

class HttpRequestDirector{
public:
    static HttpRequest create_get_request(string url){
        return HttpRequestBuilder()
                .with_url(url)
                .with_method("GET")
                .build();
    }

    static HttpRequest create_json_post_request(string url, string json_body){
        return HttpRequestBuilder()
                .with_url(url)
                .with_method("POST")
                .with_header("Content-Type", "application/json")
                .with_header("Accept", "application/json")
                .with_body(json_body)
                .build();
    }
};

int main(){
    HttpRequest normal_req = HttpRequestBuilder()
        .with_url("https://api.example.com")
        .with_method("GET")
        .with_body("{\"name\" = \"Gurekam\"}")
        .with_header("Content-Type", "application/json")
        .with_query_param("key", "12345")
        .with_timeout(60)
        .build();
    
    normal_req.execute();

    cout<<"\n\n";

    HttpRequest get_req = HttpRequestDirector::create_get_request("https://example.com");
    get_req.execute();

    cout<<"\n\n";

    HttpRequest post_req = HttpRequestDirector::create_json_post_request("https://example.com", "{\"name\": \"Gurekam\"}");
    post_req.execute();

}