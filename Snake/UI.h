#ifndef ThisUI
#define ThisUI
#include "resource.h"
class UI {
public:
	virtual void processEvent(sf::RenderWindow& window)=0;
	virtual void updateUI(sf::Time delta)=0;
	virtual void renderUI(sf::RenderWindow& window)=0;

};
#endif
