#pragma once
namespace Core { 

class Controller {
private:
    /* data */
public:
    virtual void execute();

    virtual String toString();
};


String Controller::toString() {
    return F("");
}
}