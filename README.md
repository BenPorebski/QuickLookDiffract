osc-quicklook-plugin
====================

An OSX quicklook plugin for displaying diffraction image data


NOTES

- Diffraction images are created by using modified version of diff2jpeg.
- When previews are generated, they are stored as jpeg files in /tmp/
- You can clear the /tmp manually or it will be cleared on reboot.
- Diff2jpeg is part of the CCP4 DiffractionImage package, licenced under the GNU GPL v2.
  - The modifications to Diff2Jpeg are included in this repository.
  - The modifications allow for specifying where to write the jpeg file.
- A binary version of Diff2Jpeg is included.

INSTALL

1. Compile, then copy and paste the osc.qlgenerator files to ~/Library/QuickLook/
	(If the folder does not exist, create it)

2. If the plugin does not work immediately, you can refresh the quicklook daemon with:
	
	qlmanage -r

If you are stuck or having problems with the plugin, please email me: ben@inoxx.net or ben.porebski@monash.edu
