
//Your declarations and implementations would go here
class Event {
public:
    Event(string name) {
        m_name = name;
    }
    virtual ~Event() {};

    string name() const{
        return m_name;
    }
    virtual bool isSport() const {
        return true;
    }
    virtual string need() const = 0;


private:
    string m_name;

};

class BasketballGame:public Event {
public:
    
    BasketballGame(string name) : Event(name) {}

    ~BasketballGame() {
        cout << "Destroying the " + this->name() + " basketball game" << endl;
    }

    string need() const {
        return "hoops";
    }

};

class Concert:public Event{
public:

    Concert(string name, string genre) : Event(name), m_genre(genre) {};

    ~Concert() {
        cout << "Destroying the " + this->name() + m_genre << endl;
    }

    string need() const {
        return "stage";
    }
    bool isSport() const {
        return false;
    }

private:
    string m_genre;

};

class HockeyGame:public Event {
public:

    HockeyGame(string name) : Event(name) {}

    ~HockeyGame() {
        cout << "Destroying the " + this->name() + " hockey game" << endl;
    }

    string need() const {
        return "ice";
    }
    bool isSport() const {
        return false;
    }
};

