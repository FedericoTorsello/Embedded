#ifndef __CONTEXT__
#define __CONTEXT__

class Context {

	bool objDetected;
  float objDistance;
  float maxDistance;

public:
  Context(float maxDistance){
    objDetected = false;
    this->maxDistance = maxDistance;
  }

  void setDetectedObj(float distance){
    objDetected = true;
    objDistance = distance;
  }

  void setNoObjDetected(){
    objDetected = false;
  }

  bool isObjDetected(){
    return objDetected;
  }

  float getObjDistance(){
    return objDistance;
  }

  float getMaxDistance(){
    return maxDistance;
  }
};

#endif
