#include <iostream>
#include <map>
#include <vector>

using namespace std;

// print sort map
void printSort(multimap<int, string, greater<int>> sortMapStudProj){
    map<int, string>::iterator it;
    for(it = sortMapStudProj.begin(); it != sortMapStudProj.end(); it++)
        cout  << (*it).second << " " << (*it).first << endl;
}

// sort decreasing order of number of signups. 
// If two or more projects have the same number of signups, they
// should be listed in alphabetical order
void sortMap(map <string, int> studentsInProject,
             map<string, string> projects){
    
    multimap<int, string, greater<int>> sortMapStudProj;
    map<string, int>::iterator it = studentsInProject.begin();
            
    // Iterate through the map and print the elements
    while (it != studentsInProject.end()){

        // count the number of students in a project
        map<string, string>:: iterator it2 = projects.begin();
        while(it2 != projects.end()){
            if(it->first == it2->second)
                it->second++;
            
            it2++;
        }

        // insert the project with the number of students for sorting
        sortMapStudProj.insert(pair<int, string>(it->second, it->first));
        it++;
    }

    printSort(sortMapStudProj);
}

int main(){

    string s;
    string projectName;
    string idStudent;

    vector <string> studentsSigned;
    map <string, int> studentsInProject;
    map<string, string> projects;

    while(s != "0"){
        
        s.clear();
        getline(cin >> ws, s);
        
        // check if is an ending input case
        if(s[0] == '1'){
            // erase all students has signed mora that one project
            for(long unsigned int i = 0; i<studentsSigned.size(); i++)
                projects.erase(studentsSigned[i]);

            sortMap(studentsInProject, projects);
            
            projects.clear();
            studentsInProject.clear();
        }

        // check if the first letter is uppercase
        if(isupper(s[0])){
            projectName.clear();
            projectName = s;
                        
            //map to save the projects names
            studentsInProject[projectName] = 0;
        }

        // check if the first letter is lowercase
        if(islower(s[0])){
            idStudent = s;

            // check if student has signed any project
            if(projects.count(idStudent)){
                if(projects[idStudent] != projectName)
                  studentsSigned.push_back(idStudent);  
            }else{
                projects[idStudent] = projectName;
            }
        }

        idStudent.clear();
    }
    return 0;
}