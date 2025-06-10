#include<bits/stdc++.h>
using namespace std;

class IReports{
public:
    virtual string get_json_data(string data) = 0;
    virtual ~IReports(){}
};

class XmlDataProvider{
public:
    string get_xml_data(string data){
        auto sep = data.find(':');
        string name = data.substr(0, sep);
        string id = data.substr(sep + 1);

        return "<user>" 
            "<name>" + name + "</name>" +
            "<id>" + id + "</id>" 
            "</user>";
    }
};

class XmlDataAdapter: public IReports{
private:
    XmlDataProvider* xml_provider;

public:
    XmlDataAdapter(XmlDataProvider* xml_provider){
        this->xml_provider = xml_provider;
    }

    string get_json_data(string data) override{
        string xml = xml_provider->get_xml_data(data);

        auto start_name = xml.find("<name>") + 6;
        auto end_name = xml.find("</name>");
        string name = xml.substr(start_name, end_name - start_name);

        auto start_id = xml.find("<id>") + 4;
        auto end_id = xml.find("</id>");
        string id = xml.substr(start_id, end_id - start_id);

        return "{\"name\":\"" + name + "\", \"id\": " + id + "}";
    }
};

class Client{
public:
    void get_report(IReports* report, string rawdata){
        cout<<"Processed JSON: "
            <<report->get_json_data(rawdata)<<endl;
    }
};

int main(){
    XmlDataProvider* provider = new XmlDataProvider();

    IReports* adapter = new XmlDataAdapter(provider);

    string rawdata = "Gurekam:58";

    Client* client = new Client();
    client->get_report(adapter, rawdata);

    delete adapter;
    delete provider;
}