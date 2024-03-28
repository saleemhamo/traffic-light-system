//
// Created by Saleem Hamo on 20/02/2024.
//

#ifndef CROSSGUARD_SYSTEMINTERFACE_H
#define CROSSGUARD_SYSTEMINTERFACE_H

class SystemInterface {
public:
    virtual ~SystemInterface() {}  // Virtual destructor for safe polymorphic use
    virtual void initialize() = 0;  // Prepare the system for operation
    virtual void activate() = 0;    // Activate the system
    virtual void deactivate() = 0;  // Deactivate the system

};


#endif //CROSSGUARD_SYSTEMINTERFACE_H
