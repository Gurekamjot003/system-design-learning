#include<bits/stdc++.h>
using namespace std;

class PowerSupply{
public:
    void provide_power(){
        cout<<"Power supply: Providing power..."<<endl;
    }
};

class CoolingSystem{
public:
    void start_fans(){
        cout<<"Cooling System: fans started..."<<endl;
    }
};

class CPU{
public:
    void initialize(){
        cout<<"CPU: Initialization started..."<<endl;
    }
};

class Memory{
public:
    void self_test(){
        cout<<"Memory: self tests passed..."<<endl;
    }
};

class HardDrive{
public:
    void spin_up(){
        cout<<"Hard Drive: spinning up..."<<endl;
    }
};

class BIOS{
public:
    void boot(CPU cpu, Memory memory){
        cout<<"BIOS: Booting CPU and memory checks..."<<endl;
        cpu.initialize();
        memory.self_test();
    }
};

class OperatingSystem{
public:
    void load(){
        cout<<"Operating System: Loading into memory..."<<endl;
    }
};

class ComputerFacade{
private:
    PowerSupply power_supply;
    CoolingSystem cooling_system;
    CPU cpu;
    Memory memory;
    BIOS bios;
    HardDrive hard_drive;
    OperatingSystem os;

public:
    void start_computer(){
        cout<<"-------- Starting Computer -----------"<<endl;
        power_supply.provide_power();
        cooling_system.start_fans();
        bios.boot(cpu, memory);
        hard_drive.spin_up();
        os.load();
        cout<<"Computer booted successfully!"<<endl;
    }
};

int main(){
    ComputerFacade computer;
    computer.start_computer();
}