#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// General functions
vector<string> strToVect(const string &str, char delim = ' ') {
    vector<string> result;
    string tmp;
    // Create stream from string
    istringstream ss(str);
    // Grab the elements from the stream, separated by delim
    while (getline(ss, tmp, delim)) {
        result.push_back(tmp);
        // Skip whitespace
        ss >> ws;
    }
    return result;
}

void showStrVect(vector<string> &v, int spos = 0, int epos = -1) {
    if (epos == -1)
        epos = v.size();
    for (int i = spos; i < epos; i++)
        cout << v[i] << endl;
}

void showStrVectOL(vector<string> &v, int spos = 0, int epos = -1, string sep = ", ") {
    if (epos == -1)
        epos = v.size();
    for (int i = spos; i < epos; i++)
        if (i == epos - 1)
            cout << v[i] << endl;
        else
            cout << v[i] << sep;
}


struct Date {
    unsigned int day, month, year;
    string full;
};

void extractDate(Date &date) {
    vector<string> temp;
    temp = strToVect(date.full, '/');
    date.day = stoi(temp[2]);
    date.month = stoi(temp[1]);
    date.year = stoi(temp[0]);
}

// Agency file functions
struct Agency {
    string name, nif, url, address, clientsFileName, packsFileName;
};

void openAgency(Agency &a) {
    ifstream a_file("agency.txt");
    getline(a_file, a.name);
    getline(a_file, a.nif);
    getline(a_file, a.url);
    getline(a_file, a.address);
    getline(a_file, a.clientsFileName);
    getline(a_file, a.packsFileName);
    a_file.close();
}

// Client file functions
struct Client {
    string name, nif, household, address, packs;
};

void readClients(vector<Client> &c, string f_name) {
    ifstream c_file(f_name);
    string str;

    while (!c_file.eof()) {
        // Adds new client to vector
        c.push_back(Client());
        // Grabs the client info from the file
        getline(c_file, c.back().name);
        getline(c_file, c.back().nif);
        getline(c_file, c.back().household);
        getline(c_file, c.back().address);
        getline(c_file, c.back().packs);
        // Discards delimiter line
        getline(c_file, str);
    }

    c_file.close();
}

void showClientVect(vector<Client> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i].name << endl;
        cout << v[i].nif << endl;
        cout << v[i].household << endl;
        cout << v[i].address << endl;
        cout << v[i].packs << endl;
    }
}

// Pack file function
struct Pack {
    int totalSeats, soldSeats, price;
    string id, mainDest;
    vector<string> destinations;
    Date startDate, endDate;
};

string lastID;

void readPacks(vector<Pack> &p, string f_name) {
    ifstream p_file(f_name);
    string str;
    vector<string> vect;

    // Grabs lastID
    getline(p_file, lastID);

    while(!p_file.eof()) {
        // Adds new client to vector
        p.push_back(Pack());

        // Gets pack id
        getline(p_file, p.back().id);

        // Gets destinations
        getline(p_file, str);
        p.back().destinations = strToVect(str, '-');
        p.back().mainDest = p.back().destinations[0];
        // Split the smaller destinations, if they exist
        if (p.back().destinations.size() > 1) {
            vect = strToVect(p.back().destinations[1], ',');
            p.back().destinations.insert(p.back().destinations.end() - 1, vect.begin(), vect.end());
            p.back().destinations.pop_back();
        }

        // Gets start date
        getline(p_file, p.back().startDate.full);
        extractDate(p.back().startDate);
        // Gets end date
        getline(p_file, p.back().endDate.full);
        extractDate(p.back().endDate);

        // Get price
        getline(p_file, str);
        p.back().price = stoi(str);

        // Get seats
        getline(p_file, str);
        p.back().totalSeats = stoi(str);
        getline(p_file, str);
        p.back().soldSeats = stoi(str);

        // Discard delimiter
        getline(p_file, str);
    }

    p_file.close();
}

void showPackVect(vector<Pack> &v) {
    cout << "Last ID: " << lastID << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i].id << endl;
        cout << v[i].mainDest << endl;
        showStrVectOL(v[i].destinations, 1, -1); // Not printed if only one main destination
        cout << v[i].startDate.full << endl;
        cout << v[i].startDate.day << '-' << v[i].startDate.month << '-' << v[i].startDate.year << endl;
        cout << v[i].endDate.full << endl;
        cout << v[i].endDate.day << '-' << v[i].endDate.month << '-' << v[i].endDate.year << endl;
        cout << v[i].price << endl;
        cout << v[i].totalSeats << endl;
        cout << v[i].soldSeats << endl;
    }
}


int main() {
    Agency a1;
    vector<Client> clients;
    vector<Pack> packs;
    vector<string> plist;
    openAgency(a1);
    readClients(clients, a1.clientsFileName);
    readPacks(packs, a1.packsFileName);
    showPackVect(packs);
}