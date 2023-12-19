#include<iostream>
#include<fstream>
using namespace std;
//parent class human body
class HumanBody
{
//access specifiers
private:
    //hidden from the outside world
    int arms,legs;
public:
    HumanBody(){}
    //virtual function
    virtual void digesting()
    {
         cout << "Digesting inside the body. "<<endl;
    }
};

//template(generic function) to calculate amount of calorie intake
//concept:templates
template<typename T>
T calculateCalories(T a, T b)
{
    return (a+b);
}

//class digestive system depends on class food
//concept: dependency, class forwarding
class Food
{
public:
    int calories;
    //defining constructors
    //concept: constructors in classes and function overloading, as constructors are special member functions
    //default constructor
    Food()
    {
        //exception handling, try block - might contain suspicious code
        try
        {
            int q,r,s;
            cout << "Enter the calories of three foods you ate today: ";
            cin >> q >> r >> s;
            //code optimization(avoids creation of extra temp variable) and typecasting
            int p =  calculateCalories<int>(calculateCalories<int>(q,r),s);
            cout << "Amount of calories is: " << p <<endl;
            if(p >= 1000)
            {
                cout << "You have exceeded the calorie limit! " <<endl;
                //throwing exception
                throw(p);
            }
            else
            {
                cout << "You have not exceeded the calorie limit. " <<endl;
            }
        }
        //catch block - catches a thrown exception
        catch(int x)
        {
            cout << "Exception caught by 'int' catch block: " << x << " calories" <<endl;
        }
        //catches any type of exception
        catch(...)
        {
            cout << "Exception caught by special catch block:" <<endl;
        }
    }
    //initializer list(parameterized constructor)
    Food(int a):calories(a)
    {
        cout << "Your food has " << a << " calories."  <<endl;
    }
    //copy constructor
    //constant object is taken as parameter
    Food(const Food &f)
    {
        calories = f.calories;
        cout << "Your food has" << calories << " calories."  <<endl;
    }
    //destructor
    ~Food()
    {
        cout << "Food is dumped. (destructor) "<<endl;
    }
};

//we are deriving class digestive system from class HumanBody in public mode
//concept: classes and objects, inheritance
class DigestiveSystem: public HumanBody
{
public:
    int vitamins,minerals;
    DigestiveSystem(){}
    void eating(Food &f)
    {
        cout << "You have eaten your food. " <<endl;
    }
    //function over-riding
    void digesting()
    {
        cout << "Your food is getting digested. "<<endl;
    }
};

//inheriting class excretory system from class human body(hierarchical)
//since excretory system and digestive system are inter-dependent, it is composition relation.
class ExcretorySystem: public HumanBody
{
private:
    //the interface of digestive system is visible only to excretory system, not its clients.
    DigestiveSystem d;
public:
    void absorbing()
    {
        cout << "The required contents in your food is being absorbed. " <<endl;
    }
    void excreting()
    {
        cout << "The body wastes have been excreted. "<<endl;
    }
};

//inheriting class nervous system from class human body
class NervousSystem: public HumanBody
{
public:
    int nerves,neurons;
    //concept: nested classes, also a type of composition relation
    class Brain
    {
    public:
        void instruction()
        {
            cout << "The instruction is passed. "<<endl;
        }
    };
    class SpinalCord
    {
    public:
        void reflex()
        {
            cout << "The reflex action has taken place. "<<endl;
        }
    };
};

//inheriting skeletal system from class human body
class SkeletalSystem: public HumanBody
{
private:
    int bones;
public:
    //accessing private data members using get and set functions
    //concept: data encapsulation
    void sett()
    {
        bones = 206;
    }
    void get()
    {
        cout << "You have " << bones << " bones in your body. "<<endl;
    }
};

//inheriting class muscular system from human body
//relation between muscular system and skeletal system is aggregation as bones can exist without muscles(skeleton)
class MuscularSystem: public HumanBody
{
public:
    int muslces;
    void walking()
    {
        cout << "You are walking. "<<endl;
    }
    void movement()
    {
        SkeletalSystem s;
        s.sett();
        s.get();
        cout << "You are moving your muscles. "<<endl;
    }
};

class Hormones
{
private:
    string hormone;
public:
    //friend function to access private data members of class
    friend istream &operator>>(istream &in,Hormones &h1);
    friend ostream &operator<<(ostream &out,Hormones &h1);
};

//stream operator overloaded function to get input and output
//concept: operator overloading
istream &operator >>(istream &in,Hormones &h)
{
    in >> h.hormone;
    return (in);
}
ostream &operator <<(ostream &out,Hormones &h)
{
    out << "The hormone is: " << h.hormone <<endl;
    return (out);
}

//inheriting class endocrine system from human body
class EndocrineSystem:public HumanBody
{
private:
    Hormones h1;
public:
    void secreted()
    {
        cout << "Hormones are secreted into the blood. "<<endl;
    }
};

//defining class oxygen
class Oxygen
{
public:
    float molecules;
};

//inheriting class respiratory system from human body class
//since respiratory system depends on oxygen, it is dependency relation
class RespiratorySystem: public HumanBody
{
public:
    string alveoli;
    void breathing(Oxygen &o)
    {
        cout << "You are breathing. "<<endl;
    }
};

//inheriting class reproductive system from human body class
//it is an abstract class.It cannot be instantiated, can only be inherited.
//Concept: data abstraction
class ReproductiveSystem:public HumanBody
{
public:
    //pure virtual function,should have no body in base class and should be initiated to zero(cannot be instantiated).
    virtual void birth()=0;
};

//inheriting class new born from class reproductive system.
//multi-level inheritance
class NewBorn: public ReproductiveSystem
{
public:
    //function over-riding
    void birth()
    {
        cout << "The baby is born. "<<endl;
    }
};

//deriving class circulatory system from class human body
class CirculatorySystem: public HumanBody
{
public:
    //pure virtual destructor
    virtual ~CirculatorySystem()=0;
};
//explicit destructor call
CirculatorySystem::~CirculatorySystem()
{
    cout << "Blood is leaking. (pure virtual destructor) " <<endl;
}

//deriving class blood from class circulatory system
//multi-level inheritance
class Blood:public CirculatorySystem
{
    ~Blood()
    {
        cout << "Blood is leaking. " <<endl;
    };
};

//function for file handling
void medicalRecord()
{
    string name,disease;
    int age;
    cout << "Enter the patient's name: ";
    cin >> name;
    cout << "Enter the patient's age: ";
    cin >> age;
    cout << "Enter the patient's disease: ";
    cin >> disease;
    ofstream myfile;
    myfile.open("MedicalRecord.txt",ios::out | ios::app);
    if(myfile)
    {
        myfile << name << "\t" << age << "\t" << disease<< endl;
        cout << "Contents written into file. " <<endl;
    }
    else
    {
        cout << "Unable to open file. " <<endl;
    }
    myfile.close();
}
//main function
int main()
{
    //digestive system part
    DigestiveSystem d;
    //dynamic binding, run-time polymorphism,calls digesting function of digestive system class
    HumanBody *h;
    h = &d;
    h->digesting();
    cout << endl;
    //static binding
    Food f;
    d.eating(f);
    cout << endl;
    //excretory system
    ExcretorySystem e;
    e.absorbing();
    e.excreting();
    cout << endl;
    //muscular system
    MuscularSystem m;
    m.walking();
    m.movement();
    cout << endl;
    //endocrine system
    EndocrineSystem e1;
    Hormones h1;
    cout << "Enter the hormone: ";
    cin >> h1;
    cout << h1;
    e1.secreted();
    cout << endl;
    //respiratory system
    Oxygen o1;
    RespiratorySystem r1;
    r1.breathing(o1);
    cout << endl;
    //reproductive system
    NewBorn n1;
    n1.birth();
    cout << endl;
    //circulatory system
    //pure virtual destructor call
    CirculatorySystem *c = new Blood();
    delete c;
    cout << endl;
    medicalRecord();
    return 0;
}
