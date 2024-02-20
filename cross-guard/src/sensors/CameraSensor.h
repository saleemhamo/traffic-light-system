//
// Created by Saleem Hamo on 07/02/2024.
//

#ifndef _CROSS_GUARD_CAMERASENSOR_H
#define _CROSS_GUARD_CAMERASENSOR_H

class CameraSensor {
public:
    CameraSensor();

    ~CameraSensor();

    void initialize();

    bool detectMovement();  // Simulates detecting movement using the camera
};

#endif //_CROSS_GUARD_CAMERASENSOR_H
