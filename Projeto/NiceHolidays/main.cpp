#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//
// Diplay functions
//
bool isNumeric(const string &str);

string trim(string &str) {
    auto str_init = str.find_first_not_of(" \t");
    if (str_init == string::npos)
        return ""; // String is all whitespace
    auto str_end = str.find_last_not_of(" \t");
    auto str_range = str_end - str_init + 1;

    return str.substr(str_init, str_range);
}

vector<string> strToVect(const string &str, char delim = ' ') {
    // Splits a string into a vector of strings
    vector<string> result;
    string tmp;
    // Create stream from string
    istringstream ss(str);
    // Grab the elements from the stream, separated by delim
    while (getline(ss, tmp, delim)) {
        result.push_back(trim(tmp));
        // Skip whitespace
        ss >> ws;
    }
    return result;
}

vector<int> strToIntVect(const string &str, char delim = ' ') {
    // Splits a string into a vector of UNSIGNED integers
    vector<int> result;
    string tmp;
    // Create stream from string
    istringstream ss(str);
    // Grab the elements from the stream, separated by delim
    // If string is empty return an empty vector
    while (getline(ss, tmp, delim)) {
        tmp = trim(tmp);
        if (isNumeric(tmp))
            result.push_back(stoi(tmp));
        else
            throw 100;
        // Skip whitespace
        ss >> ws;
    }
    return result;
}

void showStrVect(const vector<string> &v, int spos = 0, long epos = -1, bool oneline = false, const string sep = ", ") {
    // Prints a vector of strings, either all on the same line with a separator, or one per line
    if (epos == -1)
        epos = v.size();
    if (oneline) {
        for (int i = spos; i < epos; i++)
            if (i == epos - 1)
                cout << v[i];
            else
                cout << v[i] << sep;
    }
    else {
        for (int i = spos; i < epos; i++)
            cout << v[i] << endl;
    }
}

void showIntVect(vector<int> &v, int spos = 0, int epos = -1, bool oneline = false, const string sep = ", ") {
    // Prints a vector of ints, either all on the same line with a separator, or one per line
    if (epos == -1)
        epos = v.size();
    if (oneline) {
        for (int i = spos; i < epos; i++)
            if (i == epos - 1)
                cout << v[i];
            else
                cout << v[i] << sep;
    }
    else {
        for (int i = spos; i < epos; i++)
            cout << v[i] << endl;
    }
}

void line(int size, char ch = '-') {
    // Prints a line of specified size with specified character
    cout << setfill(ch) << setw(size) << "" << endl << setfill(' ');
}


//
// Input functions
//
void cinERR(string message) {
    // Outputs an error message and clears cin and flags
    cerr << message;
    cout << endl;
    cin.clear();
}

void getOption(int &dest, string message = "Opção: ") {
    // Tries to get a valid int option from cin to use in a switch-case
    string str;

    while (true) {
        try {
            cout << endl << message;
            getline(cin, str);
            cout << endl;
            dest = stoi(str);
            break;
        } catch (invalid_argument) {
            str = "";
            cinERR("ERRO: Entrada inválida, tente outra vez");
        }
    }
}

bool isNumeric(const string &str) {
    if (str.empty())
        return false;
    for (int i = 0; i < str.length(); i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}


//
// Date handling
//
struct Date {
    unsigned int day, month, year;
    string full;
    bool valid = false;
};

void extractDate(Date &date, bool file = false) {
    try {
        if (date.full.empty()) throw 100;
        vector<string> temp;
        temp = strToVect(date.full, '/');
        if (file) {
            if (temp[0].length() != 4 || temp[1].length() != 2 || temp[2].length() != 2)
                throw 2;
            date.day = stoi(temp[2]);
            date.month = stoi(temp[1]);
            date.year = stoi(temp[0]);
        } else {
            if (temp[0].length() != 2 || temp[1].length() != 2 || temp[2].length() != 4)
                throw 2;
            date.day = stoi(temp[0]);
            date.month = stoi(temp[1]);
            date.year = stoi(temp[2]);
        }
        if (date.day > 31)
            throw 31;
        if (date.day > 29 && date.month == 2)
            throw 29;
        if (date.month > 12)
            throw 12;
        if (date.day <= 0 || date.month <= 0 || date.year <= 0)
            throw 0;
        date.valid = true;
    } catch(invalid_argument) {
        date.valid = false;
        cinERR("Introduza uma data válida no formato DD/MM/YYYY");
    } catch (int &e) {
        date.valid = false;
        cinERR("Introduza uma data válida no formato DD/MM/YYYY");
    }
}

bool cmpDate(Date &date_1, Date &date_2) {
    // Checks if date_1 is later than or the same as date_2
    if (date_1.year < date_2.year)
        return false;
    else if (date_1.month < date_2.month && date_1.year == date_2.year)
        return false;
    else if (date_1.day < date_2.day && date_1.month == date_2.month && date_1.year == date_2.year)
        return false;
    return true;
}


//
// Address handling
//
struct Address {
    // rua / número da porta / número do andar / código postal / localidade
    string street, door, level, postcode, town, file_format, display_format;
};

void extractAddress(Address &address, bool file = true) {
    vector<string> temp;
    if (file) {
        temp = strToVect(address.file_format, '/');
        if (temp.size() != 5)
            throw 100;
        address.display_format = temp[0] + ", " + temp[1] + ", " + temp[2] + ", " + temp[3] + ", " + temp[4];
    }
    else {
        temp = strToVect(address.display_format, ',');
        if (temp.size() != 5)
            throw 100;
        address.file_format = temp[0] + " / " + temp[1] + " / " + temp[2] + " / " + temp[3] + " / " + temp[4];
    }
    address.street = temp[0];
    address.door = temp[1];
    address.level = temp[2];
    address.postcode = temp[3];
    address.town = temp[4];
}

void grabAddress(Address &address, bool edit = false) {
    string str;
    while (true) {
        try {
            if (edit) {
                cout << setw(4) << left << '|' << "Morada (" << address.display_format << "): ";
                getline(cin, str);
                if (str != "") {
                    Address tempAddress;
                    tempAddress.display_format = str;
                    extractAddress(tempAddress, false); // Throws exception if address in invalid
                    address = tempAddress;
                    str = "";
                }
                break;
            } else {
                cout << "Morada: ";
                getline(cin, address.display_format);
                extractAddress(address, false);
                break;
            }
        } catch (int e) {
            cinERR("ERRO: Introduza a morada no formato: rua, número da porta, número do andar, código postal, "
                    "localidade, sem omissões");
            cout << endl;
        }
    }
}


//
// NIF handling
//
void grabNIF(string &nif, bool edit = false) {
    string str;
    while (true) {
        try {
            if (edit) {
                cout << setw(4) << left << '|' << "NIF (" << nif << "): ";
                getline(cin, str);
                if (str != "") {
                    if (!(str.length() == 9) || !isNumeric(str))
                        throw 100;
                    nif = str;
                }
                break;
            } else {
                cout << "NIF: ";
                getline(cin, str);
                if (!(str.length() == 9) || !isNumeric(str))
                    throw 100;
                nif = str;
                break;
            }
        } catch (int e) {
            cinERR("ERRO: Introduza um NIF válido");
            cout << endl;
        }
    }
}


//
// Housekeeping
//
void grabHousehold(string &hhold, bool edit = false) {
    string str;
    while (true) {
        try {
            if (edit) {
                cout << setw(4) << left << '|' << "Nº de pessoas no agregado (" << hhold << "): ";
                getline(cin, str);
                if (str != "") {
                    if (!isNumeric(str))
                        throw 100;
                    hhold = str;
                }
                break;
            } else {
                cout << "Nº de pessoas no agregado: ";
                getline(cin, str);
                if (!isNumeric(str))
                    throw 100;
                hhold = str;
                break;
            }
        } catch (int e) {
            cinERR("ERRO: Introduza um número válido");
            cout << endl;
        }
    }
}


//
// Pack handling
//
void grabPacks(vector<int> &packs, bool edit = false) {
    string str; // TODO Verify if pack is in packs file
    while (true) {
        try {
            if (edit) {
                cout << setw(4) << left << '|' << "Pacotes adquiridos (";
                showIntVect(packs, 0, -1, true);
                cout << "): ";
                getline(cin, str);
                packs = strToIntVect(str, ',');
                break;
            } else {
                cout << "Pacotes adquiridos: ";
                getline(cin, str);
                packs = strToIntVect(str, ',');
                break;
            }
        } catch (int &e) {
            cinERR("ERRO: Introduza pacotes separados por ,");
            cout << endl;
        }
    }
}


//
// Agency file functions
//
struct Agency {
    string name, nif, url, clientsFileName, packsFileName;
    Address address;
};

void openAgency(Agency &agency) {
    ifstream agency_file("agency.txt");
    getline(agency_file, agency.name);
    getline(agency_file, agency.nif);
    getline(agency_file, agency.url);
    getline(agency_file, agency.address.file_format);
    extractAddress(agency.address);
    getline(agency_file, agency.clientsFileName);
    getline(agency_file, agency.packsFileName);
    agency_file.close();
}

bool agencyModify = false;

void writeAgency(Agency &agency, string agency_f_name) {
    ofstream agency_file("agency.txt");
    agency_file << agency.name << endl;
    agency_file << agency.nif << endl;
    agency_file << agency.url << endl;
    agency_file << agency.address.file_format << endl;
    agency_file << agency.clientsFileName << endl;
    agency_file << agency.packsFileName;
    agency_file.close();
}

void showAgency(Agency &agency) {
    cout << setw(2) << ' ' << agency.name << endl;
    cout << "/" << endl;
    cout << setw(4) << left << '|' << "NIF: " << agency.nif << endl;
    cout << setw(4) << left << '|' << "Website: " << agency.url << endl;
    cout << setw(4) << left << '|' << "Morada: " << agency.address.display_format << endl;
    cout << setw(4) << left << '|' << "Ficheiro de clientes: " << agency.clientsFileName << endl;
    cout << setw(4) << left << '|' << "Ficheiro de pacotes: " << agency.packsFileName << endl;
    cout << "\\_" << endl;
}

void editAgency(Agency &agency) {
    agencyModify = true;
    string str = "";
    cout << setw(2) << ' ' << "A EDITAR AGÊNCIA" << endl;
    cout << "/" << endl;

    cout << setw(4) << left << '|' << "Nome (" << agency.name << "): ";
    getline(cin, str);
    if (str != "") {
        agency.name = str;
        str = "";
    }

    cout << setw(4) << left << '|' << "NIF (" << agency.nif << "): ";
    getline(cin, str);
    if (str != "") {
        agency.nif = str;
        str = "";
    }

    cout << setw(4) << left << '|' << "Website (" << agency.url << "): ";
    getline(cin, str);
    if (str != "") {
        agency.url = str;
        str = "";
    }

    grabAddress(agency.address, true);

    cout << setw(4) << left << '|' << "Ficheiro de clientes (" << agency.clientsFileName << "): ";
    getline(cin, str);
    if (str != "") {
        agency.clientsFileName = str;
        str = "";
    }

    cout << setw(4) << left << '|' << "Ficheiro de pacotes (" << agency.packsFileName << "): ";
    getline(cin, str);
    if (str != "") {
        agency.packsFileName = str;
        str = "";
    }
    cout << "\\_" << endl;
}


//
// Client file functions
//
struct Client {
    string name, nif, household;
    Address address;
    vector<int> packs;
};

void readClients(vector<Client> &clients, string f_name) {
    ifstream clients_file(f_name);
    string str;

    while (getline(clients_file, str)) {
        // Adds new client to vector
        clients.push_back(Client());

        // Grabs the client info from the file
        clients.back().name = str;
        getline(clients_file, clients.back().nif);
        getline(clients_file, clients.back().household);
        getline(clients_file, clients.back().address.file_format);
        extractAddress(clients.back().address);
        getline(clients_file, str);
        clients.back().packs = strToIntVect(str, ';');

        // Discards delimiter line
        getline(clients_file, str);
    }

    clients_file.close();
}

void showClientVect(vector<Client> &v) {
    cout << setw(2) << ' ' << "Clientes: " << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "/" << endl;
        cout << setw(4) << left << '|' << "Nome: " << v[i].name << endl;
        cout << setw(4) << left << '|' << "NIF: " << v[i].nif << endl;
        cout << setw(4) << left << '|' << "Nº de pessoas no agregado: " << v[i].household << endl;
        cout << setw(4) << left << '|' << "Morada: " << v[i].address.display_format << endl;
        cout << setw(4) << left << '|' << "Pacotes adquiridos: ";
        showIntVect(v[i].packs, 0, -1, true);
        cout << endl;
        cout << "\\_" << endl;
    }
}

bool clientsModify = false;

void writeClients(vector<Client> &clients, string f_name) {
    ofstream clients_file(f_name);
    for (int i = 0; i < clients.size(); i++) {
        clients_file << clients[i].name << endl;
        clients_file << clients[i].nif << endl;
        clients_file << clients[i].household << endl;
        clients_file << clients[i].address.file_format << endl;
        for (int j = 0; j < clients[i].packs.size(); j++){
            if (j == clients[i].packs.size() - 1)
                clients_file << clients[i].packs[j];
            else
                clients_file << clients[i].packs[j] << "; ";
        }
        if (i != clients.size() - 1)
            clients_file << endl << "::::::::::" << endl;
    }
    clients_file.close();
}

void addClient(vector<Client> &clients) {
    clientsModify = true;
    string str;

    // Adds new client to vector
    clients.push_back(Client());

    // Grabs the client info from cin
    while (true) {
        try {
            cout << "Nome do cliente: ";
            getline(cin, str);
            if (str.empty()) throw 100;
            clients.back().name = str;
            break;
        } catch (int &e){
            cinERR("ERRO: Entrada inválida");
        }
    }
    // Grabs NIF from cin, checking errors;
    grabNIF(clients.back().nif);
    // Grabs household size from cin, checking errors
    grabHousehold(clients.back().household);
    // Address extraction
    grabAddress(clients.back().address);
    // Pack extraction (can be empty if client hasn't bought any packs yet
    grabPacks(clients.back().packs);
}

int findClient(vector<Client> &clients, string nif) {
    for (int i = 0; i < clients.size(); i++) {
        if(clients.at(i).nif == nif)
            return i;
    }
    return -1;
}

int editClient(vector<Client> &clients, string nif) {
    int pos = findClient(clients, nif);
    if (pos == -1) {
        cerr << "Cliente não encontrado!";
        return -1;
    }

    clientsModify = true;

    string str = "";
    vector<string> vect;
    cout << setw(2) << ' ' << "A EDITAR CLIENTE (NIF:  " << nif << ")" << endl;
    cout << "/" << endl;

    cout << setw(4) << left << '|' << "Nome (" << clients.at(pos).name << "): ";
    getline(cin, str);
    if (!str.empty()) {
        clients.at(pos).name = str;
        str.clear();
    }

    while(true) {
        cout << setw(4) << left << '|' << "NIF (" << clients.at(pos).nif << "): ";
        getline(cin, str);
        if (str.empty()) {
            break;
        } else {
            if (isNumeric(str) && str.length() == 9) {
                clients.at(pos).nif = str;
                break;
            } else {
                cinERR("ERRO: Introduza um NIF válido");
            }
        }
    }

    while(true) {
        cout << setw(4) << left << '|' << "Nº de pessoas no agregado (" << clients.at(pos).household << "): ";
        getline(cin, str);
        if (str.empty()) {
            break;
        } else {
            if (isNumeric(str)) {
                clients.at(pos).household = str;
                break;
            } else {
                cinERR("ERRO: Introduza um número positivo válido");
            }
        }
    }

    grabAddress(clients.at(pos).address, true);

    grabPacks(clients.at(pos).packs, true);

    cout << "\\_" << endl;
}

int deleteClient(vector<Client> &clients, string nif) {
    int pos = findClient(clients, nif);
    if (pos == -1) {
        cerr << "Cliente não encontrado!";
        return -1;
    }

    clientsModify = true;

    clients.erase(clients.begin()+pos);
    cout << "Cliente com NIF " << nif << " apagado";
}


//
// Pack file functions
//
struct Pack {
    int id, totalSeats, soldSeats;
    double price;
    string mainDest;
    vector<string> destinations;
    Date startDate, endDate;
};

int lastID;

void readPacks(vector<Pack> &p, string f_name) {
    ifstream p_file(f_name);
    string str;
    vector<string> vect;

    // Grabs lastID
    getline(p_file, str);
    lastID = stoi(str);

    while(getline(p_file, str)) {
        // Adds new pack to vector
        p.push_back(Pack());

        // Gets pack id
        p.back().id = stoi(str);

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
        extractDate(p.back().startDate, true);
        // Gets end date
        getline(p_file, p.back().endDate.full);
        extractDate(p.back().endDate, true);

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

bool packsModify = false;

void addPack(vector<Pack> &packs) {
    packsModify = true;

    string str;
    vector<string> vect;

    // Adds new pack to vector
    packs.push_back(Pack());

    // Sets pack idpacks.at(pos).destinations
    lastID++;
    packs.back().id = lastID;
    cout << "Pack ID: " << lastID << endl;

    // Gets destinations
    while (true) {
        try {
            cout << "Destinos (principal, seguido de - e adicionais): ";
            getline(cin, str);
            // If user inputs an empty line, throw exception
            if (str.empty()) throw 100;
            // Start parsing the input
            packs.back().destinations = strToVect(str, '-');
            packs.back().mainDest = packs.back().destinations[0];
            // Split the other destinations, if they exist
            if (packs.back().destinations.size() > 1) {
                vect = strToVect(packs.back().destinations[1], ',');
                packs.back().destinations.insert(packs.back().destinations.end() - 1, vect.begin(), vect.end());
                packs.back().destinations.pop_back();
            }
            break;
        } catch (int &e) {
            cinERR("ERRO: Entrada inválida");
        }
    }


    // Gets start date
    while (!packs.back().startDate.valid) {
        cout << "Data de início: ";
        getline(cin, packs.back().startDate.full);
        extractDate(packs.back().startDate);
    }
    // Gets end date
    while (!packs.back().endDate.valid) {
        cout << "Data de fim: ";
        getline(cin, packs.back().endDate.full);
        extractDate(packs.back().endDate);
    }

    // Get price
    while (true) {
        try {
            cout << "Preço por pessoa: ";
            getline(cin, str);
            if (!isNumeric(str)) throw 100;
            packs.back().price = stoi(str);
            break;
        } catch (int &e) {
            cinERR("ERRO: Entrada inválida");
        }
    }

    // Get seats
    while (true) {
        try {
            cout << "Nº de vagas: ";
            getline(cin, str);
            if (!isNumeric(str)) throw 100;
            packs.back().totalSeats = stoi(str);
            break;
        } catch (int &e) {
            cinERR("ERRO: Entrada inválida");
        }
    }
    while (true) {
        try {
            cout << "Vagas vendidas: ";
            getline(cin, str);
            if (!isNumeric(str)) throw 100;
            packs.back().soldSeats = stoi(str);
            break;
        } catch (int &e) {
            cinERR("ERRO: Entrada inválida");
        }
    }
}

void writePacks(vector<Pack> &packs, string f_name) {
    ofstream packs_file(f_name);
    packs_file << lastID << endl;
    for (int i = 0; i < packs.size(); i++) {
        packs_file << packs[i].id << endl;
        packs_file << packs[i].mainDest;
        if (packs[i].destinations.size() > 1) {
            packs_file << " - ";
            for (int j = 1; j < packs[i].destinations.size(); j++)
                if (j == packs[i].destinations.size() - 1)
                    packs_file << packs[i].destinations[j] << endl;
                else
                    packs_file << packs[i].destinations[j] << ", ";
        } else
            packs_file << endl;
        packs_file << packs[i].startDate.year << '/' << packs[i].startDate.month << '/' << packs[i].startDate.day << endl;
        packs_file << packs[i].endDate.year << '/' << packs[i].endDate.month << '/' << packs[i].endDate.day << endl;
        packs_file << packs[i].price << endl;
        packs_file << packs[i].totalSeats << endl;
        packs_file << packs[i].soldSeats;
        if (i != packs.size() - 1)
            packs_file << endl << "::::::::::" << endl;
    }
    packs_file.close();
}

// Shows all packs
void showPackVect(vector<Pack> &v) {
    cout << setw(2) << ' ' << "Pacotes de viagem disponíveis:" << endl;
    // [DEBUG] cout << "> Last ID: " << lastID << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "/" << endl;
        cout << setw(4) << left << '|' << "Pack ID: " << v[i].id << endl;
        cout << setw(4) << left << '|' << "Destino principal: " << v[i].mainDest << endl;
        if (v[i].destinations.size() > 1) {
            cout << setw(4) << left << '|' << "Destinos adicionais: ";
            showStrVect(v[i].destinations, 1, -1, true);
            cout << endl; // Not printed if only one main destination
        }
        cout << setw(4) << left << '|' << "Data de início: " << v[i].startDate.full << endl;
        // [DEBUG] cout << setw(4) << left << '|' << "" << v[i].startDate.day << '-' << v[i].startDate.month << '-' << v[i].startDate.year << endl;
        cout << setw(4) << left << '|' << "Data de fim: " << v[i].endDate.full << endl;
        // [DEBUG] cout << setw(4) << left << '|' << "" << v[i].endDate.day << '-' << v[i].endDate.month << '-' << v[i].endDate.year << endl;
        cout << setw(4) << left << '|' << "Preço pacote: " << v[i].price << endl;
        cout << setw(4) << left << '|' << "Nº de vagas: " << v[i].totalSeats << endl;
        cout << setw(4) << left << '|' << "Vagas vendidas: " << v[i].soldSeats << endl;
        cout << "\\_" << endl;
    }
}

// Shows packs selected by range vector, displaying a message before
void showPackVect(vector<Pack> &v, vector<int> range, string message) {
    cout << setw(2) << ' ' << message << endl;

    for (int i = 0; i < range.size(); i++) {
        cout << "/" << endl;
        cout << setw(4) << left << '|' << "Pack ID: " << v[range[i]].id << endl;
        cout << setw(4) << left << '|' << "Destino principal: " << v[range[i]].mainDest << endl;
        if (v[range[i]].destinations.size() > 1) {
            cout << setw(4) << left << '|' << "Destinos adicionais: ";
            showStrVect(v[range[i]].destinations, 1, -1, true);
            cout << endl; // Not printed if only one main destination
        }
        cout << setw(4) << left << '|' << "Data de início: " << v[range[i]].startDate.full << endl;
        cout << setw(4) << left << '|' << "Data de fim: " << v[range[i]].endDate.full << endl;
        cout << setw(4) << left << '|' << "Preço pacote: " << v[range[i]].price << endl;
        cout << setw(4) << left << '|' << "Nº de vagas: " << v[range[i]].totalSeats << endl;
        cout << setw(4) << left << '|' << "Vagas vendidas: " << v[range[i]].soldSeats << endl;
        cout << "\\_" << endl;
    }
}

void showPack(vector<Pack> &packs, int i) {
    cout << setw(2) << ' ' << "Pacote " << packs.at(i).id << endl;

    cout << "/" << endl;
    cout << setw(4) << left << '|' << "Pack ID: " << packs.at(i).id << endl;
    cout << setw(4) << left << '|' << "Destino principal: " << packs.at(i).mainDest << endl;
    if (packs.at(i).destinations.size() > 1) {
        cout << setw(4) << left << '|' << "Destinos adicionais: ";
        showStrVect(packs.at(i).destinations, 1, -1, true);
        cout << endl; // Not printed if only one main destination
    }
    cout << setw(4) << left << '|' << "Data de início: " << packs.at(i).startDate.full << endl;
    cout << setw(4) << left << '|' << "Data de fim: " << packs.at(i).endDate.full << endl;
    cout << setw(4) << left << '|' << "Preço pacote: " << packs.at(i).price << endl;
    cout << setw(4) << left << '|' << "Nº de vagas: " << packs.at(i).totalSeats << endl;
    cout << setw(4) << left << '|' << "Vagas vendidas: " << packs.at(i).soldSeats << endl;
    cout << "\\_" << endl;

}

vector<int> findPacks(vector<Pack> &packs, string &dest) {
    vector<int> result;
     for (int i = 0; i < packs.size(); i++) {
        if(find(packs.at(i).destinations.begin(), packs.at(i).destinations.end(), dest) != packs.at(i).destinations.end())
            result.push_back(i);
     }
    return result;
}

vector<int> findPacks(vector<Pack> &packs, Date &date_1, Date &date_2) {
    vector<int> result;
    for (int i = 0; i < packs.size(); i++) {
        if(cmpDate(packs[i].startDate, date_1) && cmpDate(date_2, packs[i].endDate))
            result.push_back(i);
    }
    return result;
}

vector<int> findPacks(vector<Pack> &packs, string dest, Date &date_1, Date &date_2) {
    vector<int> result;
    for (int i = 0; i < packs.size(); i++) {
        if(find(packs.at(i).destinations.begin(), packs.at(i).destinations.end(), dest) != packs.at(i).destinations.end()
        && cmpDate(packs[i].startDate, date_1) && cmpDate(date_2, packs[i].endDate))
            result.push_back(i);
    }
    return result;
}

int findPacks(vector<Pack> &packs, int id) {
    for (int i = 0; i < packs.size(); i++) {
        if(packs.at(i).id == id || packs.at(i).id == -id)
            return i;
    }
    return -1;
}

int editPack(vector<Pack> &packs, int id) {
    int pos = findPacks(packs, id);
    if (pos == -1) {
        cerr << "Pacote não encontrado!";
        return -1;
    }

    packsModify = true;

    string str = "";
    vector<string> vect;
    cout << setw(2) << ' ' << "A EDITAR PACOTE " << id << endl;
    cout << "/" << endl;

    cout << setw(4) << left << '|' << "Destinos (" << packs.at(pos).mainDest;
    if (packs.at(pos).destinations.size() > 1) {
        cout << " - ";
        showStrVect(packs.at(pos).destinations, 1, -1, true);
    }
    cout << "): ";
    getline(cin, str);
    if (!str.empty()) {
        // Start parsing the input
        packs.at(pos).destinations = strToVect(str, '-');
        packs.at(pos).mainDest = packs.at(pos).destinations[0];
        // Split the other destinations, if they exist
        if (packs.at(pos).destinations.size() > 1) {
            vect = strToVect(packs.at(pos).destinations[1], ',');
            packs.at(pos).destinations.insert(packs.at(pos).destinations.end() - 1, vect.begin(), vect.end());
            packs.at(pos).destinations.pop_back();
        }
        str.clear();
    }


    while(true) {
        cout << setw(4) << left << '|' << "Data de início (" << packs.at(pos).startDate.day << "/" << packs.at(pos).startDate.month << "/" << packs.at(pos).startDate.year  << "): ";
        getline(cin, str);
        Date tempDate;
        tempDate.full = str;
        if (str.empty()) {
            break;
        } else {
            extractDate(tempDate);
            if (tempDate.valid) {
                packs.at(pos).startDate = tempDate;
                break;
            }
        }
    }

    while(true) {
        cout << setw(4) << left << '|' << "Data de fim (" << packs.at(pos).endDate.day << "/" << packs.at(pos).endDate.month << "/" << packs.at(pos).endDate.year  << "): ";
        getline(cin, str);
        Date tempDate;
        tempDate.full = str;
        if (str.empty()) {
            break;
        } else {
            extractDate(tempDate);
            if (tempDate.valid) {
                packs.at(pos).endDate = tempDate;
                break;
            }
        }
    }

    while(true) {
        cout << setw(4) << left << '|' << "Preço pacote (" << packs.at(pos).price << "): ";
        getline(cin, str);
        if (str.empty()) {
            break;
        } else {
            if (isNumeric(str)) {
                packs.at(pos).price = stoi(str);
                break;
            }
        }
    }

    while(true) {
        cout << setw(4) << left << '|' << "Nº de vagas (" << packs.at(pos).totalSeats << "): ";
        getline(cin, str);
        if (str.empty()) {
            break;
        } else {
            if (isNumeric(str)) {
                packs.at(pos).totalSeats = stoi(str);
                break;
            }
        }
    }

    while(true) {
        cout << setw(4) << left << '|' << "Vagas vendidas (" << packs.at(pos).soldSeats << "): ";
        getline(cin, str);
        if (str.empty()) {
            break;
        } else {
            if (isNumeric(str)) {
                packs.at(pos).soldSeats = stoi(str);
                break;
            }
        }
    }

    cout << "\\_" << endl;
}

int deletePack(vector<Pack> &packs, int id) {
    int pos = findPacks(packs, id);
    if (pos == -1) {
        cerr << "Pacote não encontrado!";
        return -1;
    }

    packsModify = true;

    packs.erase(packs.begin()+pos);
    cout << "Pacote " << id << " apagado";
}


//
// Sales report functions
//
void salesReport(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    line(35);
    cout << right << "Relatório " << agency.name << endl;
    line(35);
    cout << setw(4) << left << '-' << "Número de clientes: " << clients.size() << endl;
    cout << setw(4) << left << '-' << "Número de pacotes: " << packs.size() << endl;

    long n_sales = 0, np_sales = 0;
    double v_sales = 0, vp_sales = 0;
    for (int i = 0; i < packs.size(); i++) {
        n_sales += packs.at(i).soldSeats;
        v_sales += packs.at(i).soldSeats * packs.at(i).price;
        np_sales += packs.at(i).totalSeats - packs.at(i).soldSeats;
        vp_sales += (packs.at(i).totalSeats - packs.at(i).soldSeats) * packs.at(i).price;
    }

    cout << setw(4) << left << '-' << "Número de pacotes vendidos: " << n_sales << endl;
    cout << setw(4) << left << '-' << "Valor de pacotes vendidos: " << v_sales << endl;
    cout << setw(4) << left << '-' << "Número de pacotes por vender: " << np_sales << endl;
    cout << setw(4) << left << '-' << "Valor de pacotes por vender: " << vp_sales << endl;


}


//
// Main menu functions
//
void mainMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);
void clientsMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);
void packsMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);
void viewPacksMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);
void agencyMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);

bool save = true;

void mainMenuSelect(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    string str = "";
    int opt;
    bool valid;

    do {
        getOption(opt);
        valid = true;
        switch (opt) {
            case 0:
                cout << "Guardar alterações (S/n): ";
                getline(cin, str);
                if (str == "N" || str == "n") {
                    save = false;
                    cout << "Fechado sem guardar" << endl;
                } else
                    cout << "Alterações guardadas" << endl;
                break;
            // TODO implement purchasing
            case 2:
                salesReport(agency,clients,packs);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                mainMenu(agency, clients, packs);
                break;
            case 3:
                clientsMenu(agency, clients, packs);
                break;
            case 4:
                packsMenu(agency, clients, packs);
                break;
            case 5:
                agencyMenu(agency, clients, packs);
                break;
            default:
                valid = false;
                cinERR("ERRO: Opção não existe, tente outra vez");
                break;
        }
    } while (!valid);
}

void mainMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    line(35);
    cout << right << setfill(' ') << setw(22) << "INÍCIO" << endl;
    line(35);
    cout << setw(4) << left << '|' << "1. Registar compra" << endl;
    cout << setw(4) << left << '|' << "2. Relatório" << endl;
    cout << setw(4) << left << '|' << "3. Gerir clientes" << endl;
    cout << setw(4) << left << '|' << "4. Gerir pacotes" << endl;
    cout << setw(4) << left << '|' << "5. Gerir agência" << endl;
    cout << endl << setw(4) << left << '|' << "0. Fechar" << endl;
    line(35);

    mainMenuSelect(agency, clients, packs);
}


//
// Clients menu functions
//
void clientsMenuSelect(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    string str = "";
    int opt;
    bool valid;

    do {
        getOption(opt);
        valid = true;
        switch (opt) {
            case 0: {
                mainMenu(agency, clients, packs);
                break;
            }
            case 1: {
                showClientVect(clients);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                clientsMenu(agency, clients, packs);
                break;
            }
            case 2: {
                while (true) {
                    cout << "NIF do cliente a editar: ";
                    getline(cin, str);
                    if (isNumeric(str) && str.length() == 9) {
                        editClient(clients, str);
                        break;
                    }
                    cinERR("ERRO: Introduza um NIF válido");
                }
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                clientsMenu(agency, clients, packs);
                break;
            }
            case 3: {
                addClient(clients);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                clientsMenu(agency, clients, packs);
                break;
            }
            case 4: {
                while (true) {
                    cout << "NIF do cliente a apagar: ";
                    getline(cin, str);
                    if (isNumeric(str) && str.length() == 9) {
                        deleteClient(clients, str);
                        break;
                    }
                    cinERR("ERRO: Introduza um NIF válido");
                }
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                clientsMenu(agency, clients, packs);
                break;
            }
            default:
                valid = false;
                cinERR("ERRO: Opção inválida, tente outra vez");
                break;
        }
    } while (!valid);
}

void clientsMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    line(35);
    cout << right << setfill(' ') << setw(22) << "CLIENTES" << endl;
    line(35);
    cout << setw(4) << left << '|' << "1. Ver clientes" << endl;
    cout << setw(4) << left << '|' << "2. Procurar e editar cliente" << endl;
    cout << setw(4) << left << '|' << "3. Novo cliente" << endl;
    cout << setw(4) << left << '|' << "4. Eliminar cliente" << endl;
    cout << endl << setw(4) << left << '|' << "0. Voltar atrás" << endl;
    line(35);

    clientsMenuSelect(agency, clients, packs);
}


//
// Packs menu functions
//
void packsMenuSelect(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    string str;
    int opt;
    bool valid;

    do {
        getOption(opt);
        valid = true;
        switch (opt) {
            case 0:
                mainMenu(agency, clients, packs);
                break;
            case 1:
                viewPacksMenu(agency, clients, packs);
                break;
            case 2:
                while (true) {
                    cout << "ID de pacote a editar: ";
                    getline(cin, str);
                    if (isNumeric(str)) {
                        editPack(packs, stoi(str));
                        break;
                    }
                    cinERR("ERRO: Introduza um ID válido");
                }
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                packsMenu(agency, clients, packs);
                break;
            case 3:
                addPack(packs);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                packsMenu(agency, clients, packs);
                break;
            case 4:
                while (true) {
                    cout << "ID de pacote a apagar: ";
                    getline(cin, str);
                    if (isNumeric(str)) {
                        deletePack(packs, stoi(str));
                        break;
                    }
                    cinERR("ERRO: Introduza um ID válido");
                }
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                packsMenu(agency, clients, packs);
                break;
            default:
                valid = false;
                cinERR("ERRO: Opção inválida, tente outra vez");
                break;
        }
    } while (!valid);
}

void packsMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    line(35);
    cout << right << setfill(' ') << setw(22) << "PACKS" << endl;
    line(35);
    cout << setw(4) << left << '|' << "1. Ver pacotes" << endl;
    cout << setw(4) << left << '|' << "2. Procurar e editar pacote" << endl;
    cout << setw(4) << left << '|' << "3. Novo pacote" << endl;
    cout << setw(4) << left << '|' << "4. Eliminar pacote" << endl;
    cout << endl << setw(4) << left << '|' << "0. Voltar atrás" << endl;
    line(35);

    packsMenuSelect(agency, clients, packs);
}

void viewPacksMenuSelect(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    string str;
    int opt;
    bool valid;

    do {
        getOption(opt);
        valid = true;
        switch (opt) {
            case 0: {
                packsMenu(agency, clients, packs);
                break;
            }
            case 1: {// Show all packs
                showPackVect(packs);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                viewPacksMenu(agency, clients, packs);
                break;
            }
            case 2: {// Show packs by destination
                string dest, message;
                vector<int> selected;
                cout << "Destino: ";
                getline(cin, dest);
                message = "Pacotes com o destino " + dest;
                selected = findPacks(packs, dest);
                if (!selected.empty())
                    showPackVect(packs, selected, message);
                else
                    cout << "Nenhum pacote com o destino " << dest;
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                viewPacksMenu(agency, clients, packs);
                break;
            }
            case 3: {// Show packs by date
                Date date_1, date_2;
                while (!date_1.valid) {
                    cout << "Data de início: ";
                    getline(cin, date_1.full);
                    extractDate(date_1);
                }
                while (!date_2.valid) {
                    cout << "Data de início: ";
                    getline(cin, date_2.full);
                    extractDate(date_2);
                }
                string message;
                vector<int> selected;
                message = "Pacotes entre as datas " + date_1.full + " e " + date_2.full;
                selected = findPacks(packs, date_1, date_2);
                if (!selected.empty())
                    showPackVect(packs, selected, message);
                else
                    cout << "Nenhum pacote entre as datas " << date_1.full << " e " << date_2.full;
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                viewPacksMenu(agency, clients, packs);
                break;
            }
            case 4: {// Show packs by destination
                string dest, message;
                Date date_1, date_2;
                vector<int> selected;
                cout << "Destino: ";
                getline(cin, dest);
                while (!date_1.valid) {
                    cout << "Data de início: ";
                    getline(cin, date_1.full);
                    extractDate(date_1);
                }
                while (!date_2.valid) {
                    cout << "Data de início: ";
                    getline(cin, date_2.full);
                    extractDate(date_2);
                }
                message = "Pacotes com o destino " + dest + " entre as datas " + date_1.full + " e " + date_2.full;
                selected = findPacks(packs, dest, date_1, date_2);
                if (!selected.empty())
                    showPackVect(packs, selected, message);
                else
                    cout << "Nenhum pacote com o destino " << dest << " entre as datas " << date_1.full << " e " << date_2.full;
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                viewPacksMenu(agency, clients, packs);
                break;
            }
            case 5: {
                while (true) {
                    cout << "ID de pacote a pesquisar: ";
                    getline(cin, str);
                    if (isNumeric(str)) {
                        int pos = findPacks(packs, stoi(str));
                        if (pos != -1)
                            showPack(packs, pos);
                        else
                            cout << "Pacote não encontrado!";
                        break;
                    }
                    cinERR("ERRO: Introduza um ID válido");
                }
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                viewPacksMenu(agency, clients, packs);
                break;
            }
            default:
                valid = false;
                cinERR("ERRO: Opção inválida, tente outra vez");
                break;
        }
    } while (!valid);
}

void viewPacksMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    line(35);
    cout << right << setfill(' ') << setw(22) << "VER PACKS" << endl;
    line(35);
    cout << setw(4) << left << '|' << "1. Todos" << endl;
    cout << setw(4) << left << '|' << "2. Por destino" << endl;
    cout << setw(4) << left << '|' << "3. Por data" << endl;
    cout << setw(4) << left << '|' << "4. Por destino/data" << endl;
    cout << setw(4) << left << '|' << "5. Por ID" << endl;
    cout << endl << setw(4) << left << '|' << "0. Voltar atrás" << endl;
    line(35);

    viewPacksMenuSelect(agency, clients, packs);
}


//
// Agency menu functions
//
void agencyMenuSelect(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    string str;
    int opt;
    bool valid;

    do {
        getOption(opt);
        valid = true;
        switch (opt) {
            case 0:
                mainMenu(agency, clients, packs);
                break;
            case 1:
                showAgency(agency);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                agencyMenu(agency, clients, packs);
                break;
            case 2:
                editAgency(agency);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                agencyMenu(agency, clients, packs);
                break;
            default:
                cinERR("ERRO: Opção inválida, tente outra vez");
                agencyMenuSelect(agency, clients, packs);
                break;
        }
    } while (!valid);

}

void agencyMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    line(35);
    cout << right << setfill(' ') << setw(22) << "AGÊNCIA" << endl;
    line(35);
    cout << setw(4) << left << '|' << "1. Ver informação" << endl;
    cout << setw(4) << left << '|' << "2. Editar informação" << endl;
    cout << endl << setw(4) << left << '|' << "0. Voltar atrás" << endl;
    line(35);

    agencyMenuSelect(agency, clients, packs);
}



int main() {
    // Initialize variables
    Agency agency;
    vector<Client> clients;
    vector<Pack> packs;

    // Read data from files
    openAgency(agency);
    readClients(clients, agency.clientsFileName);
    readPacks(packs, agency.packsFileName);

    // Menu
    cout << "* NiceHolidays GEST v1.0 BETA *" << endl;
    mainMenu(agency, clients, packs);

    // Testing area
    if (agencyModify && save)
        writeAgency(agency, "agency.txt");
    if (clientsModify && save)
        writeClients(clients, agency.clientsFileName);
    if (packsModify && save)
        writePacks(packs, agency.packsFileName);


    return 0;
}