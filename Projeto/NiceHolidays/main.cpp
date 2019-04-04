#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Diplay functions
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
        for (int i = spos; i < epos; i++) // TODO use size_t instead of int
            if (i == epos - 1)
                cout << v[i] << endl;
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

// Input functions
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

// Date handling
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

// Address handling
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
                    address.display_format = str;
                    extractAddress(address, false);
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

// NIF handling
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

// Housekeeping
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

// Pack handling
void grabPacks(vector<int> &packs, bool edit = false) {
    string str; // TODO Verify if pack is in packs file
    while (true) {
        try {
            if (edit) {
                cout << setw(4) << left << '|' << "Pacotes adquiridos (";
                showIntVect(packs);
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
        } catch (int e) {
            cinERR("ERRO: Introduza pacotes separados por ,");
            cout << endl;
        }
    }
}

// Agency file functions
struct Agency {
    string name, nif, url, clientsFileName, packsFileName; // TODO verify nif
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
    agency_file << agency.packsFileName << endl;
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

// Client file functions
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
                clients_file << clients[i].packs[j] << endl;
            else
                clients_file << clients[i].packs[j] << "; ";
        }
        if (i != clients.size() - 1)
            clients_file << "::::::::::" << endl;
    }
    clients_file.close();
}

void addClient(vector<Client> &clients) {
    clientsModify = true;
    string str;

    // Adds new client to vector
    clients.push_back(Client());

    // Grabs the client info from cin
    cout << "Nome do cliente: ";
    getline(cin, clients.back().name);
    // Grabs NIF from cin, checking errors;
    grabNIF(clients.back().nif);
    // Grabs household size from cin, checking errors
    grabHousehold(clients.back().household);
    // Address extraction
    grabAddress(clients.back().address);
    grabPacks(clients.back().packs);
}


// Pack file function
struct Pack {
    int id, totalSeats, soldSeats, price;
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

void addPack(vector<Pack> &packs) {
    string str;
    vector<string> vect;

    // Adds new pack to vector
    packs.push_back(Pack());

    // Sets pack id
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

void showPackVect(vector<Pack> &v) {
    cout << setw(2) << ' ' << "Pacotes de viagem disponíveis:" << endl;
    // [DEBUG] cout << "> Last ID: " << lastID << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "/" << endl;
        cout << setw(4) << left << '|' << "Pack ID: " << v[i].id << endl;
        cout << setw(4) << left << '|' << "Destino principal: " << v[i].mainDest << endl;
        if (v[i].destinations.size() > 1)
            cout << setw(4) << left << '|' << "Destinos adicionais: ";
        showStrVect(v[i].destinations, 1, -1, true); // Not printed if only one main destination
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

// Main menu functions
void mainMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);
void clientsMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);
void packsMenu(Agency &agency, vector<Client> &clients, vector<Pack> &packs);
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
                getline(cin, str); // TODO Implement saving to file
                if (str == "N" || str == "n") {
                    save = false;
                    cout << "Fechado sem guardar" << endl;
                } else
                    cout << "Alterações guardadas" << endl;
                break;
            // TODO implement purchasing
            // TODO implement sales report
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

// Clients menu functions
void clientsMenuSelect(Agency &agency, vector<Client> &clients, vector<Pack> &packs) {
    string str = "";
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
                showClientVect(clients);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                clientsMenu(agency, clients, packs);
                break;
            // TODO search for and edit client
            case 3:
                addClient(clients);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                clientsMenu(agency, clients, packs);
                break;
            // TODO delet client
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

// Packs menu functions
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
                showPackVect(packs);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                packsMenu(agency, clients, packs);
                break;
            // TODO search for and edit packs
            case 3:
                addPack(packs);
                cout << endl << "ENTER para voltar atrás";
                getline(cin, str);
                packsMenu(agency, clients, packs);
                break;
            // TODO delet pack
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

// Agency menu functions
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
    return 0;
}