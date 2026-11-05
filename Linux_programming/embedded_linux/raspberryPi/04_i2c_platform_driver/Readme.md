Linux I2C Drivers Detailed : Master, Slave & User Space Drivers
1: I2C High Level Analysis
- I2C communication protocol basics/terminology
- I2C Modes
- I2C Communication Protocol Format
- Bus arbitration loss
- Clock Stretch
- AM3358 Controller (master) I2C specifications & Block Diagram
- ADXL345 & DS1307 (Slave) specifications

2: I2C Low Level Analysis
- Understanding I2C Registers for AM3358 Controller.
- Understanding Accelerometer Sensor [ADXl345] & RTC [DS1307] Specifications, comm.
Protocol format and register programming model.
- Master Slave interface Block Diagram.

3: Developing I2C Master & Slave Drivers in u-boot Space
U-boot Level
- Add I2C Mux/Pad Configuration in board specific mux file.
- Scan I2C Slave device using I2C command in prompt.
- Test basic communication with slave device using I2C command in u-boot command
prompt.

4: Developing I2C Master & Slave Drivers in Kernel Space
Kernel Level
- Add I2C Master/Slave driver platform data in to Device tree source code
- Integrating platform (I2C Master) driver and slave driver with framework.
- Check Probe and initialization functions both Master and slave drivers.
- Registering I2C master/adapter and slave drivers

5: Developing I2C Master & Slave Drivers in User Space
User Level
- Disable I2C Slave driver and test I2C Master Driver with User space driver (i2c-dev)
absent of I2C Slave driver.
- Enable I2C Slave driver and test I2C slave driver with device specific applications.
Session 6: Understanding the complete flow
- Understanding I2C Master, slave initialization and device operation source code flow
from bottom to top vice versa.
- Understanding I2C Interrupt flow with I2C Debug options.