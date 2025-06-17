#include<bits/stdc++.h>
using namespace std;

class ModelTrainer{
public:
    void train_pipeline(string path){
        load_data(path);
        preprocess_data();
        train_model();
        evaluate_model();
        save_model();
    }
protected:
    void load_data(string path){
        cout<<"[Common] Loading dataset from "<<path<<endl;
    }

    virtual void preprocess_data(){
        cout<<"[Common] Splitting data into train/test and normalizing"<<endl;
    }

    virtual void train_model() = 0;
    virtual void evaluate_model() = 0;
    virtual void save_model(){
        cout<<"[Common] Saving model to disk as default format"<<endl;
    }
};

class NeuralNetworkTrainer: public ModelTrainer{
protected:
    void train_model() override{
        cout<<"[NeuralNet] Training Neural Network for 100 epochs"<<endl;
    }
    void evaluate_model() override{
        cout<<"[NeuralNet] Evaluating accuracy and loss on validation set"<<endl;
    }

    void save_model() override{
        cout<<"[NeuralNet] Serializing network weights to .h5 file"<<endl;
    }
};

class DecisionTreeTrainer: public ModelTrainer{
protected:
    void train_model() override{
        cout<<"[DecisionTree] Building decision tree with max_depth = 5"<<endl;
    }
    void evaluate_model() override{
        cout<<"[DecisionTree] Computing classification report (precision/recall)"<<endl;
    }
};

int main(){
    cout<<"-------- Neural Network -----------"<<endl;
    ModelTrainer* neural = new NeuralNetworkTrainer();
    neural->train_pipeline("data/images/");

    cout<<endl<<"------------- Decision Tree ------------"<<endl;
    ModelTrainer* decision = new DecisionTreeTrainer();
    decision->train_pipeline("data/iris.csv");
}