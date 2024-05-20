#include <iostream>
#include <string>
#include <map>
using namespace std;

class ISite {
public:
    virtual string GetPage(int num) = 0;
    virtual ~ISite(){}
};

class Site : public ISite {
public:
    string GetPage(int num) override {
        string page = "site page" + to_string(num);
        return page;
    }
};

class SiteProxy : public ISite {
private:
    ISite* site;
    map<int, string> cache;
public:
    SiteProxy(ISite* site) : site(site){}
    ~SiteProxy() {
        delete site;
    }

    string GetPage(int num) override {
        string page;
        if (cache.find(num) == cache.end()) {
            page = site->GetPage(num);
            cache[num] = page;
        }
        else {
            page = cache[num];
            page.insert(0, "from: ");
        }
        return page;
    }
};

int main() {
    ISite* mysite = new SiteProxy(new Site());
    cout << mysite->GetPage(1) << "\n";
    cout << mysite->GetPage(2) << "\n";
    cout << mysite->GetPage(3) << "\n";

    cout << mysite->GetPage(2) << "\n";
}