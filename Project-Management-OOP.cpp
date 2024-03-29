#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <stdexcept>
using namespace std;


class Resource{
private:
    string resource_name;
    string resource_type;
    string um;
    double quantity;
    double hourly_cost;
public:
    // constructor for Resource objects
    Resource(const string& resource_name_, const string& resource_type_, const string& um_, double quantity_, double hourly_cost_):
        resource_name(resource_name_), resource_type(resource_type_), um(um_), quantity(quantity_),hourly_cost(hourly_cost_){}

    // default constructor
    Resource(){}

    // overload operator<< for objects of type Resource
    friend ostream& operator<<(ostream& os, const Resource& resource)
    {
        os << "\033[1;33mResource\033[0m"<<endl;
        os << "Resource name is: "<< resource.get_resource_name()<<endl;
        os << "Resource type is: "<<resource.get_resource_type()<<endl;
        os << "Resource unity of measurement is: "<<resource.get_um()<<endl;
        os << "Resource quantity is: "<<resource.get_quantity()<<endl;
        os << "Resource hourly cost is: "<<resource.get_resource_hourly_cost()<<endl;
    }

    // overload operator>> for objects of type Resource
    friend istream& operator>>(istream& is, Resource& resource)
    {
    string name, type, um;
    double res_quantity,cost;
    cout << "Enter resource name: ";
    getline(is, name);
    cout << "Enter resource type (manpower/tech): ";
    getline(is, type);
    cout << "Enter resource unity of measurement(manhour/watts/session duration): ";
    getline(is, um);
    cout << "Enter resource quantity (number of hours): ";
    is >> res_quantity;
    cout << "Enter resource hourly cost: ";
    is >> cost;
    resource = Resource(name,type,um,res_quantity,cost);
    return is;
    }

     // overload == operator for class Resource
    bool operator==(const Resource& other) const {
        return (resource_name == other.resource_name &&
                resource_type == other.resource_type &&
                um == other.um &&
                quantity == other.quantity &&
                hourly_cost == other.hourly_cost);
    }
    // getters and setters
    double get_resource_hourly_cost()
    const {
        return hourly_cost;
    }
    void set_resource_hourly_cost(double& cost)
    {
        hourly_cost = cost;
    }
    double get_quantity()
    const {
        return quantity;
    }
    void set_quantity(double& quantity_)
    {
        quantity = quantity_;
    }
    string get_resource_name()
    const {
        return resource_name;
    }
    string get_resource_type()
    const {
        return resource_type;
    }
    string get_um()
    const {
        return um;
    }

};

class Task{
private:
    string task_name;
    int priority; // range 1-3 1=low, 2=medium, 3=high
    string task_status; //in-progress, completed,delayed
    int start_date;
    int end_date;
    vector<Resource> resources;
public:
    // constructor for Task objects
    Task(const string& task_name_, int priority_, const string& task_status_, int start_date_, int end_date_, const vector<Resource>& resources_):
        task_name(task_name_), priority(priority_), task_status(task_status_), start_date(start_date_), end_date(end_date_), resources(resources_){}

    // default constructor
    Task() = default;

      // methods
    double calculate_task_cost() const{
        double total_cost = 0.0;
        for(const auto& resource: resources)
        {
            total_cost +=  resource.get_resource_hourly_cost() * resource.get_quantity();
        }
        return total_cost;
        }

    // overload operator<< for class Task
    friend ostream& operator<<(ostream& os, const Task& task)
    {
        os << "\033[1;35mTASK\033[0m" << endl;
        os << "Task name is: "<<task.get_task_name()<<endl;
        os << "Task priority is: "<<task.get_priority()<<endl;
        os << "Task status is: "<< task.get_task_status()<<endl;
        os << "Task start date is: "<<task.get_start_date()<<endl;
        os << "Task end date is "<< task.get_end_date()<<endl;
        os << endl;
        os << "For this task, we use the following resources:" <<endl;
        os << endl;
        for(const auto& resource: task.get_resources())
        {
            os << resource <<endl;
        }
    }
    // overload operator>> for class Task
    friend istream& operator>>(istream& is, Task& task)
    {
    string name, status;
    int priority, start_date, end_date;
    cout << "Enter task name: ";
    getline(is, name);
    cout << "Enter task priority (1 for low/2 for medium/ 3 for high): ";
    is >> priority;
    is.ignore();
    cout << "Enter task status (in-progress/completed/delayed): ";
    getline(is, status);
    cout << "Enter start date: ";
    is >> start_date;
    is.ignore();
    cout << "Enter end date: ";
    is >> end_date;
    is.ignore();
    int num_resources;
    cout << "Enter number of resources for this task: ";
    is >> num_resources;
    is.ignore();
    vector<Resource> resources;
    for (int i = 0; i < num_resources; ++i) {
        Resource resource;
        is >> resource;
        resources.push_back(resource);
    }
    task = Task(name, priority, status, start_date, end_date, resources);
    return is;
    }


    // overload == operator for class Task
   bool operator==(const Task& other) const {
        return task_name == other.task_name &&
               priority == other.priority &&
               task_status == other.task_status &&
               start_date == other.start_date &&
               end_date == other.end_date &&
               resources == other.resources;
    }
    // getters and setters
    string get_task_name()
    const {
        return task_name;
    }
    string get_task_status()
    const {
        return task_status;
    }
    void set_task_status(string& status)
    {
        task_status = status;
    }
    vector<Resource> get_resources()
    const {
        return resources;
    }
    int get_priority()
    const {
        return priority;
    }
    int get_start_date()
    const {
        return start_date;
    }
    int get_end_date()
    const {
        return end_date;
    }


};


class Project{
private:
    string project_name;
    vector<Resource> project_resources;
    vector<Task> task_list;
    int start_date_p;
    int end_date_p;
    string project_status;
    double estimated_revenue;
public:
    // constructor with initialization list
    Project(const string& project_name_, const vector<Resource>& project_resources_, const vector<Task>& task_list_, int start_date_,int end_date_, const string& project_status_, const double& estimated_revenue_):
        project_name(project_name_), project_resources(project_resources_),task_list(task_list_),start_date_p(start_date_), end_date_p(end_date_), project_status(project_status_), estimated_revenue(estimated_revenue_) {}

    // copy constructor
    Project(const Project& other) : project_name(other.project_name), project_resources(other.project_resources), task_list(other.task_list),start_date_p(other.start_date_p),end_date_p(other.end_date_p), project_status(other.project_status), estimated_revenue(other.estimated_revenue){}

    // default constructor
    Project(){}

    //Destructor for project class
    ~Project(){
        project_name="";
        project_resources.clear();
        project_status="";
        task_list.clear();
        start_date_p=0;
        end_date_p=0;
        estimated_revenue=0;
    }

    // methods
    void add_Task(const Task& task) {

        vector<Task> updated_task_list = get_task_list();
        updated_task_list.push_back(task);
        set_task_list(updated_task_list);
    }


    void remove_Task(const Task& task) {

        vector<Task> updated_task_list = get_task_list();
        auto it = find(updated_task_list.begin(), updated_task_list.end(), task);
        if (it != updated_task_list.end()) {
            updated_task_list.erase(it);
            set_task_list(updated_task_list);
        }
    }


    bool modify_Task(const Task& old_task, const Task& new_task) {
        vector<Task> updated_task_list = get_task_list();
        auto it = find(updated_task_list.begin(), updated_task_list.end(), old_task);
        if (it != updated_task_list.end()) {
            *it = new_task;
            set_task_list(updated_task_list);
            return true;
        }
        return false;
    }

    double calculate_project_cost()const{
        double cost = 0.0;
        for(auto& task: get_task_list())
        {
            cost += task.calculate_task_cost();
        }
        return cost;
    }

    int calculate_duration()const{
        int duration = get_end_date_p() - get_start_date_p();
        return duration;
    }
    double calculate_daily_balance(const int& duration, const double& total_cost)const{
        return get_estimated_revenue()/duration - total_cost/duration;
    }

    // overload operator= for class Project
    Project& operator=(const Project& other)
    {
        if(this != &other)
        {
            project_name = other.project_name;
            project_resources = other.project_resources;
            task_list = other.task_list;
            start_date_p = other.start_date_p;
            end_date_p = other.end_date_p;
            project_status = other.project_status;
            estimated_revenue = other.estimated_revenue;
       }
       return *this;
    }

    // overload operator<< for Project class
    friend ostream& operator<<(ostream& os, const Project& project)
    {
        //os << "Resource:" << endl;
        os << "\033[1;32mPROJECT\033[0m"<<endl;
        os << "\033[1;32mThe project consists of a succession of tasks and each task consists of multiple resources!\033[0m"<<endl;
        os << "Project name is: "<< project.project_name<<endl;
        os << "Start date for the project is: "<<project.get_start_date_p()<<endl;
        os << "End date for the project is: "<<project.get_end_date_p()<<endl;
        os << "Project status is: "<<project.get_project_status()<<endl;
        os << "Project estimated revenue is: "<<project.get_estimated_revenue()<<endl;
        os << endl;
        os <<"The project consists of the following tasks:"<<endl;
        os << endl;
        for(const auto& task: project.get_task_list())
        {
            cout<<task;
        }
    }
    //overload operator>> for Project class
    friend istream& operator>>(istream& is, Project& project)
    {
    string name, status;
    int start_date, end_date;
    vector<Resource> project_resources;
    vector<Task> task_list;
    double estimated_revenue;

    cout << "Enter project name: ";
    getline(is, name);
    cout << "Enter project status(in-progress/delayed/completed): ";
    getline(is, status);
    cout << "Enter start date(int number): ";
    is >> start_date;
    cout << "Enter end date(int number): ";
    is >> end_date;
    cout << "Enter estimated revenue: ";
    is >> estimated_revenue;

    int num_tasks;
    cout << "Enter number of tasks for this project: ";
    is >> num_tasks;
    is.ignore();

    for (int i = 0; i < num_tasks; ++i) {
        Task task;
        is >> task;
        task_list.push_back(task);
    }
    project = Project(name, project_resources, task_list, start_date, end_date, status, estimated_revenue);
    return is;
    }


    // overload operator== for Project class
    bool operator==(const Project& other) const {
        return (project_name == other.project_name &&
                project_resources == other.project_resources &&
                task_list == other.task_list &&
                start_date_p == other.start_date_p &&
                end_date_p == other.end_date_p &&
                project_status == other.project_status);
    }
    // getters and setters
    string get_project_name()
    const {
        return project_name;
    }
    vector<Task> get_task_list()
    const {
        return task_list;
    }
    int get_start_date_p()
    const {
        return start_date_p;
    }
    int get_end_date_p()
    const {
        return end_date_p;
    }
    string get_project_status()
    const {
        return project_status;
    }
    void change_project_status(string& new_status)
    {
        project_status = new_status;
    }
    double get_estimated_revenue()
    const {
        return estimated_revenue;
    }
    void change_project_estimated_revenue(const double& new_estimated_revenue)
    {
        estimated_revenue = new_estimated_revenue;
    }
    void change_start_date(int& new_date)
    {
        start_date_p = new_date;
    }
    void change_end_date(int& end_date)
    {
        end_date_p = end_date;
    }
    void set_task_list(const vector<Task>& updated_task_list) {
        task_list = updated_task_list;
    }

};

// function which helps us to read a Project object from a file given the filename
// it returns an object of type Project
Project readProjectFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file: " + filename);
    }
    string name, status;
    int start_date, end_date;
    vector<Resource> project_resources;
    vector<Task> task_list;
    double estimated_revenue;

    if (getline(file, name) && getline(file, status) && file >> start_date >> end_date >> estimated_revenue) {
        file.ignore();
    }
    else {
        throw runtime_error("Error reading project details from file.");
    }

    int num_tasks;
    if (!(file >> num_tasks)) {
        throw runtime_error("Error reading number of tasks from file.");
    }
    file.ignore();
    for (int i = 0; i < num_tasks; ++i) {
        string task_name, task_status;
        int priority, start_date, end_date;
        vector<Resource> resources;

        if (getline(file, task_name) && file >> priority >> task_status >> start_date >> end_date) {
            file.ignore();
        } else {
            throw runtime_error("Error reading task details from file.");
        }

        int num_resources;
        if (!(file >> num_resources)) {
        throw runtime_error("Error reading number of resources from file.");
    }
    file.ignore();
    for (int i = 0; i < num_resources; ++i) {
        string resource_name, resource_type, um;
        double quantity, hourly_cost;
        if (getline(file, resource_name) && getline(file, resource_type) && getline(file, um) && file >> quantity >> hourly_cost)
        {
            file.ignore();
            resources.emplace_back(resource_name, resource_type, um,quantity,hourly_cost); //we use emplace_back method to avoid creating unnecessary copies
            project_resources.emplace_back(resource_name, resource_type, um, quantity, hourly_cost); 
        }
        else {
            throw runtime_error("Error reading resource details from file.");
        }
    }
        task_list.emplace_back(task_name, priority, task_status, start_date, end_date, resources); 
    }
    file.close();
    return Project(name, project_resources, task_list, start_date, end_date, status, estimated_revenue);
}

int main() {
    // the vector project_list will store all the data during runtime
    vector<Project> project_list;
    // simple menu using switch statement to show the functionality of classes above
    int choice;
    do {
        cout << "\033[1;36mWelcome to Project Management Menu!\033[0m"<<endl;
        cout << "1. Create a new project" << endl;
        cout << "2. Read and display project from a file" << endl;
        cout << "3. Display a project" << endl;
        cout << "4. Display cost of a project" << endl;
        cout << "5. Display project ROI and daily balance"<< endl;
        cout << "6. Add/Remove/Change a task"<<endl;
        cout << "7. Change project_status/estimated_revenue/start_date/end_date" << endl;
        cout << "8. Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                Project newProject;
                cin>>newProject;
                project_list.push_back(newProject);
                cout << "\033[1;32mYou have succesfully created a project! Please choose the next option from the menu!\033[0m"<<endl;
                cout<<endl;
                break;
            }
            case 2: {
                cout<<"Please write the name of the file!"<<endl;
                string filename;
                getline(cin, filename);
                Project P = readProjectFromFile(filename);
                project_list.push_back(P);
                cout<<endl;
                cout<<P;
                break;
            }
            case 3:
                {
                    bool project_found = false;
                    string nume_proiect;
                    cout<<"Please write the name of the project!"<<endl;
                    getline(cin, nume_proiect);
                    for(const auto& project: project_list)
                    {
                        if(project.get_project_name() == nume_proiect)
                        {
                            cout<<project;
                            project_found = true;
                        }
                    }
                    if(!project_found)
                    {
                        cout<<"\033[1;31mThe project was not found!\033[0m"<<endl;
                    }
                    break;
                }
            case 4:{
                    if(project_list.size() != 0)
                    {
                        cout<<"Please write the name of the project you want the cost of!"<<endl;
                        bool gasit = 0;
                        string nume;
                        getline(cin, nume);
                        for(auto project: project_list)
                        {
                            if(project.get_project_name() == nume)
                            {
                                gasit = 1;
                                cout<<"The cost of the project is: "<<project.calculate_project_cost()<<endl;
                            }
                        }
                        if(gasit == 0)
                        {
                            cout<< "\033[1;31mPlease rewrite the name of the project since it was not found!\033[0m"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"\033[1;31mThere is not any project!\033[0m"<<endl;
                    }
                    break;
                }
            case 5:{
                    cout << "Please write the name of the project: "<<endl;
                    string nume_proiect;
                    getline(cin, nume_proiect);

                    bool found_project = false;
                    for(auto& project : project_list) {
                        if(project.get_project_name() == nume_proiect) {

                            cout << "The ROI for the project is: "  << "\033[1;32m" << (project.get_estimated_revenue() / project.calculate_project_cost()) * 100 <<"%"<<"\033[0m"<<endl;
                            if(project.calculate_daily_balance(project.calculate_duration(),project.calculate_project_cost()) > 0)
                                cout <<"The daily balance for the project is: " << "\033[1;32m"<<"+"<< project.calculate_daily_balance(project.calculate_duration(),project.calculate_project_cost())<<"\033[0m"<<endl;
                            else
                                cout <<"The daily balance for the project is: " <<"\033[1;31m"<<"-"<< project.calculate_daily_balance(project.calculate_duration(),project.calculate_project_cost())<<"\033[0m"<<endl;
                            break;
                        }
                    }
                    break;
                }

            case 6: {
                cout<<"Please choose one of the option: Add/Remove/Change"<<endl;
                string option;
                getline(cin, option);
                if(option == "Add")
                {
                Task task;
                cin >> task;
                string project_name;
                cout << "Please enter the name of the project to which the task will be added: ";
                getline(cin, project_name);

                bool found_project = false;
                for (auto& project : project_list) {
                    if (project.get_project_name() == project_name) {
                        project.add_Task(task);
                        found_project = true;
                        cout << "\033[1;32mTask added successfully to project:\033[0m" << project_name << endl;
                }
                }

                if (!found_project) {
                    cout << "\033[1;31mProject not found!\033[0m" << endl;
                }
                break;
                }
                if(option == "Remove")
                {
                    cout << "Please write the name of the project which contains the task you want to remove!" << endl;
                    string nume_proiect;
                    getline(cin, nume_proiect);
                    Task task;
                    for (auto& project : project_list) {
                        if (project.get_project_name() == nume_proiect) {
                            cout << "Please write the name of the task you want to remove!" << endl;
                            string task_name;
                            cin >> task_name;
                            for(auto& task: project.get_task_list())
                            {
                                if(task_name == task.get_task_name())
                                {
                                    project.remove_Task(task);
                                    cout<<"\033[1;32mTask removed succesfully\033[0m"<<endl;
                                    break;
                                }
                            }
                        }
                }
                break;
                }
                if(option == "Change")
                {
                    cout << "Please write the the name of the project which contains the task you want to change!" << endl;
                    string project_name;
                    getline(cin, project_name);

                    bool found_project = false;
                    for (auto& project : project_list) {
                        if (project.get_project_name() == project_name) {
                            cout << "Enter the name of the task you want to change:" << endl;
                            string task_name;
                            getline(cin, task_name);
                            for(auto& task: project.get_task_list())
                            {
                                if(task.get_task_name()==task_name)
                                {
                                    cout << "Enter the updated details of the task:" << endl;
                                    Task new_task;
                                    cin >> new_task;
                                    if (project.modify_Task(task, new_task)) {
                                        cout << "\033[1;32mTask modified successfully in project: \033[0m" << project_name << endl;
                                    }
                                    else {
                                        cout << "\033[1;31mTask not found in project: \033[0m" << project_name << endl;
                                    }
                                found_project = true;
                                break;
                                }
                            }
                        }
                    }

                    if (!found_project) {
                        cout << "\033[1;31mProject not found! \033[0m" << endl;
                    }
                    break;
                }
                }
                case 7 : {
                    cout <<"Please choose one option from: project_status/estimated_revenue/start_date/end_date!"<<endl;
                    string option;
                    getline(cin, option);
                    if(option == "project_status")
                    {
                    bool found_project = false;
                    cout << "Please write the name of the project you want to change the status of!" << endl;
                    string name;
                    getline(cin, name);
                    string new_status;
                    cout << "Please write the new status! (in-progress/completed/delayed)" << endl;
                    getline(cin, new_status);
                    for(auto& project: project_list)
                    {
                        if(project.get_project_name() == name)
                        {
                            found_project = true;
                            project.change_project_status(new_status);
                            cout << "\033[1;32mStatus changed succesfully!\033[0m"<<endl;
                            break;
                        }
                    }
                if(!found_project)
                {
                    cout <<"\033[1;31mProject not found! \033[0m" << endl;
                }
                break;
                }
                if(option == "estimated_revenue")
                {
                    bool found_project = false;
                    cout << "Please write the name of the project you want to change the estimated revenue of!" << endl;
                    string name;
                    getline(cin, name);
                    double new_estimated_revenue;
                    cout << "Please write the new estimated revenue!" << endl;
                    cin>>new_estimated_revenue;
                    for(auto& project: project_list)
                    {
                        if(project.get_project_name() == name)
                        {
                            found_project = true;
                            project.change_project_estimated_revenue(new_estimated_revenue);
                            cout << "\033[1;32mEstimated revenue changed succesfully!\033[0m"<<endl;
                            break;
                        }
                    }
                if(!found_project)
                {
                    cout <<"\033[1;31mProject not found! \033[0m" << endl;
                }
                break;

                }
                if(option == "start_date")
                {
                    bool found_project = false;
                    cout << "Please write the name of the project you want to change the start date of!" << endl;
                    string name;
                    getline(cin, name);
                    int new_start_date;
                    cout << "Please write the new start date!" << endl;
                    cin >> new_start_date;
                    for(auto& project: project_list)
                    {
                        if(project.get_project_name() == name)
                        {
                            found_project = true;
                            project.change_start_date(new_start_date);
                            cout << "\033[1;32mStart date changed succesfully!\033[0m" <<endl;
                            break;
                        }
                    }
                if(!found_project)
                {
                    cout <<"\033[1;31mProject not found! \033[0m" << endl;
                }
                break;
                }
                if(option == "end_date")
                {
                     bool found_project = false;
                    cout << "Please write the name of the project you want to change the end date of!" << endl;
                    string name;
                    getline(cin, name);
                    int new_end_date;
                    cout << "Please write the new end date!" << endl;
                    cin >> new_end_date;
                    for(auto& project: project_list)
                    {
                        if(project.get_project_name() == name)
                        {
                            found_project = true;
                            project.change_end_date(new_end_date);
                            cout << "\033[1;32mEnd date changed succesfully!\033[0m"<<endl;
                            break;
                        }
                    }
                if(!found_project)
                {
                    cout <<"\033[1;31mProject not found! \033[0m" << endl;
                }
                break;
                }

                }
            case 8: {cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;}

    }

}while(choice != 8);
return 0;
}
