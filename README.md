## Fast_voltmeter for high impedance circuits  
Fast voltmeter, high impedance. Only forapproximatelly measure.  
This simple device need for measure a potential in a high-impedance circuit. Normally to measure such circuit by lamp voltmeter. I use this device for measure a potential on Geiger tube in nucleo-detector. A output element of DC-DC converter have a capacitor 0,01uf with a 380V voltage. The divider for this device is 3,8MOm to 24kOm (1:157). The measure speed is about 1Msample. Howewer, if it take fast a several samples, the capacitor don't take a dramatically discharge.  

## We can't doing it with impedance - we can do it with fast speed !!!   

Active AIN = 6  
The develop environment is IAR embedded workbench.  
It use ADC in single mode, without DMA, but with calibration.  
Howewer a calibration didn't help, I added a correction manually after test measure in 2 point: for example 20V and 300V
