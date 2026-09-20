3-Key Macropad
A custom 3-key mechanical keyboard macropad powered by a Seeeduino XIAO microcontroller. Designed with a clean sandwich-mount case featuring an integrated USB port cutout.

Features
Compact 3-key layout designed for custom shortcuts and macros.

Sandwich-mount switch plate architecture for a solid typing feel.

Custom-machined case base with a 3mm floor and internal clearance for wiring and the XIAO microcontroller.

Tailored USB-C port cutout for seamless cable connection.

Bill of Materials (BOM)
Microcontroller: Seeeduino XIAO (RP2040 or SAMD21)

Switches: 3 x Cherry MX compatible mechanical switches

Keycaps: 3 x MX-compatible keycaps

Case & Plate: 3D printed case base and switch plate (STL files included)

Wiring: Hookup wire or a custom PCB matching the layout

3D Printing & Assembly
Print the Files: Slice and print the exported case base and switch plate STL files. Recommended print settings include 0.2mm layer height and at least 20% infill.

Mount the Plate: Snap your 3 mechanical switches into the switch plate cutouts.

Wire the Switches: Wire the switches to your Seeeduino XIAO using a standard matrix or direct GPIO wiring approach.

Assemble the Case: Place the wired assembly into the internal cavity of the case base, aligning the USB-C port with the rear cutout, and secure the plate to the top rim.

Firmware
This macropad is compatible with custom firmware platforms like QMK or CircuitPython depending on your Seeeduino XIAO variant. Configure your pin mappings according to the GPIO pins connected to your switches.
