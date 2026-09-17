#include <bits/stdc++.h>
using namespace std;

// Notification creation
class INotification
{
public:
    virtual string getContent() = 0;
    virtual ~INotification() = default;
};

class SimpleNotification : public INotification
{
private:
    string text;

public:
    SimpleNotification(string text) : text(text) {}
    string getContent()
    {
        return text;
    }
};
class INotificaionDecoder : public INotification
{
protected:
    INotification *notification;

public:
    INotificaionDecoder(INotification *n)
    {
        notification = n;
    }
    ~INotificaionDecoder()
    {
        delete notification;
    }
};

class TimeStampDecorator : public INotificaionDecoder
{
public:
    TimeStampDecorator(INotification *n) : INotificaionDecoder(n) {}
    string getContent()
    {
        return "[Time and Date] " + notification->getContent();
    }
};
class SignatureDecorator : public INotificaionDecoder
{
    string signature;

public:
    SignatureDecorator(INotification *notification, string signature) : INotificaionDecoder(notification), signature(signature) {}
    string getContent()
    {
        return notification->getContent() + "\n" + signature;
    }
};

// Notification Observer

class Iobserver
{
public:
    virtual void update() = 0;
    virtual ~Iobserver() = default;
};
class Iobservable
{
public:
    virtual void addObserver(Iobserver *observer) = 0;
    virtual void removeObserver(Iobserver *observer) = 0;
    virtual void notify() = 0;
    virtual ~Iobservable() = default;
};

class NotificationObservable : public Iobservable
{
    vector<Iobserver *> observers;
    INotification *notification;

public:
    void addObserver(Iobserver *observer)
    {
        if (find(observers.begin(), observers.end(), observer) == observers.end())
        {
            observers.push_back(observer);
        }
    }
    void removeObserver(Iobserver *observer)
    {
        auto it = find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
        {
            observers.erase(it);
        }
    }
    void notify()
    {
        for (auto &it : observers)
        {
            it->update();
        }
    }
    void setNotification(INotification *notification)
    {
        if (this->notification)
        {
            delete this->notification;
        }
        this->notification = notification;
        notify();
    }
    string getNotificationContent()
    {
        return notification->getContent();
    }
    ~NotificationObservable()
    {
    }
};

class Logger : public Iobserver
{

    NotificationObservable *observable;

public:
    Logger(NotificationObservable *observable)
    {
        this->observable = observable;
        observable->addObserver(this);
    }
    void update()
    {
        cout << "Getting notification through logger:\n";
        cout << observable->getNotificationContent() << endl;
    }
    ~Logger()
    {
    }
};

class INotificationService
{
public:
    virtual void send(string content) = 0;
    virtual ~INotificationService() = default;
};

class NotificationEngine : public Iobserver
{
    NotificationObservable *observable;
    vector<INotificationService *> services;

public:
    NotificationEngine(NotificationObservable *observable) : observable(observable)
    {
        observable->addObserver(this);
    }
    void update()
    {

        string content = observable->getNotificationContent();
        for (auto &service : services)
        {
            service->send(content);
        }
    }
    void addService(INotificationService *service)
    {
        services.push_back(service);
    }
    ~NotificationEngine()
    {
        for (INotificationService *n : services)
        {
            delete n;
        }
    }
};

class EmailService : public INotificationService
{
public:
    void send(string content)
    {
        cout << "Sending notification through Email: " << content << endl;
    }
};

class SMSService : public INotificationService
{
public:
    void send(string content)
    {
        cout << "Sending notification through SMS: " << content << endl;
    }
};

class NotificationSystem
{
private:
    NotificationObservable *observable;
    vector<INotification *> notifications;

public:
    NotificationSystem(NotificationObservable *observable) : observable(observable)
    {
    }
    void send(INotification *notification)
    {
        notifications.push_back(notification);
        observable->setNotification(notification);
    }
};
int main()
{
    NotificationObservable *observable = new NotificationObservable();
    NotificationSystem system(observable);

    NotificationEngine *engine = new NotificationEngine(observable);
    Logger *logger = new Logger(observable);
    engine->addService(new EmailService());
    engine->addService(new SMSService());

    string text = "Good Moring";
    INotification *notification = new SimpleNotification(text);
    notification = new TimeStampDecorator(notification);
    notification = new SignatureDecorator(notification, "--Customer case");
    cout << notification->getContent() << endl;

    system.send(notification);

    notification = new SimpleNotification("Good Night");
    system.send(notification);


    observable->removeObserver(engine);
    observable->removeObserver(logger);

    delete engine;
    delete logger;
    delete observable;
    return 0;
}