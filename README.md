# Chamberlab Score Viewer

A horizontal scrolling viewer synced to Ableton Live via the [ChamberBridge](https://github.com/dasantonym/ChamberBridge) for displaying experimental notation during our concerts. This is a quick and dirty sketch for internal use and the scrolling is still bad.

## Dependencies

* [OpenFrameworks ^0.9.8](http://openframeworks.cc/download/)
* [A fork of ofxGiantImage](https://github.com/dasantonym/ofxGiantImage)

## Usage

Put your a score graphic in JPEG format inside the ``bin/`` folder (the folder must be right next to the app) and name it ``score.jpg``.

Start the app and press 'L' to load the score graphic. The score is displayed without zoom from left to right and top to bottom (e.g. if your screen is 1920x1080 then your score could be 20000x1080).

You can show detailed infg by pressing 'I' and change the PPS (pixels per second) mapping of time in Ableton Live and the pixels of your score document.

Toggle fullscreen by pressing 'F', hide and show the metrum by pressing 'M'.
 
## Issues

* The time signature is not read from Live yet and always remains on 4/4
* Tempo changes are picked up but on first start you might need to stop Live, then start the app and then start Live again.
* The clock connection is not very smooth so the score will judder
* Probably more...
