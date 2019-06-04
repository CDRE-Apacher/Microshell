#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <set>
#include <sstream>
#include <cstdlib>
#include <algorithm> //FOR SORTING VECTOR OBJECTS
/* 	--NOTES--
MAKE THE MENU LOOP
MAKE ALL THE MANUAL FUNCTION CALLS
*/
using namespace std;

/* --PERSON CLASSES-- */
class Person{
public:
	string name;
	string surname;
	int age;
	string position;
	
	Person(string _name, string _surname, int _age, string _position){
		p_id = p_next_id++;
		
		name = _name;
		surname = _surname;
		age = _age;
		position = _position;
		
		people.push_back(this);
	}

	virtual ~Person(){
		for (size_t i=0; i<people.size(); i++){
			if(people[i] == this){
				people[i] = people.back();
				people.pop_back();
				break;
			}
		}
	}

	int p_get_id(){
		return p_id;
	}

	string to_string(){
		stringstream ss;
		
		ss<<"#"<<this->p_id
		<<" :|: "<<this->name
		<<" :|: "<<this->surname
		<<" :|: "<<this->age
		<<" :|: "<<this->position
		<<endl;
		string str = ss.str();
		return str;
	}

	static Person* p_get_by_id(int id){
		for (Person* p : people){
			if (p->p_get_id() == id) return p;
		}
		return nullptr;
	}
	
	static vector<Person*> get_object_vector(){
		return people;
	}
	
	static Person* del_p_from_vector(int id){
		Person *a = p_get_by_id(id);
		
		if(a->position == "Customer"){
			cout<<"Cannot remove Customers from the list!"<<endl;
		}else{
			for (size_t i=0; i<people.size(); i++){
				if (people[i] == a) {
					people[i] = people.back();
					people.pop_back();
					for(int i = id-1;i<people.size();i++){
						swap(people[i],people[i+1]);
					}
					break;
				}
			}
		}
	}

private:
	int p_id;
	static int p_next_id;
	static vector<Person*> people;
};
int Person::p_next_id = 1;
vector<Person*> Person::people;

class Employee : public Person{
public:	
	Employee(string _name, string _surname, int _age, string _position):Person(_name, _surname, _age, _position){}
};

class Customer : public Person{
public:
	Customer(string _name, string _surname, int _age):Person(_name, _surname, _age, "Customer"){}
};

/* --VEHICLE CLASSES-- */
class Vehicle{
public:
	string producer;
	string model;
	int production_year;
	int num_passengers;
	char fuel_type;
	int fuel_cap;
	int weight;
	char type;

//LAND
	int doors;
	int trunk_cap;
//WATER
	string w_hull_type;
	int hull_buoyancy;
//AIR
	string a_hull_type;
	int lift;
//LEASING	
	int is_leased = 0;
	int leased_to = 0;

	Vehicle(string _model, string _producer, int _production_year, int _num_passengers, char _fuel_type, int _fuel_cap, int _weight, char _type, int _doors, int _trunk_cap, string _w_hull_type, int _hull_buoyancy, string _a_hull_type, int _lift, int _is_leased){
		v_id = v_next_id++;

		model = _model;
		producer = _producer;
		production_year = _production_year;
		num_passengers = _num_passengers;
		fuel_type = _fuel_type;
		fuel_cap = _fuel_cap;
		weight = _weight;
		type = _type;
		
		doors = _doors;
		trunk_cap = _trunk_cap;
		
		w_hull_type = _w_hull_type;
		hull_buoyancy = _hull_buoyancy;
		
		a_hull_type = _a_hull_type;
		lift = _lift;
		
		is_leased = _is_leased;

		vehicles.push_back(this);
	}

	virtual ~Vehicle(){
		for (size_t i=0; i<vehicles.size(); i++){
			if (vehicles[i] == this) {
				vehicles[i] = vehicles.back();
				vehicles.pop_back();
				break;
			}
		}
	}
	
	static Vehicle* del_v_from_vector(int id){
		Vehicle *a = v_get_by_id(id);
		for (size_t i=0; i<vehicles.size(); i++){
			if (vehicles[i] == a) {
				vehicles[i] = vehicles.back();
				vehicles.pop_back();
				for(int i = id-1;i<vehicles.size();i++){
					swap(vehicles[i],vehicles[i+1]);
				}
				break;
			}
		}
	}

	int v_get_id(){
		return v_id;
	}

	string to_string(){
		stringstream ss;
		
		ss<<"#"<<this->v_id
		<<" :|: "<<this->model
		<<" :|: "<<this->producer
		<<" :|: "<<this->production_year
		<<" :|: "<<this->num_passengers
		<<" :|: "<<this->fuel_type
		<<" :|: "<<this->fuel_cap
		<<" :|: "<<this->weight
		<<" :|: "<<this->type
		<<" :|: "<<this->doors
		<<" :|: "<<this->trunk_cap
		<<" :|: "<<this->w_hull_type
		<<" :|: "<<this->hull_buoyancy
		<<" :|: "<<this->a_hull_type
		<<" :|: "<<this->lift
		<<" :|: "<<this->is_leased
		<<endl;
		
		string str = ss.str();
		return str;
	}
	
	static void leasing(int v_id, int p_id){
		Vehicle* veh = v_get_by_id(v_id);
		Person* per = Person::p_get_by_id(p_id);
		if(per->position != "Customer"){
			cout<<"Employees cannot lease vehicles!"<<endl;
		}else{
			if(veh->is_leased != 0){
				cout<<"Can't lease vechicle!"<<endl;
			}else{
			veh->is_leased = p_id;
			}
		}
		
	}
	
	static void return_leasing(int v_id){
		Vehicle* veh = v_get_by_id(v_id);
		veh->is_leased = 0;
	}

	static Vehicle* v_get_by_id(int id){
		for (Vehicle* v : vehicles){
			if (v->v_get_id() == id) return v;
		}
		return nullptr;
	}
	
	static vector<Vehicle*> get_object_vector(){
		return vehicles;
	}

private:
	int v_id;
	static int v_next_id;
	static vector<Vehicle*> vehicles;
};

int Vehicle::v_next_id = 1;
vector<Vehicle*> Vehicle::vehicles;
/* --VEHICLE LAND CLASSES-- */

class Land: public Vehicle{
public:
	Land(string _model, string _producer, int _production_year, int _num_passengers, char _fuel_type, int _fuel_cap, int _weight, int _doors, int _trunk_cap):Vehicle(_model, _producer, _production_year, _num_passengers, _fuel_type, _fuel_cap, _weight, 'L', _doors, _trunk_cap, "N/A", 0, "N/A", 0, 0){}

	virtual ~Land(){};
};
/* --VEHICLE WATER CLASSES-- */
class Water: public Vehicle{
public:
	Water(string _model, string _producer, int _production_year, int _num_passengers, char _fuel_type, int _fuel_cap, int _weight, string _w_hull_type, int _hull_buoyancy):Vehicle(_model, _producer, _production_year, _num_passengers, _fuel_type, _fuel_cap, _weight, 'W', 0, 0, _w_hull_type, _hull_buoyancy, "N/A", 0, 0){}

	virtual ~Water(){};
};
/* --VEHICLE AIR CLASSES-- */
class Air: public Vehicle{
public:
	Air(string _model, string _producer, int _production_year, int _num_passengers, char _fuel_type, int _fuel_cap, int _weight, string _a_hull_type, int _lift):Vehicle(_model, _producer, _production_year, _num_passengers, _fuel_type, _fuel_cap, _weight, 'A', 0, 0, "N/A", 0, _a_hull_type, _lift, 0){}

	virtual ~Air(){};
};
/* --MAIN-- */
int main(){
	new Land("Astra","Opel",2010,5,'D',40,2500,5,350);
	new Land("Panda","Fiat",2007,7,'G',70,2000,5,500);
	new Land("Juke","Nissan",2000,5,'G',65,1900,5,440);
	new Land("Focus","Ford",1999,5,'G',45,2300,3,300);

	new Water("Safari 28","Carter Marine",2012,6,'G',240,1200,"FIBER",1700);
	new Water("Safari 56","Carter Marine",2002,8,'G',290,1400,"FIBER",1900);
	new Water("Kirk","Amel Yachts",2016,12,'G',350,2500,"FIBER/METAL",3000);
	new Water("Fango","Amel Yachts",2008,16,'G',370,2700,"METAL/WOOD",3500);

	new Air("Everett-747","Boeing",2000,120,'N',5000,4000,"ALU/FIBER",9500);
	new Air("A-380","Airbus",20080,240,'N',5500,4500,"ALU/FIBER",12000);
	new Air("C-5 Galaxy","Lockheed Martin",2016,20,'N',65000,6000,"ALU",10000);
	new Air("GE9X","GE Aviation",2006,2,'N',2500,2500,"FIBER",6800);

	new Employee("Staszek","Grzmot",33,"Mechanic");
	new Employee("Wojtek", "Daminski", 43, "Salesman");
	new Employee("Andrzej", "Stachowiak", 28, "Deliveryman");
	new Employee("Patryk", "Wolny", 46, "Mechanic");
	new Employee("Zbigniew", "Knur", 39, "Mechanic");

	new Customer("Marek", "Wolski", 23);
	new Customer("Witold", "Brzeski", 34);
	new Customer("Damian", "Makowski", 36);
	new Customer("Adrian", "Woltycki", 54);
	
	while(1){
		
		system("cls");
		
		cout
		<<"0 -> Exit"<<endl
		
		<<"1 -> Add a vehicle"<<endl
		<<"2 -> Add an employee"<<endl
		<<"3 -> Add a customer"<<endl
		
		<<"4 -> Rent a vehicle"<<endl
		<<"5 -> Return a vehicle"<<endl
		
		<<"6 -> Revove an employee from the roster"<<endl
		<<"7 -> Remove a vehicle from the roster"<<endl
		
		<<"8 -> Viev Personel and Customer List"<<endl
		<<"9 -> Viev Vehicle List"<<endl;
		
		int com_input;
		cin>> com_input;
		
		switch(com_input){
			case 0:// EXIT PROGRAM
				return EXIT_SUCCESS;
			break;
			
			case 1://ADD VEHICLE
			
				system("cls");
			
				cout
				<<"Whatt type of vehicle do you want to add?"<<endl
				<<"1 -> Land"<<endl
				<<"2 -> Water"<<endl
				<<"3 -> Air"<<endl;
			
				int type_input;
				cin>> type_input;
				
				switch(type_input){//WHAT TYPE OF VEHICLE
					case 1://LAND
					{
						string mdl_L, prod_L;
						char f_typ_L;
						int p_year_L, n_pass_L, f_cap_L, wght_L, drs_L, t_cap_L;
						
						system("cls");
						
						cout<<"Input Model:"<<endl;
						cin>>mdl_L;
						
						cout<<"Input Producer:"<<endl;
						cin>>prod_L;
						
						cout<<"Input Production year:"<<endl;
						cin>>p_year_L;
						
						cout<<"Input Number of passengers:"<<endl;
						cin>>n_pass_L;
						
						cout<<"Input Fuel type:"<<endl;
						cout<<"G - gassoline, D - Diesel, L - LPG"<<endl;
						cin>>f_typ_L;
						
						cout<<"Input Fuel Capacity:"<<endl;
						cin>>f_cap_L;
						
						cout<<"Input Vehicle Weight:"<<endl;
						cin>>wght_L;
						
						cout<<"Input Number of Doors:"<<endl;
						cin>>drs_L;
						
						cout<<"Input Trunk Capacity:"<<endl;
						cin>>t_cap_L;
						
						cout<<"Adding Land Based Vehicle"<<endl;
						
						new Land(mdl_L, prod_L, p_year_L, n_pass_L, f_typ_L, f_cap_L, wght_L, drs_L, t_cap_L);
					}
					break;
					
					case 2://WATER
					{
						string mdl_W, prod_W, w_typ_W;
						char f_typ_W;
						int p_year_W, n_pass_W, f_cap_W, wght_W, buoy_W;
						
						system("cls");
						
						cout<<"Input Model:"<<endl;
						cin>>mdl_W;
						
						cout<<"Input Producer:"<<endl;
						cin>>prod_W;
						
						cout<<"Input Production year:"<<endl;
						cin>>p_year_W;
						
						cout<<"Input Number of passengers:"<<endl;
						cin>>n_pass_W;
						
						cout<<"Input Fuel type:"<<endl;
						cout<<"G - gassoline, D - Diesel, L - LPG"<<endl;
						cin>>f_typ_W;
						
						cout<<"Input Fuel Capacity:"<<endl;
						cin>>f_cap_W;
						
						cout<<"Input Vehicle Weight:"<<endl;
						cin>>wght_W;
						
						cout<<"Input Hull Type:"<<endl;
						cin>>w_typ_W;
						
						cout<<"Input buoyancy:"<<endl;
						cin>>buoy_W;
						
						cout<<"Adding Water Based Vehicle"<<endl;
						
						new Water(mdl_W, prod_W, p_year_W, n_pass_W, f_typ_W, f_cap_W, wght_W, w_typ_W, buoy_W);
					}
					break;
					
					case 3://AIR
					{
						string mdl_A, prod_A, a_typ_A;
						char f_typ_A;
						int p_year_A, n_pass_A, f_cap_A, wght_A, lft_A;
						
						system("cls");
						
						cout<<"Input Model:"<<endl;
						cin>>mdl_A;
						
						cout<<"Input Producer:"<<endl;
						cin>>prod_A;
						
						cout<<"Input Production year:"<<endl;
						cin>>p_year_A;
						
						cout<<"Input Number of passengers:"<<endl;
						cin>>n_pass_A;
						
						cout<<"Input Fuel type:"<<endl;
						cout<<"G - gassoline, D - Diesel, L - LPG, N - Naphta"<<endl;
						cin>>f_typ_A;
						
						cout<<"Input Fuel Capacity:"<<endl;
						cin>>f_cap_A;
						
						cout<<"Input Vehicle Weight:"<<endl;
						cin>>wght_A;
						
						cout<<"Input Hull Type:"<<endl;
						cin>>a_typ_A;
						
						cout<<"Input Lift:"<<endl;
						cin>>lft_A;
						
						cout<<"Adding Air Based Vehicle"<<endl;
						
						new Air(mdl_A, prod_A, p_year_A, n_pass_A, f_typ_A, f_cap_A, wght_A, a_typ_A, lft_A);
					}
					break;
				}	
			break;
			
			case 2://ADD EMPLOYEE
				{
					string nm_E, snm_E, pos_E;
					int ag_E;
					
					cout<<"Input Employee Name:"<<endl;
					cin>>nm_E;
					
					cout<<"Input Employee Surname:"<<endl;
					cin>>snm_E;
					
					cout<<"Input Employee Age:"<<endl;
					cin>>ag_E;
					
					cout<<"Input Employee Position:"<<endl;
					cin>>pos_E;
					
					cout<<"Adding New Employee"<<endl;
					
					new Employee(nm_E, snm_E, ag_E, pos_E);
				}
			break;
			
			case 3://ADD CLIENT
				{
					string nm_C, snm_C;
					int ag_C;
					
					cout<<"Input Customer Name:"<<endl;
					cin>>nm_C;
					
					cout<<"Input Customer Surname:"<<endl;
					cin>>snm_C;
					
					cout<<"Input Customer Age:"<<endl;
					cin>>ag_C;
					
					cout<<"Adding New Customer"<<endl;
					
					new Customer(nm_C, snm_C, ag_C);
				}
			break;
			
			case 4://RENT VEHICLE
				{
				
				system("cls");
					
				int r_v_id, r_p_id;
					
				cout<<"Which Vehicle Are You Renting?"<<endl;
				
				/*
				A FULL LIST OF VEHICLES
				*/
				
				cout<<"Select by ID:"<<endl;
				cin>>r_v_id;
				
				cout<<"To Whom is the Vehicle Rented?"<<endl;
				
				/*
				A FULL LIST OF CUSTOMERS
				*/
				
				cout<<"Select by ID:"<<endl;
				cin>>r_p_id;
				
				cout<<"Vehicle rented"<<endl;
				Vehicle::leasing(r_v_id, r_p_id);
				}
			break;
			
			case 5://RETURN VEHICLE
			{
				int r_v_id;
				
				cout<<"Which Vehicle to return?"<<endl;
				
				/*
				ALL RENTED VEHICLES
				*/
				
				cout<<"Choose by ID:"<<endl;
				cin>>r_v_id;
				
				cout<<"Returning Vehicle"<<endl;
				Vehicle::return_leasing(r_v_id);
			}
			break;
			
			case 6://REMOVE EMPLOYEE
				{
					int d_p_id;
					
					cout<<"Which Employee do You Want to Remove from the Roster?"<<endl;
					
					/*
					LIST OF ALL EMPLOYEES
					*/
					
					cout<<"Choose by ID:"<<endl;
					cin>>d_p_id;
					
					cout<<"Removing Employee";
					Person::del_p_from_vector(d_p_id);
				}
			break;
			
			case 7://REMOVE VEHICLE
				{
					int d_v_id;
					cout<<"Which Vehicle do You Want to Remove from the Roster"<<endl;
					
					/*
					LIST ALL NON RENTED VEHICLES
					*/
					
					cout<<"Choose by ID:"<<endl;
					cin>>d_v_id;
					
					cout<<"Removing Vehicle"<<endl;
					Vehicle::del_v_from_vector(d_v_id);
				}
			break;
			
			case 8:
				
			break;
			
			case 9:
				
			break;
		}
	}
	return EXIT_SUCCESS;
}

	
	/*
	
	asd
	
	vector<Vehicle*> a = Vehicle::get_object_vector();
		for(Vehicle* i : a){
			cout<<i->to_string()<<endl;
		}
	
	cout<<endl<<endl;
	
	vector<Person*> b = Person::get_object_vector();
		for(Person* j : b){
			cout<<j->to_string()<<endl;
		}
	*/
	
	/*
	Vehicle::del_from_vector(3);
	vector<Vehicle*> a = Vehicle::get_object_vector();
		for(Vehicle* i : a){
			cout<<i->to_string()<<endl;
		}
	vector<Person*> b = Person::get_object_vector();
		for(Person* j : b){
			cout<<j->to_string()<<endl;
		}
	Vehicle::leasing(2,2);
	a = Vehicle::get_object_vector();
		for(Vehicle* i : a){
			cout<<i->to_string()<<endl;
		}
	Vehicle::leasing(2,2);
	Vehicle::return_leasing(2);
	Vehicle::leasing(2,1);
	a = Vehicle::get_object_vector();
		for(Vehicle* i : a){
			cout<<i->to_string()<<endl;
		}
	b = Person::get_object_vector();
		for(Person* j : b){
			cout<<j->to_string()<<endl;
		}
	Person::del_from_vector(2);
		b = Person::get_object_vector();
		for(Person* j : b){
			cout<<j->to_string()<<endl;
		}
	*/
