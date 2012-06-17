Arduinball
==========

Arduinball!  Love your trashcan and be loved in return!
First (and last) version of a project so silly it can hurt you:
unleash the happiness of your trashcan for a work well done!

Each time you score - throwing a wadded-up ball of paper,
a shoe, a cat or whatever you like - your trashcan will be
so proud of you! (more proud than your own mother ever was, anyway)

Beware that this is just a draft, and not a mature project.
Also, beware that it will make you look very stupid in any
respectable circle.

Electronic
----------

Minimum requirements are a buzzer, a servo, an LED, a button
and an infrared proximity sensor (plus cables and some resistors).
Oh, an Arduino UNO will help. :-P

The arduinball.fzz file contains the Fritzing circuit diagram; for
the proximity sensor I've used a Sharp GP2Y0A02YK0F; you
may use whatever you have, but you'll probably need to fix
some values in the code.

Software
--------

Just copy the arduinball directory into your ~/sketchbook directory.
Most of it is commented, if you can understand my English.

Multimedia
----------

In the media directory, you'll find some picture that may help
you building the project (no, really: you're doing it for real?)
and a short video (sorry for the abysmally low quality of the audio).
Also, the backboard.png and backboard.svg (Inkscape format) files can
be used to create the backboard.

How it works
============

 - copy the arduinball directory into your ~/sketchbook directory
 - it needs the Arduino RRD library, which can be found here: https://github.com/alberanid/arduino-rrd
 - build the backboard and install the various pieces as you wish (I've put a small paper heart
   on the stick rotated by the servo; inside it, there a red LED).
 - upload the program to your Arduino UNO board.
 - throw something into your trashcan.
 - prepare to be loved!

Author
======

Davide Alberani <da@erlug.linux.it> (C) 2012
http://www.mimante.net/

License
=======

The music library is released under the terms of the MIT license;
the rest of the code is covered by the GPL 3 or later license.
The videos, pictures and the circuit diagram are covered by a by-sa/3.0
creative commons license.

