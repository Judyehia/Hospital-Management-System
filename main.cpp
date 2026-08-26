#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// ========== ENUMERATIONS ========== //
enum Department {
    CARDIOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    PEDIATRICS,
    EMERGENCY,
    GENERAL
};

enum RoomType {
    GENERAL_WARD,
    ICU,
    PRIVATE_ROOM,
    SEMI_PRIVATE
};

// ========== EMERGENCY CASE CLASS ========== //
// Advanced Feature: priority_queue
class EmergencyCase {
private:
    int patientId;
    int severity;

public:
    EmergencyCase(int pid, int s);

    int getPatientId() const;
    int getSeverity() const;

    // Higher severity = higher priority
    bool operator<(const EmergencyCase& other) const;
};
EmergencyCase::EmergencyCase(int pid, int s)
{
    patientId = pid;
    severity = s;
}

int EmergencyCase::getPatientId() const
{
    return patientId;
}

int EmergencyCase::getSeverity() const
{
    return severity;
}

bool EmergencyCase::operator<(const EmergencyCase& other) const
{
    return severity < other.severity;
}


// ========== PATIENT CLASS ========== //
class Patient {
private:
    int id;
    string name;
    int age;
    string contact;

    // Data Structures
    stack<string> medicalHistory;
    queue<string> testQueue;
    vector<string> prescriptions;

    bool isAdmitted;
    RoomType roomType;

    // Advanced Feature: Billing
    double bill;

public:
    // Constructor
    Patient(int pid, string n, int a, string c)
    {
        id=pid;
        name=n;
        age=a;
        contact=c;
        isAdmitted=false;
        bill=0;
    }
    // ========== ORIGINAL FEATURES ========== //

    void admitPatient(RoomType type)
    {
      if(isAdmitted)
     { cout << "Patient is already admitted." << endl;
      return;
     }
     isAdmitted=true;
     roomType=type;
     medicalHistory.push("Patient admitted to hospital");

    switch (type)
    {
    case GENERAL_WARD:
      addBill(500);
      break;
    case ICU:
      addBill(3000);
      break;
    case PRIVATE_ROOM:
      addBill(1500);
      break;
    case SEMI_PRIVATE:
      addBill(1000);
      break;
    }

    }
    void dischargePatient()
    {
        if(!isAdmitted)
        {
             cout << "Patient is not currently admitted." << endl;
             return;
        }
    isAdmitted=false;
    medicalHistory.push("Patient discharged from hospital");
    }
    void addMedicalRecord(string record)
    {medicalHistory.push(record);}

    void requestTest(string testName)
    {
        testQueue.push(testName);
        medicalHistory.push("Test requested: "+testName);
    }
    string performTest()
    { if(testQueue.empty())
        return "No tests pending" ;
      else
      { string testName=testQueue.front();
        testQueue.pop();
        medicalHistory.push("Test performed: "+testName);
        addBill(300);
        return testName;
      }
    }

    void displayHistory()
    { stack<string> temp=medicalHistory;
        if (medicalHistory.empty())
        {
            cout << "No history is found." << endl;
        }
        while (!temp.empty())
        {
         cout << "- " << temp.top() <<endl;
         temp.pop();
        }
    }

    int getId()
    { return id;}
    string getName()
    {
      return name;
    }
    bool getAdmissionStatus()
    { return isAdmitted;}


    // ========== NEW FEATURES ========== //

    // Medical Tests
    void displayPendingTests()
    {
         if(testQueue.empty())
        {
            cout<<"No tests pending." <<endl;
            return;
        }
        cout << "Pending Tests:" << endl;
        queue<string> copy=testQueue;
        while(!copy.empty())
        {
       cout << "- " << copy.front() <<endl;
       copy.pop();
        }

    }

    // Prescriptions
    void addPrescription(string medicine)
    {
        prescriptions.push_back(medicine);
        medicalHistory.push("Prescription added: " + medicine);
        addBill(100);
    }
    void displayPrescriptions()
    { if(prescriptions.empty())
        { cout << "No prescriptions." << endl;
         return;}
         cout << "Prescriptions:" << endl;
     for (int i = 0; i < prescriptions.size(); i++)
         cout << "- " << prescriptions[i] << endl;
    }

    // Billing
    void addBill(double amount)
    {
        bill=bill+amount;

    }
    double getBill()
     {return bill; }

    void displayBill()
{
    cout << "========== PATIENT BILL ==========" << endl;
    cout << "Patient ID: " << id << endl;
    cout << "Patient Name: " << name << endl;
    cout << "Total Bill: $" << bill << endl;
    cout << "==================================" << endl;
}
    // Additional Getters
    int getAge()
    {
        return age;
    }
    string getContact()
    {
     return contact;
    }
    RoomType getRoomType()
    {
      return roomType;
    }
};


// ========== DOCTOR CLASS ========== //
class Doctor {
private:
    int id;
    string name;
    Department department;

    // Queue of patients waiting for doctor
    queue<int> appointmentQueue;

public:
    // Constructor
    Doctor(int did, string n, Department d);

    // ========== ORIGINAL FEATURES ========== //

    void addAppointment(int patientId);
    int seePatient();

    int getId();
    string getName();
    string getDepartment();

    // ========== NEW FEATURES ========== //

    // Display waiting patients
    void displayAppointments();

    // Cancel appointment
    void cancelAppointment(int patientId);

    // Number of waiting patients
    int getAppointmentCount();
};


// ========== DOCTOR CLASS IMPLEMENTATION ========== //


Doctor::Doctor(int did, string n, Department d) {
    id = did;
    name = n;
    department = d;
}

void Doctor::addAppointment(int patientId) {
    appointmentQueue.push(patientId);
}

int Doctor::seePatient() {
    if (appointmentQueue.empty()) {
        return -1;
    }

    int patientId = appointmentQueue.front();
    appointmentQueue.pop();

    return patientId;
}

int Doctor::getId() {
    return id;
}

string Doctor::getName() {
    return name;
}

string Doctor::getDepartment() {
    switch (department) {
        case CARDIOLOGY:
            return "Cardiology";
        case NEUROLOGY:
            return "Neurology";
        case ORTHOPEDICS:
            return "Orthopedics";
        case PEDIATRICS:
            return "Pediatrics";
        case EMERGENCY:
            return "Emergency";
        case GENERAL:
            return "General";
        default:
            return "Unknown";
    }
}

void Doctor::displayAppointments() {
    if (appointmentQueue.empty()) {
        cout << "No appointments." << endl;
        return;
    }

    cout << "Appointment Queue:" << endl;

    queue<int> temp = appointmentQueue;

    while (!temp.empty()) {
        cout << "- Patient ID: " << temp.front() << endl;
        temp.pop();
    }
}

void Doctor::cancelAppointment(int patientId) {
    if (appointmentQueue.empty()) {
        cout << "No appointments available." << endl;
        return;
    }

    queue<int> temp;
    bool found = false;

    while (!appointmentQueue.empty()) {
        int currentPatient = appointmentQueue.front();
        appointmentQueue.pop();

        if (currentPatient == patientId && !found) {
            found = true;
        } else {
            temp.push(currentPatient);
        }
    }

    appointmentQueue = temp;

    if (found) {
        cout << "Appointment cancelled successfully." << endl;
    } else {
        cout << "Appointment not found." << endl;
    }
}

int Doctor::getAppointmentCount() {
    return appointmentQueue.size();
}

// ========== HOSPITAL CLASS ========== //
class Hospital {
private:

    // Main collections
    vector<Patient> patients;
    vector<Doctor> doctors;

    // Original emergency queue
    queue<int> emergencyQueue;

    // Advanced emergency queue
    priority_queue<EmergencyCase> priorityEmergencyQueue;

    // Counters
    int patientCounter;
    int doctorCounter;

    // ========== ROOM MANAGEMENT ========== //

    int generalRooms;
    int icuRooms;
    int privateRooms;
    int semiPrivateRooms;


public:

    // Constructor
    Hospital() {
        patientCounter = 1;
        doctorCounter = 1;
        generalRooms = 20;
        icuRooms = 5;
        privateRooms = 10;
        semiPrivateRooms = 10;

        patients = vector<Patient>();
        doctors = vector<Doctor>();
    }

    // =====================================================
    // ORIGINAL FEATURES
    // ===================================================== //

    int registerPatient(string name, int age, string contact) {
        int id = patientCounter;

        Patient newPatient(id, name, age, contact);
        patients.push_back(newPatient);

        patientCounter++;

        return id;
    }

    int addDoctor(string name, Department dept) {
        int id = doctorCounter;

        Doctor newDoctor(id, name, dept);
        doctors.push_back(newDoctor);

        doctorCounter++;

        return id;
    }

    void admitPatient(int patientId, RoomType type)
{
    for (auto &patient : patients)
    {
        if (patient.getId() == patientId)
        {
            if (!isRoomAvailable(type))
            {
                cout << "No room available for this room type." << endl;
                return;
            }

            patient.admitPatient(type);



return;
        }
    }

    cout << "Patient with ID " << patientId << " not found." << endl;
}


    void addEmergency(int patientId)
{
    emergencyQueue.push(patientId);
}
    int handleEmergency()
{
    if (emergencyQueue.empty())
    {
        cout << "No emergencies in queue." << endl;
        return -1;
    }

    int patientId = emergencyQueue.front();
    emergencyQueue.pop();

    cout << "Handled emergency for patient: "
         << patientId << endl;

    return patientId;
}

    void bookAppointment(int doctorId, int patientId)
{
    Doctor* doctor = nullptr;
    Patient* patient = nullptr;

    for (auto &d : doctors)
    {
        if (d.getId() == doctorId)
        {
            doctor = &d;
            break;
        }
    }

    for (auto &p : patients)
    {
        if (p.getId() == patientId)
        {
            patient = &p;
            break;
        }
    }

    if (doctor == nullptr)
    {
        cout << "Doctor with ID " << doctorId << " not found." << endl;
        return;
    }

    if (patient == nullptr)
    {
        cout << "Patient with ID " << patientId << " not found." << endl;
        return;
    }

    doctor->addAppointment(patientId);

    cout << "Appointment booked for patient "
         << patientId << " with doctor "
         << doctorId << endl;
}

    void displayPatientInfo(int patientId)
{
    Patient* patient = findPatient(patientId);

    if (patient == nullptr)
    {
        cout << "Patient with ID " << patientId
             << " not found." << endl;
        return;
    }

    cout << "Patient Information:" << endl;
    cout << "ID: " << patient->getId() << endl;
    cout << "Name: " << patient->getName() << endl;
    cout << "Admission Status: "
         << (patient->getAdmissionStatus() ?
             "Admitted" : "Not Admitted") << endl;

    cout << "Medical History for "
         << patient->getName()
         << " (ID: " << patient->getId() << "):"
         << endl;

    patient->displayHistory();
}

    void displayDoctorInfo(int doctorId)
{
    Doctor* doctor = findDoctor(doctorId);

    if (doctor == nullptr)
    {
        cout << "Doctor with ID " << doctorId
             << " not found." << endl;
        return;
    }

    cout << "Doctor Information:" << endl;
    cout << "ID: " << doctor->getId() << endl;
    cout << "Name: " << doctor->getName() << endl;
    cout << "Department: "
         << doctor->getDepartment() << endl;
}

    // =====================================================
    // NEW FEATURE 1
    // Find Patient
    // ===================================================== //

    Patient* findPatient(int patientId)
{
    for (auto &patient : patients)
    {
        if (patient.getId() == patientId)
        {
            return &patient;
        }
    }

    return nullptr;
}

    // =====================================================
    // NEW FEATURE 2
    // Find Doctor
    // ===================================================== //

   Doctor* findDoctor(int doctorId)
{
    for (auto &doctor : doctors)
    {
        if (doctor.getId() == doctorId)
        {
            return &doctor;
        }
    }

    return nullptr;
}

    // =====================================================
    // NEW FEATURE 3
    // Search Patient By Name
    // ===================================================== //

    void searchPatientByName(string name) {
        bool found = false;
        for (auto &patient : patients) {
            if (patient.getName() == name) {
                cout<<"Patient ID: "<<patient.getId()<<endl;
                cout<<"Name: "<<patient.getName()<<endl;
                cout<<"Age: "<<patient.getAge()<<endl;
                cout<<"Contact: "<<patient.getContact()<<endl;
                cout<<"Admitted: "<<(patient.getAdmissionStatus() ? "Yes" : "No")<<endl;
                found = true;
            }
        }
        if (!found) {
            cout<<"No patient found with name: "<<name<<endl;
        }
    }

    // =====================================================
    // NEW FEATURE 4
    // Discharge Patient
    // ===================================================== //

    void dischargePatient(int patientId)
{
    for (auto &patient : patients)
    {
        if (patient.getId() == patientId)
        {
            if (!patient.getAdmissionStatus())
            {
                cout << "Patient is not currently admitted." << endl;
                return;
            }

            patient.dischargePatient();
            cout << "Patient discharged successfully." << endl;
            return;
        }
    }

    cout << "Patient with ID " << patientId << " not found." << endl;
}

    // =====================================================
    // NEW FEATURE 5
    // Request Medical Test
    // ===================================================== //

    void requestPatientTest(int patientId, string testName) {
        Patient* patient = findPatient(patientId);
        if (patient) {
            patient->requestTest(testName);
            cout <<"Test requested successfully. "<<endl;
        } else {
            cout<<"Patient with ID "<<patientId<<" not found."<<endl;
        }
    }

    // =====================================================
    // NEW FEATURE 6
    // Perform Medical Test
    // ===================================================== //
void performPatientTest(int patientId)
{
    Patient* patient = findPatient(patientId);

    if (patient)
    {
        string testResult = patient->performTest();

        if (testResult == "No tests pending")
        {
            cout << "No pending tests for patient ID: "
                 << patientId << endl;
        }
        else
        {
            cout << "Test result/action: " << testResult << endl;
        }
    }
    else
    {
        cout << "Patient with ID "
             << patientId << " not found." << endl;
    }
}

    // =====================================================
    // NEW FEATURE 7
    // Display Pending Tests
    // ===================================================== //

    void displayPatientTests(int patientId) {
        Patient* patient = findPatient(patientId);
        if (patient) {
            patient->displayPendingTests();
        } else {
            cout<<"Patient with ID "<<patientId<<" not found."<<endl;
        }
    }

    // =====================================================
    // NEW FEATURE 8
    // Add Prescription
    // ===================================================== //

    void prescribeMedicine(int patientId, string medicine) {
        Patient* patient = findPatient(patientId);
        if (patient) {
            patient->addPrescription(medicine);
            cout << "Medicine prescribed successfully." << endl;
        } else {
            cout<<"Patient with ID "<<patientId<<" not found."<<endl;
        }
    }

    // =====================================================
    // NEW FEATURE 9
    // Display Prescriptions
    // ===================================================== //

    void displayPrescriptions(int patientId) {
        Patient* patient = findPatient(patientId);
        if (patient) {
            patient->displayPrescriptions();
        } else {
            cout<<"Patient with ID "<<patientId<<" not found."<<endl;
        }
    }

    // =====================================================
    // NEW FEATURE 10
    // Patient Bill
    // ===================================================== //

    void displayPatientBill(int patientId) {
        Patient* patient = findPatient(patientId);
        if (patient) {
            patient->displayBill();
        } else {
            cout<<"Patient with ID "<<patientId<<" not found."<<endl;
        }
    }

    // =====================================================
    // NEW FEATURE 11
    // Priority Emergency
    // ===================================================== //

    void addPriorityEmergency(int patientId, int severity)
{
    if (findPatient(patientId) == nullptr)
    {
        cout << "Patient with ID " << patientId << " not found." << endl;
        return;
    }

    if (severity < 1 || severity > 5)
    {
        cout << "Severity must be between 1 and 5." << endl;
        return;
    }

    EmergencyCase newCase(patientId, severity);
    priorityEmergencyQueue.push(newCase);
    cout << "Emergency added with severity "
     << severity << endl;
}


    // =====================================================
    // NEW FEATURE 12
    // Handle Priority Emergency
    // ===================================================== //

    int handlePriorityEmergency()
{
    if (priorityEmergencyQueue.empty())
    {
        cout << "No priority emergencies." << endl;
        return -1;
    }

    EmergencyCase topCase = priorityEmergencyQueue.top();
    priorityEmergencyQueue.pop();

    cout << "Handling patient " << topCase.getPatientId()
         << " with severity " << topCase.getSeverity() << endl;

    return topCase.getPatientId();
}

    // =====================================================
    // NEW FEATURE 13
    // Room Availability
    // ===================================================== //

    bool isRoomAvailable(RoomType type) {
        switch (type) {
            case GENERAL_WARD:
                return generalRooms > 0;
            case ICU:
                return icuRooms > 0;
            case PRIVATE_ROOM:
                return privateRooms > 0;
            case SEMI_PRIVATE:
                return semiPrivateRooms > 0;
            default:
                return false;
        }
    }

    // =====================================================
    // NEW FEATURE 14
    // Display Room Status
    // ===================================================== //

    void displayRoomStatus()
{
    cout << "========== ROOM STATUS ==========" << endl;
    cout << "General Ward: " << generalRooms << endl;
    cout << "ICU: " << icuRooms << endl;
    cout << "Private Rooms: " << privateRooms << endl;
    cout << "Semi Private Rooms: " << semiPrivateRooms << endl;
    cout << "=================================" << endl;
}
    // =====================================================
    // NEW FEATURE 15
    // Display All Patients
    // ===================================================== //

    void displayAllPatients()
{
    if (patients.empty())
    {
        cout << "No patients registered." << endl;
        return;
    }

    cout << "========== ALL PATIENTS ==========" << endl;

    for (auto &patient : patients)
    {
        cout << "ID: " << patient.getId()
             << " | Name: " << patient.getName()
             << " | Age: " << patient.getAge()
             << " | Status: "
             << (patient.getAdmissionStatus()
                 ? "Admitted" : "Not Admitted")
             << endl;
    }
}

    // =====================================================
    // NEW FEATURE 16
    // Display All Doctors
    // ===================================================== //

    void displayAllDoctors()
{
    if (doctors.empty())
    {
        cout << "No doctors registered." << endl;
        return;
    }

    cout << "========== ALL DOCTORS ==========" << endl;

    for (auto &doctor : doctors)
    {
        cout << "ID: " << doctor.getId()
             << " | Name: " << doctor.getName()
             << " | Department: "
             << doctor.getDepartment()
             << " | Appointments: "
             << doctor.getAppointmentCount()
             << endl;
    }
}

    // =====================================================
    // NEW FEATURE 17
    // Display Doctor Appointments
    // ===================================================== //

    // Looks up the doctor and calls displayAppointments().
    void displayDoctorAppointments(int doctorId) {
        if (Doctor* doctor = findDoctor(doctorId)) {
            doctor->displayAppointments();
        } else {
            cout<<"Doctor with ID "<<doctorId<<" not found."<<endl;
        }
    }

    // =====================================================
    // NEW FEATURE 18
    // Cancel Appointment
    // ===================================================== //

    void cancelAppointment( int doctorId, int patientId) {
        if (Doctor* doctor = findDoctor(doctorId)) {
            doctor->cancelAppointment(patientId);
        } else {
            cout<<"Doctor with ID "<<doctorId<<" not found."<<endl;
        }
    }

    // =====================================================
    // NEW FEATURE 19
    // Doctor Sees Next Patient
    // ===================================================== //

    void doctorSeePatient(int doctorId) {
        if (Doctor* doctor = findDoctor(doctorId)) {
            int patientId = doctor->seePatient();
            if (patientId == -1) {
                cout << "No patients waiting." << endl;
            } else {
                cout << doctor->getName()
     << " is now seeing patient "
     << patientId << endl;
            }
        } else {
            cout << "Doctor with ID " << doctorId << " not found." << endl;
        }
    }

    // =====================================================
    // NEW FEATURE 20
    // Hospital Statistics
    // ===================================================== //

    void displayStatistics()
{
    int admittedCount = 0;
    double totalBilled = 0;

    for (auto &patient : patients)
    {
        if (patient.getAdmissionStatus())
            admittedCount++;

        totalBilled += patient.getBill();
    }

    cout << "========== HOSPITAL STATISTICS ==========" << endl;
    cout << "Total Patients: " << patients.size() << endl;
    cout << "Total Doctors: " << doctors.size() << endl;
    cout << "Admitted Patients: " << admittedCount << endl;
    cout << "Waiting Emergencies: " << emergencyQueue.size() << endl;
    cout << "Priority Emergencies: "
         << priorityEmergencyQueue.size() << endl;
    cout << "Total Generated Bills: $" << totalBilled << endl;
    cout << "=========================================" << endl;
}
};


// ========== MAIN PROGRAM ========== //
int main() {

    Hospital hospital;


    // =====================================================
    // TEST CASE 1
    // Registering patients
    // ===================================================== //

    int p1 =
        hospital.registerPatient(
            "John Doe",
            35,
            "555-1234"
        );

    int p2 =
        hospital.registerPatient(
            "Jane Smith",
            28,
            "555-5678"
        );

    int p3 =
        hospital.registerPatient(
            "Mike Johnson",
            45,
            "555-9012"
        );


    // =====================================================
    // TEST CASE 2
    // Adding doctors
    // ===================================================== //

    int d1 =
        hospital.addDoctor(
            "Dr. Smith",
            CARDIOLOGY
        );

    int d2 =
        hospital.addDoctor(
            "Dr. Brown",
            NEUROLOGY
        );

    int d3 =
        hospital.addDoctor(
            "Dr. Lee",
            PEDIATRICS
        );


    // =====================================================
    // TEST CASE 3
    // Admitting patients
    // ===================================================== //

    hospital.admitPatient(
        p1,
        PRIVATE_ROOM
    );

    hospital.admitPatient(
        p2,
        ICU
    );

    // Try admitting already admitted patient
    hospital.admitPatient(
        p1,
        SEMI_PRIVATE
    );


    // =====================================================
    // TEST CASE 4
    // Booking appointments
    // ===================================================== //

    hospital.bookAppointment(
        d1,
        p1
    );

    hospital.bookAppointment(
        d1,
        p2
    );

    hospital.bookAppointment(
        d2,
        p3
    );

    // Invalid doctor
    hospital.bookAppointment(
        999,
        p1
    );

    // Invalid patient
    hospital.bookAppointment(
        d1,
        999
    );
// =====================================================
    // TEST CASE 5
    // Handling medical tests
    // ===================================================== //

    hospital.requestPatientTest(
        p1,
        "Blood Test"
    );

    hospital.requestPatientTest(
        p1,
        "X-Ray"
    );

    hospital.requestPatientTest(
        p1,
        "MRI"
    );

    hospital.displayPatientTests(
        p1
    );

    hospital.performPatientTest(
        p1
    );

    hospital.displayPatientTests(
        p1
    );




    // =====================================================
    // TEST CASE 6
    // Emergency cases
    // ===================================================== //

    hospital.addEmergency(p3);

    hospital.addEmergency(p1);

    int emergencyPatient =
        hospital.handleEmergency();

    emergencyPatient =
        hospital.handleEmergency();

    emergencyPatient =
        hospital.handleEmergency();

    // No more emergencies



    // =====================================================
    // TEST CASE 7
    // Discharging patients
    // ===================================================== //

    hospital.dischargePatient(
        p1
    );


    // =====================================================
    // TEST CASE 8
    // Displaying information
    // ===================================================== //

    hospital.displayPatientInfo(
        p1
    );

    hospital.displayPatientInfo(
        p2
    );

    hospital.displayPatientInfo(
        999
    );


    hospital.displayDoctorInfo(
        d1
    );

    hospital.displayDoctorInfo(
        d2
    );

    hospital.displayDoctorInfo(
        999
    );


    // =====================================================
    // TEST CASE 9
    // Doctor seeing patients
    // ===================================================== //

    hospital.displayDoctorAppointments(
        d1
    );

    hospital.doctorSeePatient(
        d1
    );

    hospital.displayDoctorAppointments(
        d1
    );


    // =====================================================
    // TEST CASE 10
    // Search Patient
    // ===================================================== //

    hospital.searchPatientByName(
        "John Doe"
    );

    hospital.searchPatientByName(
        "Unknown Patient"
    );


    // =====================================================
    // TEST CASE 11
    // Prescriptions
    // ===================================================== //

    hospital.prescribeMedicine(
        p1,
        "Paracetamol"
    );

    hospital.prescribeMedicine(
        p1,
        "Antibiotic"
    );

    hospital.displayPrescriptions(
        p1
    );


    // =====================================================
    // TEST CASE 12
    // Patient Billing
    // ===================================================== //

    hospital.displayPatientBill(
        p1
    );

    hospital.displayPatientBill(
        p2
    );


    // =====================================================
    // TEST CASE 13
    // Priority Emergency
    // ===================================================== //

    hospital.addPriorityEmergency(
        p1,
        2
    );

    hospital.addPriorityEmergency(
        p2,
        5
    );

    hospital.addPriorityEmergency(
        p3,
        3
    );

    hospital.addPriorityEmergency(
        p1,
        4
    );


    // =====================================================
    // TEST CASE 14
    // Handle Priority Emergencies
    // ===================================================== //

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();


    // =====================================================
    // TEST CASE 15
    // Room Management
    // ===================================================== //

    hospital.displayRoomStatus();


    // =====================================================
    // TEST CASE 16
    // Display All Patients
    // ===================================================== //

    hospital.displayAllPatients();


    // =====================================================
    // TEST CASE 17
    // Display All Doctors
    // ===================================================== //

    hospital.displayAllDoctors();


    // =====================================================
    // TEST CASE 18
    // Cancel Appointment
    // ===================================================== //

    hospital.cancelAppointment(
        d1,
        p2
    );


    // =====================================================
    // TEST CASE 19
    // More Doctor Appointments
    // ===================================================== //

    hospital.displayDoctorAppointments(
        d1
    );

    hospital.displayDoctorAppointments(
        d2
    );


    // =====================================================
    // TEST CASE 20
    // Hospital Statistics
    // ===================================================== //

    hospital.displayStatistics();


    // =====================================================
    // TEST CASE 21
    // Edge Cases
    // ===================================================== //

    Hospital emptyHospital;

    emptyHospital.displayPatientInfo(
        1
    );

    emptyHospital.displayDoctorInfo(
        1
    );

    emptyHospital.handleEmergency();

    emptyHospital.handlePriorityEmergency();

    emptyHospital.searchPatientByName(
        "John Doe"
    );

    emptyHospital.displayAllPatients();

    emptyHospital.displayAllDoctors();

    emptyHospital.displayStatistics();


    return 0;
}
