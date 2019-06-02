#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

class Sold
{
public:
	int id;
	int year_of_production;
	float engine_volume;
	string brand;
	char fuel_type;
	char type;
	int seats;
	int doors;
	int capacity;
	float height;
	static vector<Sold*> cars_sold;
	Sold(int ID,int yop,float ev,string bd,char ft ,char tp,int sea,int drs,int cap, float hgt)
	{
		id = ID;
		year_of_production=yop;
		engine_volume=ev;
		brand=bd;
		fuel_type=ft;
		type=tp;
		seats=sea;
		doors=drs;
		capacity=cap;
		height=hgt;
		cars_sold.push_back(this);
	}
	string ToString()
	{
		stringstream ss;
		ss<<"| "<<this->id<<" | "<<this->year_of_production<<" | "<<this->engine_volume<<" | "<<this->brand<<" | "<<this->fuel_type<<" | "<<this->type<<" | "<<this->seats<<" | "<<this->doors<<" | "<<this->capacity<<" | "<<this->height<<" | ";
		string str=ss.str();
		return str;
	}
	static vector<Sold*> GetPointers(){
		return cars_sold;
	}
	int getId() { return id; }
	static Sold* getById(int id)
	{
		for (Sold* e : cars_sold) {
			if (e->getId() == id) return e;
		}
		return nullptr;
	}
	
};

vector<Sold*> Sold::cars_sold;

class Car
{
public:
	int id;
	int year_of_production;
	float engine_volume;
	string brand;
	char fuel_type;
	char type;
	int seats;
	int doors;
	int capacity;
	float height;
	static int nextId;
	static vector<Car*> cars;
	Car(int yop,float ev,string bd,char ft ,char tp,int sea,int drs,int cap, float hgt)
	{
		id = nextId++;
		year_of_production=yop;
		engine_volume=ev;
		brand=bd;
		fuel_type=ft;
		type=tp;
		seats=sea;
		doors=drs;
		capacity=cap;
		height=hgt;
		cars.push_back(this);
	}
	virtual ~Car()
	{
		for (size_t i=0; i<cars.size(); i++) {
			if (cars[i] == this) {
				cars[i] = cars.back();
				cars.pop_back();
				break;
			}
		}
	}

	int getId() { return id; }
	
	static vector<Car*> GetPointers(){
		return cars;
	}

	static Car* getById(int id)
	{
		for (Car* e : cars) {
			if (e->getId() == id) return e;
		}
		return nullptr;
	}
		string ToString()
	{
		stringstream ss;
		ss<<"| "<<this->id<<" | "<<this->year_of_production<<" | "<<this->engine_volume<<" | "<<this->brand<<" | "<<this->fuel_type<<" | "<<this->type<<" | "<<this->seats<<" | "<<this->doors<<" | "<<this->capacity<<" | "<<this->height<<" | ";
		string str=ss.str();
		return str;
	}
	static Car* del(int id){
		Car *a=getById(id);
		new Sold(a->id,a->year_of_production,a->engine_volume,a->brand,a->fuel_type,a->type,a->seats,a->doors,a->capacity,a->height);
		for (size_t i=0; i<cars.size(); i++) {
			if (cars[i] == a) {
				cars[i] = cars.back();
				cars.pop_back();
				for(int i=id-1;i<cars.size();i++)
				{
					swap(cars[i],cars[i+1]);
				}
				break;
			}
		}
		return nullptr;
	}
};

int Car::nextId = 1;
vector<Car*> Car::cars;

class Personal : Car
{
public:
	Personal(int yop,float ev,string bd,char ft,int sea ,int drs) : Car(yop,ev,bd,ft ,'p',sea,drs,0,0){}
	virtual ~Personal(){}
		
};

class Van : Car
{
public:
	Van(int yop,float ev,string bd,char ft,int cap ,float hgt) : Car(yop,ev,bd,ft ,'v',0,0,cap,hgt){}
	virtual ~Van(){}
		
};

class Client 
{
public:
	int id;
	string name;
	string surname;
	long int pesel;
	static int nextId;
	static vector<Client*> clients;
	Client(string n,string sn, int p){
		id=nextId++;
		name=n;
		surname=sn;
		pesel=p;
		clients.push_back(this);
	}
	
	virtual ~Client(){}
	
	int getId() { return id; }
	
	static Client* getById(int id)
	{
		for (Client* e : clients) {
			if (e->getId() == id) return e;
		}
		return nullptr;
	}
	
	string ToString()
	{
		stringstream ss;
		ss<<"| "<<this->id<<" | "<<this->name<<" | "<<this->surname<<" | "<<this->pesel;
		string str=ss.str();
		return str;
	}
	static vector<Client*> GetPointers(){
		return clients;
	}
	
};

int Client::nextId = 1;
vector<Client*> Client::clients;

class Worker
{
public:
	int id;
	string name;
	string surname;
	long int pesel;
	static int nextId;
	static vector<Worker*> workers;
	Worker(string n,string sn, int p){
		id=nextId++;
		name=n;
		surname=sn;
		pesel=p;
		workers.push_back(this);
	}
	
	virtual ~Worker(){}
	
	int getId() { return id; }
	
	static Worker* getById(int id)
	{
		for (Worker* e : workers) {
			if (e->getId() == id) return e;
		}
		return nullptr;
	}
	
	string ToString()
	{
		stringstream ss;
		ss<<"| "<<this->id<<" | "<<this->name<<" | "<<this->surname<<" | "<<this->pesel;
		string str=ss.str();
		return str;
	}
		static vector<Worker*> GetPointers(){
		return workers;
	}
	
};

int Worker::nextId = 1;
vector<Worker*> Worker::workers;	

class Sales
{
public:	
	int id;
	Sold* car;
	Client* client;
	Worker* worker;
	static int nextId;
	static vector<Sales*> sales;
	Sales(Sold *sold_car,Client *cli,Worker *work)
	{
	id=nextId++;
	car=sold_car;
	client=cli;
	worker=work;
	sales.push_back(this);
	}
	
	string ToString()
	{
		stringstream ss;
		ss<<"| "<<this->id<<" | "<<this->car->brand<<" "<<this->car->year_of_production<<" | "<<this->client->name<<" "<<this->client->surname<<" | "<<this->worker->name<<" "<<this->worker->surname;
		string str=ss.str();
		return str;
	}
	static vector<Sales*> GetPointers(){
		return sales;
	}
	
	
};
int Sales::nextId = 1;
vector<Sales*> Sales::sales;

int main() 
{
	new Personal(2011,1.4,"Opel",'p',5,4);
	new Personal(2012,1.6,"Opel",'p',5,5);
	new Personal(1997,2.0,"Opel",'p',5,3);
	new Van(2000,4.5,"Opel",'d',1500,2.5);
	new Van(2001,3.2,"Opel",'d',2000,2.3);
	new Van(1040,2.2,"Opel",'d',2000,4.3);
	new Client("Adam","Kowalski",938424254);
	new Client("Ewa","Maruszak",583272853);
	new Worker("Jan","Nowak",111111111);
	new Worker("Edmund","Nowakowski",222333444);
int t=1;
while(t==1)
{
	system("cls");
	int command;
	cout<<"Car Selling Program by Witold Borowiak"<<endl;
	cout<<"0 <-> Exit"<<endl;
	cout<<"1 <-> Add car"<<endl;
	cout<<"2 <-> Add client"<<endl;
	cout<<"3 <-> Add worker"<<endl;
	cout<<"4 <-> Sell a car"<<endl;
	cout<<"5 <-> Show all cars"<<endl;
	cout<<"6 <-> Show all clients"<<endl;
	cout<<"7 <-> Show all workers"<<endl;
	cout<<"8 <-> Show all sold cars"<<endl;
	cout<<"9 <-> Show all sales"<<endl;
	cin>>command;
	if(command==0)
	{
		t=0;
	}
	else if(command==1)
	{
		int yop,seats,doors,volume;
		float ev,height;
		string brand;
		char type;
		char confirm;
		system("cls");
		cout<<"** ADD CAR MODULE **"<<endl;
		cout<<"Personal car or a Van? (P/V): ";
		cin>>type;
		if(type=='P' || type=='p')
		{
		cout<<"Year of production: ";
		cin>>yop;
		cout<<"Engine volume: ";
		cin>>ev;
		cout<<"Brand: ";
		cin>>brand;
		cout<<"Fuel type (D-diesel,L-lpg,P-petrolium): ";
		cin>>type;
		cout<<"Number of seats: ";
		cin>>seats;
		cout<<"Number of doors: ";
		cin>>doors;
		cout<<"Are you sure(Y/N)? : ";
		cin>>confirm;
		if(confirm=='Y'||confirm=='y')
		{
		new Personal(yop,ev,brand,type,seats,doors);
		}
		}
			if(type=='V' || type=='v')
		{
		cout<<"Year of production: ";
		cin>>yop;
		cout<<"Engine volume: ";
		cin>>ev;
		cout<<"Brand: ";
		cin>>brand;
		cout<<"Fuel type (D-diesel,L-lpg,P-petrolium): ";
		cin>>type;
		cout<<"volume: ";
		cin>>volume;
		cout<<"Height: ";
		cin>>height;
		cout<<"Are you sure(Y/N)? : ";
		cin>>confirm;
		if(confirm=='Y'||confirm=='y')
		{
		new Van(yop,ev,brand,type,volume,height);
		}
		}
		
	}
	else if(command==2)
	{
		system("cls");
		long int pesel;
		string name,surname;
		char confirm;
		cout<<"** ADD CLIENT MODULE **"<<endl;
		cout<<"Name: ";
		cin>>name;
		cout<<"Surname: ";
		cin>>surname;
		cout<<"Pesel: ";
		cin>>pesel;
		cout<<"Are you sure(Y/N)? : ";
		cin>>confirm;
		if(confirm=='Y'||confirm=='y')
		{
			new Client(name,surname,pesel);
		}
	}
	else if(command==3)
	{
		system("cls");
		long int pesel;
		string name,surname;
		char confirm;
		cout<<"** ADD WORKER MODULE **"<<endl;
		cout<<"Name: ";
		cin>>name;
		cout<<"Surname: ";
		cin>>surname;
		cout<<"Pesel: ";
		cin>>pesel;
		cout<<"Are you sure(Y/N)? : ";
		cin>>confirm;
		if(confirm=='Y'||confirm=='y')
		{
			new Worker(name,surname,pesel);
		}
	}
	else if(command==4)
	{
		system("cls");
		int car,worker,client;
		char confirm;
		cout<<"** CAR SALE MODULE**"<<endl;
		cout<<"__CARS__"<<endl;
		cout<<"|ID|Year of production|Engine|Brand|Fuel|Type|seats|doors|volume|Height"<<endl<<endl;
	
		vector<Car*> cars=Car::GetPointers();
		for(Car* e: cars){
		cout<<e->ToString()<<endl;
		}
		cout<<endl;
		cout<<"Insert ID of car you want to sell: ";
		cin>>car;
		system("cls");
		cout<<"_CLIENTS_"<<endl;
		cout<<"|ID|Name|Surname|Pesel|"<<endl<<endl;
	
		vector<Client*> clients=Client::GetPointers();
		for(Client* e: clients){
		cout<<e->ToString()<<endl;
	}
		cout<<endl;
		cout<<"Insert ID of Client: ";
		cin>>client;
		system("cls");
		cout<<"__WORKERS__"<<endl;
		cout<<"|ID|Name|Surname|Pesel|"<<endl<<endl;
	
		vector<Worker*> workers=Worker::GetPointers();
		for(Worker* e: workers){
		cout<<e->ToString()<<endl;
	}
		cout<<endl;
		cout<<"Insert your worker ID: ";
		cin>>worker;
		system("cls");
		Car* p_car=Car::getById(car);
		Client* p_client=Client::getById(client);
		Worker* p_worker=Worker::getById(worker);
		cout<<"Are you sure you want to sell "<<p_car->brand<<"("<<p_car->year_of_production<<") to "<<p_client->name<<" "<<p_client->surname<<"(Y/N)? : ";
		cin>>confirm;
		if(confirm=='Y'||confirm=='y')
		{
			Car::del(car);
			Sold* p_sold=Sold::getById(car);
			new Sales(p_sold,p_client,p_worker);
		}
	}
	else if(command==5)
	{
	system("cls");
	cout<<"** CARS **"<<endl;
	cout<<"|ID|Year of production|Engine|Brand|Fuel|Type|seats|doors|volume|Height"<<endl<<endl;
	
	vector<Car*> cars=Car::GetPointers();
	for(Car* e: cars){
		cout<<e->ToString()<<endl;
	}
	cout<<endl;
	system("pause");
	}
	else if(command==6)
	{
	system("cls");
	cout<<"** CLIENTS **"<<endl;
	cout<<"|ID|Name|Surname|Pesel|"<<endl<<endl;
	
	vector<Client*> clients=Client::GetPointers();
	for(Client* e: clients){
		cout<<e->ToString()<<endl;
	}
	cout<<endl;
	system("pause");
	}
	else if(command==7)
	{
	system("cls");
	cout<<"** WORKERS **"<<endl;
	cout<<"|ID|Name|Surname|Pesel|"<<endl<<endl;
	
	vector<Worker*> workers=Worker::GetPointers();
	for(Worker* e: workers){
		cout<<e->ToString()<<endl;
	}
	cout<<endl;
	system("pause");
	}
	else if(command==8)
	{
	system("cls");
	cout<<"** SOLD CARS **"<<endl;
	cout<<"|ID|Year of production|Engine|Brand|Fuel|Type|seats|doors|volume|Height"<<endl<<endl;
	
	vector<Sold*> cars_sold=Sold::GetPointers();
	for(Sold* e: cars_sold){
		cout<<e->ToString()<<endl;
	}
	cout<<endl;
	system("pause");
	}
	else if(command==9)
	{
	system("cls");
	cout<<"** Sales **"<<endl;
	cout<<"|ID|Car|Client|Worker|"<<endl<<endl;
	vector<Sales*> sales=Sales::GetPointers();
	for(Sales* e: sales){
	cout<<e->ToString()<<endl;
	}
	cout<<endl;
	system("pause");
	}
	
}
	return 0;
}
