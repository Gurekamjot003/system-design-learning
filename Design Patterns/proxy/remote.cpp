#include<bits/stdc++.h>
using namespace std;

class IDataService{
public:
    virtual string fetch_data() = 0;
    virtual ~IDataService() = default;
};

class RealDataService: public IDataService{
public:
    RealDataService(){
        cout<<"[RealDataService] initialized simulating remote setup"<<endl;
    }

    string fetch_data() override{
        return "[RealDataService] Data from server \n";
    }
};

class DataServiceProxy: public IDataService{
private:
    RealDataService* real_data;
    

public:
    DataServiceProxy(){
        real_data = new RealDataService();
    }

    string fetch_data() override{
        cout<<"[DataServiceProxy] Connecting to remote service...\n";
        return real_data->fetch_data();
    }
};

int main(){
    IDataService* data_service = new DataServiceProxy();
    cout<<data_service->fetch_data()<<endl;
}