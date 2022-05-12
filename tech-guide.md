# EEERover Technical Guide

		During the Spring Term you should put your high-level design ideas into practice by creating the circuits, software and hardware that will implement your EEERover. This guide has three main aims: \begin{enumerate}
			\item Document the additional hardware that you are provided with to get started
			\item Specify the processes you will need to develop your design (e.g.~ordering components)
			\item Provide some implementation ideas that you may find useful
			\end{enumerate}
	
		Most of the contents of this guide is advisory. You do not have to use your EEEBug or the items in the starter kit if you wish to pursue different ideas. The only obligatory content is in Section~\ref{s:processes}, which relates to the constraints you face for budget, facilities and ordering processes.
	
 ## Starter Kit
	
		\begin{table}
			\caption{EEERover starter kit components}
			\label{t:parts}
			\footnotesize
			\begin{tabu}{lX}
				Qty.&	Description\\
				\hline
				\multicolumn{2}{l}{\textbf{EEEBug add-ons}} \\
				1&		TB6612FNG motor driver module\\
				2&		5 way PCB Receptacle, 2.54mm pitch\\
				1&		6 way PCB Receptacle, 2.54mm pitch\\
				1&		2×2 way PCB Receptacle, 2.54mm pitch\\
				1&		Adafruit Metro M0 Express (Arduino-compatible MCU board)\\
				1&		Adafruit WINC1500 WiFi Shield\\
				1&		USB cable\\
				4&		M2.5x12mm machine screw\\
				8&		M2.5 nylon nut\\
				\multicolumn{2}{l}{\textbf{Exolizard lizard simulator}} \\
				1&		Exolizard\\
				1&		8mm button magnet\\
			\end{tabu}
		\end{table}
			
		You are given one starter kit per group --- the contents are given in Table\ref{t:parts}. The parts will be kept by the technicians until you need them, so ask when you are ready. In addition to this, your EEEBug has been designed to support modification for work on this project. At the rear of the chassis is a mounting point for the Metro board and the central PCB has mounting points for the motor driver module. The breadboard, as you have already seen, is ideal for prototyping circuits but a number of mounting holes have also been provided for you to attach additional circuitry and components if you need more space. Finally, the design of the chassis is available to you in electronic format and you will have the opportunity to manufacture a modified version.
    

		
 ### Motor Driver
			\begin{figure}
				\centering
				\input{graphics/hbridge.tex}
				\caption{A single channel of the H Bridge motor driver with the truth table for decoding logic inputs DIR and PWM}\label{f:hbridge}
			\end{figure}
			The motor driver is a two-channel integrated \emph{H Bridge} with decode logic, illustrated in Fig.~\ref{f:hbridge}. One channel controls the left motor and one channel controls the right motor. Each channel has two digital inputs, DIR and PWM, which are available on J2 of the EEEBug PCB (refer to the circuit diagram in the appendix of the EEEBug instructions). The digital inputs are decoded and used to control four \emph{MOSFETs}, which are low-impedance switching transistors. The inputs can be connected directly to digital outputs on the Metro board. DIR controls the motor direction and the motor speed can be controlled by applying a rectangular waveform to the PWM input and varying the duty cycle. The motor driver plugs into J4 and J5 of the EEEBug PCB.
			
		\subsection*{Metro board}
			The Adafruit Metro M0 Express board is a embedded computing platform based on an ARM M0 microcontroller and compatible with the Arduino form factor, libraries and development tools. It is programmed in C++ and features digital inputs and outputs, inputs with digital-to-analogue conversion and PWM outputs. Internet connectivity is provided by a Adafruit WINC1500 WiFi Shield, which plugs into the Metro board.

			You are provided with demonstration code (see the labweb website) that shows the use of basic functions of the Metro board. The WiFi interface is used to host a basic webpage, which you will see hard-coded into the demonstration code. The webpage provides two links which, when pressed, turn on and off the onboard LED. Use the Arduino Serial Monitor to connect to the board via USB and you will see some debug messages reporting on the connection status. Whenever the webpage is retrieved you will see the HTML request made by the web browser.
			
			Arduino is a popular platform for prototyping and you will find a lot of information and many code examples on the internet. Use these resources but beware that many are provided by third parties and may not be well-written or even correct! 
			
			\subsubsection*{Arduino IDE}
			You can install the Arduino IDE on your own computers by visiting the Arduino website. Additional libraries are needed to work with the Metro board and WiFi module. Follow the instructions at \href{
			https://learn.adafruit.com/experimenters-guide-for-metro/setting-up-your-metro}{\texttt{learn.adafruit.com}}
			to add support for the Metro board.
			
			The WiFi communication functions are provided by the WiFi101 library, which also must be installed with the Library Manager. The library installs its own set of example sketches and the reference is here: \url{https://www.arduino.cc/en/Reference/WiFi101}. The demonstration code from Labweb is based on these examples.
		
			
 ### Connections and Power
			\begin{figure}
				\includegraphics[width=\textwidth]{graphics/Adafruit_Metro_M0_Express_Pinout.png}
				\caption{Diagram showing the key components of the Adafruit Metro M0 module. From \url{https://learn.adafruit.com/assets/110930}}
				\label{f:arduino}
			\end{figure}
			
			(see Fig.~\ref{f:arduino})
			
			The logic level of the Metro board is 3.3V, which is supplied by an on-board voltage regulator. \textbf{You will damage the board if you connect the input/output pins to a voltage greater than 3.3V!} Use potential dividers to reduce voltages greater than 3.3V and test your circuits before connecting them to the Metro board. The safest option is to design add-on circuits with a 3.3V power supply. Digital inputs should be 0V for logic low and 3.3V for logic high. Analogue inputs should be in the range 0--3.3V.
			
			The pin locations and functions are broadly compatible with the Arduino layout used on the Orangepip Kona328 board used in the Microcontroller lab experiment. The I/O pins pass through the WiFi Shield when it is connected, but the pins labelled CS, IRQ and RST on the WiFi Shield (Arduino pins 5,7 and 10) are used by WiFi and can't be used for other purposes. 
			
      ![metro-power](https://user-images.githubusercontent.com/4660308/168094499-c8400774-8b45-464e-aa2f-800d0181cbf0.svg)
			
      \caption{A simplified diagram showing the connection of the Metro board power supply, battery and motor supply}\label{f:power}
			The Metro board can be powered by USB or by the EEEBug batteries. There is also a power jack but that is not needed. To connect to the EEEBug batteries you will need to make the following connections between the Metro board and the EEEBug PCB:\begin{itemize}
			\item 5V$\rightarrow$5V
			\item GND$\rightarrow$GND
			\end{itemize}
			\textbf{Always check these connections before switching on the power. You may damage the microprocessor if you make a mistake!}
			
			The Metro board will automatically take power from the USB cable if battery power is not present. The 5V terminals on the Metro board are powered by USB in this case so the USB connection will continue to power other circuitry connected to 5V if the battery is turned off. However, recall that the EEEBug PCB contains a diode between the battery and the 5V terminals. The diode prevents the 5V power rail from feeding back to the motor driver, so the motors will only operate if batteries are inserted and the EEEBug power switch is turned on. Fig.~\ref{f:power} shows the interaction of the battery and USB power supplies.
			
			You can connect your own circuits to the 5V or 3.3V connections on the EEEBug PCB or Metro board. However, the 3.3V regulator on the Metro board can only supply a limited current and if you connect too large a load the microprocessor will not work.
			
      
 ### WiFi
			The demo code is configured to connect to a stand-alone WiFi network \texttt{EEERover} that is set up in the lab. Before uploading the demonstration code, change the IP address defined in the code to the value \texttt{192.168.0.}$n$, where $n$ is the number of your Metro board written on a label on the board. Once you have uploaded the code, connect to the EEERover network with a laptop or other device  (password \texttt{exhibition}) and use a web browser to access your IP address, for example \url{http://192.168.0.1/}.
			
			You will see in the code how you can define which WiFi network the Metro board will connect to. You can change it to connect to other networks, but it is not possible to connect to networks secured with WPA2-enterprise, including the Imperial College network.
			
			It is also possible for the board to host its own WiFi network --- see the example in \texttt{WiFi101} → \texttt{AP\_SimpleWebServer}. Please connect via the EEERover network if you are in the lab because communication over many different WiFi networks will cause interference and unreliable connections.
			
			\subsubsection*{Power}

			\subsubsection*{Mounting}
			The Metro board can be mounted on the space at the back of your EEEBug. Insert the M2.5x12mm screws from the underside of the chassis and secure them with one nylon nut per screw. The Metro board is then located on top so that the nuts act as a spacers to hold it clear of the chassis. The additional nuts can be added on top of the Metro board to secure it but not all of these will fit due to the proximity of components to the mounting holes.
	
 ### Exorock mineral simulator
      
      ![exorock](https://user-images.githubusercontent.com/4660308/168095519-44b9d1c9-ec1a-468f-af53-7b428f99cf31.jpg)
      
      ![exorock-flow](https://user-images.githubusercontent.com/4660308/168096296-662e0d1e-3798-4e09-81d1-5d50be0c499b.svg)
			
			Your prototype will be developed and tested using Exolizard simulators: electronic devices which can replicate the properties of the lizards that you are searching for. An Exolizard is provided to you to aid your development. Fig.~\ref{f:exolizard} shows the underside of an Exolizard with access to the control switches. Figs.~\ref{f:xltop} and~\ref{f:xlbot} show the arrangement of key components on the internal circuit board. 
					
			The Exolizard is configured by setting a group of DIP switches on the PCB. A push button is used to turn it on and off, and an LED indicates when it is active. A flow chart depicting the operation of the Exolizard is given in Fig.~\ref{f:modes}. From standby, press the button to turn on and observe the LED to determine whether the battery has sufficient charge. After the battery display sequence is complete the Exolizard begins emitting signals according to the mode set up on the DIP switches. The LED flashes a code at intervals to confirm the mode selection and indicate operation.
		
			Pushing the button during operation will reset the Exolizard --- this is necessary to change the operation mode. A second press, occurring during the battery sequence, will turn the device off. If the Exolizard is left operating for five minutes it will automatically power off to preserve the battery.
			
			The Exolizard cannot simulate the magnetic property in an readily-configurable manner so you are provided with a small magnet to test this functionality. In the demo, magnets will be fixed underneath the top skin of the lizard --- allow a skin and adhesive thickness of 5mm when testing the range of your sensor.
			
			The emitted infrared signal is strongest above the exolizard, while the ultrasonic signal emits from the mouth. The radio signal is not precisely located, although you can observe the orientation of the antenna coil on the internal PCB.

	
			
			
 ## Components and Construction
		\label{s:processes}
 ### Ordering components
			A tool for ordering components is provided in the downloads section on Labweb: \url{https://intranet.ee.ic.ac.uk/intranet/labweb/downloads/}.\\Each project group has a budget of £50 to cover all the additional components you'll need for designing and building your prototype. 
			When you first open the ordering system you will need to allocate a treasurer for the group, who will be responsible for managing the budget and placing orders. Each order you create must be approved by another group member. Group members receive emails when an order is placed and the approver will receive an email when the parts are available for collection from Stores on level 1, near the lifts. Orders, assuming the items are in stock, will take up to a week to arrive. You can order some components directly from stores stock and these will usually be available for collection sooner.
			
			The ordering tool contains links and a browsing window for choosing parts from the department's approved suppliers. When you have selected a part, copy the information into the form to add it to the order. Please be aware of the following rules and common pitfalls when ordering components:
			\begin{itemize}[noitemsep]
				\item You must only order items that you can use safely. If you have any doubts about this then talk to a member of staff before ordering. Do not order chemicals (including glue), tools or mains-powered equipment/parts without consulting staff.
				\item Always check that the supplier holds sufficient stock. If an item is out of stock it will be placed on back-order and it may take months to arrive. Try to find an alternative part or supplier instead.
				\item Some suppliers offer stock from sister companies around the world. Do not order any items which warn about additional delivery charges.
				\item Many electronic components are \emph{surface mount}. This means that they sit on flat pads on a PCB instead of having flexible leads to insert into a prototyping board. They are also usually very small. You will find surface mount components difficult to use so avoid them by checking item descriptions carefully.
				\item You need to maintain the goodwill of the stores staff to order parts for this project and future projects. Do not chase the staff for your order until one week has passed from placing the order. It is your responsibility to check parts for suitability and availability.
			\end{itemize}
			
 ### Ordering a new chassis
			You can use the ordering tool to buy a new laser-cut chassis for your EEERover. Since these are made to order there are two limited windows for purchasing them: \begin{enumerate}[noitemsep]
				\item Order by 17:00 on 1 March for delivery on 11 March
				\item Order by 17:00 on 26 April for delivery on 6 May
			\end{enumerate}
			
			You can download a design file for the EEEBug chassis from labweb in PDF format --- it is recommended that you use this as a template. You will see that cut lines are drawn in red and engrave lines are drawn in blue. Laser cutting removes a tapering width of material known as a \emph{kerf}, which for 3mm acrylic is typically 0.1mm at the bottom of the material and 0.3--0.4mm at the top. Hence, cut edges are not vertical, external dimensions will be slightly smaller than drawn and internal dimensions slightly larger than drawn.
			
			Designs for laser cutting must be submitted in PDF format. Two sizes are available to order and the entire design must fit within the quoted dimensions. Multiple separate parts can be ordered as long as they are laid out in an area that fits the selected order size. Each part must be engraved with your group name. You are strongly recommended to check your design by printing it on paper first --- the scaling will be identical as long as the same PDF file is used.
			
		\subsection*{3D printing and Workshop facilities}
			A basic workshop is available in the lab. To use it talk to Vic and be prepared to explain exactly what you want to do and demonstrate that you are capable of doing it safely. You can also have components 3D printed if you are willing to learn the necessary design techniques independently. Talk to Amine in the technicians' office if you would like to use 3D printing.
			
		
			
 ## Implementation Hints
			The table of material types from the design brief as follows:
			
			\noindent
			\begin{small}
		\begin{tabu}{lp{5.5cm}p{4.5cm}}
				Species&	Property 1 &	Property 2\\
				\hline
				Gaborus&		61kHz radio modulated `\#GAB' &	Acoustic signal at 40.0kHz\\
				Nucinkius&		61kHz radio modulated `\#NUC' &	None\\
				Durranis&		89kHz radio modulated `\#DUR' &	Magnetic field up\\
				Pereai&			89kHz radio modulated `\#PER' &	Magnetic field down\\
				Cheungus&		Infrared pulses at 353Hz &					None\\
				Yeatmana&		Infrared pulses at 571Hz &					Acoustic signal at 40.0kHz\\
				
			\end{tabu}
			
			\end{small}
			
  ### Radio
			Four material types emit radio waves, but you can choose the amount of discrimination that you can provide. Do you need to distinguish between the carrier frequencies? Do you need to decode the messages?
			
			It is recommended that you use a tuned coil antenna to pick up the signal. This is essentially an air-cored inductor with a reasonably large diameter, which you can make by coiling wire. This inductor can then be used in a tuned circuit that will be most sensitive at the resonant frequency. There are only two carrier frequencies to detect so you do not need the continuous adjustment of tuning that you get with an audio radio receiver, for example.
			
			The signal amplitude generated by your antenna will be small so it will need amplification before you can use it to indicate detection. The microcontroller will struggle to sample the radio signal at its carrier frequency so you will need to perform demodulation with \emph{envelope detection} to produce a signal which indicates the amplitude of the signal. The easiest way to do this is by rectification. The on-off modulation is a form of \emph{amplitude modulation}, where the amplitude of the signal varies between 1 and 0.
			
			You will find it difficult to trigger the oscilloscope on the radio signal because the carrier frequency contains many edges and it's hard to pick out the first rising edge of the coded transmission. Try changing the trigger mode to pulse width: this allows you to detect the UART start bits, where the signal is zero for at least one bit period, while ignoring the cycles of the carrier frequency.
			
			You can decode the messages by sampling the signal at the required bit rate and reforming the characters bit by bit. You can also use a built-in decoder on the microprocessor. The UART interface  \texttt{Serial} is suitable but is already used for the USB connection. You may see UART ports created with the \texttt{SoftwareSerial} library but this is not supported by the Metro microprocessor. There are instructions for creating additional UART ports on the Metro board at \href{https://learn.adafruit.com/using-atsamd21-sercom-to-add-more-spi-i2c-serial-ports}{\texttt{learn.adafruit.com}}.
			
 ### Infrared
			You have already made a light sensor as part of the EEEBug and most silicon-based photosensors (such as the EEEBug phototransistor) are just as sensitive to infrared as visible light. However, the optical power given by the Exolizard is weaker than the light source you used for the EEEBug so a greater amount of amplification may be needed than the bipolar transistor which you used before. You may need to measure the pulse frequency of the signal and this can be done with analogue or digital methods.
			
 ### Ultrasonic and magnetic
			The magnetic field of the Exolizard is static, meaning that it will not induce a current in a coil of wire unless that coil is moving. A moving coil is a possibility, but there are also sensors and switches that can detect a static magnetic field. Test any new components and read their datasheets to determine if any amplification or signal processing is required. You may need to sense the polarity of the magnetic field.
			
			Sensors are also readily available for detecting ultrasonic signals. Amplification may or may not be necessary, depending on the sensitivity of your sensor. As with the radio receiver, rectification will convert the high-frequency audio signal into a voltage representing the amplitude. Most ultrasonic transducers have a resonant frequency at which they are most sensitive. Check component datasheets to confirm the frequency sensitivity of any sensor you are planning to use.
			
 ### Opamps
			You may wish to implement amplification or filtering using an opamp. There are many different opamps and they have different specifications. Some manufacturers have parametric search facilities on their websites to narrow down the options based on your specifications. Look at the appendix of the opamps experiment instruction to see an example of how the LT1366 device was selected for that application.
			


\end{document}
