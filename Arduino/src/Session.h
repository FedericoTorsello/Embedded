#ifndef __SESSION__
#define __SESSION__

class Session {

  int currentSession;

public:
  Session();
  Session(int initialSession);
  int getSession();
  void setSession(int value);
};

#endif
