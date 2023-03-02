// SparkMaxMC.hpp
// Contains class for dealing with a Spark Max Motor Controller based
// on their provided documentation
//
// Author: Aiden Carney

#ifndef SPARKMAXMC_HPP
#define SPARKMAXMC_HPP


#include "CANDevice.hpp"


class SparkMaxMC : public CANDevice {
    protected:
        // Creates a can frame and sends it over the can network.
        //
        // Params:
        //    canFrameId - the integer containing 29 bits that correspond to the 
        //                 id of the can frame
        //    data       - the data to be sent
        //    nBytes     - the number of bytes to send in the packet. Same as length of
        //                 data
        // Return:
        //    int - if the frame was written successfully
        int _sendFrame(uint32_t canFrameId, uint8_t data[], int nBytes) override;


    public:
        // ctor
        //
        // Params:
        //    canDeviceId - the id to use for this motor controller. Can be set using
        //                  the REV Hardware client
        // Return:
        //    The new instance
        SparkMaxMC(int canDeviceId);


        // Takes an incoming CAN Frame and responds accordingly.
        //
        // Params:
        //    canFrameId - the integer containing 29 bits that correspond to the 
        //                 id of the can frame
        //    data       - the data to be parsed
        // Return:
        //    None
        void _parseIncomingFrame(uint32_t canFrameId, uint8_t data[PACKET_LENGTH]) override;


        // (Speed Set) sets the target velocity of the motor in RPM. 
        //
        // Params:
        //    targetRPM - the new target speed in RPM
        // Return:
        //    int - if the command was sent successfully
        int velocitySet(float targetRPM);


        // (Smart Velocity Set) sets the target velocity of the motor in RPM. 
        // Honors the max acceleration and max velocity from smart motion 
        // parameters at the firmware level
        //
        // Params:
        //    targetRPM - the new target speed in RPM
        // Return:
        //    int - if the command was sent successfully
        int smartVelocitySet(float targetRPM);


        // (Voltage Set) Sets the closed loop speed controller where the
        // target voltage is in volts
        //
        // Params:
        //    targetVoltage: - the target voltage in units of volts
        // Return:
        //    int - if the command was sent successfully     
        int voltageSet(float targetVoltage);


        // (Position Set) Sets the closed loop speed controller where the
        // target position is in rotations
        //
        // Params:
        //    targetRotations: - the target position in units of rotations
        // Return:
        //    int - if the command was sent successfully       
        int positionSet(float targetRotations);


        // (Smart Motion Set) Sets the closed loop smart motion 
        // controller where the target position is in rotations
        //
        // Params:
        //    targetPosition: - the target position in rotations
        // Return:
        //    int - if the command was sent successfully  
        int smartPositionSet(float targetPosition);


        // (Identify) Causes the motor controller LED to flash
        // rapidly so it can be identified
        //
        // Params:
        //    None:
        // Return;
        //    int - if the command was sent successfully  
        int identify();


};




#endif