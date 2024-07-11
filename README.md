Power Functions Remote
======================

Control Power Functions from a LEGO MindStorms RCX
--------------------------------------------------
Now you can use your RCX to control LEGO Power Functions.
That's right, the RCX can act as a PF remote control but it 
can do something that the PF remote can't do yet.  The RCX
can do PWM with your PF receiver modules.

While this is based on the BrickOS firmware, you do not
need to build BrickOS to get this to work.  The Windows
executables, RCX firmware, and RCX program that you need
are included with the release.

> [!NOTE]
> Power Function capabilities are now available as part of
> [brickOS-bibo](https://github.com/BrickBot/brickOS-bibo).

Instructions
------------
1. Remove previous firmware from RCX 
   1. Remove the batteries in the RCX then turn on the RCX
   2. Replace the batteries
    
     
2. Download firmware:
   - use the following command in the DOS command shell
     `firmdl3 brickOS.srec`
   - if you have a USB tower use this command
     `firmdl3 --tty=usb brickOS.srec`
   - OR you can use BricxCC to download the brickOS.srec firmware
     (Bob: I could not get firmdl3 to work so i used BricxCC.)
 
     
3. Download the example program
   - use the following command in the DOS command shell
     `dll pf.lx`
   - if you have a USB tower use this command
     `dll -tusb pf.lx`
  
     
4. Connect a rotation sensor to sensor port 1 and sensor port 3


5. Press run on the RCX the point at a PF receiver
   - turn rotation sensor 1 to control the red port on the PF
   - turn rotation sensor 3 to control the blue port on the PF
   - press view/prgm buttons to switch PF channels


Credits
-------
Bob Kojima bob@fial.com
https://www.bong69.com/site/pages/software.php
01-20-2008
