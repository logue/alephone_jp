smpeg is an example portable mpeg decoding library for use with SDL.

The source code is available from: http://icculus.org/smpeg/

This library is distributed under the terms of the GNU LGPL license: http://www.gnu.org/copyleft/lesser.html

This packages contains the smpeg.framework for OS X. Conforming with Apple guidelines, this framework contains both the SDL runtime component and development header files.

Requirements:
You must have the SDL.framework installed.

To Install:
Copy the smpeg.framework to /Library/Frameworks

You may alternatively install it in <your home directory>/Library/Frameworks if your access privileges are not high enough. (Be aware that the Xcode templates we provide in the SDL Developer Extras package may require some adjustment for your system if you do this.)


Known Issues:

Currently, the MMX optimizations are not compiled in due to compile errors (shown below). Assuming this can fixed, to activate MMX optimizations, you must add the two flags to OTHER_CFLAGS_i386 in the framework and static library targets:
-Di386 -DUSE_MMX

    cd /Users/ewing/Source/SMPEGCVS/smpeg/Xcode
    /usr/bin/gcc-4.0 -x assembler-with-cpp -arch i386 -pipe -Wno-trigraphs -fpascal-strings -fasm-blocks -O3 -DNOCONTROLS -DNDEBUG -fmessage-length=0 -ftree-vectorize -mmacosx-version-min=10.4 -I/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/build/smpeg.build/Deployment/Framework.build/smpeg.hmap -Wmost -Wno-four-char-constants -Wno-unknown-pragmas -F/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/build/Deployment -F/Users/ewing/Library/Frameworks -F/Library/Frameworks -I/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/build/Deployment/include -I/Users/ewing/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL.framework/Headers -I/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/build/smpeg.build/Deployment/Framework.build/DerivedSources -Di386 -DUSE_MMX -isysroot /Developer/SDKs/MacOSX10.4u.sdk -c /Users/ewing/Source/SMPEGCVS/smpeg/Xcode/../video/mmxflags_asm.S -o /Users/ewing/Source/SMPEGCVS/smpeg/Xcode/build/smpeg.build/Deployment/Framework.build/Objects-normal/i386/mmxflags_asm.o
/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/../video/mmxflags_asm.S:7:Unknown pseudo-op: .type
/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/../video/mmxflags_asm.S:7:Rest of line ignored. 1st junk character valued 99 (c).
/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/../video/mmxflags_asm.S:49:Unknown pseudo-op: .size
/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/../video/mmxflags_asm.S:49:Rest of line ignored. 1st junk character valued 99 (c).
	/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/../video/mmxflags_asm.S:49:Rest of line ignored. 1st junk character valued 99 (c).
	/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/../video/mmxflags_asm.S:49:Rest of line ignored. 1st junk character valued 99 (c).
	/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/../video/mmxflags_asm.S:49:Rest of line ignored. 1st junk character valued 99 (c).
	/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/../video/mmxflags_asm.S:49:Rest of line ignored. 1st junk character valued 99 (c).
	/Users/ewing/Source/SMPEGCVS/smpeg/Xcode/../video/mmxflags_asm.S:49:Rest of line ignored. 1st junk character valued 99 (c).




(Partial) History of PB/Xcode projects:
2006-01-31 - First entry in history. Updated from Project Builder to Xcode for Universal Binaries. MMX code fails to compile so it is currently not compiled in.

