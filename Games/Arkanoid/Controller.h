#ifndef CONTROLLER_h
#define CONTROLLER_h

#include "BallBehaviour.h"
#include <Model/Component.h>
#include <Model/Scene.h>


class Controller: public Component {
private:
	BallBehaviour* ball;
public:
	explicit Controller(GameObject*, BallBehaviour*);
	virtual void Update() override;
	virtual void Start() override;
	virtual ~Controller() override;
};
#endif //CONTROLLER_h