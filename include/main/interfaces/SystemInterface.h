//
// Created by Saleem Hamo on 20/02/2024. Documented by Miguel Rosa
//

/**
 * @file SystemInterface.h
 * @brief Abstract base class for system interfaces.
 * @author of documentation Miguel Rosa
 *
 * Defines an interface for system operations, including initialization, activation,
 * and deactivation of a system. This class serves as a contract for all derived system
 * control classes, ensuring they implement these essential functions.
 */

#ifndef CROSSGUARD_SYSTEMINTERFACE_H
#define CROSSGUARD_SYSTEMINTERFACE_H

/**
 * @class SystemInterface
 * @brief Interface for system control classes.
 *
 * An abstract class that defines the standard interface for all system control classes.
 * It requires implementing the initialize, activate, and deactivate methods to ensure
 * that derived classes conform to expected system control protocols.
 */

class SystemInterface {
public:
    /**
     * @brief Virtual destructor.
     *
     * Ensures that derived classes can be deleted safely via a base class pointer,
     * which is crucial for polymorphic use.
     */
    virtual ~SystemInterface() {} 
    /**
     * @brief Initializes the system.
     *
     * Prepares the system for operation. Must be implemented by any derived class to
     * handle specific initialization procedures.
     */
    virtual void initialize() = 0; 
    /**
     * @brief Activates the system.
     *
     * Activates or enables the system. Implementation must define what it means for
     * the specific system to be "active."
     */
    virtual void activate() = 0; 

    /**
     * @brief Deactivates the system.
     *
     * Turns off or disables the system. Implementations must ensure that all necessary
     * procedures for safely shutting down or disabling the system are included.
     */
    virtual void deactivate() = 0;
    
    
};


#endif //CROSSGUARD_SYSTEMINTERFACE_H
