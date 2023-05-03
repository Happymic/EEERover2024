# ELEC40006 Electronics Design Project 
## Project Brief: EEERover
	
## Introduction
	
		\begin{figure}
			\centering
			\includegraphics[width=\linewidth]{moon.jpg}
			\caption{The moon}
			\label{f:moon}
		\end{figure}

Most of the Summer Term study time is allocated to the Engineering Group Design Project, which is one of the six modules that make up your first year of study.
It brings together theoretical and practical content from your lectures and labs with important industrial skills relating to product design, project management and team working.
		
You will work in tutorial groups of 5–7 people to complete the project.
It will be assessed with an interim interview, a final report, and a demo.
		
## Brief

You are requested to design a remotely-controlled rover that can explore a remote planet and survey the creatures that live there.
Using a variety of electromagnetic signals, you must find out the name, age and magnetic polarity of each alien.
  
A prototype of the design must be built and tested in an artificial environment in the lab.
The quality of the design will be assessed against the following criteria:
- Is it possible to find the characteristics of all the aliens?
- Is the design cost and weight effective?
- Is the rover manoeuvrable enough to negotiate the environment?
- Is the construction robust and reliable?
- Is the remote control interface logical and easy to use?
	
## Characteristics of the aliens
### Name

The aliens communicate with radio waves and each alien will tell you its name.
Communication uses a carrier frequency of 89kHz, modulated with two-level *amplitude-shift keying* (on off modulation).
The name is encoded using ASCII character codes in UART packets with 1 start bit and 1 stop bit.
The data rate is 600 bits per second and each alien's name is four characters long, including an initial `#` symbol.
	
- [ ] Add diagram of modulation
	
### Age

Aliens have a pulse that can be detected optically, just like humans.
As with humans, the pulse tends to slow with age, though the correlation is much stronger — the period of the pulse increases at exactly 1ms per century of lifetime.
Unlike humans, aliens emit infrared radiation at a wavelength of 950nm, allowing the pulse to be detected by passive observation with a suitable sensor.
	
Aliens spend the first century of their lives underground, so you won't encounter any aliens younger than that.
	
### Magnetic field

Most aliens have a static magnetic field orientated with their body.
In some aliens the field points away from the top of their head, in others it points towards.
Some aliens have no magnetic field at all.
	
## Deliverables and assessments
	
The project will be assessed with a report, a show-and-tell group interview and a head-to-head competition.
	
### Report
			\textbf{Date of submission:  19 June 2022}\\
			The report is a formal documentation of all the technical and non-technical work you have done on the project. By this time all your design decisions will have been made and you will be able to document the performance of various aspects of your prototype. You should also have a clear plan for any work outstanding before you can complete the demonstration. One team member should act as overall editor to ensure that the report is consistent in style and content.
			Marks awarded: 50\%

### Group Interview
			\textbf{Date of assessment:  24 June 2022}\\
			The group interview will take place immediately before the demo and it is an opportunity for you to show your examiner the details of your implementation and answer their technical questions.\\
			Marks awarded: 30\%
			
### Demo
			\textbf{Date of assessment:  24 June 2022}\\
			The demo will take place as a contest between three or four rovers in a test arena. You must try to identify all the rocks in the fastest time without colliding with the obstacles or other rovers.\\
			Marks awarded: 20\%
	
## Getting started
				
### EEEBug Expansion Kit
Your EEEBug has been designed to support modification for work on this project.
The Orangepip will be replaced with an ARM-based microcontroller platform with a WiFi module, but you can continue to develop code using the Arduino framework and IDE.
The central PCB has connections for a motor driver module, which will simplify the challenge of steering and reversing your rover.
			
### Sensing
You should use the outcome of your lab experiments to develop ideas for making sensors and analogue interfaces to detect the signals.
The EEEBug experiment showed you an example of an optical sensor.
The Passive Networks experiment (Autumn Term) introduces the concept of resonant circuits which, if the inductor is suitably constructed and orientated, will oscillate in the presence of radio waves of the correct frequency.
Magnetic sensors are not covered directly in the labs and you should carry out your own research in this area.
			
In certain cases you may wish to detect particular frequencies while blocking others, and you have explored to do this with passive and opamp-based circuits.
Some sensors will produce a weak signal that will need amplification.

Signals will need to be converted into the digital domain for transmission back to the rover operator.
Consider whether a binary input is sufficient, or you need to measure the voltage with more precision.
Research software libraries that can help you determine time-domain characteristics such as frequency or serial data encoding.
			
### Construction
Mechanical design is not a core component of the EEE/EIE degree so it is left to you to be innovative in the construction of your rover.
The EEEBug chassis is designed to be a useful platform but feel free to modify it, taking into account the budget and weight constraints.
			
You can download a computer-aided manufacturing (CAM) drawing of the chassis, which can be modified for reproduction in acrylic with a laser cutter.
Workshop facilities are available on arrangement with the lab technicians.
You may wish to consider 3D printing, though you will need to research and teach yourself the necessary techniques first.
3D printers are available to use with the help of the lab technicians.	

### Demo Environment
The demo environment has a smooth floor with some uncrossable obstacles.
Aliens will be distributed across the environment, spaced at least 500mm apart.
Some aliens are very sensitive and they won't communicate if a heavy rover is nearby.
The arena is fitted with sensors in one area to check the weight of your rover.
