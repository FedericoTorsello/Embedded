#ifndef __SESSION__
#define __SESSION__

class Session {
public:
  Session();
  Session(int initialSession);
  int getSession();
  void setSession(unsigned int value);
private:
  unsigned int currentSession;
};

#endif
