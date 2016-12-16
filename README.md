# Chamberlab Score Viewer

A horizontal scrolling viewer synced to Ableton Live via the [ChamberBridge](https://github.com/dasantonym/ChamberBridge) for displaying experimental notation during our concerts. This is a quick and dirty sketch for internal use and the scrolling is still bad.

## Dependencies

* [OpenFrameworks ^0.9.8](http://openframeworks.cc/download/)
* [A fork of ofxGiantImage](https://github.com/dasantonym/ofxGiantImage)

## Usage

Put your a score graphic(s) in JPEG format inside the ``bin/`` folder (the folder must be right next to the app). Then edit the file ``bin/keys.xml`` as follows: The tags ``<key-0>`` specifies the filename to be loaded for key ``0`` and ``<key-0-pps>`` declares the resolution in pixels per second. You can set up keys 0-9 with this system.

Start the app and press the number of the score you'd like to load. The score is displayed without zoom from left to right and top to bottom (e.g. if your screen is 1920x1080 then your score could be 20000x1080).

You can show detailed infg by pressing 'i', toggle fullscreen by pressing 'f' and toggle the metrum (only available when connected to Live) by pressing 'm'.

Press 'Space' to play the score without being connected to Live.

Exit the app with 'Esc'. **Important:** On the first run you need to exit using 'Esc' to create the file ``bin/keys.xml``.
 
## Issues

* The time signature is not read from Live yet and always remains on 4/4
* Tempo changes are picked up but on first start you might need to stop Live, then start the app and then start Live again.
* The clock connection is not very smooth so the score will judder
* Probably more...
