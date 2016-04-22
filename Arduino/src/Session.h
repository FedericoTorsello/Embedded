#ifndef __SESSION__
#define __SESSION__

class Session {
public:
    Session();
    Session(bool initialSession);
    bool isEnabled();
    void setSession(bool value);
private:
    bool currentSession;
};

#endif
