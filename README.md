Remote control using NRF24 and digital servo for steering.  I have used 2 NANO/NRF24 transmitter units one for speed and direction, and the second for steering.  Both use the same data pipe to send a data array. The array holds the speed, direction and steering. Using two transmitters seems to give a much better data transmission.  Both NANO’s use a joystick connected to A0, one for forward reverse and speed. The second for left, right and straight. The data is added to the arrays and sent to the receiver. The UNO receiver is connected to a motor driver and servo, this method seems to be 100% reliable. There are two sets of sketches one using “Serial. Print” for diagnostics, the second has no “Serial. Print”  and to 40% smaller.